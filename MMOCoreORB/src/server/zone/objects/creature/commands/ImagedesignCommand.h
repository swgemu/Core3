/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef IMAGEDESIGNCOMMAND_H_
#define IMAGEDESIGNCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/ImageDesignMessage.h"
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

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (!creature->hasSkill("social_entertainer_novice")) {
			creature->sendSystemMessage("@ui_imagedesigner:noskill"); // You don't have any image designer skills
			return GENERALERROR;
		}

		//Disabled again for public use until bugs can be worked out.
		//return SUCCESS;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		CreatureObject* playerTarget = NULL;
		CreatureObject* designer = cast<CreatureObject*>( creature);

		if (object == NULL || !object->isPlayerCreature())
			playerTarget = designer;
		else
			playerTarget = cast<CreatureObject*>( object.get());

		Locker clocker(playerTarget, creature);

		if (playerTarget->isDead()) {
			designer->sendSystemMessage("@image_designer:target_dead");
			return GENERALERROR;
		}

		if (playerTarget->isInvisible()) {
			designer->sendSystemMessage("You can't image design an invisible player.");
			return GENERALERROR;
		}

		// --- GROUP CHECKING
		if (designer != playerTarget) {
			StringIdChatParameter stringIdNotGrp;
			stringIdNotGrp.setStringId("@image_designer:not_in_same_group");
			stringIdNotGrp.setTT(playerTarget);

			if (!designer->isGrouped() || designer->getGroupID() != playerTarget->getGroupID()) {
				//You must be within the same group as %TT in order to use your Image Design abilites.
				designer->sendSystemMessage(stringIdNotGrp);
				return GENERALERROR;
			}
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

		if (playerTarget->containsActiveSession(SessionFacadeType::IMAGEDESIGN) && playerTarget != designer) {
			StringIdChatParameter stringId;
			stringId.setStringId("@image_designer:outstanding_offer"); //%TT already has an outstanding Image Design offer.
			stringId.setTT(playerTarget);

			designer->sendSystemMessage(stringId);

			return GENERALERROR;
		}

		ManagedReference<Facade*> facade = designer->getActiveSession(SessionFacadeType::IMAGEDESIGN);
		ManagedReference<ImageDesignSession*> session = dynamic_cast<ImageDesignSession*>(facade.get());

		if (session != NULL) {
			designer->sendSystemMessage("@image_designer:already_image_designing");
			return GENERALERROR;
		}

		//Create Session
		session = new ImageDesignSession(designer);
		session->deploy();
		session->startImageDesign(designer, playerTarget);

		return SUCCESS;
	}

};

#endif //IMAGEDESIGNCOMMAND_H_
