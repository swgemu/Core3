/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GIVEITEMCOMMAND_H_
#define GIVEITEMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"

#include "server/zone/objects/tangible/attachment/Attachment.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/objects/tangible/components/droid/DroidStimpackModuleDataComponent.h"
#include "server/zone/objects/tangible/components/droid/DroidTrapModuleDataComponent.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

class GiveItemCommand : public QueueCommand {
public:

	GiveItemCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
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

			ManagedReference<SceneObject*> objectsParent = object->getParent().get();

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
							chatMan->broadcastChatMessage(vendor, message, object->getObjectID(), 0, vendor->getMoodID());
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

						petManager->enqueueOwnerOnlyPetCommand(creature, aiAgent, STRING_HASHCODE("petfeed"), String::valueOf( object->getObjectID() ) );

					}

				}
				else if (sceno->isPet() && sceno->isDroidObject() && object->getGameObjectType() == SceneObjectType::STIMPACK) {
					Reference<DroidObject*> droid = sceno.castTo<DroidObject*>();
					if (droid != NULL) {
						Locker cross(sceno,creature);
						StimPack* medicine = cast<StimPack*>(object.get());
						if(medicine != NULL) {
							auto module = droid->getModule("stimpack_module").castTo<DroidStimpackModuleDataComponent*>();
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
							auto module = droid->getModule("trap_module").castTo<DroidTrapModuleDataComponent*>();
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
					Locker objLocker(object);
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
