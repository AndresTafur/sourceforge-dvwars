#include "LoginAdapter.h"

#include "DWClientAttender.h"

LoginAdapter::LoginAdapter()
{

}


    void LoginAdapter::manage(ClientAttender* attender,std::vector<std::string> &params)
    {
            if( params[0] == "601")
                login(attender,params);
            else if( params[0] == "602" )
                logOut(attender,params);
            else if( params[0] == "600" )
                userRegister(attender,params);
    }


    void LoginAdapter::login(ClientAttender* attender,std::vector<std::string> &params)
    {
      Client *clt = attender->getClient();
      User usr;

                fprintf(stderr,"\n==== User Login. ====\n");

                usr.setName(params[1]);
                usr.setPassword(params[2]);

                try
                {
                    if( mLogMgr.userLogin(usr)  )
                    {
                        clt->Send("404");
                        fprintf(stderr,"\t- ERROR: User doesn't exists or db connection down.\n");
                    }
                    else
                    {
                        fprintf(stderr,"\t- User Logged in.\n");
                        clt->Send("201");
                        attender->removeRequestCtrl("601");
                        static_cast<DWClientAttender*>(attender)->setPlayer( new Player(usr) );
                        mChallMgr.addPlayerAttender( attender );
                        mChatMgr.addPlayerAttender( attender );
                    }
                }
                catch(DBException ex)
                {
                    std::cerr << ex.what();
                }
    }


    void  LoginAdapter::userRegister(ClientAttender* attender, std::vector<std::string> &params)
    {
      Client *clt = attender->getClient();
      User usr;

                    fprintf(stderr,"\n==== Registering User. ====\n");

                    usr.setName(params[1]);
                    usr.setPassword(params[2]);
                    usr.setEmail(params[3]);
                    usr.setSide(params[4]);

                    try
                    {
                        if( !mLogMgr.userRegister(usr) )
                        {
                            clt->Send("409");
                            fprintf(stderr,"\t- ERROR: User exists or db connection down.\n");
                        }
                        else
                        {
                            clt->Send("200");
                            fprintf(stderr,"\t- User Registered.\n");
                        }
                    }
                    catch(DBException ex)
                    {
                        std::cerr << ex.what();
                    }
    }


    void  LoginAdapter::logOut(ClientAttender* attender,std::vector<std::string> &params)
    {
        Client *clt = attender->getClient();
        User usr;


                fprintf(stderr,"==== User Logout. ====\n");

                usr.setName(params[1]);

                if( !mLogMgr.userLogout(usr)  )
                {
                        clt->Send("404");
                        fprintf(stderr,"\t- ERROR: User doesn't exists or db connection down.\n");
                }
                else
                {
                        clt->Send("200");
                        fprintf(stderr,"\t- User Logged out.\n");
                        attender->removeRequestCtrl("602");
                        attender->addRequestCtrl("601",this);
                }
    }


LoginAdapter::~LoginAdapter()
{
    //dtor
}
