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
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/objects/creature/events/CommandQueueActionEvent.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/scene/variables/ParameterizedStringId.h"
#include "server/zone/objects/scene/variables/DeltaVectorMap.h"
#include "server/zone/objects/creature/variables/CommandQueueAction.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/packets/creature/UpdatePVPStatusMessage.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/managers/template/TemplateManager.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/managers/professions/ProfessionManager.h"

#include "professions/SkillBox.h"

void CreatureObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	skillModList.setNullValue(0);

	groupInviterID = 0;
	groupInviteCounter = 0;

	setLoggingName("CreatureObject");
}

void CreatureObjectImplementation::loadTemplateData(LuaObject* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	bankCredits = 1000;
	cashCredits = 100;

	pvpStatusBitmask = CreatureFlag::ATTACKABLE;

	posture = 0;
	factionRank = 0;
	faction = 0;

	height = 1;

	shockWounds = 0.f;

	gender = templateData->getIntField("gender");
	species = templateData->getIntField("species");
	slopeModPercent = templateData->getFloatField("slopeModPercent");
	slopeModAngle = templateData->getFloatField("slopeModAngle");
	swimHeight = templateData->getFloatField("swimHeight");

	stateBitmask = 0;
	terrainNegotiation = 0.f;

	listenToID = 0;

	level = 0;

	weapon = NULL;
	group = NULL;
	groupInviterID = 0;
	groupInviteCounter = 0;
	guildID = 0;
	targetID = 0;
	moodID = 0;
	performanceCounter = 0;
	instrumentID = 0;

	optionsBitmask = 0x80;

	for (int i = 0; i < 3; ++i) {
		encumbrances.add(0);
	}

	LuaObject hams = templateData->getObjectField("baseHAM");

	for (int i = 1; i <= hams.getTableSize(); ++i) {
		baseHAM.add(hams.getIntAt(i));
	}

	hams.pop();

	for (int i = 0; i < 9; ++i) {
		wounds.add(0);
	}

	for (int i = 0; i < 9; ++i) {
		hamList.add(baseHAM.get(i));
	}

	for (int i = 0; i < 9; ++i) {
		maxHamList.add(baseHAM.get(i));
	}

	frozen = 0;

	LuaObject accel = templateData->getObjectField("acceleration");

	if (accel.getTableSize() > 0) {
		runAcceleration = accel.getFloatAt(1);
		walkAcceleration = accel.getFloatAt(2);
	} else {
		runAcceleration = 0;
		walkAcceleration = 0;
	}

	accel.pop();

	LuaObject speedTempl = templateData->getObjectField("speed");

	if (speedTempl.getTableSize() > 0) {
		runSpeed = speedTempl.getFloatAt(1);
		walkSpeed = speedTempl.getFloatAt(2);
	} else {
		runSpeed = 0;
		walkSpeed = 0;
	}

	speedTempl.pop();

}

void CreatureObjectImplementation::finalize() {
	for (int i = 0; i < commandQueue.size(); ++i) {
		delete commandQueue.get(i);
	}

	commandQueue.removeAll();
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

	BaseMessage* pvp = new UpdatePVPStatusMessage(this, pvpStatusBitmask);
	player->sendMessage(pvp);
}

void CreatureObjectImplementation::sendSlottedObjectsTo(SceneObject* player) {
	for (int i = 0; i < slottedObjects.size(); ++i) {
		SceneObject* object = slottedObjects.get(i);

		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (player != _this && (childArrangement == "bank" || childArrangement == "inventory"
					|| childArrangement == "datapad" || childArrangement == "mission_bag"))
				continue;
			else
				object->sendTo(player);
		}
	}
}

void CreatureObjectImplementation::sendSystemMessage(const String& message) {
	if (!isPlayerCreature())
		return;

	UnicodeString msg(message);
	sendSystemMessage(msg);
}

void CreatureObjectImplementation::sendSystemMessage(const String& file, const String& stringid) {
	if (!isPlayerCreature())
		return;

	ChatSystemMessage* msg = new ChatSystemMessage(file, stringid);
	sendMessage(msg);
}


void CreatureObjectImplementation::sendSystemMessage(ParameterizedStringId& message) {
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

void CreatureObjectImplementation::setCombatState() {
	//lastCombatAction.update();

	if (!(stateBitmask & CreatureState::COMBAT)) {
		stateBitmask |= CreatureState::COMBAT;

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

void CreatureObjectImplementation::setState(uint64 state, bool notifyClient) {
	if (!(stateBitmask & state)) {
		stateBitmask |= state;

		if (notifyClient) {
			CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
			dcreo3->updateState();
			dcreo3->close();

			broadcastMessage(dcreo3, true);
		}
	}
}


void CreatureObjectImplementation::clearState(uint64 state, bool notifyClient) {
	if (stateBitmask & state) {
		stateBitmask &= ~state;

		if (notifyClient) {
			CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
			dcreo3->updateState();
			dcreo3->close();

			broadcastMessage(dcreo3, true);
		}
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

void CreatureObjectImplementation::enqueueCommand(unsigned int actionCRC, unsigned int actionCount, uint64 targetID, const UnicodeString& arguments) {
	ObjectController* objectController = getZoneServer()->getObjectController();

	QueueCommand* queueCommand = objectController->getQueueCommand(actionCRC);

	if (queueCommand == NULL) {
		StringBuffer msg;
		msg << "trying to enqueue NULL QUEUE COMMAND 0x" << hex << actionCRC;
		error(msg.toString());
		return;
	}

	if (queueCommand->getDefaultPriority() == QueueCommand::IMMEDIATE) {
		objectController->activateCommand(_this, actionCRC, actionCount, targetID, arguments);

		return;
	}

	if (commandQueue.size() > 15) {
		clearQueueAction(actionCRC);

		return;
	}

	CommandQueueAction* action = new CommandQueueAction(_this, targetID, actionCRC, actionCount, arguments);

	if (commandQueue.size() != 0 || !nextAction.isPast()) {
		if (commandQueue.size() == 0) {
			CommandQueueActionEvent* e = new CommandQueueActionEvent(_this);
			e->schedule(nextAction);
		}

		if (queueCommand->getDefaultPriority() == QueueCommand::NORMAL)
			commandQueue.add(action);
		else if (queueCommand->getDefaultPriority() == QueueCommand::FRONT)
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

	CommandQueueAction* action = commandQueue.remove(0);

	ObjectController* objectController = getZoneServer()->getObjectController();

	float time = objectController->activateCommand(_this, action->getCommand(), action->getActionCounter(), action->getTarget(), action->getArguments());

	delete action;

	nextAction.updateToCurrentTime();

	if (time != 0)
		nextAction.addMiliTime((uint32) (time * 1000));

	if (commandQueue.size() != 0) {
		CommandQueueActionEvent* e = new CommandQueueActionEvent(_this);

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
			delete action;
			break;
		}
	}
}

int CreatureObjectImplementation::onPositionUpdate() {
	TerrainManager* terrainManager = zone->getPlanetManager()->getTerrainManager();

	float waterHeight;

	if (parent == NULL && terrainManager->getWaterHeight(positionX, positionY, waterHeight)) {
		//info("detected water height " + String::valueOf(waterHeight), true);

		float roundingPositionZ = floor(positionZ * 10) / 10;

		float result = waterHeight - swimHeight;
		/*StringBuffer msg;
		msg << "rounding:" << roundingPositionZ << " positionZ :" << positionZ << " waterHeight - swimHeight:" << result;
		info(msg.toString(), true);*/

		if (roundingPositionZ == (waterHeight - swimHeight)) {
			//info("trying to set swimming state");
			setState(CreatureState::SWIMMING);
		} else {
			clearState(CreatureState::SWIMMING);
		}
	} else
		clearState(CreatureState::SWIMMING);

	return 0;
}

uint32 CreatureObjectImplementation::getWearableMask() {
	uint16 characterMask = 0;

	int raceID = Races::getRaceID(TemplateManager::instance()->getTemplateFile(serverObjectCRC));

	if (this->isRebel())
		characterMask |= WearableObject::REBEL;
	else if (this->isImperial())
		characterMask |= WearableObject::IMPERIAL;
	else
		characterMask |= WearableObject::NEUTRAL;

	/*if (this->isOnLeave())
		characterMask |= WearableObject::COVERT;*/

	switch (raceID) {
	case 0:
		characterMask |= WearableObject::MALE | WearableObject::HUMAN;
		break;
	case 1:
		characterMask |= WearableObject::MALE | WearableObject::TRANDOSHAN;
		break;
	case 2:
		characterMask |= WearableObject::MALE | WearableObject::TWILEK;
		break;
	case 3:
		characterMask |= WearableObject::MALE | WearableObject::BOTHAN;
		break;
	case 4:
		characterMask |= WearableObject::MALE | WearableObject::ZABRAK;
		break;
	case 5:
		characterMask |= WearableObject::MALE | WearableObject::RODIAN;
		break;
	case 6:
		characterMask |= WearableObject::MALE | WearableObject::MONCALAMARI;
		break;
	case 7:
		characterMask |= WearableObject::MALE | WearableObject::WOOKIEE;
		break;
	case 8:
		characterMask |= WearableObject::MALE | WearableObject::SULLUSTAN;
		break;
	case 9:
		characterMask |= WearableObject::MALE | WearableObject::ITHORIAN;
		break;
	case 10:
		characterMask |= WearableObject::FEMALE | WearableObject::HUMAN;
		break;
	case 11:
		characterMask |= WearableObject::FEMALE | WearableObject::TRANDOSHAN;
		break;
	case 12:
		characterMask |= WearableObject::FEMALE | WearableObject::TWILEK;
		break;
	case 13:
		characterMask |= WearableObject::FEMALE | WearableObject::BOTHAN;
		break;
	case 14:
		characterMask |= WearableObject::FEMALE | WearableObject::ZABRAK;
		break;
	case 15:
		characterMask |= WearableObject::FEMALE | WearableObject::RODIAN;
		break;
	case 16:
		characterMask |= WearableObject::FEMALE | WearableObject::MONCALAMARI;
		break;
	case 17:
		characterMask |= WearableObject::FEMALE | WearableObject::WOOKIEE;
		break;
	case 18:
		characterMask |= WearableObject::FEMALE | WearableObject::SULLUSTAN;
		break;
	case 19:
		characterMask |= WearableObject::FEMALE | WearableObject::ITHORIAN;
		break;
	}

	return characterMask;
}

int CreatureObjectImplementation::canAddObject(SceneObject* object) {
	if (object->isTangibleObject()) {
		TangibleObject* wearable = (TangibleObject*) object;

		uint16 charMask = getWearableMask();
		uint16 objMask = wearable->getPlayerUseMask();

		uint16 maskRes = ~objMask & charMask;

		if (maskRes != 0) {
			/*StringBuffer maskResol;
			maskResol << "returned maskRes :" << maskRes;
			info(maskResol.toString(), true);*/
			return TransferErrorCode::PLAYERUSEMASKERROR;
		}
	}

	return SceneObjectImplementation::canAddObject(object);
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
	ObjectController* objectController = getZoneServer()->getObjectController();

	objectController->activateCommand(_this, actionCRC, 0, 0, "");
}
