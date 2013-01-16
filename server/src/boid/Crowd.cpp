#include "Crowd.h"

#include "BoidContext.h"

Crowd::Crowd()
{

}

    void Crowd::setBoidContext(BoidContext* cont)
    {
         mContext = cont;

            for(size_t i=0; i < mBoidsArray.size(); i++)
                mBoidsArray[i]->setContext(cont);
    }

    void Crowd::moveTo(Vector2 target)
    {
        mBoidsArray[0]->move(target);
    }


    void Crowd::setPosition(Vector2 target)
    {
      size_t size;


            size = mBoidsArray.size();

            for(size_t i=0; i < size; i++)
                mBoidsArray[i]->setPosition(target+Vector2(10*i,10*i) );

    }


    unsigned int Crowd::getSize()
    {
         return mBoidsArray.size();
    }
