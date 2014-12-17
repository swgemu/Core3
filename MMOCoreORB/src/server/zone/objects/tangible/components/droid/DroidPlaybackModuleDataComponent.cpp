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

#include "DroidPlaybackModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/player/events/RecordTrackTimeoutEvent.h"
#include "server/zone/objects/creature/events/DroidPlaybackTask.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/SelectTrackSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"
#include "server/zone/managers/skill/Performance.h"
#include "server/zone/managers/skill/PerformanceManager.h"
#include "server/zone/packets/object/Flourish.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/player/PlayerManager.h"


DroidPlaybackModuleDataComponent::DroidPlaybackModuleDataComponent() {
	active = false;
	recording = false;
	setLoggingName("DroidPlaybackModule");
	totalTracks = 1;
	selectedIndex = -1;
	recordingTrack = -1;
	recordingSong = "";
	recordingInstrument = 1;
}
DroidPlaybackModuleDataComponent::~DroidPlaybackModuleDataComponent() {

}
String DroidPlaybackModuleDataComponent::getModuleName() {
	return String("playback_module");
}
void DroidPlaybackModuleDataComponent::initializeTransientMembers() {

	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	if(droidComponent->hasKey("module_count")) {
		totalTracks = droidComponent->getAttributeHidden("module_count");
	}
}

String DroidPlaybackModuleDataComponent::getCurrentTrack() {
	if (selectedIndex == -1) {
		return "";
	}
	if (selectedIndex >=0 && selectedIndex < tracks.size()) {
		return tracks.get(selectedIndex);
	}
	return "";
}
void DroidPlaybackModuleDataComponent::doFlourish(int number) {
	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null");
		return;
	}
	if (!active) {
		return;
	}
	Locker dlock(droid);

	if( !droid->hasPower() ){
		droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
		return;
	}

	PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();
	Performance* performance = NULL;
	performance = performanceManager->getSong(getCurrentTrack(), getCurrentInstrument());
	if(performance == NULL) {
		return;
	}

	float baseActionDrain =  performance->getActionPointsPerLoop();
	float flourishActionDrain = baseActionDrain / 2.0;
	int actionDrain = (int)round((flourishActionDrain * 10 + 0.5) / 10.0); // Round to nearest dec for actual int cost
	actionDrain = droid->calculateCostAdjustment(CreatureAttribute::QUICKNESS, actionDrain);

	if (droid->getHAM(CreatureAttribute::ACTION) > actionDrain) {
		droid->inflictDamage(droid, CreatureAttribute::ACTION, actionDrain, false, true);
		Flourish* flourish = new Flourish(droid, number);
		droid->broadcastMessage(flourish, true);
	}
}
void DroidPlaybackModuleDataComponent::addListener(uint64 id) {
	if (listeners.contains(id))
		listeners.removeElement(id);
	listeners.add(id);
}
int DroidPlaybackModuleDataComponent::getCurrentInstrument() {
	if (selectedIndex == -1) {
		return -1;
	}
	if (selectedIndex >=0 && selectedIndex < instruments.size()) {
		return instruments.get(selectedIndex);
	}
	return -1;
}


void DroidPlaybackModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute( "playback_modules", tracks.size());
}

void DroidPlaybackModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if( player == NULL )
		return;

	// Novice Musician required to utilize this module
	if (player->hasSkill("social_musician_novice")){
		menuResponse->addRadialMenuItem(PLAYBACK_ACCESS_MENU, 3, "@pet/droid_modules:playback_menu_playback" );
		menuResponse->addRadialMenuItem(PLAYBACK_STOP_MENU, 3, "@pet/droid_modules:playback_menu_stop_playback");
	}

}

int DroidPlaybackModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	if(selectedID == PLAYBACK_STOP_MENU) {
		deactivate();
	}
	if(selectedID == PLAYBACK_ACCESS_MENU) {
		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null");
			return 0;
		}

		if( !droid->hasPower() ){
			player->sendSystemMessage("@pet/droid_modules:playback_msg_play_out_of_power");
			return 0;
		}

		Locker dlock( droid, player );
		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::DROID_PLAYBACK_MENU, SuiListBox::HANDLETHREEBUTTON);
		box->setCallback(new SelectTrackSuiCallback(player->getZoneServer()));
		box->setPromptText("@pet/droid_modules:playback_list_prompt");
		box->setPromptTitle("@pet/droid_modules:playback_list_title"); // Configure Effects
		box->setOkButton(true,"@pet/droid_modules:playback_btn_play_record");
		box->setOtherButton(true, "@pet/droid_modules:playback_btn_delete");
		box->setCancelButton(true, "@cancel");
		// Add tracks
		for(int i =0; i< tracks.size();i++){
			box->addMenuItem( tracks.elementAt(i), i);
		}

		box->setUsingObject(droid);
		player->getPlayerObject()->addSuiBox(box);
		player->sendMessage(box->generateMessage());

	}
	return 0;
}

void DroidPlaybackModuleDataComponent::stopRecording(CreatureObject* player, bool success) {
	if (success) {
		tracks.setElementAt(recordingTrack,recordingSong);
		instruments.setElementAt(recordingTrack,recordingInstrument);
		player->dropObserver(ObserverEventType::STARTENTERTAIN, observer);
		player->dropObserver(ObserverEventType::STOPENTERTAIN, observer);
		player->dropObserver(ObserverEventType::CHANGEENTERTAIN, observer);
	}
	recording = false;
	recordingInstrument = -1;
	recordingSong = "";
	recordingTrack = -1;
	stopTimer();
}
bool DroidPlaybackModuleDataComponent::trackEmpty(int index) {
	return tracks.get(index) == "@pet/droid_modules:playback_blank_track";
}
bool DroidPlaybackModuleDataComponent::isActive() {
	return active;
}
bool DroidPlaybackModuleDataComponent::isPlayingMusic() {
	return active;
}
void DroidPlaybackModuleDataComponent::playSong(CreatureObject* player, int index) {
	if (active) {
		deactivate();
	}
	if (index >= 0 && index <= tracks.size()) {
		Reference<Task*> task = new DroidPlaybackTask(this);
		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null" );
			return;
		}
		Locker dlock( droid );
		active = true;
		selectedIndex = index;
		droid->addPendingTask("droid_playback",task,0);
	}
}
void DroidPlaybackModuleDataComponent::sessionTimeout(CreatureObject* player, int state) {
	if(recording) {
		if (state == STATE_WAITING_TO_RECORD) {
			player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_timeout");
			stopRecording(player,false);
		}
		if (state == STATE_RECORDING_TRACK) {
			player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_complete");
			if (recordingSong.length() > 0) {
				tracks.setElementAt(recordingTrack,recordingSong);
				instruments.setElementAt(recordingTrack,recordingInstrument);
			} else {
				player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_corrupted");
			}
			stopRecording(player,true);
		}
	}
}
void DroidPlaybackModuleDataComponent::stopTimer() {
	ManagedReference<DroidObject*> droid = getDroidObject();
	if(droid != NULL) {
		Locker dlock(droid);
		Task* ptask = droid->getPendingTask( "droid_recording" );
		if (ptask != NULL) {
			Core::getTaskManager()->cancelTask(ptask);
			droid->removePendingTask( "droid_recording" );
		}
	}
}
void DroidPlaybackModuleDataComponent::songChanged(CreatureObject* player) {
	if(recording) {
		player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_corrupted");
		stopRecording(player,false);
	}
}
void DroidPlaybackModuleDataComponent::songStopped(CreatureObject* player) {
	if (recording) {
		player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_not_finished");
		stopRecording(player,false);
	}
}


void DroidPlaybackModuleDataComponent::startRecordingSession(CreatureObject* entertainer, int index) {
	if (recording) {
		entertainer->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_already_playing");
		return;
	}
	if (observer == NULL) {
		observer = new DroidPlaybackObserver(this);
		observer->deploy();
	}
	recording = true;
	recordingTrack = index;
	ManagedReference<DroidObject*> droid = getDroidObject();
	if(droid != NULL) {
		Locker dlock(droid);
		stopTimer();
		Reference<Task*> task = new RecordTrackTimeoutEvent( this,entertainer,STATE_WAITING_TO_RECORD );
		droid->addPendingTask("droid_recording",task,30 * 1000);
		// set the slot
		observer->setSlot(index);
		entertainer->registerObserver(ObserverEventType::STARTENTERTAIN, observer);
		entertainer->registerObserver(ObserverEventType::CHANGEENTERTAIN, observer);
		entertainer->registerObserver(ObserverEventType::STOPENTERTAIN, observer);
	}
}
void DroidPlaybackModuleDataComponent::deleteTrack(CreatureObject* player, int slotIndex) {
	if( 0 <= slotIndex && slotIndex <= tracks.size() ){
		// check to see if ti was blank
		if (tracks.get(slotIndex) == "@pet/droid_modules:playback_blank_track") {
			player->sendSystemMessage("@pet/droid_modules:playback_msg_del_track_already_empty");
			return;
		}
		tracks.setElementAt( slotIndex, "@pet/droid_modules:playback_blank_track" );
		instruments.setElementAt(slotIndex,-1);
		player->sendSystemMessage("@pet/droid_modules:playback_msg_del_track_deleted");
	}
}
void DroidPlaybackModuleDataComponent::setTrack( CreatureObject* player, String song, int instrument){
	if (active) {
		player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_already_playing");
		return;
	}
	if (recording) {
		stopTimer();
		ManagedReference<DroidObject*> droid = getDroidObject();
		if(droid != NULL) {
			Locker dlock(droid);
			Reference<Task*> task = new RecordTrackTimeoutEvent( this,player,STATE_RECORDING_TRACK );
			droid->addPendingTask("droid_recording",task,30 * 1000);
			recordingSong = song;
			recordingInstrument = instrument;
			player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_begun");
		}
	}
}

int DroidPlaybackModuleDataComponent::getBatteryDrain() {
	if( active ){
		return 4;
	}
	return 0;
}

void DroidPlaybackModuleDataComponent::deactivate() {

	// set choosen track to empty
	active = false;
	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null" );
		return;
	}
	Locker dlock( droid );
	stopTimer();
	// cancel animation of the droid
	String performance = getCurrentTrack();
	// Cancel playback task if it hasnt launched yet
	Task* task = droid->getPendingTask( "droid_playback" );
	if( task != NULL ){
		Core::getTaskManager()->cancelTask(task);
		droid->removePendingTask( "droid_playback" );
	}
	droid->setPerformanceAnimation(performance, false);
	droid->setPerformanceCounter(0, false);
	droid->setInstrumentID(0, false);

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(droid);
	dcreo6->updatePerformanceAnimation(performance);
	dcreo6->updatePerformanceCounter(0);
	dcreo6->updateInstrumentID(0);
	dcreo6->close();

	droid->broadcastMessage(dcreo6, true);
	selectedIndex = -1;
	ManagedReference<PlayerManager*> playerManager = droid->getZoneServer()->getPlayerManager();
	if (playerManager != NULL) {
		for(int i=0;i<listeners.size();i++) {
			ManagedReference<SceneObject*> object = droid->getZoneServer()->getObject(listeners.get(i));
			CreatureObject* c = cast<CreatureObject*>(object.get());
			Locker lock(c);
			if(c->getListenID() == droid->getObjectID())
				playerManager->stopListen(c,droid->getObjectID());
		}
	}

}

String DroidPlaybackModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}

void DroidPlaybackModuleDataComponent::onCall(){
	deactivate();
}

void DroidPlaybackModuleDataComponent::onStore(){
	deactivate();
}

void DroidPlaybackModuleDataComponent::addToStack(BaseDroidModuleComponent* other){

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	totalTracks += 1;
	droidComponent->changeAttributeValue("module_count",(float)totalTracks);
	// add to the track list
	tracks.add("@pet/droid_modules:playback_blank_track");
	instruments.add(-1);

}
void DroidPlaybackModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	totalTracks = 1;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL) {
		droidComponent->addProperty("module_count",(float)totalTracks,0,"hidden",true);
	}
	// add to the track list
	tracks.add("@pet/droid_modules:playback_blank_track");
	instruments.add(-1);
}

/** Serilization Methods below */

bool DroidPlaybackModuleDataComponent::toBinaryStream(ObjectOutputStream* stream) {

	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);

	return true;
}

int DroidPlaybackModuleDataComponent::writeObjectMembers(ObjectOutputStream* stream) {

	String _name;
	int _offset;
	uint32 _totalSize;

	_name = "tracks";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< Vector<String> >::toBinaryStream(&tracks, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "instruments";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< Vector<int> >::toBinaryStream(&instruments, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);


	_name = "totalTracks";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< int >::toBinaryStream(&totalTracks, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	return 3;
}

bool DroidPlaybackModuleDataComponent::readObjectMember(ObjectInputStream* stream, const String& name) {

	if (name == "tracks") {
		TypeInfo< Vector<String> >::parseFromBinaryStream(&tracks, stream);
		return true;
	}
	if (name == "instruments") {
		TypeInfo< Vector<int> >::parseFromBinaryStream(&instruments, stream);
		return true;
	}
	if (name == "totalTracks") {
		TypeInfo< int >::parseFromBinaryStream(&totalTracks, stream);
	}
	return false;
}

bool DroidPlaybackModuleDataComponent::parseFromBinaryStream(ObjectInputStream* stream) {

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
