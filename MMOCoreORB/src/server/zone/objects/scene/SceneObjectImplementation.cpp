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

#include "../creature/skills/target/AttackTargetSkill.h"

#include "../tangible/lair/LairObject.h"

#include "../../managers/player/PlayerManager.h"

#include "../tangible/TangibleObjectImplementation.h"

SceneObjectImplementation::SceneObjectImplementation()
	: SceneObjectServant(), QuadTreeEntry(), ContainerObject(this), Logger() {
	objectID = 0;
	objectType = 0;

	server = NULL;
	zone = NULL;

	positionX = positionZ = positionY = 0;
	directionX = directionZ = directionY = 0;

	parent = NULL;

	groupDamageList.setInsertPlan(SortedVector<int>::ALLOW_OVERWRITE);
	playerDamageList.setInsertPlan(SortedVector<DamageDone>::ALLOW_OVERWRITE);

	linkType = 0x04;

	moving = false;

	undeployEvent = NULL;
	keepObject = false;

	attackable = false;
}

SceneObjectImplementation::SceneObjectImplementation(uint64 oid, int type)
	: SceneObjectServant(), QuadTreeEntry(), ContainerObject(this), Logger() {
	objectID = oid;
	objectType = type;

	StringBuffer name;
	name << "SceneObject(" << objectType << ")  0x" << hex << objectID;
	//setDeployingName(name.toString());

	server = NULL;
	zone = NULL;

	positionX = positionZ = positionY = 0;
	directionY = 1;
	directionZ = directionX = directionW = 0;

	parent = NULL;

	groupDamageList.setInsertPlan(SortedVector<int>::ALLOW_OVERWRITE);
	playerDamageList.setInsertPlan(SortedVector<DamageDone>::ALLOW_OVERWRITE);

	linkType = 0x04;

	moving = false;

	undeployEvent = NULL;
	keepObject = false;

	attackable = false;
}

SceneObjectImplementation::~SceneObjectImplementation() {
	parent = NULL;

	if (isInQuadTree()) {
		error("deleting an object that is still in QuadTree");

		StackTrace::printStackTrace();
	}

	for (int i = 0; i < playerDamageList.size(); i++) {
		VectorMapEntry<CreatureObject*, DamageDone*> *entry = playerDamageList.SortedVector<VectorMapEntry<CreatureObject*, DamageDone*>*>::get(i);
		CreatureObject *creature = entry->getKey();
		creature->release();
	}

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

	BaseMessage* msg = new UpdateContainmentMessage(_this, container, linkType);
	client->sendMessage(msg);
}

BaseMessage* SceneObjectImplementation::link(SceneObject* container, uint32 type) {
	return new UpdateContainmentMessage(objectID, container->getObjectID(), type);
}

BaseMessage* SceneObjectImplementation::link(uint64 container, uint32 type) {
	return new UpdateContainmentMessage(objectID, container, type);
}

BaseMessage* SceneObjectImplementation::link(SceneObject* container) {
	return new UpdateContainmentMessage(_this, container, linkType);
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
	//TODO:Cell permission check

	if (_this->getParent() != NULL) {
		bool cellPermission = true;

		if (_this->getParent()->isCell() && cellPermission) {
			omr->addRadialItem(0, 10, 3, "Pickup");
		}
	}

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

void SceneObjectImplementation::setLockName(const String& name) {
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
		System::out << "exception SceneObjectImplementation::insertToZone(Zone* zone)\n";

		zone->unlock();
	}
}

void SceneObjectImplementation::insertToBuilding(BuildingObject* building) {
	if (isInQuadTree() || !parent->isCell())
		return;

	try {
		//building->lock(doLock);

		info("SceneObjectImplementation::insertToBuilding");

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
		//System::out << "CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
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

					//System::out << "CreatureObject - sending message to player " << player->getFirstName() << "\n";
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

	//System::out << "finished CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
}

void SceneObjectImplementation::broadcastMessage(StandaloneBaseMessage* msg, int range, bool doLock) {
	if (zone == NULL) {
		delete msg;
		return;
	}

	try {
		//System::out << "SceneObjectImplementation::broadcastMessage(Message* msg, int range, bool doLock)\n";
		zone->lock(doLock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);
			SceneObject* object = (SceneObject*) scno->_getStub();

			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (range == 128 || isInRange(player, range) || player->getParent() != NULL) {
					//System::out << "CreatureObject - sending message to player " << player->getFirstName() << "\n";
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

	//System::out << "finished SceneObjectImplementation::broadcastMessage(Message* msg, int range, bool doLock)\n";
}

void SceneObjectImplementation::broadcastMessages(Vector<BaseMessage*>& msgs, int range, bool doLock) {
	if (zone == NULL) {
		for (int j = 0; j < msgs.size(); ++j) {
			Message* msg = msgs.get(j);
			delete msg;
		}

		msgs.removeAll();

		return;
	}

	try {
		//System::out << "CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)\n";

		zone->lock(doLock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (range == 128 || isInRange(player, range) || player->getParent() != NULL) {
					for (int j = 0; j < msgs.size(); ++j) {
						BaseMessage* msg = msgs.get(j);
						player->sendMessage(msg->clone());
					}
				}
			}
		}

		for (int j = 0; j < msgs.size(); ++j) {
			Message* msg = msgs.get(j);
			delete msg;
		}

		msgs.removeAll();

		zone->unlock(doLock);

		//System::out << "finished CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)\n";
	} catch (...) {
		error("exception CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)");

		zone->unlock(doLock);
	}
}

void SceneObjectImplementation::removeFromZone(bool doLock) {
	try {
		//System::out << "SceneObjectImplementation::removeFromZone(bool doLock) Entered" << endl;
		if (zone == NULL || !isInQuadTree())
			return;

		//System::out << "SceneObjectImplementation::removeFromZone(bool doLock) After Zone/QuadTree check" << endl;
		//deaggro();

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
		System::out << "exception SceneObjectImplementation::removeFromZone(bool doLock)\n";

		zone->unlock(doLock);
	}
}

void SceneObjectImplementation::removeFromBuilding(BuildingObject* building) {
	if (building == NULL || !isInQuadTree() || !parent->isCell())
		return;

	try {
		//building->lock(doLock);

		info("removing from building");

		broadcastMessage(link((uint64)0, (uint32)0xFFFFFFFF), 128, false);

		((CellObject*)parent)->removeChild(_this);

		building->remove(this);

		//building->unlock(doLock);
	} catch (...) {
		error("exception SceneObjectImplementation::removeFromBuilding(BuildingObject* building, bool doLock)");

		//building->unlock(doLock);
	}
}

void SceneObjectImplementation::addDamageDone(CreatureObject* creature, int damage, String skillname) {
	String xptype;

	AttackTargetSkill *askill;
	Skill *skill = server->getSkillManager()->getSkill(skillname);
	if (skill->isAttackSkill())
		askill = (AttackTargetSkill*)skill;


	switch (askill->getSkillType()) {
	case AttackTargetSkill::DEBUFF:
		return;
		break;
	case AttackTargetSkill::DIRECT:
	case AttackTargetSkill::DOT:
	case AttackTargetSkill::RANDOM:
	case AttackTargetSkill::WOUNDS:
	case AttackTargetSkill::OTHER:
		if (creature->getWeapon() == NULL)
			xptype = String("combat_meleespecialize_unarmed");
		else
			xptype = creature->getWeapon()->getXpType();
		break;
	case AttackTargetSkill::WEAPONLESS:
		xptype = "medical";
		break;
	case AttackTargetSkill::FORCE:
		xptype = "jedi_general";
		break;
	default:
		xptype = "none";
		break;
	};

	DamageDone *dmg;
	if (creature->isIncapacitated() || creature->isDead())
		return;

	if (!playerDamageList.contains(creature)) {
		creature->acquire();
		dmg = new DamageDone;
	} else
		dmg = playerDamageList.get(creature);

	if (!creature->isPlayer())
		dmg->addDamage(xptype, damage, 0);
	else {
		Player* player = (Player*)creature;
		dmg->addDamage(xptype, damage, player->calcPlayerLevel(xptype));
	}

	playerDamageList.put(creature, dmg);

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
	DamageDone* damageDone = playerDamageList.get(creature);

	if (damageDone == NULL || !creature->isCreature())
		return;

	int damage = damageDone->getTotalDamage();

	if (playerDamageList.drop(creature))
		creature->release();

	delete damageDone;

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

	for (int i = 0; i < playerDamageList.size(); i++) {
		damage += playerDamageList.get(i)->getTotalDamage();
	}

	return damage;
}

void SceneObjectImplementation::disseminateXp(int levels) {
	float total = (float)getTotalDamage();

	for (int i = 0; i < playerDamageList.size(); i++) {
		VectorMapEntry<CreatureObject*, DamageDone*> *entry = playerDamageList.SortedVector<VectorMapEntry<CreatureObject*, DamageDone*>*>::get(i);
		CreatureObject *creature = entry->getKey();
		DamageDone *dmg = entry->getValue();

		// don't do any of this if this isn't a player
		if (!creature->isPlayer()) {
			//delete dmg; ?
			continue;
		}

		Player* player = (Player*)creature;
		float xpadd = 0.0f;

		float totaldamage = (float)dmg->getTotalDamage();

		float multiplier = levels / 10.0f;
		if (multiplier > 2.5f)
			multiplier = 2.5f;
		else if (multiplier < 1.0f)
			multiplier = 1.0f;

		for ( int j = 0; j < dmg->getSize(); j++) {
			float damage = (float)dmg->getDamage(j);
			float playerlevel = (float)dmg->getLevel(j);
			String xptype = dmg->getXpType(j);
			float xpaddsingle = 0.0f;

			if (player->isInAGroup()) { // use group calculation
				GroupObject *group = player->getGroupObject();
				if (isNonPlayerCreature()) {
					xpaddsingle = (groupDamageList.get(group)/total)*(damage/totaldamage)*40.0f*((float)levels)*((multiplier)/(group->getGroupSize()))*(1.0f+((group->getGroupSize()+5.0f)*.01f));
					if (levels > 25)
						xpaddsingle += (playerlevel - levels) * 60.0f;
					else if (playerlevel > levels)
						xpaddsingle += (levels - playerlevel) * 4.5f;
				} else if (isAttackableObject()) {
					AttackableObject *attobj = (AttackableObject*)_this;
					if (attobj->getTemplateTypeName() == "lair_n") {
						LairObject *lair = (LairObject*)attobj;
						xpaddsingle = lair->getLevel() * 100 / (group->getGroupSize()) * (1.0f+((group->getGroupSize()+5.0f)*.01f));
					}
				}

			} else { // use solo calculation
				if (isNonPlayerCreature()) {
					xpaddsingle = (damage/total)*40.0f*((float)levels)*(multiplier);
					if (levels > 25)
						xpaddsingle += (playerlevel - levels) * 60.0f;
					else if (playerlevel > levels)
						xpaddsingle += (levels - playerlevel) * 4.5f;
				} else if (isAttackableObject()) {
					AttackableObject *attobj = (AttackableObject*)_this;
					if (attobj->getTemplateTypeName() == "lair_n") {
						LairObject *lair = (LairObject*)attobj;
						xpaddsingle = lair->getLevel() * 100;
					}
				}
			}

			if (xptype == "jedi_general")
				xpaddsingle /= 3.4f;

			if (xpaddsingle < 1.0f)
				xpaddsingle = 1.0f;

			PlayerManager* pmng = server->getPlayerManager();
			if (pmng != NULL)
				xpaddsingle *= pmng->getXpScale();

			player->addXp(xptype, (int)xpaddsingle, true);
			if (xptype != "jedi_general")
				xpadd += xpaddsingle;
		}

		xpadd /= 10.0f;
		String xptype = String("combat_general");
		player->addXp(xptype, (int)xpadd, true);

		//delete dmg;
	}

	cleanupDamageDone();
}

void SceneObjectImplementation::cleanupDamageDone() {
	while ( !playerDamageList.isEmpty() ) {
		VectorMapEntry<CreatureObject*, DamageDone*> *entry = playerDamageList.SortedVector<VectorMapEntry<CreatureObject*, DamageDone*>*>::get(0);
		CreatureObject *creature = entry->getKey();
		DamageDone *dmg = entry->getValue();

		if (playerDamageList.drop(creature))
			creature->release();

		delete dmg;
	}

	groupDamageList.removeAll();
}



//Event Handlers

void SceneObjectImplementation::onIncapacitateTarget(CreatureObject* victim) {

}

void SceneObjectImplementation::onInflictDamage(AttackableObject* victim, uint32 damage) {

}

void SceneObjectImplementation::onInflictDamage(CreatureObject* victim, uint8 attribute, uint32 damage) {

}

/**
 * This event handler is called after performing a deathblow on a player.
 * \param victim Victim is the target of the deathblow. Only players can be deathblown. NPC's are just killed.
 */
void SceneObjectImplementation::onDeathblow(Player* victim) {
}


/**
 * This event handler is called after killing a creature.
 * \param victim The victim of the kill.
 */
void SceneObjectImplementation::onKill(CreatureObject* victim) {
	//Award any faction points
	//Gain experienced
	clearCombatState(true);
}

/**
 * This event handler is called following receiving a payment from a creature.
 * \param sender The creature whom sent the payment.
 * \param amount The amount of the payment.
 */
void SceneObjectImplementation::onReceivePaymentFrom(CreatureObject* sender, uint32 amount) {

}



//Actions
/**
 * Action performed to inflict damage on an attackable object.
 * \param victim An attackable object that is to receive the damage.
 * \parma amount How much damage to inflict.
 */
bool SceneObjectImplementation::inflictDamage(AttackableObject* victim, uint32 damage) {
	return false;
}

/**
 * Action performed to inflict damage on a creature.
 * \param victim A creature that is to receive the damage.
 * \param attribute The attribute to inflict damage to.
 * \parma amount How much damage to inflict.
 */
bool SceneObjectImplementation::inflictDamage(CreatureObject* victim, uint8 attribute, uint32 damage) {
	if (!victim->isAttackable())
		return false;

	int32 oldValue = victim->getAttribute(attribute);
	int32 newValue = oldValue - damage;

	victim->setAttributeBar(attribute, newValue);

	if (newValue <= 0) {
		if (victim->isPlayer() || victim->isPet())
			incapacitate(victim);
		else
			kill(victim);
	}

	return true;
}

/**
 * Action performed when incapacitating a creature.
 * \param victim Creature that is being incapacitated.
 */
void SceneObjectImplementation::incapacitate(CreatureObject* victim) {
	if (!victim->isAttackable())
		return;

	onIncapacitateTarget(victim);

	if (victim->isPlayer()) {
		Player* playerVictim = (Player*) victim;
		playerVictim->onIncapacitated(_this);
	} else {
		victim->onIncapacitated(_this);
	}
}

/**
 * This action is performed when a creature deathblows a player, as opposed to a player deathblowing a player. (PlayerImplementation::deathblow() handles player to player deathblow)
 * \param victim Victim is the target of the deathblow. Only players can be deathblown. NPC's are just killed.
 */
void SceneObjectImplementation::deathblow(Player* victim) {
	onDeathblow(victim);
	try {
		unlock();
		victim->onReceiveDeathblow(_this);
		wlock(victim);
	} catch (...) {
		System::out << "Unhandled exception in SceneObjectImplementation::deathblow" << endl;
		wlock(victim);
	}
}

/**
 * Action that is performed when a creature, or player, kills a creature. Creature's can't be deathblown.
 * \param victim Victim is the target of the kill.
 */
void SceneObjectImplementation::kill(CreatureObject* victim) {
	onKill(victim);
	victim->onKilled(_this);
}

/**
 * Action that is performed when a payment has been received from a creature.
 * \param sender The creature whom sent the payment.
 * \param amount The amount the payment was for.
 */
void SceneObjectImplementation::receivePaymentFrom(CreatureObject* sender, uint32 amount) {
	onReceivePaymentFrom(sender, amount);
}

/**
 * Warps the object to the new location within the cell.
 * \param x The x coordinate to warp to.
 * \param y The y coordinate to warp to.
 * \param parentID The ID of the new cell to warp to. 0 = outside.
 */
void SceneObjectImplementation::warpTo(float x, float z, float y, uint64 parentID) {
	if (zone == NULL)
		return;

	removeFromZone();

	parent = NULL;



	if (parentID != 0) {
		setPosition(x, z, y);

		SceneObject* newParent = zone->lookupObject(parentID);

		if (newParent != NULL && newParent->isCell())
			parent = newParent;
	} else {
		setPosition(x, zone->getHeight(x, y), y);
	}

	//setIgnoreMovementTests(10);

	insertToZone(zone);
}

Coordinate* SceneObjectImplementation::getCoordinate(SceneObject* object, float distance, float angle) {
	float newX;
	float newZ;
	float newY;

	float angleRads = angle * (M_PI / 180.0f);
	float newAngle = angleRads + object->getPrecisionDirectionAngle();

	newX = object->getPositionX() + (sin(newAngle) * distance);
	newY = object->getPositionY() + (cos(newAngle) * distance);
	newZ = zone->getHeight(newX, newY);

	Coordinate* newPosition = new Coordinate(newX, newZ, newY);
	return newPosition;
}

Coordinate* SceneObjectImplementation::getCoordinate(SceneObject* object1, SceneObject* object2, float distanceFromObject1) {
	Coordinate* newPosition = new Coordinate;

	float dx = object2->getPositionX() - object1->getPositionX();
	float dy = object2->getPositionY() - object1->getPositionY();

	float distance = sqrt((dx * dx) + (dy * dy));

	if (distanceFromObject1 == 0 || distance == 0) {
		newPosition->setPosition(object1->getPositionX(), object1->getPositionZ(), object1->getPositionY());
		return newPosition;

	} else if (distance < distanceFromObject1) {
		newPosition->setPosition(object2->getPositionX(), object2->getPositionZ(), object2->getPositionY());
		return newPosition;
	}

	float newPositionX = object1->getPositionX() + (distanceFromObject1 * (dx / distance));
	float newPositionY = object1->getPositionY() + (distanceFromObject1 * (dy / distance));
	float newPositionZ = zone->getHeight(newPositionX, newPositionY);

	newPosition->setPosition(newPositionX, newPositionZ, newPositionY);

	return newPosition;
}

float SceneObjectImplementation::calculateDistance(SceneObject* scno) {
	return (sqrt(pow(getPositionX() - scno->getPositionX(), 2) + pow(getPositionY() - scno->getPositionY(), 2)));
}
