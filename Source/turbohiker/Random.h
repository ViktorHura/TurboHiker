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

    public:
        static Random *instance();

        double Double();

        double Double(const double& min, const double& max);

        int Int(const int& min, const int& max);
    };
}

#endif //TURBOHIKER_RANDOM_H
