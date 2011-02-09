/*
 * ImageDesignSessionImplementation.cpp
 *
 *  Created on: Feb 2, 2011
 *      Author: Polonel
 */

#include "engine/engine.h"
#include "ImageDesignSession.h"
#include "server/zone/packets/object/ImageDesignMessage.h"
#include "server/zone/packets/object/ImageDesignRejectMessageCallback.h"
#include "server/zone/managers/professions/ProfessionManager.h"
#include "server/zone/managers/professions/ImageDesignManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/objects/player/events/ImageDesignTimeoutEvent.h"

int ImageDesignSessionImplementation::initializeSession() {
	return 0;
}

void ImageDesignSessionImplementation::startImageDesign(PlayerCreature* object, PlayerCreature* designer, PlayerCreature* targetPlayer, uint64 tent, int type)
{
	ImageDesignStartMessage* msg = new ImageDesignStartMessage(object,designer,targetPlayer,tent,type);
	object->sendMessage(msg);

	designerCreature = designer;
	targetCreature = targetPlayer;

	idTimeoutEvent = new ImageDesignTimeoutEvent(_this);

}

void ImageDesignSessionImplementation::updateImageDesign(uint64 object, uint64 designer, uint64 targetPlayer, uint64 tent, int type)
{
	ImageDesignChangeMessage* msgDesigner = new ImageDesignChangeMessage(designer,designer,targetPlayer,tent,type);
	ImageDesignChangeMessage* msgTarget = new ImageDesignChangeMessage(targetPlayer,designer,targetPlayer,tent,type);

	msgDesigner->insertAscii(hairObject);
	msgTarget->insertAscii(hairObject);

	msgDesigner->insertAscii(ukstring1);
	msgTarget->insertAscii(ukstring1);

	msgDesigner->insertInt(ukint1);
	msgTarget->insertInt(ukint1);
	msgDesigner->insertInt(timestamp);
	msgTarget->insertInt(timestamp);

	msgDesigner->insertInt(requiredPayment);
	msgTarget->insertInt(requiredPayment);
	msgDesigner->insertInt(offeredPayment);
	msgTarget->insertInt(offeredPayment);

	msgDesigner->insertByte(designerAccepted);
	msgTarget->insertByte(designerAccepted);
	msgDesigner->insertInt(targetAccepted);
	msgTarget->insertInt(targetAccepted);

	msgDesigner->insertByte(statMigration);
	msgTarget->insertByte(statMigration);

	msgDesigner->insertInt(ukint4);
	msgTarget->insertInt(ukint4);
	msgDesigner->insertInt(ukint5);
	msgTarget->insertInt(ukint5);
	msgDesigner->insertInt(ukint6);
	msgTarget->insertInt(ukint6);
	msgDesigner->insertInt(ukint7);
	msgTarget->insertInt(ukint7);

	msgDesigner->insertInt(sizeFloatAttrs);
	msgTarget->insertInt(sizeFloatAttrs);

	if(targetCreature == NULL || designerCreature == NULL)
		return;

	bool commitChanges = false;
	//TODO: set XP Values
	if (designerAccepted == 1 && targetCreature == designerCreature)
		commitChanges = true;

	// Designer Accepted but waiting on target. Start the timeout event. (AFK Target)
	if (designerAccepted == 1 && targetAccepted == 0 && targetCreature != designerCreature) {
		if (!idTimeoutEvent->isScheduled())
			idTimeoutEvent->schedule(120000);
	}

	if (designerAccepted == 1 && targetAccepted == 1 && targetCreature != designerCreature) {
		if (doPayment())
			commitChanges = true;
	}

	try{

		if (commitChanges)
			idMgr = ProfessionManager::instance()->getImageDesignManager();

		for (int i = 0; i < floatMap.size(); ++i) {
			String& key = floatMap.elementAt(i).getKey();
			float value = floatMap.elementAt(i).getValue();

			msgDesigner->insertAscii(key);
			msgTarget->insertAscii(key);
			msgDesigner->insertFloat(value);
			msgTarget->insertFloat(value);

			if(commitChanges)
				idMgr->updateCustomization(key,value, targetCreature);

		}

		msgDesigner->insertInt(attributesSize);
		msgTarget->insertInt(attributesSize);

		for (int i = 0; i < colorMap.size(); ++i) {
			String& key = colorMap.elementAt(i).getKey();
			uint32 value = colorMap.elementAt(i).getValue();

			msgDesigner->insertAscii(key.toCharArray());
			msgTarget->insertAscii(key.toCharArray());
			msgDesigner->insertInt(value);
			msgTarget->insertInt(value);

			if(commitChanges)
				idMgr->updateCustomization(key,value,targetCreature);

		}


	} catch(...) {
		System::out << "Error happened before packet sent in ImageDesignSessionImplementation.cpp" << endl;
	}

	msgDesigner->insertAscii(holoEmote);
	msgTarget->insertAscii(holoEmote);

	if (designerCreature == targetCreature) {
		// do not send packet!
	} else if(object == designer) {
		// Coming from the Designer, send to Target!
		targetCreature->sendMessage(msgTarget);

	} else if(object == targetPlayer) {
		// Coming from the Target, send to the Designer!
		designerCreature->sendMessage(msgDesigner);
	}

	if (commitChanges) {
		idMgr->updateHairObject(targetCreature,hairObject);

		designerCreature->dropActiveSession(3);
		targetCreature->dropActiveSession(3);

		if (idTimeoutEvent->isScheduled())
			_this->dequeueIdTimeoutEvent();

		targetCreature->updateToDatabase();

	}

	floatMap.removeAll();
	colorMap.removeAll();
}

int ImageDesignSessionImplementation::doPayment() {
	int targetCash = targetCreature->getCashCredits();
	// The client should pervent this, but in case it doesn't
	if (targetCash < requiredPayment) {
		targetCreature->sendSystemMessage("You do not have enough cash to pay the required payment.");
		designerCreature->sendSystemMessage("Target does not have enough cash for the required payment.");

		_this->cancelSession();

		return 0;
	}

	targetCreature->substractCashCredits(requiredPayment);
	designerCreature->addCashCredits(requiredPayment);

	return 1;

}

void ImageDesignSessionImplementation::cancelImageDesign(uint64 object, uint64 designer, uint64 targetPlayer, uint64 tent, int type) {
	// Send reject Packet callback
	ImageDesignRejectMessage* msgDesigner = new ImageDesignRejectMessage(designer,designer,targetPlayer,tent,type);
	ImageDesignRejectMessage* msgTarget = new ImageDesignRejectMessage(targetPlayer,designer,targetPlayer,tent,type);

	msgDesigner->insertAscii(hairObject);
	msgTarget->insertAscii(hairObject);

	msgDesigner->insertAscii(ukstring1);
	msgTarget->insertAscii(ukstring1);

	msgDesigner->insertInt(ukint1);
	msgTarget->insertInt(ukint1);
	msgDesigner->insertInt(timestamp);
	msgTarget->insertInt(timestamp);

	msgDesigner->insertInt(requiredPayment);
	msgTarget->insertInt(requiredPayment);
	msgDesigner->insertInt(offeredPayment);
	msgTarget->insertInt(offeredPayment);

	msgDesigner->insertByte(designerAccepted);
	msgTarget->insertByte(designerAccepted);
	msgDesigner->insertInt(targetAccepted);
	msgTarget->insertInt(targetAccepted);

	msgDesigner->insertByte(statMigration);
	msgTarget->insertByte(statMigration);

	msgDesigner->insertInt(ukint4);
	msgTarget->insertInt(ukint4);
	msgDesigner->insertInt(ukint5);
	msgTarget->insertInt(ukint5);
	msgDesigner->insertInt(ukint6);
	msgTarget->insertInt(ukint6);
	msgDesigner->insertInt(ukint7);
	msgTarget->insertInt(ukint7);

	msgDesigner->insertInt(sizeFloatAttrs);
	msgTarget->insertInt(sizeFloatAttrs);

	if(targetCreature == NULL || designerCreature == NULL)
		return;

	try{

		for (int i = 0; i < floatMap.size(); ++i) {
			String& key = floatMap.elementAt(i).getKey();
			float value = floatMap.elementAt(i).getValue();

			msgDesigner->insertAscii(key);
			msgTarget->insertAscii(key);
			msgDesigner->insertFloat(value);
			msgTarget->insertFloat(value);

		}

		msgDesigner->insertInt(attributesSize);
		msgTarget->insertInt(attributesSize);

		for (int i = 0; i < colorMap.size(); ++i) {
			String& key = colorMap.elementAt(i).getKey();
			uint32 value = colorMap.elementAt(i).getValue();

			msgDesigner->insertAscii(key.toCharArray());
			msgTarget->insertAscii(key.toCharArray());
			msgDesigner->insertInt(value);
			msgTarget->insertInt(value);

		}

	} catch(...) {
		System::out << "Error happened before packet sent in ImageDesignSessionImplementation.cpp" << endl;
	}

	msgDesigner->insertAscii(holoEmote);
	msgTarget->insertAscii(holoEmote);

	if (designerCreature == targetCreature) {
		// do not send packet!
	} else if(object == designer) {
		// Coming from the Designer, send to Target!
		targetCreature->sendMessage(msgTarget);

	} else if(object == targetPlayer) {
		// Coming from the Target, send to the Designer!
		designerCreature->sendMessage(msgDesigner);
	}

	_this->cancelSession();

	floatMap.removeAll();
	colorMap.removeAll();
}

void ImageDesignSessionImplementation::setFloatMap(VectorMap<String, float>& map) {
	floatMap = map;
}
void ImageDesignSessionImplementation::setColorMap(VectorMap<String, uint32>& map) {
	colorMap = map;
}
