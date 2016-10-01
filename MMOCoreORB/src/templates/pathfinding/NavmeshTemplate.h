/*
 * LootItemTemplate.h
 *
 *  Created on: 18/12/2011
 *      Author: victor
 */

#ifndef LOOTITEMTEMPLATE_H_
#define LOOTITEMTEMPLATE_H_

#include "engine/engine.h"
#include "templates/LuaTemplate.h"

class NavmeshTemplate: public LuaTemplate {
protected:
	String areaName;
	float radius;
	bool absolutePosition;
	Vector3 position;
public:
	NavmeshTemplate() {
		radius = 0;
	}
	
	void readObject(LuaObject* templateData) {
		areaName = templateData->getStringField("name");
		radius = templateData->getFloatField("radius");
		absolutePosition = (bool)templateData->getIntField("absolutePosition");
		if(!absolutePosition) {
			x = templateData->getFloatField();
			y = templateData->getFloatField();
			z = templateData->getFloatField();
		}
	}
	
	String& getAreaName() {
		return areaName;
	}
	
	float getRadius() {
		return radius;
	}
	
};

#endif /* LOOTITEMTEMPLATE_H_ */
