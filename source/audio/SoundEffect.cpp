/*
 * =====================================================================================
 *
 *       Filename:  SoundEffect.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/09/2014 23:03:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include "Exception.hpp"
#include "ResourceHandler.hpp"
#include "SoundEffect.hpp"

SoundEffect::SoundEffect(const std::string &filename) {
	load(filename);
}

void SoundEffect::load(const std::string &filename) {
	m_sfx.reset(Mix_LoadWAV(filename.c_str()));
	if(!m_sfx) {
		throw EXCEPTION("Unable to load sound effect:", filename, ":", Mix_GetError());
	}
}

void SoundEffect::play(s8 channel) {
	Mix_PlayChannel(channel, m_sfx.get(), 0);
}

void SoundEffect::play(const std::string &resourceName) {
	ResourceHandler::getInstance().get<SoundEffect>(std::string("sfx-") + resourceName).play();
}

