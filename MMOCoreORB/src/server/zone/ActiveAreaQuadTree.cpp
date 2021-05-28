#include "server/zone/ActiveAreaQuadTree.h"

using namespace server::zone;

ActiveAreaQuadTreeNode::ActiveAreaQuadTreeNode(float minx, float miny, float maxx, float maxy, const ActiveAreaQuadTreeNode* parent)
	: minX(minx), minY(miny), maxX(maxx), maxY(maxy), parentNode(parent) {
	dividerX = (minX + maxX) / 2;
	dividerY = (minY + maxY) / 2;

	regions.setNoDuplicateInsertPlan();
}

#ifndef REGION_TREE_SIMPLE

void ActiveAreaQuadTree::insert(ActiveAreaQuadTreeNode& node, ActiveArea* region) {
	if (!node.hasSubNodes()) {
		if ((node.maxX - node.minX <= 8) && (node.maxY - node.minY <= 8)) {
			node.insertRegion(region);

			return;
		}
	}

	const float x = region->getPositionX();
	const float y = region->getPositionY();
	const float radius = region->getRadius();

	if (node.testRegionInside(x, y, radius)) {
		if (node.testInSWArea(x, y)) {
			if (node.swNode == nullptr) {
				node.swNode = makeUnique<ActiveAreaQuadTreeNode>(node.minX, node.minY, node.dividerX, node.dividerY, &node);
			}

			insert(*node.swNode, region);
		} else if (node.testInNWArea(x, y)) {
			if (node.nwNode == nullptr)
				node.nwNode = makeUnique<ActiveAreaQuadTreeNode>(node.minX, node.dividerY, node.dividerX, node.maxY, &node);

			insert(*node.nwNode, region);
		} else if (node.testInSEArea(x, y)) {
			if (node.seNode == nullptr)
				node.seNode = makeUnique<ActiveAreaQuadTreeNode>(node.dividerX, node.minY, node.maxX, node.dividerY, &node);

			insert(*node.seNode, region);
		} else {
			E3_ASSERT(node.testInNEArea(x, y));

			if (node.neNode == nullptr)
				node.neNode = makeUnique<ActiveAreaQuadTreeNode>(node.dividerX, node.dividerY, node.maxX, node.maxY, &node);

			insert(*node.neNode, region);
		}

		return;
	}

	// insert here
	node.insertRegion(region);

	return;
}

void ActiveAreaQuadTree::remove(Reference<ActiveArea*> area) {
	removeActiveArea(*root, area);
}

void ActiveAreaQuadTree::removeActiveArea(ActiveAreaQuadTreeNode& node, ActiveArea* area) {
	node.dropRegion(area);

	const auto& nodeSW = node.swNode;
	const auto& nodeSE = node.seNode;
	const auto& nodeNW = node.nwNode;
	const auto& nodeNE = node.neNode;

	const float positionX = area->getPositionX();
	const float positionY = area->getPositionY();
	const float radius = area->getRadius();

	if (nodeSW != nullptr && nodeSW->testRegionInside(positionX, positionY, radius)) {
		removeActiveArea(*nodeSW, area);
	} else if (nodeSE != nullptr && nodeSE->testRegionInside(positionX, positionY, radius)) {
		removeActiveArea(*nodeSE, area);
	} else if (nodeNW != nullptr && nodeNW->testRegionInside(positionX, positionY, radius)) {
		removeActiveArea(*nodeNW, area);
	} else if (nodeNE != nullptr && nodeNE->testRegionInside(positionX, positionY, radius)) {
		removeActiveArea(*nodeNE, area);
	}
}
#endif
