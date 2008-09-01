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

#include "../../ZoneClient.h"
#include "../creature/CreatureObject.h"

#include "../player/Player.h"
#include "../scene/SceneObjectImplementation.h"

#include "../../Zone.h"

#include "../../packets.h"

#include "TangibleObjectImplementation.h"

#include "../building/BuildingObject.h"
#include "../building/cell/CellObject.h"


TangibleObjectImplementation::TangibleObjectImplementation(uint64 oid, int tp)
		: TangibleObjectServant(oid, TANGIBLE) {
	initialize();

	objectSubType = tp;

	pvpStatusBitmask = 0;

	playerUseMask = ALL;
}

TangibleObjectImplementation::TangibleObjectImplementation(uint64 oid, const unicode& n, const string& tempname, uint32 tempCRC, int tp)
		: TangibleObjectServant(oid, TANGIBLE) {
	initialize();

	objectCRC = tempCRC;

	name = n;

	objectSubType = tp;

	pvpStatusBitmask = 0;

	playerUseMask = ALL;
}

TangibleObjectImplementation::TangibleObjectImplementation(CreatureObject* creature, const unicode& n, const string& tempname, uint32 tempCRC, int tp)
		: TangibleObjectServant() {
	initialize();

	name = n;

	objectCRC = tempCRC;
	objectID = creature->getNewItemID();

	objectType = TANGIBLE;

	objectSubType = tp;

	playerUseMask = ALL;
}

TangibleObjectImplementation::~TangibleObjectImplementation() {
	if (container != NULL) {
		error(_this->getTemplateName() + "item still in container on delete");

		//raise(SIGSEGV);
	}

	delete itemAttributes;
	itemAttributes = NULL;

}

void TangibleObjectImplementation::initialize() {
	stringstream name;
	name << "TangibleObject :" << objectID;
	setLoggingName(name.str());

	setLogging(false);
	setGlobalLogging(true);


	container = NULL;
	zone = NULL;

	persistent = false;
	updated = false;

	building = NULL;

	objectCount = 0;

	conditionDamage = 0;
	maxCondition = 6000;

	objectType = SceneObjectImplementation::TANGIBLE;

	equipped = false;

	pvpStatusBitmask = 0;

	itemAttributes = new ItemAttributes();

}

void TangibleObjectImplementation::parseAttributes() {
	maxCondition = itemAttributes->getMaxCondition();

	conditionDamage = (maxCondition - itemAttributes->getCurrentCondition());
}

void TangibleObjectImplementation::generateSkillMods(AttributeListMessage* alm, int skillModType, int skillModValue) {
	switch (skillModType) {
	case 1:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:melee_defense", skillModValue);
		break;
	case 2:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:ranged_defense", skillModValue);
		break;
	case 3:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:stun_defense", skillModValue);
		break;
	case 4:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:dizzy_defense", skillModValue);
		break;
	case 5:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:blind_defense", skillModValue);
		break;
	case 6:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:knockdown_defense", skillModValue);
		break;
	case 7:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:intimidate_defense", skillModValue);
		break;
	case 8:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:pistol_speed", skillModValue);
		break;
	case 9:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:carbine_speed", skillModValue);
		break;
	case 10:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:rifle_speed", skillModValue);
		break;
	case 11:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:unarmed_speed", skillModValue);
		break;
	case 12:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:onehandmelee_speed", skillModValue);
		break;
	case 13:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:twohandmelee_speed", skillModValue);
		break;
	case 14:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:polearm_speed", skillModValue);
		break;
	case 15:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:pistol_accuracy", skillModValue);
		break;
	case 16:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:carbine_accuracy", skillModValue);
		break;
	case 17:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:rifle_accuracy", skillModValue);
		break;
	case 18:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:unarmed_accuracy", skillModValue);
		break;
	case 19:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:onehandmelee_accuracy", skillModValue);
		break;
	case 20:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:twohandmelee_accuracy", skillModValue);
		break;
	case 21:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:polearm_accuracy", skillModValue);
		break;
	case 22:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:dodge", skillModValue);
		break;
	case 23:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:block", skillModValue);
		break;
	case 24:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:counterattack", skillModValue);
		break;
	case 25:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_bleeding", skillModValue);
		break;
	case 26:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_disease", skillModValue);
		break;
	case 27:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_fire", skillModValue);
		break;
	case 28:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_poison", skillModValue);
		break;
	case 29:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:slope_move", skillModValue);
		break;
	case 30:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:heavyweapon_speed", skillModValue);
		break;
	case 31:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:heavyweapon_accuracy", skillModValue);
		break;
	}
}

void TangibleObjectImplementation::insertToZone(Zone* zone) {
	TangibleObjectImplementation::zone = zone;

	/*if (container != NULL) {
		if (container->isCell())
			building = (BuildingObject*) container->getParent();
	}*/

	try {
		zone->lock();

		zone->registerObject((TangibleObject*) _this);

		zone->insert(this);
		zone->inRange(this, 128);

		zone->unlock();
	} catch (...) {
		cout << "exception TangibleObject::insertToZone(Zone* zone)\n";

		zone->unlock();
	}
}

void TangibleObjectImplementation::removeFromZone() {
	if (zone == NULL)
		return;

	try {
		zone->lock();

    	for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);

			if (obj != this)
				obj->removeInRangeObject(this);
		}

		removeInRangeObjects();

		zone->remove(this);
		zone->deleteObject(objectID);

		zone->unlock();

		zone = NULL;
	} catch (...) {
		cout << "exception TangibleObject::removeFromZone(bool doLock)\n";

		zone->unlock();
	}
}

void TangibleObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (container != NULL)
		link(client, container);

	BaseMessage* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);

	BaseMessage* tano6 = new TangibleObjectMessage6((TangibleObject*) _this);
	client->sendMessage(tano6);

	if (pvpStatusBitmask != 0) {
		UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
		client->sendMessage(msg);
	}

	if (doClose)
		SceneObjectImplementation::close(client);

}

void TangibleObjectImplementation::sendDestroyTo(Player* player) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	destroy(client);
}

void TangibleObjectImplementation::sendDeltas(Player* player) {

	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);

	dtano3->setQuantity(_this->getObjectCount());
	dtano3->close();

	client->sendMessage(dtano3);

}

void TangibleObjectImplementation::close(Player* player) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::close(client);
}


void TangibleObjectImplementation::repairItem(Player* player) {
	int roll = System::random(100);

	int decayRate = 100;

	stringstream txt;

	if (roll < 10) {
		player->sendSystemMessage("You have completely failed to repair the item. The item falls apart.");
		maxCondition = 1;
		conditionDamage = 1;
		updated = true;
		return;
	} else if (roll < 75) {
		txt << "You have repaired the item, however the items maximum condition has been reduced.";
		decayRate = 20;
	} else {
		txt << "You have completely repaired the item.";
		decayRate = 0;
	}

	player->sendSystemMessage(txt.str());

	maxCondition = (maxCondition - (maxCondition / 100 * decayRate));
	conditionDamage = 0;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
	dtano3->updateConditionDamage();
	dtano3->updateMaxCondition();
	dtano3->close();
	player->broadcastMessage(dtano3);

	updated = true;
}

void TangibleObjectImplementation::decay(int decayRate) {
	conditionDamage = conditionDamage + (maxCondition / 100 * decayRate);

	if (conditionDamage > maxCondition)
		conditionDamage = maxCondition;

	updated = true;
}

void TangibleObjectImplementation::addAttributes(AttributeListMessage* alm) {
	stringstream cond;
	cond << (maxCondition-conditionDamage) << "/" << maxCondition;

	alm->insertAttribute("condition", cond);

	alm->insertAttribute("volume", "1");
}
