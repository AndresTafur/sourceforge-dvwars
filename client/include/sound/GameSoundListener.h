#ifndef _GAME_SOUND_LISTENER_H_
#define _GAME_SOUND_LISTENER_H_

class GameSound;

class GameSoundListener
{
  public:

            virtual void onFinished(GameSound *sound) = 0;

};
#endif
