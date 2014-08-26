/*
 * PetDeedImplementation.cpp
 *
 *  Created on: Aug 17, 2013
 *      Author: washu
 */

#include "server/zone/objects/tangible/deed/pet/PetDeed.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/IngredientSlot.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/ComponentSlot.h"
#include "server/zone/templates/tangible/PetDeedTemplate.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/Creature.h"
#include "server/zone/templates/tangible/SharedCreatureObjectTemplate.h"
#include "server/zone/objects/tangible/component/genetic/GeneticComponent.h"


void PetDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);
	PetDeedTemplate* deedData = dynamic_cast<PetDeedTemplate*>(templateData);

	if (deedData == NULL)
		return;

	controlDeviceObjectTemplate = deedData->getControlDeviceObjectTemplate();

}

void PetDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);
	alm->insertAttribute("challenge_level", level);
	alm->insertAttribute("creature_health", health);
	alm->insertAttribute("creature_action", action);
	alm->insertAttribute("creature_mind", mind);
	if (armor == 0)
		alm->insertAttribute("armor_rating", "None");
	else if (armor == 1)
		alm->insertAttribute("armor_rating", "Light");
	else if (armor == 2)
		alm->insertAttribute("armor_rating", "Medium");
	else if (armor == 3)
		alm->insertAttribute("armor_rating", "Heavy");

	if (kinResist < 0)
		alm->insertAttribute("dna_comp_armor_kinetic", "Vulnerable");
	else
		alm->insertAttribute("dna_comp_armor_kinetic", kinResist);

	if (energyResist < 0)
		alm->insertAttribute("dna_comp_armor_energy", "Vulnerable");
	else
		alm->insertAttribute("dna_comp_armor_energy", energyResist);

	if (blastResist < 0)
		alm->insertAttribute("dna_comp_armor_blast", "Vulnerable");
	else
		alm->insertAttribute("dna_comp_armor_blast", blastResist);

	if (heatResist < 0)
		alm->insertAttribute("dna_comp_armor_heat", "Vulnerable");
	else
		alm->insertAttribute("dna_comp_armor_heat", heatResist);

	if (coldResist < 0)
		alm->insertAttribute("dna_comp_armor_cold", "Vulnerable");
	else
		alm->insertAttribute("dna_comp_armor_cold", coldResist);

	if (elecResist < 0)
		alm->insertAttribute("dna_comp_armor_electric", "Vulnerable");
	else
		alm->insertAttribute("dna_comp_armor_electric", elecResist);

	if (acidResist < 0)
		alm->insertAttribute("dna_comp_armor_acid", "Vulnerable");
	else
		alm->insertAttribute("dna_comp_armor_acid", acidResist);

	if (stunResist < 0)
		alm->insertAttribute("dna_comp_armor_stun", "Vulnerable");
	else
		alm->insertAttribute("dna_comp_armor_stun", stunResist);

	if (saberResist < 0)
		alm->insertAttribute("dna_comp_armor_saber", "Vulnerable");
	else
		alm->insertAttribute("dna_comp_armor_saber", saberResist);

	alm->insertAttribute("creature_attack", attackSpeed);
	alm->insertAttribute("creature_tohit", chanceHit);
	alm->insertAttribute("creature_damage", String::valueOf(damageMin) + " - " + String::valueOf(damageMax));

	if (special1 != "none" && special1 != "defaultattack")
		alm->insertAttribute("spec_atk_1", special1);
	else
		alm->insertAttribute("spec_atk_1", "---");

	if (special2 != "none" && special2 != "defaultattack")
		alm->insertAttribute("spec_atk_2", special2);
	else
		alm->insertAttribute("spec_atk_2", "---");

	if(ranged)
		alm->insertAttribute("dna_comp_ranged_attack", "Yes");
	else
		alm->insertAttribute("dna_comp_ranged_attack", "No");
}

void PetDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("PetDeed");
}

void PetDeedImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ManagedReference<ManufactureSchematic*> manufact = values->getManufactureSchematic();
	for (int i = 0; i < manufact->getSlotCount(); ++i) {
		// Dna Component Slots
		Reference<IngredientSlot* > iSlot = manufact->getSlot(i);
		if (iSlot->isComponentSlot()) {
			ComponentSlot* cSlot = cast<ComponentSlot*>(iSlot.get());
			ManagedReference<TangibleObject*> tano = cSlot->getPrototype();
			ManagedReference<GeneticComponent*> component = cast<GeneticComponent*>( tano.get());
			// Now we can suck in the values
			level = component->getLevel();
			chanceHit = component->getHit();
			attackSpeed = component->getSpeed();
			damageMin = component->getMinDamage();
			damageMax = component->getMaxDamage();
			armor = component->getArmor();
			kinResist = component->getKinetic();
			energyResist = component->getEnergy();
			blastResist = component->getBlast();
			coldResist = component->getCold();
			heatResist = component->getHeat();
			elecResist = component->getElectrical();
			acidResist = component->getAcid();
			stunResist = component->getStun();
			saberResist = component->getSaber();
			health = component->getHealth();
			action = component->getAction();
			mind = component->getMind();
			special1 = component->getSpecial1();
			special2 = component->getSpecial2();
			ranged = component->getRanged();
		}
	}
	//TemplateManager* templateManager = TemplateManager::instance();
	//uint32 petCRC = generatedObjectTemplate.hashCode();
	//SharedCreatureObjectTemplate* petTemplate = dynamic_cast<SharedCreatureObjectTemplate*>(templateManager->getTemplate(petCRC));
	// We need to adjust cl based on creature template
}

void PetDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if(isASubChildOf(player))
		menuResponse->addRadialMenuItem(20, 3, "@pet/pet_menu:menu_tame");
}

int PetDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (selectedID == 20) {

		if (generated || !isASubChildOf(player))
			return 1;

		if (player->isInCombat() || player->getParentRecursively(SceneObjectType::BUILDING) != NULL) {
			player->sendSystemMessage("@pet/pet_menu:cant_call"); //You can only unpack vehicles while Outside and not in Combat.
			return 1;
		}

		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

		if (datapad == NULL) {
			player->sendSystemMessage("Datapad doesn't exist when trying to call pet");
			return 1;
		}
		if (datapad->getContainerObjectsSize() >= datapad->getContainerVolumeLimit()) {
			player->sendSystemMessage("@faction_recruiter:datapad_full"); // Your datapad is full. You must first free some space.
			return 1;
		}
		// Does the player have room
		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

		int numberStored = 0;
		int maxStoredPets = playerManager->getBaseStoredCreaturePets() + player->getSkillMod("stored_pets");

		for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

			if (object != NULL && object->isPetControlDevice()) {
				PetControlDevice* device = cast<PetControlDevice*>( object.get());

				if (device->getPetType() == PetManager::CREATUREPET) {
					if (++numberStored >= maxStoredPets) {
						player->sendSystemMessage("@pet/pet_menu:sys_too_many_stored"); // There are too many pets stored in this container. Release some of them to make room for more.
						return 1;
					}

				}
			}
		}
		// Can the player control it
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		int currentlySpawned = 0;
		int spawnedLevel = 0;
		int cLevel = level;
		int maxPets = player->getSkillMod("keep_creature");
		int maxLevelofPets = player->getSkillMod("tame_level");

		for (int i = 0; i < ghost->getActivePetsSize(); ++i) {
			ManagedReference<AiAgent*> object = ghost->getActivePet(i);

			if (object != NULL && object->isCreature()) {
				if (++currentlySpawned >= maxPets) {
					player->sendSystemMessage("@pet/pet_menu:too_many"); // You can't control any more pets. Store one first
					return 1;
				}

				spawnedLevel += object->getLevel();

				if ((spawnedLevel + cLevel) >= maxLevelofPets) {
					player->sendSystemMessage("Taming this pet would exceed your control level ability.");
					return 1;
				}
			}
		}
		// Does he have enough skill to tame it
		if (level > 10) {
			if (!player->hasSkill("outdoors_creaturehandler_novice") || (level > maxLevelofPets)) {
				player->sendSystemMessage("@pet/pet_menu:sys_lack_skill"); // You lack the skill to be able to tame that creature.
				return 1;
			}
		}
		/*
		Reference<Creature*> petTemplate = (server->getZoneServer()->createObject(generatedObjectTemplate.hashCode(), 1)).castTo<Creature*>();
		if (petTemplate == NULL) {
			error("Failed to load template crc");
			return 1;
		}
		// determine if pet is viscious non-ch cant tame a viscious pet
		bool isViscious = petTemplate->getPvpStatusBitmask() & CreatureFlag::AGGRESSIVE;
		if ((isViscious && player->getSkillMod("tame_aggro") < 1)) {
			player->sendSystemMessage("@pet/pet_menu:sys_lack_skill"); // You lack the skill to be able to tame that creature.
			return 1;
		}
		*/
		// All checks complete, lets setup the control device and do it.
		player->sendSystemMessage("Taming checks passed soon my son");
		return 0;
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}

