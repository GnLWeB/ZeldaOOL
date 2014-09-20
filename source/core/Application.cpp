/*
 * =====================================================================================
 *
 *       Filename:  Application.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/09/2014 19:37:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include "Application.hpp"
#include "GameStateManager.hpp"

Window Application::window;

Application::Application() {
	window.open();
	
	GameStateManager::init();
}

Application::~Application() {
	GameStateManager::free();
	
	window.free();
}

void Application::run() {
	while(window.isOpen()) {
		GameStateManager::top()->handleEvents();
		
		GameStateManager::top()->update();
		
		window.clear();
		
		GameStateManager::top()->render();
		
		window.update();
	}
}

