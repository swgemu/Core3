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

	if (targetCreature == NULL || designerCreature == NULL)
		return;

	Locker locker(designerCreature);
	Locker clocker(targetCreature, designerCreature);

	ImageDesignChangeMessage* message = NULL;

	if (designerCreature == targetCreature) {
		// do not send packet!
	} else if (object == designer) {
		// Coming from the Designer, send to Target!
		message = new ImageDesignChangeMessage(targetPlayer,designer,targetPlayer,tent,type);
	} else if(object == targetPlayer) {
		// Coming from the Target, send to the Designer!
		message = new ImageDesignChangeMessage(designer,designer,targetPlayer,tent,type);;
	}

	if (message != NULL) {
		message->insertAscii(hairObject);

		message->insertAscii(ukstring1);

		message->insertInt(ukint1);
		message->insertInt(timestamp);

		message->insertInt(requiredPayment);
		message->insertInt(offeredPayment);

		message->insertByte(designerAccepted);
		message->insertInt(targetAccepted);

		message->insertByte(statMigration);

		message->insertInt(ukint4);
		message->insertInt(ukint5);
		message->insertInt(ukint6);
		message->insertInt(ukint7);

		message->insertInt(sizeFloatAttrs);
	}

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

	try {
		if (commitChanges)
			idMgr = ProfessionManager::instance()->getImageDesignManager();

		for (int i = 0; i < floatMap.size(); ++i) {
			String& key = floatMap.elementAt(i).getKey();
			float value = floatMap.elementAt(i).getValue();

			if (message != NULL) {
				message->insertAscii(key);
				message->insertFloat(value);
			}

			if (commitChanges)
				idMgr->updateCustomization(key,value, targetCreature);

		}

		if (message != NULL)
			message->insertInt(attributesSize);

		for (int i = 0; i < colorMap.size(); ++i) {
			String& key = colorMap.elementAt(i).getKey();
			uint32 value = colorMap.elementAt(i).getValue();

			if (message != NULL) {
				message->insertAscii(key.toCharArray());
				message->insertInt(value);
			}

			if (commitChanges)
				idMgr->updateCustomization(key,value,targetCreature);

		}

	} catch (...) {
		System::out << "Error happened before packet sent in ImageDesignSessionImplementation.cpp" << endl;
	}

	if (message != NULL)
		message->insertAscii(holoEmote);

	if (message != NULL) {
		if (object == designer) {
			// Coming from the Designer, send to Target!
			targetCreature->sendMessage(message);
		} else if (object == targetPlayer) {
			// Coming from the Target, send to the Designer!
			designerCreature->sendMessage(message);
		} else
			delete message;
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

	if (targetCreature == NULL || designerCreature == NULL)
			return;

	Locker locker(designerCreature);

	Locker clocker(targetCreature, designerCreature);

	ImageDesignRejectMessage* message = NULL;

	if (designerCreature == targetCreature) {
		// do not send packet!
	} else if(object == designer) {
		// Coming from the Designer, send to Target!
		message = new ImageDesignRejectMessage(targetPlayer,designer,targetPlayer,tent,type);

	} else if(object == targetPlayer) {
		// Coming from the Target, send to the Designer!
		message = new ImageDesignRejectMessage(designer,designer,targetPlayer,tent,type);
	}

	if (message != NULL) {
		message->insertAscii(hairObject);

		message->insertAscii(ukstring1);

		message->insertInt(ukint1);
		message->insertInt(timestamp);

		message->insertInt(requiredPayment);
		message->insertInt(offeredPayment);

		message->insertByte(designerAccepted);
		message->insertInt(targetAccepted);

		message->insertByte(statMigration);

		message->insertInt(ukint4);
		message->insertInt(ukint5);
		message->insertInt(ukint6);
		message->insertInt(ukint7);

		message->insertInt(sizeFloatAttrs);

		try {
			for (int i = 0; i < floatMap.size(); ++i) {
				String& key = floatMap.elementAt(i).getKey();
				float value = floatMap.elementAt(i).getValue();

				message->insertAscii(key);
				message->insertFloat(value);
			}

			message->insertInt(attributesSize);

			for (int i = 0; i < colorMap.size(); ++i) {
				String& key = colorMap.elementAt(i).getKey();
				uint32 value = colorMap.elementAt(i).getValue();

				message->insertAscii(key.toCharArray());
				message->insertInt(value);
			}

		} catch(...) {
			System::out << "Error happened before packet sent in ImageDesignSessionImplementation.cpp" << endl;
		}

		message->insertAscii(holoEmote);

		if (object == designer) {
			// Coming from the Designer, send to Target!
			targetCreature->sendMessage(message);

		} else if (object == targetPlayer) {
			// Coming from the Target, send to the Designer!
			designerCreature->sendMessage(message);

		} else
			delete message;
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
