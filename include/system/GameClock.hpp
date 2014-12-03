/*
 * =====================================================================================
 *
 *       Filename:  GameClock.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/12/2014 18:14:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef GAMECLOCK_HPP_
#define GAMECLOCK_HPP_

#include <functional>

#include <SFML/System.hpp>

#include "Types.hpp"

class GameClock {
	public:
		GameClock();
		~GameClock();
		
		static u32 getTicks(bool realTime = false);
		
		void measureLastFrameDuration();
		
		void updateGame(std::function<void(void)> updateFunc);
		
		void drawGame(std::function<void(void)> drawFunc);
		
	private:
		static sf::Clock clock;
		static u32 ticks;
		
		u32 m_lastFrameDate;
		u32 m_lag;
		u32 m_timeDropped;
		u32 m_now;
		u32 m_lastFrameDuration;
		u32 m_timestep;
		u8 m_numUpdates;
};

#endif // GAMECLOCK_HPP_
