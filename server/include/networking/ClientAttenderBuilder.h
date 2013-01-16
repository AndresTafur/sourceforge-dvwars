#ifndef _CLIENTATTENDERBUILDER_H_
#define _CLIENTATTENDERBUILDER_H_

#include "ClientAttender.h"

/**
 * Interface to abstract the attender builders.
 */
class ClientAttenderBuilder
{
 public:

        /**
         * Returns a new ClientAttender derived object
         * @return new derived attender.
         */
       virtual ClientAttender* getClientAttender() = 0;

 };

#endif // _CLIENTATTENDERBUILDER_H_
