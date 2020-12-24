
#ifndef TURBOHIKER_UTILS_H
#define TURBOHIKER_UTILS_H

#include <string>

namespace turbohiker {
    namespace Utils{
        /**
         * \defgroup Utils
         * \ingroup turbohiker
         * \brief holds utility functions and classes
         */

        /**
         * \class Vector
         * \ingroup Utils
         * \brief represents a 2d vector
         */
        class Vector{
            double x_ = 0;
            double y_ = 0;

        public:
            Vector()= default;

            /**
             * Create a 2D vector
             * @param x
             * @param y
             */
            Vector(const double& x, const double& y);

            /**
             * override values of the vector
             * @param x
             * @param y
             * @return
             */
            Vector& set(const double& x, const double& y);

            /**
             * override values of the vector
             * @param x
             * @param y
             * @return
             */
            Vector& set(const Vector& vec2);

            /**
             * x getter
             * @return
             */
            double x() const;

            /**
             * y getter
             * @return
             */
            double y() const;

            /**
             * add another vector to this vector
             * @param vec2
             * @return
             */
            Vector& add(const Vector& vec2);

            /**
             * scalar multiply this vector
             * @param s
             * @return
             */
            Vector& scalar(const double& s);

            /**
             * get the magnitude(length) of this vector
             * @return
             */
            double magnitude() const;

            /**
             * normalize this vector
             * @return
             */
            Vector& normalize();

            std::string toString();

            /**
             * get lane(0-3) of this vector
             * @return
             */
            int getLane() const;
        };

    }
}

#endif //TURBOHIKER_UTILS_H
