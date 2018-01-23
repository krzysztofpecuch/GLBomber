#include "animationhandler.h"

Animation::Animation(unsigned int startFrame, unsigned int endFrame, float duration)
{
	this->startFrame = startFrame;
	this->endFrame = endFrame;
	this->duration = duration;
}

unsigned int Animation::getLength()
{
	return endFrame - startFrame + 1;
}

//######################################

AnimationHandler::AnimationHandler()
{
	this->m_t = 0.0f;
	this->m_currentAnimation = -1;
}

AnimationHandler::AnimationHandler(const sf::IntRect & frameSize)
{
	this->frameSize = frameSize;
	this->m_t = 0.0f;
	this->m_currentAnimation = -1;
}

void AnimationHandler::addAnimation(Animation & anim)
{
	m_animations.push_back(anim);
}

void AnimationHandler::update(const float dt)
{
	if (m_currentAnimation >= m_animations.size() || m_currentAnimation < 0)
		return;

	float duration = this->m_animations[m_currentAnimation].duration;

	if (int((m_t + dt) / duration) > int(m_t / duration))
	{
		int frame = int((m_t + dt) / duration);

		frame %= m_animations[m_currentAnimation].getLength();

		sf::IntRect rect = frameSize;
		rect.left = rect.width * frame;
		rect.top = rect.height * m_currentAnimation;
		bounds = rect;
	}

	m_t += dt;

	if (m_t > duration * m_animations[m_currentAnimation].getLength())
	{
		m_t = 0.0f;
	}
}

void AnimationHandler::changeAnimation(unsigned int animationNumber)
{
	if (m_currentAnimation == animationNumber || animationNumber >= m_animations.size() || animationNumber < 0)
		return;

	m_currentAnimation = animationNumber;
	sf::IntRect rect = frameSize;
	rect.top = rect.height * animationNumber;
	bounds = rect;
	m_t = 0.0f;
}

