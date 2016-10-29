/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidEffectsModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/creature/events/DroidEffectsTask.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/DroidEffectsModuleTemplate.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/SelectDroidEffectSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

DroidEffectsModuleDataComponent::DroidEffectsModuleDataComponent() {
	active = false;
	currentEffectIndex = -1;
	setLoggingName("DroidEffectsModule");

	// Initialize configured effects
	for( int i=0; i <= 9; i++ ){
		configuredEffects.add("@pet/droid_modules:empty_slot");
		configuredDelays.add(0);
	}

}
DroidEffectsModuleDataComponent::~DroidEffectsModuleDataComponent() {

}
String DroidEffectsModuleDataComponent::getModuleName() {
	return String("effects_module");
}
void DroidEffectsModuleDataComponent::initializeTransientMembers() {

	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	ManagedReference<DroidEffectsModuleTemplate*> moduleTemplate = cast<DroidEffectsModuleTemplate*>(droidComponent->getObjectTemplate());
	if (moduleTemplate == NULL){
		info("Module was null");
		return;
	}

	installedEffects.put( moduleTemplate->getEffectName(), moduleTemplate->getAnimation() );

}

void DroidEffectsModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {

	// Loop over all installed effects
	for(int i =0; i< installedEffects.size();i++){
		String effectName = installedEffects.elementAt(i).getKey();
		effectName = effectName.subString( effectName.indexOf(':')+1, effectName.length() );
		alm->insertAttribute( effectName, "Installed" );
	}

}

void DroidEffectsModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if( player == NULL )
		return;

	// Novice Musician or Novice Dancer required to utilize this module
	if (player->hasSkill("social_musician_novice") || player->hasSkill("social_dancer_novice")){

		menuResponse->addRadialMenuItem(EFFECTS_MODULE_TOGGLE, 3, "@pet/droid_modules:toggle_effects" );
		menuResponse->addRadialMenuItem(EFFECTS_MODULE_CONFIGURE, 3, "@pet/droid_modules:effects_set_up");

		// Add slots
		for(int i=0; i <= 9; i++){
			menuResponse->addRadialMenuItemToRadialID( EFFECTS_MODULE_CONFIGURE, EFFECTS_MODULE_SLOT1+i, 3, configuredEffects.get(i));
		}
	}

}

int DroidEffectsModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	// Handle toggle on/off
	if( selectedID == EFFECTS_MODULE_TOGGLE ){

		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null");
			return 0;
		}

		Locker dlock( droid, player );

		// Toggle off
		if (active){
			deactivate();
			player->sendSystemMessage("@pet/droid_modules:effects_off");  // You turn off the droid's effects
		}
		// Toggle on
		else{

			// Check droid states
			if( droid->isDead() || droid->isIncapacitated() )
				return 0;

			// Droid must have power
			if( !droid->hasPower() ){
				droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
				return 0;
			}

			// Ensure we don't accidentally have another task outstanding
			deactivate();

			// Ensure we have a valid effect
			if( !nextEffect() ){
				player->sendSystemMessage("@pet/droid_modules:no_effects_program");	// The droid's effect program must have at least one active slot in order to active it.
				return 0;
			}

			// Submit effects task
			Reference<Task*> task = new DroidEffectsTask( this );
			droid->addPendingTask("droid_effects", task, 0); // 10 sec
			player->sendSystemMessage("@pet/droid_modules:effects_started");  // You turn on the droid's effects
			active = true;
		}

	}
	// Handle slot configure
	else if( EFFECTS_MODULE_SLOT1 <= selectedID && selectedID <= EFFECTS_MODULE_SLOT10 ){

		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null");
			return 0;
		}

		Locker dlock( droid, player );

		// Toggle effects off before allowing configuration
		if (active){
			deactivate();
			player->sendSystemMessage("@pet/droid_modules:effects_off");  // You turn off the droid's effects
		}

		int slotIndex = selectedID - EFFECTS_MODULE_SLOT1;

		// Build SUI
		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::SELECT_DROID_EFFECT, SuiListBox::HANDLETWOBUTTON);
		box->setCallback(new SelectDroidEffectSuiCallback(player->getZoneServer(), this, slotIndex));
		box->setPromptText("Select the desired effect for this slot");
		box->setPromptTitle("@pet/droid_modules:effects_set_up"); // Configure Effects
		box->setOkButton(true, "@ok");
		box->setCancelButton(true, "@cancel");

		// Add empty slot to clear slot
		box->addMenuItem( "@pet/droid_modules:empty_slot" );

		// Add all installed effects
		for(int i =0; i< installedEffects.size();i++){
			box->addMenuItem( installedEffects.elementAt(i).getKey() );
		}

		box->setUsingObject(droid);
		player->getPlayerObject()->addSuiBox(box);
		player->sendMessage(box->generateMessage());

	}
	return 0;
}

bool DroidEffectsModuleDataComponent::nextEffect(){

	int startIdx = currentEffectIndex + 1;

	// Find next valid effect
	for( int i=0; i<=9; i++){

		int nextIdx = (startIdx + i)%10;
		if( !configuredEffects.get(nextIdx).contains("empty_slot") && configuredDelays.get(nextIdx) > 0 ){
			currentEffectIndex = nextIdx;
			//info( "nextEffect currentEffectIndex=" + String::valueOf(currentEffectIndex), true );
			return true;
		}
	}

	// No valid effects configured
	return false;

}

String DroidEffectsModuleDataComponent::getCurrentAnimation(){

	if( currentEffectIndex < 0 || currentEffectIndex > 9 ){
		return "";
	}

	const String& effectName = configuredEffects.get(currentEffectIndex);
	return installedEffects.get( effectName );

}

int DroidEffectsModuleDataComponent::getCurrentDelay(){

	if( currentEffectIndex < 0 || currentEffectIndex > 9 ){
		return -1;
	}

	return configuredDelays.get(currentEffectIndex);
}

void DroidEffectsModuleDataComponent::setEffect( String effectName, int delay, int slotIndex ){

	if( 0 <= slotIndex && slotIndex <= 9 ){
		configuredEffects.setElementAt( slotIndex, effectName );
		configuredDelays. setElementAt( slotIndex, delay );
	}

}

int DroidEffectsModuleDataComponent::getBatteryDrain() {

	if( active ){
		return 4;
	}

	return 0;
}

void DroidEffectsModuleDataComponent::deactivate() {

	active = false;
	currentEffectIndex = -1;

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null" );
		return;
	}

	Locker dlock( droid );

	// Cancel effects task
	Task* task = droid->getPendingTask( "droid_effects" );
	if( task != NULL ){
		Core::getTaskManager()->cancelTask(task);
		droid->removePendingTask( "droid_effects" );
	}

}

String DroidEffectsModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}

void DroidEffectsModuleDataComponent::onCall(){
	deactivate();
}

void DroidEffectsModuleDataComponent::onStore(){
	deactivate();
}

void DroidEffectsModuleDataComponent::addToStack(BaseDroidModuleComponent* other){

	DroidEffectsModuleDataComponent* otherModule = cast<DroidEffectsModuleDataComponent*>(other);
	if( otherModule == NULL )
		return;

	DroidComponent* droidComponent = cast<DroidComponent*>(otherModule->getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	ManagedReference<DroidEffectsModuleTemplate*> moduleTemplate = cast<DroidEffectsModuleTemplate*>(droidComponent->getObjectTemplate());
	if (moduleTemplate == NULL){
		info("Module was null");
		return;
	}

	if( !installedEffects.contains( moduleTemplate->getEffectName() ) ){
		installedEffects.put( moduleTemplate->getEffectName(), moduleTemplate->getAnimation() );
	}

}

bool DroidEffectsModuleDataComponent::toBinaryStream(ObjectOutputStream* stream) {

	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);

	return true;
}

int DroidEffectsModuleDataComponent::writeObjectMembers(ObjectOutputStream* stream) {

	String _name;
	int _offset;
	uint32 _totalSize;

	_name = "installedEffects";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< VectorMap<String,String> >::toBinaryStream(&installedEffects, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "configuredEffects";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< Vector<String> >::toBinaryStream(&configuredEffects, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "configuredDelays";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< Vector<int> >::toBinaryStream(&configuredDelays, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	return 3;
}

bool DroidEffectsModuleDataComponent::readObjectMember(ObjectInputStream* stream, const String& name) {

	if (name == "installedEffects") {
		TypeInfo< VectorMap<String,String> >::parseFromBinaryStream(&installedEffects, stream);
		return true;
	}

	if (name == "configuredEffects") {
		TypeInfo< Vector<String> >::parseFromBinaryStream(&configuredEffects, stream);
		return true;
	}

	if (name == "configuredDelays") {
		TypeInfo< Vector<int> >::parseFromBinaryStream(&configuredDelays, stream);
		return true;
	}

	return false;
}

bool DroidEffectsModuleDataComponent::parseFromBinaryStream(ObjectInputStream* stream) {

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
