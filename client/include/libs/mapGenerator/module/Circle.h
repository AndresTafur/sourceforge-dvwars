#ifndef _NOISE_MODULE_CIRCLE_H_
#define _NOISE_MODULE_CIRCLE_H_

#include <libnoise/module/modulebase.h>

namespace noise
{
    namespace module
    {

        /// Default circle radius for the noise::module::Circle noise module.
        const double DEFAULT_CIRCLE_RADIUS = 1.0;

        /**
         * Noise module which will create circle.
         * This module will create circle with specified radius.
         */
        class Circle: public Module
        {
            public:

                /**
                 * Constructor.
                 * Default radius is set to noise::module::DEFAULT_CIRCLE_RADIUS.
                 */
                Circle ();

                /**
                 * Returns radius of circle.
                 *
                 * @return Current radius of circle.
                 */
                double GetRadius () const
                {
                    return m_radius;
                }

                /**
                 * Returns number of source modules which are required.
                 *
                 * @return Number of source modules which are required.
                 */
                virtual int GetSourceModuleCount () const
                {
                    return 0;
                }

                /**
                 * Returns value for point given by axis x, y and z.
                 *
                 * @return Current value given by coordinate.
                 */
                virtual double GetValue (double x, double y, double z) const;

                /**
                 * Sets the radius of the circle.
                 *
                 * @param radius New radius of circle.
                 */
                void SetRadius (double radius)
                {
                    m_radius = radius;
                }
            protected:

                /// Radius of the circle.
                double m_radius;
        };
    }
}

#endif // _NOISE_MODULE_CIRCLE_H_

