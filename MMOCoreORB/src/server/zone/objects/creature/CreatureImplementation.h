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

#ifndef CREATUREIMPLEMENTATION_H_
#define CREATUREIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../db/ServerDatabase.h"

#include "../../Zone.h"

#include "../creature/CreatureObject.h"

#include "Creature.h"

#include "PatrolPoint.h"

#include "events/CreatureRemoveEvent.h"


class CreatureManagerImplementation;
class CreatureGroup;
class LairObject;
class BuildingObject;

class CreatureImplementation : public CreatureServant, public Event {
protected:
	CreatureManagerImplementation* creatureManager;

	uint64 baseID;
	int type;

	String creatureName;
	String objectFile; //object iff

	// Inherent Armor,Resists
	uint32 armor;

	float kinetic;
	float energy;
	float electricity;
	float stun;
	float blast;
	float heat;
	float cold;
	float acid;
	float lightSaber;

	Vector<PatrolPoint*> patrolPoints;

	bool doRandomMovement;

	bool hasRandomMovement;

	// misc
	CreatureGroup* creatureGroup;

	int itemShift;

	uint32 activityCount;
	uint32 highestMadeDamage;

	// stats
	int creatureState;

	ManagedReference<CreatureObject> aggroedCreature;

	bool willAggro;

	bool lootCreated;

	// Lair
	LairObject* lair;

	// movement
	PatrolPoint* nextPosition;
	float actualSpeed;

	// respawn
	PatrolPoint* spawnPosition;
	bool randomizeRespawn;
	uint32 respawnTimer;

	Vector<String> playerCanHarvest;
	CreatureRemoveEvent* creatureRemoveEvent;

	bool looted;

	uint32 fpValue;

//private:
	void broadcastNextPositionUpdate(PatrolPoint* point = NULL);
	void setNextPosition();
	void checkNewAngle(float directionangle);

	uint32 lastCamoUser;
	int camoCount;
	bool camoSet;

	void doCamoCheck(CreatureObject* target);

	bool onEscape;

public:

	const static int CREATURE = 1;
	const static int TRAINER = 2;
	const static int SHUTTLE = 3;
	const static int RECRUITER = 3;
	const static int MOUNT = 4;
	const static int CREATUREPET = 5;

	const static int ACTIVE = 1;
	const static int INACTIVE = 2;
	const static int DESPAWNING = 3;
	const static int RESPAWNING = 4;

public:
	CreatureImplementation(uint64 oid, CreatureGroup* group = NULL);

	~CreatureImplementation();

	void init();

	void reload();
	void unload();

	void scheduleDespawnCreature(int time);

	void clearLootItems();

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void generateAttributes(SceneObject* obj);

	// spatial methods

	void updateZone(bool lightUpdate = false, bool sendPackets = true);
	void updateZoneWithParent(uint64 par, bool lightUpdate = false, bool sendPackets = true);
	void updateCreaturePosition(bool lightUpdate);

	void loadItems();

	// combat methods
	bool activate();

	inline bool isActive() {
		return isQueued();
	}
	void removeFromQueue();

	bool checkState();
	void resetState();

	bool doMovement();

	void createHarvestList();
	void doStandUp();

	void notifyPositionUpdate(QuadTreeEntry* obj);

	void agro(bool all);

	void deaggro();

	void doAttack(CreatureObject* target, int damage = 1);
	bool attack(CreatureObject* target);

	void activateRecovery();
	bool doRecovery();
	void doStatesRecovery();

	void queueRespawn();

	bool shouldAgro(SceneObject * target);

	void performRandomIncapAnimation();

	CreatureObject* getAggroedCreature() {
		return aggroedCreature;
	}

	// waypoint methods
	void setPatrolPoint(PatrolPoint* cord, bool doLock = true );

	void addPatrolPoint(float x, float y, bool doLock = true);
	void addPatrolPoint(PatrolPoint* cord, bool doLock = true);
	void addPatrolPoint(SceneObject* obj, bool doLock = true);

	void addRandomPatrolPoint(float radius = 30, bool doLock = true);

	void resetPatrolPoints(bool doLock = true);

	int compareTo(Creature* creature) {
		if (objectID < creature->getObjectID())
			return 1;
		else if (objectID > creature->getObjectID())
			return -1;
		else
			return 0;
	}

	// setters and getters
	inline void setCreatureManager(CreatureManagerImplementation* mgr) {
		creatureManager = mgr;
	}

	inline void setCreatureGroup(CreatureGroup* group) {
		creatureGroup = group;
	}

	inline void setObjectFileName(const String& name) {
		objectFile = name;
	}

	inline String& getObjectFileName() {
		return objectFile;
	}

	inline void setType(int tp) {
		type = tp;
	}

	inline void setRespawnTimer(uint32 seconds) {
		respawnTimer = seconds;
	}

	inline void setCreatureState(int state) {
		creatureState = state;
	}

	inline void setLair(LairObject* Lair) {
		lair = Lair;
	}

	inline void setLootCreated(bool value) {
		lootCreated = value;
	}

	inline void setRandomMovement(bool val) {
		hasRandomMovement = val;
	}

	void setSpawnPosition(float posX, float posZ, float posY, uint64 cellid = 0) {
		spawnPosition->setPosition(posX, posZ, posY);
		spawnPosition->setCellID(cellid);
	}

	inline void setArmor(uint32 ar) {
		armor = ar;
	}

	inline void setKinetic(float kin) {
		kinetic = kin;
	}

	inline void setEnergy(float ene) {
		energy = ene;
	}

	inline void setElectricity(float ele) {
		electricity = ele;
	}

	inline void setStun(float stu) {
		stun = stu;
	}

	inline void setBlast(float bla) {
		blast = bla;
	}

	inline void setHeat(float hea) {
		heat = hea;
	}

	inline void setCold(float col) {
		cold = col;
	}

	inline void setAcid(float aci) {
		acid = aci;
	}

	inline void setLightSaber(float lig) {
		lightSaber = lig;
	}

	inline uint32 getArmor() {
		return armor;
	}

	float getArmorResist(int resistType);

	inline float getKinetic() {
		return kinetic - (kinetic * calculateBFRatio());
	}

	inline float getEnergy() {
		return energy - (energy  * calculateBFRatio());
	}

	inline float getElectricity() {
		return electricity - (electricity  * calculateBFRatio());
	}

	inline float getStun() {
		return stun - (stun * calculateBFRatio());
	}

	inline float getBlast() {
		return blast - (blast * calculateBFRatio());
	}

	inline float getHeat() {
		return heat - (heat * calculateBFRatio());
	}

	inline float getCold() {
		return cold - (cold * calculateBFRatio());
	}

	inline float getAcid() {
		return acid - (acid * calculateBFRatio());
	}

	inline float getLightSaber() {
		return lightSaber - (lightSaber * calculateBFRatio());
	}

	inline int getType() {
		return type;
	}

	inline String& getName() {
		return creatureName;
	}

	inline int getZoneIndex() {
		return zoneID;
	}

	inline Zone* getZone() {
		return zone;
	}

	/*inline String& getHairObject() {
		//return hairObject;
	}*/

	inline uint64 getNewItemID() {
		return baseID + itemShift++;
	}

	inline uint32 getRespawnTimer() {
		return respawnTimer;
	}

	inline bool isCreature() {
		return type == CREATURE;
	}

	inline bool isTrainer() {
		return type == TRAINER;
	}

	inline bool isRecruiter() {
		return type == RECRUITER;
	}

	inline bool isMount() {
		return type == MOUNT;
	}

	inline bool isInActiveState() {
		return creatureState == ACTIVE;
	}

	inline bool isDeSpawning() {
		return creatureState == DESPAWNING;
	}

	inline bool isReSpawning() {
		return creatureState == RESPAWNING;
	}

	inline LairObject* getLair() {
		return lair;
	}

	inline bool hasLootCreated() {
		return lootCreated == true;
	}

	inline bool canHarvest(String firstName) {
		if (getBoneMax() == 0 && getHideMax() == 0 && getMeatMax() == 0){
			return false;
		}

		for (int i = 0; i < playerCanHarvest.size(); ++i){

			if (playerCanHarvest.get(i) == firstName){
				return true;
			}
		}

		return false;
	}

	inline bool beenLooted(){
		return looted == true;
	}

	inline void wasLooted(){
		looted = true;
		if (playerCanHarvest.size() == 0) {

			if (server != NULL && creatureRemoveEvent != NULL && creatureRemoveEvent->isQueued())
				server->removeEvent(creatureRemoveEvent);

			scheduleDespawnCreature(500);

		}
	}

	inline void removePlayerFromHarvestList(String firstName){


		for (int i = 0; i < playerCanHarvest.size(); ++i){

			if (firstName == playerCanHarvest.get(i)){

				playerCanHarvest.remove(i);
				break;

			}

		}

		if (playerCanHarvest.size() == 0 && beenLooted()){

			server->removeEvent(creatureRemoveEvent);

			scheduleDespawnCreature(500);

		}

	}


	inline bool isMoving() {
		return actualSpeed != 0;
	}

	inline void setFPValue(uint32 value) {
		fpValue = value;
	}

	inline uint32 getFPValue() {
		return fpValue;
	}

	void activateEscapeRoute();

	//Event Handlers
	void onIncapacitateTarget(CreatureObject* victim);
	void onKilled(CreatureObject* killer);
	void onDeath();

	inline bool isOnEscape() {
		return onEscape;
	}

	inline void setOnEscape(bool escape) {
		onEscape = escape;
	}

	friend class CreatureManagerImplementation;

};

#endif /*CREATUREIMPLEMENTATION_H_*/
