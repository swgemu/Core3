/*
 Copyright (C) 2007 <SWGEmu>. All rights reserved.
 Distribution of this file for usage outside of Core3 is prohibited.
 */

#ifndef ZONEQUADTREENODE_H_
#define ZONEQUADTREENODE_H_

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
class QuadTreeEntry;

class QuadTreeNode: public Object {
	SortedVector<Reference<QuadTreeEntry*> > objects;

	WeakReference<QuadTreeNode*> parentNode;
	Reference<QuadTreeNode*> nwNode;
	Reference<QuadTreeNode*> neNode;
	Reference<QuadTreeNode*> swNode;
	Reference<QuadTreeNode*> seNode;

	float minX, minY;
	float maxX, maxY;

	float dividerX, dividerY;

public:
	QuadTreeNode();
	QuadTreeNode(float minx, float miny, float maxx, float maxy,
			QuadTreeNode *parent);

	~QuadTreeNode();

	Object* clone() {
		return ObjectCloner<QuadTreeNode>::clone(this);
	}

	Object* clone(void* object) {
		return TransactionalObjectCloner<QuadTreeNode>::clone(this);
	}

	void free() {
		TransactionalMemoryManager::instance()->destroy(this);
	}

	// Add a object to this node
	void addObject(QuadTreeEntry *obj);

	QuadTreeEntry* getObject(int index) {
		return objects.get(index);
	}

	// Remove a object by GUID
	void removeObject(QuadTreeEntry *obj);

	void removeObject(int index);

	// Approximative test if a circle with center in x,y and
	// given radius crosses this node.
	bool testInRange(float x, float y, float range) const;

	// Check if this node makes any sense to exist
	void check();

	bool validateNode() const {
		if (minX > maxX || minY > maxY/* || objects.size() > 1000*/)
			return false;
		else
			return true;
	}

	// Check if this node has any associated objects
	inline bool isEmpty() const {
		return objects.isEmpty();
	}

	// Check if this node has children nodes
	inline bool hasSubNodes() const {
		return nwNode != NULL || neNode != NULL || swNode != NULL || seNode
				!= NULL;
	}

	// Test if the point is inside this node
	inline bool testInside(float x, float y) const {
		return x >= minX && x < maxX && y >= minY && y < maxY;
	}

	// Test if the object is inside this node
	bool testInside(QuadTreeEntry* obj) const;

	String toStringData();

	friend class server::zone::QuadTree;
	friend class server::zone::QuadTreeEntryImplementation;
};

} // namespace server
} // namespace zone


#endif /*QUADTREENODE_H_*/
