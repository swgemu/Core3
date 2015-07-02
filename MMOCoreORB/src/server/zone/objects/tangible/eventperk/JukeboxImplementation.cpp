#include "server/zone/objects/tangible/eventperk/Jukebox.h"
#include "server/zone/objects/tangible/eventperk/JukeboxObserver.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/creature/sui/JukeboxSelectionSuiCallback.h"
#include "server/zone/templates/tangible/EventPerkDeedTemplate.h"
#include "server/zone/objects/tangible/tasks/RemoveEventPerkItemTask.h"
#include "server/zone/managers/player/JukeboxSong.h"

void JukeboxImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	activateRemoveEvent();
}

void JukeboxImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	ManagedReference<CreatureObject*> perkOwner = getOwner().get();

	if ((perkOwner != NULL && perkOwner == player) || (player->getPlayerObject() != NULL && player->getPlayerObject()->isPrivileged())) {
		TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
		menuResponse->addRadialMenuItem(132, 3, "@event_perk:mnu_show_exp_time"); // Show Expiration Time
	}

	if (!isASubChildOf(player)) {
		menuResponse->addRadialMenuItem(68, 3, "@event_perk:jukebox_operate");
		menuResponse->addRadialMenuItemToRadialID(68, 69, 3, "@event_perk:jukebox_start_music");
		menuResponse->addRadialMenuItemToRadialID(68, 70, 3, "@event_perk:jukebox_stop_music");
	}
}


int JukeboxImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	ManagedReference<CreatureObject*> perkOwner = getOwner().get();

	bool isOwner = perkOwner != NULL && player == perkOwner;

	// Non owners cannot pick up
	if (selectedID == 10 && !isOwner)
		return 0;

	if (selectedID == 69) {
		if (isOwner)
			doMusicSelection(player);
		else
			playMusicToPlayer(player, curSong);
	} else if (selectedID == 70) {
		if (isOwner)
			stopPlaying();
		else
			playMusicToPlayer(player, "sound/music_silence.snd");
	} else if (selectedID == 132) {
		Time currentTime;
		uint32 timeDelta = currentTime.getMiliTime() - getPurchaseTime()->getMiliTime();
		uint32 minutes = (EventPerkDeedTemplate::TIME_TO_LIVE - timeDelta) / 60000;

		StringIdChatParameter params("event_perk", "show_exp_time"); // This rental will expire in approximately %DI minutes.
		params.setDI(minutes);
		player->sendSystemMessage(params);
		return 0;
	} else if (selectedID == 10) {
		stopPlaying();
	}
	return 0;
}

void JukeboxImplementation::notifyInsertToZone(Zone* zone) {
	ManagedReference<Jukebox*> jbox = _this.getReferenceUnsafeStaticCast();

	Locker _lock(jbox);

	createChildObjects();

	ManagedReference<JukeboxObserver*> observer = new JukeboxObserver(jbox);

	jbox->registerObserver(ObserverEventType::PARENTCHANGED, observer);

	ManagedReference<SceneObject*> obj = jbox->getParentRecursively(SceneObjectType::BUILDING);

	if (obj == NULL || !obj->isStructureObject())
		setRadius(100);
	else
		setRadius(30);

	SortedVector<ManagedReference<SceneObject*> >* children = jbox->getChildObjects();

	for (int i = 0; i < children->size(); ++i) {
		ManagedReference<SceneObject*> child = children->get(i);

		if (child != NULL && child->isActiveArea()) {
			ManagedReference<ActiveArea*> area = cast<ActiveArea*>(child.get());
			area->registerObserver(ObserverEventType::ENTEREDAREA, observer);
			area->registerObserver(ObserverEventType::EXITEDAREA, observer);
		}
	}
}

void JukeboxImplementation::setRadius(float newRadius) {
	ManagedReference<Jukebox*> jbox = _this.getReferenceUnsafeStaticCast();

	SortedVector<ManagedReference<SceneObject*> >* children = jbox->getChildObjects();

	if (newRadius == radius)
		return;

	if (children == NULL)
		return;

	radius = newRadius;

	for (int i = 0; i < children->size(); ++i) {
		ManagedReference<SceneObject*> child = children->get(i);

		if (child != NULL && child->isActiveArea()) {
			ManagedReference<ActiveArea*> area = cast<ActiveArea*>(child.get());

			Locker clocker(area, jbox);
			area->setRadius(newRadius);
			return;
		}
	}
}

void JukeboxImplementation::doMusicSelection(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

	if (playerManager == NULL)
		return;

	ManagedReference<SuiListBox*> listbox = new SuiListBox(player, SuiWindowType::JUKEBOX_SELECTION);
    listbox->setCallback(new JukeboxSelectionSuiCallback(server->getZoneServer()));
	listbox->setPromptTitle("@event_perk_jukebox_songs:songs_t"); // Music Select
	listbox->setPromptText("@event_perk_jukebox_songs:songs_d"); // Select a song to play from the list below.
	listbox->setUsingObject(_this.getReferenceUnsafeStaticCast());
	listbox->setForceCloseDistance(32.f);
	listbox->setCancelButton(true, "@cancel");

	int songListSize = playerManager->getNumJukeboxSongs();
	JukeboxSong* song = NULL;

	for (int i = 0; i < songListSize; i++) {
		song = playerManager->getJukeboxSong(i);

		if (song != NULL) {
			listbox->addMenuItem(song->getStringId());
		}
	}

	ghost->addSuiBox(listbox);
	player->sendMessage(listbox->generateMessage());
}

void JukeboxImplementation::playMusicToPlayer(CreatureObject* player, const String& song) {
	if (player == NULL || !player->isPlayerCreature())
		return;

	PlayMusicMessage* pmm = new PlayMusicMessage(song);

	player->sendMessage(pmm);
}

void JukeboxImplementation::changeMusic(const String& song) {
	Zone* zone = getZone();

	if (zone == NULL)
		return;

	curSong = song;

	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
	zone->getInRangeObjects(getPositionX(), getPositionY(), radius, &closeObjects, true);

	for (int i = 0; i < closeObjects.size(); i++) {
		SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());
		if (targetObject != NULL && targetObject->isPlayerCreature()) {
			ManagedReference<CreatureObject*> player = cast<CreatureObject*>(targetObject);

			if (player != NULL)
				playMusicToPlayer(player, song);
		}
	}
}

void JukeboxImplementation::startPlaying(const String& song) {
	isPlaying = true;
	changeMusic(song);
}

void JukeboxImplementation::stopPlaying() {
	isPlaying = false;
	changeMusic("sound/music_silence.snd");
}


void JukeboxImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	ManagedReference<CreatureObject*> strongOwner = owner.get();

	if (strongOwner != NULL) {
		Locker clocker(strongOwner, _this.getReferenceUnsafeStaticCast());

		PlayerObject* ghost = strongOwner->getPlayerObject();

		if (ghost != NULL) {
			ghost->removeEventPerk(_this.getReferenceUnsafeStaticCast());
		}
	}

	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void JukeboxImplementation::activateRemoveEvent(bool immediate) {
	if (removeEventPerkItemTask == NULL) {
		removeEventPerkItemTask = new RemoveEventPerkItemTask(_this.getReferenceUnsafeStaticCast());

		Time currentTime;
		uint64 timeDelta = currentTime.getMiliTime() - purchaseTime.getMiliTime();

		if (timeDelta >= EventPerkDeedTemplate::TIME_TO_LIVE || immediate) {
			removeEventPerkItemTask->execute();
		} else {
			removeEventPerkItemTask->schedule(EventPerkDeedTemplate::TIME_TO_LIVE - timeDelta);
		}
	} else if (immediate) {
		if (removeEventPerkItemTask->isScheduled()) {
			removeEventPerkItemTask->reschedule(1);
		} else {
			removeEventPerkItemTask->execute();
		}
	}
}
