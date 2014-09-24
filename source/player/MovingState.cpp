/*
 * =====================================================================================
 *
 *       Filename:  MovingState.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/09/2014 22:25:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "EffectManager.hpp"
#include "Keyboard.hpp"
#include "MovingState.hpp"
#include "StandingState.hpp"
#include "TimeManager.hpp"

MovingState::MovingState() {
	m_stateType = StateType::TypeMoving;
	m_nextStateType = StateType::TypeMoving;
	
	m_directionLocked = false;
}

MovingState::~MovingState() {
}

void MovingState::move() {
	if(Keyboard::isKeyPressed(Keyboard::Left)) {
		m_player.setVX(-1);
		
		if(!Keyboard::isKeyPressed(Keyboard::Up)
		&& !Keyboard::isKeyPressed(Keyboard::Down)) {
			if(!m_directionLocked) m_player.setDirection(Player::Direction::Left);
		}
	}
	else if(Keyboard::isKeyPressed(Keyboard::Right)) {
		m_player.setVX(1);
		
		if(!Keyboard::isKeyPressed(Keyboard::Up)
		&& !Keyboard::isKeyPressed(Keyboard::Down)) {
			if(!m_directionLocked) m_player.setDirection(Player::Direction::Right);
		}
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Up)) {
		m_player.setVY(-1);
		
		if(!Keyboard::isKeyPressed(Keyboard::Left)
		&& !Keyboard::isKeyPressed(Keyboard::Right)) {
			if(!m_directionLocked) m_player.setDirection(Player::Direction::Up);
		}
	}
	else if(Keyboard::isKeyPressed(Keyboard::Down)) {
		m_player.setVY(1);
		
		if(!Keyboard::isKeyPressed(Keyboard::Left)
		&& !Keyboard::isKeyPressed(Keyboard::Right)) {
			if(!m_directionLocked) m_player.setDirection(Player::Direction::Down);
		}
	}
	
	if((Keyboard::isKeyPressed(Keyboard::Left)
	 || Keyboard::isKeyPressed(Keyboard::Right))
	&& (Keyboard::isKeyPressed(Keyboard::Up)
	 || Keyboard::isKeyPressed(Keyboard::Down))) {
		m_player.setVelocity(m_player.vx() / 1.4, m_player.vy() / 1.4);
	}
	
	m_player.mapCollisions();
	
	m_player.move(m_player.vx() * 0.6f,
				  m_player.vy() * 0.6f);
	
	m_player.setVelocity(0, 0);
}

void MovingState::update() {
	if(Keyboard::isKeyPressed(Keyboard::A)) {
		m_nextStateType = StateType::TypeSword;
	}
	
	if(!Keyboard::isKeyPressed(Keyboard::Left)
	&& !Keyboard::isKeyPressed(Keyboard::Right)
	&& !Keyboard::isKeyPressed(Keyboard::Up)
	&& !Keyboard::isKeyPressed(Keyboard::Down)) {
		m_nextStateType = StateType::TypeStanding;
	}
	
	move();
}

void MovingState::draw() {
	m_player.playAnimation(m_player.x(), m_player.y(), m_player.direction());
	
	EffectManager::drawEffects(&m_player);
}
