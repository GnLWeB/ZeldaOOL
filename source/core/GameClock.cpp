/*
 * =====================================================================================
 *
 *       Filename:  GameClock.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/12/2014 18:19:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include "Application.hpp"
#include "GameClock.hpp"

sf::Clock GameClock::clock;
u32 GameClock::ticks = 0;

GameClock::GameClock() {
	m_lastFrameDate = 0;
	m_lag = 0;
	m_timeDropped = 0;
	m_now = 0;
	m_lastFrameDuration = 0;
	m_timestep = 6;
	m_numUpdates = 0;
}

GameClock::~GameClock() {
}

u32 GameClock::getTicks(bool realTime) {
	if(realTime) {
		return clock.getElapsedTime().asMilliseconds();
	} else {
		return ticks;
	}
}

void GameClock::measureLastFrameDuration() {
	m_now = getTicks(true) - m_timeDropped;
	m_lastFrameDuration = m_now - m_lastFrameDate;
	m_lastFrameDate = m_now;
	m_lag += m_lastFrameDuration;
	
	if(m_lag >= 200) {
		m_timeDropped += m_lag - m_timestep;
		m_lag = m_timestep;
		m_lastFrameDate = getTicks(true) - m_timeDropped;
	}
}

void GameClock::updateGame(std::function<void(void)> updateFunc) {
	m_numUpdates = 0;
	
	while(m_lag >= m_timestep && m_numUpdates < 10 && Application::getInstance().window().isOpen()) {
		ticks += m_timestep;
		
		updateFunc();
		
		m_lag -= m_timestep;
		m_numUpdates++;
	}
}

void GameClock::drawGame(std::function<void(void)> drawFunc) {
	if(m_numUpdates > 0) {
		drawFunc();
	}
	
	m_lastFrameDuration = getTicks(true) - m_timeDropped - m_lastFrameDate;
	
	if(m_lastFrameDuration < m_timestep) {
		sf::sleep(sf::milliseconds(m_timestep - m_lastFrameDuration));
	}
	
	m_now = 0;
	m_lastFrameDuration = 0;
}

