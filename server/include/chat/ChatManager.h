#ifndef _CHATMANAGER_H_
#define _CHATMANAGER_H_


#include <Player.h>
#include <ClientAttender.h>
#include <RequestManager.h>


class ChatManager : public RequestManager
{

public:

        ChatManager();

        void manage(ClientAttender* attender, std::vector<std::string> &params);

        inline std::string getControllerName() { return "ChatManager"; }


        /**
         * Adds a new player to the challenge system.
         * @param attender Player attender.
         * @see ClientAttender
         */
        void addPlayerAttender(ClientAttender *attender);


        void sendToHall(Player *sender, std::string msg);


        void sendToUser(Player *sender, std::string user, std::string msg);

        virtual ~ChatManager();


private:

std::map<std::string, ClientAttender*> mPlayers;

};

#endif // _CHATMANAGER_H_
