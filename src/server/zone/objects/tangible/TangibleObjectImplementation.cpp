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

#include "../../ZoneClientSession.h"

#include "../../Zone.h"

#include "../../objects.h"
#include "../../packets.h"

TangibleObjectImplementation::TangibleObjectImplementation(uint64 oid, int tp)
		: TangibleObjectServant(oid, TANGIBLE) {

	init();

	if (tp == NONPLAYERCREATURE || tp == PLAYER)
		objectType = tp;

	objectSubType = tp;

	pvpStatusBitmask = 0;

	playerUseMask = ALL;

	optionsBitmask = 0;
}

TangibleObjectImplementation::TangibleObjectImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempname, int tp)
		: TangibleObjectServant(oid, TANGIBLE) {

	init();

	objectCRC = tempCRC;

	customName = n;

	stfName = tempname;

	objectSubType = tp;

	pvpStatusBitmask = 0;

	playerUseMask = ALL;

	optionsBitmask = 0;
}

TangibleObjectImplementation::TangibleObjectImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempname, int tp)
		: TangibleObjectServant() {

	init();

	customName = n;

	objectCRC = tempCRC;
	stfName = tempname;
	objectID = creature->getNewItemID();

	objectType = TANGIBLE;

	objectSubType = tp;

	playerUseMask = ALL;

	optionsBitmask = 0;
}

TangibleObjectImplementation::~TangibleObjectImplementation() {
	if (parent != NULL && !isPlayer() && !isNonPlayerCreature()) {
		error(_this->getStfName() + "item still in container on delete");

		StackTrace::printStackTrace();

		//raise(SIGSEGV);
	}

	delete itemAttributes;

	itemAttributes = NULL;
}

void TangibleObjectImplementation::init() {
	StringBuffer name;
	name << "TangibleObject :" << objectID;
	setLoggingName(name.toString());

	setLogging(false);
	setGlobalLogging(true);

	zone = NULL;

	complexity = 100.f;

	defenderUpdateCounter = 0;
	inCombat = false;
	attackable = false;

	unknownByte = 1;

	volume = 1;

	persistent = false;
	updated = false;

	objectCount = 0;

	conditionDamage = 0;
	maxCondition = 6000;

	objectType = TANGIBLE;

	equipped = false;

	wasLooted = false;

	pvpStatusBitmask = 0;

	firstCraftingUpdate = true;

	setLoot(false);

	setSliced(false);
	setSlicable(false);
	setSlicerID(0);
}

void TangibleObjectImplementation::parseAttributes() {
	maxCondition = itemAttributes->getMaxCondition();

	conditionDamage = (maxCondition - itemAttributes->getCurrentCondition());
}

void TangibleObjectImplementation::parseItemAttributes() {
	String attr = "craftersname";
	setCraftersName(itemAttributes->getStringAttribute(attr));

	attr = "craftedserial";
	setCraftedSerial(itemAttributes->getStringAttribute(attr));

	attr = "looted";
	setLoot(itemAttributes->getBooleanAttribute(attr));

	attr = "sliced";
	setSliced(itemAttributes->getBooleanAttribute(attr));

	attr = "slicable";
	setSlicable(itemAttributes->getBooleanAttribute(attr));

	attr = "slicerID";
	setSlicerID(itemAttributes->getUnsignedLongAttribute(attr));

	attr = "objectcount";
	setObjectCount(itemAttributes->getIntAttribute(attr));
}

void TangibleObjectImplementation::synchronizedUIListen(Player* player, int value) {

	// Send TANO7 Baseline
	TangibleObjectMessage7* tano7 = new TangibleObjectMessage7(_this);
	player->sendMessage(tano7);
}

void TangibleObjectImplementation::synchronizedUIStopListen(Player* player, int value) {

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

void TangibleObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (parent != NULL)
		link(client, parent);

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
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	destroy(client);
}

void TangibleObjectImplementation::sendDeltas(Player* player) {

	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);

	dtano3->setQuantity(_this->getObjectCount());
	dtano3->close();

	client->sendMessage(dtano3);

}

void TangibleObjectImplementation::close(Player* player) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::close(client);
}

void TangibleObjectImplementation::setDefender(SceneObject* defender) {
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

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6((TangibleObject*) _this);

	if (temp != NULL) {
		dtano6->startDefenderUpdate(2);
		dtano6->setDefender(i, temp->getObjectID());
		dtano6->setDefender(0, defender->getObjectID());
	} else {
		dtano6->startDefenderUpdate(1);
		dtano6->addDefender(defenderList.size(), defender->getObjectID());

		defenderList.add(defender);
	}

	dtano6->close();

	broadcastMessage(dtano6);
}

void TangibleObjectImplementation::addDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	setCombatState();

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defender == defenderList.get(i))
			return;
	}

	info("adding defender");

	defenderList.add(defender);

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6((TangibleObject*) _this);
	dtano6->startDefenderUpdate(1);
	dtano6->addDefender(defenderList.size() - 1, defender->getObjectID());
	dtano6->close();

	broadcastMessage(dtano6);
}

void TangibleObjectImplementation::removeDefenders() {
	//info("removing all defenders");
	if (defenderList.size() == 0) {
		//info("no defenders in list");
		return;
	}

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6((TangibleObject*) _this);
	dtano6->startDefenderUpdate(1);

	dtano6->removeDefenders();
	dtano6->close();

	broadcastMessage(dtano6);

	defenderList.removeAll();

	//info("removed all defenders");
}

void TangibleObjectImplementation::removeDefender(SceneObject* defender) {
	if (zone == NULL)
		return;

	//info("trying to remove defender");
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender) {
			defenderList.remove(i);

			info("removing defender");

			TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6((TangibleObject*) _this);
			dtano6->startDefenderUpdate(1);

			if (defenderList.size() == 0)
				dtano6->removeDefenders();
			else
				dtano6->removeDefender(i);

			dtano6->close();

			broadcastMessage(dtano6);

			//info("defender found and removed");
			break;
		}
	}

	if (defenderList.size() == 0)
		clearCombatState(false);

	//info("finished removing defender");
}

bool TangibleObjectImplementation::hasDefender(SceneObject* defender) {
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender)
			return true;
	}
	return false;
}

void TangibleObjectImplementation::setCombatState() {
	//lastCombatAction.update();
	inCombat = true;
}

void TangibleObjectImplementation::clearCombatState(bool removedefenders) {
	inCombat = false;

	if (removedefenders)
		removeDefenders();

	//info("finished clearCombatState");
}

void TangibleObjectImplementation::doDamage(int damage, SceneObject* attacker) {
	conditionDamage = conditionDamage + damage;

	TangibleObjectDeltaMessage3* upd = new TangibleObjectDeltaMessage3((TangibleObject*) _this);
	upd->updateConditionDamage();
	upd->close();
	broadcastMessage(upd);

	if (conditionDamage >= maxCondition) {
		doDestroyed(attacker);
	}
}

void TangibleObjectImplementation::onReceiveDamage(SceneObject* attacker, uint32 amount) {

}

void TangibleObjectImplementation::doDestroyed(SceneObject* attacker) {
	pvpStatusBitmask = 0;
	attackable = false;
	optionsBitmask = 0x80;

	UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
	broadcastMessage(msg);

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
	dtano3->updateOptionsBitmask();
	dtano3->close();

	broadcastMessage(dtano3);
}


void TangibleObjectImplementation::repairItem(Player* player) {
	//TODO: Should master weaponsmith or armorsmith get a bonus to repair?

	if (getCondition() == getMaxCondition()) {
		//TODO: This will never get called after this is moved to the sui list box and referenced through the repair kits.
		player->sendSystemMessage("That item is not in need of repair.");
		return;
	}

	//Condition is unrepairable
	if (getCondition() <= 0) {
		StfParameter* params = new StfParameter();
		params->addTT(getObjectID());
		player->sendSystemMessage("error_message", "sys_repair_unrepairable", params); //%TT's condition is beyond repair even for your skills.
		delete params;
		return;
	}

	float conditionRatio = getConditionDamage() / getMaxCondition();

	//We subtract the conditionRatio from a random roll of 0 to 100.
	int32 roll = (int32) ceil(System::random(100) - (conditionRatio / 3));

	//Gate our roll at 0.
	roll = (roll >= 0) ? roll : 0;

	float repairRate = 1.0f;

	if (roll >= 75) {
		player->sendSystemMessage("error_message", "sys_repair_perfect"); //You have repaired the item with only minor blemishes.
	} else if (roll >= 50) {
		player->sendSystemMessage("error_message", "sys_repair_slight"); //You have repaired the item, however the item's maximum condition has been reduced.
		repairRate = 0.75f; //75% repair
	} else if (roll >= 25) {
		player->sendSystemMessage("error_message", "sys_repair_imperfect"); //You have only marginally repaired the item. The item's max condition has been reduced.
		repairRate = 0.50f; //50% repair
	} else {
		player->sendSystemMessage("error_message", "sys_repair_failed"); //You have completely failed to repair the item. The item falls apart.
		repairRate = 0.0f; //0% repair

		if (isWeapon())
			((Weapon*)_this)->onBroken();

		if (isArmor())
			((Armor*)_this)->onBroken();
	}

	//Gate our new max condition at 1
	int newMaxCondition = (int) ceil(((float) getMaxCondition()) * repairRate);
	setMaxCondition((newMaxCondition > 1) ? newMaxCondition : 1);

	setConditionDamage(0);

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
	dtano3->updateConditionDamage();
	dtano3->updateMaxCondition();
	dtano3->close();
	player->broadcastMessage(dtano3);

	updated = true;
}

void TangibleObjectImplementation::setObjectName(Player * player) {
	try {
		//player->wlock();
		player->setCurrentStructureID(this->getObjectID());
		//player->unlock();

		SuiInputBox * setTheName = new SuiInputBox(player, SuiWindowType::REMOVE_FROM_GUILD, 0x00);

		setTheName->setPromptTitle("Name the Object");
		setTheName->setPromptText("Please enter the new name you would like for this object");

		player->addSuiBox(setTheName);
		player->sendMessage(setTheName->generateMessage());

	}
	catch(...) {
		System::out << "Unreported exception in TangibleObjectImplementation::setObjectName\n";
		//player->unlock();
	}
}

void TangibleObjectImplementation::addAttributes(AttributeListMessage* alm) {
	StringBuffer cond;
	cond << (maxCondition-conditionDamage) << "/" << maxCondition;

	alm->insertAttribute("condition", cond);

	alm->insertAttribute("volume", "1");
}



//Sending of Messages

/**
 * Sends the delta packet to the player updating this items optionsBitmask
 */
void TangibleObjectImplementation::updateOptionsBitmask(Player* player) {
	TangibleObjectDeltaMessage3* tanod3 = new TangibleObjectDeltaMessage3(_this);
	tanod3->updateOptionsBitmask();
	tanod3->close();
	player->sendMessage(tanod3);
}

void TangibleObjectImplementation::updateInsurance(Player* player, bool insure) {
	setInsured(insure);
	updateOptionsBitmask(player);
}

//Event Handlers
void TangibleObjectImplementation::onBroken() {

}

void TangibleObjectImplementation::onSlicingFailure(Player* slicer) {

}

//Actions
void TangibleObjectImplementation::decay(float decayRate) {
	if (isInsured())
		setInsured(false);

	conditionDamage += (int) floor((float) maxCondition * decayRate);

	if (conditionDamage > maxCondition)
		conditionDamage = maxCondition;

	updated = true;
}

void TangibleObjectImplementation::slice(Player* slicer) {

}
