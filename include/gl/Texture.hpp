/*
 * =====================================================================================
 *
 *       Filename:  Texture.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/12/2014 17:07:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <string>

#include <SFML/OpenGL.hpp>

#include "Types.hpp"

class Texture {
	public:
		Texture();
		Texture(std::string filename);
		~Texture();
		
		void load(std::string filename);
		
		u16 width() const { return m_width; }
		u16 height() const { return m_height; }
		
		static void bind(const Texture *texture);
		
	protected:
		std::string m_filename;
		
		u16 m_width;
		u16 m_height;
		
		GLuint m_texture;
};

#endif // TEXTURE_HPP_
