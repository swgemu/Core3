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

#include "engine/engine.h"

#include "AttackableObjectImplementation.h"

#include "../../objects.h"
#include "../../packets.h"

#include "../player/Player.h"
#include "../scene/SceneObjectImplementation.h"

#include "../../Zone.h"
#include "../../ZoneClient.h"

AttackableObjectImplementation::AttackableObjectImplementation(uint64 oid) : AttackableObjectServant(oid, ATTACKABLE) {
	objectID = oid;
	inCombat = false;
}

void AttackableObjectImplementation::insertToZone(Zone* zone) {
	AttackableObjectImplementation::zone = zone;
	zoneID = zone->getZoneID();

	try {
		zone->lock();

		zone->registerObject((AttackableObject*) _this);

		zone->insert(this);
		zone->inRange(this, 128);

		zone->unlock();
	} catch (...) {
		error("exception AttackableObject::insertToZone(Zone* zone)");

		zone->unlock();
	}
}

void AttackableObjectImplementation::removeFromZone(bool dolock) {
	if (zone == NULL)
		return;

	try {
		zone->lock(dolock);

		if (parent != NULL && parent->isCell()) {
			CellObject* cell = (CellObject*) parent;
			BuildingObject* building = (BuildingObject*)parent->getParent();

			// removeFromBuilding(building);
		} else
			zone->remove(this);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);

			if (obj != this)
				obj->removeInRangeObject(this);
		}

		removeInRangeObjects();

		//TODO: deleteObject is crashing server
		//zone->deleteObject(objectID);

		zone->unlock(dolock);
	} catch (...) {
		error("exception AttackableObjectImplementation::removeFromZone(bool doLock)");

		zone->unlock(dolock);
	}
}

void AttackableObjectImplementation::setCombatState() {
	//lastCombatAction.update();
	inCombat = true;
}

void AttackableObjectImplementation::setDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	setCombatState();

	ManagedReference<SceneObject> temp = NULL;

	int i = 0;
	for (; i < defenderList.size(); i++) {
		if (defenderList.get(i) == defender) {
			if (i == 0)
				return;

			temp = defenderList.get(0);

			defenderList.set(0, defender);
			defenderList.set(i, temp);

			break;
		}
	}

	if (temp == NULL) {
		defenderList.add(defender);
	}
}

void AttackableObjectImplementation::addDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	setCombatState();

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defender == defenderList.get(i))
			return;
	}

	defenderList.add(defender);
}

void AttackableObjectImplementation::removeDefenders() {
	info("removing all defenders");
	if (defenderList.size() == 0) {
		//info("no defenders in list");
		return;
	}

	defenderList.removeAll();
}

void AttackableObjectImplementation::removeDefender(SceneObject* defender) {
	if (zone == NULL)
		return;

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender) {
			defenderList.remove(i);

			//info("removing defender");
			break;
		}
	}

	if (defenderList.size() == 0)
		clearCombatState(false);

	//info("finished removing defender");
}

bool AttackableObjectImplementation::hasDefender(SceneObject* defender) {
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender)
			return true;
	}

	return false;
}

void AttackableObjectImplementation::clearCombatState(bool removedefenders) {
	inCombat = false;

	if (removedefenders)
		removeDefenders();

	//info("finished clearCombatState");
}

void AttackableObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	BaseMessage* tano3 = new AttackableObjectMessage3((AttackableObject*) _this);
	client->sendMessage(tano3);

	BaseMessage* tano6 = new AttackableObjectMessage6((AttackableObject*) _this);
	client->sendMessage(tano6);

	UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
	client->sendMessage(msg);

	if (doClose)
		SceneObjectImplementation::close(client);
}

void AttackableObjectImplementation::doDamage(int damage, SceneObject* attacker) {
	conditionDamage = conditionDamage + damage;

	AttackableObjectDeltaMessage3* upd = new AttackableObjectDeltaMessage3((AttackableObject*) _this);
	upd->updateConditionDamage();
	upd->close();
	broadcastMessage(upd);

	if (conditionDamage >= maxCondition) {
		doDestroyed(attacker);
	}
}

void AttackableObjectImplementation::doDestroyed(SceneObject* attacker) {
	pvpStatusBitmask = 0;
	attackable = false;

	UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
	broadcastMessage(msg);

	AttackableObjectDeltaMessage3* dcreo3 = new AttackableObjectDeltaMessage3(_this);
	dcreo3->update06Operand(0x80);
	dcreo3->close();

	broadcastMessage(dcreo3);
}

void AttackableObjectImplementation::broadcastMessage(BaseMessage* msg, int range, bool doLock) {
	if (zone == NULL) {
		delete msg;
		return;
	}

	try {
		zone->lock(doLock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);
			SceneObject* object = (SceneObject*) scno->_getStub();

			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (range == 128 || isInRange(player, range) || player->getParent() != NULL) {
					//cout << "CreatureObject - sending message to player " << player->getFirstName() << "\n";
					player->sendMessage(msg->clone());
				}
			}
		}

		delete msg;

		zone->unlock(doLock);

	} catch (...) {
		error("exception AttackableObjectImplementation::broadcastMessage(Message* msg, int range, bool doLock)");

		zone->unlock(doLock);
	}
}

void AttackableObjectImplementation::sendDestroyTo(Player* player) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	destroy(client);
}
