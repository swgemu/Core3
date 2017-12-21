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

#include "server/zone/QuadTreeEntry.h"

#include "QuadTree.h"

#define NO_ENTRY_REF_COUNTING

using namespace server::zone;

QuadTreeNode::QuadTreeNode() {
	objects.setNoDuplicateInsertPlan();

//  smart pointer classes automatically initialize to nullptr
//	parentNode = nullptr;
//	nwNode = neNode = swNode = seNode = nullptr;

	minX = 0;
	minY = 0;
	maxX = 0;
	maxY = 0;

	dividerX = 0;
	dividerY = 0;
}

QuadTreeNode::QuadTreeNode(float minx, float miny, float maxx, float maxy, QuadTreeNode *parent) {
	objects.setNoDuplicateInsertPlan();

	parentNode = parent;
//	nwNode = neNode = swNode = seNode = nullptr;

	minX = minx;
	minY = miny;
	maxX = maxx;
	maxY = maxy;

	if (!validateNode() || minX > maxX || minY > maxY) {
		StringBuffer msg;
		msg << "[QuadTree] invalid node in create - " << toStringData();
		Logger::console.error(msg);
	}

	dividerX = (minX + maxX) / 2;
	dividerY = (minY + maxY) / 2;
}

QuadTreeNode::~QuadTreeNode() {
	/*if (nwNode != nullptr)
		delete nwNode;

	if (neNode != nullptr)
		delete neNode;

	if (swNode != nullptr)
 		delete swNode;

	if (seNode != nullptr)
		delete seNode;*/
}


void QuadTreeNode::addObject(QuadTreeEntry *obj) {
	if (QuadTree::doLog())
		System::out << hex << "object [" << obj->getObjectID() <<  "] added to QuadTree"
		<< toStringData() << "\n";

	if (!validateNode())
		System::out << "[QuadTree] invalid node in addObject() - " << toStringData() << "\n";

	objects.put(obj);
	obj->setNode(this);
}

void QuadTreeNode::removeObject(QuadTreeEntry *obj) {
	if (!objects.drop(obj)) {
		System::out << hex << "object [" << obj->getObjectID() <<  "] not found on QuadTree"
				<< toStringData() << "\n";
	} else {
		obj->setNode(nullptr);

		if (QuadTree::doLog())
			System::out <<  hex << "object [" << obj->getObjectID() <<  "] removed QuadTree"
			<< toStringData() << "\n";
	}
}

void QuadTreeNode::removeObject(int index) {
	QuadTreeEntry* obj = objects.remove(index);
	obj->setNode(nullptr);
}

bool QuadTreeNode::testInside(QuadTreeEntry* obj) const {
	float x = obj->getPositionX();
	float y = obj->getPositionY();

	return x >= minX && x < maxX && y >= minY && y < maxY;
}

bool QuadTreeNode::testInRange(float x, float y, float range) const {
	bool insideX = (minX <= x) && (x < maxX);
	bool insideY = (minY <= y) && (y < maxY);

	if (insideX && insideY)
		return true;

	bool closeenoughX = (fabs(minX - x) <= range || fabs(maxX - x) <= range);
	bool closeenoughY = (fabs(minY - y) <= range || fabs(maxY - y) <= range);

	if ((insideX || closeenoughX) && (insideY || closeenoughY))
		return true;
	else
		return false;
}

void QuadTreeNode::check () {
	Reference<QuadTreeNode*> parentNode = this->parentNode.get();

	if (isEmpty() && !hasSubNodes() && parentNode != nullptr) {
		if (parentNode->nwNode == this)
			parentNode->nwNode = nullptr;
		else if (parentNode->neNode == this)
			parentNode->neNode = nullptr;
		else if (parentNode->swNode == this)
			parentNode->swNode = nullptr;
		else if (parentNode->seNode == this)
			parentNode->seNode = nullptr;

		if (QuadTree::doLog())
			System::out << "deleteing node (" << this << ")\n";

		//delete this;
	}
}

String QuadTreeNode::toStringData() {
	StringBuffer s;
	s << "Node " << this << " (" << (int) minX << ","
			<< (int) minY << "," << (int) maxX << "," << (int) maxY
			<< ") [" << objects.size() << "]";

	return s.toString();
}

//---------------------------------------------------------------------------//

bool QuadTree::logTree = false;

QuadTree::QuadTree() {
	root = nullptr;
}

QuadTree::QuadTree(float minx, float miny, float maxx, float maxy) {
	root = new QuadTreeNode(minx, miny, maxx, maxy, nullptr);
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

	root = new QuadTreeNode(minx, miny, maxx, maxy, nullptr);
}

void QuadTree::insert(QuadTreeEntry *obj) {
	/*if (!isLocked()) {
		System::out << "inserting to unlocked quad tree\n";
		StackTrace::printStackTrace();
		raise(SIGSEGV);
	}*/

	assert(obj->getParent() == nullptr);

	Locker locker(&mutex);

	try {
		if (QuadTree::doLog()) {
			System::out << hex << "object [" << obj->getObjectID() <<  "] inserting\n";
			System::out << "(" << obj->getPositionX() << ", " << obj->getPositionY() << ")\n";
		}

		if (obj->getNode() != nullptr)
			remove(obj);

		_insert(root, obj);

		if (QuadTree::doLog())
			System::out << hex << "object [" << obj->getObjectID() <<  "] finished inserting\n";
	} catch (Exception& e) {
		System::out << "[QuadTree] error - " << e.getMessage() << "\n";
		e.printStackTrace();
	}
}

bool QuadTree::update(QuadTreeEntry *obj) {
	//assert(obj->getParent() == nullptr);

	Locker locker(&mutex);

	try {
		if (QuadTree::doLog()) {
			System::out << hex << "object [" << obj->getObjectID() <<  "] updating on node "
					<< obj->getNode()->toStringData() << " \n" << "(" << obj->getPositionX()
					<< ", " << obj->getPositionY() << ")\n";
		}

		if (obj->getNode() == nullptr) {
#ifdef OUTPUTQTERRORS
			System::out << hex << "object [" << obj->getObjectID() <<  "] updating error\n";
#endif
			return false;
		}

		Reference<QuadTreeNode*> node = obj->getNode();
		bool res = _update(node, obj);

		if (QuadTree::doLog())
			System::out << hex << "object [" << obj->getObjectID() <<  "] finished updating\n";

		return res;
	} catch (Exception& e) {
		System::out << "[QuadTree] error - " << e.getMessage() << "\n";
		e.printStackTrace();

		return false;
	}
}

void QuadTree::inRange(QuadTreeEntry *obj, float range) {
	/*if (!isLocked()) {
		System::out << "inRange unlocked quad tree\n";
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
				QuadTreeEntry* o = closeObjects->get(i);
				ManagedReference<QuadTreeEntry*> objectToRemove = o;
				ManagedReference<QuadTreeEntry*> rootParent = o->getRootParent();

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
				System::out << hex << "object [" << obj->getObjectID() <<  "] in range (";

				/*for (int i = 0; i < obj->inRangeObjectCount(); ++i) {
				System::out << hex << obj->getInRangeObject(i)->getObjectID() << ", ";
			}*/

				System::out << "\n";
			}

	} catch (Exception& e) {
		System::out << "[QuadTree] " << e.getMessage() << "\n";
		e.printStackTrace();
	}
}

int QuadTree::inRange(float x, float y, float range, SortedVector<ManagedReference<QuadTreeEntry*> >& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, range, objects);
	} catch (Exception& e) {
		System::out << "[QuadTree] " << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}

int QuadTree::inRange(float x, float y, float range,
		SortedVector<QuadTreeEntry*>& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, range, objects);
	} catch (Exception& e) {
		System::out << "[QuadTree] " << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}

void QuadTree::remove(QuadTreeEntry *obj) {
	/*if (!isLocked()) {
		System::out << "remove on unlocked quad tree\n";
		StackTrace::printStackTrace();
		raise(SIGSEGV);
	}*/

	Locker locker(&mutex);

	if (QuadTree::doLog())
		System::out << hex << "object [" << obj->getObjectID() <<  "] removing\n";

	Reference<QuadTreeNode*> node = obj->getNode();

	if (node != nullptr) {
		if (!node->validateNode()) {
			System::out << "[QuadTree] " << obj->getObjectID() << " error on remove() - invalid Node"
					<< node->toStringData() << "\n";
		}

		node->removeObject(obj);

		node->check();
		obj->setNode(nullptr);
	} else {
		System::out << hex << "object [" << obj->getObjectID() <<  "] ERROR - removing the node\n";
		StackTrace::printStackTrace();
	}

	if (QuadTree::doLog())
		System::out << hex << "object [" << obj->getObjectID() <<  "] finished removing\n";
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
void QuadTree::_insert(Reference<QuadTreeNode*>& node, QuadTreeEntry *obj) {
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
			QuadTreeEntry* existing = node->getObject(i);

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
					node->swNode = new QuadTreeNode(node->minX, node->minY, node->dividerX, node->dividerY, node);

				_insert(node->swNode, existing);
			} else if (existing->isInSEArea(node)) {
				if (node->seNode == nullptr)
					node->seNode = new QuadTreeNode(node->dividerX, node->minY, node->maxX, node->dividerY, node);

				_insert(node->seNode, existing);
			} else if (existing->isInNWArea(node)) {
				if (node->nwNode == nullptr)
					node->nwNode = new QuadTreeNode(node->minX, node->dividerY, node->dividerX, node->maxY, node);

				_insert(node->nwNode, existing);
			} else {
				if (node->neNode == nullptr)
					node->neNode = new QuadTreeNode(node->dividerX, node->dividerY, node->maxX, node->maxY, node);

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
				node->swNode = new QuadTreeNode(node->minX, node->minY, node->dividerX, node->dividerY, node);

			_insert(node->swNode, obj);
		} else if (obj->isInSEArea(node)) {
			if (node->seNode == nullptr)
				node->seNode = new QuadTreeNode(node->dividerX, node->minY, node->maxX, node->dividerY, node);

			_insert(node->seNode, obj);
		} else if (obj->isInNWArea(node)) {
			if (node->nwNode == nullptr)
				node->nwNode = new QuadTreeNode(node->minX, node->dividerY, node->dividerX, node->maxY, node);

			_insert(node->nwNode, obj);
		} else {
			if (node->neNode == nullptr)
				node->neNode = new QuadTreeNode(node->dividerX, node->dividerY, node->maxX, node->maxY, node);

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
bool QuadTree::_update(Reference<QuadTreeNode*>& node, QuadTreeEntry *obj) {
	// Whew, still in the same square. Lucky bastards we are.
	//System::out << "(" << obj->positionX << "," << obj->positionY << ")\n";

	if (node->testInside(obj))
		return true;

	// Since we'll have to temporarily remove the object from the Quad Tree,
	// make sure it won't be deleted as we do that
	//data->IncRef ();

	// Go upwards til the object is inside the square.
	Reference<QuadTreeNode*> cur = node->parentNode.get();
	while (cur != nullptr && !cur->testInside(obj))
		cur = cur->parentNode.get();

	remove(obj);

	// Here is the right spot for the object, so lets drop it in.
	// May result in another squaring frenzy.
	if (cur != nullptr) {
		Reference<QuadTreeNode*> c = cur;
		_insert(c, obj);
	}
#ifdef OUTPUTQTERRORS
	else
		System::out << "[QuadTree] error on update() - invalid Node\n";
#endif

	// We don't need the reference anymore. If the object goes out of the
	// quadtree and there aren't any references left... well... goodbye
	//data->DecRef ();
	return cur != nullptr;
}

void QuadTree::safeInRange(QuadTreeEntry* obj, float range) {
	CloseObjectsVector* closeObjectsVector = obj->getCloseObjects();

#ifdef NO_ENTRY_REF_COUNTING
	SortedVector<QuadTreeEntry*> closeObjectsCopy;
#else
	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjectsCopy;
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
	SortedVector<QuadTreeEntry*> inRangeObjects(500, 250);
#else
	SortedVector<ManagedReference<QuadTreeEntry*> > inRangeObjects(500, 250);
#endif

	ReadLocker locker(&mutex);

	copyObjects(root, x, y, range, inRangeObjects);

	locker.release();

	for (int i = 0; i < inRangeObjects.size(); ++i) {
		QuadTreeEntry *o = inRangeObjects.getUnsafe(i);

		if (o != obj) {
			float deltaX = x - o->getPositionX();
			float deltaY = y - o->getPositionY();

			try {
				if (deltaX * deltaX + deltaY * deltaY <= rangesq) {
					CloseObjectsVector* objCloseObjects = obj->getCloseObjects();

					if (objCloseObjects != nullptr)
						obj->addInRangeObject(o, false);

					CloseObjectsVector* oCloseObjects = o->getCloseObjects();

					if (oCloseObjects != nullptr)
						o->addInRangeObject(obj);
				}
			} catch (...) {
				System::out << "unreported exception caught in safeInRange()\n";
			}
		} else {
			if (obj->getCloseObjects() != nullptr)
				obj->addInRangeObject(obj, false);
		}
	}


}

void QuadTree::copyObjects(const Reference<QuadTreeNode*>& node, float x, float y, float range, SortedVector<ManagedReference<server::zone::QuadTreeEntry*> >& objects) {
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

void QuadTree::copyObjects(const Reference<QuadTreeNode*>& node, float x, float y, float range, SortedVector<server::zone::QuadTreeEntry*>& objects) {
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

void QuadTree::_inRange(Reference<QuadTreeNode*>& node, QuadTreeEntry *obj, float range) {
	Reference<QuadTreeNode*> refNode = node;

	float rangesq = range * range;

	float x = obj->getPositionX();
	float y = obj->getPositionY();

	float oldx = obj->getPreviousPositionX();
	float oldy = obj->getPreviousPositionY();

	for (int i = 0; i < refNode->objects.size(); i++) {
		QuadTreeEntry *o = refNode->objects.get(i);

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

int QuadTree::inRange(float x, float y, SortedVector<ManagedReference<QuadTreeEntry*> >& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, objects);
	} catch (Exception& e) {
		System::out << "[QuadTree] " << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}

int QuadTree::inRange(float x, float y, SortedVector<QuadTreeEntry*>& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, objects);
	} catch (Exception& e) {
		System::out << "[QuadTree] " << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}

int QuadTree::_inRange(const Reference<QuadTreeNode*>& node, float x, float y,
		SortedVector<ManagedReference<QuadTreeEntry*> >& objects) const {
	int count = 0;

	for (int i = 0; i < node->objects.size(); i++) {
		QuadTreeEntry *o = node->objects.get(i);

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

int QuadTree::_inRange(const Reference<QuadTreeNode*>& node, float x, float y,
		SortedVector<QuadTreeEntry* >& objects) const {
	int count = 0;

	for (int i = 0; i < node->objects.size(); i++) {
		QuadTreeEntry *o = node->objects.get(i);

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

int QuadTree::_inRange(const Reference<QuadTreeNode*>& node, float x, float y, float range,
		SortedVector<ManagedReference<QuadTreeEntry*> >& objects) const {
	int count = 0;

	for (int i = 0; i < node->objects.size(); i++) {
		QuadTreeEntry *o = node->objects.get(i);

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

int QuadTree::_inRange(const Reference<QuadTreeNode*>& node, float x, float y, float range,
		SortedVector<QuadTreeEntry* >& objects) const {
	int count = 0;

	for (int i = 0; i < node->objects.size(); i++) {
		QuadTreeEntry *o = node->objects.getUnsafe(i);

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
