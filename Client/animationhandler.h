#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include <vector>
#include "SFML\Graphics.hpp"

class Animation
{
public:
	Animation(unsigned int startFrame, unsigned int endFrame, float duration);

	unsigned int startFrame;
	unsigned int endFrame;
	float duration;

	unsigned int getLength();
};

class AnimationHandler
{
public:
	AnimationHandler();
	AnimationHandler(const sf::IntRect &frameSize);

	void addAnimation(Animation &anim);
	void update(const float dt);
	void changeAnimation(unsigned int animationNumber);

	sf::IntRect frameSize;
	sf::IntRect bounds;
private:
	std::vector<Animation> m_animations;
	float m_t;
	int m_currentAnimation;
};

#endif // !ANIMATIONHANDLER_H