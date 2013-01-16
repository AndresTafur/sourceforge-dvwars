#ifndef _WS_REQUESTMANAGER_H_
#define _WS_REQUESTMANAGER_H_

#include <string>
#include <vector>

class ClientAttender;

/**
 * Interface to define request managers, based on protocols.
 * @see ClientAttender.
 */
class RequestManager
{
    public:

        /** Default constructor */
        RequestManager();


        virtual RequestManager* getController();

        virtual void manage(ClientAttender* attender, std::vector<std::string> &params) = 0;

        virtual std::string getControllerName() = 0;

        /** Default destructor */
        virtual ~RequestManager();

    private:
};

#endif // _WS_REQUESTCONTROLLER_H_
