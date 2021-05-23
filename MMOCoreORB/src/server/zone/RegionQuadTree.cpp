#include "server/zone/RegionQuadTree.h"

using namespace server::zone;

RegionQuadTreeNode::RegionQuadTreeNode(float minx, float miny, float maxx, float maxy, const RegionQuadTreeNode* parent)
	: minX(minx), minY(miny), maxX(maxx), maxY(maxy), parentNode(parent) {
	dividerX = (minX + maxX) / 2;
	dividerY = (minY + maxY) / 2;
}

#ifndef REGION_TREE_SIMPLE

void RegionQuadTree::insert(RegionQuadTreeNode& node, ActiveArea* region) {
	if (!node.hasSubNodes()) {
		if ((node.maxX - node.minX <= 8) && (node.maxY - node.minY <= 8)) {
			node.insertRegion(region);

			return;
		}
	}

	if (node.testRegionInside(region->getPositionX(), region->getPositionY(), region->getRadius())) {
		if (node.testInSWArea(*region)) {
			if (node.swNode == nullptr) {
				node.swNode = makeUnique<RegionQuadTreeNode>(node.minX, node.minY, node.dividerX, node.dividerY, &node);
			}

			insert(*node.swNode, region);

			return;
		} else if (node.testInNWArea(*region)) {
			if (node.nwNode == nullptr)
				node.nwNode = makeUnique<RegionQuadTreeNode>(node.minX, node.dividerY, node.dividerX, node.maxY, &node);

			insert(*node.nwNode, region);

			return;
		} else if (node.testInSEArea(*region)) {
			if (node.seNode == nullptr)
				node.seNode = makeUnique<RegionQuadTreeNode>(node.dividerX, node.minY, node.maxX, node.dividerY, &node);

			insert(*node.seNode, region);

			return;
		} else {
			E3_ASSERT (node.testInNEArea(*region));

			if (node.neNode == nullptr)
				node.neNode = makeUnique<RegionQuadTreeNode>(node.dividerX, node.dividerY, node.maxX, node.maxY, &node);

			insert(*node.neNode, region);

			return;
		}
	}

	// insert here
	node.insertRegion(region);

	return;
}

void RegionQuadTree::remove(Reference<ActiveArea*> area) {
	removeActiveArea(*root, area);
}

void RegionQuadTree::removeActiveArea(RegionQuadTreeNode& node, ActiveArea* area) {
	for (int i = 0; i < node.regions.size(); ++i) {
		if (node.regions.get(i) == area) {
			node.regions.remove(i);
			break;
		}
	}

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
	} else if (nodeNE != nullptr) {
	       	E3_ASSERT(nodeNE->testRegionInside(positionX, positionY, radius));

		removeActiveArea(*nodeNE, area);
	}
}
#endif
