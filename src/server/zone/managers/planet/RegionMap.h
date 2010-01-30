/*
 * RegionMap.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef REGIONMAP_H_
#define REGIONMAP_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/StringId.h"

class Region : public Serializable {
protected:
	StringId name;
	float x, y;
	float radius;
	float radius2;

public:
	Region(const String& fullName, float posX, float posY, float radi) {
		name.setStringId(fullName);
		x = posX;
		y = posY;
		radius = radi;
		radius2 = radius * radius;

		addSerializableVariable("name", &name);
		addSerializableVariable("x", &x);
		addSerializableVariable("y", &y);
		addSerializableVariable("radius", &radius);
		addSerializableVariable("radius2", &radius2);
	}

	bool containsPoint(float px, float py) {
		return (((px - x) * (px - x)) + ((py - y) * (py - y)) <= radius2 );
	}

	inline StringId getName() {
		return name;
	}

	inline float getX() {
		return x;
	}

	inline float getY() {
		return y;
	}

	inline float getRadius() {
		return radius;
	}

};

class RegionMap : public Serializable {
	Vector<Region*> regions;

public:
	RegionMap() {
		addSerializableVariable("regions", &regions);
	}

	~RegionMap() {
		for (int i = 0; i < regions.size(); ++i) {
			delete regions.get(i);
		}
	}

	void addRegion(const String& name, float x, float y, float radius) {
		regions.add(new Region(name, x, y, radius));
	}

	bool getRegion(StringId* name, float x, float y) {
		for (int i = 0; i < regions.size(); ++i) {
			Region* region = regions.get(i);

			if (region->containsPoint(x, y)) {
				*name = region->getName();

				return true;
			}
		}

		return false;
	}

	inline int size() {
		return regions.size();
	}
};


#endif /* REGIONMAP_H_ */
