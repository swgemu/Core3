/*
 * ActiveAreaOctree.h
 *
 * Created on: 01/03/2024
 * Author: Hakry
*/

#pragma once

#include "system/lang.h"
#include "engine/log/Logger.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "system/util/Vector.h"
#include "system/lang/ref/UniqueReference.h"

//#define AREA_TREE_SIMPLE

#define DEBUG_AA_OCTREE

namespace server {
namespace zone {

class ActiveAreaOctreeNode : public Logger {
protected:
	SortedVector<Reference<ActiveArea*>> areas;

	UniqueReference<ActiveAreaOctreeNode*> nwNode{};
	UniqueReference<ActiveAreaOctreeNode*> neNode{};
	UniqueReference<ActiveAreaOctreeNode*> swNode{};
	UniqueReference<ActiveAreaOctreeNode*> seNode{};

	UniqueReference<ActiveAreaOctreeNode*> nwNode2{};
	UniqueReference<ActiveAreaOctreeNode*> neNode2{};
	UniqueReference<ActiveAreaOctreeNode*> swNode2{};
	UniqueReference<ActiveAreaOctreeNode*> seNode2{};

	float minX = 0, minY = 0, minZ = 0;
	float maxX = 0, maxY = 0, maxZ = 0;

	const ActiveAreaOctreeNode* parentNode;

	float dividerX = 0, dividerY = 0, dividerZ = 0;

public:
	ActiveAreaOctreeNode(float minx, float miny, float minz, float maxx, float maxy, float maxz, const ActiveAreaOctreeNode* parent);

	bool isEmpty() const {
		return areas.isEmpty();
	}

	void insertArea(ActiveArea* area) {
		areas.put(area);
	}

	void dropArea(ActiveArea* area) {
		areas.drop(area);
	}

	inline bool testInside(float x, float y, float z) const {
		return x >= minX && x < maxX && y >= minY && y < maxY && z >= minZ && z < maxZ;
	}

	bool testAreaInside(float x, float y, float z, float radius) const {
		float xDelta1 = x - radius;
		float xDelta2 = x + radius;
		float yDelta1 = y - radius;
		float yDelta2 = y + radius;
		float zDelta1 = z - radius;
		float zDelta2 = z + radius;

		bool runTest = ((xDelta1 >= minX && xDelta2 < maxX) && (yDelta1 >= minY && yDelta2 < maxY)
			&& (zDelta1 >= minZ && zDelta2 < maxZ));

		return runTest;
	}

	bool testAreaInsideCuboid(ActiveArea* area) const {
		if (area == nullptr)
			return false;

		Vector3 center = area->getAreaCenter();
		//Vector3 bounds = area->getRectangularDimensions();

		float width = area->getWidth();
		float height = area->getHeight();
		float radius = area->getRadius();

		//float llX = bounds[0];
		//float llY = bounds[1];
		//float urX = bounds[2];
		//float urY = bounds[3];

		//bool runTest = (llX >= minX && urX < maxX && llY >= minY && urY < maxY);

		//info(true) << "testAreaInside -- llX = " << llX << " llY = " << llY << " urX = " << urX << " urY = " << urY;

		//return runTest;

		return true;
	}

	bool hasSubNodes() const {
		return nwNode != nullptr || neNode != nullptr || swNode != nullptr || seNode
			!= nullptr || nwNode2 != nullptr || neNode2 != nullptr || swNode2 != nullptr || seNode2 != nullptr;
	}

	bool testInSWArea(float x, float y, float z, float radius) const {
		return (x - radius) >= minX && (x + radius) < dividerX && (y - radius) >= minY && (y + radius) < dividerY
			&& (z - radius) >= minZ && (z + radius) < dividerZ;
	}

	bool testInSEArea(float x, float y, float z, float radius) const {
		return (x - radius) >= dividerX && (x + radius) < maxX && (y - radius) >= minY && (y + radius) < dividerY
			&& (z - radius) >= minZ && (z + radius) < dividerZ;
	}

	bool testInNWArea(float x, float y, float z, float radius) const {
		return (x - radius) >= minX && (x + radius) < dividerX && (y - radius) >= dividerY && (y + radius) < maxY
			&& (z - radius) >= minZ && (z + radius) < dividerZ;
	}

	bool testInNEArea(float x, float y, float z, float radius) const {
		return (x - radius) >= dividerX && (x + radius) < maxX && (y - radius) >= dividerY && (y + radius) < maxY
			&& (z - radius) >= minZ && (z + radius) < dividerZ;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool testInSWArea2(float x, float y, float z, float radius) const {
		return (x - radius) >= minX && (x + radius) < dividerX && (y - radius) >= minY && (y + radius) < dividerY
			&& (z + radius) >= dividerZ && (z - radius) < maxZ;
	}

	bool testInSEArea2(float x, float y, float z, float radius) const {
		return (x - radius) >= dividerX && (x + radius) < maxX && (y - radius) >= minY && (y + radius) < dividerY
			&& (z + radius) >= dividerZ && (z - radius) < maxZ;
	}

	bool testInNWArea2(float x, float y, float z, float radius) const {
		return (x - radius) >= minX && (x + radius) < dividerX && (y - radius) >= dividerY && (y + radius) < maxY
			&& (z + radius) >= dividerZ && (z - radius) < maxZ;
	}

	bool testInNEArea2(float x, float y, float z, float radius) const {
		return (x - radius) >= dividerX && (x + radius) < maxX && (y - radius) >= dividerY && (y + radius) < maxY
			&& (z + radius) >= dividerZ && (z - radius) < maxZ;
	}

	friend class ActiveAreaOctree;
};

class ActiveAreaOctree : public Object, public Logger {
#ifdef AREA_TREE_SIMPLE
	SortedVector<Reference<ActiveArea*>> areas;
#else
	UniqueReference<ActiveAreaOctreeNode*> root{};
#endif

public:
	ActiveAreaOctree(float minx, float miny, float minz, float maxx, float maxy, float maxz) {
#ifndef AREA_TREE_SIMPLE
		root = makeUnique<ActiveAreaOctreeNode>(minx, miny, minz, maxx, maxy, maxz, nullptr);
#else
		areas.setNoDuplicateInsertPlan();
#endif

		setLoggingName("ActiveAreaOctree");
	}

	template <typename AreaType>
	void getActiveAreas(float x, float y, float z, ArrayList<AreaType>& areas) const {
#ifndef AREA_TREE_SIMPLE
		getActiveAreas(root.get(), x, y, z, areas);
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
	void insert(ActiveAreaOctreeNode& node, ActiveArea* area);
	void removeActiveArea(ActiveAreaOctreeNode& node, ActiveArea* area);

	template <typename AreaType>
	void getActiveAreas(ActiveAreaOctreeNode* node, float x, float y, float z, ArrayList<AreaType>& areas) const {
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

		const auto& nodeSW2 = node->swNode2;
		const auto& nodeSE2 = node->seNode2;
		const auto& nodeNW2 = node->nwNode2;
		const auto& nodeNE2 = node->neNode2;

		if (nodeSW != nullptr && nodeSW->testInside(x, y, z)) {
			getActiveAreas(nodeSW.get(), x, y, z, areas);
		} else if (nodeSE != nullptr && nodeSE->testInside(x, y, z)) {
			getActiveAreas(nodeSE.get(), x, y, z, areas);
		} else if (nodeNW != nullptr && nodeNW->testInside(x, y, z)) {
			getActiveAreas(nodeNW.get(), x, y, z, areas);
		} else if (nodeNE != nullptr && nodeNE->testInside(x, y, z)) {
			getActiveAreas(nodeNE.get(), x, y, z, areas);
		} else if (nodeSW2 != nullptr && nodeSW2->testInside(x, y, z)) {
			getActiveAreas(nodeSW.get(), x, y, z, areas);
		} else if (nodeSE2 != nullptr && nodeSE2->testInside(x, y, z)) {
			getActiveAreas(nodeSE.get(), x, y, z, areas);
		} else if (nodeNW2 != nullptr && nodeNW2->testInside(x, y, z)) {
			getActiveAreas(nodeNW.get(), x, y, z, areas);
		} else if (nodeNE2 != nullptr && nodeNE2->testInside(x, y, z)) {
			getActiveAreas(nodeNE.get(), x, y, z, areas);
		}
	}
#endif
};

} // namespace zone
} // namespace server
