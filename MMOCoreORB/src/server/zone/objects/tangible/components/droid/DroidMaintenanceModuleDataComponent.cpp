/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidMaintenanceModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/RemoveDroidStructureSuiCallback.h"
#include "server/zone/objects/player/sessions/DroidMaintenanceSession.h"
#include "server/zone/Zone.h"

DroidMaintenanceModuleDataComponent::DroidMaintenanceModuleDataComponent() {
	setLoggingName("DroidMaintenanceModule");
	moduleRating = 0;
	maxStructures = 3;
	assignedStructures.removeAll();
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
		//droid->getCooldownTimerMap()->updateToCurrentAndAddMili("Droid_Cooldown",1800000);
		// Interplanetary Time + 1 hour 40 minutes, 33 seconds
		// Local time: distance < 432 == 15 mins + (1s per 3 meters to next structure for that planet @ < 432m from first structure)
		// Local time: distance > 432 == 48 minutes 20 seconds
		// Start a session for the player and this module!
		ManagedReference<DroidMaintenanceSession*> session = new DroidMaintenanceSession(this, player);
		session->initialize();
		player->addActiveSession(SessionFacadeType::DROIDMAINTENANCERUN, session);
		session->sendMaintanceRunBox();
		return 0;
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
					box->addMenuItem( structureObject->getDisplayedName(), objectId );
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
void DroidMaintenanceModuleDataComponent::getStructureList(Vector<ManagedReference<StructureObject* > >* list,ZoneServer* srv, uint32 planet) {
	for (int i = 0; i < assignedStructures.size(); i++) {
		uint64 objectId = assignedStructures.elementAt(i);
		ManagedReference<SceneObject*> obj = srv->getObject(objectId);
		if( obj != NULL && obj->isStructureObject() ){
			StructureObject* structureObject = cast<StructureObject*>(obj.get());
			if( structureObject != NULL ){
				// is it on this planet?
				Zone* zone = structureObject->getZone();

				if (zone == NULL) {
					continue;
				}

				if (zone->getZoneCRC() == planet) {
					list->add(structureObject);
				} else {
					if (moduleRating >= 12) // ratign 12 min for interplanetary
						list->add(structureObject);
				}
			}
		}
	}
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

	if (moduleRating < 6) {
		maxStructures = 3;
	} else if (moduleRating < 12) {
		maxStructures = 6;
	} else if (moduleRating < 15) {
		maxStructures = 9;
	} else {
		maxStructures = 10;
	}
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

	if (moduleRating < 6) {
		maxStructures = 3;
	} else if (moduleRating < 12) {
		maxStructures = 6;
	} else if (moduleRating < 15) {
		maxStructures = 9;
	} else {
		maxStructures = 10;
	}

}

String DroidMaintenanceModuleDataComponent::toString(){
	StringBuffer str;
	str << getModuleName() << "\n";
	str << "Number of Assigned Structures: " << assignedStructures.size() << "\n";
	for (int i = 0; i < assignedStructures.size(); i++) {
		uint64 objectID = assignedStructures.elementAt(i);
		str << "\tStructure: " << objectID << "\n";
	}
	return str.toString();
}
bool DroidMaintenanceModuleDataComponent::isAssignedTo(uint64 structure) {
	return assignedStructures.contains(structure);
}
bool DroidMaintenanceModuleDataComponent::assignStructure( uint64 objectID ){

	if( !assignedStructures.contains( objectID ) && assignedStructures.size() <= maxStructures) {
		assignedStructures.add( objectID );
		return true;
	} else {
		return false;
	}

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
	assignedStructures.clone( structures );

	for (int i = 0; i < structures.size(); i++) {

		uint64 objectID = structures.elementAt(i);
		if( !isValidStructure( objectID ) ){
			assignedStructures.removeElement( objectID );
		}

	}

}
void DroidMaintenanceModuleDataComponent::payStructures(CreatureObject* player, VectorMap<unsigned long long, int> assignments) {
	// we know each struct to pay and any fees applied.
	ManagedReference<DroidObject*> droid = getDroidObject();

	for(int i=0;i< assignments.size();i++) {
		uint64 objectID = assignments.elementAt(i).getKey();
		int maintToPay = assignments.elementAt(i).getValue();
		ManagedReference<SceneObject*> obj = player->getZoneServer()->getObject(objectID);
		StructureObject* structureObject = cast<StructureObject*>(obj.get());
		if (structureObject != NULL) {
			Locker sLock(obj,player);
			structureObject->payMaintenance(maintToPay,player,true);
		}
	}
}
long DroidMaintenanceModuleDataComponent::calculateRunTime(const VectorMap<unsigned long long, int>& assignments, const String& localPlanet, DroidObject* droid) {
	long duration = 0;
	ManagedReference<SceneObject*> primeStructure;
	for(int i=0;i< assignments.size();i++) {
		uint64 objectID = assignments.elementAt(i).getKey();
		if(isValidStructure(objectID)) {
			ManagedReference<SceneObject*> obj = droid->getZoneServer()->getObject(objectID);
			if (obj->getZone()->getZoneName() != localPlanet) {
				duration += 6033000; // 1 hr 40 minutes and 33 seconds
			}else {
				// same planet
				if (primeStructure == NULL) {
					primeStructure = obj;
				}
				if (obj == primeStructure) {
					if (droid->getDistanceTo(obj) > 432) {
						duration += 2900000; // 48 minutes and 20 seconds
					} else {
						duration += 900000; // 15 minutes
					}
				} else {
					float distance = primeStructure->getDistanceTo(obj);
					if (distance > 432) {
						duration += 2900000; // 48 minutes and 20 seconds
						primeStructure = obj; // new prime structure
					} else {
						// this struct is within 432 of prime
						float timeAdded = (distance/3) * 1000; // add 1 sec for every 3 meters apart
						duration += (timeAdded + 900000);
						primeStructure = obj; // we now grab this structure as our prime going down the list.
					}
				}
			}
		}
	}
	return duration;
}
bool DroidMaintenanceModuleDataComponent::isValidStructure(uint64 objectID){

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ) {
		return false;
	}

	ManagedReference<SceneObject*> obj = droid->getZoneServer()->getObject(objectID);
	if( obj == NULL ) {
		return false;
	}

	if( !obj->isStructureObject() ) {
		return false;
	}
	// we need to check for more than structure we need to check for factories and harvestors as well.
	StructureObject* structureObject = cast<StructureObject*>(obj.get());
	if( structureObject == NULL ) {
		return false;
	}

	ManagedWeakReference< CreatureObject*> linkedCreature = droid->getLinkedCreature();
	if( linkedCreature == NULL ) {
		return false;
	}

	if( !structureObject->isOnAdminList( linkedCreature.get() ) ) {
		return false;
	}

	if( structureObject->getZone() == NULL ) {
		return false;
	}

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
	TypeInfo< Vector<unsigned long long> >::toBinaryStream(&assignedStructures, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	return 1;
}

bool DroidMaintenanceModuleDataComponent::readObjectMember(ObjectInputStream* stream, const String& name) {

	if (name == "assignedStructures") {
		TypeInfo< Vector<unsigned long long> >::parseFromBinaryStream(&assignedStructures, stream);
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
