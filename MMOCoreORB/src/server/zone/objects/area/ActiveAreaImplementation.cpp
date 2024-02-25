/*
 * ActiveAreaImplementation.cpp
 *
 *  Created on: 02/06/2010
 *      Author: victor
 */

#include "server/zone/objects/area/ActiveArea.h"
#include "events/ActiveAreaEvent.h"
#include "server/zone/objects/area/areashapes/AreaShape.h"
#include "server/zone/objects/region/SpawnArea.h"
#include "server/zone/managers/creature/SpawnAreaMap.h"
#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/objects/area/areashapes/CuboidAreaShape.h"
#include "server/zone/objects/player/PlayerObject.h"

bool ActiveAreaImplementation::containsPoint(float px, float py, uint64 cellid) const {
	if (cellObjectID != 0 && cellObjectID != cellid)
		return false;

	return containsPoint(px, py);
}

bool ActiveAreaImplementation::containsPoint(float px, float py) const {
	if (areaShape == nullptr) {
		float dx = getPositionX() - px;
		float dy = getPositionY() - py;

		float squaredLength = dx * dx + dy * dy;
		return squaredLength <= (radius * radius);
	}

	return areaShape->containsPoint(px, py);
}

bool ActiveAreaImplementation::containsPoint(float px, float pz, float py, uint64 cellid) const {
	if (cellObjectID != 0 && cellObjectID != cellid)
		return false;

	return containsPoint(px, pz, py);
}

bool ActiveAreaImplementation::containsPoint(float px, float pz, float py) const {
	if (areaShape == nullptr) {
		Vector3 position(px, pz, py);

		bool testRange = (getPosition().squaredDistanceTo(position) < (radius * radius));
		return testRange;
	}

	return areaShape->containsPoint(px, pz, py);
}

void ActiveAreaImplementation::enqueueEnterEvent(SceneObject* obj) {
#ifdef WITH_STM
	notifyEnter(obj);
#else
	Reference<Task*> task = new ActiveAreaEvent(_this.getReferenceUnsafeStaticCast(), obj, ActiveAreaEvent::ENTEREVENT);
	obj->executeOrderedTask(task);

#endif
}

void ActiveAreaImplementation::enqueueExitEvent(SceneObject* obj) {
#ifdef WITH_STM
	notifyExit(obj);
#else
	Reference<Task*> task = new ActiveAreaEvent(_this.getReferenceUnsafeStaticCast(), obj, ActiveAreaEvent::EXITEVENT);
	obj->executeOrderedTask(task);

#endif
}

void ActiveAreaImplementation::notifyEnter(SceneObject* obj) {
	if (cellObjectID == 0 || cellObjectID == obj->getParentID())
		notifyObservers(ObserverEventType::ENTEREDAREA, obj);

	if (isLockedArea() && ejectFromArea(obj)) {
		return;
	}

	if (obj->isPlayerCreature()) {
		if (attachedScenery.size() > 0) {
			ManagedReference<SceneObject*> sceno = obj;
			Vector<ManagedReference<SceneObject* > > scene = attachedScenery;

			Core::getTaskManager()->executeTask([=] () {
				for (int i = 0; i < scene.size(); i++) {
					SceneObject* scenery = scene.get(i);
					Locker locker(scenery);

					scenery->sendTo(sceno, true);
				}
			}, "SendSceneryLambda");
		}

		if (obj->isDebuggingRegions())
			sendDebugMessage(obj, true);
	}
}

void ActiveAreaImplementation::notifyExit(SceneObject* obj) {
	if (cellObjectID == 0 || cellObjectID != obj->getParentID())
		notifyObservers(ObserverEventType::EXITEDAREA, obj);

	if (obj->isPlayerCreature()) {
		if (attachedScenery.size() > 0) {
			ManagedReference<SceneObject*> sceno = obj;
			Vector<ManagedReference<SceneObject* > > scene = attachedScenery;

			Core::getTaskManager()->executeTask([=] () {
				for (int i = 0; i < scene.size(); i++) {
					SceneObject* scenery = scene.get(i);
					Locker locker(scenery);

					scenery->sendDestroyTo(sceno);
				}
			}, "SendDestroySceneryLambda");
		}

		if (obj->isDebuggingRegions())
			sendDebugMessage(obj, false);
	}
}

void ActiveAreaImplementation::sendDebugMessage(SceneObject* object, bool entry) {
	if (object == nullptr || !object->isPlayerCreature())
		return;

	CreatureObject* creature = object->asCreatureObject();

	if (creature == nullptr)
		return;

	StringBuffer debugMsg;

	if (entry) {
		debugMsg << "Entering Region:  " << areaName << "  -  ";
	} else {
		debugMsg << "Exiting Region:  " << areaName << "  -  ";
	}

	String shapeString = areaShape == nullptr ? " null shape " : areaShape->isRectangularAreaShape() ? " rectangle " : areaShape->isCircularAreaShape() ? " circle "
		: areaShape->isRingAreaShape() ? " ring " : " none ";

	debugMsg << " Region Shape = " << shapeString;
	debugMsg << " Radius = " << getRadius() << "  ";

	Vector3 playerCoords = creature->getWorldPosition();
	debugMsg << " Player Coords: X = " << playerCoords.getX() <<  "  Z = " << playerCoords.getZ() <<"  Y = " << playerCoords.getY() << " ";

	Vector3 coords = getWorldPosition();
	debugMsg << " Area Coords - X = " << coords.getX() <<  " Z = " << coords.getZ() <<"  Y = " << coords.getY() << " ";

	StringBuffer regionTypes;

	if (isUndefinedRegion())
		regionTypes << "UNDEFINEDAREA ";
	if (isSpawnArea())
		regionTypes << "SPAWNAREA ";
	if (isNoSpawnArea())
		regionTypes << "NOSPAWNAREA ";
	if (isWorldSpawnArea())
		regionTypes << "WORLDSPAWNAREA ";
	if (isNoWorldSpawnArea())
		regionTypes << "NOWORLDSPAWNAREA ";
	if (isNoBuildZone())
		regionTypes << "NOBUILDZONEAREA ";
	if (isCampingArea())
		regionTypes << "CAMPINGAREA ";
	if (isCityRegion())
		regionTypes << "CITY ";
	if (shouldBuildNavmesh())
		regionTypes << "NAVAREA ";
	if (isNamedRegion())
		regionTypes << "NAMEDREGION ";
	if (isLockedArea())
		regionTypes << "LOCKEDAREA";

	if (isNoCombatArea())
		regionTypes << "NOCOMBATAREA";
	if (isNoDuelArea())
		regionTypes << "NODUELAREA";
	if (isPvpArea())
		regionTypes << "PVPAREA";
	if (isOvertArea())
		regionTypes << "OVERTAREA";
	if (isRebelArea())
		regionTypes << "REBELAREA";
	if (isImperialArea())
		regionTypes << "IMPERIALAREA";
	if (isNoPetArea())
		regionTypes << "NOPETAREA";

	debugMsg << " Region Types: (" << regionTypes.toString() << ")";

	creature->sendSystemMessage(debugMsg.toString());
}

void ActiveAreaImplementation::setZone(Zone* zone) {
	this->zone = zone;
}

bool ActiveAreaImplementation::intersectsWith(ActiveArea* area) const {
	if (areaShape == nullptr) {
		return false;
	}

	return areaShape->intersectsWith(area->getAreaShape());
}

void ActiveAreaImplementation::initializeChildObject(SceneObject* controllerObject) {
	ManagedReference<SceneObject*> objectParent = controllerObject->getParent().get();

	if (objectParent != nullptr && objectParent->isCellObject()) {
		setCellObjectID(objectParent->getObjectID());
	}
}

void ActiveAreaImplementation::addAreaFlag(uint32 flag) {
	if (!(areaFlags & flag)) {
		areaFlags |= flag;
	}
}

void ActiveAreaImplementation::removeAreaFlag(uint32 flag) {
	if (areaFlags & flag) {
		areaFlags &= ~flag;
	}
}

Vector3 ActiveAreaImplementation::getAreaCenter() const {
	if (areaShape != nullptr)
		return areaShape->getAreaCenter();
	else
		return getPosition();
}

Vector4 ActiveAreaImplementation::getRectangularDimensions() const {
	Vector4 dimsensions;

	if (isRectangularAreaShape()) {
		RectangularAreaShape* rect = dynamic_cast<RectangularAreaShape*>(areaShape.get());

		if (rect != nullptr)
			dimsensions = rect->getRectangularDimensions();
	}

	return dimsensions;
}

Vector3 ActiveAreaImplementation::getCuboidDimensions() const {
	Vector3 dimsensions;

	if (isCuboidAreaShape()) {
		CuboidAreaShape* cuboid = dynamic_cast<CuboidAreaShape*>(areaShape.get());

		if (cuboid != nullptr)
			dimsensions = cuboid->getCuboidDimensions();
	}

	return dimsensions;
}

bool ActiveAreaImplementation::ejectFromArea(SceneObject* object) {
	if (object == nullptr || !object->isCreatureObject()) {
		return false;
	}

	CreatureObject* creature = object->asCreatureObject();

	if (creature == nullptr)
		return false;

	try {
		if (creature->isPlayerCreature()) {
			PlayerObject* ghost = creature->getPlayerObject();

			if (ghost != nullptr && ghost->isPrivileged()) {
				return false;
			}
		}

		float x = creature->getPositionX();
		float y = creature->getPositionY();

		float diffX = x - getPositionX();
		float diffY = y - getPositionY();

		float angle = atan2(diffY, diffX);
		float rad = getRadius() + 20.f;

		float newPosX = getPositionX() + (cos(angle) * rad);
		float newPosY = getPositionY() + (sin(angle) * rad);

		creature->teleport(newPosX, creature->getPositionZ(), newPosY, 0);
		creature->sendSystemMessage("You are not permitted to enter this area.");
	} catch (Exception& e) {
		e.printStackTrace();
		return false;
	}

	return true;
}