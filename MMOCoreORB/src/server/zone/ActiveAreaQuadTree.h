#pragma once

#include "system/lang.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "system/util/Vector.h"
#include "system/lang/ref/UniqueReference.h"

//#define REGION_TREE_SIMPLE

namespace server {
namespace zone {

class ActiveAreaQuadTreeNode {
protected:
	SortedVector<Reference<ActiveArea*>> regions;

	UniqueReference<ActiveAreaQuadTreeNode*> nwNode{};
	UniqueReference<ActiveAreaQuadTreeNode*> neNode{};
	UniqueReference<ActiveAreaQuadTreeNode*> swNode{};
	UniqueReference<ActiveAreaQuadTreeNode*> seNode{};

	float minX = 0, minY = 0;
	float maxX = 0, maxY = 0;

	const ActiveAreaQuadTreeNode* parentNode;

	float dividerX = 0, dividerY = 0;

public:
	ActiveAreaQuadTreeNode(float minx, float miny, float maxx, float maxy, const ActiveAreaQuadTreeNode* parent);

	bool isEmpty() const {
		return regions.isEmpty();
	}

	void insertRegion(ActiveArea* region) {
		regions.put(region);
	}

	void dropRegion(ActiveArea* area) {
		regions.drop(area);
	}

	bool testInside(float x, float y) const {
		return x >= minX && x < maxX && y >= minY && y < maxY;
	}

	bool testRegionInside(float x, float y, float radius) const {
		return (x - radius) >= minX && (x + radius) < maxX && (y - radius) >= minY && (y + radius) < maxY;
	}

	bool hasSubNodes() const {
		return nwNode || neNode || swNode || seNode;
	}

	bool testInSWArea(float x, float y) const {
		return x >= minX && x < dividerX && y >= minY && y < dividerY;
	}

	bool testInSEArea(float x, float y) const {
		return x >= dividerX && x < maxX && y >= minY && y < dividerY;
	}

	bool testInNWArea(float x, float y) const {
		return x >= minX && x < dividerX && y >= dividerY && y < maxY;
	}

	bool testInNEArea(float x, float y) const {
		return x >= dividerX && x < maxX && y >= dividerY && y < maxY;
	}

	friend class ActiveAreaQuadTree;
};

class ActiveAreaQuadTree : public Object {
#ifdef REGION_TREE_SIMPLE
	SortedVector<Reference<ActiveArea*>> regions;
#else
	UniqueReference<ActiveAreaQuadTreeNode*> root{};
#endif

public:
	ActiveAreaQuadTree(float minx, float miny, float maxx, float maxy) {
#ifndef REGION_TREE_SIMPLE
		root = makeUnique<ActiveAreaQuadTreeNode>(minx, miny, maxx, maxy, nullptr);
#else
		regions.setNoDuplicateInsertPlan();
#endif
	}

	template <typename AreaType>
	void getActiveAreas(float x, float y, ArrayList<AreaType>& areas) const {
#ifndef REGION_TREE_SIMPLE
		getActiveAreas(root.get(), x, y, areas);
#else
		for (const auto& area : regions) {
			if (area->containsPoint(x, y)) {
				areas.emplace(area);
			}
		}
#endif
	}

	void insert(Reference<ActiveArea*> region) {
#ifndef REGION_TREE_SIMPLE
		insert(*root, region);
#else
		regions.put(std::move(region));
#endif
	}

#ifdef REGION_TREE_SIMPLE
	void remove(Reference<ActiveArea*> region) {
		regions.drop(region);
	}
#else
	void remove(Reference<ActiveArea*> region);
#endif

protected:
#ifndef REGION_TREE_SIMPLE
	void insert(ActiveAreaQuadTreeNode& node, ActiveArea* region);
	void removeActiveArea(ActiveAreaQuadTreeNode& node, ActiveArea* area);

	template <typename AreaType>
	void getActiveAreas(ActiveAreaQuadTreeNode* node, float x, float y, ArrayList<AreaType>& regions) const {
		if (node == nullptr) {
			return;
		}

		for (const auto& regionEntry : node->regions) {
			if (regionEntry->containsPoint(x, y)) {
				regions.emplace(regionEntry);
			}
		}

		const auto& nodeSW = node->swNode;
		const auto& nodeSE = node->seNode;
		const auto& nodeNW = node->nwNode;
		const auto& nodeNE = node->neNode;

		if (nodeSW != nullptr && nodeSW->testInside(x, y)) {
			getActiveAreas(nodeSW.get(), x, y, regions);
		} else if (nodeSE != nullptr && nodeSE->testInside(x, y)) {
			getActiveAreas(nodeSE.get(), x, y, regions);
		} else if (nodeNW != nullptr && nodeNW->testInside(x, y)) {
			getActiveAreas(nodeNW.get(), x, y, regions);
		} else if (nodeNE != nullptr && nodeNE->testInside(x, y)) {
			getActiveAreas(nodeNE.get(), x, y, regions);
		}
	}
#endif
};

} // namespace zone
} // namespace server
