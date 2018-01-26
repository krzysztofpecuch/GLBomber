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
	m_timeCount = 0.0f;
	m_currentAnimation = -1;
	m_freezeFrame = false;
	m_looped = false;
	m_endOfAnimation = false;
}

AnimationHandler::AnimationHandler(const sf::IntRect & frameSize)
{
	this->frameSize = frameSize;
	m_timeCount = 0.0f;
	m_currentAnimation = -1;
	m_frame = 0;
	m_freezeFrame = false;
	m_looped = false;
	m_endOfAnimation = false;
}

void AnimationHandler::addAnimation(const Animation & anim)
{
	m_animations.push_back(anim);
}

void AnimationHandler::update(const float dt)
{
	if ((m_currentAnimation >= m_animations.size() || m_currentAnimation < 0) && (m_animations.size()>0))
	{
		return;
	}

	if (m_freezeFrame)
	{
		return;
	}

	float duration = this->m_animations[m_currentAnimation].duration;

	if (int((m_timeCount + dt) / duration) > int(m_timeCount / duration))
	{
		m_frame = int((m_timeCount + dt) / duration);

		m_frame %= m_animations[m_currentAnimation].getLength();
		if (!m_looped) {
			if (m_frame == m_animations[m_currentAnimation].getLength() - 1) {
				m_freezeFrame = true;
				m_endOfAnimation = true;
			}
		}

		sf::IntRect rect = frameSize;
		rect.left = rect.width * m_frame;
		rect.top = rect.height * m_currentAnimation;
		bounds = rect;
	}

	m_timeCount += dt;

	if (m_timeCount > duration * m_animations[m_currentAnimation].getLength())
	{
		m_timeCount = 0.0f;
	}
}

void AnimationHandler::changeAnimation(unsigned int animationVariant)
{
	if (m_currentAnimation == animationVariant || animationVariant >= m_animations.size() || animationVariant < 0)
		return;

	m_currentAnimation = animationVariant;
	sf::IntRect rect = frameSize;
	rect.top = rect.height * animationVariant;
	bounds = rect;
	m_timeCount = 0.0f;
}

void AnimationHandler::activateAnimation()
{
	m_freezeFrame = false;
	m_timeCount = 0.0f;
}

void AnimationHandler::setLooped()
{
	m_looped = true;
}

bool AnimationHandler::animationEnded()
{
	return m_endOfAnimation;
}
