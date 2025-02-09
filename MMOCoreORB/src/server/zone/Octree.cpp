/*
	Copyright (C) 2007 <SWGEmu>. All rights reserved.
	Distribution of this file for usage outside of Core3 is prohibited.

	Octree Implementation
*/

#include <math.h>
#include "server/zone/TreeEntry.h"
#include "server/zone/CloseObjectsVector.h"
#include "server/zone/TreeNode.h"
#include "Octree.h"
#include "server/zone/objects/scene/SceneObject.h"

#define NO_ENTRY_REF_COUNTING

using namespace server::zone;

bool Octree::logTree = false;

// #define OUTPUT_OT_ERRORS
// #define DEBUG_OCTREE_AI

Octree::Octree() {
	root = nullptr;
}

Octree::Octree(float minx, float miny, float minz, float maxx, float maxy, float maxz) {
	root = new TreeNode(minx, miny, minz, maxx, maxy, maxz, nullptr);
}

Octree::~Octree() {
	root = nullptr;
}

Object* Octree::clone() {
	return ObjectCloner<Octree>::clone(this);
}

Object* Octree::clone(void* mem) {
	return TransactionalObjectCloner<Octree>::clone(this);
}

void Octree::setSize(float minx, float miny, float minz, float maxx, float maxy, float maxz) {
	root = new TreeNode(minx, miny, minz, maxx, maxy, maxz, nullptr);
}

void Octree::insert(TreeEntry *obj) {
	if (Octree::doLog()) {
		Logger::console.info("OctTee::insert", true);
	}

	if (obj->getParent() != nullptr) {
		auto  scno = cast<SceneObject*>(obj);
		auto objParent = obj->getParent().get().castTo<SceneObject*>();

		Logger::console.info(true) << "Octree::insert - Object Inserted to Octree still has a parent Object: " << scno->getDisplayedName() << " ID: " << scno->getObjectID() << " Parent: " << objParent->getDisplayedName() << " ID: " << objParent->getObjectID();

		E3_ASSERT(obj->getParent() == nullptr);
	}

	Locker locker(&mutex);

	try {
		if (Octree::doLog()) { //--------------------------------------- HERE
			SceneObject* scno = cast<SceneObject*>(obj);
			Logger::console.info(true) << "Octree::insert[" << scno->getObjectID() << "] " << scno->getDisplayedName() <<  " inserting at: (" << obj->getPositionX() << ", " << obj->getPositionZ() << ", " << obj->getPositionY() << ")";
		}

		if (obj->getNode() != nullptr) {
			remove(obj);
		}

		_insert(root, obj);

#ifdef DEBUG_OCTREE_AI
		SceneObject* shipScno = cast<SceneObject*>(obj);

		if (shipScno->isShipAiAgent()) {
			Logger::console.info(true) << "Octree::insert[" << shipScno->getObjectID() <<  "] finished inserting " << shipScno->getDisplayedName() << " " << obj->getNode()->toStringData();
		}
#endif // DEBUG_OCTREE_AI

		if (Octree::doLog()) {
			SceneObject* scno = cast<SceneObject*>(obj);

			Logger::console.info(true) << "Octree::insert[" << scno->getObjectID() <<  "] finished inserting " << scno->getDisplayedName() << " Total Objects in Node: " << root->objects.size();
		}
	} catch (Exception& e) {
		Logger::console.info(true) << "[Octree] error - " << e.getMessage() << "\n";
		e.printStackTrace();
	}
}

bool Octree::update(TreeEntry* obj) {
	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::update";
	}

	Locker locker(&mutex);

	try {
		if (Octree::doLog()) {
			SceneObject* scno = cast<SceneObject*>(obj);

			Logger::console.info(true) << "Octree::update[" << obj->getObjectID() << "] " << "Current Position:" << obj->getPosition().toString();
		}

		auto node = obj->getNode();

		if (node == nullptr) {
#ifdef OUTPUT_OT_ERRORS
			SceneObject* scno = cast<SceneObject*>(obj);

			if (scno->isShipAiAgent()) {
				Logger::console.info(true) << "";
				Logger::console.error() << "Octree::update[" << obj->getObjectID() <<  "] ERROR -- updating error, object has a null node!\n";
			}
#endif
			return false;
		}

		bool res = _update(node, obj);

		if (Octree::doLog())
			Logger::console.info(true) << "Octree - Object ID # [" << obj->getObjectID() <<  "] finished updating\n";

		return res;
	} catch (Exception& e) {
		Logger::console.info(true) << "[Octree] error - " << e.getMessage() << "\n";
		e.printStackTrace();

		return false;
	}
}

void Octree::inRange(TreeEntry* obj, float range) {
	if (Octree::doLog())
		Logger::console.info(true) << "Octree::inRange-1";

	ReadLocker locker(&mutex);

	CloseObjectsVector* closeObjects = obj->getCloseObjects();

	float x = obj->getPositionX();
	float y = obj->getPositionY();
	float z = obj->getPositionZ();

	float oldx = obj->getPreviousPositionX();
	float oldy = obj->getPreviousPositionY();
	float oldz = obj->getPreviousPositionZ();

	uint64 objectID = obj->getObjectID();

	try {
		if (closeObjects != nullptr) {
			for (int i = 0; i < closeObjects->size(); i++) {
				TreeEntry* o = closeObjects->get(i).castTo<TreeEntry*>();
				ManagedReference<TreeEntry*> objectToRemove = o;
				ManagedReference<TreeEntry*> rootParent = o->getRootParent();

				if (rootParent != nullptr)
					o = rootParent;

				if (o != obj) {
					float nearEntryOutOfRange = Math::max(o->getOutOfRangeDistance(objectID), obj->getOutOfRangeDistance(o->getObjectID()));
					float outOfRangeSqr = Math::sqr(nearEntryOutOfRange);

					float deltaX = x - o->getPositionX();
					float deltaY = y - o->getPositionY();
					float deltaZ = z - o->getPositionZ();
					int deltaCalc = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

					if (deltaCalc > outOfRangeSqr) {
						float oldDeltaX = oldx - o->getPositionX();
						float oldDeltaY = oldy - o->getPositionY();
						float oldDeltaZ = oldz - o->getPositionZ();

						int deltaCalc2 = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

						if (deltaCalc2 <= outOfRangeSqr) {
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

			if (Octree::doLog()) {
				Logger::console.info(true) << "Octree - Object ID # [" << scno->getDisplayedName() <<  "] in range (";

				/*for (int i = 0; i < obj->inRangeObjectCount(); ++i) {
					Logger::console.info(true) << obj->getInRangeObject(i)->getObjectID() << ", ";
				}*/
			}

	} catch (Exception& e) {
		Logger::console.info(true) << "[Octree] " << e.getMessage();
		e.printStackTrace();
	}
}

int Octree::inRange(float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	ReadLocker locker(&mutex);

	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::inRange-2";
	}

	try {
		return _inRange(root, x, y, z, range, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[Octree] " << e.getMessage();
		e.printStackTrace();
	}

	return 0;
}

int Octree::inRange(float x, float y, float z, float range, SortedVector<TreeEntry*>& objects) const {
	ReadLocker locker(&mutex);

	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::inRange-3 called using root node -- Range: " << range << " X: " << x << " Z: " << z << " Y: " << y;
	}

	try {
		return _inRange(root, x, y, z, range, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[Octree] " << e.getMessage();
		e.printStackTrace();
	}

	return 0;
}

void Octree::remove(TreeEntry *obj) {
	Locker locker(&mutex);

	if (Octree::doLog()) {
		SceneObject* scno = cast<SceneObject*>(obj);

		Logger::console.info(true) << "Octree::remove - Object ID # [" << obj->getObjectID() <<  "] removing";
	}

	auto node = obj->getNode();

	if (node != nullptr) {
		if (!node->validateNode()) {
			Logger::console.info(true) << "Octree::remove - Object ID # " << obj->getObjectID() << " error on remove() - invalid Node" << node->toStringData();
		}

		node->removeObject(obj);

		node->check();
		obj->setNode(nullptr);
	} else {
		Logger::console.info(true) << "Octree::remove - Object ID # [" << obj->getObjectID() <<  "] ERROR - removing the node\n";
		StackTrace::printStackTrace();
	}

	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::remove - Object ID # " << obj->getObjectID() <<  " finished removing\n";
	}
}

void Octree::removeAll() {
	Locker locker(&mutex);

	if (root != nullptr) {
		root = nullptr;
		//delete root;
	}
}

void Octree::_insert(const Reference<TreeNode*>& node, TreeEntry* obj) {
#ifdef DEBUG_OCTREE_AI
	auto sceneO = static_cast<SceneObject*>(obj);
	bool isShipAgent = sceneO->isShipAiAgent();
#endif // DEBUG_OCTREE_AI

	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::_insert -- " << node->toStringData() << " for Object ID # " << obj->getObjectID();
	}

	/*
	 * Logic:
	 *
	 * 1) We have Objects in this Node and the Node has no children.
	 *		It has not yet been broken down into eight sections since it has been needed yet,
	 *		so we do it now and move all the objects down into the squares that arent locked.
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

		float xDiff = node->maxX - node->minX;
		float yDiff = node->maxY - node->minY;
		float zDiff = node->maxZ - node->minZ;

		if ((xDiff < 64.f) && (yDiff < 64.f) && (zDiff < 64.f)) {
			/*
			* This protects from killing the stack. If something is messed up it may
			* blow the stack because the recursion runs forever. Stop squaring when
			* it doesnt make sense anymore. If the two objects have the same coordinate
			* we add the new one to the map. The search is linear for objects inside
			* .1 Unit. So what.
			*/

#ifdef DEBUG_OCTREE_AI
			if (isShipAgent) {
				Logger::console.info(true) << "Octree::_insert[" << obj->getObjectID() << "] -- @ lowest node diff " << node->toStringData();
			}
#endif // DEBUG_OCTREE_AI

			node->addObject(obj);
			return;
		}

		/* Run 1)
		 * Proceed objects in node in reverse direction since this
		 * makes handling deletions from the vector easier.
		 */
		for (int i = node->objects.size() - 1; i >= 0; i--) {
			TreeEntry* existing = node->getObject(i);

			// We remove the Object from the Node if its not locked
			// for crossing boundaries to add it to another Node
			if (existing->isBounding()) {
				continue;
			}

#ifdef DEBUG_OCTREE_AI
			if (isShipAgent) {
				Logger::console.info(true) << "Octree::_insert[" << obj->getObjectID() << "] checking existing object for recursive node update ID: " << existing->getObjectID();
			}
#endif // DEBUG_OCTREE_AI

			// First find out which cube it needs, then Insert it into it
			// We divide the Node area into 8 squares, reusing existing children
			// octree node ctor TreeNode(float minx, float miny, float minz, float maxx, float maxy, float maxz, server::zone::TreeNode *parent)

			if (existing->isInSWArea(node)) {
				if (node->swNode == nullptr) {
					node->swNode = new TreeNode(node->minX, node->minY, node->minZ, node->dividerX, node->dividerY, node->dividerZ, node);
				}

				node->removeObject(i);

				_insert(node->swNode, existing);
			} else if (existing->isInSEArea(node)) {
				if (node->seNode == nullptr) {
					node->seNode = new TreeNode(node->dividerX, node->minY, node->minZ, node->maxX, node->dividerY, node->dividerZ, node);
				}

				node->removeObject(i);

				_insert(node->seNode, existing);
			} else if (existing->isInNWArea(node)) {
				if (node->nwNode == nullptr) {
					node->nwNode = new TreeNode(node->minX, node->dividerY, node->minZ, node->dividerX, node->maxY, node->dividerZ, node);
				}

				node->removeObject(i);

				_insert(node->nwNode, existing);
			} else if (existing->isInNEArea(node)) {
				if (node->neNode == nullptr) {
					node->neNode = new TreeNode(node->dividerX, node->dividerY, node->minZ, node->maxX, node->maxY, node->dividerZ, node);
				}

				node->removeObject(i);

				_insert(node->neNode, existing);
			//////////////////////////////////////////////////////
			} else if (existing->isInSW2Area(node)) {
				if (node->swNode2 == nullptr) {
					node->swNode2 = new TreeNode(node->minX, node->minY, node->dividerZ, node->dividerX, node->dividerY, node->maxZ, node);
				}

				node->removeObject(i);

				_insert(node->swNode2, existing);
			} else if (existing->isInSE2Area(node)) {
				if (node->seNode2 == nullptr) {
					node->seNode2 = new TreeNode(node->dividerX, node->minY, node->dividerZ, node->maxX, node->dividerY, node->maxZ, node);
				}

				node->removeObject(i);

				_insert(node->seNode2, existing);
			} else if (existing->isInNW2Area(node)) {
				if (node->nwNode2 == nullptr) {
					node->nwNode2 = new TreeNode(node->minX, node->dividerY, node->dividerZ, node->dividerX, node->maxY, node->maxZ, node);
				}

				node->removeObject(i);

				_insert(node->nwNode2, existing);
			} else if (existing->isInNE2Area(node)) {
				if (node->neNode2 == nullptr) {
					node->neNode2 = new TreeNode(node->dividerX, node->dividerY, node->dividerZ, node->maxX, node->maxY, node->maxZ, node);
				}

				node->removeObject(i);

				_insert(node->neNode2, existing);
			// Object is not in any of the children, keep it in the current node
			} else {
				existing->setBounding();

#ifdef DEBUG_OCTREE_AI
				if (isShipAgent) {
					Logger::console.info(true) << "Octree::_insert[" << existing->getObjectID() << "] object was not in any children nodes, keeping current - Position: " << existing->getPosition().toString();
				}
#endif // DEBUG_OCTREE_AI
			}
		}
	}

	/*
	* We may or may not have created more children nodes but this object extends beyond one
	* of the boundaries, so we cannot put it into a lower node. It will be
	* placed in this one regardless and locked.
	*/
	if (obj->isInArea(node)) {
		obj->setBounding();
		node->addObject(obj);

#ifdef DEBUG_OCTREE_AI
		if (isShipAgent) {
			Logger::console.info(true) << "Octree::_insert [" << obj->getObjectID() << "] -- Node: " << node->toStringData() << " is in area, ADDDING to node and setBounding due to crossing node boundaries";
		}
#endif // DEBUG_OCTREE_AI
		return;
	}

	/*
	* Child nodes were created because there was already an object inside.
	* Also, the new object is contained in one of those new children nodes
	* So we search for the right one and insert the object there.
	*/
	if (node->hasSubNodes()) {
		if (Octree::doLog()) {
			Logger::console.info(true) << "Octree::_insert [" << obj->getObjectID() << "] -- has subnodes for " << node->toStringData();
		}

		if (obj->isInSWArea(node)) {
			if (node->swNode == nullptr) {
				node->swNode = new TreeNode(node->minX, node->minY, node->minZ, node->dividerX, node->dividerY, node->dividerZ, node);
			}

			_insert(node->swNode, obj);
		} else if (obj->isInSEArea(node)) {
			if (node->seNode == nullptr) {
				node->seNode = new TreeNode(node->dividerX, node->minY, node->minZ, node->maxX, node->dividerY, node->dividerZ, node);
			}

			_insert(node->seNode, obj);
		} else if (obj->isInNWArea(node)) {
			if (node->nwNode == nullptr) {
				node->nwNode = new TreeNode(node->minX, node->dividerY, node->minZ, node->dividerX, node->maxY, node->dividerZ, node);
			}

			_insert(node->nwNode, obj);
		} else if (obj->isInNEArea(node)) {
			if (node->neNode == nullptr) {
				node->neNode = new TreeNode(node->dividerX, node->dividerY, node->minZ, node->maxX, node->maxY, node->dividerZ, node);
			}

			_insert(node->neNode, obj);
		//////////////////////////////////////////////////////
		} else if (obj->isInSW2Area(node)) {
			if (node->swNode2 == nullptr) {
				node->swNode2 = new TreeNode(node->minX, node->minY, node->dividerZ, node->dividerX, node->dividerY, node->maxZ, node);
			}

			_insert(node->swNode2, obj);
		} else if (obj->isInSE2Area(node)) {
			if (node->seNode2 == nullptr) {
				node->seNode2 = new TreeNode(node->dividerX, node->minY, node->dividerZ, node->maxX, node->dividerY, node->maxZ, node);
			}

			_insert(node->seNode2, obj);
		} else if (obj->isInNW2Area(node)) {
			if (node->nwNode2 == nullptr) {
				node->nwNode2 = new TreeNode(node->minX, node->dividerY, node->dividerZ, node->dividerX, node->maxY, node->maxZ, node);
			}

			_insert(node->nwNode2, obj);
		} else if (obj->isInNE2Area(node)) {
			if (node->neNode2 == nullptr) {
				node->neNode2 = new TreeNode(node->dividerX, node->dividerY, node->dividerZ, node->maxX, node->maxY, node->maxZ, node);
			}

			_insert(node->neNode2, obj);
		}
#ifdef DEBUG_OCTREE_AI
		else {
			if (isShipAgent) {
				Logger::console.info(true) << "Octree::_insert [" << obj->getObjectID() << "] -- Node: " << node->toStringData() << " --  Object was not in any node area.";
			}
		}
#endif // DEBUG_OCTREE_AI

		if (Octree::doLog()) {
			Logger::console.info(true) << "Octree::_insert -- Node: " << node->toStringData() << " -- Object ID # " << obj->getObjectID() << " HITTING RETURN, object not added!";
		}

		return;
	}

	// No children nodes were created and we have only one data entry, so it can stay
	// this way. Data can be Inserted, and the recursion is over.

	node->addObject(obj);

	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::_insert [" << obj->getObjectID() << "] -- Node: " << obj->getNode()->toStringData() << " -- node added object - Total Objects: " << obj->getNode()->objects.size();
	}
}

bool Octree::_update(const Reference<TreeNode*>& node, TreeEntry* obj) {
	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::_update -- Poisition (" << obj->getPositionX() << "," << obj->getPositionZ() << "," << obj->getPositionY() << ")\n";
	}

	// Still in the same node square
	if (node->testInsideOctree(obj)) {
		return true;
	}

	// We have to remporarily remove the object from the octree
	// so we hold it in Reference so it is not cleaned up by garbage collection
	Reference<TreeNode*> currentNode = node->parentNode.get();

	// Move up parent nodes until the object is in the square
	while (currentNode != nullptr && !currentNode->testInsideOctree(obj)) {
		currentNode = currentNode->parentNode.get();
	}

	// Remove the object from current node
	remove(obj);

	// Insert the object into the new node
	if (currentNode != nullptr) {
		_insert(currentNode, obj);
	}
#ifdef OUTPUT_OT_ERRORS
	else {
		SceneObject* scno = cast<SceneObject*>(obj);

		if (scno->isShipAiAgent())
			Logger::console.info(true) << "Octree::_update[" << obj->getObjectID() << "] ERROR -- currentNode is a nullptr";
	}
#endif // OUTPUT_OT_ERRORS

	// Return true if the new node is not null
	return (currentNode != nullptr);
}

void Octree::safeInRange(TreeEntry* obj, float range) {
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

	float x = obj->getPositionX();
	float y = obj->getPositionY();
	float z = obj->getPositionZ();
	uint64 objectID = obj->getObjectID();

	if (obj->getReceiverFlags() & CloseObjectsVector::CREOTYPE) {
		x = obj->getWorldPositionX();
		y = obj->getWorldPositionY();
		z = obj->getWorldPositionZ();
	}

#ifdef NO_ENTRY_REF_COUNTING
	SortedVector<TreeEntry*> inRangeObjects(1000, 250);
#else
	SortedVector<ManagedReference<TreeEntry*> > inRangeObjects(1000, 250);
#endif

	ReadLocker locker(&mutex);

	// Space has a much lower number of objects and we need to be able to add space stations and special mission ships to cov at all times.
	copyObjects(root, x, y, z, 32768.f, inRangeObjects);

	locker.release();

	if (Octree::doLog()) {
		SceneObject* sceneO = cast<SceneObject*>(obj);
		Logger::console.info(true) << "Octree::safeInRange -- " << sceneO->getDisplayedName() << " Range: " << range << " Objects: " << inRangeObjects.size() << "\n";
	}

	for (int i = 0; i < inRangeObjects.size(); ++i) {
		TreeEntry* nearEntry = inRangeObjects.getUnsafe(i);

		if (nearEntry == obj) {
			if (obj->getCloseObjects() != nullptr) {
				obj->addInRangeObject(obj, false);
			}

			continue;
		}

		Vector3 nearObjPos = nearEntry->getPosition();

		float deltaX = x - nearObjPos.getX();
		float deltaY = y - nearObjPos.getY();
		float deltaZ = z - nearObjPos.getZ();
		int deltaCalc = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

		try {
			float nearEntryOutOfRange = Math::max(nearEntry->getOutOfRangeDistance(objectID), obj->getOutOfRangeDistance(nearEntry->getObjectID()));
			float outOfRangeSqr = Math::sqr(nearEntryOutOfRange);

			if (Octree::doLog()) {
				SceneObject* nearSceneO = cast<SceneObject*>(nearEntry);
				Logger::console.info(true) << "Octree::safeInRange -- Close Object #" << i << " " << nearSceneO->getDisplayedName() << " Out of Range Sq: " << outOfRangeSqr << " Delta Calc: " << deltaCalc << " Obj Position: " << nearObjPos.getX() << " " << nearObjPos.getZ() << " " << nearObjPos.getY();
			}

			if (deltaCalc < outOfRangeSqr) {
				CloseObjectsVector* objCloseObjects = obj->getCloseObjects();

				if (objCloseObjects != nullptr) {
					if (Octree::doLog()) {
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
	}
}

void Octree::copyObjects(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<ManagedReference<server::zone::TreeEntry*> >& objects) {
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

void Octree::copyObjects(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<server::zone::TreeEntry*>& objects) {
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

void Octree::_inRange(const Reference<TreeNode*>& node, TreeEntry *obj, float range) {
	Reference<TreeNode*> refNode = node;

	if (Octree::doLog())
		Logger::console.info(true) << "Octree::_inRange-1 -- Total Objects = " << node->objects.size();

	float x = obj->getPositionX();
	float y = obj->getPositionY();
	float z = obj->getPositionZ();

	float oldx = obj->getPreviousPositionX();
	float oldy = obj->getPreviousPositionY();
	float oldz = obj->getPreviousPositionZ();
	uint64 objectID = obj->getObjectID();

	for (int i = 0; i < refNode->objects.size(); i++) {
		TreeEntry* treeEntry = refNode->objects.get(i);

		if (treeEntry != obj) {
			float nearEntryOutOfRange = Math::max(treeEntry->getOutOfRangeDistance(objectID), obj->getOutOfRangeDistance(treeEntry->getObjectID()));
			float outOfRangeSqr = Math::sqr(nearEntryOutOfRange);

			float deltaX = x - treeEntry->getPositionX();
			float deltaY = y - treeEntry->getPositionY();
			float deltaZ = z - treeEntry->getPositionZ();
			int deltaCalc = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

			if (deltaCalc < outOfRangeSqr) {
				CloseObjectsVector* objCloseObjects = obj->getCloseObjects();

				if (objCloseObjects != nullptr && !objCloseObjects->contains(treeEntry)) {
					obj->addInRangeObject(treeEntry, false);
					//obj->notifyInsert(treeEntry);
				}

				CloseObjectsVector* entryCloseObjects = treeEntry->getCloseObjects();

				if (entryCloseObjects != nullptr && !entryCloseObjects->contains(obj)) {
					treeEntry->addInRangeObject(obj);
					//treeEntry->notifyInsert(obj);
				} else {
					treeEntry->notifyPositionUpdate(obj);
				}

				/*obj->addInRangeObject(treeEntry, false);
				treeEntry->addInRangeObject(obj);*/
			} else {
				float oldDeltaX = oldx - treeEntry->getPositionX();
				float oldDeltaY = oldy - treeEntry->getPositionY();
				float oldDeltaZ = oldz - treeEntry->getPositionZ();

				int deltaCalc2 = (oldDeltaX * oldDeltaX) + (oldDeltaY * oldDeltaY) + (oldDeltaZ * oldDeltaZ);

				if (deltaCalc2 < outOfRangeSqr) {
					CloseObjectsVector* objCloseObjects = obj->getCloseObjects();

					if (objCloseObjects != nullptr) {
						obj->removeInRangeObject(treeEntry);
					}

					CloseObjectsVector* entryCloseObjects = treeEntry->getCloseObjects();

					if (entryCloseObjects != nullptr) {
						treeEntry->removeInRangeObject(obj);
					}
				}
			}
		} else {
			if (obj->getCloseObjects() != nullptr) {
				obj->addInRangeObject(obj, false);
			}
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

int Octree::inRange(float x, float y, float z, SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, z, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[Octree] " << e.getMessage();
		e.printStackTrace();
	}

	return 0;
}

int Octree::inRange(float x, float y, float z, SortedVector<TreeEntry*>& objects) const {
	ReadLocker locker(&mutex);

	try {
		return _inRange(root, x, y, z, objects);
	} catch (Exception& e) {
		Logger::console.info(true) << "[Octree] " << e.getMessage();
		e.printStackTrace();
	}

	return 0;
}

int Octree::_inRange(const Reference<TreeNode*>& node, float x, float y, float z, SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	int count = 0;

	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::_inRange-2 -- Location - X: " << x << " Z: " << z << " Y: " << y << " Node: " << node->toStringData();
	}

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry* treeEntry = node->objects.get(i);

		if (treeEntry->containsPoint(x, y, z)) {
			++count;
			objects.put(treeEntry);
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

int Octree::_inRange(const Reference<TreeNode*>& node, float x, float y, float z, SortedVector<TreeEntry*>& objects) const {
	int count = 0;

	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::_inRange-3 -- Location - X: " << x << " Z: " << z << " Y: " << y << " Node: " << node->toStringData();
	}

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry* treeEntry = node->objects.get(i);

		if (Octree::doLog()) {
			Logger::console.info(true) << "_inRange-5 is check if object #" << i << " is in range. Node: " << node->toStringData();
		}

		if (treeEntry->isInRange(x, y, z)) {
			++count;
			objects.put(treeEntry);
		}
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInside(x, y, z)) {
			count += _inRange(node->nwNode, x, y, z, objects);
		}
		if (node->neNode != nullptr && node->neNode->testInside(x, y, z)) {
			count += _inRange(node->neNode, x, y, z, objects);
		}
		if (node->swNode != nullptr && node->swNode->testInside(x, y, z)) {
			count += _inRange(node->swNode, x, y, z, objects);
		}
		if (node->seNode != nullptr && node->seNode->testInside(x, y, z)) {
			count += _inRange(node->seNode, x, y, z, objects);
		}
		//////////////////////////////////////////////////////
		if (node->nwNode2 != nullptr && node->nwNode2->testInside(x, y, z)) {
			count += _inRange(node->nwNode2, x, y, z, objects);
		}
		if (node->neNode2 != nullptr && node->neNode2->testInside(x, y, z)) {
			count += _inRange(node->neNode2, x, y, z, objects);
		}
		if (node->swNode2 != nullptr && node->swNode2->testInside(x, y, z)) {
			count += _inRange(node->swNode2, x, y, z, objects);
		}
		if (node->seNode2 != nullptr && node->seNode2->testInside(x, y, z)) {
			count += _inRange(node->seNode2, x, y, z, objects);
		}
	}

	return count;
}

int Octree::_inRange(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >& objects) const {
	int count = 0;

	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::_inRange-4 -- Range: " << range << " Location - X: " << x << " Z: " << z << " Y: " << y << " Node: " << node->toStringData();
	}

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry* treeEntry = node->objects.get(i);

		if (treeEntry->isInRange(x, y, z, range)) {
			++count;
			objects.put(treeEntry);
		}
	}

	if (node->hasSubNodes()) {
		if (node->nwNode != nullptr && node->nwNode->testInRange(x, y, z, range)) {
			count += _inRange(node->nwNode, x, y, z, range, objects);
		}
		if (node->neNode != nullptr && node->neNode->testInRange(x, y, z, range)) {
			count += _inRange(node->neNode, x, y, z, range, objects);
		}
		if (node->swNode != nullptr && node->swNode->testInRange(x, y, z, range)) {
			count += _inRange(node->swNode, x, y, z, range, objects);
		}
		if (node->seNode != nullptr && node->seNode->testInRange(x, y, z, range)) {
			count += _inRange(node->seNode, x, y, z, range, objects);
		}
		//////////////////////////////////////////////////////
		if (node->nwNode2 != nullptr && node->nwNode2->testInRange(x, y, z, range)) {
			count += _inRange(node->nwNode2, x, y, z, range, objects);
		}
		if (node->neNode2 != nullptr && node->neNode2->testInRange(x, y, z, range)) {
			count += _inRange(node->neNode2, x, y, z, range, objects);
		}
		if (node->swNode2 != nullptr && node->swNode2->testInRange(x, y, z, range)) {
			count += _inRange(node->swNode2, x, y, z, range, objects);
		}
		if (node->seNode2 != nullptr && node->seNode2->testInRange(x, y, z, range)) {
			count += _inRange(node->seNode2, x, y, z, range, objects);
		}
	}

	return count;
}

int Octree::_inRange(const Reference<TreeNode*>& node, float x, float y, float z, float range,	SortedVector<TreeEntry*>& objects) const {
	int count = 0;

	if (Octree::doLog()) {
		Logger::console.info(true) << "Octree::_inRange-5 -- Range: " << range << " Location - X: " << x << " Z: " << z << " Y: " << y << " Node: " << node->toStringData();
	}

	for (int i = 0; i < node->objects.size(); i++) {
		TreeEntry* treeEntry = node->objects.getUnsafe(i);

		if (Octree::doLog()) {
			Logger::console.info(true) << "_inRange-5 is check if object #" << i << " is in range. Node: " << node->toStringData();
		}

		if (treeEntry->isInRange(x, y, z, range)) {
			objects.put(treeEntry);
			count++;
		}
	}

	if (node->hasSubNodes()) {
		if (Octree::doLog()) {
			Logger::console.info(true) << "Octree::_inRange-5 -- has Sub Nodes - Current Object Count: Node: " << node->toStringData();
		}

		if (node->nwNode != nullptr && node->nwNode->testInRange(x, y, z, range)) {
			count += _inRange(node->nwNode, x, y, z, range, objects);
		}

		if (node->neNode != nullptr && node->neNode->testInRange(x, y, z, range)) {
			count += _inRange(node->neNode, x, y, z, range, objects);
		}

		if (node->swNode != nullptr && node->swNode->testInRange(x, y, z, range)) {
			count += _inRange(node->swNode, x, y, z, range, objects);
		}

		if (node->seNode != nullptr && node->seNode->testInRange(x, y, z, range)) {
			count += _inRange(node->seNode, x, y, z, range, objects);
		}

		//////////////////////////////////////////////////////

		if (node->nwNode2 != nullptr && node->nwNode2->testInRange(x, y, z, range)) {
			count += _inRange(node->nwNode2, x, y, z, range, objects);
		}

		if (node->neNode2 != nullptr && node->neNode2->testInRange(x, y, z, range)) {
			count += _inRange(node->neNode2, x, y, z, range, objects);
		}

		if (node->swNode2 != nullptr && node->swNode2->testInRange(x, y, z, range)) {
			count += _inRange(node->swNode2, x, y, z, range, objects);
		}

		if (node->seNode2 != nullptr && node->seNode2->testInRange(x, y, z, range)) {
			count += _inRange(node->seNode2, x, y, z, range, objects);
		}
	}

	return count;
}
