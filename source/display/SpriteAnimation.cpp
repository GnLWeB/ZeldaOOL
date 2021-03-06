/*
 * =====================================================================================
 *
 *       Filename:  SpriteAnimation.cpp
 *
 *    Description:
 *
 *        Created:  27/04/2015 15:30:50
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "Sprite.hpp"

void SpriteAnimation::reset(u16 frameID) {
	m_timer.reset();
	m_timer.setTime(frameID * m_delay);
}

void SpriteAnimation::start() {
	m_timer.start();

	if(!Sprite::pause) m_isPaused = false;
}

void SpriteAnimation::stop() {
	m_timer.stop();

	if(!Sprite::pause) m_isPaused = true;
}

void SpriteAnimation::play() {
	if(Sprite::pause || m_isPaused) {
		stop();
	} else {
		start();
	}

	if(isFinished()) {
		if(m_isRepeated) {
			reset();
			start();
		} else {
			stop();
		}
	}
}

u16 SpriteAnimation::getFrame(u16 frameID) const {
	return m_frames[frameID];
}

u16 SpriteAnimation::currentFrame() const {
	u16 frameID = displayedFramesAmount();
	if(frameID >= m_frames.size()) {
		return getFrame(m_frames.size() - 1);
	} else {
		return getFrame(frameID);
	}
}

u16 SpriteAnimation::displayedFramesAmount() const {
	return m_timer.time() / m_delay;
}

const Vector2i &SpriteAnimation::currentPosition() const {
	if(!isFinished()) {
		return m_positions.at(displayedFramesAmount());
	} else {
		return m_positions.at(m_frames.size() - 1);
	}
}
