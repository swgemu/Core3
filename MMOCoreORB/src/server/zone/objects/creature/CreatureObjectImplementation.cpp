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

#include "CreatureObject.h"
#include "CreatureState.h"
#include "CreatureFlag.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/professions/ProfessionManager.h"
#include "server/zone/ZoneClientSession.h"
#include "server/zone/packets/creature/CreatureObjectMessage1.h"
#include "server/zone/packets/creature/CreatureObjectMessage3.h"
#include "server/zone/packets/creature/CreatureObjectMessage4.h"
#include "server/zone/packets/creature/CreatureObjectMessage6.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage1.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage3.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage4.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/object/PostureMessage.h"
#include "server/zone/packets/object/CommandQueueRemove.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/packets/player/NewbieTutorialRequest.h"
#include "server/zone/packets/ui/NewbieTutorialEnableHudElement.h"
#include "server/zone/packets/ui/OpenHolocronToPageMessage.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/object/Animation.h"
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/objects/creature/events/CommandQueueActionEvent.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/scene/variables/DeltaVectorMap.h"
#include "server/zone/objects/creature/variables/CommandQueueAction.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "events/DizzyFallDownEvent.h"

#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/managers/professions/ProfessionManager.h"
#include "server/zone/managers/resource/resourcespawner/SampleTask.h"

#include "server/zone/templates/tangible/SharedCreatureObjectTemplate.h"

#include "professions/SkillBox.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"

void CreatureObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	skillModList.setNullValue(0);

	groupInviterID = 0;
	groupInviteCounter = 0;

	setLoggingName("CreatureObject");
}

void CreatureObjectImplementation::initializeMembers() {
	linkedCreature = NULL;
	controlDevice = NULL;

	skillModList.setNullValue(0);

	bankCredits = 1000;
	cashCredits = 100;

	pvpStatusBitmask = 0;

	posture = 0;
	factionRank = 0;
	faction = 0;

	stateBitmask = 0;
	terrainNegotiation = 0.f;

	listenToID = 0;
	watchToID = 0;

	weapon = NULL;
	guild = NULL;
	group = NULL;
	groupInviterID = 0;
	groupInviteCounter = 0;
	targetID = 0;
	moodID = 0;
	performanceCounter = 0;
	instrumentID = 0;

	optionsBitmask = 0x80;

	moodString = "neutral";

	height = 1;

	shockWounds = 0;

	accelerationMultiplierBase = 1.f;
	accelerationMultiplierMod = 1.f;
	speedMultiplierBase = 1.f;
	speedMultiplierMod = 1.f;

	cooldownTimerMap = new CooldownTimerMap();
}

void CreatureObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SharedCreatureObjectTemplate* creoData = dynamic_cast<SharedCreatureObjectTemplate*>(templateData);

	gender = creoData->getGender();
	species = creoData->getSpecies();
	slopeModPercent = creoData->getSlopeModPercent();
	slopeModAngle = creoData->getSlopeModAngle();
	swimHeight = creoData->getSwimHeight();

	level = creoData->getLevel();

	encumbrances.removeAll();

	for (int i = 0; i < 3; ++i) {
		encumbrances.add(0);
	}

	Vector<int> base = creoData->getBaseHAM();

	baseHAM.removeAll();

	for (int i = 0; i < base.size(); ++i)
		baseHAM.add(base.get(i));

	wounds.removeAll();
	for (int i = 0; i < 9; ++i) {
		wounds.add(0);
	}

	hamList.removeAll();
	for (int i = 0; i < 9; ++i) {
		hamList.add(baseHAM.get(i));
	}

	maxHamList.removeAll();
	for (int i = 0; i < 9; ++i) {
		maxHamList.add(baseHAM.get(i));
	}

	frozen = 0;

	Vector<float> accel = creoData->getAcceleration();

	if (accel.size() > 0) {
		runAcceleration = accel.get(0);
		walkAcceleration = accel.get(1);
	} else {
		runAcceleration = 0;
		walkAcceleration = 0;
	}

	Vector<float> speedTempl = creoData->getSpeed();

	if (speedTempl.size() > 0) {
		runSpeed = speedTempl.get(0);
		walkSpeed = speedTempl.get(1);
	} else {
		runSpeed = 0;
		walkSpeed = 0;
	}

	lootGroup = creoData->getLootGroup();
}

void CreatureObjectImplementation::finalize() {

}

void CreatureObjectImplementation::sendBaselinesTo(SceneObject* player) {
	if (player == _this) {
		CreatureObjectMessage1* msg = new CreatureObjectMessage1(this);
		player->sendMessage(msg);
	}

	CreatureObjectMessage3* msg3 = new CreatureObjectMessage3(_this);
	player->sendMessage(msg3);

	if (player == _this) {
		CreatureObjectMessage4* msg4 = new CreatureObjectMessage4(this);
		player->sendMessage(msg4);
	}

	CreatureObjectMessage6* msg6 = new CreatureObjectMessage6(_this);
	player->sendMessage(msg6);

	if (!player->isPlayerCreature())
		return;

	PlayerCreature* playerCreature = (PlayerCreature*) player;

	sendPvpStatusTo(playerCreature);
}

void CreatureObjectImplementation::sendSlottedObjectsTo(SceneObject* player) {
	SortedVector<SceneObject*> objects(getSlottedObjectsSize(), getSlottedObjectsSize());
	objects.setNoDuplicateInsertPlan();

	for (int i = 0; i < getSlottedObjectsSize(); ++i) {
		SceneObject* object = getSlottedObject(i);

		int arrangementSize = object->getArrangementDescriptorSize();

		bool sendWithoutContents = false;

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (player != _this && ((childArrangement == "bank") || (childArrangement == "inventory")
					|| (childArrangement == "datapad") || (childArrangement == "mission_bag"))) {
				sendWithoutContents = true;
				break;
			}
		}

		if (objects.put(object) != -1) {
			if (sendWithoutContents)
				object->sendWithoutContainerObjectsTo(player);
			else
				object->sendTo(player, true);
		}
	}
}

void CreatureObjectImplementation::sendSystemMessage(const String& message) {
	if (!isPlayerCreature())
		return;

	UnicodeString msg(message);
	sendSystemMessage(msg);
}

void CreatureObjectImplementation::playMusicMessage(const String& file) {
	PlayMusicMessage* message = new PlayMusicMessage(file);
	sendMessage(message);
}

void CreatureObjectImplementation::sendOpenHolocronToPageMessage() {
	OpenHolocronToPageMessage* message = new OpenHolocronToPageMessage();
	sendMessage(message);
}

void CreatureObjectImplementation::sendNewbieTutorialRequest(const String& request) {
	//info("sending newbie request " + request, true);
	NewbieTutorialRequest* message = new NewbieTutorialRequest(request);
	sendMessage(message);
}

void CreatureObjectImplementation::sendNewbieTutorialEnableHudElement(const String& ui, bool enable) {
	NewbieTutorialEnableHudElement* message = new NewbieTutorialEnableHudElement(ui, enable);
	sendMessage(message);
}

void CreatureObjectImplementation::sendSystemMessage(const String& file, const String& stringid) {
	if (!isPlayerCreature())
		return;

	UnicodeString message("@" + file + ":" + stringid);

	ChatSystemMessage* msg = new ChatSystemMessage(message);
	sendMessage(msg);
}


void CreatureObjectImplementation::sendSystemMessage(StringIdChatParameter& message) {
	if (!isPlayerCreature())
		return;

	ChatSystemMessage* msg = new ChatSystemMessage(message);
	sendMessage(msg);
}

void CreatureObjectImplementation::sendSystemMessage(UnicodeString& message) {
	if (!isPlayerCreature())
		return;

	ChatSystemMessage* smsg = new ChatSystemMessage(message);
	sendMessage(smsg);
}

void CreatureObjectImplementation::clearQueueAction(uint32 actioncntr, float timer, uint32 tab1, uint32 tab2) {
	if (!isPlayerCreature())
		return;

	BaseMessage* queuemsg = new CommandQueueRemove(_this, actioncntr, timer, tab1, tab2);
	sendMessage(queuemsg);
}

void CreatureObjectImplementation::setWeapon(WeaponObject* weao, bool notifyClient) {
	if (weapon == weao)
		return;

	weapon = weao;

	if (notifyClient) {
		CreatureObjectDeltaMessage6* msg = new CreatureObjectDeltaMessage6(_this);
		msg->updateWeapon();
		msg->close();

		broadcastMessage(msg, true);
	}
}

void CreatureObjectImplementation::setInstrumentID(int instrumentid, bool notifyClient) {
	if (instrumentid == instrumentID)
		return;

	instrumentID = instrumentid;

	if (notifyClient) {
		CreatureObjectDeltaMessage6* msg = new CreatureObjectDeltaMessage6(_this);
		msg->updateInstrumentID(instrumentID);
		msg->close();

		broadcastMessage(msg, true);
	}
}

void CreatureObjectImplementation::setTargetID(uint64 targetID, bool notifyClient) {
	CreatureObjectImplementation::targetID = targetID;

	if (notifyClient) {
		CreatureObjectDeltaMessage6* msg = new CreatureObjectDeltaMessage6(_this);
		msg->updateTarget();
		msg->close();

		broadcastMessage(msg, false);
	}
}


void CreatureObjectImplementation::setShockWounds(int newShock, bool notifyClient) {
	if (shockWounds == newShock)
		return;

	shockWounds = newShock;

	if (notifyClient) {
		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->updateShockWounds();
		dcreo3->close();

		broadcastMessage(dcreo3, true);
	}
}

void CreatureObjectImplementation::addShockWounds(int shockToAdd, bool notifyClient) {
	int newShockWounds = shockWounds + shockToAdd;

	if (newShockWounds < 0) {
		newShockWounds = 0;
	} else if (newShockWounds > 1000) {
		newShockWounds = 1000;
	}

	setShockWounds(newShockWounds, notifyClient);
}


void CreatureObjectImplementation::setCombatState() {
	//lastCombatAction.update();

	if (!(stateBitmask & CreatureState::COMBAT)) {
		stateBitmask |= CreatureState::COMBAT;

		lastSuccessfulCombatAction.updateToCurrentTime();

		if (stateBitmask & CreatureState::PEACE)
			stateBitmask &= ~CreatureState::PEACE;

		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->updateCreatureBitmask(0x80);
		dcreo3->updateState();
		dcreo3->close();

		broadcastMessage(dcreo3, true);

		if (posture == CreaturePosture::SITTING)
			setPosture(CreaturePosture::UPRIGHT);
	}
}

void CreatureObjectImplementation::clearCombatState(bool removedefenders) {
	//info("trying to clear CombatState");
	if (stateBitmask & CreatureState::COMBAT) {
		if (stateBitmask & CreatureState::PEACE)
			stateBitmask &= ~CreatureState::PEACE;

		stateBitmask &= ~CreatureState::COMBAT;

		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->updateCreatureBitmask(0x80);
		dcreo3->updateState();
		dcreo3->close();

		broadcastMessage(dcreo3, true);
	}

	if (removedefenders)
		removeDefenders();

	//info("finished clearCombatState");
}

bool CreatureObjectImplementation::setState(uint64 state, bool notifyClient) {
	if (!(stateBitmask & state)) {
		stateBitmask |= state;

		if (notifyClient) {
			CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
			dcreo3->updateState();
			dcreo3->close();

			broadcastMessage(dcreo3, true);
		}

		return true;
	}

	return false;
}


bool CreatureObjectImplementation::clearState(uint64 state, bool notifyClient) {
	if (stateBitmask & state) {
		stateBitmask &= ~state;

		if (notifyClient) {
			CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
			dcreo3->updateState();
			dcreo3->close();

			broadcastMessage(dcreo3, true);
		}

		switch (state) {
		case CreatureState::STUNNED:
			sendSystemMessage("cbt_spam", "no_stunned_single");
			showFlyText("combat_effects", "no_stunned", 0xFF, 0, 0);
			break;
		case CreatureState::BLINDED:
			sendSystemMessage("cbt_spam", "no_blind_single");
			showFlyText("combat_effects", "no_blind", 0xFF, 0, 0);
			break;
		case CreatureState::DIZZY:
			sendSystemMessage("cbt_spam", "no_dizzy_single");
			showFlyText("combat_effects", "no_dizzy", 0xFF, 0, 0);
			break;
		case CreatureState::POISONED:
			sendSystemMessage("dot_message", "stop_poisoned");
			break;
		case CreatureState::DISEASED:
			sendSystemMessage("dot_message", "stop_diseased");
			break;
		case CreatureState::ONFIRE:
			sendSystemMessage("dot_message", "stop_fire");
			break;
		case CreatureState::BLEEDING:
			sendSystemMessage("dot_message", "stop_bleeding");
			break;
		case CreatureState::INTIMIDATED:
			showFlyText("combat_effects", "no_intimidated", 0xFF, 0, 0);
			break;
		case CreatureState::SNARED:
			showFlyText("combat_effects", "no_snare", 0xFF, 0, 0);
			break;
		case CreatureState::ROOTED:
			showFlyText("combat_effects", "no_rooted", 0xFF, 0, 0);
			break;
		case CreatureState::RALLIED:
			showFlyText("combat_effects", "no_rally", 0xFF, 0, 0);
			break;
		case CreatureState::BERSERK:
			showFlyText("combat_effects", "no_berserk", 0xFF, 0, 0);
			break;
		case CreatureState::AIMING:
			break;
		case CreatureState::COVER: {

			showFlyText("combat_effects", "no_cover", 0xFF, 0, 0);

			uint32 undercover = String("undercover").hashCode();
			if (hasBuff(undercover)) {
				removeBuff(undercover);
			}

			setSpeedMultiplierMod(1.f);

			}
			break;
		default:
			break;
		}

		return true;
	} else {
		return false;
	}
}

void CreatureObjectImplementation::setHAM(int type, int value, bool notifyClient) {
	if (hamList.get(type) == value)
		return;

	/*StringBuffer msg;
	msg << "setting ham type " << type << " to " << value;
	info(msg.toString(), true);*/

	if (notifyClient) {
		CreatureObjectDeltaMessage6* msg = new CreatureObjectDeltaMessage6(_this);
		msg->startUpdate(0x0D);
		hamList.set(type, value, msg);
		msg->close();

		broadcastMessage(msg, true);
	} else {
		hamList.set(type, value, NULL);
	}
}

int CreatureObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, int damage, bool destroy, bool notifyClient) {
	if (damageType < 0 || damageType >= hamList.size()) {
		error("incorrect damage type in CreatureObjectImplementation::inflictDamage");
		return 0;
	}

	if (this->isIncapacitated() || this->isDead())
		return 0;

	int currentValue = hamList.get(damageType);

	int newValue = currentValue - damage;

	if (!destroy && newValue <= 0)
		newValue = 1;

	if (damageType % 3 != 0 && newValue < 0) // secondaries never should go negative
		newValue = 0;

	setHAM(damageType, newValue, notifyClient);

	if (newValue <= 0)
		notifyObjectDestructionObservers(attacker, newValue);

	return 0;
}

int CreatureObjectImplementation::healDamage(TangibleObject* healer, int damageType, int damage, bool notifyClient) {
	if (damage == 0)
		return 0;

	if (damageType < 0 || damageType >= hamList.size()) {
		error("incorrect damage type in CreatureObjectImplementation::healDamage");
		return 0;
	}

	/*if (damage < 0 && (isDead() || isIncapacitated()))
		return 0;*/

	int returnValue = damage;

	int currentValue = hamList.get(damageType);

	int newValue = currentValue + damage;

	int maxValue = maxHamList.get(damageType) - wounds.get(damageType);

	if (newValue > maxValue)
		returnValue = maxValue - currentValue;

	newValue = MIN(newValue, maxValue);

	if (currentValue <= 0 && (isIncapacitated() || isDead())) {
		if (newValue <= 0)
			newValue = 1;

		if (damageType % 3 == 0)
			setPosture(CreaturePosture::UPRIGHT);
	}

	if (damageType % 3 != 0 && newValue < 0)
		newValue = 0;

	setHAM(damageType, newValue, notifyClient);

	return returnValue;
}

void CreatureObjectImplementation::setBaseHAM(int type, int value, bool notifyClient) {
	if (baseHAM.get(type) == value)
		return;

	/*StringBuffer msg;
	msg << "setting baseham type " << type << " to " << value;
	info(msg.toString(), true);*/

	if (notifyClient) {
		CreatureObjectDeltaMessage1* msg = new CreatureObjectDeltaMessage1(this);
		msg->startUpdate(0x02);
		baseHAM.set(type, value, msg);
		msg->close();

		broadcastMessage(msg, true);
	} else {
		baseHAM.set(type, value, NULL);
	}
}

void CreatureObjectImplementation::setWounds(int type, int value, bool notifyClient) {
	if (value < 0)
		value = 0;

	if (value >= maxHamList.get(type))
		value = maxHamList.get(type) - 1;

	if (wounds.get(type) == value)
		return;

	if (notifyClient) {
		CreatureObjectDeltaMessage3* msg = new CreatureObjectDeltaMessage3(_this);
		msg->startUpdate(0x11);
		wounds.set(type, value, msg);
		msg->close();

		broadcastMessage(msg, true);
	} else {
		wounds.set(type, value, NULL);
	}

	int maxHamValue = maxHamList.get(type) - wounds.get(type);

	if (getHAM(type) > maxHamValue) {
		setHAM(type, maxHamValue, notifyClient);
	} else if (type % 3 != 0) { //update secondary stats to the max
		setHAM(type, maxHamValue, notifyClient);
	}
}

int CreatureObjectImplementation::addWounds(int type, int value, bool notifyClient) {
	if (type < 0 || type >= wounds.size()) {
		error("unknown wound type in changeWounds");
		return 0;
	}

	int returnValue = value;

	int currentValue = wounds.get(type);

	int newValue = currentValue + value;

	if (newValue < 0)
		returnValue = value - newValue;

	setWounds(type, newValue, notifyClient);

	return returnValue;
}

void CreatureObjectImplementation::setMaxHAM(int type, int value, bool notifyClient) {
	if (maxHamList.get(type) == value)
		return;

	/*StringBuffer msg;
	msg << "setting maxham type " << type << " to " << value;
	info(msg.toString(), true);*/

	if (notifyClient) {
		CreatureObjectDeltaMessage6* msg = new CreatureObjectDeltaMessage6(_this);
		msg->startUpdate(0x0E);
		maxHamList.set(type, value, msg);
		msg->close();

		broadcastMessage(msg, true);
	} else {
		maxHamList.set(type, value, NULL);
	}

	if (wounds.get(type) >= maxHamList.get(type)) // this will reset our wounds to not overflow max value
		setWounds(type, wounds.get(type), notifyClient);

	if (type % 3 != 0) { //changing secondary stats, updating current value
		healDamage(_this, type, value - hamList.get(type), notifyClient);
	}
}

void CreatureObjectImplementation::setEncumbrance(int type, int value, bool notifyClient) {
	if (encumbrances.get(type) == value)
		return;

	if (notifyClient) {
		CreatureObjectDeltaMessage4* msg = new CreatureObjectDeltaMessage4(this);
		msg->startUpdate(0x02);
		encumbrances.set(type, value, msg);
		msg->close();

		broadcastMessage(msg, true);
	} else {
		encumbrances.set(type, value, NULL);
	}
}

void CreatureObjectImplementation::addMaxHAM(int type, int value, bool notifyClient) {
	if (type < 0 || type > maxHamList.size()) {
		error("invalid type in CreatureObjectImplementation::addMaxHAM");
		return;
	}

	int currentValue = maxHamList.get(type);
	int newValue = currentValue + value;

	setMaxHAM(type, newValue, notifyClient);
}

void CreatureObjectImplementation::addEncumbrance(int type, int value, bool notifyClient) {
	if (type < 0 || type >= encumbrances.size()) {
		error("invalid type in CreatureObjectImplementation::addEncumbrance");
		return;
	}

	int currentValue = encumbrances.get(type);
	int newValue = currentValue + value;

	setEncumbrance(type, newValue, notifyClient);
}

void CreatureObjectImplementation::setBankCredits(int credits, bool notifyClient) {
	if (bankCredits == credits)
		return;

	bankCredits = credits;

	if (notifyClient) {
		CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
		delta->updateBankCredits();
		delta->close();

		sendMessage(delta);
	}
}


void CreatureObjectImplementation::setCashCredits(int credits, bool notifyClient) {
	if (cashCredits == credits)
		return;

	cashCredits = credits;

	if (notifyClient) {
		CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
		delta->updateCashCredits();
		delta->close();

		sendMessage(delta);
	}
}

void CreatureObjectImplementation::addSkillBox(SkillBox* skillBox, bool notifyClient) {
	if (skillBoxList.contains(skillBox))
		return;

	if (notifyClient) {
		CreatureObjectDeltaMessage1* msg = new CreatureObjectDeltaMessage1(this);
		msg->startUpdate(0x03);
		skillBoxList.add(skillBox, msg);
		msg->close();

		sendMessage(msg);
	} else {
		skillBoxList.add(skillBox, NULL);
	}
}

void CreatureObjectImplementation::removeSkillBox(SkillBox* skillBox, bool notifyClient) {
	if (!skillBoxList.contains(skillBox))
		return;

	if (notifyClient) {
		CreatureObjectDeltaMessage1* msg = new CreatureObjectDeltaMessage1(this);
		msg->startUpdate(0x03);
		skillBoxList.remove(skillBox, msg);
		msg->close();

		sendMessage(msg);
	} else {
		skillBoxList.remove(skillBox);
	}
}

void CreatureObjectImplementation::removeSkillBox(const String& skillBox, bool notifyClient) {
	ZoneServer* zoneServer = server->getZoneServer();
	ProfessionManager* professionManager = zoneServer->getProfessionManager();

	SkillBox* skillBoxObject = professionManager->getSkillBox(skillBox);

	if (skillBoxObject == NULL) {
		error("trying to remove null skill box " + skillBox);
		return;
	}

	removeSkillBox(skillBoxObject, notifyClient);
}

void CreatureObjectImplementation::removeSkillMod(const String& skillMod, bool notifyClient) {
	if (!skillModList.contains(skillMod))
		return;

	if (notifyClient) {
		CreatureObjectDeltaMessage4* msg = new CreatureObjectDeltaMessage4(this);
		msg->startUpdate(0x03);
		skillModList.drop(skillMod, msg, 1);
		msg->close();

		sendMessage(msg);
	} else {
		skillModList.drop(skillMod);
	}
}

void CreatureObjectImplementation::addSkillMod(const String& skillMod, int64 value, bool notifyClient) {
	if (skillModList.contains(skillMod)) {
		value += skillModList.get(skillMod);

		if (value <= 0) {
			removeSkillMod(skillMod, notifyClient);
			return;
		}
	}

	if (notifyClient) {
		CreatureObjectDeltaMessage4* msg = new CreatureObjectDeltaMessage4(this);
		msg->startUpdate(0x03);
		skillModList.set(skillMod, value, msg, 1);
		msg->close();

		sendMessage(msg);
	} else {
		skillModList.set(skillMod, value);
	}
}

void CreatureObjectImplementation::addSkillBox(const String& skillBox, bool notifyClient) {
	ZoneServer* zoneServer = server->getZoneServer();
	ProfessionManager* professionManager = zoneServer->getProfessionManager();

	SkillBox* skillBoxObject = professionManager->getSkillBox(skillBox);

	if (skillBoxObject == NULL) {
		error("trying to add null skill box " + skillBox);
		return;
	}

	addSkillBox(skillBoxObject, notifyClient);
}

void CreatureObjectImplementation::setPosture(int newPosture, bool notifyClient) {
	if (posture == newPosture)
		return;

	if (newPosture == CreaturePosture::PRONE) {
		setSpeedMultiplierBase(0.2f);
	} else if (posture == CreaturePosture::PRONE) {
		setSpeedMultiplierBase(1.f);
		if (isInCover()) {
			clearState(CreatureState::COVER);
		}
	}

	posture = newPosture;

	if (posture != CreaturePosture::SITTING && hasState(CreatureState::SITTINGONCHAIR))
		clearState(CreatureState::SITTINGONCHAIR);

	if (notifyClient) {
		Vector<BasePacket*> messages;

		PostureMessage* octrl = new PostureMessage(_this);
		messages.add(octrl);

		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->updatePosture();
		dcreo3->updateState();
		dcreo3->close();

		messages.add(dcreo3);

		broadcastMessages(&messages, true);
	}

	notifyPostureChange(newPosture);
}

UnicodeString CreatureObjectImplementation::getCreatureName() {
	return objectName.getCustomString();
}

void CreatureObjectImplementation::updateGroupInviterID(uint64 id, bool notifyClient) {
	groupInviterID = id;
	++groupInviteCounter;

	CreatureObjectDeltaMessage6* delta = new CreatureObjectDeltaMessage6(_this);
	delta->updateInviterId();
	delta->close();

	broadcastMessage(delta, true);
}

void CreatureObjectImplementation::updateGroup(GroupObject* grp, bool notifyClient) {
	group = grp;

	CreatureObjectDeltaMessage6* delta = new CreatureObjectDeltaMessage6(_this);
	delta->updateGroupID();
	delta->close();

	broadcastMessage(delta, true);
}

void CreatureObjectImplementation::setMood(byte mood, bool notifyClient) {
	moodID = mood;
	moodString = Races::getMoodStr(Races::getMood(moodID));

	if (notifyClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMoodID();
		dcreo6->updateMoodStr();
		dcreo6->close();

		broadcastMessage(dcreo6, true);
	}
}

void CreatureObjectImplementation::setAccelerationMultiplierBase(float newMultiplierBase, bool notifyClient) {
	if (accelerationMultiplierBase == newMultiplierBase)
		return;

	accelerationMultiplierBase = newMultiplierBase;

	if (notifyClient) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);
		dcreo4->updateAccelerationMultiplierBase();
		dcreo4->close();

		sendMessage(dcreo4);
	}
}

void CreatureObjectImplementation::setAccelerationMultiplierMod(float newMultiplierMod, bool notifyClient) {
	if (accelerationMultiplierMod == newMultiplierMod)
		return;

	accelerationMultiplierMod = newMultiplierMod;

	if (notifyClient) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);
		dcreo4->updateAccelerationMultiplierMod();
		dcreo4->close();

		sendMessage(dcreo4);
	}
}

void CreatureObjectImplementation::setSpeedMultiplierBase(float newMultiplierBase, bool notifyClient) {
	if (speedMultiplierBase == newMultiplierBase)
		return;

	speedMultiplierBase = newMultiplierBase;

	if (notifyClient) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);
		dcreo4->updateSpeedMultiplierBase();
		dcreo4->close();

		sendMessage(dcreo4);
	}
}

void CreatureObjectImplementation::setSpeedMultiplierMod(float newMultiplierMod, bool notifyClient) {
	if (speedMultiplierMod == newMultiplierMod)
		return;

	speedMultiplierMod = newMultiplierMod;

	int bufferSize = speedMultiplierModChanges.size();

	if (bufferSize > 5) {
		speedMultiplierModChanges.remove(0);
	}

	speedMultiplierModChanges.add(SpeedModChange(speedMultiplierMod));

	if (notifyClient) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);
		dcreo4->updateSpeedMultiplierMod();
		dcreo4->close();

		sendMessage(dcreo4);
	}
}

void CreatureObjectImplementation::setRunSpeed(float newSpeed, bool notifyClient) {
	if (runSpeed == newSpeed)
		return;

	runSpeed = newSpeed;

	if (notifyClient) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);
		dcreo4->updateRunSpeed();
		dcreo4->close();

		sendMessage(dcreo4);
	}
}

void CreatureObjectImplementation::setMoodString(const String& moodAnimationString, bool notifyClient) {
	moodString = moodAnimationString;

	if (notifyClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMoodStr();
		dcreo6->close();

		broadcastMessage(dcreo6, true);
	}
}

void CreatureObjectImplementation::setPerformanceCounter(int counter, bool notifyClient) {
	if (performanceCounter == counter)
		return;

	performanceCounter = counter;

	if (!notifyClient)
		return;

	CreatureObjectDeltaMessage6* codm4 = new CreatureObjectDeltaMessage6(_this);
	codm4->updatePerformanceCounter(counter);
	codm4->close();
	broadcastMessage(codm4, true);
}

void CreatureObjectImplementation::setListenToID(uint64 id, bool notifyClient) {
	if (listenToID == id)
		return;

	listenToID = id;

	if (!notifyClient)
		return;

	CreatureObjectDeltaMessage4* codm4 = new CreatureObjectDeltaMessage4(this);
	codm4->updateListenToID(id);
	codm4->close();
	sendMessage(codm4);
}

void CreatureObjectImplementation::setPerformanceAnimation(const String& animation, bool notifyClient) {
	if (performanceAnimation == animation)
		return;

	performanceAnimation = animation;

	if (!notifyClient)
		return;

	CreatureObjectDeltaMessage6* codm4 = new CreatureObjectDeltaMessage6(_this);
	codm4->updatePerformanceAnimation(animation);
	codm4->close();
	broadcastMessage(codm4, true);
}

void CreatureObjectImplementation::setTerrainNegotiation(float value, bool notifyClient) {
	if (terrainNegotiation == value)
		return;

	terrainNegotiation = value;

	if (!notifyClient)
		return;

	CreatureObjectDeltaMessage4* codm4 = new CreatureObjectDeltaMessage4(this);
	codm4->updateTerrainNegotiation();
	codm4->close();
	sendMessage(codm4);
}

void CreatureObjectImplementation::enqueueCommand(unsigned int actionCRC, unsigned int actionCount, uint64 targetID, const UnicodeString& arguments, int priority) {
	ManagedReference<ObjectController*> objectController = getZoneServer()->getObjectController();

	QueueCommand* queueCommand = objectController->getQueueCommand(actionCRC);

	if (queueCommand == NULL) {
		StringBuffer msg;
		msg << "trying to enqueue NULL QUEUE COMMAND 0x" << hex << actionCRC;
		error(msg.toString());

		StackTrace::printStackTrace();
		return;
	}

	if (priority < 0)
		priority = queueCommand->getDefaultPriority();

	if (priority == QueueCommand::IMMEDIATE) {
		objectController->activateCommand(_this, actionCRC, actionCount, targetID, arguments);

		return;
	}

	if (commandQueue.size() > 15 && priority != QueueCommand::FRONT) {
		clearQueueAction(actionCount);

		return;
	}

	Reference<CommandQueueAction*> action = new CommandQueueAction(_this, targetID, actionCRC, actionCount, arguments);

	if (commandQueue.size() != 0 || !nextAction.isPast()) {
		if (commandQueue.size() == 0) {
			Reference<CommandQueueActionEvent*> e = new CommandQueueActionEvent(_this);
			e->schedule(nextAction);
		}

		if (priority == QueueCommand::NORMAL)
			commandQueue.add(action);
		else if (priority == QueueCommand::FRONT)
			commandQueue.add(0, action);
	} else {
		nextAction.updateToCurrentTime();

		commandQueue.add(action);
		activateQueueAction();
	}
}

void CreatureObjectImplementation::activateQueueAction() {
	if (nextAction.isFuture()) {
		CommandQueueActionEvent* e = new CommandQueueActionEvent(_this);
		e->schedule(nextAction);

		return;
	}

	if (commandQueue.size() == 0)
		return;

	Reference<CommandQueueAction*> action = commandQueue.get(0);
	commandQueue.remove(0);

	ManagedReference<ObjectController*> objectController = getZoneServer()->getObjectController();

	float time = objectController->activateCommand(_this, action->getCommand(), action->getActionCounter(), action->getTarget(), action->getArguments());

	//delete action;

	nextAction.updateToCurrentTime();

	if (time > 0)
		nextAction.addMiliTime((uint32) (time * 1000));

	if (commandQueue.size() != 0) {
		Reference<CommandQueueActionEvent*> e = new CommandQueueActionEvent(_this);

		if (!nextAction.isFuture()) {
			nextAction.updateToCurrentTime();
			nextAction.addMiliTime(100);
		}

		e->schedule(nextAction);
	}
}

void CreatureObjectImplementation::deleteQueueAction(uint32 actionCount) {
	for (int i = 0; i < commandQueue.size(); ++i) {
		CommandQueueAction* action = commandQueue.get(i);

		if (action->getActionCounter() == actionCount) {
			commandQueue.remove(i);
			break;
		}
	}
}

uint32 CreatureObjectImplementation::getWearableMask() {
	uint16 characterMask = 0;

	if (this->isRebel())
		characterMask |= WearableObject::REBEL;
	else if (this->isImperial())
		characterMask |= WearableObject::IMPERIAL;
	else
		characterMask |= WearableObject::NEUTRAL;

	/*if (this->isOnLeave())
		characterMask |= WearableObject::COVERT;*/

	switch (species) {
	case 0: // HUMAN
		characterMask |= WearableObject::HUMAN;
		break;
	case 2: // TRANDOSHAN
		characterMask |= WearableObject::TRANDOSHAN;
		break;
	case 6: // TWILEK
		characterMask |= WearableObject::TWILEK;
		break;
	case 5: // BOTHAN
		characterMask |= WearableObject::BOTHAN;
		break;
	case 7: // ZABRAK
		characterMask |= WearableObject::ZABRAK;
		break;
	case 1: // RODIAN
		characterMask |= WearableObject::RODIAN;
		break;
	case 3: //MONCALAMARI
		characterMask |= WearableObject::MONCALAMARI;
		break;
	case 4: //WOOKIEE:
		characterMask |= WearableObject::WOOKIEE;
		break;
	case 49: //SULLUSTAN:
		characterMask |= WearableObject::SULLUSTAN;
		break;
	case 33: //ITHORIAN:
		characterMask |= WearableObject::ITHORIAN;
		break;
	}

	if (gender == MALE)
		characterMask |= WearableObject::MALE;
	else if (gender == FEMALE)
		characterMask |= WearableObject::FEMALE;

	return characterMask;

}

int CreatureObjectImplementation::notifyObjectInserted(SceneObject* object) {
	if (object->isWeaponObject())
		setWeapon((WeaponObject*)object);

	return TangibleObjectImplementation::notifyObjectInserted(object);
}

int CreatureObjectImplementation::notifyObjectRemoved(SceneObject* object) {
	if (object->isWeaponObject())
		setWeapon(NULL);

	return TangibleObjectImplementation::notifyObjectInserted(object);
}

void CreatureObjectImplementation::setCreatureLink(CreatureObject* object, bool notifyClient) {
	if (linkedCreature == object)
		return;

	linkedCreature = object;

	if (!notifyClient)
		return;

	CreatureObjectDeltaMessage3* delta = new CreatureObjectDeltaMessage3(_this);
	delta->updateCreatureLinkID();
	delta->close();

	broadcastMessage(delta, true);
}

void CreatureObjectImplementation::executeObjectControllerAction(unsigned int actionCRC) {
	ManagedReference<ObjectController*> objectController = getZoneServer()->getObjectController();

	objectController->activateCommand(_this, actionCRC, 0, 0, "");
}

void CreatureObjectImplementation::executeObjectControllerAction(unsigned int actionCRC, uint64 targetID, const UnicodeString& args) {
	ManagedReference<ObjectController*> objectController = getZoneServer()->getObjectController();

	objectController->activateCommand(_this, actionCRC, 0, targetID, args);
}


void CreatureObjectImplementation::doCombatAnimation(CreatureObject* defender, uint32 animcrc, byte hit) {
	CombatAction* action = new CombatAction(_this, defender, animcrc, hit);

	broadcastMessage(action, true);
}

void CreatureObjectImplementation::doAnimation(const String& anim) {
	Animation* msg = new Animation(_this, anim);

	broadcastMessage(msg, true);
}


void CreatureObjectImplementation::playEffect(const String& file, const String& aux) {
	PlayClientEffectObjectMessage* effect = new PlayClientEffectObjectMessage(_this, file, aux);

	broadcastMessage(effect, true);
}

void CreatureObjectImplementation::dismount() {
	executeObjectControllerAction(String("dismount").hashCode());
}


float CreatureObjectImplementation::calculateBFRatio() {
	if (shockWounds <= 250)
		return 0;
	else
		return ((((float) shockWounds) - 250.0f) / 1000.0f);
}

void CreatureObjectImplementation::setDizziedState(int durationSeconds) {
	if (setState(CreatureState::DIZZY)) {
		playEffect("clienteffect/combat_special_defender_dizzy.cef");
		showFlyText("combat_effects", "go_dizzy", 0, 0xFF, 0);
		sendSystemMessage("cbt_spam", "go_dizzy_single");

		cooldownTimerMap->updateToCurrentAndAddMili("dizzyRecoveryTime", durationSeconds * 1000);
	}
}

void CreatureObjectImplementation::setAimingState(int durationSeconds) {
	if (setState(CreatureState::AIMING)) {
		playEffect("clienteffect/combat_special_attacker_aim.cef");

		cooldownTimerMap->updateToCurrentAndAddMili("aimRecoveryTime", durationSeconds * 1000);
	}
}

void CreatureObjectImplementation::setRalliedState(int durationSeconds) {
	if (setState(CreatureState::RALLIED)) {
		showFlyText("combat_effects", "go_rally", 0, 0xFF, 0);

		cooldownTimerMap->updateToCurrentAndAddMili("ralliedRecoveryTime", durationSeconds * 1000);
	}
}

void CreatureObjectImplementation::setCoverState(int durationSeconds) {
	setPosture(CreaturePosture::PRONE);

	if (setState(CreatureState::COVER)) {
		playEffect("clienteffect/combat_special_attacker_cover.cef");
		showFlyText("combat_effects", "go_cover", 0, 0xFF, 0);
		sendSystemMessage("cbt_spam", "cover_success_single");

		if(hasSkillBox("combat_rifleman_speed_03")) {
			setSpeedMultiplierMod(0.5f);
		} else {
			setSpeedMultiplierMod(0.f);
		}

		cooldownTimerMap->updateToCurrentAndAddMili("coverRecoveryTime", durationSeconds * 1000);
	}
}

void CreatureObjectImplementation::setBerserkedState(uint32 duration) {
	if (setState(CreatureState::BERSERK)) {
		playEffect("clienteffect/combat_special_attacker_berserk.cef");
		showFlyText("combat_effects", "go_berserk", 0, 0xFF, 0);

		cooldownTimerMap->updateToCurrentAndAddMili("berserkRecoveryTime", duration * 1000);
	}
}
void CreatureObjectImplementation::setStunnedState(int durationSeconds) {
	if (setState(CreatureState::STUNNED)) {
		playEffect("clienteffect/combat_special_defender_stun.cef");
		showFlyText("combat_effects", "go_stunned", 0, 0xFF, 0);
		sendSystemMessage("cbt_spam", "go_stunned_single");

		cooldownTimerMap->updateToCurrentAndAddMili("stunRecoveryTime", durationSeconds * 1000);
	}
}

void CreatureObjectImplementation::setBlindedState(int durationSeconds) {
	if (setState(CreatureState::BLINDED)) {
		playEffect("clienteffect/combat_special_defender_blind.cef");
		showFlyText("combat_effects", "go_blind", 0, 0xFF, 0);
		sendSystemMessage("cbt_spam", "go_blind_single");

		cooldownTimerMap->updateToCurrentAndAddMili("blindRecoveryTime", durationSeconds * 1000);
	}
}

void CreatureObjectImplementation::setIntimidatedState(int durationSeconds) {
	if (setState(CreatureState::INTIMIDATED)) {
		playEffect("clienteffect/combat_special_defender_intimidate.cef");
		showFlyText("combat_effects", "go_intimidated", 0, 0xFF, 0);

		cooldownTimerMap->updateToCurrentAndAddMili("intimidateRecoveryTime", durationSeconds * 1000);
	}
}

void CreatureObjectImplementation::setSnaredState(int durationSeconds) {
	if (setState(CreatureState::SNARED)) {
		//playEffect("clienteffect/combat_special_defender_intimidate.cef");
		showFlyText("combat_effects", "go_snare", 0, 0xFF, 0);

		cooldownTimerMap->updateToCurrentAndAddMili("snareRecoveryTime", durationSeconds * 1000);
	}
}

void CreatureObjectImplementation::setRootedState(int durationSeconds) {
	if (setState(CreatureState::ROOTED)) {
		//playEffect("clienteffect/combat_special_defender_intimidate.cef");
		showFlyText("combat_effects", "go_rooted", 0, 0xFF, 0);

		cooldownTimerMap->updateToCurrentAndAddMili("rootRecoveryTime", durationSeconds * 1000);
	}
}

bool CreatureObjectImplementation::setNextAttackDelay(int del) {
	if (cooldownTimerMap->isPast("nextAttackDelayRecovery")) {
		cooldownTimerMap->updateToCurrentAndAddMili("nextAttackDelay", del * 1000);

		cooldownTimerMap->updateToCurrentAndAddMili("nextAttackDelayRecovery", 30000 + (del * 1000));

		if (isPlayerCreature()) {
			StringIdChatParameter stringId("combat_effects", "delay_applied_self");
			stringId.setDI(del);
			sendSystemMessage(stringId);
		}

		return true;
	}

	return false;
}

void CreatureObjectImplementation::setMeditateState() {
	if (isInCombat())
		return;

	setMoodString("meditating");
	setPosture(CreaturePosture::SITTING);
	setState(CreatureState::ALERT);
}

void CreatureObjectImplementation::queueDizzyFallEvent() {
	if (getPendingTask("dizzyFallDownEvent") != NULL)
		return;

	Task* task = new DizzyFallDownEvent(_this);
	addPendingTask("dizzyFallDownEvent", task);
	task->schedule(200);
}

void CreatureObjectImplementation::activateStateRecovery() {
	if (isDizzied() && cooldownTimerMap->isPast("dizzyRecoveryTime"))
		clearState(CreatureState::DIZZY);

	if (isBlinded() && cooldownTimerMap->isPast("blindRecoveryTime"))
		clearState(CreatureState::BLINDED);

	if (isStunned() && cooldownTimerMap->isPast("stunRecoveryTime"))
		clearState(CreatureState::STUNNED);

	if (isIntimidated() && cooldownTimerMap->isPast("intimidateRecoveryTime"))
		clearState(CreatureState::INTIMIDATED);

	if (isBerserked() && cooldownTimerMap->isPast("berserkRecoveryTime")) {
		clearState(CreatureState::BERSERK);
		//setBerserkDamage(0);
	}

	if (isAiming() && cooldownTimerMap->isPast("aimRecoveryTime")) {
		clearState(CreatureState::AIMING);
	}

	if (isRallied() && cooldownTimerMap->isPast("ralliedRecoveryTime")) {
		clearState(CreatureState::RALLIED);
	}

	if (isInCover() && cooldownTimerMap->isPast("coverRecoveryTime")) {
		clearState(CreatureState::COVER);
	}

	//applyDots();

	//updateStates();
}

void CreatureObjectImplementation::updateToDatabaseAllObjects(bool startTask) {
	if (!isPersistent())
		return;

	creatureBuffs.updateBuffsToDatabase();

	TangibleObjectImplementation::updateToDatabaseAllObjects(startTask);
}

void CreatureObjectImplementation::addBuff(Buff* buff) {
	if (buff == NULL)
		return;

	uint32 buffcrc = buff->getBuffCRC();

	creatureBuffs.addBuff(_this, buff);
}

void CreatureObjectImplementation::removeBuff(uint32 buffcrc) {
	//BuffList::removeBuff checks to see if the buffcrc exists in the map.
	creatureBuffs.removeBuff(_this, buffcrc);
}

void CreatureObjectImplementation::removeBuff(Buff* buff) {
	if (buff == NULL)
		return;

	uint32 buffcrc = buff->getBuffCRC();

	//BuffList::removeBuff checks to see if the buffcrc exists in the map.
	creatureBuffs.removeBuff(_this, buff);
}

void CreatureObjectImplementation::clearBuffs(bool updateclient) {
	creatureBuffs.clearBuffs(_this, updateclient);
}

void CreatureObjectImplementation::notifyPostureChange(int newPosture) {
	notifyObservers(ObserverEventType::POSTURECHANGED, NULL, newPosture);
}

void CreatureObjectImplementation::notifySelfPositionUpdate() {
	if (getZone() != NULL) {
		ManagedReference<PlanetManager*> planetManager = getZone()->getPlanetManager();

		if (planetManager != NULL) {
			TerrainManager* terrainManager = planetManager->getTerrainManager();

			if (terrainManager != NULL)
				terrainManager->notifyPositionUpdate(_this);
		}
	}

	TangibleObjectImplementation::notifySelfPositionUpdate();
}

void CreatureObjectImplementation::activateHAMRegeneration() {
	if (isIncapacitated() || isDead())
		return;

	float modifier = 1.f;// (isInCombat()) ? 1.f : 1.f;

	if (isKneeling())
		modifier *= (1.5);
	else if (isSitting())
		modifier *= (2);

	if (!isPlayerCreature()) {
		modifier /= 3.0f;
	}

	uint32 healthTick = (uint32) ceil((float) MAX(0, getHAM(CreatureAttribute::CONSTITUTION)) * 13.0f / 1200.0f * 3.0f * modifier);
	uint32 actionTick = (uint32) ceil((float) MAX(0, getHAM(CreatureAttribute::STAMINA)) * 13.0f / 1200.0f * 3.0f * modifier);
	uint32 mindTick = (uint32) ceil((float) MAX(0, getHAM(CreatureAttribute::WILLPOWER)) * 13.0f / 1200.0f * 3.0f * modifier);

	if (healthTick < 1)
		healthTick = 1;

	if (actionTick < 1)
		actionTick = 1;

	if (mindTick < 1)
		mindTick = 1;

	healDamage(_this, CreatureAttribute::HEALTH, healthTick);
	healDamage(_this, CreatureAttribute::ACTION, actionTick);
	healDamage(_this, CreatureAttribute::MIND, mindTick);

	//Check for passive wound healing
	/*if (isInBuilding()) {
		BuildingObject* building = (BuildingObject*) getBuilding();
		passiveWoundHeal += building->getPassiveWoundHealRate();

		if (passiveWoundHeal >= 100) {
			healWound(_this, getNextWoundedAttribute(true, true, false), 1);
			passiveWoundHeal = 0;
		}
	} else if (passiveWoundHeal > 0) {
		//Reset passive wound heal if they leave the building.
		passiveWoundHeal = 0;
	}

	//TODO: Refactor this with event handlers
	if (isMeditating()) {
		int meditateMod = getSkillMod("meditate");
		float meditateBonus = 1 + ((float)meditateMod / 100);
		healthTick *= (int)meditateBonus;
		actionTick *= (int)meditateBonus;
		mindTick *= (int)meditateBonus;
		doMeditateHeals();
	}

	//TODO: Refactor this into an event handler
	if (isPlayer()) {
		Player* player = (Player*)_this;
		if (player->getPowerboosted() && pbMind != 0) {
			doPowerboostTick(player);
		}
	}

	//TODO: Refactor this into an event handler
	if (isPlayer()) {
		Player* player = (Player*)_this;
		if (channelForceHAM != 0) {
			doChannelForceTick(player);
		}
	}

	if(!returningHome)
		changeHAMBars(healthTick, actionTick, mindTick, true);
	else if(returningHome)
		changeHAMBars(healthTick * 20, actionTick * 20, mindTick * 20, true);*/
}

bool CreatureObjectImplementation::isResuscitable() {
	return (isDead() && (timeOfDeath.miliDifference()) < DEAD_TOO_LONG);
}

bool CreatureObjectImplementation::isDancing() {
	Facade* facade = this->getActiveSession(SessionFacadeType::ENTERTAINING);

	if (facade == NULL)
		return false;

	EntertainingSession* session = dynamic_cast<EntertainingSession*>(facade);

	if (session == NULL)
		return false;

	return session->isDancing();
}

bool CreatureObjectImplementation::isPlayingMusic() {
	Facade* facade = this->getActiveSession(SessionFacadeType::ENTERTAINING);

	if (facade == NULL)
		return false;

	EntertainingSession* session = dynamic_cast<EntertainingSession*>(facade);

	if (session == NULL)
		return false;

	return session->isPlayingMusic();
}

void CreatureObjectImplementation::stopEntertaining() {
	Facade* facade = this->getActiveSession(SessionFacadeType::ENTERTAINING);

	if (facade == NULL)
		return;

	EntertainingSession* session = dynamic_cast<EntertainingSession*>(facade);

	if (session == NULL)
		return;

	session->cancelSession();
}
