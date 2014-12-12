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

#ifndef GIVEITEMCOMMAND_H_
#define GIVEITEMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"

#include "server/zone/objects/tangible/attachment/Attachment.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/objects/tangible/components/droid/DroidStimpackModuleDataComponent.h"
#include "server/zone/objects/tangible/components/droid/DroidTrapModuleDataComponent.h"
#include "server/zone/objects/creature/AiAgent.h"

class GiveItemCommand : public QueueCommand {
public:

	GiveItemCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer args(arguments.toString());

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (!args.hasMoreTokens())
			return GENERALERROR;

		uint64 targetObjectID = 0;

		try {
			targetObjectID = args.getLongToken();
		} catch (Exception& e) {
			error("could not get long token in " + arguments.toString());
			error(e.getMessage());

			return GENERALERROR;
		}

		ManagedReference<SceneObject*> sceno = server->getZoneServer()->getObject(targetObjectID);

		if (object != NULL) {

			ManagedReference<SceneObject*> objectsParent = object->getParent();

			if (objectsParent == NULL)
				return GENERALERROR;

			if (!objectsParent->checkContainerPermission(creature, ContainerPermissions::MOVEOUT))
				return GENERALERROR;

			if (!object->checkContainerPermission(creature, ContainerPermissions::MOVECONTAINER))
				return GENERALERROR;

			if (object->isAttachment()) {
				Attachment* attachment = cast<Attachment*>( object.get());

				if (sceno->isWearableObject() && sceno->isASubChildOf(creature)) {
					WearableObject* wearable = cast<WearableObject*>( sceno.get());
					wearable->applyAttachment(creature, attachment);
					return SUCCESS;
				}

			} else if (sceno != NULL) {
				Locker clocker(sceno, creature);

				if (sceno->isVendor() && sceno->isCreatureObject()) {

					if (object->isWearableObject() || object->isWeaponObject()) {

						CreatureObject* vendor = cast<CreatureObject*>(sceno.get());

						CreatureObject* player = cast<CreatureObject*>(creature);
						if (player->getSkillMod("hiring") < 90) {

							UnicodeString message("@player_structure:wear_noway");
							ChatManager* chatMan = server->getChatManager();
							chatMan->broadcastMessage(vendor, message, object->getObjectID(), vendor->getMoodID(), 0);
							return GENERALERROR;
						}

						DataObjectComponentReference* data = sceno->getDataObjectComponent();
						if(data == NULL || data->get() == NULL || !data->get()->isVendorData()) {
							error("Vendor has no data component");
							return GENERALERROR;
						}

						VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
						if(vendorData == NULL) {
							error("Vendor has invalid data component");
							return GENERALERROR;
						}

						TangibleObject* clothing = cast<TangibleObject*>(object.get());

						if (creature->getObjectID() != vendorData->getOwnerId())
							return GENERALERROR;

						if(vendor == NULL || vendor->getZone() == NULL || vendor->getZone()->getCreatureManager() == NULL)
							return GENERALERROR;

						if(vendor->getZone()->getCreatureManager()->addWearableItem(vendor, clothing))
							return SUCCESS;
						else
							return GENERALERROR;

					}
				}
				else if( sceno->isPet() && object->getGameObjectType() == SceneObjectType::FOOD){
					Reference<AiAgent*> aiAgent = sceno.castTo<AiAgent*>();
					if( aiAgent != NULL ){

						Locker crossLocker(aiAgent, creature);

						PetManager* petManager = aiAgent->getZoneServer()->getPetManager();
						if (petManager == NULL)
							return GENERALERROR;

						petManager->enqueueOwnerOnlyPetCommand(creature, aiAgent,String("petFeed").toLowerCase().hashCode(), String::valueOf( object->getObjectID() ) );

					}

				}
				else if (sceno->isPet() && sceno->isDroidObject() && object->getGameObjectType() == SceneObjectType::STIMPACK) {
					Reference<DroidObject*> droid = sceno.castTo<DroidObject*>();
					if (droid != NULL) {
						Locker cross(sceno,creature);
						StimPack* medicine = cast<StimPack*>(object.get());
						if(medicine != NULL) {
							DroidStimpackModuleDataComponent* module = cast<DroidStimpackModuleDataComponent*>(droid->getModule("stimpack_module"));
							CreatureObject* player = cast<CreatureObject*>(creature);
							if(module != NULL)
								module->handleInsertStimpack(player,medicine);
							else
								creature->sendSystemMessage("@pet/droid_modules:not_stimpack_droid");
						} else {
							return GENERALERROR;
						}
					}
				}
				else if(sceno->isPet() && sceno->isDroidObject() && object->isTrapObject()) {
					Reference<DroidObject*> droid = sceno.castTo<DroidObject*>();
					if (droid != NULL) {
						Locker cross(sceno,creature);
						TangibleObject* trap = cast<TangibleObject*>(object.get());
						if(trap != NULL) {
							DroidTrapModuleDataComponent* module = cast<DroidTrapModuleDataComponent*>(droid->getModule("trap_module"));
							CreatureObject* player = cast<CreatureObject*>(creature);
							if(module != NULL)
								module->handleInsertTrap(player,trap);
						} else {
							return GENERALERROR;
						}
					}
				}
				else if (sceno->isCreatureObject()) {
					String err;
					if (sceno->canAddObject(object, -1, err) == 0) {
						sceno->transferObject(object, -1, true);
					}
				}
			}
		}


		return SUCCESS;
	}

};

#endif //GIVEITEMCOMMAND_H_
