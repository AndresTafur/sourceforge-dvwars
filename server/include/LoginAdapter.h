#ifndef _LOGINADAPTER_H_
#define _LOGINADAPTER_H_

#include <iostream>

#include <RequestManager.h>
#include <ClientAttender.h>
#include <userManager/LoginManager.h>
#include <game/ChallengeManager.h>
#include <chat/ChatManager.h>
/**
 * Adapts Network and UserMagnament
 * @see LoginManager.
 * @see RequestManager.
 */
class LoginAdapter : public RequestManager
{
public:

        LoginAdapter();

            inline std::string getControllerName() { return "LoginController";}

            void  manage(ClientAttender* attender,std::vector<std::string> &params);

            virtual ~LoginAdapter();


private:

    void  login(ClientAttender* attender,std::vector<std::string> &params);

    void  userRegister(ClientAttender* attender, std::vector<std::string> &params);

    void  logOut(ClientAttender* attender,std::vector<std::string> &params);



private:
  LoginManager      mLogMgr;

  ChallengeManager  mChallMgr;

  ChatManager       mChatMgr;
};

#endif // _LOGINADAPTER_H_
