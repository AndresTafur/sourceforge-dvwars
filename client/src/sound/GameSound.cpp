/*
 *  Copyright (C) 2011-2013 Jorge A. Tafur Q. (jatafurq).
 *
 *  This file is part of Da Vinci Wars project.
 *
 *  Da Vinci Wars is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Da Vinci Wars is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Da Vinci Wars.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "GameSound.h"


GameSound::GameSound() : Thread()
{

        alutInit(NULL,NULL);

        alGenBuffers(4, buffers);
    	alGenSources(1, &source);

        alSource3f(source, AL_POSITION,        0.0, 0.0, 0.0);
    	alSource3f(source, AL_VELOCITY,        +20.0, 0.0, 0.0);
    	alSource3f(source, AL_DIRECTION,       0.0, 0.0, 0.0);
    	alSourcef (source, AL_ROLLOFF_FACTOR,  0.0          );
    	alSourcei (source, AL_SOURCE_RELATIVE, AL_TRUE      );

    	fprintf(stderr,"Source and buffers generated\n");
    	m_running = false;
}

bool GameSound::open(std::string path)
{

        m_path = path;

		if(!(oggFile = fopen(path.c_str(), "rb")))
		{
			fprintf(stderr,"Could not open Ogg file.");
			return false;
		}

		if(ov_open(oggFile, &oggStream, NULL, 0) < 0)
		{
		        fclose(oggFile);
                fprintf(stderr,"Could not open Ogg stream.");
                return false;
        }

		vorbisInfo = ov_info(&oggStream, -1);

    	if(vorbisInfo->channels == 1)
		        format = AL_FORMAT_MONO16;
		else
		        format = AL_FORMAT_STEREO16;

        fprintf(stderr,"File %s opened\n",path.c_str());

        alSourceStop(source);
        return true;
}


void GameSound::run()
{

       fprintf(stderr,"Starting GameSound Thread\n");

       while( m_running)
       {
            if(update())
            {
                if( !isActive() )
                {
                  if(!stream(buffers[0]) )
                      m_running = false;
                  else if( !stream(buffers[1]) )
                      m_running = false;
                  else
                  {
                    alSourceQueueBuffers(source, 2, buffers);
                    alSourcePlay(source);
                  }
                }
            }
            else
               m_running = false;
       }
       release();
}

bool GameSound::stream(ALuint buffer)
{
    char data[BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;
    bool flag = true;


            while(size < BUFFER_SIZE)
            {
                result = ov_read(&oggStream, data + size, BUFFER_SIZE - size, 0, 2, 1, & section);

                if(result > 0)
                    size += result;
                else if(result < 0)
                    flag = false;
                else if(m_loop && result == 0)
                {
                  seek(0);
                  return true;
                }
                else if(!m_listeners.empty())
                {
                 std::list<GameSoundListener*>::iterator iter = m_listeners.begin();
                 flag = false;
                 if( (*iter))
                    (*iter)->onFinished(this);
                 m_running = false;
                }
            }

        if(size == 0)
            return false;

        alBufferData(buffer, format, data, size, vorbisInfo->rate);
        check();

    return flag;
}



bool GameSound::update()
{
    int processed;
    bool active = true;


        alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

       if( m_running)
        while(processed--)
        {
          ALuint buffer;

                alSourceUnqueueBuffers(source, 1, &buffer);
                check();

                if( (active = stream(buffer)) )
                {
                    alSourceQueueBuffers(source, 1, &buffer);
                    check();
                }
        }

    return active;
}

void GameSound::release()
{
    alSourceStop(source);

    empty();

    alDeleteSources(1, &source);

    if( buffers)
        alDeleteBuffers(1, buffers);

    ov_clear(&oggStream);
}

bool GameSound::isActive()
{
    ALenum state = AL_STOPPED;

        alGetSourcei(source, AL_SOURCE_STATE, &state);
        return (state == AL_PLAYING || state == AL_STOPPED || state == AL_PAUSED);
}


bool GameSound::isPlaying()
{
    ALenum state;

        alGetSourcei(source, AL_SOURCE_STATE, &state);
        return (state == AL_PLAYING);
}

bool GameSound::isStopped()
{
    ALenum state;

        alGetSourcei(source, AL_SOURCE_STATE, &state);
        return (state == AL_STOPPED);
}

bool GameSound::isPaused()
{
    ALenum state;

        alGetSourcei(source, AL_SOURCE_STATE, &state);
        return (state == AL_PAUSED);
}




bool GameSound::seek(double secs)
{
	return ov_time_seek(&oggStream, secs) == 0;
}

void GameSound::play(double start, double end)
{

        if( !this->m_running)
        {
            m_running = true;
            this->startThread();
        }


}



void GameSound::empty()
{
    int queued = 1;
    ALuint buffer;

        alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);

        while(queued--)
            alSourceUnqueueBuffers(source, 1, &buffer);
}


void GameSound::check()
{
    int error = alGetError();
    std::string errType;

        if(error != AL_NO_ERROR)
        {
            if( error == AL_INVALID_NAME)
                errType = "Invalid Name";
            else if( error == AL_INVALID_ENUM)
                errType = "Invalid enum";
            else if( error == AL_INVALID_VALUE)
                errType = "Invalid value";
            else if( error == AL_INVALID_OPERATION)
                errType = "Invalid operation";
            else if( error == AL_OUT_OF_MEMORY)
                errType = "Out of mem";
                //TODO: error on exit
        }
}

std::string GameSound::errorString(int code)
{
    switch(code)
    {
        case OV_EREAD:
            return std::string("Read from media.");
        case OV_ENOTVORBIS:
            return std::string("Not Vorbis data.");
        case OV_EVERSION:
            return std::string("Vorbis version mismatch.");
        case OV_EBADHEADER:
            return std::string("Invalid Vorbis header.");
        case OV_EFAULT:
            return std::string("Internal logic fault (bug or heap/stack corruption.");
        default:
            return std::string("Unknown Ogg error.");
    }
}

void GameSound::setVolume(float vol)
{
 alSourcef(source,AL_GAIN, vol);

}

GameSound::~GameSound()
{
    alDeleteSources(1, &source);
    alDeleteBuffers(4, buffers);
    alutExit();
}
