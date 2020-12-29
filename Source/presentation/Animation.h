//
// Created by viktor on 29.12.20.
//

#ifndef TURBOHIKER_ANIMATION_H
#define TURBOHIKER_ANIMATION_H

#include <memory>
#include <SFML/Graphics/Sprite.hpp>

namespace turbohikerSFML {

    /**
     * \class Animation
     * \ingroup turbohikerSFML
     * \brief abstracts animations for the SFML sprites
     */
    class Animation {
        int frames = 0;
        double framerate = 0;
        bool play_once = false;

        int frame = 0;
        double animationtimer = 0;
        bool playing = false;


        double duration();

        void updateFrame(sf::Sprite& sprite, const int& frame);

    public:

        Animation()= default;

        /**
         * create an animation object
         * tilemap must be a rectangle built of frames, glued left to right
         * each frame must be same size
         * @param frames : amount of frames in the tilemap
         * @param framerate
         * @param playonce : will only play once or loop
         */
        Animation(int frames, double framerate, bool playonce = false);

        /**
         * change the framerate of the animation
         * @param framerate
         * @return
         */
        Animation& setRate(double framerate);

        /**
         * change the duration of this animation
         * @param duration : in seconds
         * @return
         */
        Animation& setDuration(double duration);

        /**
         * start playing the animation
         * @param sprite
         * @return
         */
        Animation& play(sf::Sprite& sprite);

        /**
         * stops playing the animation, resets internal state
         * @param sprite
         * @return
         */
        Animation& stop(sf::Sprite& sprite);

        /**
         * must be called each game frame, delta in seconds
         * and a reference to sprite
         * @param delta
         * @param sprite
         */
        Animation& update(double delta, sf::Sprite& sprite);

        /**
         * is playing?
         */
        bool isPlaying();
    };

}
#endif //TURBOHIKER_ANIMATION_H
