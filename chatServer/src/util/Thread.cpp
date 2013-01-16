#include "Thread.h"



    DaVinciWars::Thread::Thread() : m_stoprequested(false)
    {
    }


    // Create the thread and start work
    void DaVinciWars::Thread::startThread()
    {
        assert(!m_thread);
        m_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Thread::run, this)));
    }

    void DaVinciWars::Thread::stopThread() // Note 1
    {
       if(m_thread)
            m_stoprequested = true;
    }


    void DaVinciWars::Thread::joinThread()
    {
         if(m_thread)
         {
            m_stoprequested = true;
            m_thread->join();
         }
    }

    void DaVinciWars::Thread::run()
    {

    }


    DaVinciWars::Thread::~Thread()
    {
        stopThread();
    }




