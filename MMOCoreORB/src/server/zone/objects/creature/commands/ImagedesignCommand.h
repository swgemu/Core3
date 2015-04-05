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
