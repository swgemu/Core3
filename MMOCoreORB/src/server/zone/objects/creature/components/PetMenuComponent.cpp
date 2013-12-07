
#include "PetMenuComponent.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

void PetMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	if (!sceneObject->isPet())
		return;

	AiAgent* pet = cast<AiAgent*>(sceneObject);

	if (!player->getPlayerObject()->isPrivileged() && pet->getLinkedCreature() != player)
		return;

	menuResponse->addRadialMenuItem(59, 3, "@pet/pet_menu:menu_store"); // Store

	ManagedReference<PetControlDevice*> controlDevice = pet->getControlDevice().get().castTo<PetControlDevice*>();
	if( controlDevice == NULL )
		return;

	// DROIDS
	if( controlDevice->getPetType() == PetControlDevice::DROIDPET ){

		menuResponse->addRadialMenuItem(132, 3, "@pet/pet_menu:droid_options"); // SERVER_ITEM_OPTIONS
		menuResponse->addRadialMenuItemToRadialID(132, 234, 3, "@pet/pet_menu:menu_recharge" ); // PET_FEED

		menuResponse->addRadialMenuItem(141, 3, "@pet/pet_menu:menu_command_droid"); // PET_COMMAND
		menuResponse->addRadialMenuItemToRadialID(141, 142, 3, "@pet/pet_menu:menu_follow" ); // PET_FOLLOW
		menuResponse->addRadialMenuItemToRadialID(141, 143, 3, "@pet/pet_menu:menu_stay" ); // PET_STAY
		menuResponse->addRadialMenuItemToRadialID(141, 144, 3, "@pet/pet_menu:menu_guard" ); // PET_GUARD
		menuResponse->addRadialMenuItemToRadialID(141, 145, 3, "@pet/pet_menu:menu_friend" ); // PET_FRIEND
		menuResponse->addRadialMenuItemToRadialID(141, 146, 3, "@pet/pet_menu:menu_attack" ); // PET_ATTACK
		menuResponse->addRadialMenuItemToRadialID(141, 147, 3, "@pet/pet_menu:menu_patrol" ); // PET_PATROL
		menuResponse->addRadialMenuItemToRadialID(141, 148, 3, "@pet/pet_menu:menu_get_patrol_point" ); // PET_GET_PATROL_POINT
		menuResponse->addRadialMenuItemToRadialID(141, 149, 3, "@pet/pet_menu:menu_clear_patrol_points" ); // PET_CLEAR_PATROL_POINTS
		menuResponse->addRadialMenuItemToRadialID(141, 150, 3, "@pet/pet_menu:menu_assume_formation_1" ); // PET_ASSUME_FORMATION_1
		menuResponse->addRadialMenuItemToRadialID(141, 151, 3, "@pet/pet_menu:menu_assume_formation_2" ); // PET_ASSUME_FORMATION_2
		menuResponse->addRadialMenuItemToRadialID(141, 158, 3, "@pet/pet_menu:menu_group" ); // PET_GROUP
		menuResponse->addRadialMenuItemToRadialID(141, 163, 3, "@pet/pet_menu:menu_ranged_attack" );
		menuResponse->addRadialMenuItemToRadialID(141, 164, 3, "@pet/pet_menu:menu_store" );
		menuResponse->addRadialMenuItemToRadialID(141, 165, 3, "@pet/pet_menu:menu_follow_other" );

		ManagedReference<DroidObject*> droidObject = dynamic_cast<DroidObject*>(controlDevice->getControlledObject());
		if( droidObject != NULL && droidObject->isPowerDroid() ){
			menuResponse->addRadialMenuItemToRadialID(141, 235, 3, "@pet/pet_menu:menu_recharge_other" );
		}

	}
	// FACTION
	else if( controlDevice->getPetType() == PetControlDevice::FACTIONPET ){

		menuResponse->addRadialMenuItem(141, 3, "@pet/pet_menu:menu_command"); // PET_COMMAND
		menuResponse->addRadialMenuItemToRadialID(141, 142, 3, "@pet/pet_menu:menu_follow" ); // PET_FOLLOW
		menuResponse->addRadialMenuItemToRadialID(141, 143, 3, "@pet/pet_menu:menu_stay" ); // PET_STAY
		menuResponse->addRadialMenuItemToRadialID(141, 144, 3, "@pet/pet_menu:menu_guard" ); // PET_GUARD
		menuResponse->addRadialMenuItemToRadialID(141, 145, 3, "@pet/pet_menu:menu_friend" ); // PET_FRIEND
		menuResponse->addRadialMenuItemToRadialID(141, 146, 3, "@pet/pet_menu:menu_attack" ); // PET_ATTACK
		menuResponse->addRadialMenuItemToRadialID(141, 147, 3, "@pet/pet_menu:menu_patrol" ); // PET_PATROL
		menuResponse->addRadialMenuItemToRadialID(141, 148, 3, "@pet/pet_menu:menu_get_patrol_point" ); // PET_GET_PATROL_POINT
		menuResponse->addRadialMenuItemToRadialID(141, 149, 3, "@pet/pet_menu:menu_clear_patrol_points" ); // PET_CLEAR_PATROL_POINTS
		menuResponse->addRadialMenuItemToRadialID(141, 150, 3, "@pet/pet_menu:menu_assume_formation_1" ); // PET_ASSUME_FORMATION_1
		menuResponse->addRadialMenuItemToRadialID(141, 151, 3, "@pet/pet_menu:menu_assume_formation_2" ); // PET_ASSUME_FORMATION_2
		menuResponse->addRadialMenuItemToRadialID(141, 158, 3, "@pet/pet_menu:menu_group" ); // PET_GROUP
		menuResponse->addRadialMenuItemToRadialID(141, 163, 3, "@pet/pet_menu:menu_ranged_attack" );
		menuResponse->addRadialMenuItemToRadialID(141, 164, 3, "@pet/pet_menu:menu_store" );
		menuResponse->addRadialMenuItemToRadialID(141, 165, 3, "@pet/pet_menu:menu_follow_other" );

	}
	// CREATURES
	else if( controlDevice->getPetType() == PetControlDevice::CREATUREPET ){

		menuResponse->addRadialMenuItem(141, 3, "@pet/pet_menu:menu_command"); // PET_COMMAND

		if( player->hasSkill( "outdoors_creaturehandler_novice" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 142, 3, "@pet/pet_menu:menu_follow" ); // PET_FOLLOW
			menuResponse->addRadialMenuItemToRadialID(141, 146, 3, "@pet/pet_menu:menu_attack" ); // PET_ATTACK
			menuResponse->addRadialMenuItemToRadialID(141, 164, 3, "@pet/pet_menu:menu_store" );
		}

		if( player->hasSkill( "outdoors_creaturehandler_training_01" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 143, 3, "@pet/pet_menu:menu_stay" ); // PET_STAY
		}

		if( player->hasSkill( "outdoors_creaturehandler_training_02" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 144, 3, "@pet/pet_menu:menu_guard" ); // PET_GUARD
		}

		if( player->hasSkill( "outdoors_creaturehandler_training_03" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 147, 3, "@pet/pet_menu:menu_patrol" ); // PET_PATROL
			menuResponse->addRadialMenuItemToRadialID(141, 148, 3, "@pet/pet_menu:menu_get_patrol_point" ); // PET_GET_PATROL_POINT
			menuResponse->addRadialMenuItemToRadialID(141, 149, 3, "@pet/pet_menu:menu_clear_patrol_points" ); // PET_CLEAR_PATROL_POINTS
		}

		if( player->hasSkill( "outdoors_creaturehandler_training_04" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 150, 3, "@pet/pet_menu:menu_assume_formation_1" ); // PET_ASSUME_FORMATION_1
			menuResponse->addRadialMenuItemToRadialID(141, 151, 3, "@pet/pet_menu:menu_assume_formation_2" ); // PET_ASSUME_FORMATION_2
		}

		if( player->hasSkill( "outdoors_creaturehandler_healing_01" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 154, 3, "@pet/pet_menu:menu_trick_1" ); // PET_TRICK_1
		}

		if( player->hasSkill( "outdoors_creaturehandler_healing_03" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 155, 3, "@pet/pet_menu:menu_trick_2" ); // PET_TRICK_2
		}

		if( player->hasSkill( "outdoors_creaturehandler_support_01" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 158, 3, "@pet/pet_menu:menu_group" ); // PET_GROUP
		}

		if( player->hasSkill( "outdoors_creaturehandler_support_02" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 165, 3, "@pet/pet_menu:menu_follow_other" );
		}

		if( player->hasSkill( "outdoors_creaturehandler_support_03" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 145, 3, "@pet/pet_menu:menu_friend" ); // PET_FRIEND
		}

		if( player->hasSkill( "outdoors_creaturehandler_taming_03" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 161, 3, "@pet/pet_menu:menu_specialattack_one" ); // PET_SPECIAL_ATTACK_ONE
		}

		if( player->hasSkill( "outdoors_creaturehandler_taming_04" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 162, 3, "@pet/pet_menu:menu_specialattack_two" ); // PET_SPECIAL_ATTACK_TWO
		}

		if( player->hasSkill( "outdoors_creaturehandler_master" ) ){
			menuResponse->addRadialMenuItemToRadialID(141, 163, 3, "@pet/pet_menu:menu_ranged_attack" );
		}

	}

}

int PetMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isPet())
		return 0;

	AiAgent* pet = cast<AiAgent*>(sceneObject);

	if (!player->getPlayerObject()->isPrivileged() && pet->getLinkedCreature() != player)
		return 0;

	ManagedReference<PetControlDevice*> petControlDevice = pet->getControlDevice().get().castTo<PetControlDevice*>();

	if (petControlDevice == NULL)
		return 0;

	// Store
	if (selectedID == 59) {
		petControlDevice->storeObject(player);
		return 0;
	}

	// Recharge
	if (selectedID == 234 ){
		ManagedReference<DroidObject*> droidObject = dynamic_cast<DroidObject*>(petControlDevice->getControlledObject());
		if( droidObject != NULL ){
			return droidObject->rechargeFromBattery(player);
		}
	}

	// Trained Command: Recharge Other
	if (selectedID == 235 ){
		petControlDevice->setTrainingCommand( PetControlDevice::RECHARGEOTHER );
	}

	// Train Command: Follow
	if (selectedID == 142 ){ // PET_FOLLOW
		petControlDevice->setTrainingCommand( PetControlDevice::FOLLOW );
	}

	// Train Command: Stay
	if (selectedID == 143 ){ // PET_STAY
		petControlDevice->setTrainingCommand( PetControlDevice::STAY );
	}

	// Train Command: Guard
	if (selectedID == 144 ){ // PET_GUARD
		petControlDevice->setTrainingCommand( PetControlDevice::GUARD );
	}

	// Train Command: Friend
	if (selectedID == 145 ){ // PET_FRIEND
		petControlDevice->setTrainingCommand( PetControlDevice::FRIEND );
	}

	// Train Command: Attack
	if (selectedID == 146 ){ // PET_ATTACK
		petControlDevice->setTrainingCommand( PetControlDevice::ATTACK );
	}

	// Train Command: Patrol
	if (selectedID == 147 ){ // PET_PATROL
		petControlDevice->setTrainingCommand( PetControlDevice::PATROL );
	}

	// Get Patrol Point
	if (selectedID == 148 ){ // PET_GET_PATROL_POINT
		// TODO Handle setting patrol point
		player->sendSystemMessage("PET_GET_PATROL_POINT pet command is not yet implemented.");
	}

	// Clear Patrol Points
	if (selectedID == 149 ){ // PET_CLEAR_PATROL_POINTS
		// TODO Handle clearing patrol points
		player->sendSystemMessage("PET_CLEAR_PATROL_POINTS pet command is not yet implemented.");
	}

	// Train Command: Wedge Formation
	if (selectedID == 150 ){ // PET_ASSUME_FORMATION_1
		petControlDevice->setTrainingCommand( PetControlDevice::FORMATION1 );
	}

	// Train Command: Column Formation
	if (selectedID == 151 ){ // PET_ASSUME_FORMATION_2
		petControlDevice->setTrainingCommand( PetControlDevice::FORMATION2 );
	}

	// Train Command: Trick 1
	if (selectedID == 154 ){ // PET_TRICK_1
		petControlDevice->setTrainingCommand( PetControlDevice::TRICK1 );
	}

	// Train Command: Trick 2
	if (selectedID == 155 ){ // PET_TRICK_2
		petControlDevice->setTrainingCommand( PetControlDevice::TRICK2 );
	}

	// Train Command: Group
	if (selectedID == 158 ){ // PET_GROUP
		petControlDevice->setTrainingCommand( PetControlDevice::GROUP );
	}

	// Train Command: Special Attack 1
	if (selectedID == 161 ){ // PET_SPECIAL_ATTACK_ONE
		petControlDevice->setTrainingCommand( PetControlDevice::SPECIAL_ATTACK1 );
	}

	// Train Command: Special Attack 2
	if (selectedID == 162 ){ // PET_SPECIAL_ATTACK_TWO
		petControlDevice->setTrainingCommand( PetControlDevice::SPECIAL_ATTACK2 );
	}

	// Train Command: Ranged Attack
	if (selectedID == 163 ){
		petControlDevice->setTrainingCommand( PetControlDevice::RANGED_ATTACK );
	}

	// Train Command: Store
	if (selectedID == 164 ){
		petControlDevice->setTrainingCommand( PetControlDevice::STORE );
	}

	// Train Command: Follow Other
	if (selectedID == 165 ){
		petControlDevice->setTrainingCommand( PetControlDevice::FOLLOWOTHER );
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
