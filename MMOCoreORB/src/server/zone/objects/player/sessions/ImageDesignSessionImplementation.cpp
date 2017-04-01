/*
 * ImageDesignSessionImplementation.cpp
 *
 *  Created on: Feb 2, 2011
 *      Author: Polonel
 */

#include "engine/engine.h"
#include "server/zone/objects/player/sessions/ImageDesignSession.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/object/ImageDesignMessage.h"
#include "server/zone/managers/skill/imagedesign/ImageDesignManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/ImageDesignPositionObserver.h"
#include "server/zone/objects/player/events/ImageDesignTimeoutEvent.h"
#include "server/zone/objects/player/sessions/MigrateStatsSession.h"
#include "server/zone/objects/player/PlayerObject.h"

void ImageDesignSessionImplementation::initializeTransientMembers() {
	FacadeImplementation::initializeTransientMembers();
}

int ImageDesignSessionImplementation::cancelSession() {
	ManagedReference<CreatureObject*> designerCreature = this->designerCreature.get();
	ManagedReference<CreatureObject*> targetCreature = this->targetCreature.get();

	if (designerCreature != NULL) {
		designerCreature->dropActiveSession(SessionFacadeType::IMAGEDESIGN);

		if (positionObserver != NULL)
			designerCreature->dropObserver(ObserverEventType::POSITIONCHANGED, positionObserver);
	}

	if (targetCreature != NULL) {
		targetCreature->dropActiveSession(SessionFacadeType::IMAGEDESIGN);

		if (positionObserver != NULL)
			targetCreature->dropObserver(ObserverEventType::POSITIONCHANGED, positionObserver);
	}

	dequeueIdTimeoutEvent();

	return 0;
}

void ImageDesignSessionImplementation::startImageDesign(CreatureObject* designer, CreatureObject* targetPlayer) {
	uint64 designerTentID = 0; // Equals False, that controls if you can stat migrate or not (only in a Salon).
	uint64 targetTentID = 0;

	ManagedReference<SceneObject*> obj = designer->getParentRecursively(SceneObjectType::SALONBUILDING);

	if (obj != NULL) // If they are in a salon, enable the tickmark for stat migration.
		designerTentID = obj->getObjectID();

	if (designerTentID != 0) {
		obj = targetPlayer->getParentRecursively(SceneObjectType::SALONBUILDING);

		if (obj != NULL)
			targetTentID = obj->getObjectID();

		if (targetTentID != 0) {
			positionObserver = new ImageDesignPositionObserver(_this.getReferenceUnsafeStaticCast());

			designer->registerObserver(ObserverEventType::POSITIONCHANGED, positionObserver);

			if (targetPlayer != designer)
				targetPlayer->registerObserver(ObserverEventType::POSITIONCHANGED, positionObserver);
		}
	}

	if (targetTentID == 0 || designerTentID == 0) {
		targetTentID = 0;
		designerTentID = 0;
	}

	designer->addActiveSession(SessionFacadeType::IMAGEDESIGN, _this.getReferenceUnsafeStaticCast());

	String hairTemplate;

	Reference<TangibleObject*> targetHair = targetPlayer->getSlottedObject("hair").castTo<TangibleObject*>();

	ImageDesignStartMessage* msg = new ImageDesignStartMessage(designer, designer, targetPlayer, designerTentID, hairTemplate);
	designer->sendMessage(msg);

	if (designer != targetPlayer) {
		targetPlayer->addActiveSession(SessionFacadeType::IMAGEDESIGN, _this.getReferenceUnsafeStaticCast());

		ImageDesignStartMessage* msg2 = new ImageDesignStartMessage(targetPlayer, designer, targetPlayer, targetTentID, hairTemplate);
		targetPlayer->sendMessage(msg2);
	}

	designerCreature = designer;
	targetCreature = targetPlayer;

	idTimeoutEvent = new ImageDesignTimeoutEvent(_this.getReferenceUnsafeStaticCast());
}

void ImageDesignSessionImplementation::updateImageDesign(CreatureObject* updater, uint64 designer, uint64 targetPlayer, uint64 tent, int type, const ImageDesignData& data) {
	ManagedReference<CreatureObject*> strongReferenceTarget = targetCreature.get();
	ManagedReference<CreatureObject*> strongReferenceDesigner = designerCreature.get();

	if (strongReferenceTarget == NULL || strongReferenceDesigner == NULL)
		return;

	Locker locker(strongReferenceDesigner);
	Locker clocker(strongReferenceTarget, strongReferenceDesigner);

	imageDesignData = data;

	CreatureObject* targetObject = NULL;

	if (updater == strongReferenceDesigner)
		targetObject = strongReferenceTarget;
	else
		targetObject = strongReferenceDesigner;

	//ManagedReference<SceneObject*> obj = targetObject->getParentRecursively(SceneObjectType::SALONBUILDING);
	//tent = obj != NULL ? obj->getObjectID()

	ImageDesignChangeMessage* message = new ImageDesignChangeMessage(targetObject->getObjectID(), designer, targetPlayer, tent, type);

	imageDesignData.insertToMessage(message);

	bool commitChanges = false;

	if (imageDesignData.isAcceptedByDesigner()) {
		commitChanges = true;

		if (strongReferenceDesigner != strongReferenceTarget && !imageDesignData.isAcceptedByTarget()) {
			commitChanges = false;

			if (idTimeoutEvent == NULL)
				idTimeoutEvent = new ImageDesignTimeoutEvent(_this.getReferenceUnsafeStaticCast());

			if (!idTimeoutEvent->isScheduled())
				idTimeoutEvent->schedule(120000); //2 minutes
		} else {
			commitChanges = doPayment();
		}
	}

	//System::out << h << endl;
	if (commitChanges) {
		//TODO: set XP Values

		int xpGranted = 0; // Minimum Image Design XP granted (base amount).

		//if (imageDesignData.mi)

		String hairTemplate = imageDesignData.getHairTemplate();

		bool statMig = imageDesignData.isStatMigrationRequested();

		if (statMig && strongReferenceDesigner->getParentRecursively(SceneObjectType::SALONBUILDING)
				&& strongReferenceDesigner->getParentRecursively(SceneObjectType::SALONBUILDING) && strongReferenceDesigner != strongReferenceTarget) {

			ManagedReference<Facade*> facade = strongReferenceTarget->getActiveSession(SessionFacadeType::MIGRATESTATS);
			ManagedReference<MigrateStatsSession*> session = dynamic_cast<MigrateStatsSession*>(facade.get());

			if (session != NULL) {
				session->migrateStats();
				xpGranted = 2000;
			}
		}

		VectorMap<String, float>* bodyAttributes = imageDesignData.getBodyAttributesMap();
		VectorMap<String, uint32>* colorAttributes = imageDesignData.getColorAttributesMap();

		ImageDesignManager* imageDesignManager = ImageDesignManager::instance();

		hairObject = strongReferenceTarget->getSlottedObject("hair").castTo<TangibleObject*>();

		if (type == 1) {
			String oldCustomization;

			if (hairObject != NULL)
				hairObject->getCustomizationString(oldCustomization);

			hairObject = imageDesignManager->createHairObject(strongReferenceDesigner, strongReferenceTarget, imageDesignData.getHairTemplate(), imageDesignData.getHairCustomizationString());

			if (hairObject != NULL) {
				Locker hlocker(hairObject);
				hairObject->setCustomizationString(oldCustomization);
			}

			if (xpGranted < 100)
				xpGranted = 100;
		}

		if (bodyAttributes->size() > 0) {
			if (xpGranted < 300)
				xpGranted = 300;
			for (int i = 0; i < bodyAttributes->size(); ++i) {
				VectorMapEntry<String, float>* entry = &bodyAttributes->elementAt(i);
				imageDesignManager->updateCustomization(strongReferenceDesigner, entry->getKey(), entry->getValue(), strongReferenceTarget);
			}
		}


		if (colorAttributes->size() > 0) {
			if(xpGranted < 100)
				xpGranted = 100;
			for (int i = 0; i < colorAttributes->size(); ++i) {
				VectorMapEntry<String, uint32>* entry = &colorAttributes->elementAt(i);
				imageDesignManager->updateColorCustomization(strongReferenceDesigner, entry->getKey(), entry->getValue(), hairObject, strongReferenceTarget);
			}
		}

		imageDesignManager->updateHairObject(strongReferenceTarget, hairObject);

		// Add holo emote
		String holoemote = imageDesignData.getHoloEmote();
		if( !holoemote.isEmpty() ){

			PlayerObject* ghost = strongReferenceTarget->getPlayerObject();
			ghost->setInstalledHoloEmote( holoemote );  // Also resets number of uses available

			strongReferenceTarget->sendSystemMessage("@image_designer:new_holoemote"); //"Congratulations! You have purchased a new Holo-Emote generator. Type '/holoemote help' for instructions."

			if(xpGranted < 100)
				xpGranted = 100;

		}

		// Drop the Session for both the designer and the targetCreature;
		strongReferenceDesigner->dropActiveSession(SessionFacadeType::IMAGEDESIGN);
		strongReferenceTarget->dropActiveSession(SessionFacadeType::IMAGEDESIGN);

		// Award XP.
		PlayerManager* playerManager = strongReferenceDesigner->getZoneServer()->getPlayerManager();

		if (playerManager != NULL && xpGranted > 0) {
			if(strongReferenceDesigner == strongReferenceTarget)
				xpGranted /= 2;
			playerManager->awardExperience(strongReferenceDesigner, "imagedesigner", xpGranted, true);
		}

		if (idTimeoutEvent != NULL && idTimeoutEvent->isScheduled())
			dequeueIdTimeoutEvent();
	}

	targetObject->sendMessage(message);
}

int ImageDesignSessionImplementation::doPayment() {
	ManagedReference<CreatureObject*> designerCreature = this->designerCreature.get();
	ManagedReference<CreatureObject*> targetCreature = this->targetCreature.get();

	int targetCredits = targetCreature->getCashCredits() + targetCreature->getBankCredits();

	uint32 requiredPayment = imageDesignData.getRequiredPayment();

	// The client should prevent this, but in case it doesn't
	if (targetCredits < requiredPayment) {
		targetCreature->sendSystemMessage("You do not have enough credits to pay the required payment.");
		designerCreature->sendSystemMessage("Target does not have enough credits for the required payment.");

		cancelSession();

		return 0;
	}

	if (requiredPayment <= targetCreature->getCashCredits()) {
		targetCreature->subtractCashCredits(requiredPayment);
		designerCreature->addCashCredits(requiredPayment);
	} else {
		int requiredBankCredits = requiredPayment - targetCreature->getCashCredits();
		targetCreature->subtractCashCredits(targetCreature->getCashCredits());
		targetCreature->subtractBankCredits(requiredBankCredits);
		designerCreature->addCashCredits(requiredPayment);
	}
	return 1;
}

void ImageDesignSessionImplementation::checkDequeueEvent(SceneObject* scene) {
	ManagedReference<CreatureObject*> designerCreature = this->designerCreature.get();
	ManagedReference<CreatureObject*> targetCreature = this->targetCreature.get();

	if (targetCreature == NULL || designerCreature == NULL)
		return;

	if (scene == designerCreature) {
		Locker clocker(targetCreature, designerCreature);

		if (targetCreature->getParentRecursively(SceneObjectType::SALONBUILDING) == NULL || designerCreature->getParentRecursively(SceneObjectType::SALONBUILDING) == NULL)
			return;
	} else if (scene == targetCreature) {
		Locker clocker(designerCreature, targetCreature);

		if (targetCreature->getParentRecursively(SceneObjectType::SALONBUILDING) == NULL || designerCreature->getParentRecursively(SceneObjectType::SALONBUILDING) == NULL)
			return;
	}

	dequeueIdTimeoutEvent();
}

void ImageDesignSessionImplementation::sessionTimeout() {
	ManagedReference<CreatureObject*> designerCreature = this->designerCreature.get();
	ManagedReference<CreatureObject*> targetCreature = this->targetCreature.get();

	if (designerCreature != NULL) {
		Locker locker(designerCreature);

		if (designerCreature->getParentRecursively(SceneObjectType::SALONBUILDING) == NULL || imageDesignData.isAcceptedByDesigner()) {
			designerCreature->sendSystemMessage("Image Design session has timed out. Changes aborted.");

			cancelImageDesign(designerCreature->getObjectID(), targetCreature->getObjectID(), 0, 0, imageDesignData);

			return;
		}
	}

	if (targetCreature != NULL) {
		Locker locker(designerCreature);
		Locker clocker(targetCreature, designerCreature);

		if (targetCreature->getParentRecursively(SceneObjectType::SALONBUILDING) == NULL || imageDesignData.isAcceptedByDesigner()) {
			targetCreature->sendSystemMessage("Image Design session has timed out. Changes aborted.");

			cancelImageDesign(designerCreature->getObjectID(), targetCreature->getObjectID(), 0, 0, imageDesignData);

			return;
		}
	}
}

void ImageDesignSessionImplementation::cancelImageDesign(uint64 designer, uint64 targetPlayer, uint64 tent, int type, const ImageDesignData& data) {
	ManagedReference<CreatureObject*> designerCreature = this->designerCreature.get();
	ManagedReference<CreatureObject*> targetCreature = this->targetCreature.get();

	if (targetCreature == NULL || designerCreature == NULL)
		return;

	Locker locker(designerCreature);
	Locker clocker(targetCreature, designerCreature);

	imageDesignData = data;

	ImageDesignRejectMessage* message = new ImageDesignRejectMessage(targetCreature->getObjectID(), designer, targetPlayer,tent, type);
	imageDesignData.insertToMessage(message);
	targetCreature->sendMessage(message);

	ImageDesignRejectMessage* msg2 = new ImageDesignRejectMessage(designerCreature->getObjectID(), designer, targetPlayer,tent, type);
	imageDesignData.insertToMessage(msg2);
	designerCreature->sendMessage(msg2);


	//TODO: Needs research.

	cancelSession();
}
