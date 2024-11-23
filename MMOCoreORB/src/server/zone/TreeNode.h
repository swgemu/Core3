/*
 Copyright (C) 2007 <SWGEmu>. All rights reserved.
 Distribution of this file for usage outside of Core3 is prohibited.
 */

#ifndef ZONETREENODE_H_
#define ZONETREENODE_H_

/*
 Quad tree interface
 Copyright (C) 2003 by The Arianne Team
 Copyright (C) 2005 Team OpenWoW
 Copyright (C) 2006 Team SWGEmu

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "system/lang.h"

//#ifdef WITH_STM
#include "engine/stm/TransactionalReference.h"
#include "engine/stm/TransactionalMemoryManager.h"
//#endif

/**
 * A quad tree is a 2D data structure that keeps lots of objects nicely
 * sorted in a tree with four children in every node, so that queries like
 * "give me a list of objects that are near the point X,Y" works lighting
 * fast.
 */

namespace server {
namespace zone {

class QuadTree;
class Octree;
class TreeEntry;
class TreeEntryImplementation;

class TreeNode: public Object {
	static const uint8 QUADTREE_NODE = 0;
	static const uint8 OCTREE_NODE = 1;

	SortedVector<Reference<TreeEntry*> > objects;

	WeakReference<TreeNode*> parentNode;
	Reference<TreeNode*> nwNode;
	Reference<TreeNode*> neNode;
	Reference<TreeNode*> swNode;
	Reference<TreeNode*> seNode;
	Reference<TreeNode*> nwNode2;
	Reference<TreeNode*> neNode2;
	Reference<TreeNode*> swNode2;
	Reference<TreeNode*> seNode2;

	float minX, minY, minZ;
	float maxX, maxY, maxZ;

	float dividerX, dividerY, dividerZ;

	String nodeName;

	uint8 nodeType;

public:
	TreeNode();
	TreeNode(float minx, float miny, float minz, float maxx, float maxy, float maxz, TreeNode *parent);
	TreeNode(float minx, float miny, float maxx, float maxy, TreeNode *parent);
	~TreeNode();

	Object* clone() {
		return ObjectCloner<TreeNode>::clone(this);
	}

	Object* clone(void* object) {
		return TransactionalObjectCloner<TreeNode>::clone(this);
	}

	void free() {
		TransactionalMemoryManager::instance()->destroy(this);
	}

	// Add a object to this node
	void addObject(TreeEntry *obj);

	TreeEntry* getObject(int index) {
		return objects.get(index);
	}

	// Remove a object by GUID
	void removeObject(TreeEntry *obj);

	void removeObject(int index);

	// Approximative test if a circle with center in x,y and
	// given radius crosses this node.
	bool testInRange(float x, float y, float z, float range) const;

	bool testInRange(float x, float y, float range) const;

	// Check if this node makes any sense to exist
	void check();

	bool validateNode() const {
		if (nodeType == OCTREE_NODE) {
			if (minX > maxX || minY > maxY || minZ > maxZ) {
				return false;
			}
		} else if (minX > maxX || minY > maxY) {
			return false;
		}

		return true;
	}

	// Check if this node has any associated objects
	inline bool isEmpty() const {
		return objects.isEmpty();
	}

	// Check if this node has children nodes
	inline bool hasSubNodes() const {
		return nwNode != nullptr || neNode != nullptr || swNode != nullptr || seNode != nullptr || nwNode2 != nullptr || neNode2 != nullptr || swNode2 != nullptr || seNode2 != nullptr;
	}

	// Test if the point is inside this node
	inline bool testInside(float x, float y, float z) const {
		// Logger::console.info(true) << "TreeNode - testInside --- Using X: " << x << " Z: " << z << " Y: " << y << " minX: " << minX << " maxX: " << maxX << " minZ: " << minZ << " maxZ: " << maxZ << " minY: " << minY << " maxY: " << maxY;

		return ((x > minX) && (x < maxX) && (y > minY) && (y < maxY) && (z > minZ) && (z < maxZ));
	}

	inline bool testInside(float x, float y) const {
		return ((x > minX) && (x < maxX) && (y > minY) && (y < maxY));
	}

	// Test if the object is inside this quad tree node
	bool testInsideQuadTree(TreeEntry* obj) const;

	// Test if the object is inside this oct tree node
	bool testInsideOctree(TreeEntry* obj) const;

	String toStringData();

	friend class server::zone::QuadTree;
	friend class server::zone::Octree;
	friend class server::zone::TreeEntryImplementation;
};

} // namespace server
} // namespace zone


#endif /*ZONETREENODE_H_*/
