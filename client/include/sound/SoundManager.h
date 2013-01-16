#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include <string>
#include <map>

#include "GameSound.h"


class SoundManager : public GameSoundListener
{
protected:

        SoundManager();

public:

        static SoundManager* getInstance();

        static void destroy();


        GameSound * playSound(std::string path);


        inline void pause() { m_music->pause();}

        inline void resume() { m_music->resume();}

        void onFinished(GameSound *sound);

        ~SoundManager();

private:
static SoundManager* sm_instance;
unsigned int m_index, m_totalSongs;
std::list<GameSound*> m_sounds;
GameSound *m_music;
};
#endif
