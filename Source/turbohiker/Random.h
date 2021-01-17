//
// Created by viktor on 21.12.20.
//

#ifndef TURBOHIKER_RANDOM_H
#define TURBOHIKER_RANDOM_H

namespace turbohiker {
    /**
     * \class Random
     * \ingroup turbohiker
     * \brief singleton to generate pseudo random numbers
     */
    class Random {
        static Random *_instance;

        explicit Random();
        ~Random() = default;

    public:
        /**
         * get instance
         * @return instance
         */
        static Random *instance();

        /**
         * @return random double in [0,1]
         */
        static double Double();

        /**
         * @param min
         * @param max
         * @return random double between min and max
         */
        static double Double(const double& min, const double& max);

        /**
         * @param min
         * @param max
         * @return random int between min and max
         */
        static int Int(const int& min, const int& max);
    };
}

#endif //TURBOHIKER_RANDOM_H
