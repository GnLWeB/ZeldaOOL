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
#include <ctime>

#include "Application.hpp"
#include "AudioPlayer.hpp"
#include "GameStateManager.hpp"
#include "ResourceHandler.hpp"
#include "TextureLoader.hpp"

Application::Application() {
	srand(time(nullptr));
	
	AudioPlayer::init();
	
	ResourceHandler::getInstance().addType("data/config/textures.xml", TextureLoader());
	
	GameStateManager::init();
}

Application::~Application() {
	GameStateManager::free();
}

void Application::handleEvents() {
	SDL_Event event;
	
	while(SDL_PollEvent(&event) != 0) {
		switch(event.type) {
			case SDL_QUIT:
				m_window.close();
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE) {
					m_window.close();
				}
				break;
			default:
				break;
		}
	}
}

void Application::run() {
	while(m_window.isOpen()) {
		m_clock.measureLastFrameDuration();
		
		handleEvents();
		
		m_clock.updateGame([&] {
			GameStateManager::top()->update();
		});
		
		m_clock.drawGame([&] {
			m_window.clear();
			
			GameStateManager::top()->render();
			
			m_window.update();
		});
	}
}

