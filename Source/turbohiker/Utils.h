
#ifndef TURBOHIKER_UTILS_H
#define TURBOHIKER_UTILS_H

namespace turbohiker {
    namespace Utils{
        /**
         * \defgroup Utils
         *
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

            Vector(const double& x, const double& y);

            Vector* set(const double& x, const double& y);

            double x() const;
            double y() const;

        };

    }
}

#endif //TURBOHIKER_UTILS_H
