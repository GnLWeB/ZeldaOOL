/*
 * =====================================================================================
 *
 *       Filename:  Entity.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  13/08/2014 22:53:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Entity.hpp"

Entity::Entity(s16 x, s16 y, u16 width, u16 height) {
	m_x = x;
	m_y = y;
	
	m_width = width;
	m_height = height;
	
	m_vx = 0;
	m_vy = 0;
	
	m_hitbox = sf::IntRect(m_x, m_y, m_width, m_height);
}

Entity::~Entity() {
}

