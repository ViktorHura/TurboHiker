#ifndef TURBOHIKER_TRANSFORMATION_H
#define TURBOHIKER_TRANSFORMATION_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "../turbohiker/Utils.h"

namespace turbohikerSFML {
    /**
     * \class Transformation
     * \ingroup turbohikerSFML
     * \brief converts pixel values to the visible 2D game world space of [-4,4] x [-3, 3]
     */
    class Transformation {
        static Transformation *_instance;

        /// weak pointer to the window object
        std::weak_ptr<sf::RenderWindow> window;

        explicit Transformation(std::weak_ptr<sf::RenderWindow> w);

        double y_pos = 0; // y positions of camera

        double y_pos_old = 0; // previous y position of camera

        double y_delta = 0; // how much camera has moved, used for parallax background

        double max_y_pos = 180;

        double p_speed = 1; // player speed, used for parallax background

    public:
        /**
         * returns the singleton instance
         *
         * @param w weak pointer to the window, must be provided on first call to init the internal window pointer
         * @return singleton instance
         */
        static Transformation *instance(std::weak_ptr<sf::RenderWindow> w = {});

        /**
         * set the Y position of camera, usually player y position
         * @param ypos
         */
        void setYpos(const double& ypos);

        /**
         * has the screen gone up as much as it can(for parallax effect)
         * @return
         */
        bool Yismax();

        /**
         * get how much camera has moved last frame
         * @return
         */
        double getYdelta() const;

        /**
         * get player speed
         * @return
         */
        double getPspeed();

        /**
         * update player speed
         * @param p
         */
        void setPspeed(const double& p);

        /**
         * converts 1 textSize unit to 1/10 screen diagonal
         * @param size
         * @return
         */
        int textSize(const double &size) const;

        /**
         * converts [-4,4] x coords to pixel coords in [0, window_width]
         * @param x
         * @return
         */
        float x(const double &x) const;

        /**
         * converts [-3,3] y coords to pixel coords in [window_height, 0], adjusting for camera
         * @param y
         * @return
         */
        float y(const double &y) const;

        /**
         * converts [-3,3] y coords to pixel coords in [window_height, 0], ignoring camera
         * @param y
         * @return
         */
        float yFixed(const double &y) const;

        /**
         * converts position vector
         * @param vec
         * @return
         */
        sf::Vector2f pos(const turbohiker::Utils::Vector& vec) const;

        /**
         * converts position vector, without accounting for the camera
         * @param vec
         * @return
         */
        sf::Vector2f posFixed(const turbohiker::Utils::Vector& vec) const;

        /**
         * converts size vector
         * @param vec
         * @return
         */
        sf::Vector2f size(const turbohiker::Utils::Vector& vec) const;

        /**
         * rescales sprite to a sizeVector
         * @param size
         * @param sprite
         */
        void rescaleSprite(const turbohiker::Utils::Vector& size, sf::Sprite& sprite);

        void reset();
    };
}



#endif //TURBOHIKER_TRANSFORMATION_H
