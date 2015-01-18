/*
 * =====================================================================================
 *
 *       Filename:  MapState.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/09/2014 00:22:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <cmath>

#include "AnimationManager.hpp"
#include "BackgroundMusic.hpp"
#include "CharacterManager.hpp"
#include "ChestObject.hpp"
#include "DialogState.hpp"
#include "DoorManager.hpp"
#include "DoorTransition.hpp"
#include "EffectManager.hpp"
#include "Keyboard.hpp"
#include "MapLoader.hpp"
#include "MapState.hpp"
#include "MenuState.hpp"
#include "Octorok.hpp"
#include "ResourceHandler.hpp"
#include "ScrollingTransition.hpp"
#include "SoundEffect.hpp"
#include "TilesetLoader.hpp"
#include "TransitionState.hpp"
#include "WeaponManager.hpp"

#include "KeyboardMovement.hpp"

MapState::MapState() {
	WeaponManager::init();
	
	CharacterManager::player.load();
	
	ResourceHandler::getInstance().addType("data/config/tilesets.xml", TilesetLoader());
	ResourceHandler::getInstance().addType("data/config/maps.xml", MapLoader());
	
	Map::currentMap = &Map::getMap(0, 0, 0);
	
	DoorManager::init();
	
	EffectManager::init();
	
	AnimationManager::init();
	
	Object &button = Map::currentMap->addObject<Object>(7 * 16, 2 * 16);
	
	//button->setEventAction(Map::EventType::ButtonPressed, [&](Object *obj) {
	//	SoundEffect::play("chest");
	//	
	//	Map::currentMap->setTile(obj->x() / 16, obj->y() / 16, 8);
	//	
	//	Map::currentMap->setTile(7, 6, 36);
	//	Map::currentMap->setTile(8, 6, 36);
	//});
	
	Map::getMap(0, 0, 1).addObject<ChestObject>(1 * 16, 5 * 16);
	Map::getMap(2, 0, 0).addObject<ChestObject>(5 * 16, 2 * 16);
	
	Map::getMap(0, 1, 0).addObject<Octorok>(5 * 16, 4 * 16, Character::Direction::Right);
	Map::getMap(2, 0, 0).addObject<Octorok>(5 * 16, 3 * 16, Character::Direction::Right);
	
	BackgroundMusic::play("plain");
}

void MapState::update() {
	Map::currentMap->update();
	
	CharacterManager::player.update();
	
	if(CharacterManager::player.stateManager().currentState()->canStartMapTransition()) {
		if(CharacterManager::player.x() < -3) {
			m_stateStack->push<TransitionState>(new ScrollingTransition(ScrollingTransition::Mode::ScrollingLeft));
		}
		else if(CharacterManager::player.x() + 13 > Map::currentMap->width() * 16) {
			m_stateStack->push<TransitionState>(new ScrollingTransition(ScrollingTransition::Mode::ScrollingRight));
		}
		else if(CharacterManager::player.y() < -1) {
			m_stateStack->push<TransitionState>(new ScrollingTransition(ScrollingTransition::Mode::ScrollingUp));
		}
		else if(CharacterManager::player.y() + 15 > Map::currentMap->height() * 16) {
			m_stateStack->push<TransitionState>(new ScrollingTransition(ScrollingTransition::Mode::ScrollingDown));
		}
	}
	
	if(Keyboard::isKeyPressedOnce(Keyboard::Select)) {
		m_stateStack->push<DialogState>(this, "L'[1]Arbre Bojo[0] est tout à l'est de cette grotte.");
	}
	
	if(Keyboard::isKeyPressedOnce(Keyboard::Start)) {
		SoundEffect::play("menuOpen");
		
		m_stateStack->push<MenuState>();
	}
}

void MapState::render() {
	View::bind(&Map::currentMap->view());
	
	Map::currentMap->draw();
	
	AnimationManager::playAnimations();
	
	CharacterManager::player.draw();
	
	EffectManager::drawEffects(CharacterManager::player);
	
	View::bind(nullptr);
	
	m_statsBar.draw();
}

