/*
 * =====================================================================================
 *
 *       Filename:  Map.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/09/2014 20:53:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef MAP_HPP_
#define MAP_HPP_

#include "AnimatedTile.hpp"
#include "Object.hpp"
#include "Tileset.hpp"
#include "VertexArray.hpp"

class Map {
	public:
		Map();
		Map(std::string filename, Tileset &tileset, u16 area, u16 x, u16 y);
		~Map();
		
		bool load(std::string filename, Tileset &tileset, u16 area, u16 x, u16 y);
		
		void resetTiles();
		
		void updateTile(s16 x, s16 y);
		void update(s16 offsetX = 0, s16 offsetY = 0);
		
		void drawAnimatedTiles();
		void draw();
		
		u16 getTile(u16 tileX, u16 tileY);
		void setTile(u16 tileX, u16 tileY, u16 tile);
		
		void addObject(Object &obj) { m_objects.push_back(Object(obj)); }
		
		enum EventType {
			ButtonPressed
		};
		
		void sendEvent(EventType event, Entity *e = nullptr);
		
		Tileset tileset() const { return m_tileset; }
		
		u16 area() const { return m_area; }
		
		u16 x() const { return m_x; }
		u16 y() const { return m_y; }
		
		u16 width() const { return m_width; }
		u16 height() const { return m_height; }
		
	private:
		Tileset m_tileset;
		
		u16 m_area;
		
		u16 m_x;
		u16 m_y;
		
		VertexArray m_vertices;
		
		std::vector<s16> m_baseData;
		std::vector<s16> m_data;
		
		u16 m_width;
		u16 m_height;
		
		u16 m_tileWidth;
		u16 m_tileHeight;
		
		std::vector<AnimatedTile> m_animatedTiles;
		
		std::vector<Object> m_objects;
};

#endif // MAP_HPP_
