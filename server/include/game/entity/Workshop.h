#ifndef _WORKSHOP_H_
#define _WORKSHOP_H_

#include <Vector2.h>

class Workshop
{
    public:

        Workshop(Vector2 coord);

        void setTarget(Vector2 target);

        inline Vector2 getPosition() { return mPosition; }

        inline Vector2 getTarget() { return mTarget; }

        virtual ~Workshop();

    private:

    Vector2 mPosition;
    Vector2 mTarget;
    unsigned long mHitPoints;
};

#endif // _WORKSHOP_H_
