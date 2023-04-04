/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

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
#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"

DroidPlaybackModuleDataComponent::DroidPlaybackModuleDataComponent() {
	currentlyRecording = false;
	setLoggingName("DroidPlaybackModule");
	totalTracks = 1;
	performanceIndex = 0;
	recordingTrack = -1;
	recordingPerformanceIndex = 0;
}

DroidPlaybackModuleDataComponent::~DroidPlaybackModuleDataComponent() {

}

String DroidPlaybackModuleDataComponent::getModuleName() const {
	return String("playback_module");
}

void DroidPlaybackModuleDataComponent::initializeTransientMembers() {
	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());

	if (droidComponent == nullptr) {
		info("droidComponent was null");
		return;
	}

	if (droidComponent->hasKey("module_count")) {
		totalTracks = droidComponent->getAttributeHidden("module_count");
	}
}

void DroidPlaybackModuleDataComponent::doFlourish(int number) {
	ManagedReference<DroidObject*> droid = getDroidObject();

	if (droid == nullptr)
		return;

	if (!isPlayingMusic())
		return;

	Locker dlock(droid);

	if (!droid->hasPower()) {
		droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
		return;
	}

	PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();
	Performance* performance = performanceManager->getPerformanceFromIndex(performanceIndex);

	if (performance == nullptr)
		return;

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

void DroidPlaybackModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute("playback_modules", trackList.size());
}

void DroidPlaybackModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player == nullptr)
		return;

	ManagedReference<DroidObject*> droid = getDroidObject();

	if (droid == nullptr || droid->isDead() || droid->isIncapacitated() || droid->getLinkedCreature().get() != player)
		return;

	// Novice Musician required to utilize this module
	if (player->hasSkill("social_musician_novice")) {
		if (!isPlayingMusic())
			menuResponse->addRadialMenuItem(PLAYBACK_ACCESS_MENU, 3, "@pet/droid_modules:playback_menu_playback" );
		else
			menuResponse->addRadialMenuItem(PLAYBACK_STOP_MENU, 3, "@pet/droid_modules:playback_menu_stop_playback");
	}
}

int DroidPlaybackModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {
	if (selectedID == PLAYBACK_STOP_MENU) {
		deactivate();
	} else if (selectedID == PLAYBACK_ACCESS_MENU) {
		ManagedReference<DroidObject*> droid = getDroidObject();

		if (droid == nullptr || droid->getLinkedCreature().get() != player)
			return 0;

		if (!droid->hasPower()) {
			player->sendSystemMessage("@pet/droid_modules:playback_msg_play_out_of_power");
			return 0;
		}

		Locker dlock(droid, player);

		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::DROID_PLAYBACK_MENU, SuiListBox::HANDLETHREEBUTTON);
		box->setCallback(new SelectTrackSuiCallback(player->getZoneServer()));
		box->setPromptText("@pet/droid_modules:playback_list_prompt");
		box->setPromptTitle("@pet/droid_modules:playback_list_title"); // Playback Module
		box->setOkButton(true,"@pet/droid_modules:playback_btn_play_record"); // Record/Play
		box->setOtherButton(true, "@pet/droid_modules:playback_btn_delete"); // Delete
		box->setCancelButton(true, "@cancel");

		// Add tracks
		for(int i = 0; i< trackList.size(); i++) {
			int curTrack = trackList.elementAt(i);

			if (curTrack == 0) {
				String itemName = "@pet/droid_modules:playback_track " + String::valueOf(i+1) + " @pet/droid_modules:playback_blank_track";
				box->addMenuItem(itemName);
			} else {
				String itemName = getTrackName(curTrack);
				box->addMenuItem(itemName);
			}
		}

		box->setUsingObject(droid);
		player->getPlayerObject()->addSuiBox(box);
		player->sendMessage(box->generateMessage());
	}

	return 0;
}

String DroidPlaybackModuleDataComponent::getTrackName(int perfIndex) {
	String trackName = "";

	ManagedReference<DroidObject*> droid = getDroidObject();

	if (droid == nullptr)
		return trackName;

	SkillManager* skillManager = droid->getZoneServer()->getSkillManager();
	PerformanceManager* performanceManager = skillManager->getPerformanceManager();

	Performance* performance = performanceManager->getPerformanceFromIndex(perfIndex);

	if (performance == nullptr)
		return trackName;

	String instrumentName = performanceManager->getProperInstrumentName(performance->getInstrumentAudioId());
	String songName = performance->getName();

	if (Character::isDigit(songName.charAt(songName.length() - 1)))
		songName = songName.subString(0, (songName.length() - 1)) + " " + songName.subString(songName.length() - 1);

	trackName = instrumentName + " - " + songName;

	return trackName;
}

void DroidPlaybackModuleDataComponent::stopRecording(CreatureObject* player, bool success) {
	if (success) {
		trackList.setElementAt(recordingTrack, recordingPerformanceIndex);
		player->dropObserver(ObserverEventType::STARTENTERTAIN, observer);
		player->dropObserver(ObserverEventType::STOPENTERTAIN, observer);
		player->dropObserver(ObserverEventType::CHANGEENTERTAIN, observer);
	}

	currentlyRecording = false;
	recordingPerformanceIndex = 0;
	recordingTrack = -1;

	stopTimer();
}

void DroidPlaybackModuleDataComponent::playSong(CreatureObject* player, int perfIndex) {
	ManagedReference<DroidObject*> droid = getDroidObject();

	if (droid == nullptr || (!droid->isGrouped() && droid->getLinkedCreature().get() != player))
		return;

	if (isPlayingMusic())
		return;

	Locker plock(player);

	player->setListenToID(droid->getObjectID());

	plock.release();

	Locker dlock(droid);

	bool activeBandSong = false;
	int newPerfIndex = 0;

	SkillManager* skillManager = droid->getZoneServer()->getSkillManager();
	PerformanceManager* performanceManager = skillManager->getPerformanceManager();

	ManagedReference<GroupObject*> group = droid->getGroup();

	if (group != nullptr) {
		for (int i = 0; i < group->getGroupSize(); i++) {
			ManagedReference<CreatureObject*> groupMember = group->getGroupMember(i);

			if (groupMember == nullptr || !groupMember->isPlayerCreature() || groupMember == droid || !groupMember->isPlayingMusic())
				continue;

			ManagedReference<Facade*> memberFacade = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING);
			ManagedReference<EntertainingSession*> memberSession = dynamic_cast<EntertainingSession*> (memberFacade.get());

			if (memberSession == nullptr)
				continue;

			int memberPerformanceIndex = memberSession->getPerformanceIndex();

			if (memberPerformanceIndex == 0)
				continue;

			newPerfIndex = getMatchingIndex(droid, memberPerformanceIndex);
			activeBandSong = true;
			break;
		}
	}

	if (activeBandSong) {
		if (newPerfIndex == 0) {
			performanceManager->performanceMessageToDroidOwner(droid, nullptr, "performance", "music_track_not_available"); // Your droid does not have a track recorded for the current song in progress.
			return;
		}
		perfIndex = newPerfIndex;
	}

	performanceIndex = perfIndex;
	String performanceAnim = "";

	if (performanceIndex > 0) {
		droid->setPosture(CreaturePosture::SKILLANIMATING);

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();
		Performance* performance = performanceManager->getPerformanceFromIndex(performanceIndex);

		if (performance == nullptr)
			return;

		if (performance->isMusic())
			performanceAnim = performanceManager->getInstrumentAnimation(performance->getInstrumentAudioId());
		else
			performanceAnim = performanceManager->getDanceAnimation(performance->getPerformanceIndex());
	} else {
		droid->setPosture(CreaturePosture::UPRIGHT);
	}

	droid->setPerformanceAnimation(performanceAnim, false);
	droid->setPerformanceStartTime(0, false);
	droid->setPerformanceType(performanceIndex, false);

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(droid);
	dcreo6->updatePerformanceAnimation(performanceAnim);
	dcreo6->updatePerformanceStartTime(0);
	dcreo6->updatePerformanceType(performanceIndex);
	dcreo6->close();

	droid->broadcastMessage(dcreo6, true);

	Reference<Task*> task = new DroidPlaybackTask(this);
	droid->addPendingTask("droid_playback", task, 0);
}

int DroidPlaybackModuleDataComponent::getMatchingIndex(DroidObject* droid, int memberPerformanceIndex) {
	SkillManager* skillManager = droid->getZoneServer()->getSkillManager();
	PerformanceManager* performanceManager = skillManager->getPerformanceManager();

	Performance* memberPerformance = performanceManager->getPerformanceFromIndex(memberPerformanceIndex);

	if (memberPerformance == nullptr)
		return 0;

	for(int i = 0; i< trackList.size(); i++) {
		int curTrack = trackList.elementAt(i);

		if (curTrack == 0)
			continue;

		Performance* perf = performanceManager->getPerformanceFromIndex(curTrack);

		if (perf == nullptr)
			continue;

		if (memberPerformance->getName() == perf->getName())
			return curTrack;
	}

	return 0;
}

void DroidPlaybackModuleDataComponent::sessionTimeout(CreatureObject* player, int state) {
	if (currentlyRecording) {
		if (state == STATE_WAITING_TO_RECORD) {
			player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_timeout");
			stopRecording(player, false);
		} else if (state == STATE_RECORDING_TRACK) {
			player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_complete");

			if (recordingPerformanceIndex > 0) {
				trackList.setElementAt(recordingTrack, recordingPerformanceIndex);
			} else {
				player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_corrupted");
			}

			stopRecording(player, true);
		}
	}
}

void DroidPlaybackModuleDataComponent::stopTimer() {
	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid != nullptr) {
		Locker dlock(droid);

		Task* ptask = droid->getPendingTask("droid_recording");

		if (ptask != nullptr) {
			Core::getTaskManager()->cancelTask(ptask);
			droid->removePendingTask("droid_recording");
		}
	}
}

void DroidPlaybackModuleDataComponent::songChanged(CreatureObject* player) {
	if (currentlyRecording) {
		player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_corrupted");
		stopRecording(player, false);
	}
}

void DroidPlaybackModuleDataComponent::songStopped(CreatureObject* player) {
	if (currentlyRecording) {
		player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_not_finished");
		stopRecording(player, false);
	}
}

void DroidPlaybackModuleDataComponent::startRecordingSession(CreatureObject* entertainer, int index) {
	ManagedReference<DroidObject*> droid = getDroidObject();

	if (droid == nullptr)
		return;

	if (entertainer->isPlayingMusic()) {
		entertainer->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_already_playing");
		return;
	}

	if (trackList.get(index) != 0) {
		entertainer->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_track_full"); // Recording failed: You cannot record over a track that is not empty.
		return;
	}

	if (observer == nullptr) {
		observer = new DroidPlaybackObserver(this);
		observer->deploy();
	}

	currentlyRecording = true;
	recordingTrack = index;

	Locker dlock(droid);

	stopTimer();

	Reference<Task*> task = new RecordTrackTimeoutEvent(this, entertainer, STATE_WAITING_TO_RECORD);
	droid->addPendingTask("droid_recording", task, 30 * 1000);

	entertainer->sendSystemMessage("@pet/droid_modules:playback_msg_rec_start"); // Your droid is ready to start recording your music.

	// set the slot
	observer->setSlot(index);
	entertainer->registerObserver(ObserverEventType::STARTENTERTAIN, observer);
	entertainer->registerObserver(ObserverEventType::CHANGEENTERTAIN, observer);
	entertainer->registerObserver(ObserverEventType::STOPENTERTAIN, observer);
}

void DroidPlaybackModuleDataComponent::deleteTrack(CreatureObject* player, int slotIndex) {
	if (slotIndex >= 0 && slotIndex <= trackList.size()) {
		if (trackList.get(slotIndex) == 0) {
			player->sendSystemMessage("@pet/droid_modules:playback_msg_del_track_already_empty");
			return;
		}

		trackList.setElementAt(slotIndex, 0);
		player->sendSystemMessage("@pet/droid_modules:playback_msg_del_track_deleted");
	}
}

void DroidPlaybackModuleDataComponent::setTrack(CreatureObject* player, int perfIndex) {
	if (isPlayingMusic()) {
		player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_fail_already_playing");
		return;
	}

	if (isRecording()) {
		stopTimer();

		ManagedReference<DroidObject*> droid = getDroidObject();

		if (droid != nullptr) {
			Locker dlock(droid);

			Reference<Task*> task = new RecordTrackTimeoutEvent(this, player, STATE_RECORDING_TRACK);
			droid->addPendingTask("droid_recording", task, 30 * 1000);
			recordingPerformanceIndex = perfIndex;
			player->sendSystemMessage("@pet/droid_modules:playback_msg_rec_begun");
		}
	}
}

int DroidPlaybackModuleDataComponent::getBatteryDrain() {
	if (isPlayingMusic()) {
		return 4;
	}

	return 0;
}

void DroidPlaybackModuleDataComponent::deactivate() {
	// set choosen track to empty
	performanceIndex = 0;

	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == nullptr) {
		info("Droid is null");
		return;
	}

	Locker dlock(droid);

	stopTimer();

	Task* task = droid->getPendingTask("droid_playback");

	if (task != nullptr) {
		Core::getTaskManager()->cancelTask(task);
		droid->removePendingTask("droid_playback");
	}

	ManagedReference<PlayerManager*> playerManager = droid->getZoneServer()->getPlayerManager();

	if (playerManager != nullptr) {
		for (int i = 0; i < listeners.size(); i++) {
			ManagedReference<CreatureObject*> object = droid->getZoneServer()->getObject(listeners.get(i)).castTo<CreatureObject*>();

			if (object != nullptr) {
				Locker clock(object, droid);

				if (object->getListenID() == droid->getObjectID()) // stop all listeners and send packets and force it so mood gets fixed
					playerManager->stopListen(object, droid->getObjectID(), true, true, false);
			}
		}
	}

	droid->setPerformanceAnimation("", false);
	droid->setPerformanceStartTime(0, false);
	droid->setPerformanceType(performanceIndex, false);

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(droid);
	dcreo6->updatePerformanceAnimation("");
	dcreo6->updatePerformanceStartTime(0);
	dcreo6->updatePerformanceType(performanceIndex);
	dcreo6->close();

	droid->broadcastMessage(dcreo6, true);

	droid->notifyObservers(ObserverEventType::STOPENTERTAIN, droid);

	if (droid->getPosture() == CreaturePosture::SKILLANIMATING)
		droid->setPosture(CreaturePosture::UPRIGHT);
}

String DroidPlaybackModuleDataComponent::toString() const {
	return BaseDroidModuleComponent::toString();
}

void DroidPlaybackModuleDataComponent::onCall() {
	deactivate();
}

void DroidPlaybackModuleDataComponent::onStore() {
	deactivate();
}

void DroidPlaybackModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());

	if (droidComponent == nullptr) {
		info("droidComponent was null");
		return;
	}

	totalTracks += 1;
	droidComponent->changeAttributeValue("module_count", (float)totalTracks);

	// add to the track list
	trackList.add(0);
}

void DroidPlaybackModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	totalTracks = 1;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());

	if (droidComponent != nullptr) {
		droidComponent->addProperty("module_count", (float)totalTracks, 0, "hidden", true);
	}

	// add to the track list
	trackList.add(0);
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

	_name = "trackList";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< Vector<int> >::toBinaryStream(&trackList, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "totalTracks";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo< int >::toBinaryStream(&totalTracks, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	return 2;
}

bool DroidPlaybackModuleDataComponent::readObjectMember(ObjectInputStream* stream, const String& name) {
	if (name == "trackList") {
		TypeInfo< Vector<int> >::parseFromBinaryStream(&trackList, stream);
		return true;
	} else if (name == "totalTracks") {
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
		if (readObjectMember(stream, _name)) {
		}
		stream->setOffset(_currentOffset + _varSize);
	}

	return true;
}
