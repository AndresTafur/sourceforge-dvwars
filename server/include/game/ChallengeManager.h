#ifndef _CHALLENGEMANAGER_H_
#define _CHALLENGEMANAGER_H_

#include <map>
#include <Player.h>
#include <GameManager.h>
#include <RequestManager.h>
#include <ClientAttender.h>


/**
 * Handles challenge system
 * @see RequestManager
 */
class ChallengeManager : public RequestManager
{
public:

        ChallengeManager();

        /**
         * Manages a request
         */
        void manage(ClientAttender* attender, std::vector<std::string> &params);

        /**
         * Adds a new player to the challenge system.
         * @param attender Player attender.
         * @see ClientAttender
         */
        void addPlayerAttender(ClientAttender *attender);

        inline std::string getControllerName() { return "ChallengeManager"; }

        virtual ~ChallengeManager();

private:

        /**
         * Send current players to client.
         * @param clt Client to send players.
         */
        void sendActivePlayers(Client *clt);

        /**
         * Send current players to all clients.
         */
        void sendActivePlayers();

private:

std::map<std::string, ClientAttender*> mPlayers;

std::map<std::string, GameManager*> mGames;

};

#endif // _CHALLENGEMANAGER_H_
