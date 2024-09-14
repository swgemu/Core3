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

// #define AREA_TREE_SIMPLE
// #define DEBUG_AA_OCTREE

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

	float minX = 0, minZ = 0, minY = 0;
	float maxX = 0, maxZ = 0, maxY = 0;

	const ActiveAreaOctreeNode* parentNode;

	float dividerX = 0, dividerZ = 0, dividerY = 0;

public:
	ActiveAreaOctreeNode(float minx, float minz, float miny, float maxx, float maxz, float maxy, const ActiveAreaOctreeNode* parent);

	bool isEmpty() const {
		return areas.isEmpty();
	}

	void insertArea(ActiveArea* area) {
		areas.put(area);
	}

	void dropArea(ActiveArea* area) {
		areas.drop(area);
	}

	inline bool testInside(float x, float z, float y) const {
		return x >= minX && x < maxX && y >= minY && y < maxY && z >= minZ && z < maxZ;
	}

	bool testAreaInside(float x, float z, float y, float radius) const {
		float xDelta1 = x - radius;
		float xDelta2 = x + radius;
		float yDelta1 = y - radius;
		float yDelta2 = y + radius;
		float zDelta1 = z - radius;
		float zDelta2 = z + radius;

#ifdef DEBUG_AA_OCTREE
		info(true) << "testAreaInside --- Radius: " << radius << " xDelta1 = " << xDelta1 << " xDelta2 = " << xDelta2 << " yDelta1 = " << yDelta1 << " yDelta2 = " << yDelta2 <<
		" zDelta1 = " << zDelta1 << " zDelta2 = " << zDelta2;
		info(true) << "minX = " << minX << " maxX = " << maxX << " minZ = " << minZ << " maxZ = " << maxZ << " minY = " << minY << " maxY = " << maxY;
#endif

		bool runTest = ((xDelta1 > minX && xDelta2 < maxX) && (yDelta1 > minY && yDelta2 < maxY) && (zDelta1 > minZ && zDelta2 < maxZ));

		return runTest;
	}

	bool testAreaInsideCuboid(ActiveArea* area) const {
		if (area == nullptr)
			return false;

		Vector3 centerPos = area->getAreaCenter();
		Vector3 cuboidDimensions = area->getCuboidDimensions();

		float length = cuboidDimensions[0];
		float width = cuboidDimensions[1];
		float height = cuboidDimensions[2];

#ifdef DEBUG_AA_OCTREE
		info(true) << "testAreaInsideCuboid -- called for " << area->getAreaName() << " Location: " << centerPos.toString() << " Length: " << length << " Width: " << width << " Height: " << height;
#endif

		float areaMinX, areaMinY, areaMinZ, areaMaxX, areaMaxY, areaMaxZ;

		areaMinX = centerPos.getX() - (width / 2);
		areaMaxX = centerPos.getX() + (width / 2);
		areaMinY = centerPos.getY() - (length / 2);
		areaMaxY = centerPos.getY() + (length / 2);
		areaMinZ = centerPos.getZ() - (height / 2);
		areaMaxZ = centerPos.getZ() + (height / 2);

		bool runTestX = (areaMinX >= minX && areaMaxX < maxX);
		bool runTestY = (areaMinY >= minY && areaMaxY < maxY);
		bool runTestZ = (areaMinZ >= minZ && areaMaxZ < maxZ);

		return runTestX && runTestY && runTestZ;
	}

	bool hasSubNodes() const {
		return nwNode != nullptr || neNode != nullptr || swNode != nullptr || seNode != nullptr || nwNode2 != nullptr || neNode2 != nullptr || swNode2 != nullptr || seNode2 != nullptr;
	}

	bool testInSWArea(float x, float z, float y, float radius) const {
		float xDelta1 = x - radius;
		float xDelta2 = x + radius;
		float yDelta1 = y - radius;
		float yDelta2 = y + radius;
		float zDelta1 = z - radius;
		float zDelta2 = z + radius;

#ifdef DEBUG_AA_OCTREE
		info(true) << "testInSWArea --- Radius: " << radius << " xDelta1 = " << xDelta1 << " xDelta2 = " << xDelta2 << " yDelta1 = " << yDelta1 << " yDelta2 = " << yDelta2 <<
		" zDelta1 = " << zDelta1 << " zDelta2 = " << zDelta2;
		info(true) << "minX = " << minX << " dividerX = " << dividerX << " minZ = " << minZ << " dividerZ = " << dividerZ << " minY = " << minY << " dividerY = " << dividerY;
#endif

		return (xDelta1 > minX && xDelta2 < dividerX) && (yDelta1 > minY && yDelta2 < dividerY) && (zDelta1 > minZ && zDelta2 < dividerZ);
	}

	bool testInSEArea(float x, float z, float y, float radius) const {
		float xDelta1 = x - radius;
		float xDelta2 = x + radius;
		float yDelta1 = y - radius;
		float yDelta2 = y + radius;
		float zDelta1 = z - radius;
		float zDelta2 = z + radius;

#ifdef DEBUG_AA_OCTREE
		info(true) << "testInSEArea --- Radius: " << radius << " xDelta1 = " << xDelta1 << " xDelta2 = " << xDelta2 << " yDelta1 = " << yDelta1 << " yDelta2 = " << yDelta2 <<
		" zDelta1 = " << zDelta1 << " zDelta2 = " << zDelta2;
		info(true) << "dividerX = " << dividerX << " maxX = " << maxX << " minZ = " << minZ << " dividerZ = " << dividerZ << " minY = " << minY << " dividerY = " << dividerY;
#endif

		return (xDelta1 > dividerX && xDelta2 < maxX) && (yDelta1 > minY && yDelta2 < dividerY) && (zDelta1 > minZ && zDelta2 < dividerZ);
	}

	bool testInNWArea(float x, float z, float y, float radius) const {
		float xDelta1 = x - radius;
		float xDelta2 = x + radius;
		float yDelta1 = y - radius;
		float yDelta2 = y + radius;
		float zDelta1 = z - radius;
		float zDelta2 = z + radius;

#ifdef DEBUG_AA_OCTREE
		info(true) << "testInNWArea --- Radius: " << radius << " xDelta1 = " << xDelta1 << " xDelta2 = " << xDelta2 << " yDelta1 = " << yDelta1 << " yDelta2 = " << yDelta2 <<
		" zDelta1 = " << zDelta1 << " zDelta2 = " << zDelta2;
		info(true) << "minX = " << minX << " dividerX = " << dividerX << " minZ = " << minZ << " dividerZ = " << dividerZ << " dividerY = " << dividerY << " maxY = " << maxY;
#endif

		return (xDelta1 > minX && xDelta2 < dividerX) && (yDelta1 > dividerY && yDelta2 < maxY) && (zDelta1 > minZ && zDelta2 < dividerZ);
	}

	bool testInNEArea(float x, float z, float y, float radius) const {
		float xDelta1 = x - radius;
		float xDelta2 = x + radius;
		float yDelta1 = y - radius;
		float yDelta2 = y + radius;
		float zDelta1 = z - radius;
		float zDelta2 = z + radius;

#ifdef DEBUG_AA_OCTREE
		info(true) << "testInNEArea --- Radius: " << radius << " xDelta1 = " << xDelta1 << " xDelta2 = " << xDelta2 << " yDelta1 = " << yDelta1 << " yDelta2 = " << yDelta2 <<
		" zDelta1 = " << zDelta1 << " zDelta2 = " << zDelta2;
		info(true) << "minX = " << minX << " dividerX = " << dividerX << " minZ = " << minZ << " dividerZ = " << dividerZ << " dividerY = " << dividerY << " maxY = " << maxY;
#endif

		return (xDelta1 > dividerX && xDelta2 < maxX) && (yDelta1 > dividerY && yDelta2 < maxY) && (zDelta1 > minZ && zDelta2 < dividerZ);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool testInSWArea2(float x, float z, float y, float radius) const {
		float xDelta1 = x - radius;
		float xDelta2 = x + radius;
		float yDelta1 = y - radius;
		float yDelta2 = y + radius;
		float zDelta1 = z - radius;
		float zDelta2 = z + radius;

#ifdef DEBUG_AA_OCTREE
		info(true) << "testInSWArea2 --- Radius: " << radius << " xDelta1 = " << xDelta1 << " xDelta2 = " << xDelta2 << " yDelta1 = " << yDelta1 << " yDelta2 = " << yDelta2 <<
		" zDelta1 = " << zDelta1 << " zDelta2 = " << zDelta2;
		info(true) << "minX = " << minX << " dividerX = " << dividerX << " dividerZ = " << dividerZ << " maxZ = " << maxZ << " minY = " << minY << " dividerY = " << dividerY;
#endif

		return (xDelta1 > minX && xDelta2 < dividerX) && (yDelta1 > minY && yDelta2 < dividerY) && (zDelta1 > dividerZ && zDelta2 < maxZ);
	}

	bool testInSEArea2(float x, float z, float y, float radius) const {
		float xDelta1 = x - radius;
		float xDelta2 = x + radius;
		float yDelta1 = y - radius;
		float yDelta2 = y + radius;
		float zDelta1 = z - radius;
		float zDelta2 = z + radius;

#ifdef DEBUG_AA_OCTREE
		info(true) << "testInSEArea2 --- Radius: " << radius << " xDelta1 = " << xDelta1 << " xDelta2 = " << xDelta2 << " yDelta1 = " << yDelta1 << " yDelta2 = " << yDelta2 <<
		" zDelta1 = " << zDelta1 << " zDelta2 = " << zDelta2;
		info(true) << "dividerX = " << dividerX << " maxX = " << maxX << " minZ = " << minZ << " maxZ = " << maxZ << " minY = " << minY << " maxY = " << maxY;
#endif

		return (xDelta1 > dividerX && xDelta2 < maxX) && (yDelta1 > minY && yDelta2 < dividerY) && (zDelta1 > dividerZ && zDelta2 < maxZ);
	}

	bool testInNWArea2(float x, float z, float y, float radius) const {
		float xDelta1 = x - radius;
		float xDelta2 = x + radius;
		float yDelta1 = y - radius;
		float yDelta2 = y + radius;
		float zDelta1 = z - radius;
		float zDelta2 = z + radius;

#ifdef DEBUG_AA_OCTREE
		info(true) << "testInNWArea2 --- Radius: " << radius << " xDelta1 = " << xDelta1 << " xDelta2 = " << xDelta2 << " yDelta1 = " << yDelta1 << " yDelta2 = " << yDelta2 <<
		" zDelta1 = " << zDelta1 << " zDelta2 = " << zDelta2;
		info(true) << "minX = " << minX << " dividerX = " << dividerX << " dividerZ = " << dividerZ << " maxZ = " << maxZ << " dividerY = " << minY << " maxY = " << maxY;
#endif

		return (xDelta1 > minX && xDelta2 < dividerX) && (yDelta1 > dividerY && yDelta2 < maxY) && (zDelta1 > dividerZ && zDelta2 < maxZ);
	}

	bool testInNEArea2(float x, float z, float y, float radius) const {
		float xDelta1 = x - radius;
		float xDelta2 = x + radius;
		float yDelta1 = y - radius;
		float yDelta2 = y + radius;
		float zDelta1 = z - radius;
		float zDelta2 = z + radius;

#ifdef DEBUG_AA_OCTREE
		info(true) << "testInNEArea2 --- Radius: " << radius << " xDelta1 = " << xDelta1 << " xDelta2 = " << xDelta2 << " yDelta1 = " << yDelta1 << " yDelta2 = " << yDelta2 <<
		" zDelta1 = " << zDelta1 << " zDelta2 = " << zDelta2;
		info(true) << "dividerX = " << dividerX << " maxX = " << maxX << " dividerZ = " << dividerZ << " maxZ = " << maxZ << " dividerY = " << dividerY << " maxY = " << maxY;
#endif

		return (xDelta1 > dividerX && xDelta2 < maxX) && (yDelta1 > dividerY && yDelta2 < maxY) && (zDelta1 > dividerZ && zDelta2 < maxZ);
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
	ActiveAreaOctree(float minx, float minz, float miny, float maxx, float maxz, float maxy) {
#ifndef AREA_TREE_SIMPLE
		root = makeUnique<ActiveAreaOctreeNode>(minx, minz, miny, maxx, maxz, maxy, nullptr);
#else
		areas.setNoDuplicateInsertPlan();
#endif

		setLoggingName("ActiveAreaOctree");
	}

	template <typename AreaType>
	void getActiveAreas(float x, float z, float y, ArrayList<AreaType>& areas) const {
#ifndef AREA_TREE_SIMPLE
		getActiveAreas(root.get(), x, z, y, areas);
#else
		for (const auto& area : areas) {
			if (area->containsPoint(x, z, y)) {
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
	void getActiveAreas(ActiveAreaOctreeNode* node, float x, float z, float y, ArrayList<AreaType>& areas) const {
		if (node == nullptr) {
			return;
		}

#ifdef DEBUG_AA_OCTREE
		info(true) << "getActiveAreas - Loc: X = " << x << ", Z = " << z << ", Y = " << y << " Area Size: " << node->areas.size();
#endif

		for (const auto& areaEntry : node->areas) {
			if (areaEntry->containsPoint(x, z, y)) {
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

		if (nodeSW != nullptr && nodeSW->testInside(x, z, y)) {
			getActiveAreas(nodeSW.get(), x, z, y, areas);
		} else if (nodeSE != nullptr && nodeSE->testInside(x, z, y)) {
			getActiveAreas(nodeSE.get(), x, z, y, areas);
		} else if (nodeNW != nullptr && nodeNW->testInside(x, z, y)) {
			getActiveAreas(nodeNW.get(), x, z, y, areas);
		} else if (nodeNE != nullptr && nodeNE->testInside(x, z, y)) {
			getActiveAreas(nodeNE.get(), x, z, y, areas);
		} else if (nodeSW2 != nullptr && nodeSW2->testInside(x, z, y)) {
			getActiveAreas(nodeSW2.get(), x, z, y, areas);
		} else if (nodeSE2 != nullptr && nodeSE2->testInside(x, z, y)) {
			getActiveAreas(nodeSE2.get(), x, z, y, areas);
		} else if (nodeNW2 != nullptr && nodeNW2->testInside(x, z, y)) {
			getActiveAreas(nodeNW2.get(), x, z, y, areas);
		} else if (nodeNE2 != nullptr && nodeNE2->testInside(x, z, y)) {
			getActiveAreas(nodeNE2.get(), x, z, y, areas);
		}
	}
#endif
};

} // namespace zone
} // namespace server
