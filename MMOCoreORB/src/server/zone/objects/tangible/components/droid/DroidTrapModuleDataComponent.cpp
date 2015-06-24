/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidTrapModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/events/DroidTrapTask.h"
#include "server/zone/templates/tangible/TrapTemplate.h"

const String DroidTrapModuleDataComponent::EMPTY_TRAP_MESSAGE = "@pet/droid_modules:no_trap_loaded";
DroidTrapModuleDataComponent::DroidTrapModuleDataComponent() {
	setLoggingName("DroidTrapModule");
	trapBonus = 0;
	modules = 1;
}
DroidTrapModuleDataComponent::~DroidTrapModuleDataComponent() {

}
String DroidTrapModuleDataComponent::getModuleName() {
	return String("trap_module");
}
void DroidTrapModuleDataComponent::initializeTransientMembers() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	if(droidComponent->hasKey( "trap_bonus")) {
		trapBonus = droidComponent->getAttributeValue( "trap_bonus");
	}
	if(droidComponent->hasKey( "module_count")) {
		modules = droidComponent->getAttributeValue( "module_count");
	}
}
void DroidTrapModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	trapBonus = values->getCurrentValue("trap_bonus");
}
void DroidTrapModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// convert module rating to actual rating
	alm->insertAttribute( "trap_bonus", trapBonus);
	ManagedReference<DroidObject*> d = getDroidObject();
	TangibleObject* o;
	if (d != NULL) {
		if (trap == NULL)
			alm->insertAttribute("droid_trap_type",EMPTY_TRAP_MESSAGE);
		else
			alm->insertAttribute("droid_trap_type",trap->getObjectName()->getFullPath());
	}
	StringBuffer sb;
	int loaded = 0;
	if (trap != NULL) {
		loaded = trap->getUseCount();
	}
	sb << loaded;
	sb << "/";
	sb << (modules * 10);
	alm->insertAttribute("max_trap_load",sb.toString());
}
String DroidTrapModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
void DroidTrapModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidTrapModuleDataComponent* otherModule = cast<DroidTrapModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	trapBonus = trapBonus + otherModule->trapBonus;
	modules += 1;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL){
		droidComponent->changeAttributeValue("trap_bonus",(float)trapBonus);
		droidComponent->changeAttributeValue("module_count",(float)modules);
	}
}
void DroidTrapModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidTrapModuleDataComponent* otherModule = cast<DroidTrapModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	trapBonus = otherModule->trapBonus;
	modules = 1;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL){
		droidComponent->addProperty("trap_bonus",(float)trapBonus,0,"exp_effectiveness");
		droidComponent->addProperty("module_count",(float)modules,0,"hidden",true);
	}
}
void DroidTrapModuleDataComponent::onCall() {
	// ensure the trap loaded can be used by the current owner
}

bool DroidTrapModuleDataComponent::compatibleTrap(CreatureObject* player, uint32 type) {
	// get trap meta data and see if the player can use it.
	SharedObjectTemplate* templateData =TemplateManager::instance()->getTemplate(type);
	if (templateData == NULL) {
		return false;
	}

	TrapTemplate* trapData = cast<TrapTemplate*> (templateData);
	if (trapData == NULL) {
		return false;
	}

	// No skill Check
	int trappingSkill = player->getSkillMod("trapping");
	if(trappingSkill < 1) {
		return false;
	}

	/// Skill too low check
	if(trappingSkill < trapData->getSkillRequired()) {
		return false;
	}

	return true;
}
void DroidTrapModuleDataComponent::onStore() {
}
/**
 * Add Droid sub-radial options, need to be a top level radial not submenu
 */
void DroidTrapModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player != NULL && player->hasSkill("outdoors_scout_novice")) {
		menuResponse->addRadialMenuItem(TRAP_MODULE_CONTROLS, 3, "@pet/droid_modules:throw_trap_options" );
		menuResponse->addRadialMenuItemToRadialID(TRAP_MODULE_CONTROLS, TRAP_MODULE_TRAIN, 3, "@pet/droid_modules:train_throw_one" );
		menuResponse->addRadialMenuItemToRadialID(TRAP_MODULE_CONTROLS, TRAP_MODULE_CLEAR, 3, "@pet/droid_modules:clear_trap" );
	}
}

int DroidTrapModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	ManagedReference<DroidObject*> droid = getDroidObject();
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if( droid == NULL || droidComponent == NULL){
		return 0;
	}
	if( droid->isDead() || droid->isIncapacitated() || player->isDead()) {
		return 0;
	}
	if( !droid->hasPower() ){
		droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
		return 0;
	}

	if( selectedID == TRAP_MODULE_TRAIN ){
		if( controller == NULL )
			return 0;

		controller->setTrainingCommand( PetManager::THROWTRAP );
		return 0;
	}

	if( selectedID == TRAP_MODULE_CLEAR ){
		if (trap != NULL) {
			trap->destroyObjectFromWorld(true);
			trap->destroyObjectFromDatabase(true);
			trap = NULL;
		}
		player->sendSystemMessage("@pet/droid_modules:trap_matrix_cleared");
	}
	return 0;
}
void DroidTrapModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker){

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		return;
	}

	ManagedReference<PetControlDevice*> pcd = droid->getControlDevice().get().castTo<PetControlDevice*>();
	if( pcd == NULL ) {
		return;
	}

	PetManager* petManager = droid->getZoneServer()->getPetManager();
	if( petManager == NULL ) {
		return;
	}

	// Owner-only command
	if( droid->getLinkedCreature().get() != speaker ) {
		return;
	}
	if( petManager->isTrainedCommand( pcd, PetManager::THROWTRAP, cmd ) ){
		if (trap == NULL) {
			speaker->sendSystemMessage("@pet/droid_modules:no_trap_loaded");
			return;
		}
		petManager->enqueuePetCommand(speaker, droid, STRING_HASHCODE("petthrow"), "");
	}
}


void DroidTrapModuleDataComponent::handleInsertTrap(CreatureObject* player, TangibleObject* input) {
	// we need to send the invlid stimpack message just wher eis a good question
	if (!player->hasSkill("outdoors_scout_novice") || !compatibleTrap(player,input->getServerObjectCRC()) ) {
		player->sendSystemMessage("@pet/droid_modules:insufficient_skill");
		return;
	}

	ManagedReference<DroidObject*> droid = getDroidObject();
	Locker dlock(droid);
	Locker crossLock(player,droid);
	if (droid == NULL) {
		return;
	}
	if (input == NULL) {
		return;
	}
	if(droid->getLinkedCreature().get() != player) {
		return;
	}
	int loaded = 0;
	if (trap != NULL) {
		loaded = trap->getUseCount();
	}

	int allowed = (modules * 10) - loaded;
	Locker locker(input);
	// adding to existing trap
	if (trap == NULL) {
		// add the trap into the unit
		ObjectManager* objectManager = ObjectManager::instance();
		if (allowed > input->getUseCount()) {
			// just clone it and set old one to 0 uses to destroy it so it transfer correctly as we dont store this directly in the droid
			ManagedReference<TangibleObject*> protoclone = cast<TangibleObject*>( objectManager->cloneObject(input));
			if (protoclone != NULL) {
				Locker cloneLocker(protoclone);

				if (protoclone->hasAntiDecayKit()) {
					protoclone->removeAntiDecayKit();
				}

				protoclone->setParent(NULL);
				protoclone->setUseCount(input->getUseCount());
				trap = protoclone;
				input->setUseCount(0);
				StringIdChatParameter msg;
				msg.setStringId("@pet/droid_modules:trap_module_initialize");
				msg.setTU(trap->getObjectName()->getFullPath());
				msg.setDI(trap->getUseCount());
				player->sendSystemMessage(msg);
			}
		} else {
			// should technically never happen as you cant experiment traps use count but someone might config base useCount > 10
			ManagedReference<TangibleObject*> protoclone = cast<TangibleObject*>( objectManager->cloneObject(input));
			if (protoclone != NULL) {
				Locker cloneLocker(protoclone);

				if (protoclone->hasAntiDecayKit()) {
					protoclone->removeAntiDecayKit();
				}

				protoclone->setParent(NULL);
				protoclone->setUseCount(allowed);
				input->setUseCount(input->getUseCount() - allowed);
				trap = protoclone;
				StringIdChatParameter msg;
				msg.setStringId("@pet/droid_modules:trap_module_initialize");
				msg.setTU(trap->getObjectName()->getFullPath());
				msg.setDI(trap->getUseCount());
				player->sendSystemMessage(msg);
				player->sendSystemMessage("@pet/droid_modules:trap_max_reached");
			}
		}
	}
	else {
		// trap already loaded
		if (trap->getServerObjectCRC() == input->getServerObjectCRC()) {
			// same trap
			if (allowed <= 0) {
				player->sendSystemMessage("@pet/droid_modules:trap_matrix_full");
			} else {
				Locker tlocker(trap);

				if (allowed > input->getUseCount()) {
					trap->setUseCount(trap->getUseCount() + input->getUseCount());
					input->setUseCount(0);
				} else {
					trap->setUseCount(trap->getUseCount() + allowed);
					input->setUseCount(input->getUseCount() - allowed);
					player->sendSystemMessage("@pet/droid_modules:trap_max_reached");
				}
			}
		} else {
			// differnet trap
			player->sendSystemMessage("@pet/droid_modules:already_loaded");
		}
	}
}

/** Serializaiton methods */

bool DroidTrapModuleDataComponent::toBinaryStream(ObjectOutputStream* stream) {

	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);

	return true;
}

int DroidTrapModuleDataComponent::writeObjectMembers(ObjectOutputStream* stream) {

	String _name;
	int _offset;
	uint32 _totalSize;


	_name = "trapBonus";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< int >::toBinaryStream(&trapBonus, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "modules";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< int >::toBinaryStream(&modules, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);


	_name = "trap";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< ManagedReference<TangibleObject* > >::toBinaryStream(&trap, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	return 3;
}
void DroidTrapModuleDataComponent::decrementTrap() {
	if(trap != NULL) {
		Locker locker(trap);

		trap->decreaseUseCount();

		if(trap->getUseCount() == 0) {
			trap = NULL;
		}
	}
}
bool DroidTrapModuleDataComponent::readObjectMember(ObjectInputStream* stream, const String& name) {

	if (name == "trapBonus") {
		TypeInfo< int >::parseFromBinaryStream(&trapBonus, stream);
		return true;
	}
	if (name == "modules") {
		TypeInfo< int >::parseFromBinaryStream(&modules, stream);
		return true;
	}
	if (name == "trap") {
		TypeInfo< ManagedReference<TangibleObject* > >::parseFromBinaryStream(&trap, stream);
	}
	return false;
}

bool DroidTrapModuleDataComponent::parseFromBinaryStream(ObjectInputStream* stream) {

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
