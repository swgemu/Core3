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
#include "server/zone/managers/professions/imagedesign/ImageDesignManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/objects/player/events/ImageDesignTimeoutEvent.h"

void ImageDesignSessionImplementation::startImageDesign(PlayerCreature* designer, PlayerCreature* targetPlayer) {
	uint64 tentID = 0;

	ManagedReference<SceneObject*> obj = designer->getParentRecursively(SceneObject::SALONBUILDING);

	if (obj != NULL)
		tentID = obj->getObjectID();

	designer->addActiveSession(SessionFacadeType::IMAGEDESIGN, _this);

	ImageDesignStartMessage* msg = new ImageDesignStartMessage(designer, designer, targetPlayer, tentID, 0);
	designer->sendMessage(msg);

	if (designer != targetPlayer) {
		targetPlayer->addActiveSession(SessionFacadeType::IMAGEDESIGN, _this);

		ImageDesignStartMessage* msg = new ImageDesignStartMessage(targetPlayer, designer, targetPlayer, tentID, 0);
		targetPlayer->sendMessage(msg);
	}

	designerCreature = designer;
	targetCreature = targetPlayer;

	idTimeoutEvent = new ImageDesignTimeoutEvent(_this);
}

void ImageDesignSessionImplementation::updateImageDesign(uint64 designer, uint64 targetPlayer, uint64 tent, int type, const ImageDesignData& data) {
	imageDesignData = data;

	ManagedReference<SceneObject*> strongReferenceTarget = targetCreature.get();
	ManagedReference<SceneObject*> strongReferenceDesigner = designerCreature.get();

	if (strongReferenceTarget == NULL || strongReferenceDesigner == NULL)
		return;

	Locker locker(designerCreature);
	Locker clocker(targetCreature, designerCreature);

	ImageDesignChangeMessage* message = new ImageDesignChangeMessage(targetPlayer, designer, targetPlayer, tent, type);

	imageDesignData.insertToMessage(message);

	bool commitChanges = false;

	if (imageDesignData.isAcceptedByDesigner()) {
		commitChanges = true;

		if (designerCreature != targetCreature && !imageDesignData.isAcceptedByTarget()) {
			commitChanges = false;

			if (!idTimeoutEvent->isScheduled())
				idTimeoutEvent->schedule(120000); //2 minutes
		} else {
			commitChanges = doPayment();
		}
	}

	String h = imageDesignData.getHairCustomizationString();
	//System::out << h << endl;
	if (commitChanges) {
		//TODO: set XP Values

		String hairTemplate = imageDesignData.getHairTemplate();

		VectorMap<String, float>* bodyAttributes = imageDesignData.getBodyAttributesMap();
		VectorMap<String, uint32>* colorAttributes = imageDesignData.getColorAttributesMap();

		imageDesignManager = ProfessionManager::instance()->getImageDesignManager();

		// if Designer is changing just Hair (with no color changes) set default hair template. BUG FIX!
		if (bodyAttributes->isEmpty() && colorAttributes->isEmpty()) {
			String hairCustomization = "";
			imageDesignManager->updateHairObject(targetCreature, hairTemplate, hairCustomization);
		}

		for (int i = 0; i < bodyAttributes->size(); ++i) {
			VectorMapEntry<String, float>* entry = &bodyAttributes->elementAt(i);
			imageDesignManager->updateCustomization(entry->getKey(), entry->getValue(), hairTemplate, targetCreature);
		}

		for (int i = 0; i < colorAttributes->size(); ++i) {
			VectorMapEntry<String, uint32>* entry = &colorAttributes->elementAt(i);
			imageDesignManager->updateCustomization(entry->getKey(), entry->getValue(), hairTemplate, targetCreature);
		}

		// Drop the Session for both the designer and the targetCreature;
		designerCreature->dropActiveSession(SessionFacadeType::IMAGEDESIGN);
		targetCreature->dropActiveSession(SessionFacadeType::IMAGEDESIGN);

		if (idTimeoutEvent->isScheduled())
			dequeueIdTimeoutEvent();
	}

	if (targetCreature->getObjectID() == targetPlayer) {
		targetCreature->sendMessage(message);
	} else {
		designerCreature->sendMessage(message);
	}
}

int ImageDesignSessionImplementation::doPayment() {
	int targetCash = targetCreature->getCashCredits();

	uint32 requiredPayment = imageDesignData.getRequiredPayment();

	// The client should pervent this, but in case it doesn't
	if (targetCash < requiredPayment) {
		targetCreature->sendSystemMessage("You do not have enough cash to pay the required payment.");
		designerCreature->sendSystemMessage("Target does not have enough cash for the required payment.");

		cancelSession();

		return 0;
	}

	targetCreature->substractCashCredits(requiredPayment);
	designerCreature->addCashCredits(requiredPayment);

	return 1;

}

void ImageDesignSessionImplementation::cancelImageDesign(uint64 designer, uint64 targetPlayer, uint64 tent, int type, const ImageDesignData& data) {
	imageDesignData = data;

	if (targetCreature == NULL || designerCreature == NULL)
			return;

	Locker locker(designerCreature);
	Locker clocker(targetCreature, designerCreature);

	ImageDesignRejectMessage* message = new ImageDesignRejectMessage(designer, targetPlayer,tent, type);

	imageDesignData.insertToMessage(message);

	targetCreature->sendMessage(message);
	/*
	if (designerCreature == targetCreature) {
	} else if(object == designer) {
		message = new ImageDesignRejectMessage(targetPlayer,designer,targetPlayer,tent,type);
	} else if(object == targetPlayer) {
		message = new ImageDesignRejectMessage(designer,designer,targetPlayer,tent,type);
	}
	*/

	//TODO: Needs research.

	cancelSession();
}
