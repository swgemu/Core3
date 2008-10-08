/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef SCENEOBJECTIMPLEMENTATION_H_
#define SCENEOBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "SceneObject.h"

#include "engine/util/QuadTreeEntry.h"

#include "events/UndeploySceneObjectEvent.h"

#include "../area/BaseArea.h"

#include "../../managers/planet/PlanetManager.h"

#include "../../Zone.h"

class Zone;
class ZoneClientSession;
class Player;

class ZoneProcessServerImplementation;

class ObjectMenuResponse;

class SceneObjectImplementation : public SceneObjectServant, public QuadTreeEntry, public Logger {

protected:
	ZoneProcessServerImplementation* server;

	Zone* zone;

	int objectType;
	uint32 objectCRC;

	int zoneID;

	uint32 movementCounter;
	bool moving;

	float directionX;
	float directionZ;
	float directionY;
	float directionW;

	uint8 directionAngle;

	SceneObject* parent;

	uint32 linkType;

	UndeploySceneObjectEvent* undeployEvent;

	bool keepObject;

	uint64 associatedArea;

public:
	static const int NONPLAYERCREATURE = 1;
	static const int PLAYER = 2;
	static const int TANGIBLE = 3;
	static const int GROUP = 4;
	static const int BUILDING = 5;
	static const int CELL = 6;
	static const int INTANGIBLE = 7;
	static const int STATIC = 8;
	static const int SHIP = 9;
	static const int ATTACKABLE = 10;
	static const int MISSION = 11;
	static const int PLAYEROBJECT = 12;
	static const int WAYPOINT = 13;
	static const int MANUFACTURESCHEMATIC = 14;

public:
	SceneObjectImplementation();
	SceneObjectImplementation(uint64 oid, int type);

	virtual ~SceneObjectImplementation();

	bool destroy();

	void redeploy();

	void scheduleUndeploy();

	void undeploy();

	void removeUndeploymentEvent();

	void create(ZoneClientSession* client);
	void destroy(ZoneClientSession* client);

	void link(ZoneClientSession* client, SceneObject* obj);
	BaseMessage* link(SceneObject* obj);
	BaseMessage* link(uint64 container, uint32 type);

	void close(ZoneClientSession* client);

	virtual void insertToZone(Zone * zone);
	virtual void insertToBuilding(BuildingObject * building);
	virtual void removeFromZone(bool doLock = true);
	virtual void removeFromBuilding(BuildingObject* building);

	void broadcastMessage(BaseMessage* msg, int range = 128, bool doLock = true);
	void broadcastMessage(StandaloneBaseMessage* msg, int range = 128, bool doLock = true);

	virtual void sendTo(Player* player, bool doClose = true) {
	}

	virtual void sendDestroyTo(Player* player) {
	}

	virtual void notifyInsert(QuadTreeEntry* obj) {
	}

	virtual void notifyDissapear(QuadTreeEntry* obj) {
	}

	virtual void sendConversationStartTo(SceneObject* obj) {
	}

	virtual void selectConversationOption(int option, SceneObject* obj) {
	}

	virtual void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	virtual int useObject(Player* player) {
		return 0;
	}

	virtual void generateAttributes(SceneObject* obj);

	void randomizePosition(float radius);

	//TODO: figure out why gcc don't fookin see these shit from ManagedObjectImplementation directly
	void lock(bool doLock = true);
	void lock(ManagedObject* obj);

	void wlock(bool doLock = true);
	void wlock(ManagedObject* obj);

	void unlock(bool doLock = true);

	void setLockName(const string& name);

	// setters and getters
	inline void setMovementCounter(uint32 cnt) {
		movementCounter = cnt;
	}

	void switchMovingState() {
		if (moving)
			moving = false;
		else
			moving = true;
	}

	inline uint32 returnMovementCounter() {
		return movementCounter;
	}

	inline void increaseMovementCounter() {
		movementCounter++;
	}

	inline void setNorthDirection() {
		directionX = 0;
		directionZ = 0;
		directionY = 1;
	}

	inline void setSouthDirection() {
		directionX = 0;
		directionZ = 0;
		directionY = -1;
	}

	inline void setWestDirection() {
		directionX = -1;
		directionZ = 0;
		directionY = 1;
	}

	inline void setEastDirection() {
		directionX = 1;
		directionZ = 0;
		directionY = 0;
	}

	// set direction by angle
	inline void setDirection(float angle) {
		float angleInRadial = (angle / 180) * M_PI;

		directionAngle = (uint8) ((angleInRadial/6.283f) * 100);

		directionX = sin(angleInRadial);
		directionY = cos(angleInRadial);
		directionZ = 0;
	}

	inline void setRadialDirection(float radangle) {
		directionAngle = (uint8) ((radangle/6.283f) * 100);

		directionX = sin(radangle);
		directionY = cos(radangle);
		directionZ = 0;
	}

	// set direction by quaternion
	inline void setDirection(float x, float z, float y, float w) {
		float angle;

		directionX = x;
		directionZ = z;
		directionY = y;
		directionW = w;

		if (x * x + z * z + y * y > 0.0f) {
			if (w > 0.0f && z < 0)
				w *= -1.0f;

			angle = 2.0f * acos(w);
		} else
			angle = 0.0f;

		directionAngle = (uint8) ((angle/6.283f) * 100);
	}

	bool isInRange(SceneObject* obj, float range) {
		return QuadTreeEntry::isInRange(obj->getPositionX(), obj->getPositionY(), range);
	}

	bool isInRange(float x, float y, float range) {
		return QuadTreeEntry::isInRange(x, y, range);
	}

	inline bool isPlayer() {
		return objectType == PLAYER;
	}

	inline bool isNonPlayerCreature() {
		return objectType == NONPLAYERCREATURE;
	}

	inline bool isBuilding() {
		return objectType == BUILDING;
	}

	inline bool isCell() {
		return objectType == CELL;
	}

	inline bool isTangible() {
		return objectType == TANGIBLE;
	}

	inline bool isIntangible() {
		return objectType == INTANGIBLE;
	}

	inline bool isStatic() {
		return objectType == STATIC;
	}

	inline bool isShip() {
		return objectType == SHIP;
	}

	inline bool isAttackableObject() {
		return objectType == ATTACKABLE;
	}

	inline bool isMission() {
		return objectType == MISSION;
	}

	inline bool isPlayerObject() {
		return objectType == PLAYEROBJECT;
	}

	inline bool isWaypoint() {
		return objectType == WAYPOINT;
	}

	inline bool isManufactureSchematic() {
		return objectType == MANUFACTURESCHEMATIC;
	}

	int compareTo(SceneObject* obj) {
		uint64 id = obj->getObjectID();

		if (objectID < id)
			return 1;
		else if (objectID > id)
			return -1;
		else
			return 0;
	}

	// setters
	inline void setParent(SceneObject* par, uint32 linktype = 0x04) {
		if (par != _this) {
			parent = par;
			linkType = linktype;
		}
	}

	void setZoneProcessServer(ZoneProcessServerImplementation* serv) {
		server = serv;
	}

	void setZone(Zone* zne) {
		zone = zne;
	}

	inline void setZoneIndex(int id) {
		zoneID = id;
	}

	inline void setObjectID(uint64 oid) {
		objectID = oid;
	}

	inline void setObjectCRC(uint32 crc) {
		objectCRC = crc;
	}

	inline void setObjectKeeping(bool keeping) {
		keepObject = true;
	}

	inline void clearUndeploymentEvent() {
		undeployEvent = NULL;
	}

	inline bool isUndeploymentScheduled() {
		return undeployEvent != NULL;
	}

	inline void setAssociatedArea(uint64 uid) {
		associatedArea = uid;
	}

	// getters
	inline Zone* getZone() {
		return zone;
	}

	inline int getZoneID() {
		return zoneID;
	}

	inline uint32 getObjectCRC() {
		return objectCRC;
	}

	inline int getObjectType() {
		return objectType;
	}

	inline uint32 getMovementCounter() {
		return movementCounter;
	}

	inline bool isMoving() {
		return moving;
	}

	inline float getDirectionX() {
		return directionX;
	}

	inline float getDirectionZ() {
		return directionZ;
	}

	inline float getDirectionY() {
		return directionY;
	}

	inline float getDirectionW() {
		return directionW;
	}

	inline uint8 getDirectionAngle() {
		return directionAngle;
	}

	inline SceneObject* getParent() {
		return parent;
	}

	inline QuadTreeEntry* getQuadTreeEntry() {
		return (QuadTreeEntry*) this;
	}

	inline uint64 getParentID() {
		if (parent == NULL)
			return 0;
		else
			return parent->getObjectID();
	}

	inline float getPrecision(float num, int digits) {
		float power = pow(10, digits);
		return float(floor(num * power + .05f) / power);
	}

	inline uint64 getAssociatedArea() {
		return associatedArea;
	}

	inline bool doKeepObject() {
		return keepObject;
	}

	// Virtual combat functions
	virtual void setDefender(SceneObject* defender) {
	}

	virtual void addDefender(SceneObject* defender) {
	}

	virtual void removeDefender(SceneObject* defender) {
	}

	virtual void removeDefenders() {
	}

	virtual bool hasDefender(SceneObject* defender) {
		return false;
	}

	virtual void setCombatState() {
	}

	virtual void clearCombatState(bool removeDefenders = true) {
	}

	virtual SceneObject* getDefender(int idx) {
		return NULL;
	}

	virtual bool isPeaced() {
		return true;
	}

	virtual uint32 getDefenderListSize() {
		return 0;
	}

	virtual bool isAttackableBy(CreatureObject* creature) {
		return false;
	}

	inline bool isInANoBuildArea() {
		PlanetManager * planetManager = this->getZone()->getPlanetManager();

		return planetManager->isNoBuildArea(positionX, positionY);
	}

};

#endif /*SCENEOBJECTIMPLEMENTATION_H_*/
