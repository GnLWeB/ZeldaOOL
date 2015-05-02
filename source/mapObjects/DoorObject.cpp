/*
 * =====================================================================================
 *
 *       Filename:  DoorObject.cpp
 *
 *    Description:  
 *
 *        Created:  06/10/2014 18:13:42
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "ApplicationStateStack.hpp"
#include "AudioPlayer.hpp"
#include "DoorObject.hpp"
#include "DoorTransition.hpp"
#include "Map.hpp"
#include "TransitionState.hpp"

void DoorObject::setDestination(u16 area, u8 mapX, u8 mapY, float playerX, float playerY, u8 playerDirection) {
	m_area = area;
	
	m_mapX = mapX;
	m_mapY = mapY;
	
	m_playerX = playerX;
	m_playerY = playerY;
	
	m_playerDirection = playerDirection;
}

void DoorObject::onEvent(u8 event) {
	if(event == Map::EventType::ChangeMap) {
		AudioPlayer::playEffect("mapStairs");
		
		// FIXME: TO REMOVE LATER
		ApplicationStateStack::getInstance().push<TransitionState>(new DoorTransition(m_area, m_mapX, m_mapY, m_playerX, m_playerY, m_playerDirection));
	}
}
