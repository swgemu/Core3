/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
 */

/*
   Quad tree implementation
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

#include <math.h>

#include "server/zone/TreeEntry.h"
#include "engine/log/Logger.h"

#include "QuadTree.h"

#define NO_ENTRY_REF_COUNTING

using namespace server::zone;

bool QuadTree::logTree = false;

//#define OUTPUTQTERRORS

QuadTree::QuadTree() {
	root = nullptr;
}

QuadTree::QuadTree(float minx, float miny, float maxx, float maxy) {
	root = new TreeNode(minx, miny, maxx, maxy, nullptr);
}

QuadTree::~QuadTree() {
	//delete root;

	root = nullptr;
}

Object* QuadTree::clone() {
	return ObjectCloner<QuadTree>::clone(this);
}

Object* QuadTree::clone(void* mem) {
	return TransactionalObjectCloner<QuadTree>::clone(this);
}

void QuadTree::setSize(float minx, float miny, float maxx, float maxy) {
	//delete root;

	root = new TreeNode(minx, miny, maxx, maxy, nullptr);
}

void QuadTree::insert(TreeEntry *obj) {
	/*if (!isLocked()) {
		Logger::console.info(true) << "inserting to unlocked quad tree\n";
		StackTrace::printStackTrace();
		raise(SIGSEGV);
	}*/

	E3_ASSERT(obj->getParent() == nullptr);

	Locker locker(&mutex);

	try {
		if (QuadTree::doLog()) {
			Logger::console.info(true) << "QuadTree - Object: " << obj->getObjectID() << " - inserting" << "(" << obj->getPositionX() << ", " << obj->getPositionY() << ")";
		}

		if (obj->getNode() != nullptr)
			remove(obj);

		_insert(root, obj);

		if (QuadTree::doLog())
			Logger::console.info(true) << "QuadTree - Object: " << obj->getObjectID() <<  " - finished inserting\n";
	} catch (Exception& e) {
		Logger::console.info(true) << "[QuadTree] error - " << e.getMessage() << "\n";
		e.printStackTrace();
	}
}

bool QuadTree::update(TreeEntry *obj) {
	//assert(obj->getParent() == nullptr);

	Locker locker(&mutex);

	try {
		auto node = obj->getNode();

		if (node == nullptr) {
#ifdef OUTPUTQTERRORS
			Logger::console.error("QuadTree::update -- node is a nullptr!");
#endif
			return false;
		}

		if (QuadTree::doLog()) {
			Logger::console.info(true) << hex << "object [" << obj->getObjectID() <<  "] updating on node " << node->toStringData() << " \n" << "(" << obj->getPositionX()
				<< ", " << obj->getPositionY() << ")\n";
		}

		bool res = _update(node, obj);

		if (QuadTree::doLog())
			Logger::console.info(true) << hex << "object [" << obj->getObjectID() <<  "] finished updating\n";

		return res;
	} catch (Exception& e) {
		Logger::console.info(true) << "[QuadTree] error - " << e.getMessage() << "\n";
		e.printStackTrace();

		return false;
	}
}

void QuadTree::inRange(TreeEntry *obj, float range) {
	/*if (!isLocked()) {
		Logger::console.info(true) << "inRange unlocked quad tree\n";
		StackTrace::printStackTrace();
		raise(SIGSEGV);
	}*/

	//assert(obj->getParent() == nullptr);

	ReadLocker locker(&mutex);

	CloseObjectsVector* closeObjects = obj->getCloseObjects();

	float rangesq = range * range;

	float x = obj->getPositionX();
	float y = obj->getPositionY();

	float oldx = obj->getPreviousPositionX();
	float oldy = obj->getPreviousPositionY();

	try {
		if (closeObjects != nullptr) {
			for (int i = 0; i < closeObjects->size(); i++) {
				TreeEntry* o = closeObjects->get(i);
				ManagedReference<TreeEntry*> objectToRemove = o;
				ManagedReference<TreeEntry*> rootParent = o->getRootParent();

				if (rootParent != nullptr)
					o = rootParent;

				if (o != obj) {
					float deltaX = x - o->getPositionX();
					float deltaY = y - o->getPositionY();

					if (deltaX * deltaX + deltaY * deltaY > rangesq) {
						float oldDeltaX = oldx - o->getPositionX();
						float oldDeltaY = oldy - o->getPositionY();

						if (oldDeltaX * oldDeltaX + oldDeltaY * oldDeltaY <= rangesq) {
							obj->removeInRangeObject(objectToRemove);

							CloseObjectsVector* objCloseObjects = objectToRemove->getCloseObjects();

							if (objCloseObjects != nullptr)
								objectToRemove->removeInRangeObject(obj);
						}
					}
				}
			}
		}


		//	try {
			_inRange(root, obj, range);

			if (QuadTree::doLog()) {
				Logger::console.info(true) << hex << "object [" << obj->getObjectID() <<  "] in range (";

				/*for (int i = 0; i < obj->inRangeObjectCount(); ++i) {
				Logger::console.info(true) << hex << obj->getInRangeObject(i)->getObjectID() << ", ";
			}*/

				Logger::console.info(true) << "\n";
			}

	} catch (Exception& e) {
		Logger::console.info(true) << "[QuadTree] " << e.getMessage() << "\n";
		e.printStackTrace();
	}
}

int QuadTree::inRange(float x, float y, float range, SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, range, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[QuadTree] " << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}

int QuadTree::inRange(float x, float y, float range, SortedVector<TreeEntry*>& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, range, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[QuadTree] " << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}

void QuadTree::remove(TreeEntry *obj) {
	/*if (!isLocked()) {
		Logger::console.info(true) << "remove on unlocked quad tree\n";
		StackTrace::printStackTrace();
		raise(SIGSEGV);
	}*/

	Locker locker(&mutex);

	if (QuadTree::doLog())
		Logger::console.info(true) << hex << "object [" << obj->getObjectID() <<  "] removing\n";

	auto node = obj->getNode();

	if (node != nullptr) {
		if (!node->validateNode()) {
			Logger::console.info(true) << "[QuadTree] " << obj->getObjectID() << " error on remove() - invalid Node"
					<< node->toStringData() << "\n";
		}

		node->removeObject(obj);

		node->check();
		obj->setNode(nullptr);
	} else {
		Logger::console.info(true) << hex << "object [" << obj->getObjectID() <<  "] ERROR - removing the node\n";
		StackTrace::printStackTrace();
	}

	if (QuadTree::doLog())
		Logger::console.info(true) << hex << "object [" << obj->getObjectID() <<  "] finished removing\n";
}

void QuadTree::removeAll() {
	Locker locker(&mutex);

	if (root != nullptr) {
		root = nullptr;
		//delete root;
	}
}

/*
 * Every Node can have data and children. Every data must be completely
 * contained inside the Node, so boundary sphere is checked.
 */
void QuadTree::_insert(const Reference<TreeNode*>& node, TreeEntry *obj) {
	/*
	 * Logic:
	 *
	 * 1) We have Objects in this Node. The Node has no children.
	 *    - Squaring was not yet needed, so we do it now and move
	 *      all the objects down into the squares that arent locked.
	 *
	 * 2) We have Objects in this Node. The Node has children.
	 *    - All those objects must be locked, else they would have been
	 *    moved down on squaring. So we dont worry about moving them.
	 *
	 * 3) The Node is empty. We add the object.
	 */

	// Initially assume the object is not crossing any boundaries
	obj->clearBounding();

	if (!node->isEmpty() && !node->hasSubNodes()) {
		/*
		 * We want to Insert another object, so we square this Node up and move
		 * all the Objects that arent locked (cause they cross a boundary) down.
		 */
		if ((node->maxX - node->minX <= 8) && (node->maxY - node->minY <= 8)) {
			/*
			 * This protects from killing the stack. If something is messed up it may
			 * blow the stack because the recursion runs forever. Stop squaring when
			 * it doesnt make sense anymore. If the two objects have the same coordinate
			 * we add the new one to the map. The search is linear for objects inside
			 * .1 Unit. So what.
			 */
			node->addObject(obj);
			return;
		}

		/**
		 * Proceed objects in node in reverse direction since this
		 * makes handling deletions from the vector easier.
		 */
		for (int i = node->objects.size() - 1; i >= 0; i--) {
			TreeEntry* existing = node->getObject(i);

			// We remove the Object from the Node if its not locked
			// for crossing boundaries to add it to another Node
			if (existing->isBounding())
				continue;

			// Increment the refcount on the Object since if this is the
			// last reference ever, the object will be destroyed by Delete()
			//existing->IncRef ();
			node->removeObject(i);

			// First find out which square it needs, then Insert it into it
			// We divide the Node area into 4 squares, reusing existing children

			if (existing->isInSWArea(node)) {
				if (node->swNode == nullptr)
					node->swNode = new TreeNode(node->minX, node->minY, node->dividerX, node->dividerY, node);

				_insert(node->swNode, existing);
			} else if (existing->isInSEArea(node)) {
				if (node->seNode == nullptr)
					node->seNode = new TreeNode(node->dividerX, node->minY, node->maxX, node->dividerY, node);

				_insert(node->seNode, existing);
			} else if (existing->isInNWArea(node)) {
				if (node->nwNode == nullptr)
					node->nwNode = new TreeNode(node->minX, node->dividerY, node->dividerX, node->maxY, node);

				_insert(node->nwNode, existing);
			} else {
				if (node->neNode == nullptr)
					node->neNode = new TreeNode(node->dividerX, node->dividerY, node->maxX, node->maxY, node);

				_insert(node->neNode, existing);
			}

			// Okay, we don't need this reference anymore
			//existing->DecRef ();
		}
	}

	/*
	 * Maybe we squared, maybe we didnt. Anyway, this object extends beyond one
	 * of the boundaries, so we cannot put it into a lower node. It will be
	 * placed in this one regardless and locked.
	 */

	if (obj->isInArea(node)) {
		obj->setBounding();
		node->addObject(obj);

		return;
	}

	/*
	 * The Node has been squared because there was already an object inside.
	 * Also, the new object is contained in one of those new squares.
	 * So we search for the right one and insert the object there.
	 */
	if (node->hasSubNodes()) {
		if (obj->isInSWArea(node)) {
			if (node->swNode == nullptr)
				node->swNode = new TreeNode(node->minX, node->minY, node->dividerX, node->dividerY, node);

			_insert(node->swNode, obj);
		} else if (obj->isInSEArea(node)) {
			if (node->seNode == nullptr)
				node->seNode = new TreeNode(node->dividerX, node->minY, node->maxX, node->dividerY, node);

			_insert(node->seNode, obj);
		} else if (obj->isInNWArea(node)) {
			if (node->nwNode == nullptr)
				node->nwNode = new TreeNode(node->minX, node->dividerY, node->dividerX, node->maxY, node);

			_insert(node->nwNode, obj);
		} else {
			if (node->neNode == nullptr)
				node->neNode = new TreeNode(node->dividerX, node->dividerY, node->maxX, node->maxY, node);

			_insert(node->neNode, obj);
		}

		return;
	}

	// Node is not squared, and we have only one data entry, so it can stay
	// this way. Data can be Inserted, and the recursion is over.
	node->addObject(obj);
}

/* The difference to the Insert is that it starts at the current node
 * and tries to find the right place to be now that the position changed.
 */
bool QuadTree::_update(const Reference<TreeNode*>& node, TreeEntry *obj) {
	// Whew, still in the same square. Lucky bastards we are.

	if (node->testInsideQuadTree(obj)) {
		return true;
	}

	// Since we'll have to temporarily remove the object from the Quad Tree,
	// make sure it won't be deleted as we do that
	//data->IncRef ();

	// Go upwards til the object is inside the square.
	Reference<TreeNode*> cur = node->parentNode.get();
	while (cur != nullptr && !cur->testInsideQuadTree(obj))
		cur = cur->parentNode.get();

	remove(obj);

	// Here is the right spot for the object, so lets drop it in.
	// May result in another squaring frenzy.
	if (cur != nullptr) {
		_insert(cur, obj);
	}
#ifdef OUTPUTQTERRORS
	else
		Logger::console.info(true) << "[QuadTree] error on update() - invalid Node\n";
#endif

	// We don't need the reference anymore. If the object goes out of the
	// quadtree and there aren't any references left... well... goodbye
	//data->DecRef ();
	return cur != nullptr;
}

void QuadTree::safeInRange(TreeEntry* obj, float range) {
	CloseObjectsVector* closeObjectsVector = obj->getCloseObjects();

#ifdef NO_ENTRY_REF_COUNTING
	SortedVector<TreeEntry*> closeObjectsCopy;
#else
	SortedVector<ManagedReference<TreeEntry*> > closeObjectsCopy;
#endif

	Locker objLocker(obj);

	if (closeObjectsVector != nullptr) {
		closeObjectsCopy.removeAll(closeObjectsVector->size(), 50);
		closeObjectsVector->safeCopyTo(closeObjectsCopy);
	}

	float rangesq = range * range;

	float x = obj->getPositionX();
	float y = obj->getPositionY();

#ifdef NO_ENTRY_REF_COUNTING
	SortedVector<TreeEntry*> inRangeObjects(500, 250);
#else
	SortedVector<ManagedReference<TreeEntry*> > inRangeObjects(500, 250);
#endif

	ReadLocker locker(&mutex);

	copyObjects(root, x, y, Math::min(range * 2.0f, 768.0f), inRangeObjects);

	locker.release();

	for (int i = 0; i < inRangeObjects.size(); ++i) {
		TreeEntry *o = inRangeObjects.getUnsafe(i);

		if (o != obj) {
			float deltaX = x - o->getPositionX();
			float deltaY = y - o->getPositionY();

			try {
				float outOfRangeSqr = Math::sqr(Math::max(range, o->getOutOfRangeDistance()));

				if (deltaX * deltaX + deltaY * deltaY <= outOfRangeSqr) {
					CloseObjectsVector* objCloseObjects = obj->getCloseObjects();

					if (objCloseObjects != nullptr)
						obj->addInRangeObject(o, false);

					CloseObjectsVector* oCloseObjects = o->getCloseObjects();

					if (oCloseObjects != nullptr)
						o->addInRangeObject(obj);
				}
			} catch (...) {
				Logger::console.info(true) << "unreported exception caught in safeInRange()\n";
			}
		} else {
			if (obj->getCloseObjects() != nullptr)
				obj->addInRangeObject(obj, false);
		}
	}


}

void QuadTree::copyObjects(const Reference<TreeNode*>& node, float x, float y, float range, SortedVector<ManagedReference<server::zone::TreeEntry*> >& objects) {
	//	ReadLocker locker(&mutex);

	//objects.addAll(node->objects);
	for (int i = 0; i < node->objects.size(); ++i) {
		objects.add(node->objects.getUnsafe(i).get());
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInRange(x, y, range))
			copyObjects(node->nwNode, x, y, range, objects);
		if (node->neNode != nullptr && node->neNode->testInRange(x, y, range))
			copyObjects(node->neNode, x, y, range, objects);
		if (node->swNode != nullptr && node->swNode->testInRange(x, y, range))
			copyObjects(node->swNode, x, y, range, objects);
		if (node->seNode != nullptr && node->seNode->testInRange(x, y, range))
			copyObjects(node->seNode, x, y, range, objects);
	}
}

void QuadTree::copyObjects(const Reference<TreeNode*>& node, float x, float y, float range, SortedVector<server::zone::TreeEntry*>& objects) {
	//	ReadLocker locker(&mutex);

	//objects.addAll(node->objects);

	for (int i = 0; i < node->objects.size(); ++i) {
		objects.add(node->objects.getUnsafe(i).get());
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInRange(x, y, range))
			copyObjects(node->nwNode, x, y, range, objects);
		if (node->neNode != nullptr && node->neNode->testInRange(x, y, range))
			copyObjects(node->neNode, x, y, range, objects);
		if (node->swNode != nullptr && node->swNode->testInRange(x, y, range))
			copyObjects(node->swNode, x, y, range, objects);
		if (node->seNode != nullptr && node->seNode->testInRange(x, y, range))
			copyObjects(node->seNode, x, y, range, objects);
	}
}

void QuadTree::_inRange(const Reference<TreeNode*>& node, TreeEntry *obj, float range) {
	Reference<TreeNode*> refNode = node;

	float rangesq = range * range;

	float x = obj->getPositionX();
	float y = obj->getPositionY();

	float oldx = obj->getPreviousPositionX();
	float oldy = obj->getPreviousPositionY();

	for (int i = 0; i < refNode->objects.size(); i++) {
		TreeEntry *o = refNode->objects.get(i);

		if (o != obj) {
			float deltaX = x - o->getPositionX();
			float deltaY = y - o->getPositionY();

			if (deltaX * deltaX + deltaY * deltaY <= rangesq) {
				CloseObjectsVector* objCloseObjects = obj->getCloseObjects();
				if (objCloseObjects != nullptr && !objCloseObjects->contains(o)) {
					obj->addInRangeObject(o, false);
					//obj->notifyInsert(o);
				}

				CloseObjectsVector* oCloseObjects = o->getCloseObjects();

				if (oCloseObjects != nullptr && !oCloseObjects->contains(obj)) {
					o->addInRangeObject(obj);
					//o->notifyInsert(obj);
				} else
					o->notifyPositionUpdate(obj);

				/*obj->addInRangeObject(o, false);
				o->addInRangeObject(obj);*/
			} else {
				float oldDeltaX = oldx - o->getPositionX();
				float oldDeltaY = oldy - o->getPositionY();

				if (oldDeltaX * oldDeltaX + oldDeltaY * oldDeltaY <= rangesq) {

					CloseObjectsVector* objCloseObjects = obj->getCloseObjects();
					if (objCloseObjects != nullptr)
						obj->removeInRangeObject(o);


					CloseObjectsVector* oCloseObjects = o->getCloseObjects();

					if (oCloseObjects != nullptr)
						o->removeInRangeObject(obj);
				}
			}
		} else {
			if (obj->getCloseObjects() != nullptr)
				obj->addInRangeObject(obj, false);
		}
	}

	if (refNode->hasSubNodes()) {
		if (refNode->nwNode != nullptr && refNode->nwNode->testInRange(x, y, range))
			_inRange(refNode->nwNode, obj, range);
		if (refNode->neNode != nullptr && refNode->neNode->testInRange(x, y, range))
			_inRange(refNode->neNode, obj, range);
		if (refNode->swNode != nullptr && refNode->swNode->testInRange(x, y, range))
			_inRange(refNode->swNode, obj, range);
		if (refNode->seNode != nullptr && refNode->seNode->testInRange(x, y, range))
			_inRange(refNode->seNode, obj, range);
	}
}

int QuadTree::inRange(float x, float y, SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[QuadTree] " << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}

int QuadTree::inRange(float x, float y, SortedVector<TreeEntry*>& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[QuadTree] " << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}

int QuadTree::_inRange(const Reference<TreeNode*>& node, float x, float y,
		SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	int count = 0;

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry *o = node->objects.get(i);

		if (o->containsPoint(x, y)) {
			++count;
			objects.put(o);
		}
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInside(x, y))
			count += _inRange(node->nwNode, x, y, objects);
		if (node->neNode != nullptr && node->neNode->testInside(x, y))
			count += _inRange(node->neNode, x, y, objects);
		if (node->swNode != nullptr && node->swNode->testInside(x, y))
			count += _inRange(node->swNode, x, y, objects);
		if (node->seNode != nullptr && node->seNode->testInside(x, y))
			count += _inRange(node->seNode, x, y, objects);
	}

	return count;
}

int QuadTree::_inRange(const Reference<TreeNode*>& node, float x, float y,
		SortedVector<TreeEntry* >& objects) const {
	int count = 0;

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry *o = node->objects.get(i);

		if (o->containsPoint(x, y)) {
			++count;
			objects.put(o);
		}
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInside(x, y))
			count += _inRange(node->nwNode, x, y, objects);
		if (node->neNode != nullptr && node->neNode->testInside(x, y))
			count += _inRange(node->neNode, x, y, objects);
		if (node->swNode != nullptr && node->swNode->testInside(x, y))
			count += _inRange(node->swNode, x, y, objects);
		if (node->seNode != nullptr && node->seNode->testInside(x, y))
			count += _inRange(node->seNode, x, y, objects);
	}

	return count;
}

int QuadTree::_inRange(const Reference<TreeNode*>& node, float x, float y, float range,
		SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	int count = 0;

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry *o = node->objects.get(i);

		if (o->isInRange(x, y, range)) {
			++count;
			objects.put(o);
		}
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInRange(x, y, range))
			count += _inRange(node->nwNode, x, y, range, objects);
		if (node->neNode != nullptr && node->neNode->testInRange(x, y, range))
			count += _inRange(node->neNode, x, y, range, objects);
		if (node->swNode != nullptr && node->swNode->testInRange(x, y, range))
			count += _inRange(node->swNode, x, y, range, objects);
		if (node->seNode != nullptr && node->seNode->testInRange(x, y, range))
			count += _inRange(node->seNode, x, y, range, objects);
	}

	return count;
}

int QuadTree::_inRange(const Reference<TreeNode*>& node, float x, float y, float range, SortedVector<TreeEntry* >& objects) const {
	int count = 0;

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry *o = node->objects.getUnsafe(i);

		if (o->isInRange(x, y, range)) {
			++count;
			objects.put(o);
		}
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInRange(x, y, range))
			count += _inRange(node->nwNode, x, y, range, objects);
		if (node->neNode != nullptr && node->neNode->testInRange(x, y, range))
			count += _inRange(node->neNode, x, y, range, objects);
		if (node->swNode != nullptr && node->swNode->testInRange(x, y, range))
			count += _inRange(node->swNode, x, y, range, objects);
		if (node->seNode != nullptr && node->seNode->testInRange(x, y, range))
			count += _inRange(node->seNode, x, y, range, objects);
	}

	return count;
}
