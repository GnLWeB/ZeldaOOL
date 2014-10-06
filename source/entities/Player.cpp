/*
 * =====================================================================================
 *
 *       Filename:  Player.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/09/2014 22:17:50
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
#include "MapHelper.hpp"
#include "MapManager.hpp"
#include "MovingState.hpp"
#include "Player.hpp"
#include "PushingState.hpp"
#include "StandingState.hpp"
#include "TilesData.hpp"
#include "TimeManager.hpp"
#include "WeaponManager.hpp"

Player::Player() {
	
}

Player::~Player() {
}

void Player::load() {
	Character::load("graphics/characters/link.png", 64, 64, 16, 16, Direction::Down);
	// Movement
	addAnimation({4, 0}, 110);
	addAnimation({5, 1}, 110);
	addAnimation({6, 2}, 110);
	addAnimation({7, 3}, 110);
	
	// Pushing
	addAnimation({ 8, 12}, 90);
	addAnimation({ 9, 13}, 90);
	addAnimation({10, 14}, 90);
	addAnimation({11, 15}, 90);
	
	// Using sword
	addAnimation({16, 20, 20, 20, 20, 20, 20, 20}, 40);
	addAnimation({17, 21, 21, 21, 21, 21, 21, 21}, 40);
	addAnimation({18, 22, 22, 22, 22, 22, 22, 22}, 40);
	addAnimation({19, 23, 23, 23, 23, 23, 23, 23}, 40);
	
	// SpinAttack
	addAnimation({20, 20, 22, 22, 23, 23, 21, 21}, 50);
	
	m_state = new StandingState();
	
	m_maxLife = 13 * 4;
	m_life = 11 * 4;
	
	m_rupees = 197;
	
	m_inventory.addWeapon(WeaponManager::SwordID);
	
	m_inDoor = false;
}

void Player::mapCollisions() {
	u8 collisionMatrix[4][4] = {
		{12, 8,12,13},
		{ 3, 8, 3,13},
		{ 5, 5,10, 5},
		{ 5,15,10,15}
	};
	
	for(u8 i = 0 ; i < 4 ; i++) {
		bool test;
		
		if(i == 0) {
			test = (m_vx > 0);
		}
		else if(i == 1) {
			test = (m_vx < 0);
		}
		else if(i == 2) {
			test = (m_vy < 0);
		}
		else if(i == 3) {
			test = (m_vy > 0);
		}
		
		if(test
		&& (!MapHelper::passable(m_x + collisionMatrix[i][0], m_y + collisionMatrix[i][1])
		||  !MapHelper::passable(m_x + collisionMatrix[i][2], m_y + collisionMatrix[i][3]))) {
			if(i < 2)	m_vx = 0;
			else		m_vy = 0;
			
			if((i == 0 && m_direction == Direction::Right)
			|| (i == 1 && m_direction == Direction::Left)
			|| (i == 2 && m_direction == Direction::Up)
			|| (i == 3 && m_direction == Direction::Down)) {
				m_state->setNextStateType(PlayerState::TypePushing);
			}
			
			if( MapHelper::passable(m_x + collisionMatrix[i][2], m_y + collisionMatrix[i][3])
			&& !MapHelper::passable(m_x + collisionMatrix[i][0], m_y + collisionMatrix[i][1])) {
				if(i < 2 && m_vy == 0)	m_vy = 1;
				else if(    m_vx == 0)	m_vx = 1;
				
				m_state->resetNextStateType();
			}
			
			if( MapHelper::passable(m_x + collisionMatrix[i][0], m_y + collisionMatrix[i][1])
			&& !MapHelper::passable(m_x + collisionMatrix[i][2], m_y + collisionMatrix[i][3])) {
				if(i < 2 && m_vy == 0)	m_vy = -1;
				else if(    m_vx == 0)	m_vx = -1;
				
				m_state->resetNextStateType();
			}
		}
	}
	
	if(onTile(TilesData::TileType::SlowingTile)) {
		m_vx /= 2;
		m_vy /= 2;
	}
	
	if(onTile(TilesData::TileType::LowGrassTile)) {
		m_vx /= 4;
		m_vx *= 3;
		
		m_vy /= 4;
		m_vy *= 3;
	}
	
	if(onTile(TilesData::TileType::Button)) {
		MapManager::currentMap->sendEvent(Map::EventType::ButtonPressed);
	}
	
	if(MapHelper::onDoor(m_x + 8, m_y + 8) && !m_inDoor) {
		m_inDoor = true;
		
		MapManager::currentMap->sendEvent(Map::EventType::ChangeMap, this, Vector2i(8, 8));
	}
	
	//if(!MapHelper::onDoor(m_x +  2, m_y +  2)
	//&& !MapHelper::onDoor(m_x + 14, m_y +  2)
	//&& !MapHelper::onDoor(m_x +  2, m_y + 14)
	//&& !MapHelper::onDoor(m_x + 14, m_y + 14)) {
	if(!MapHelper::onDoor(m_x + 8, m_y + 8)) {
		m_inDoor = false;
	}
}

void Player::update() {
	if(m_state->stateType() != m_state->nextStateType()) {
		m_state = m_state->nextState();
	}
	
	m_state->update();
}

void Player::draw() {
	m_state->draw();
}

void Player::setNextStateType(PlayerState::StateType nextType) {
	m_state->setNextStateType(nextType);
}

