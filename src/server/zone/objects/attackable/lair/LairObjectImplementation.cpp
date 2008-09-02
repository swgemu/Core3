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

#include "LairObjectImplementation.h"

#include "../AttackableObjectImplementation.h"
#include "../../scene/SceneObjectImplementation.h"

LairObjectImplementation::LairObjectImplementation(uint32 objCRC, uint64 oid)
	: LairObjectServant(oid) {

	objectCRC = objCRC;


	conditionDamage = 0;
	maxCondition = 20000;

	templateTypeName = "lair_n";

	name = unicode("");

	string templateDetailName = "lair_d";

	objectType = ATTACKABLE;
	pvpStatusBitmask = 1;
	attackable = true;

	creatureCRC = 0;
	string creatureName = "dewback";
	string creatureStfName = "a Dewback";

	spawnSize = 0;
	babiesPerMillion = 0;

	spawn1 = false;
	spawn2 = false;
}

void LairObjectImplementation::doDamage(int damage, SceneObject* attacker) {
	if (!attackable)
		return;

	conditionDamage = conditionDamage + damage;

	if ((conditionDamage >= maxCondition / 20) && !spawn1) {
		spawn1 = true;
		spawnCreatures();
	} else if ((conditionDamage >= maxCondition / 2) && !spawn2) {
		spawn2 = true;
		spawnCreatures();
	}

	AttackableObjectDeltaMessage3* upd = new AttackableObjectDeltaMessage3((AttackableObject*) _this);
	upd->updateConditionDamage();
	upd->close();
	broadcastMessage(upd);

	if (conditionDamage >= maxCondition) {
		doDestroyed(attacker);
	}
}

void LairObjectImplementation::spawnCreatures() {

	if (zone == NULL) {
		cout << "Zone is NULL" << endl;
		return;
	}

	CreatureManager* creatureManager = zone->getCreatureManager();

	for (int i = 0; i < spawnSize; i++) {

		bool baby = false;
		if (System::random(1000000) < babiesPerMillion) {
			baby = true;
		}

		int bitmask = 1;
		float x = positionX + (30.0f - System::random(600) / 10.0f);
		float y = positionY + (30.0f - System::random(600) / 10.0f);

		Creature* creature = creatureManager->spawnCreature(creatureCRC, 0, x, y, bitmask, baby, false);
		creatures.add(creature);

		try {
			creature->wlock(_this);

			for (int i = 0; i < defenderList.size(); i++) {
				creature->addDefender(defenderList.get(i));
			}

			creature->unlock();

		} catch (...) {
			creature->unlock();
		}
	}
}

void LairObjectImplementation::addDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	setCombatState();

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defender == defenderList.get(i))
			return;
	}

	defenderList.add(defender);

	for (int i = 0; i < creatures.size(); i++) {
		Creature* creature = creatures.get(i);

		try {
			creature->wlock(_this);

			creature->addDefender(defender);

			creature->unlock();
		} catch (...) {
			creature->unlock();
		}
	}
}

void LairObjectImplementation::doDestroyed(SceneObject* attacker) {
	pvpStatusBitmask = 0x20;
	attackable = false;

	AttackableObjectDeltaMessage3* dcreo3 = new AttackableObjectDeltaMessage3(_this);
	dcreo3->update06Operand(0x80);
	dcreo3->close();

	broadcastMessage(dcreo3);

	string explodeStr = "clienteffect/lair_damage_heavy.cef";
	string extraStr = "";

	PlayClientEffectObjectMessage* explode = new PlayClientEffectObjectMessage(_this, explodeStr, extraStr);
	broadcastMessage(explode);

	PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc(explodeStr, zoneID, positionX, positionZ, positionY);
	broadcastMessage(explodeLoc);

	UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
	broadcastMessage(msg);

	SceneObjectDestroyMessage* destroyMsg = new SceneObjectDestroyMessage(_this);
	broadcastMessage(destroyMsg);

	for (int i = 0; i < defenderList.size(); i++) {
		SceneObject* obj = defenderList.get(i);

		try {
			if (obj != attacker)
				obj->wlock(_this);

			obj->removeDefender(_this);

			if (obj != attacker)
				obj->unlock();
		} catch (...) {
			if (obj != attacker)
				obj->unlock();
		}
	}

	removeFromZone(true);
}
