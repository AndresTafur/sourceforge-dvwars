#ifndef _DVWARS_THREAD_H_
#define _DVWARS_THREAD_H_

#include <boost/thread.hpp>

namespace DaVinciWars
{
class Thread;

};

/**
 * Handles OS specific threads.
 */
class DaVinciWars::Thread
{
public:

    Thread();

    void startThread();

    void stopThread();

    void joinThread();

    virtual ~Thread();


protected:

    virtual void run();

protected:
    volatile bool m_stoprequested;
private:
    boost::shared_ptr<boost::thread> m_thread;
};

#endif

