/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
 */

#include <math.h>
#include "server/zone/TreeEntry.h"
#include "server/zone/CloseObjectsVector.h"
#include "server/zone/TreeNode.h"
#include "OctTree.h"
#include "server/zone/objects/scene/SceneObject.h"

#define NO_ENTRY_REF_COUNTING

using namespace server::zone;

bool OctTree::logTree = false;

//#define OUTPUT_OT_ERRORS

OctTree::OctTree() {
	root = nullptr;
}

OctTree::OctTree(float minx, float miny, float minz, float maxx, float maxy, float maxz) {
	root = new TreeNode(minx, miny, minz, maxx, maxy, maxz, nullptr);
}

OctTree::~OctTree() {
	root = nullptr;
}

Object* OctTree::clone() {
	return ObjectCloner<OctTree>::clone(this);
}

Object* OctTree::clone(void* mem) {
	return TransactionalObjectCloner<OctTree>::clone(this);
}

void OctTree::setSize(float minx, float miny, float minz, float maxx, float maxy, float maxz) {
	root = new TreeNode(minx, miny, minz, maxx, maxy, maxz, nullptr);
}

void OctTree::insert(TreeEntry *obj) {
	if (OctTree::doLog()) {
		Logger::console.info("OctTee::insert", true);
	}

	if (obj->getParent() != nullptr) {
		auto  scno = cast<SceneObject*>(obj);
		auto objParent = obj->getParent().get().castTo<SceneObject*>();

		Logger::console.info(true) << "Object Inserted to Octree still has a parent Object: " << scno->getDisplayedName() << " ID: " << scno->getObjectID() << " Parent: " << objParent->getDisplayedName() << " ID: " << objParent->getObjectID();

		E3_ASSERT(obj->getParent() == nullptr);
	}

	Locker locker(&mutex);

	try {
		if (OctTree::doLog()) { //--------------------------------------- HERE
			SceneObject* scno = cast<SceneObject*>(obj);
			Logger::console.info(true) << "OctTree - Object ID " << scno->getObjectID() << " " << scno->getDisplayedName() <<  " inserting at: (" << obj->getPositionX() << ", " << obj->getPositionZ() << ", " << obj->getPositionY() << ")";
		}

		if (obj->getNode() != nullptr)
			remove(obj);

		_insert(root, obj);

		SceneObject* scno = cast<SceneObject*>(obj);

		if (OctTree::doLog())
			Logger::console.info(true) << "OctTree - Object ID # [" << scno->getObjectID() <<  "] finished inserting " << scno->getDisplayedName() << " Total Objects in Node: " << root->objects.size();
	} catch (Exception& e) {
		Logger::console.info(true) << "[OctTree] error - " << e.getMessage() << "\n";
		e.printStackTrace();
	}
}

bool OctTree::update(TreeEntry *obj) {
	//assert(obj->getParent() == nullptr);

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::update";

	Locker locker(&mutex);

	try {
		if (OctTree::doLog()) {
			SceneObject* scno = cast<SceneObject*>(obj);
			Logger::console.info(true) << "OctTree - Object ID # [" << scno->getDisplayedName() << "] " << "Current Position:" << "(" << String::valueOf(scno->getPositionX())
					<< ", " << scno->getPositionZ() << ", " << scno->getPositionY() << ")\n";
		}

		TreeNode* node = obj->getNode();

		// Print COV
		/*
		SceneObject* scno = cast<SceneObject*>(obj);

		Locker locker(obj);

		CloseObjectsVector* closeObjectsVector = scno->getCloseObjects();
		Logger::console.info(true) << "\n\nClose objects for: " + scno->getDisplayedName();

		if (closeObjectsVector != nullptr) {
			for (int i = 0; i < closeObjectsVector->size(); ++i) {
				TreeEntry* obj = closeObjectsVector->get(i);

				if (obj == nullptr)
					continue;

				SceneObject* sceneO = cast<SceneObject*>(obj);

				if (sceneO != nullptr)
					Logger::console.info(true) << "Object #" << i << ": " + sceneO->getDisplayedName();
			}
		}

		Logger::console.info(true) << "End Close Objects \n\n";
		*/

		if (node == nullptr) {
#ifdef OUTPUT_OT_ERRORS
			Logger::console.info(true) << "OctTree - Object ID # [" << obj->getObjectID() <<  "] updating error\n";
#endif
			return false;
		}

		bool res = _update(node, obj);

		if (OctTree::doLog())
			Logger::console.info(true) << "OctTree - Object ID # [" << obj->getObjectID() <<  "] finished updating\n";

		return res;
	} catch (Exception& e) {
		Logger::console.info(true) << "[OctTree] error - " << e.getMessage() << "\n";
		e.printStackTrace();

		return false;
	}
}

void OctTree::inRange(TreeEntry *obj, float range) {
	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::inRange-1";

	ReadLocker locker(&mutex);

	CloseObjectsVector* closeObjects = obj->getCloseObjects();

	int rangesq = range * range;

	float x = obj->getPositionX();
	float y = obj->getPositionY();
	float z = obj->getPositionZ();

	float oldx = obj->getPreviousPositionX();
	float oldy = obj->getPreviousPositionY();
	float oldz = obj->getPreviousPositionZ();

	try {
		if (closeObjects != nullptr) {
			for (int i = 0; i < closeObjects->size(); i++) {
				TreeEntry* o = closeObjects->get(i).castTo<TreeEntry*>();
				ManagedReference<TreeEntry*> objectToRemove = o;
				ManagedReference<TreeEntry*> rootParent = o->getRootParent();

				if (rootParent != nullptr)
					o = rootParent;

				if (o != obj) {
					float deltaX = x - o->getPositionX();
					float deltaY = y - o->getPositionY();
					float deltaZ = z - o->getPositionZ();
					int deltaCalc = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

					if (deltaCalc > rangesq) {
						float oldDeltaX = oldx - o->getPositionX();
						float oldDeltaY = oldy - o->getPositionY();
						float oldDeltaZ = oldz - o->getPositionZ();
						int deltaCalc2 = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

						if (deltaCalc2 <= rangesq) {
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

			SceneObject* scno = cast<SceneObject*>(obj);

			if (OctTree::doLog()) {
				Logger::console.info(true) << "OctTree - Object ID # [" << scno->getDisplayedName() <<  "] in range (";

				/*for (int i = 0; i < obj->inRangeObjectCount(); ++i) {
					Logger::console.info(true) << obj->getInRangeObject(i)->getObjectID() << ", ";
				}*/
			}

	} catch (Exception& e) {
		Logger::console.info(true) << "[OctTree] " << e.getMessage();
		e.printStackTrace();
	}
}

int OctTree::inRange(float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	ReadLocker locker(&mutex);

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::inRange-2";

	try {
		return _inRange(root, x, y, z, range, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[OctTree] " << e.getMessage();
		e.printStackTrace();
	}

	return 0;
}

int OctTree::inRange(float x, float y, float z, float range, SortedVector<TreeEntry*>& objects) const {
	ReadLocker locker(&mutex);

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::inRange-3";

	try {
		return _inRange(root, x, y, z, range, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[OctTree] " << e.getMessage();
		e.printStackTrace();
	}

	return 0;
}

void OctTree::remove(TreeEntry *obj) {
	Locker locker(&mutex);

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree - Object ID # [" << obj->getObjectID() <<  "] removing\n";

	TreeNode* node = obj->getNode().castTo<TreeNode*>();

	if (node != nullptr) {
		if (!node->validateNode()) {
			Logger::console.info(true) << "OctTree - Object ID # " << obj->getObjectID() << " error on remove() - invalid Node" << node->toStringData();
		}

		node->removeObject(obj);

		node->check();
		obj->setNode(nullptr);
	} else {
		Logger::console.info(true) << "OctTree - Object ID # [" << obj->getObjectID() <<  "] ERROR - removing the node\n";
		StackTrace::printStackTrace();
	}

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree - Object ID # " << obj->getObjectID() <<  " finished removing\n";
}

void OctTree::removeAll() {
	Locker locker(&mutex);

	if (root != nullptr) {
		root = nullptr;
		//delete root;
	}
}

void OctTree::_insert(const Reference<TreeNode*>& node, TreeEntry *obj) {
	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::_insert called - Object ID # " << obj->getObjectID();

	obj->clearBounding();

	if (!node->isEmpty() && !node->hasSubNodes()) {
		if ((node->maxX - node->minX <= 8) && (node->maxY - node->minY <= 8) && (node->maxZ - node->minZ <= 8)) {
			node->addObject(obj);
			return;
		}

		for (int i = node->objects.size() - 1; i >= 0; i--) {
			TreeEntry* existing = node->getObject(i);

			if (existing->isBounding())
				continue;

			node->removeObject(i);

			if (OctTree::doLog())
				Logger::console.info(true) << "OctTree::_insert - Object ID # " << obj->getObjectID() << " is Removing Object #" << existing->getObjectID();

			if (existing->isInSWArea(node)) {
				if (node->swNode == nullptr)
					node->swNode = new TreeNode(node->minX, node->minY, node->minZ, node->dividerX, node->dividerY, node->dividerZ, node);

				_insert(node->swNode, existing);
			} else if (existing->isInSEArea(node)) {
				if (node->seNode == nullptr)
					node->seNode = new TreeNode(node->dividerX, node->minY, node->minZ, node->maxX, node->dividerY, node->dividerZ, node);

				_insert(node->seNode, existing);
			} else if (existing->isInNWArea(node)) {
				if (node->nwNode == nullptr)
					node->nwNode = new TreeNode(node->minX, node->dividerY, node->minZ, node->dividerX, node->maxY, node->dividerZ, node);

				_insert(node->nwNode, existing);
			} else if (existing->isInNEArea(node)) {
				if (node->neNode == nullptr)
					node->neNode = new TreeNode(node->dividerX, node->dividerY, node->minZ, node->maxX, node->maxY, node->dividerZ, node);

				_insert(node->neNode, existing);
			} else if (existing->isInSW2Area(node)) {
				if (node->swNode2 == nullptr)
					node->swNode2 = new TreeNode(node->minX, node->minY, node->dividerZ, node->dividerX, node->dividerY, node->maxZ, node);

				_insert(node->swNode2, existing);
			} else if (existing->isInSE2Area(node)) {
				if (node->seNode2 == nullptr)
					node->seNode2 = new TreeNode(node->dividerX, node->minY, node->dividerZ, node->maxX, node->dividerY, node->maxZ, node);

				_insert(node->seNode2, existing);
			} else if (existing->isInNW2Area(node)) {
				if (node->nwNode2 == nullptr)
					node->nwNode2 = new TreeNode(node->minX, node->dividerY, node->dividerZ, node->dividerX, node->maxY, node->maxZ, node);

				_insert(node->nwNode2, existing);
			} else if (existing->isInNE2Area(node)) {
				if (node->neNode2 == nullptr)
					node->neNode2 = new TreeNode(node->dividerX, node->dividerY, node->dividerZ, node->maxX, node->maxY, node->maxZ, node);

				_insert(node->neNode2, existing);
			}
		}
	}

	if (obj->isInArea(node)) {
		obj->setBounding();
		node->addObject(obj);

		if (OctTree::doLog())
			Logger::console.info(true) << "OctTree::_insert Object ID # " << obj->getObjectID() << " is in area, adding to node and setBounding";

		return;
	}

	if (node->hasSubNodes()) {
		if (OctTree::doLog())
			Logger::console.info(true) << "OctTree::_insert Object ID # " << obj->getObjectID() << " node has subnodes";

		if (obj->isInSWArea(node)) {
			if (node->swNode == nullptr)
				node->swNode = new TreeNode(node->minX, node->minY, node->minZ, node->dividerX, node->dividerY, node->dividerZ, node);

			_insert(node->swNode, obj);
		} else if (obj->isInSEArea(node)) {
			if (node->seNode == nullptr)
				node->seNode = new TreeNode(node->dividerX, node->minY, node->minZ, node->maxX, node->dividerY, node->dividerZ, node);

			_insert(node->seNode, obj);
		} else if (obj->isInNWArea(node)) {
			if (node->nwNode == nullptr)
				node->nwNode = new TreeNode(node->minX, node->dividerY, node->minZ, node->dividerX, node->maxY, node->dividerZ, node);

			_insert(node->nwNode, obj);
		} else if (obj->isInNEArea(node)){
			if (node->neNode == nullptr)
				node->neNode = new TreeNode(node->dividerX, node->dividerY, node->minZ, node->maxX, node->maxY, node->dividerZ, node);

			_insert(node->neNode, obj);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if (obj->isInSW2Area(node)) {
			if (node->swNode2 == nullptr)
				node->swNode2 = new TreeNode(node->minX, node->minY, node->dividerZ, node->dividerX, node->dividerY, node->maxZ, node);

			_insert(node->swNode2, obj);
		} else if (obj->isInSE2Area(node)) {
			if (node->seNode2 == nullptr)
				node->seNode2 = new TreeNode(node->dividerX, node->minY, node->dividerZ, node->maxX, node->dividerY, node->maxZ, node);

			_insert(node->seNode2, obj);
		} else if (obj->isInNW2Area(node)) {
			if (node->nwNode2 == nullptr)
				node->nwNode2 = new TreeNode(node->minX, node->dividerY, node->dividerZ, node->dividerX, node->maxY, node->maxZ, node);

			_insert(node->nwNode2, obj);
		} else  {
			if (node->neNode2 == nullptr)
				node->neNode2 = new TreeNode(node->dividerX, node->dividerY, node->dividerZ, node->maxX, node->maxY, node->maxZ, node);

			_insert(node->neNode2, obj);
		}

		if (OctTree::doLog())
			Logger::console.info(true) << "OctTree::_insert Object ID # " << obj->getObjectID() << " HITTING RETURN, object not added!";

		return;
	}

	node->addObject(obj);

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::_insert Object ID # " << obj->getObjectID() << " node added object - Total Objects: " << node->objects.size();
}

bool OctTree::_update(const Reference<TreeNode*>& node, TreeEntry* obj) {
	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::_update -- Poisition (" << obj->getPositionX() << "," << obj->getPositionZ() << "," << obj->getPositionY() << ")\n";

	if (node->testInsideOctTree(obj))
		return true;

	Reference<TreeNode*> cur = node->parentNode.get();
	while (cur != nullptr && !cur->testInsideOctTree(obj))
		cur = cur->parentNode.get();

	remove(obj);

	if (cur != nullptr) {
		_insert(cur, obj);
	}
#ifdef OUTPUT_OT_ERRORS
	else
		Logger::console.info(true) << "[OctTree] error on update() - invalid Node\n";
#endif
	return cur != nullptr;
}

void OctTree::safeInRange(TreeEntry* obj, float range) {
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

	int rangeSq = range * range;

	float x = obj->getPositionX();
	float y = obj->getPositionY();
	float z = obj->getPositionZ();

#ifdef NO_ENTRY_REF_COUNTING
	SortedVector<TreeEntry*> inRangeObjects(500, 250);
#else
	SortedVector<ManagedReference<TreeEntry*> > inRangeObjects(500, 250);
#endif

	ReadLocker locker(&mutex);

	copyObjects(root, x, y, z, range, inRangeObjects);

	locker.release();

	if (OctTree::doLog()) {
		SceneObject* sceneO = cast<SceneObject*>(obj);
		Logger::console.info(true) << "OctTree::safeInRange -- " << sceneO->getDisplayedName() << " Range: " << range << " Objects: " << inRangeObjects.size();
	}

	for (int i = 0; i < inRangeObjects.size(); ++i) {
		TreeEntry* nearEntry = inRangeObjects.getUnsafe(i);

		if (nearEntry != obj) {
			Vector3 nearObjPos = nearEntry->getPosition();

			float deltaX = x - nearObjPos.getX();
			float deltaY = y - nearObjPos.getY();
			float deltaZ = z - nearObjPos.getZ();
			int deltaCalc = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

			try {
				float outOfRangeSqr = Math::sqr(Math::max(range, nearEntry->getOutOfRangeDistance()));

				if (OctTree::doLog()) {
					SceneObject* nearSceneO = cast<SceneObject*>(nearEntry);
					Logger::console.info(true) << "OctTree::safeInRange -- Close Object #" << i << " " << nearSceneO->getDisplayedName() << " Out of Range Sq: " << outOfRangeSqr << " Delta Calc: " << deltaCalc << " Obj Position: " << nearObjPos.getX() << " " << nearObjPos.getZ() << " " << nearObjPos.getY();
				}

				if (deltaCalc < outOfRangeSqr) {
					CloseObjectsVector* objCloseObjects = obj->getCloseObjects();

					if (objCloseObjects != nullptr) {
						if (OctTree::doLog()) {
							SceneObject* nearSceneO = cast<SceneObject*>(nearEntry);
							Logger::console.info(true) << "Added Object to COV: " << nearSceneO->getDisplayedName();
						}

						obj->addInRangeObject(nearEntry, false);
					}

					CloseObjectsVector* oCloseObjects = nearEntry->getCloseObjects();

					if (oCloseObjects != nullptr)
						nearEntry->addInRangeObject(obj);
				}
			} catch (...) {
				Logger::console.info(true) << "unreported exception caught in Octree::safeInRange()\n";
			}
		} else {
			if (obj->getCloseObjects() != nullptr)
				obj->addInRangeObject(obj, false);
		}
	}
}

void OctTree::copyObjects(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<ManagedReference<server::zone::TreeEntry*> >& objects) {
	//	ReadLocker locker(&mutex);

	//objects.addAll(node->objects);
	for (int i = 0; i < node->objects.size(); ++i) {
		objects.add(node->objects.getUnsafe(i).get());
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInRange(x, y, z, range))
			copyObjects(node->nwNode, x, y, z, range, objects);
		if (node->neNode != nullptr && node->neNode->testInRange(x, y, z, range))
			copyObjects(node->neNode, x, y, z, range, objects);
		if (node->swNode != nullptr && node->swNode->testInRange(x, y, z, range))
			copyObjects(node->swNode, x, y, z, range, objects);
		if (node->seNode != nullptr && node->seNode->testInRange(x, y, z, range))
			copyObjects(node->seNode, x, y, z, range, objects);
		//////
		if (node->nwNode2 != nullptr && node->nwNode2->testInRange(x, y, z, range))
			copyObjects(node->nwNode2, x, y, z, range, objects);
		if (node->neNode2 != nullptr && node->neNode2->testInRange(x, y, z, range))
			copyObjects(node->neNode2, x, y, z, range, objects);
		if (node->swNode2 != nullptr && node->swNode2->testInRange(x, y, z, range))
			copyObjects(node->swNode2, x, y, z, range, objects);
		if (node->seNode2 != nullptr && node->seNode2->testInRange(x, y, z, range))
			copyObjects(node->seNode2, x, y, z, range, objects);
	}
}

void OctTree::copyObjects(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<server::zone::TreeEntry*>& objects) {

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::copyObjects -- called";

	for (int i = 0; i < node->objects.size(); ++i) {
		objects.add(node->objects.getUnsafe(i).get());
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInRange(x, y, z, range))
			copyObjects(node->nwNode, x, y, z, range, objects);
		if (node->neNode != nullptr && node->neNode->testInRange(x, y, z, range))
			copyObjects(node->neNode, x, y, z, range, objects);
		if (node->swNode != nullptr && node->swNode->testInRange(x, y, z, range))
			copyObjects(node->swNode, x, y, z, range, objects);
		if (node->seNode != nullptr && node->seNode->testInRange(x, y, z, range))
			copyObjects(node->seNode, x, y, z, range, objects);
		////////
		if (node->nwNode2 != nullptr && node->nwNode2->testInRange(x, y, z, range))
			copyObjects(node->nwNode2, x, y, z, range, objects);
		if (node->neNode2 != nullptr && node->neNode2->testInRange(x, y, z, range))
			copyObjects(node->neNode2, x, y, z, range, objects);
		if (node->swNode2 != nullptr && node->swNode2->testInRange(x, y, z, range))
			copyObjects(node->swNode2, x, y, z, range, objects);
		if (node->seNode2 != nullptr && node->seNode2->testInRange(x, y, z, range))
			copyObjects(node->seNode2, x, y, z, range, objects);
	}
}

void OctTree::_inRange(const Reference<TreeNode*>& node, TreeEntry *obj, float range) {
	Reference<TreeNode*> refNode = node;

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::_inRange-1 -- Total Objects = " << node->objects.size();

	int rangesq = range * range;

	float x = obj->getPositionX();
	float y = obj->getPositionY();
	float z = obj->getPositionZ();

	float oldx = obj->getPreviousPositionX();
	float oldy = obj->getPreviousPositionY();
	float oldz = obj->getPreviousPositionZ();

	for (int i = 0; i < refNode->objects.size(); i++) {
		TreeEntry *o = refNode->objects.get(i);

		if (o != obj) {
			float deltaX = x - o->getPositionX();
			float deltaY = y - o->getPositionY();
			float deltaZ = z - o->getPositionZ();
			int deltaCalc = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

			if (deltaCalc <= rangesq) {
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
				float oldDeltaZ = oldz - o->getPositionZ();
				int deltaCalc2 = oldDeltaX * oldDeltaX + oldDeltaY * oldDeltaY + oldDeltaZ * oldDeltaZ;

				if (deltaCalc2 <= rangesq) {
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
		if (refNode->nwNode != nullptr && refNode->nwNode->testInRange(x, y, z, range))
			_inRange(refNode->nwNode, obj, range);
		if (refNode->neNode != nullptr && refNode->neNode->testInRange(x, y, z, range))
			_inRange(refNode->neNode, obj, range);
		if (refNode->swNode != nullptr && refNode->swNode->testInRange(x, y, z, range))
			_inRange(refNode->swNode, obj, range);
		if (refNode->seNode != nullptr && refNode->seNode->testInRange(x, y, z, range))
			_inRange(refNode->seNode, obj, range);
			////////
		if (refNode->nwNode2 != nullptr && refNode->nwNode2->testInRange(x, y, z, range))
			_inRange(refNode->nwNode2, obj, range);
		if (refNode->neNode2 != nullptr && refNode->neNode2->testInRange(x, y, z, range))
			_inRange(refNode->neNode2, obj, range);
		if (refNode->swNode2 != nullptr && refNode->swNode2->testInRange(x, y, z, range))
			_inRange(refNode->swNode2, obj, range);
		if (refNode->seNode2 != nullptr && refNode->seNode2->testInRange(x, y, z, range))
			_inRange(refNode->seNode2, obj, range);
	}
}

int OctTree::inRange(float x, float y, float z, SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, z, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[OctTree] " << e.getMessage();
		e.printStackTrace();
	}

	return 0;
}

int OctTree::inRange(float x, float y, float z, SortedVector<TreeEntry*>& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, z, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[OctTree] " << e.getMessage();
		e.printStackTrace();
	}

	return 0;
}

int OctTree::_inRange(const Reference<TreeNode*>& node, float x, float y, float z, SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	int count = 0;

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::_inRange-2 -- Total Objects = " << node->objects.size();

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry *o = node->objects.get(i);

		if (o->containsPoint(x, y, z)) {
			++count;
			objects.put(o);
		}
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInside(x, y, z))
			count += _inRange(node->nwNode, x, y, z, objects);
		if (node->neNode != nullptr && node->neNode->testInside(x, y, z))
			count += _inRange(node->neNode, x, y, z, objects);
		if (node->swNode != nullptr && node->swNode->testInside(x, y, z))
			count += _inRange(node->swNode, x, y, z, objects);
		if (node->seNode != nullptr && node->seNode->testInside(x, y, z))
			count += _inRange(node->seNode, x, y, z, objects);
		/////
		if (node->nwNode2 != nullptr && node->nwNode2->testInside(x, y, z))
			count += _inRange(node->nwNode2, x, y, z, objects);
		if (node->neNode2 != nullptr && node->neNode2->testInside(x, y, z))
			count += _inRange(node->neNode2, x, y, z, objects);
		if (node->swNode2 != nullptr && node->swNode2->testInside(x, y, z))
			count += _inRange(node->swNode2, x, y, z, objects);
		if (node->seNode2 != nullptr && node->seNode2->testInside(x, y, z))
			count += _inRange(node->seNode2, x, y, z, objects);
	}

	return count;
}

int OctTree::_inRange(const Reference<TreeNode*>& node, float x, float y, float z, SortedVector<TreeEntry* >& objects) const {
	int count = 0;

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::_inRange-3 -- Total Objects = " << node->objects.size();

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry *o = node->objects.get(i);

		if (o->containsPoint(x, y, z)) {
			++count;
			objects.put(o);
		}
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInside(x, y, z))
			count += _inRange(node->nwNode, x, y, z, objects);
		if (node->neNode != nullptr && node->neNode->testInside(x, y, z))
			count += _inRange(node->neNode, x, y, z, objects);
		if (node->swNode != nullptr && node->swNode->testInside(x, y, z))
			count += _inRange(node->swNode, x, y, z, objects);
		if (node->seNode != nullptr && node->seNode->testInside(x, y, z))
			count += _inRange(node->seNode, x, y, z, objects);
		//////
		if (node->nwNode2 != nullptr && node->nwNode2->testInside(x, y, z))
			count += _inRange(node->nwNode2, x, y, z, objects);
		if (node->neNode2 != nullptr && node->neNode2->testInside(x, y, z))
			count += _inRange(node->neNode2, x, y, z, objects);
		if (node->swNode2 != nullptr && node->swNode2->testInside(x, y, z))
			count += _inRange(node->swNode2, x, y, z, objects);
		if (node->seNode2 != nullptr && node->seNode2->testInside(x, y, z))
			count += _inRange(node->seNode2, x, y, z, objects);
	}

	return count;
}

int OctTree::_inRange(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	int count = 0;

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::_inRange-4 -- Total Objects = " << node->objects.size();

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry *o = node->objects.get(i);

		if (o->isInRange(x, y, z, range)) {
			++count;
			objects.put(o);
		}
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInside(x, y, z))
			count += _inRange(node->nwNode, x, y, z, objects);
		if (node->neNode != nullptr && node->neNode->testInside(x, y, z))
			count += _inRange(node->neNode, x, y, z, objects);
		if (node->swNode != nullptr && node->swNode->testInside(x, y, z))
			count += _inRange(node->swNode, x, y, z, objects);
		if (node->seNode != nullptr && node->seNode->testInside(x, y, z))
			count += _inRange(node->seNode, x, y, z, objects);
		//////
		if (node->nwNode2 != nullptr && node->nwNode2->testInside(x, y, z))
			count += _inRange(node->nwNode2, x, y, z, objects);
		if (node->neNode2 != nullptr && node->neNode2->testInside(x, y, z))
			count += _inRange(node->neNode2, x, y, z, objects);
		if (node->swNode2 != nullptr && node->swNode2->testInside(x, y, z))
			count += _inRange(node->swNode2, x, y, z, objects);
		if (node->seNode2 != nullptr && node->seNode2->testInside(x, y, z))
			count += _inRange(node->seNode2, x, y, z, objects);
	}

	return count;
}

int OctTree::_inRange(const Reference<TreeNode*>& node, float x, float y, float z, float range,	SortedVector<TreeEntry* >& objects) const {
	int count = 0;

	if (OctTree::doLog())
		Logger::console.info(true) << "OctTree::_inRange-5 -- Total Objects = " << node->objects.size();

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry *o = node->objects.getUnsafe(i);

		if (o->isInRange(x, y, z, range)) {
			++count;
			objects.put(o);
		}
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInside(x, y, z))
			count += _inRange(node->nwNode, x, y, z, objects);
		if (node->neNode != nullptr && node->neNode->testInside(x, y, z))
			count += _inRange(node->neNode, x, y, z, objects);
		if (node->swNode != nullptr && node->swNode->testInside(x, y, z))
			count += _inRange(node->swNode, x, y, z, objects);
		if (node->seNode != nullptr && node->seNode->testInside(x, y, z))
			count += _inRange(node->seNode, x, y, z, objects);
		//////
		if (node->nwNode2 != nullptr && node->nwNode2->testInside(x, y, z))
			count += _inRange(node->nwNode2, x, y, z, objects);
		if (node->neNode2 != nullptr && node->neNode2->testInside(x, y, z))
			count += _inRange(node->neNode2, x, y, z, objects);
		if (node->swNode2 != nullptr && node->swNode2->testInside(x, y, z))
			count += _inRange(node->swNode2, x, y, z, objects);
		if (node->seNode2 != nullptr && node->seNode2->testInside(x, y, z))
			count += _inRange(node->seNode2, x, y, z, objects);
	}

	return count;
}
