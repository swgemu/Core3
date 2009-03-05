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

#include "../../managers/planet/PlanetManager.h"

#include "../../managers/player/ProfessionManager.h"

#include "../../Zone.h"

#include "ContainerObject.h"

#include "DamageDone.h"

class Zone;
class ZoneClientSession;
class Player;
class GroupObject;

class ZoneProcessServerImplementation;

class ObjectMenuResponse;

class SceneObjectImplementation : public SceneObjectServant, public QuadTreeEntry, public ContainerObject, public Logger {

protected:
	/*
	 * objectName - 2 asciis
	detailedDescription - string_id_table
	lookAtText - string_id_table
	snapToTerrain - short default 1
	containerType -
	containerVolumeLimit
	tintPalette
	slotDescriptorFilename
	arrangementDescriptorFilename
	appearanceFilename
	portalLayoutFilename
	clientDataFile
	collisionMaterialFlags
	collisionMaterialPassFlags
	collisionMaterialBlockFlags
	collisionActionFlags
	collisionActionPassFlags
	collisionActionBlockFlags
	scale
	gameObjectType
	sendToClient
	scaleThresholdBeforeExtentTest
	clearFloraRadius
	surfaceType
	noBuildRadius
	onlyVisibleInTools
	locationReservationRadius*/

	ZoneProcessServerImplementation* server;

	Zone* zone;

	int objectType;
	uint32 objectCRC;

	UnicodeString customName;
	String templateTypeName;
	String templateName;

	int zoneID;

	uint32 movementCounter;
	bool moving;

	float directionX;
	float directionZ;
	float directionY;
	float directionW;

	uint8 directionAngle;
	float precisionDirectionAngle;

	SceneObject* parent;

	uint32 linkType;

	UndeploySceneObjectEvent* undeployEvent;

	bool keepObject;

	bool canPickup;

	uint64 associatedArea;

	bool attackable;

	VectorMap<GroupObject*, int> groupDamageList;
	VectorMap<CreatureObject*, DamageDone*> playerDamageList;

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
	static const int CAMPSITE = 15;
	static const int INVENTORYOBJECT = 16;
	static const int BANKINVENTORYSTORAGE = 17;

	static const int NONATTACKABLE_BITMASK = 0x1000;
	static const int CREO_BITMASK = 0x80;

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
	BaseMessage* link(SceneObject* obj, uint32 type);
	BaseMessage* link(SceneObject* obj);
	BaseMessage* link(uint64 container, uint32 type);

	void close(ZoneClientSession* client);

	void init();
	virtual void initScriptedValues();

	virtual void insertToZone(Zone * zone);
	virtual void insertToBuilding(BuildingObject * building);
	virtual void removeFromZone(bool doLock = true);
	virtual void removeFromBuilding(BuildingObject* building);

	// experience functions
	/**
	 * Adds to or creates a log of the damage done
	 * to this object by creature.
	 * \param creature The CreatureObject that is doing the damage.
	 * \param damage How much damage is done.
	 * \param skillname the name of the skill that is doing the damage.
	 */
	void addDamageDone(CreatureObject* creature, int damage, String skillname);
	/**
	 * Removes the damage log of a specific creature
	 * from this object.
	 * \param creature The CreatureObject that is getting dropped.
	 */
	void dropDamageDone(CreatureObject* creature);
	/**
	 * Calculates the value of the total damage done
	 * to this object in all of the logs.
	 * \return Total damage done to the mob according to the damage log.
	 */
	int getTotalDamage();
	/**
	 * takes the level of the destroyed/dead scno
	 * and disseminates experience appropriately.
	 * \param levels The level of the dead object.
	 */
	void disseminateXp(int levels);
	/**
	 * Cleans up the damage logs and frees the
	 * appropriate resources after the logs have
	 * been used.
	 */
	void cleanupDamageDone();

	void broadcastMessage(BaseMessage* msg, int range = 128, bool doLock = true, bool sendSelf = true);
	void broadcastMessage(StandaloneBaseMessage* msg, int range = 128, bool doLock = true);
	void broadcastMessages(Vector<BaseMessage*>& msgs, int range = 128, bool doLock = true);

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

	void setLockName(const String& name);

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
		directionY = 0;
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

		if (w * w + y * y > 0.0f) {
			if (w > 0.0f && y < 0.0f)
				w *= -1.0f;

			angle = 2.0f * acos(w);
		} else
			angle = 0.0f;

		precisionDirectionAngle = angle;
		directionAngle = (uint8) ((angle/6.283f) * 100); //used for updating player clients.
	}

	/**
	 * getCoordinate Returns the coordinates of a position away from a set of coordinates, using desired distance and angle offset.
	 * The angle offset is clockwise relative to north and is on a 360 degree scale.
	 * Example: If you want a position directly east of the given position, input 90.0f for angle.
	 * Example: If you want a position directly west of the given position, input -90.0f for angle.
	 * \param x The x-coordinate of the position we are finding a new position away from.
	 * \param y The y-coordinate of the position we are finding a new position away from.
	 * \param distance The distance away from the given position the new position will be (in meters).
	 * \param angle The clockwise direction from north we want the new position to be (in degrees).
	 * \return The Coordinate of the new position.
	 */
	Coordinate* SceneObjectImplementation::getCoordinate(float x, float y, float distance, float angle);

	/**
	 * getCoordinate Returns the coordinates of a position away from an object, using desired distance and angle offset.
	 * The angle offset is clockwise relative to the object's front surface and is on a 360 degree scale.
	 * Example: If you want a position directly to the right of a player's viewing angle, you input 90.0f for angle.
	 * Example: If you want a position directly to the left of a player's viewing angle, enter -90.0f for angle.
	 * \param object The object from which we are finding a position nearby.
	 * \param distance The distance away from the object the new position will be (in meters).
	 * \param angle The clockwise direction from the object's front surface we want the new position to be (in degrees).
	 * \return The Coordinate of the new position.
	 */
	Coordinate* getCoordinate(SceneObject* object, float distance, float angle);

	/**
	 * getCoordinate Returns the coordinates of a position directly between two objects, using distance from the first object.
	 * \param object1 The first object which we will find a new position a given distance away from, toward the second object.
	 * \param object2 The second object.
	 * \param distanceFromObject1 The distance from object1 we want the new position to be (in meters).
	 * \return The Coordinate of the new position.
	 */
	Coordinate* getCoordinate(SceneObject* object1, SceneObject* object2, float distanceFromObject1);

	bool isInRange(SceneObject* obj, float range) {
		return QuadTreeEntry::isInRange(obj->getPositionX(), obj->getPositionY(), range);
	}

	bool isInRange(float x, float y, float range) {
		return QuadTreeEntry::isInRange(x, y, range);
	}

	ZoneProcessServerImplementation* getZoneProcessServer() {
		return server;
	}

	bool isPlayer() {
		return objectType == PLAYER;
	}

	bool isNonPlayerCreature() {
		return objectType == NONPLAYERCREATURE;
	}

	bool isPlayerInventory() {
		return objectType == INVENTORYOBJECT;
	}

	bool isPlayerBankStorage() {
		return objectType == BANKINVENTORYSTORAGE;
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

	inline bool isAttackable() {
		return attackable;
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

	inline void setObjectType(int tp) {
		objectType = tp;
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

	inline float getPrecisionDirectionAngle() {
		return precisionDirectionAngle;
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

	inline UnicodeString& getCustomName() {
		return customName;
	}

	void setCustomName(const String& n) {
		customName = n;
	}

	void setCustomName(const UnicodeString& n) {
		customName = n;
	}

	inline void setTemplateName(const String& tempName) {
		templateName = tempName;
	}

	inline String& getTemplateName() {
		return templateName;
	}

	inline void setTemplateTypeName(const String& tempTypeName) {
		templateTypeName = tempTypeName;
	}

	inline String& getTemplateTypeName() {
		return templateTypeName;
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

	//Event Handlers
	virtual void onIncapacitateTarget(CreatureObject* victim);
	virtual void onInflictDamage(CreatureObject* victim, uint8 attribute, uint32 damage);
	virtual void onKill(CreatureObject* victim);
	virtual void onDeathblow(Player* victim);
	virtual void onResuscitateTarget(CreatureObject* patient);
	virtual void onHealTargetDamage(CreatureObject* patient, uint8 attribute, uint32 amount);
	virtual void onHealTargetWound(CreatureObject* patient, uint8 attribute, uint32 amount);
	virtual void onHealEnhanceTarget(CreatureObject* patient, uint8 attribute, uint32 amount, float duration);
	virtual void onReceivePaymentFrom(CreatureObject* sender, uint32 amount);

	//Actions
	virtual bool inflictDamage(CreatureObject* victim, uint8 attribute, uint32 damage);
	virtual void incapacitate(CreatureObject* victim);
	virtual void kill(CreatureObject* victim);
	virtual void deathblow(Player* victim);
	virtual void resuscitate(CreatureObject* patient, bool forced = false);
	virtual uint32 healDamage(CreatureObject* patient, uint8 attribute, uint32 amount);
	virtual uint32 healWound(CreatureObject* patient, uint8 attribute, uint32 amount);
	virtual uint32 healEnhance(CreatureObject* patient, uint8 attribute, uint32 amount, float duration);
	virtual void receivePaymentFrom(CreatureObject* sender, uint32 amount);
	virtual void warpTo(float x, float z, float y, uint64 parentID = 0);

	float calculateDistance(SceneObject* scno);

	virtual bool getPickupFlag() {
		return canPickup;
	}

	virtual void setPickupFlag(bool pickup) {
		canPickup = pickup;
	}
};

#endif /*SCENEOBJECTIMPLEMENTATION_H_*/
