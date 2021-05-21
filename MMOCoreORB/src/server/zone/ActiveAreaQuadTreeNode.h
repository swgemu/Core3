/*
 Copyright (C) 2007 <SWGEmu>. All rights reserved.
 Distribution of this file for usage outside of Core3 is prohibited.
 */

#ifndef ACTIVEAREAQUADTREENODE_H_
#define ACTIVEAREAQUADTREENODE_H_

#include "system/lang.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/area/areashapes/AreaShape.h"
#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/ActiveAreaQuadTreeEntry.h"

namespace server {
namespace zone {

class ActiveAreaQuadTree;
class ActiveAreaQuadTreeEntry;

class ActiveAreaQuadTreeNode: public Object {
	SortedVector<Reference<ActiveAreaQuadTreeEntry*> > activeAreas;

    WeakReference<ActiveAreaQuadTreeNode*> parentNode;

	Reference<ActiveAreaQuadTreeNode*> nwNode;
	Reference<ActiveAreaQuadTreeNode*> neNode;
	Reference<ActiveAreaQuadTreeNode*> swNode;
	Reference<ActiveAreaQuadTreeNode*> seNode;

	float minX, minY;
	float maxX, maxY;

	float dividerX, dividerY;

public:
	ActiveAreaQuadTreeNode();
	ActiveAreaQuadTreeNode(float minx, float miny, float maxx, float maxy, ActiveAreaQuadTreeNode *parent);
	~ActiveAreaQuadTreeNode();

	bool isEmpty() const {
		return activeAreas.isEmpty();
	}

	void insertArea(Reference<ActiveArea*> area) {
		activeAreas.put(new ActiveAreaQuadTreeEntry(area.get(), area->getPositionX(), area->getPositionY()));
	}

	void removeArea(ActiveAreaQuadTreeEntry *obj) {
		activeAreas.drop(obj);
	}

	bool testInside(float x, float y) const {
		return x >= minX && x < maxX && y >= minY && y < maxY;
	}

	bool testAreaInside(Reference<ActiveArea*> area) const {
		float x = area->getPositionX();
		float y = area->getPositionY();
		float areaLeft = 0;
		float areaRight = 0;
		float areaTop = 0;
		float areaBot = 0;

		if (area->isRectangularAreaShape()) {
			Reference<RectangularAreaShape*> shape = cast<RectangularAreaShape*>(area->getAreaShape());

			if (shape == nullptr)
				return false;

			float height = shape->getHeight();
			float width = shape->getWidth();
			areaLeft = x - (width / 2);
			areaRight = x + (width / 2);
			areaTop = y + (height / 2);
			areaBot = y - (height / 2);
		} else {
			float radius = area->getRadius();
			areaLeft = x - radius;
			areaRight = x + radius;
			areaTop = y + radius;
			areaBot = y - radius;
		}

		return areaLeft >= minX && areaRight < maxX && areaBot >= minY && areaTop < maxY;
	}

	bool hasSubNodes() const {
		return nwNode || neNode || swNode || seNode;
	}

	bool testInSWArea(Reference<ActiveArea*> area) const {
		float x = area->getPositionX();
		float y = area->getPositionY();
		float areaLeft = 0;
		float areaRight = 0;
		float areaTop = 0;
		float areaBot = 0;

		if (area->isRectangularAreaShape()) {
			Reference<RectangularAreaShape*> shape = cast<RectangularAreaShape*>(area->getAreaShape());

			if (shape == nullptr)
				return false;

			float height = shape->getHeight();
			float width = shape->getWidth();
			areaLeft = x - (width / 2);
			areaRight = x + (width / 2);
			areaTop = y + (height / 2);
			areaBot = y - (height / 2);
		} else {
			float radius = area->getRadius();
			areaLeft = x - radius;
			areaRight = x + radius;
			areaTop = y + radius;
			areaBot = y - radius;
		}

		return areaLeft >= minX && areaRight < dividerX && areaBot >= minY && areaTop < dividerY;
	}

	bool testInSEArea(Reference<ActiveArea*> area) const {
		float x = area->getPositionX();
		float y = area->getPositionY();
		float areaLeft = 0;
		float areaRight = 0;
		float areaTop = 0;
		float areaBot = 0;

		if (area->isRectangularAreaShape()) {
			Reference<RectangularAreaShape*> shape = cast<RectangularAreaShape*>(area->getAreaShape());

			if (shape == nullptr)
				return false;

			float height = shape->getHeight();
			float width = shape->getWidth();
			areaLeft = x - (width / 2);
			areaRight = x + (width / 2);
			areaTop = y + (height / 2);
			areaBot = y - (height / 2);
		} else {
			float radius = area->getRadius();
			areaLeft = x - radius;
			areaRight = x + radius;
			areaTop = y + radius;
			areaBot = y - radius;
		}

		return areaLeft >= dividerX && areaRight < maxX && areaBot >= minY && areaTop < dividerY;
	}

	bool testInNWArea(Reference<ActiveArea*> area) const {
		float x = area->getPositionX();
		float y = area->getPositionY();
		float areaLeft = 0;
		float areaRight = 0;
		float areaTop = 0;
		float areaBot = 0;

		if (area->isRectangularAreaShape()) {
			Reference<RectangularAreaShape*> shape = cast<RectangularAreaShape*>(area->getAreaShape());

			if (shape == nullptr)
				return false;

			float height = shape->getHeight();
			float width = shape->getWidth();
			areaLeft = x - (width / 2);
			areaRight = x + (width / 2);
			areaTop = y + (height / 2);
			areaBot = y - (height / 2);
		} else {
			float radius = area->getRadius();
			areaLeft = x - radius;
			areaRight = x + radius;
			areaTop = y + radius;
			areaBot = y - radius;
		}

		return areaLeft >= minX && areaRight < dividerX && areaBot >= dividerY && areaTop < maxY;
	}

	bool testInNEArea(Reference<ActiveArea*> area) const {
		float x = area->getPositionX();
		float y = area->getPositionY();
		float areaLeft = 0;
		float areaRight = 0;
		float areaTop = 0;
		float areaBot = 0;

		if (area->isRectangularAreaShape()) {
			Reference<RectangularAreaShape*> shape = cast<RectangularAreaShape*>(area->getAreaShape());

			if (shape == nullptr)
				return false;

			float height = shape->getHeight();
			float width = shape->getWidth();
			areaLeft = x - (width / 2);
			areaRight = x + (width / 2);
			areaTop = y + (height / 2);
			areaBot = y - (height / 2);
		} else {
			float radius = area->getRadius();
			areaLeft = x - radius;
			areaRight = x + radius;
			areaTop = y + radius;
			areaBot = y - radius;
		}

		return areaLeft >= dividerX && areaRight < maxX && areaBot >= dividerY && areaTop < maxY;
	}

	friend class server::zone::ActiveAreaQuadTree;
};

} // namespace server
} // namespace zone


#endif /*ACTIVEAREAQUADTREENODE_H_*/
