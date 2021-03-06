/*
 * =====================================================================================
 *
 *       Filename:  ButtonLoader.cpp
 *
 *    Description:
 *
 *        Created:  22/02/2015 17:15:04
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "ButtonComponent.hpp"
#include "ButtonFactory.hpp"
#include "ButtonLoader.hpp"

void ButtonLoader::load(XMLElement *buttonElement, Scene &scene) {
	u16 tileX = buttonElement->IntAttribute("tileX");
	u16 tileY = buttonElement->IntAttribute("tileY");

	SceneObject &button = scene.addObject(ButtonFactory::create(tileX, tileY));
	auto &buttonComponent = button.get<ButtonComponent>();

	XMLElement *tileChangeElement = buttonElement->FirstChildElement("tileChange");
	while(tileChangeElement) {
		u16 tileX = tileChangeElement->IntAttribute("tileX");
		u16 tileY = tileChangeElement->IntAttribute("tileY");

		u16 newID = tileChangeElement->IntAttribute("newID");

		buttonComponent.addTileChange(tileX, tileY, newID);

		tileChangeElement = tileChangeElement->NextSiblingElement("tileChange");
	}
}

