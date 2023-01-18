#pragma once

#include "system/lang.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "system/util/Vector.h"
#include "system/lang/ref/UniqueReference.h"

//#define AREA_TREE_SIMPLE

namespace server {
namespace zone {

class ActiveAreaQuadTreeNode : public Logger {
protected:
	SortedVector<Reference<ActiveArea*>> areas;

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
		return areas.isEmpty();
	}

	void insertArea(ActiveArea* area) {
		areas.put(area);
	}

	void dropArea(ActiveArea* area) {
		areas.drop(area);
	}

	bool testInside(float x, float y) const {
		return x >= minX && x < maxX && y >= minY && y < maxY;
	}

	bool testAreaInside(float x, float y, float radius) const {
		return (x - radius) >= minX && (x + radius) < maxX && (y - radius) >= minY && (y + radius) < maxY;
	}

	bool hasSubNodes() const {
		return nwNode || neNode || swNode || seNode;
	}

	bool testInSWArea(float x, float y, float radius) const {
		return (x - radius) >= minX && (x + radius) < dividerX && (y - radius) >= minY && (y + radius) < dividerY;
	}

	bool testInSEArea(float x, float y, float radius) const {
		return (x - radius) >= dividerX && (x + radius) < maxX && (y - radius) >= minY && (y + radius) < dividerY;
	}

	bool testInNWArea(float x, float y, float radius) const {
		return (x - radius) >= minX && (x + radius) < dividerX && (y - radius) >= dividerY && (y + radius) < maxY;
	}

	bool testInNEArea(float x, float y, float radius) const {
		return (x - radius) >= dividerX && (x + radius) < maxX && (y - radius) >= dividerY && (y + radius) < maxY;
	}

	friend class ActiveAreaQuadTree;
};

class ActiveAreaQuadTree : public Object, public Logger {
#ifdef AREA_TREE_SIMPLE
	SortedVector<Reference<ActiveArea*>> areas;
#else
	UniqueReference<ActiveAreaQuadTreeNode*> root{};
#endif

public:
	ActiveAreaQuadTree(float minx, float miny, float maxx, float maxy) {
#ifndef AREA_TREE_SIMPLE
		root = makeUnique<ActiveAreaQuadTreeNode>(minx, miny, maxx, maxy, nullptr);
#else
		areas.setNoDuplicateInsertPlan();
#endif

		setLoggingName("ActiveAreaQuadTree");
	}

	template <typename AreaType>
	void getActiveAreas(float x, float y, ArrayList<AreaType>& areas) const {
#ifndef AREA_TREE_SIMPLE
		getActiveAreas(root.get(), x, y, areas);
#else
		for (const auto& area : areas) {
			if (area->containsPoint(x, y)) {
				areas.emplace(area);
			}
		}
#endif
	}

	void insert(Reference<ActiveArea*> area) {
#ifndef AREA_TREE_SIMPLE
		insert(*root, area);
#else
		areas.put(std::move(area));
#endif
	}

#ifdef AREA_TREE_SIMPLE
	void remove(Reference<ActiveArea*> area) {
		areas.drop(area);
	}
#else
	void remove(Reference<ActiveArea*> area);
#endif

protected:
#ifndef AREA_TREE_SIMPLE
	void insert(ActiveAreaQuadTreeNode& node, ActiveArea* area);
	void removeActiveArea(ActiveAreaQuadTreeNode& node, ActiveArea* area);

	template <typename AreaType>
	void getActiveAreas(ActiveAreaQuadTreeNode* node, float x, float y, ArrayList<AreaType>& areas) const {
		if (node == nullptr) {
			return;
		}

		for (const auto& areaEntry : node->areas) {
			if (areaEntry->containsPoint(x, y)) {
				areas.emplace(areaEntry);
			}
		}

		const auto& nodeSW = node->swNode;
		const auto& nodeSE = node->seNode;
		const auto& nodeNW = node->nwNode;
		const auto& nodeNE = node->neNode;

		if (nodeSW != nullptr && nodeSW->testInside(x, y)) {
			getActiveAreas(nodeSW.get(), x, y, areas);
		} else if (nodeSE != nullptr && nodeSE->testInside(x, y)) {
			getActiveAreas(nodeSE.get(), x, y, areas);
		} else if (nodeNW != nullptr && nodeNW->testInside(x, y)) {
			getActiveAreas(nodeNW.get(), x, y, areas);
		} else if (nodeNE != nullptr && nodeNE->testInside(x, y)) {
			getActiveAreas(nodeNE.get(), x, y, areas);
		}
	}
#endif
};

} // namespace zone
} // namespace server
