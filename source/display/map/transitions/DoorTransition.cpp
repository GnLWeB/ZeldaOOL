/*
 * =====================================================================================
 *
 *       Filename:  DoorTransition.cpp
 *
 *    Description:  
 *
 *        Created:  05/10/2014 21:52:55
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "AudioPlayer.hpp"
#include "Config.hpp"
#include "DoorTransition.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "PositionComponent.hpp"
#include "Scene.hpp"
#include "StandingState.hpp"

DoorTransition::DoorTransition(u16 area, u16 mapX, u16 mapY, u16 playerX, u16 playerY, u8 playerDirection, bool movePlayer) {
	m_nextMap = &Map::getMap(area, mapX, mapY);
	m_nextMap->resetTiles();
	m_nextMap->updateTiles();
	
	m_playerX = playerX;
	m_playerY = playerY;
	
	m_playerDirection = playerDirection;
	
	m_movePlayer = movePlayer;
	
	m_timer.start();
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	m_rect1.resize(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 16);
	m_rect2.resize(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 16);
	
	m_rect1.setPosition(0, 16);
	m_rect2.setPosition(SCREEN_WIDTH / 2, 16);
	
	// FIXME: TEMPORARY
	if(m_nextMap->area() == 0) {
		AudioPlayer::playMusic("plain");
	}
	else if(m_nextMap->area() == 1) {
		AudioPlayer::playMusic("indoor");
	} else {
		AudioPlayer::playMusic("underground");
	}
	
	Player::player.setNextState<StandingState>();
	
	Sprite::pause = true;
}

void DoorTransition::update() {
	if(m_rect1.x() + m_rect1.width() < 0) {
		Map::currentMap = m_nextMap;
		
		m_atEnd = true;
		
		Sprite::pause = false;
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
	
	if(m_timer.time() > 250) {
		glClearColor(Color::text.r / 255.0f, Color::text.g / 255.0f, Color::text.b / 255.0f, 1.0f);
		
		if(Scene::player && Scene::player->has<PositionComponent>()) {
			auto &positionComponent = Scene::player->get<PositionComponent>();
			
			positionComponent.x = m_playerX;
			positionComponent.y = m_playerY;
			
			positionComponent.direction = (Direction)m_playerDirection;
		}
		
		Player::player.setPosition(m_playerX, m_playerY);
		Player::player.setDirection(m_playerDirection);
		
		m_rect1.move(-1.5, 0);
		m_rect2.move(1.5, 0);
	}
}

void DoorTransition::draw() {
	if(m_timer.time() > 250) {
		m_nextMap->draw();
		
		View::bind(&Map::currentMap->view());
		
		Player::player.draw();
		
		View::bind(nullptr);
		
		m_rect1.draw(Color::text);
		m_rect2.draw(Color::text);
		
		m_statsBar.draw();
	}
}
