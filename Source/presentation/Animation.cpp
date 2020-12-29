//
// Created by viktor on 29.12.20.
//

#include "Animation.h"
#include <cmath>

turbohikerSFML::Animation::Animation(int frames, double framerate, bool playonce) {
    Animation::frames = frames;
    Animation::framerate = framerate;
    play_once = playonce;
}

turbohikerSFML::Animation &turbohikerSFML::Animation::setRate(double rate) {
    Animation::framerate = rate;
    return *this;
}

turbohikerSFML::Animation &turbohikerSFML::Animation::setDuration(double duration) {
    framerate = (double)frames / duration;
    return *this;
}

turbohikerSFML::Animation &turbohikerSFML::Animation::play(sf::Sprite& sprite) {
    stop(sprite); // first stop ongoing anim
    playing = true; // set playing back to true
    return *this;
}

turbohikerSFML::Animation & turbohikerSFML::Animation::update(double delta, sf::Sprite& sprite) {
    if (playing){
        animationtimer += delta; // increment animation timer

        double singletimer = std::fmod(animationtimer, duration()); // timer of a single loop of animation

        if(animationtimer >= duration() and play_once){ // finished animation
                return stop(sprite);
        }

        int curr_frame = std::floor(singletimer * framerate);
        updateFrame(sprite, curr_frame);

    }
    return *this;
}

double turbohikerSFML::Animation::duration() {
    return (double)frames/framerate;
}

void turbohikerSFML::Animation::updateFrame(sf::Sprite& sprite, const int& f) {
    if (frame == f){ // dont update if not needed
        return;
    }

    sf::IntRect current = sprite.getTextureRect();
    // set sprite to next frame texture
    sprite.setTextureRect(sf::IntRect(f * current.width, current.top,
                                      current.width, current.height));
    frame = f;
}

turbohikerSFML::Animation &turbohikerSFML::Animation::stop(sf::Sprite& sprite) {
    playing = false;
    animationtimer = 0;
    frame = -1;
    updateFrame(sprite, 0);
    frame = 0;
    return *this;
}

bool turbohikerSFML::Animation::isPlaying() {
    return playing;
}
