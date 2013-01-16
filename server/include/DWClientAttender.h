#ifndef _DWCLIENT_ATTENDER_H
#define _DWCLIENT_ATTENDER_H

#include "Player.h"
#include "ClientAttender.h"


/**
 * Concrete Client attender, specific for the game.
 */
class DWClientAttender : public ClientAttender
{
public:

        void attend(std::string data);

        void setPlayer(Player* ply);

        void onClose();

        /**
         * splits a command in the form OPC|ATTR1|ATTR2|...|ATTRN to a list
         * @param data Command to be split.
         */
        void parseParams(std::string data);


  /**
         * Adds new request handlers to be notified.
         * @param list new request handlers.
         */
        void addRequestCtrl(std::map<std::string,RequestManager*> list);

        /**
         * Adds new request handlers to be notified.
         * @param proto Call this handler when proto opcode has arrived.
         * @param obj    Handler.
         */
        void addRequestCtrl(std::string proto, RequestManager *obj);


        /**
         * remove Request handlers based on protocol id.
         * @param proto protocol to be removed.
         */
        void removeRequestCtrl(std::string proto);




private:
std::vector<std::string> m_params;
std::map<std::string,RequestManager*> m_controllers;

Player *m_player;
bool    m_crypt;
};

#endif // _WARSERVER_ATTENDER_H
