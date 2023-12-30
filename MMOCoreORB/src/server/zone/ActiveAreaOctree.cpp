/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/ActiveAreaOctree.h"
#include "server/zone/objects/area/areashapes/CuboidAreaShape.h"
#include "server/zone/objects/area/areashapes/SphereAreaShape.h"

using namespace server::zone;

ActiveAreaOctreeNode::ActiveAreaOctreeNode(float minx, float miny, float minz, float maxx, float maxy, float maxz, const ActiveAreaOctreeNode* parent) : minX(minx), minY(miny), minZ(minz), maxX(maxx), maxY(maxy), maxZ(maxz), parentNode(parent) {
	dividerX = (minX + maxX) / 2;
	dividerY = (minY + maxY) / 2;
	dividerZ = (minZ + maxZ) / 2;

	areas.setNoDuplicateInsertPlan();

	setLoggingName("ActiveAreaOctreeNode");
}

#ifndef AREA_TREE_SIMPLE

void ActiveAreaOctree::insert(ActiveAreaOctreeNode& node, ActiveArea* area) {
	//info(true) << "ActiveAreaOctree::insert -- called " << area->getAreaName() << " Center Point = " << area->getAreaCenter().toString() << " Radius = " << area->getRadius();
	//info(true) << "ActiveAreaOctree::insert  -- Node Info: minX = " << node.minX << " minY = " << node.minY << " maxX = " << node.maxX << " maxY = " << node.maxY << " DividerX = " << node.dividerX << " dividerY = " << node.dividerY;

	/*if (area->isRectangularAreaShape()) {
		RectangularAreaShape* rect = cast<RectangularAreaShape*>(area->getAreaShape());

		info(true) << "ActiveAreaOctree::insert  --  Rectangle Info = ";
		 rect->logDimensions();
	}*/

	if (!node.hasSubNodes()) {
		if ((node.maxX - node.minX <= 8) && (node.maxY - node.minY <= 8)) {
			node.insertArea(area);

			return;
		}
	}

	Vector3 location = area->getAreaCenter();

	const float x = location.getX();
	const float y = location.getY();
	const float z = location.getZ();

	const float radius = area->getRadius();

	/*
	bool isRectangle = area->isRectangularAreaShape();

	if ((isRectangle && node.testAreaInsideRectangle(area)) || node.testAreaInside(x, y, radius)) {
		if (node.testInSWArea(x, y, radius)) {
			if (node.swNode == nullptr) {
				node.swNode = makeUnique<ActiveAreaOctreeNode>(node.minX, node.minY, node.minz, node.dividerX, node.dividerY, &node);
			}

			insert(*node.swNode, area);
		} else if (node.testInNWArea(x, y, radius)) {
			if (node.nwNode == nullptr)
				node.nwNode = makeUnique<ActiveAreaOctreeNode>(node.minX, node.dividerY, node.dividerX, node.maxY, &node);

			insert(*node.nwNode, area);
		} else if (node.testInSEArea(x, y, radius)) {
			if (node.seNode == nullptr)
				node.seNode = makeUnique<ActiveAreaOctreeNode>(node.dividerX, node.minY, node.maxX, node.dividerY, &node);

			insert(*node.seNode, area);
		} else if (node.testInNEArea(x, y, radius)) {
			if (node.neNode == nullptr)
				node.neNode = makeUnique<ActiveAreaOctreeNode>(node.dividerX, node.dividerY, node.maxX, node.maxY, &node);

			insert(*node.neNode, area);
		} else {
			node.insertArea(area);
		}
	}
	*/
}

void ActiveAreaOctree::remove(Reference<ActiveArea*> area) {
	removeActiveArea(*root, area);
}

void ActiveAreaOctree::removeActiveArea(ActiveAreaOctreeNode& node, ActiveArea* area) {
	node.dropArea(area);

	const auto& nodeSW = node.swNode;
	const auto& nodeSE = node.seNode;
	const auto& nodeNW = node.nwNode;
	const auto& nodeNE = node.neNode;

	const auto& nodeSW2 = node.swNode2;
	const auto& nodeSE2 = node.seNode2;
	const auto& nodeNW2 = node.nwNode2;
	const auto& nodeNE2 = node.neNode2;

	const float positionX = area->getPositionX();
	const float positionY = area->getPositionY();
	const float positionZ = area->getPositionZ();

	const float radius = area->getRadius();

	if (nodeSW != nullptr && nodeSW->testAreaInside(positionX, positionY, positionZ, radius)) {
		removeActiveArea(*nodeSW, area);
	} else if (nodeSE != nullptr && nodeSE->testAreaInside(positionX, positionY, positionZ, radius)) {
		removeActiveArea(*nodeSE, area);
	} else if (nodeNW != nullptr && nodeNW->testAreaInside(positionX, positionY, positionZ, radius)) {
		removeActiveArea(*nodeNW, area);
	} else if (nodeNE != nullptr && nodeNE->testAreaInside(positionX, positionY, positionZ, radius)) {
		removeActiveArea(*nodeNE, area);
	} else if (nodeSW2 != nullptr && nodeSW2->testAreaInside(positionX, positionY, positionZ, radius)) {
		removeActiveArea(*nodeNW, area);
	} else if (nodeSE2 != nullptr && nodeSE2->testAreaInside(positionX, positionY, positionZ, radius)) {
		removeActiveArea(*nodeNW, area);
	} else if (nodeNW2 != nullptr && nodeNW2->testAreaInside(positionX, positionY, positionZ, radius)) {
		removeActiveArea(*nodeNW, area);
	} else if (nodeNE2 != nullptr && nodeNE2->testAreaInside(positionX, positionY, positionZ, radius)) {
		removeActiveArea(*nodeNW, area);
	}
}
#endif
