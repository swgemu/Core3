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

#include "DroidMaintenanceModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/RemoveDroidStructureSuiCallback.h"

DroidMaintenanceModuleDataComponent::DroidMaintenanceModuleDataComponent() {
	setLoggingName("DroidMaintenanceModule");
	moduleRating = 0;
}

DroidMaintenanceModuleDataComponent::~DroidMaintenanceModuleDataComponent() {
	// No op
}

String DroidMaintenanceModuleDataComponent::getModuleName() {
	return String("maintenance_module");
}

void DroidMaintenanceModuleDataComponent::initializeTransientMembers() {

	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	if( droidComponent->hasKey( "struct_module") ){
		moduleRating = droidComponent->getAttributeValue( "struct_module");
	}
}

void DroidMaintenanceModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	moduleRating = values->getCurrentValue("struct_module");
}

void DroidMaintenanceModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute( "struct_module", moduleRating ); // Structure Maintenance Rating
}

void DroidMaintenanceModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	menuResponse->addRadialMenuItem(MAINT_MODULE_ROOT, 3, "@pet/droid_modules:struct_maint_root" ); // Structure Maintenance
	menuResponse->addRadialMenuItemToRadialID( MAINT_MODULE_ROOT, MAINT_MODULE_PERFORM, 3, "@pet/droid_modules:struct_maint_perform" ); // Perform Maintenance Run
	menuResponse->addRadialMenuItemToRadialID( MAINT_MODULE_ROOT, MAINT_MODULE_EDIT, 3, "@pet/droid_modules:struct_maint_edit" ); // Edit Maintenance List

}

int DroidMaintenanceModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null");
		return 0;
	}

	Locker dlock( droid, player );

	// Perform Maintenance Run
	if( selectedID == MAINT_MODULE_PERFORM ){

		// Init Maintenance Run Session

	}
	// Edit Maintenance List
	else if( selectedID == MAINT_MODULE_EDIT ){

		if( assignedStructures.isEmpty() ){
			player->sendSystemMessage( "@pet/droid_modules:droid_maint_empty_list" ); // The maintenance list for this droid is empty. Go to one of your structures and assign this droid to maintain it.
			return 0;
		}

		// Build List of Assigned Structures
		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::DROID_EDIT_ASSIGNED_STRUCTURES, SuiListBox::HANDLETWOBUTTON);
		box->setCallback(new RemoveDroidStructureSuiCallback(player->getZoneServer(), this));
		box->setPromptTitle("@pet/droid_modules:droid_maint_edit_title"); // Edit Maintenance List
		box->setPromptText("@pet/droid_modules:droid_maint_edit_prompt"); // Please select a structure to remove from this droid's maintenance list.

		box->setOkButton(true, "@delete");
		box->setCancelButton(true, "@cancel");

		for (int i = 0; i < assignedStructures.size(); i++) {

			uint64 objectId = assignedStructures.elementAt(i);
			ManagedReference<SceneObject*> obj = player->getZoneServer()->getObject(objectId);
			if( obj != NULL && obj->isStructureObject() ){
				StructureObject* structureObject = cast<StructureObject*>(obj.get());
				if( structureObject != NULL ){
					box->addMenuItem( structureObject->getCustomObjectName().toString(), objectId );
				}
			}
		}

		box->setUsingObject(droid);
		player->getPlayerObject()->addSuiBox(box);
		player->sendMessage(box->generateMessage());

	}

	return 0;
}

int DroidMaintenanceModuleDataComponent::getBatteryDrain() {
	return 0;  // No constant drain, but each maintenance run will use power
}

void DroidMaintenanceModuleDataComponent::copy(BaseDroidModuleComponent* other){

	DroidMaintenanceModuleDataComponent* otherModule = cast<DroidMaintenanceModuleDataComponent*>(other);
	if( otherModule == NULL )
		return;

	moduleRating = otherModule->moduleRating;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL)
		return;

	droidComponent->addProperty("struct_module", moduleRating, 0, "exp_effectiveness");

}

void DroidMaintenanceModuleDataComponent::addToStack(BaseDroidModuleComponent* other){

	DroidMaintenanceModuleDataComponent* otherModule = cast<DroidMaintenanceModuleDataComponent*>(other);
	if( otherModule == NULL )
		return;

	// Maintenance modules do not stack.  Just keep the highest rated module
	if( otherModule->moduleRating > moduleRating )
		moduleRating = otherModule->moduleRating;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL)
		return;

	// Attribute should have already been created in copy method
	if( !droidComponent->changeAttributeValue( "struct_module", moduleRating) ){
		info( "addToStack updateAttributeValue failed");
		return;
	}

}

String DroidMaintenanceModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}

void DroidMaintenanceModuleDataComponent::assignStructure( uint64 objectID ){

	if( !assignedStructures.contains( objectID ) )
		assignedStructures.add( objectID );

}

void DroidMaintenanceModuleDataComponent::unassignStructure( uint64 objectID ){

	if( assignedStructures.contains( objectID ) )
		assignedStructures.removeElement( objectID );

}

void DroidMaintenanceModuleDataComponent::onCall(){
	validateStructures();
}

void DroidMaintenanceModuleDataComponent::validateStructures(){

	Vector<uint64> structures;
	structures.clone( assignedStructures );

	for (int i = 0; i < structures.size(); i++) {

		uint64 objectID = structures.elementAt(i);
		if( ~isValidStructure( objectID ) ){
			assignedStructures.removeElement( objectID );
		}

	}

}

bool DroidMaintenanceModuleDataComponent::isValidStructure(uint64 objectID){

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL )
		return false;

	ManagedReference<SceneObject*> obj = droid->getZoneServer()->getObject(objectID);
	if( obj == NULL )
		return false;

	if( !obj->isStructureObject() )
		return false;

	StructureObject* structureObject = cast<StructureObject*>(obj.get());
	if( structureObject == NULL )
		return false;

	ManagedWeakReference< CreatureObject*> linkedCreature = droid->getLinkedCreature();
	if( linkedCreature == NULL )
		return false;

	if( !structureObject->isOnAdminList( linkedCreature.get() ) )
		return false;

	if( structureObject->getZone() == NULL )
		return false;

	// All checks passed
	return true;

}

bool DroidMaintenanceModuleDataComponent::toBinaryStream(ObjectOutputStream* stream) {

	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);

	return true;
}

int DroidMaintenanceModuleDataComponent::writeObjectMembers(ObjectOutputStream* stream) {

	String _name;
	int _offset;
	uint32 _totalSize;

	_name = "assignedStructures";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< Vector<uint64> >::toBinaryStream(&assignedStructures, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	return 1;
}

bool DroidMaintenanceModuleDataComponent::readObjectMember(ObjectInputStream* stream, const String& name) {

	if (name == "assignedStructures") {
		TypeInfo< Vector<uint64> >::parseFromBinaryStream(&assignedStructures, stream);
		return true;
	}

	return false;
}

bool DroidMaintenanceModuleDataComponent::parseFromBinaryStream(ObjectInputStream* stream) {

	uint16 _varCount = stream->readShort();

	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);
		uint32 _varSize = stream->readInt();
		int _currentOffset = stream->getOffset();
		if(readObjectMember(stream, _name)) {
		}
		stream->setOffset(_currentOffset + _varSize);
	}
	return true;
}
