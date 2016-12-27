/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NOBUILDAREAMAP_H_
#define NOBUILDAREAMAP_H_

#include "server/zone/objects/region/Region.h"

class NoBuildAreaMap : public Object {
	Vector<ManagedReference<Region*> > areas;

public:
	NoBuildAreaMap() { }

	~NoBuildAreaMap() {

	}

	bool add(Region* region) {
		return areas.add(region);
	}

	bool isNoBuildArea(float x, float y, StringId& fullAreaName) {
		for (int i = 0; i < areas.size(); i++) {
			Region* region = areas.get(i);

			if (region->containsPoint(x,y)) {
				fullAreaName = *region->getObjectName();

				return true;
			}
		}

		return false;
	}
};
#endif /* NOBUILDAREAMAP_H_ */
