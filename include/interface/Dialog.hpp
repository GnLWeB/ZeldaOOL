/*
 * =====================================================================================
 *
 *       Filename:  Dialog.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  26/09/2014 20:34:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef DIALOG_HPP_
#define DIALOG_HPP_

#include "Font.hpp"
#include "Rectangle.hpp"

class Dialog {
	public:
		Dialog();
		~Dialog();
		
		void draw();
		
		enum Position {
			Top,
			Bottom
		};
		
		void setPosition(Position position) { m_position = position; }
		
	private:
		Position m_position;
		
		Rectangle m_rectangle;
		
		Font m_font;
};

#endif // DIALOG_HPP_