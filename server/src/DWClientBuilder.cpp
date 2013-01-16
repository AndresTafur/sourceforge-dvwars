#include "DWClientBuilder.h"

DWClientBuilder* DWClientBuilder::sm_instance = 0;

DWClientBuilder::DWClientBuilder()
{
    //ctor
}

    DWClientBuilder* DWClientBuilder::getInstancePtr()
    {
            if(!sm_instance)
                sm_instance = new DWClientBuilder();

        return sm_instance;
    }


    ClientAttender* DWClientBuilder::getClientAttender()
    {
      DWClientAttender *obj;

                obj = new DWClientAttender();
                obj->addRequestCtrl(m_reqCtrl);

        return obj;
    }


    void DWClientBuilder::addRequestCtrl(std::string proto, RequestManager *obj)
    {
        m_reqCtrl.insert( std::make_pair<std::string,RequestManager*>(proto,obj));
    }


DWClientBuilder::~DWClientBuilder()
{
    //dtor
}
