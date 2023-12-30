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
#ifdef DEBUG_AA_OCTREE
	StringBuffer debugMsg;
	debugMsg << "ActiveAreaOctree::insert -- called " << area->getAreaName() << " Center Point = " << area->getAreaCenter().toString() << " Radius = " << area->getRadius() << "\n";
	debugMsg << "Node Info: minX = " << node.minX << " minY = " << node.minY << " minZ = " << node.minZ << " maxX = " << node.maxX << " maxY = " << node.maxY << " maxZ = " << node.maxZ << "\n";
	debugMsg << "DividerX = " << node.dividerX << " dividerY = " << node.dividerY << " dividerZ =  " << node.dividerZ << "\n";

	if (area->isCuboidAreaShape()) {
		CuboidAreaShape* cube = cast<CuboidAreaShape*>(area->getAreaShape());

		debugMsg << cube->getDimensionLog();
	}
#endif

	if (!node.hasSubNodes()) {
		if ((node.maxX - node.minX <= 8) && (node.maxY - node.minY <= 8) && (node.maxZ - node.minZ <= 8)) {
			node.insertArea(area);

			return;
		}
	}

	Vector3 location = area->getAreaCenter();

	const float x = location.getX();
	const float y = location.getY();
	const float z = location.getZ();

	const float radius = area->getRadius();

	bool isCuboid = area->isCuboidAreaShape();

	if ((isCuboid && node.testAreaInsideCuboid(area)) || node.testAreaInside(x, y, z, radius)) {
		if (node.testInSWArea(x, y, z, radius)) {
			if (node.swNode == nullptr) {
				node.swNode = makeUnique<ActiveAreaOctreeNode>(node.minX, node.minY, node.minZ, node.dividerX, node.dividerY, node.dividerZ, &node);
			}

			insert(*node.swNode, area);
		} else if (node.testInSEArea(x, y, z, radius)) {
			if (node.seNode == nullptr)
				node.seNode = makeUnique<ActiveAreaOctreeNode>(node.dividerX, node.minY, node.minZ, node.maxX, node.dividerY, node.dividerZ, &node);

			insert(*node.seNode, area);
		} else if (node.testInNWArea(x, y, z, radius)) {
			if (node.nwNode == nullptr)
				node.nwNode = makeUnique<ActiveAreaOctreeNode>(node.minX, node.dividerY, node.minZ, node.dividerX, node.maxY, node.dividerZ, &node);

			insert(*node.nwNode, area);
		} else if (node.testInNEArea(x, y, z, radius)) {
			if (node.neNode == nullptr)
				node.neNode = makeUnique<ActiveAreaOctreeNode>(node.dividerX, node.dividerY, node.minZ, node.maxX, node.maxY, node.dividerZ, &node);

			insert(*node.neNode, area);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if (node.testInSWArea2(x, y, z, radius)) {
			if (node.swNode2 == nullptr) {
				node.swNode2 = makeUnique<ActiveAreaOctreeNode>(node.minX, node.minY, node.dividerZ, node.dividerX, node.dividerY, node.maxZ, &node);
			}

			insert(*node.swNode2, area);
		} else if (node.testInSEArea2(x, y, z, radius)) {
			if (node.seNode2 == nullptr)
				node.seNode2 = makeUnique<ActiveAreaOctreeNode>(node.minX, node.minY, node.dividerZ, node.maxX, node.dividerY, node.maxZ, &node);

			insert(*node.seNode2, area);
		} else if (node.testInNWArea2(x, y, z, radius)) {
			if (node.nwNode2 == nullptr)
				node.nwNode2 = makeUnique<ActiveAreaOctreeNode>(node.minX, node.minY, node.dividerZ, node.dividerX, node.maxY, node.maxZ, &node);

			insert(*node.nwNode2, area);
		} else if (node.testInNEArea2(x, y, z, radius)) {
			if (node.neNode2 == nullptr)
				node.neNode2 = makeUnique<ActiveAreaOctreeNode>(node.minX, node.minY, node.dividerZ, node.maxX, node.maxY, node.maxZ, &node);

			insert(*node.neNode2, area);
		} else {
			node.insertArea(area);
		}
	}
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
