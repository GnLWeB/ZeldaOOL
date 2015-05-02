/*
 * =====================================================================================
 *
 *       Filename:  Weapon.cpp
 *
 *    Description:  
 *
 *        Created:  15/09/2014 22:26:02
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "GamePad.hpp"
#include "Player.hpp"
#include "Weapon.hpp"

Weapon::Weapon(const std::string &textureName, u8 level, u16 width, u16 height) : Movable(textureName, 0, 0, width, height), m_player(Player::player) {
	m_level = level;
	
	std::string weaponName = textureName.substr(textureName.find_first_of('-') + 1);
	if(m_level > 0) weaponName += "L" + std::to_string(m_level);
	
	m_icon.load(std::string("icons-") + weaponName);
}

bool Weapon::keyPressed() {
	return((GamePad::isKeyPressed(GameKey::A)
		 && m_player.inventory().weaponA() == this)
		|| (GamePad::isKeyPressed(GameKey::B)
		 && m_player.inventory().weaponB() == this));
}

bool Weapon::keyPressedOnce() {
	return((GamePad::isKeyPressedOnce(GameKey::A)
		 && m_player.inventory().weaponA() == this)
		|| (GamePad::isKeyPressedOnce(GameKey::B)
		 && m_player.inventory().weaponB() == this));
}
