/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/ActiveAreaOctree.h"
#include "server/zone/objects/area/areashapes/CuboidAreaShape.h"
#include "server/zone/objects/area/areashapes/SphereAreaShape.h"

using namespace server::zone;

ActiveAreaOctreeNode::ActiveAreaOctreeNode(float minx, float minz, float miny, float maxx, float maxz, float maxy, const ActiveAreaOctreeNode* parent) : minX(minx), minZ(minz), minY(miny), maxX(maxx), maxZ(maxz), maxY(maxy), parentNode(parent) {
	dividerX = (minX + maxX) / 2;
	dividerZ = (minZ + maxZ) / 2;
	dividerY = (minY + maxY) / 2;

	areas.setNoDuplicateInsertPlan();

	setLoggingName("ActiveAreaOctreeNode");
}

#ifndef AREA_TREE_SIMPLE

void ActiveAreaOctree::insert(ActiveAreaOctreeNode& node, ActiveArea* area) {
#ifdef DEBUG_AA_OCTREE
	StringBuffer debugMsg;
	debugMsg << "ActiveAreaOctree::insert -- called " << area->getAreaName() << " Center Point = " << area->getAreaCenter().toString() << " Radius = " << area->getRadius() << "\n";
	debugMsg << "Node Info: minX = " << node.minX << " minZ = " << node.minZ << " minY = " << node.minY << " maxX = " << node.maxX << " maxZ = " << node.maxZ << " maxY = " << node.maxY << "\n";
	debugMsg << "DividerX = " << node.dividerX << " dividerZ = " << node.dividerZ << " dividerY = " << node.dividerY << "\n";

	if (area->isCuboidAreaShape()) {
		CuboidAreaShape* cube = cast<CuboidAreaShape*>(area->getAreaShape());

		debugMsg << cube->getDimensionLog();
	}

	info(true) << debugMsg.toString();
#endif

	if (!node.hasSubNodes()) {
#ifdef DEBUG_AA_OCTREE
		info(true) << "insert -- area has no subnodes.";
#endif

		if ((node.maxX - node.minX <= 8) && (node.maxZ - node.minZ <= 8) && (node.maxY - node.minY <= 8)) {
			node.insertArea(area);
			return;
		}
	}

	Vector3 location = area->getAreaCenter();

	const float x = location.getX();
	const float z = location.getZ();
	const float y = location.getY();

	const float radius = area->getRadius();

	bool isCuboid = area->isCuboidAreaShape();

#ifdef DEBUG_AA_OCTREE
	info(true) << "insert -- isCuboid: " << (isCuboid ? "True" : "False") << " Radius: " << radius;
#endif

	if ((isCuboid && node.testAreaInsideCuboid(area)) || node.testAreaInside(x, z, y, radius)) {
		if (node.testInSWArea(x, z, y, radius)) {
			if (node.swNode == nullptr) {
				node.swNode = makeUnique<ActiveAreaOctreeNode>(node.minX, node.minZ, node.minY, node.dividerX, node.dividerZ, node.dividerY, &node);
			}

#ifdef DEBUG_AA_OCTREE
			info(true) << "Inside SW node";
#endif

			insert(*node.swNode, area);
		} else if (node.testInSEArea(x, z, y, radius)) {
			if (node.seNode == nullptr) {
				node.seNode = makeUnique<ActiveAreaOctreeNode>(node.dividerX, node.minZ, node.minY, node.maxX, node.dividerZ, node.dividerY, &node);
			}

#ifdef DEBUG_AA_OCTREE
			info(true) << "Inside SE node";
#endif

			insert(*node.seNode, area);
		} else if (node.testInNWArea(x, z, y, radius)) {
			if (node.nwNode == nullptr) {
				node.nwNode = makeUnique<ActiveAreaOctreeNode>(node.minX, node.minZ, node.dividerY, node.dividerX, node.dividerZ, node.maxY, &node);
			}

#ifdef DEBUG_AA_OCTREE
			info(true) << "Inside NW node";
#endif

			insert(*node.nwNode, area);
		} else if (node.testInNEArea(x, z, y, radius)) {
			if (node.neNode == nullptr) {
				node.neNode = makeUnique<ActiveAreaOctreeNode>(node.dividerX, node.minZ, node.dividerY, node.maxX, node.dividerZ, node.maxY, &node);
			}

#ifdef DEBUG_AA_OCTREE
			info(true) << "Inside NE node";
#endif

			insert(*node.neNode, area);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if (node.testInSWArea2(x, z, y, radius)) {
			if (node.swNode2 == nullptr) {
				node.swNode2 = makeUnique<ActiveAreaOctreeNode>(node.minX, node.dividerZ, node.minY, node.dividerX, node.maxZ, node.dividerY, &node);
			}

#ifdef DEBUG_AA_OCTREE
			info(true) << "Inside SW-2 node";
#endif

			insert(*node.swNode2, area);
		} else if (node.testInSEArea2(x, z, y, radius)) {
			if (node.seNode2 == nullptr) {
				node.seNode2 = makeUnique<ActiveAreaOctreeNode>(node.minX, node.dividerZ, node.minY, node.maxX, node.maxZ, node.dividerY, &node);
			}

#ifdef DEBUG_AA_OCTREE
			info(true) << "Inside SE-2 node";
#endif

			insert(*node.seNode2, area);
		} else if (node.testInNWArea2(x, z, y, radius)) {
			if (node.nwNode2 == nullptr) {
				node.nwNode2 = makeUnique<ActiveAreaOctreeNode>(node.minX, node.dividerZ, node.minY, node.dividerX, node.maxZ, node.maxY, &node);
			}

#ifdef DEBUG_AA_OCTREE
			info(true) << "Inside NW-2 node";
#endif

			insert(*node.nwNode2, area);
		} else if (node.testInNEArea2(x, z, y, radius)) {
			if (node.neNode2 == nullptr) {
				node.neNode2 = makeUnique<ActiveAreaOctreeNode>(node.minX, node.dividerZ, node.minY, node.maxX, node.maxZ, node.maxY, &node);
			}

#ifdef DEBUG_AA_OCTREE
			info(true) << "Inside NE-2 node";
#endif

			insert(*node.neNode2, area);
		} else {
#ifdef DEBUG_AA_OCTREE
			info(true) << "insert FINAL -- Inserting into node.";
#endif
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

	if (nodeSW != nullptr && nodeSW->testAreaInside(positionX, positionZ, positionY, radius)) {
		removeActiveArea(*nodeSW, area);
	} else if (nodeSE != nullptr && nodeSE->testAreaInside(positionX, positionZ, positionY, radius)) {
		removeActiveArea(*nodeSE, area);
	} else if (nodeNW != nullptr && nodeNW->testAreaInside(positionX, positionZ, positionY, radius)) {
		removeActiveArea(*nodeNW, area);
	} else if (nodeNE != nullptr && nodeNE->testAreaInside(positionX, positionZ, positionY, radius)) {
		removeActiveArea(*nodeNE, area);
	} else if (nodeSW2 != nullptr && nodeSW2->testAreaInside(positionX, positionZ, positionY, radius)) {
		removeActiveArea(*nodeSW2, area);
	} else if (nodeSE2 != nullptr && nodeSE2->testAreaInside(positionX, positionZ, positionY, radius)) {
		removeActiveArea(*nodeSE2, area);
	} else if (nodeNW2 != nullptr && nodeNW2->testAreaInside(positionX, positionZ, positionY, radius)) {
		removeActiveArea(*nodeNW2, area);
	} else if (nodeNE2 != nullptr && nodeNE2->testAreaInside(positionX, positionZ, positionY, radius)) {
		removeActiveArea(*nodeNE2, area);
	}
}
#endif
