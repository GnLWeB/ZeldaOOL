/*
 * =====================================================================================
 *
 *       Filename:  Octorok.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/10/2014 21:39:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include "Octorok.hpp"
#include "Sound.hpp"

Octorok::Octorok() {
}

Octorok::Octorok(u16 x, u16 y, u8 direction) {
	load(x, y, direction);
}

Octorok::~Octorok() {
	delete m_hurtMovement;
}

void Octorok::load(u16 x, u16 y, u8 direction) {
	Enemy::load("graphics/enemies/octorok.png", x, y, 16, 16, direction);
	
	addAnimation({4, 0}, 150);
	addAnimation({5, 1}, 150);
	addAnimation({6, 2}, 150);
	addAnimation({7, 3}, 150);
	
	m_hurtMovement = new HurtMovement(this, 0.8);
	
	reset();
}

void Octorok::reset() {
	m_maxLife = 2;
	Battler::reset();
	
	m_dead = false;
	
	resetMovement();
}

void Octorok::resetMovement() {
	m_state = State::Standing;
	
	m_timer.reset();
	
	m_movementCounter = 0;
	
	m_randomMinTimeToWait = 1000 + (rand() % 2) * 500;
	m_randomMaxMovement = 16 + (rand() % 5) * 8;
	
	m_hurtMovement->reset();
	
	stopAnimation(m_direction);
}

void Octorok::update() {
	if(m_dead) return;
	
	Battler::update();
	
	if(m_state == State::Standing) {
		m_timer.start();
		
		if(m_timer.time() > m_randomMinTimeToWait) {
			m_vx = rand() % 3 - 1;
			m_vy = rand() % 3 - 1;
			
			if(m_vx != 0 && m_vy != 0) {
				if(rand() % 2 == 0) {
					m_vx = 0;
				} else {
					m_vy = 0;
				}
			}
			
			mapCollisions();
			
			updateDirection();
			
			if(m_vx != 0 || m_vy != 0) m_state = State::Moving;
		}
	}
	else if(m_state == State::Moving) {
		if(m_movementCounter < m_randomMaxMovement) {
			mapBordersCollisions();
			
			mapCollisions();
			
			move(m_vx * 0.3f, m_vy * 0.3f);
			
			m_movementCounter += 0.3f;
		} else {
			resetMovement();
		}
	}
	else if(m_state == State::Hurt) {
		mapBordersCollisions();
		
		m_hurtMovement->update();
		
		if(m_hurtMovement->isFinished()) {
			m_hurt = false;
			
			checkDeath();
			
			m_state = State::Standing;
		}
	}
}

void Octorok::draw() {
	if(m_dead) return;
	
	if(m_state == State::Standing) {
		drawFrame(m_x, m_y, m_lastFrameDisplayed);
	}
	else if(m_state == State::Moving) {
		playAnimation(m_x, m_y, m_direction);
	}
	else if(m_state == State::Hurt) {
		drawFrame(m_x, m_y, m_direction);
	}
}

void Octorok::mapCollisionAction(float vx, float vy) {
	if(m_state == State::Moving) {
		if(vx != 0) {
			m_vy = rand() % 3 - 1;
			if(m_vy == 0) m_vx = -m_vx;
			else m_vx = 0;
		}
		else if(vy != 0) {
			m_vx = rand() % 3 - 1;
			if(m_vx == 0) m_vy = -m_vy;
			else m_vy = 0;
		}
		
		updateDirection();
	} else {
		Character::mapCollisionAction(vx, vy);
	}
}

void Octorok::hurtAction() {
	m_hurtMovement->reset();
	
	m_state = State::Hurt;
	
	Sound::Effect::enemyHit.play();
}
