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

#include "../../../ServerCore.h"

#include "../../ZoneClientSession.h"

#include "../../ZoneProcessServerImplementation.h"

#include "../../Zone.h"

#include "../../packets.h"

#include "../tangible/weapons/WeaponImplementation.h"

#include "SceneObjectImplementation.h"

#include "engine/core/ManagedObjectImplementation.h"

#include "../building/cell/CellObject.h"

SceneObjectImplementation::SceneObjectImplementation() : SceneObjectServant(), QuadTreeEntry(), Logger() {
	objectID = 0;
	objectType = 0;

	server = NULL;
	zone = NULL;

	positionX = positionZ = positionY = 0;
	directionX = directionZ = directionY = 0;

	parent = NULL;
	
	weaponDamageList.setInsertPlan(SortedVector<int>::ALLOW_OVERWRITE);
	weaponCreatureList.setInsertPlan(SortedVector<Creature*>::ALLOW_OVERWRITE);
	groupDamageList.setInsertPlan(SortedVector<int>::ALLOW_OVERWRITE);

	linkType = 0x04;

	moving = false;

	undeployEvent = NULL;
	keepObject = false;
}

SceneObjectImplementation::SceneObjectImplementation(uint64 oid, int type) : SceneObjectServant(),QuadTreeEntry(), Logger() {
	objectID = oid;
	objectType = type;

	stringstream name;
	name << "SceneObject(" << objectType << ")  0x" << hex << objectID;
	//setDeployingName(name.str());

	server = NULL;
	zone = NULL;

	positionX = positionZ = positionY = 0;
	directionY = 1;
	directionZ = directionX = directionW = 0;

	parent = NULL;
	
	weaponDamageList.setInsertPlan(SortedVector<int>::ALLOW_OVERWRITE);
	weaponCreatureList.setInsertPlan(SortedVector<Creature*>::ALLOW_OVERWRITE);
	groupDamageList.setInsertPlan(SortedVector<int>::ALLOW_OVERWRITE);

	linkType = 0x04;

	moving = false;

	undeployEvent = NULL;
	keepObject = false;
}

SceneObjectImplementation::~SceneObjectImplementation() {
	parent = NULL;

	undeploy();
}

bool SceneObject::destroy() {
	bool destroying = ServerCore::getZoneServer()->destroyObject(this);

	if (destroying) {
		//info("destroying object");

		delete this;
	}

	return destroying;
}

bool SceneObjectImplementation::destroy() {
	return _this->destroy();
}

void SceneObjectImplementation::redeploy() {
	info("redeploying object");

	_this->revoke();

	removeUndeploymentEvent();
}

void SceneObjectImplementation::scheduleUndeploy() {
	if (undeployEvent == NULL && !keepObject && server != NULL) {
		info("scheduling uneploy");

		undeployEvent = new UndeploySceneObjectEvent(_this);
		server->addEvent(undeployEvent);
	}
}

void SceneObjectImplementation::undeploy() {
	if (isInQuadTree()) {
		error("Deleting scene object that is in QT");
		raise(SIGSEGV);
	}

	removeUndeploymentEvent();

	/*if (zone != NULL)
		//zone->deleteObject(_this);
		error("object is still in Zone");*/
}

void SceneObjectImplementation::removeUndeploymentEvent() {
	if (undeployEvent != NULL) {
		server->removeEvent(undeployEvent);

		delete undeployEvent;
		undeployEvent = NULL;
	}
}

void SceneObjectImplementation::create(ZoneClientSession* client) {
	BaseMessage* msg = new SceneObjectCreateMessage(_this);

	client->sendMessage(msg);
}

void SceneObjectImplementation::link(ZoneClientSession* client, SceneObject* container) {
	if (client == NULL)
		return;

	parent = container;

	BaseMessage* msg = new UpdateContainmentMessage(container, _this, linkType);
	client->sendMessage(msg);
}

BaseMessage* SceneObjectImplementation::link(uint64 container, uint32 type) {
	return new UpdateContainmentMessage(objectID, container, type);
}

BaseMessage* SceneObjectImplementation::link(SceneObject* container) {
	return new UpdateContainmentMessage(container, _this, linkType);
}

void SceneObjectImplementation::close(ZoneClientSession* client) {
	if (client == NULL)
		return;

	BaseMessage* msg = new SceneObjectCloseMessage(_this);
	client->sendMessage(msg);
}

void SceneObjectImplementation::destroy(ZoneClientSession* client) {
	if (client == NULL)
		return;

	BaseMessage* msg = new SceneObjectDestroyMessage(_this);
	client->sendMessage(msg);
}

void SceneObjectImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage(_this);
	player->sendMessage(alm);
}

void SceneObjectImplementation::randomizePosition(float radius) {
	Coordinate::randomizePosition(radius);

	previousPositionZ = positionZ;

	if (zone != NULL)
		positionZ = zone->getHeight(positionX, positionY);
	else
		positionZ = 0;

}

void SceneObjectImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	omr->finish();

	player->sendMessage(omr);
}

void SceneObjectImplementation::lock(bool doLock) {
	ManagedObjectImplementation::wlock(doLock);
}

void SceneObjectImplementation::lock(ManagedObject* obj) {
	ManagedObjectImplementation::wlock(obj);
}

void SceneObjectImplementation::wlock(bool doLock) {
	ManagedObjectImplementation::wlock(doLock);
}

void SceneObjectImplementation::wlock(ManagedObject* obj) {
	ManagedObjectImplementation::wlock(obj);
}

void SceneObjectImplementation::unlock(bool doLock) {
	ManagedObjectImplementation::unlock(doLock);
}

void SceneObjectImplementation::setLockName(const string& name) {
	//ManagedObjectImplementation::setLockName(name);
}

void SceneObjectImplementation::insertToZone(Zone* zone) {
	SceneObjectImplementation::zone = zone;
	zoneID = zone->getZoneID();

	try {
		zone->lock();

		zone->registerObject(_this);

		if (parent != NULL && parent->isCell()) {
			BuildingObject* building = (BuildingObject*)parent->getParent();

			insertToBuilding(building);

			building->notifyInsertToZone(_this);
		} else {
			zone->insert(this);
			zone->inRange(this, 128);

			/*for (int i = 0; i < inRangeObjectCount(); ++i) {  // eats all the cpu
				QuadTreeEntry* obj = getInRangeObject(i);
				SceneObjectImplementation* objImpl = (SceneObjectImplementation*) obj;

				obj->notifyPositionUpdate(this);
				this->notifyPositionUpdate(obj);
			}*/
		}

		zone->unlock();
	} catch (...) {
		cout << "exception SceneObjectImplementation::insertToZone(Zone* zone)\n";

		zone->unlock();
	}
}

void SceneObjectImplementation::insertToBuilding(BuildingObject* building) {
	if (isInQuadTree() || !parent->isCell())
		return;

	try {
		//building->lock(doLock);

		info("inserting to building");

		((CellObject*)parent)->addChild(_this);

		building->insert(this);
		building->inRange(this, 128);

		//building->unlock(doLock);

		linkType = 0xFFFFFFFF;
		broadcastMessage(link(parent), 128, false);

	} catch (...) {
		error("exception SceneObjectImplementation::insertToBuilding(BuildingObject* building)");

		//building->unlock(doLock);
	}
}

void SceneObjectImplementation::broadcastMessage(BaseMessage* msg, int range, bool doLock, bool sendSelf) {
	if (zone == NULL) {
		delete msg;
		return;
	}

	try {
		//cout << "CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
		zone->lock(doLock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);
			SceneObject* object = (SceneObject*) scno->_getStub();

			if (object->isPlayer()) {
				Player* player = (Player*) object;

                if (range == 128 || isInRange(player, range) || player->getParent() != NULL) { 
                    if (this->isPlayer()) { 
                        Player* sender = (Player*) this->_getStub(); 
            			if (!sendSelf && (player == sender)) 
                			continue; 
                    }
					//cout << "CreatureObject - sending message to player " << player->getFirstName() << "\n";
					player->sendMessage(msg->clone());
				}
			}
		}

		delete msg;

		zone->unlock(doLock);

	} catch (...) {
		error("exception SceneObject::broadcastMessage(Message* msg, int range, bool doLock)");

		zone->unlock(doLock);
	}

	//cout << "finished CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
}

void SceneObjectImplementation::broadcastMessage(StandaloneBaseMessage* msg, int range, bool doLock) {
	if (zone == NULL) {
		delete msg;
		return;
	}

	try {
		//cout << "SceneObjectImplementation::broadcastMessage(Message* msg, int range, bool doLock)\n";
		zone->lock(doLock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);
			SceneObject* object = (SceneObject*) scno->_getStub();

			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (range == 128 || isInRange(player, range) || player->getParent() != NULL) {
					//cout << "CreatureObject - sending message to player " << player->getFirstName() << "\n";
					player->sendMessage((StandaloneBaseMessage*)msg->clone());
				}
			}
		}

		delete msg;

		zone->unlock(doLock);

	} catch (...) {
		error("exception SceneObjectImplementation::broadcastMessage(Message* msg, int range, bool doLock)");

		zone->unlock(doLock);
	}

	//cout << "finished SceneObjectImplementation::broadcastMessage(Message* msg, int range, bool doLock)\n";
}

void SceneObjectImplementation::removeFromZone(bool doLock) {
	try {
		//cout << "SceneObjectImplementation::removeFromZone(bool doLock) Entered" << endl;
		if (zone == NULL || !isInQuadTree())
			return;

		//cout << "SceneObjectImplementation::removeFromZone(bool doLock) After Zone/QuadTree check" << endl;
		//deagro();

		zone->lock(doLock);

		if (parent != NULL && parent->isCell()) {
			CellObject* cell = (CellObject*) parent;
			BuildingObject* building = (BuildingObject*)parent->getParent();

			removeFromBuilding(building);
		} else
			zone->remove(this);

    	for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);

			if (obj != this)
				obj->removeInRangeObject(this);
		}

		removeInRangeObjects();

		zone->deleteObject(objectID);

		zone->unlock(doLock);
	} catch (...) {
		cout << "exception SceneObjectImplementation::removeFromZone(bool doLock)\n";

		zone->unlock(doLock);
	}
}

void SceneObjectImplementation::removeFromBuilding(BuildingObject* building) {
	if (building == NULL || !isInQuadTree() || !parent->isCell())
		return;

	try {
		//building->lock(doLock);

		info("removing from building");

		broadcastMessage(link(0, 0xFFFFFFFF), 128, false);

		((CellObject*)parent)->removeChild(_this);

		building->remove(this);

		//building->unlock(doLock);
	} catch (...) {
		error("exception SceneObjectImplementation::removeFromBuilding(BuildingObject* building, bool doLock)");

		//building->unlock(doLock);
	}
}

void SceneObjectImplementation::addDamageDone(CreatureObject* creature, int damage) {
	//Weapon *weap = creature->getWeapon();
	uint64 weapid;
	if (creature->getWeapon() == NULL)
		weapid = creature->getObjectID();
	else
		weapid = creature->getWeapon()->getObjectID();
			
	if (weaponDamageList.contains(weapid)) {
		int newdamage = weaponDamageList.get(weapid);
		newdamage += damage;
		weaponDamageList.drop(weapid);
		weaponDamageList.put(weapid, newdamage);
		
		// shouldn't happen
		if (!weaponCreatureList.contains(weapid) || weaponCreatureList.get(weapid) != creature)
			weaponCreatureList.put(weapid, creature);
	} else {
		weaponDamageList.put(weapid, damage);
		weaponCreatureList.put(weapid, creature);
	}
	
	if (creature->isInAGroup() && creature->isPlayer()) {
		Player *player = (Player*)creature;
		GroupObject *group = player->getGroupObject();
		if (groupDamageList.contains(group)) {
			int groupdamage = groupDamageList.get(group);
			groupdamage += damage;
			groupDamageList.drop(group);
			groupDamageList.put(group, groupdamage);
		} else {
			groupDamageList.put(group, damage);
		}
	}
}

void SceneObjectImplementation::dropDamageDone(CreatureObject* creature) {
	int damage = 0;
	//Weapon *weap = creature->getWeapon();
	uint64 weapid;
	if (creature->getWeapon() == NULL)
		weapid = creature->getObjectID();
	else
		weapid = creature->getWeapon()->getObjectID();
	
	for (int i = 0; i < weaponCreatureList.size(); i++) {
		VectorMapEntry<uint64, CreatureObject*> *entry = weaponCreatureList.SortedVector<VectorMapEntry<uint64, CreatureObject*>*>::get(i);
		if (entry->getValue() == creature) {
			damage += weaponDamageList.get(weapid);
			weaponCreatureList.drop(entry->getKey());
			weaponDamageList.drop(entry->getKey());
		}
	}
	
	if (creature->isInAGroup() && creature->isPlayer()) {
		Player *player = (Player*)creature;
		GroupObject *group = player->getGroupObject();
		
		if (groupDamageList.contains(group)) {
			int groupdamage = groupDamageList.get(group);
			groupdamage -= damage;
			groupDamageList.drop(group);
			groupDamageList.put(group, groupdamage);
		}
	}	

}

int SceneObjectImplementation::getTotalDamage() {
	int damage = 0;
	
	for (int i = 0; i < weaponDamageList.size(); i++) {
		damage += weaponDamageList.get(i);
	}
	
	return damage;
}

void SceneObjectImplementation::disseminateXp(int levels) {
	VectorMap<Player*, int> playerxp;
	playerxp.setInsertPlan(SortedVector<int>::ALLOW_OVERWRITE);
	int total = getTotalDamage();
	
	for (int i = 0; i < weaponDamageList.size(); i++) {
		VectorMapEntry<uint64, int> *entry = weaponDamageList.SortedVector<VectorMapEntry<uint64, int>*>::get(i);
		CreatureObject *creature = weaponCreatureList.get(entry->getKey());
		
		// don't do any of this if this isn't a player
		if (!creature->isPlayer())
			continue;
		
		Player* player = (Player*)creature;
			
		int totaldamage = 0;
		for (int k = 0; k < weaponCreatureList.size(); k++) {
			if (weaponCreatureList.get(k) == creature) {
				VectorMapEntry<uint64, CreatureObject*> *crentry = weaponCreatureList.SortedVector<VectorMapEntry<uint64, CreatureObject*>*>::get(k);
				totaldamage += weaponDamageList.get(crentry->getKey());
			}
		}
		
		SceneObject* sco = zone->lookupObject(entry->getKey());
		Weapon* weap;
		
		if (sco == NULL)
			sco = player->getPlayerItem(entry->getKey());
			
		if (sco == NULL)
			continue;
		
		if ( sco->isTangible() ) {
			TangibleObject *tano = (TangibleObject*)sco;
			if (tano->isWeapon()) {
				weap = (Weapon*)tano;
			}
		} else if ( sco->isPlayer() ) {
			weap = NULL;
		} else
			continue;
			
		string xptype;
		if (weap == NULL)
			xptype = "combat_meleespecialize_unarmed";
		else
			xptype =(weap->getXpType());
		int damage = entry->getValue();
		float xpadd = 0.0f;
		
		int playerlevel = player->getPlayerLevel();
		cout << playerlevel << endl;
		//int multiplier = 1;
		//if (playerlevel > 10) 
		//	multiplier = playerlevel / 10;
		float multiplier = levels / 10.0f;
		if (multiplier > 2.5f)
			multiplier = 2.5f;
		else if (multiplier < 1.0f)
			multiplier = 1.0f;
			
		
		
		//40xpl(cl/25)(pl/10)
		//40*(cl) * (cl/10)
		if (player->isInAGroup()) { // use group calculation
			GroupObject *group = player->getGroupObject();
			if (isNonPlayerCreature()) {
				xpadd = ceil((1-(total-groupDamageList.get(group))/total)*(1-(totaldamage-damage)/totaldamage)*40*(levels)*(multiplier)*(1+(group->getGroupSize()+5)*.01));
				if (levels > 25)
					xpadd += (playerlevel - levels) * 60;
				else if (playerlevel > levels)
					xpadd += (levels - playerlevel) * 4.5;
				if (xptype == "jedi_general" || xptype == "combat_meleespecialize_onehandlightsaber" || xptype == "combat_meleespecialize_twohandlightsaber" || xptype == "combat_meleespecialize_polearmlightsaber")
					xpadd /= 3.4f;
			}
		} else { // use solo calculation
			if (isNonPlayerCreature()) {
				xpadd = ceil((1-(total-damage)/total)*40*(levels)*(multiplier));
				if (levels > 25)
					xpadd += (playerlevel - levels) * 60;
				else if (playerlevel > levels)
					xpadd += (levels - playerlevel) * 4.5;
				if (xptype == "jedi_general" || xptype == "combat_meleespecialize_onehandlightsaber" || xptype == "combat_meleespecialize_twohandlightsaber" || xptype == "combat_meleespecialize_polearmlightsaber")
					xpadd /= 3.4f;
			}
		}
		
		if (xpadd < 1)
			xpadd = 1;
		
		player->addXp(xptype, (int)xpadd, true);
		
		if (playerxp.contains(player)) {
			int xptemp = playerxp.get(player);
			playerxp.drop(player);
			playerxp.put(player, xptemp);
		} else
			playerxp.put(player, (int)xpadd);
	}
	
	for (int j = 0; j < playerxp.size(); j++) {
		VectorMapEntry<Player*, int> *entry = playerxp.SortedVector<VectorMapEntry<Player*, int>*>::get(j);
		Player *player = entry->getKey();
		int xp = entry->getValue();
		string combatxp("combat_general");
		
		player->addXp(combatxp, xp/10, true);
	}
}
