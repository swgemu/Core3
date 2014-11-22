/*
 * Copyright (C) 2014 <SWGEmu>
 * This File is part of Core3.
 * This program is free software; you can redistribute
 * it and/or modify it under the terms of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program; if not, write to
 * the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Linking Engine3 statically or dynamically with other modules
 * is making a combined work based on Engine3.
 * Thus, the terms and conditions of the GNU Lesser General Public License
 * cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of Engine3
 * give you permission to combine Engine3 program with free software
 * programs or libraries that are released under the GNU LGPL and with
 * code included in the standard release of Core3 under the GNU LGPL
 * license (or modified versions of such code, with unchanged license).
 * You may copy and distribute such a system following the terms of the
 * GNU LGPL for Engine3 and the licenses of the other code concerned,
 * provided that you include the source code of that other code when
 * and as the GNU LGPL requires distribution of source code.
 *
 * Note that people who make modified versions of Engine3 are not obligated
 * to grant this special exception for their modified versions;
 * it is their choice whether to do so. The GNU Lesser General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 */

#include "DroidRepairModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/creature/PetManager.h"

DroidRepairModuleDataComponent::DroidRepairModuleDataComponent() {
	setLoggingName("DroidRepairModule");
}
DroidRepairModuleDataComponent::~DroidRepairModuleDataComponent() {

}
String DroidRepairModuleDataComponent::getModuleName() {
	return String("repair_module");
}
void DroidRepairModuleDataComponent::initializeTransientMembers() {
	// no op
}

void DroidRepairModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute( "repair_module", "Installed" );
}

void DroidRepairModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// Add to Droid Options subradial from PetMenuComponent
	menuResponse->addRadialMenuItemToRadialID(132, REPAIR_MODULE_ACTIVATE, 3, "Repair" );

	// Add to Program subradial from PetMenuComponent
	menuResponse->addRadialMenuItemToRadialID(141, REPAIR_MODULE_TRAIN, 3, "@pet/pet_menu:menu_repair_other" ); // "Repair Other Droid"
}

int DroidRepairModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	// Handle repair request
	if( selectedID == REPAIR_MODULE_ACTIVATE ){

		PetManager* petManager = player->getZoneServer()->getPetManager();
		if( petManager == NULL )
			return 0;

		petManager->enqueuePetCommand(player, getDroidObject(), String("petRepair").toLowerCase().hashCode(), "");

	}
	// Handle command training
	else if( selectedID == REPAIR_MODULE_TRAIN ){

		if( controller == NULL )
			return 0;

		controller->setTrainingCommand( PetManager::REPAIR );

	}

	return 0;
}

void DroidRepairModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker){

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL )
		return;

	ManagedReference<PetControlDevice*> pcd = droid->getControlDevice().get().castTo<PetControlDevice*>();
	if( pcd == NULL )
		return;

	PetManager* petManager = droid->getZoneServer()->getPetManager();
	if( petManager == NULL )
		return;

	// Owner-only command
	if( droid->getLinkedCreature() != speaker )
		return;

	if( petManager->isTrainedCommand( pcd, PetManager::REPAIR, cmd ) ){
		petManager->enqueuePetCommand(speaker, droid, String("petRepair").toLowerCase().hashCode(), "");
	}
}

int DroidRepairModuleDataComponent::getBatteryDrain() {
	return 0;  // No constant drain, but each activation will use power
}

String DroidRepairModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
