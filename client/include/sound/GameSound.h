#ifndef _GAMESOUND_
#define _GAMESOUND_

#include <string>
#include <list>
#include <AL/al.h>

#include <AL/alut.h>
#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#include "GameSoundListener.h"
#include "util/Thread.h"



class GameSound : public DaVinciWars::Thread
{
  public:
        GameSound();

        bool open(std::string file);

        void release();

        void display();

        void setVolume(float vol);

        inline void setPitch(float pitch) { alSourcef(source, AL_PITCH, pitch); }

        bool isPlaying();

        bool isStopped();

        bool isPaused();

        void play(double start = 0, double end = -2);


        inline void setLoop(bool loop) { m_loop = loop;}


        inline void pause() { alSourcePause(source);}

        inline void resume(){ alSourcePlay(source);}

        inline void stop() { m_running = false;}

        inline void addListener(GameSoundListener *listener) { m_listeners.push_back(listener);}

        void run();

        bool seek(double sec);


        inline unsigned int getId() { return m_id;}

        inline std::string getPath() { return m_path;}

        inline void setPosition(double x, double y, double z){ alSource3f(source, AL_POSITION,  x, y, z); }

        inline void setVelocity(double x, double y, double z){ alSource3f(source, AL_VELOCITY,  x, y, z); }

        inline void setDirection(double x, double y, double z){alSource3f(source, AL_DIRECTION,       x, y, z);}

        inline void setRolloff(double val){ 	alSourcef (source, AL_ROLLOFF_FACTOR,  val );}

        inline void setId(unsigned int id) { m_id = id;}


        ~GameSound();

 protected:


        bool isActive();

        bool update();

        bool stream(ALuint buffer);

        void empty();

        void check();

        std::string errorString(int code);


private:
FILE*           oggFile;
OggVorbis_File  oggStream;
vorbis_info*    vorbisInfo;
unsigned int m_id;
bool m_loop;
bool m_running;

ALuint buffers[4];
ALuint source;
ALenum format;
std::string m_path;
const static long long BUFFER_SIZE = (4096 * 8);
std::list<GameSoundListener*> m_listeners;
friend class SoundManager;

};
#endif

