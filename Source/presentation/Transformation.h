/**
 * \class Transformation
 *
 * \brief converts 2D game world space of [-4,4] x [-3, 3] to pixel values
 */

#ifndef TURBOHIKER_TRANSFORMATION_H
#define TURBOHIKER_TRANSFORMATION_H

#include <memory>
#include <SFML/Graphics.hpp>

class Transformation {
    static Transformation* _instance;

    /// weak pointer to the window object
    std::weak_ptr<sf::RenderWindow> window;

    explicit Transformation(std::weak_ptr<sf::RenderWindow> w);

public:
    /**
     * returns the singleton instance
     *
     * @param w weak pointer to the window, must be provided on first call to init the internal window pointer
     * @return singleton instance
     */
    static Transformation* instance(std::weak_ptr<sf::RenderWindow> w = {});

    /**
     * converts 1 textSize unit to 1/10 screen diagonal
     * @param size
     * @return
     */
    int textSize(const double& size) const;

    /**
     * converts [-4,4] x coords to pixel coords in [0, window_width]
     * @param x
     * @return
     */
    float x(const double& x) const;

    /**
     * converts [-3,3] y coords to pixel coords in [window_height, 0]
     * @param y
     * @return
     */
    float y(const double& y) const;

};




#endif //TURBOHIKER_TRANSFORMATION_H
