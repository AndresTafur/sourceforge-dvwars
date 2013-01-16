#ifndef _DV_THREAD_
#define _DV_THREAD_

#include <boost/thread.hpp>
#include <stdio.h>

namespace DaVinciWars
{
class Thread;

};

/**
 * Hanles OS thread implementation.
 */
class DaVinciWars::Thread
{
public:

    Thread();

    void startThread();

    void stopThread();

    virtual ~Thread();


protected:

    virtual void run();

protected:
    volatile bool m_stoprequested;
    boost::shared_ptr<boost::thread> m_thread;
    boost::mutex m_mutex;
};

#endif

