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

#include "server/zone/managers/object/ObjectManager.h"
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
#include "server/zone/ZoneServer.h"

/*CreatureObjectImplementation::CreatureObjectImplementation(LuaObject* templateData) :
	TangibleObjectImplementation(templateData), baseHAM(9, 1), wounds(9, 1), encumbrances(3, 1), hamList(9, 1),
	maxHamList(9, 1) {

	setLoggingName("CreatureObject");

	loadTemplateData(templateData);
}*/

void CreatureObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("CreatureObject");
}

void CreatureObjectImplementation::loadTemplateData(LuaObject* templateData) {
	bankCredits = 0;
	cashCredits = 0;

	posture = 0;
	factionRank = 0;

	creatureLinkID = 0;

	shockWounds = 0.f;

	gender = templateData->getIntField("gender");
	species = templateData->getIntField("species");
	slopeModPercent = templateData->getFloatField("slopeModPercent");
	slopeModAngle = templateData->getFloatField("slopeModAngle");

	stateBitmask = 0;
	terrainNegotiation = 0.f;

	listenToID = 0;

	level = 0;

	weaponID = 0;
	groupID = 0;
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

	for (int i = 0; i < 9; ++i) {
		baseHAM.add(100);
	}

	for (int i = 0; i < 9; ++i) {
		wounds.add(0);
	}

	for (int i = 0; i < 9; ++i) {
		hamList.add(100);
	}

	for (int i = 0; i < 9; ++i) {
		maxHamList.add(100);
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

void CreatureObjectImplementation::sendSystemMessage(const String& file, const String& str, uint64 targetid) {
	if (!isPlayerCreature())
		return;

	ChatSystemMessage* msg = new ChatSystemMessage(file, str, targetid);
	sendMessage(msg);
}

void CreatureObjectImplementation::sendSystemMessage(const String& file, const String& str, StfParameter* param) {
	if (!isPlayerCreature())
		return;

	ChatSystemMessage* msg = new ChatSystemMessage(file, str, param);
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

void CreatureObjectImplementation::setWeaponID(uint64 objectID, bool notifyClient) {
	weaponID = objectID;

	if (notifyClient) {
		CreatureObjectDeltaMessage6* msg = new CreatureObjectDeltaMessage6(_this);
		msg->updateWeapon();
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

void CreatureObjectImplementation::setHAM(int type, int value, bool notifyClient) {
	if (hamList.get(type) == value)
		return;

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

		broadcastMessage(delta, true);
	}
}

void CreatureObjectImplementation::setPosture(int newPosture, bool notifyClient) {
	if (posture == newPosture)
		return;

	posture = newPosture;

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
