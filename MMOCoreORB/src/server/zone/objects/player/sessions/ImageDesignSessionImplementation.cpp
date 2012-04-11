/*
 * ImageDesignSessionImplementation.cpp
 *
 *  Created on: Feb 2, 2011
 *      Author: Polonel
 */

#include "engine/engine.h"
#include "ImageDesignSession.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/object/ImageDesignMessage.h"
#include "server/zone/packets/object/ImageDesignRejectMessageCallback.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/skill/imagedesign/ImageDesignManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/ZoneServer.h"
#include "ImageDesignPositionObserver.h"
#include "server/zone/objects/player/events/ImageDesignTimeoutEvent.h"
#include "server/zone/objects/player/sessions/MigrateStatsSession.h"

void ImageDesignSessionImplementation::initializeTransientMembers() {
	FacadeImplementation::initializeTransientMembers();
}

int ImageDesignSessionImplementation::cancelSession() {
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
			positionObserver = new ImageDesignPositionObserver(_this);

			designer->registerObserver(ObserverEventType::POSITIONCHANGED, positionObserver);

			if (targetPlayer != designer)
				targetPlayer->registerObserver(ObserverEventType::POSITIONCHANGED, positionObserver);
		}
	}

	if (targetTentID == 0 || designerTentID == 0) {
		targetTentID = 0;
		designerTentID = 0;
	}

	designer->addActiveSession(SessionFacadeType::IMAGEDESIGN, _this);

	String hairTemplate;

	TangibleObject* targetHair = dynamic_cast<TangibleObject*>(targetPlayer->getSlottedObject("hair"));

	ImageDesignStartMessage* msg = new ImageDesignStartMessage(designer, designer, targetPlayer, designerTentID, hairTemplate);
	designer->sendMessage(msg);

	if (designer != targetPlayer) {
		targetPlayer->addActiveSession(SessionFacadeType::IMAGEDESIGN, _this);

		ImageDesignStartMessage* msg2 = new ImageDesignStartMessage(targetPlayer, designer, targetPlayer, targetTentID, hairTemplate);
		targetPlayer->sendMessage(msg2);
	}

	designerCreature = designer;
	targetCreature = targetPlayer;

	idTimeoutEvent = new ImageDesignTimeoutEvent(_this);
}

void ImageDesignSessionImplementation::updateImageDesign(CreatureObject* updater, uint64 designer, uint64 targetPlayer, uint64 tent, int type, const ImageDesignData& data) {
	ManagedReference<SceneObject*> strongReferenceTarget = targetCreature.get();
	ManagedReference<SceneObject*> strongReferenceDesigner = designerCreature.get();

	if (strongReferenceTarget == NULL || strongReferenceDesigner == NULL)
		return;

	Locker locker(designerCreature);
	Locker clocker(targetCreature, designerCreature);

	imageDesignData = data;

	CreatureObject* targetObject = NULL;

	if (updater == designerCreature)
		targetObject = targetCreature;
	else
		targetObject = designerCreature;

	//ManagedReference<SceneObject*> obj = targetObject->getParentRecursively(SceneObjectType::SALONBUILDING);
	//tent = obj != NULL ? obj->getObjectID()

	ImageDesignChangeMessage* message = new ImageDesignChangeMessage(targetObject->getObjectID(), designer, targetPlayer, tent, type);

	imageDesignData.insertToMessage(message);

	bool commitChanges = false;

	if (imageDesignData.isAcceptedByDesigner()) {
		commitChanges = true;

		if (designerCreature != targetCreature && !imageDesignData.isAcceptedByTarget()) {
			commitChanges = false;

			if (idTimeoutEvent == NULL)
				idTimeoutEvent = new ImageDesignTimeoutEvent(_this);

			if (!idTimeoutEvent->isScheduled())
				idTimeoutEvent->schedule(120000); //2 minutes
		} else {
			commitChanges = doPayment();
		}
	}

	//System::out << h << endl;
	if (commitChanges) {
		//TODO: set XP Values

		int xpGranted = 50; // Minimum Image Design XP granted (base amount).

		//if (imageDesignData.mi)

		String hairTemplate = imageDesignData.getHairTemplate();

		bool statMig = imageDesignData.isStatMigrationRequested();

		if (statMig && targetCreature->getParentRecursively(SceneObjectType::SALONBUILDING)
				&& designerCreature->getParentRecursively(SceneObjectType::SALONBUILDING) && designerCreature != targetCreature) {

			ManagedReference<Facade*> facade = targetCreature->getActiveSession(SessionFacadeType::MIGRATESTATS);
			ManagedReference<MigrateStatsSession*> session = dynamic_cast<MigrateStatsSession*>(facade.get());

			if (session != NULL) {
				session->migrateStats();
			}
		}

		VectorMap<String, float>* bodyAttributes = imageDesignData.getBodyAttributesMap();
		VectorMap<String, uint32>* colorAttributes = imageDesignData.getColorAttributesMap();

		ImageDesignManager* imageDesignManager = ImageDesignManager::instance();

		hairObject = dynamic_cast<TangibleObject*>(targetCreature->getSlottedObject("hair"));

		if (type == 1) {
			String oldCustomization;

			if (hairObject != NULL)
				hairObject->getCustomizationString(oldCustomization);

			hairObject = imageDesignManager->createHairObject(designerCreature, targetCreature, imageDesignData.getHairTemplate(), imageDesignData.getHairCustomizationString());

			if (hairObject != NULL)
				hairObject->setCustomizationString(oldCustomization);
		}

		for (int i = 0; i < bodyAttributes->size(); ++i) {
			VectorMapEntry<String, float>* entry = &bodyAttributes->elementAt(i);
			imageDesignManager->updateCustomization(designerCreature, entry->getKey(), entry->getValue(), targetCreature);
			xpGranted += 25;
		}

		for (int i = 0; i < colorAttributes->size(); ++i) {
			VectorMapEntry<String, uint32>* entry = &colorAttributes->elementAt(i);
			imageDesignManager->updateColorCustomization(designerCreature, entry->getKey(), entry->getValue(), hairObject, targetCreature);
			xpGranted += 25;
		}

		imageDesignManager->updateHairObject(targetCreature, hairObject);

		// Drop the Session for both the designer and the targetCreature;
		designerCreature->dropActiveSession(SessionFacadeType::IMAGEDESIGN);
		targetCreature->dropActiveSession(SessionFacadeType::IMAGEDESIGN);

		// Award XP.
		PlayerManager* playerManager = designerCreature->getZoneServer()->getPlayerManager();

		if (playerManager != NULL && designerCreature != targetCreature)
			playerManager->awardExperience(designerCreature, "imagedesigner", xpGranted, true);

		if (idTimeoutEvent != NULL && idTimeoutEvent->isScheduled())
			dequeueIdTimeoutEvent();
	}

	targetObject->sendMessage(message);
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

	targetCreature->subtractCashCredits(requiredPayment);
	designerCreature->addCashCredits(requiredPayment);

	return 1;

}

void ImageDesignSessionImplementation::checkDequeueEvent() {
	ManagedReference<SceneObject*> strongReferenceTarget = targetCreature.get();
	ManagedReference<SceneObject*> strongReferenceDesigner = designerCreature.get();

	if (targetCreature == NULL || designerCreature == NULL)
		return;

	Locker locker(designerCreature);
	Locker clocker(targetCreature, designerCreature);

	if (targetCreature->getParentRecursively(SceneObjectType::SALONBUILDING) == NULL || designerCreature->getParentRecursively(SceneObjectType::SALONBUILDING) == NULL)
		return;

	dequeueIdTimeoutEvent();
}

void ImageDesignSessionImplementation::sessionTimeout() {
	ManagedReference<SceneObject*> strongReferenceTarget = targetCreature.get();
	ManagedReference<SceneObject*> strongReferenceDesigner = designerCreature.get();

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
	ManagedReference<SceneObject*> strongReferenceTarget = targetCreature.get();
	ManagedReference<SceneObject*> strongReferenceDesigner = designerCreature.get();

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
