/*
 * =====================================================================================
 *
 *       Filename:  PlayerState.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/09/2014 22:24:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "CharacterManager.hpp"
#include "PlayerState.hpp"

PlayerState::PlayerState() : BattlerState(&CharacterManager::player), m_player(*(Player*)(m_battler)) {
}

PlayerState::~PlayerState() {
}

