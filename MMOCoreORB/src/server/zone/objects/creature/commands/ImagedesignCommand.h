/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef IMAGEDESIGNCOMMAND_H_
#define IMAGEDESIGNCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sessions/ImageDesignSession.h"

class ImagedesignCommand : public QueueCommand {
public:

	ImagedesignCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->hasSkill("social_entertainer_novice")) {
			creature->sendSystemMessage("@ui_imagedesigner:noskill"); // You don't have any image designer skills
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		CreatureObject* playerTarget = NULL;
		CreatureObject* designer = cast<CreatureObject*>( creature);

		if (object != NULL && !object->isPlayerCreature()) {
			creature->sendSystemMessage("@image_designer:not_a_player");//You can only use your Image Design abilities on players.
			return GENERALERROR;
		}

		if (object != NULL && creature->getObjectID() == object->getObjectID())
			playerTarget = designer;
		else
			playerTarget = cast<CreatureObject*>( object.get());

		if (playerTarget == NULL) {
			creature->sendSystemMessage("@image_designer:no_target");//With whom do you want to use you Image Design abilities?
			return GENERALERROR;
		}

		Locker clocker(playerTarget, creature);

		// --- GROUP CHECKING
		if (designer != playerTarget) {
			StringIdChatParameter stringIdNotGrp;
			stringIdNotGrp.setStringId("@image_designer:not_in_same_group");//You must be within the same group as %TT in order to use your Image Design abilites.
			stringIdNotGrp.setTT(playerTarget->getObjectID());

			if (!designer->isGrouped() || designer->getGroupID() != playerTarget->getGroupID()) {
				designer->sendSystemMessage(stringIdNotGrp);
				return GENERALERROR;
			}
		}

		if (playerTarget->isDead()) {
			StringIdChatParameter stringId;
			stringId.setStringId("@image_designer:target_dead");//%TT needs a lot more than a make over.
			stringId.setTT(playerTarget->getObjectID());

			designer->sendSystemMessage(stringId);

			return GENERALERROR;
		}

		if (playerTarget->isInvisible()) {
			designer->sendSystemMessage("You can't image design an invisible player.");
			return GENERALERROR;
		}

		if (!designer->isInRange(playerTarget, 8.0f)) {
			designer->sendSystemMessage("@image_designer:out_of_range");//You must be closer to your target in order to use your Image Design abilities.
			return GENERALERROR;
		}

		/*BuildingObject* buildingObj = cast<BuildingObject*>( designer->getParentRecursively(SceneObject::SALONBUILDING));

		if (buildingObj == NULL) {
			designer->sendSystemMessage("You must be inside an Image Design tent in order to perform that action.");
			if(buildingObj != NULL) {
				int i = buildingObj->getGameObjectType();
				System::out << String::valueOf(i) << endl;
			}
			return GENERALERROR;
		}

		buildingObj = cast<BuildingObject*>( playerTarget->getRootParent());

		if (buildingObj == NULL || buildingObj->getGameObjectType() != BuildingObject::SALONBUILDING) {
			playerTarget->sendSystemMessage("You must be inside an Image Design tent in order to be Image Designed.");
			designer->sendSystemMessage("Your current target is not currently inside a valid Image Design tent.");
			return GENERALERROR;
		}*/

		if (playerTarget->containsActiveSession(SessionFacadeType::IMAGEDESIGN)) {
			if (playerTarget != designer) {
				StringIdChatParameter stringId;
				stringId.setStringId("@image_designer:outstanding_offer"); //%TT already has an outstanding Image Design offer.
				stringId.setTT(playerTarget->getObjectID());

				designer->sendSystemMessage(stringId);

				return GENERALERROR;
			} else {
				designer->sendSystemMessage("@image_designer:already_being_image_designed");//You cannot initiate an Image Design session while being Image Designed.
				return GENERALERROR;
			}
		}

		ManagedReference<Facade*> facade = designer->getActiveSession(SessionFacadeType::IMAGEDESIGN);
		ManagedReference<ImageDesignSession*> session = dynamic_cast<ImageDesignSession*>(facade.get());

		if (session != NULL) {
			designer->sendSystemMessage("@image_designer:already_image_designing");//You are already in the process of an Image Design action.
			return GENERALERROR;
		}

		if (playerTarget->hasSkill("social_entertainer_novice")) {
			ManagedReference<Facade*> facade2 = playerTarget->getActiveSession(SessionFacadeType::IMAGEDESIGN);
			ManagedReference<ImageDesignSession*> targetsSession = dynamic_cast<ImageDesignSession*>(facade.get());

			if (targetsSession != NULL) {
				StringIdChatParameter stringId;
				stringId.setTT(playerTarget->getObjectID());
				stringId.setStringId("@image_designer:target_is_image_designing");//%TT is already Image Designing someone else.

				designer->sendSystemMessage(stringId);

				return GENERALERROR;
			}
		}

		//Create Session
		session = new ImageDesignSession(designer);
		session->deploy();
		session->startImageDesign(designer, playerTarget);

		return SUCCESS;
	}

};

#endif //IMAGEDESIGNCOMMAND_H_
