#ifndef _NOISE_MODULE_CIRCLE_H_
#define _NOISE_MODULE_CIRCLE_H_

#include <libnoise/module/modulebase.h>

namespace noise
{
    namespace module
    {
        const double DEFAULT_CIRCLE_RADIUS = 1.0;
        class Circle: public Module
        {
            public:
                Circle ();
                double GetRadius () const
                {
                    return m_radius;
                }
                virtual int GetSourceModuleCount () const
                {
                    return 0;
                }
                virtual double GetValue (double x, double y, double z) const;
                void SetRadius (double radius)
                {
                    m_radius = radius;
                }
            protected:
                double m_radius;
        };
    }
}

#endif // _NOISE_MODULE_CIRCLE_H_

