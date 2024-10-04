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
#include "templates/tangible/EventPerkDeedTemplate.h"
#include "server/zone/objects/tangible/tasks/RemoveEventPerkItemTask.h"
#include "server/zone/managers/player/JukeboxSong.h"
#include "server/zone/objects/area/space/SpaceActiveArea.h"

void JukeboxImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	activateRemoveEvent();
}

void JukeboxImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	ManagedReference<CreatureObject*> perkOwner = owner.get();

	PlayerObject* playerObject = player->getPlayerObject();

	if (playerObject == nullptr)
		return;

	if ((perkOwner != nullptr && perkOwner == player) || playerObject->isPrivileged()) {
		TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
		menuResponse->addRadialMenuItem(132, 3, "@event_perk:mnu_show_exp_time"); // Show Expiration Time
	}

	if (!isASubChildOf(player)) {
		menuResponse->addRadialMenuItem(68, 3, "@event_perk:jukebox_operate");
		menuResponse->addRadialMenuItemToRadialID(68, 69, 3, "@event_perk:jukebox_start_music");
		menuResponse->addRadialMenuItemToRadialID(68, 70, 3, "@event_perk:jukebox_stop_music");


		if (playerObject->isPrivileged() && player->getParentID() == 0) {
			menuResponse->addRadialMenuItem(72, 3, "Staff Functionality");
			menuResponse->addRadialMenuItemToRadialID(72, 73, 3, "@ui_radial:item_pickup");
		}
	} else {
		if (playerObject->isPrivileged() && player->getParentID() == 0) {
			menuResponse->addRadialMenuItem(72, 3, "Staff Functionality");
			menuResponse->addRadialMenuItemToRadialID(72, 73, 3, "@ui_radial:item_drop");
		}
	}
}


int JukeboxImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	ManagedReference<CreatureObject*> perkOwner = owner.get();

	bool isOwner = perkOwner != nullptr && player == perkOwner;

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
	} else if (selectedID == 73) {
		PlayerObject* playerObject = player->getPlayerObject();

		if (playerObject == nullptr)
			return 0;

		if (playerObject->isPrivileged() && player->getParentID() == 0) {
			if (isASubChildOf(player)) {
				Zone* zone = player->getZone();

				if (zone == nullptr)
					return 0;

				ManagedReference<Jukebox*> jbox = _this.getReferenceUnsafeStaticCast();

				jbox->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
				jbox->setDirection(Math::deg2rad(player->getDirectionAngle()));
				zone->transferObject(jbox, -1, true);
			} else {
				stopPlaying();

				ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

				if (inventory == nullptr)
					return 0;

				ManagedReference<Jukebox*> jbox = _this.getReferenceUnsafeStaticCast();

				inventory->transferObject(jbox, -1, true, true);
			}
		}
	}
	return 0;
}

void JukeboxImplementation::notifyInsertToZone(Zone* zone) {
	ManagedReference<Jukebox*> jbox = _this.getReferenceUnsafeStaticCast();

	Locker _lock(jbox);

	// Spawn active area only while in ground zones
	if (!zone->isSpaceZone()) {
		createChildObjects();
	}

	ManagedReference<JukeboxObserver*> observer = new JukeboxObserver(jbox);

	if (observer == nullptr) {
		return;
	}

	jbox->registerObserver(ObserverEventType::PARENTCHANGED, observer);

	ManagedReference<SceneObject*> obj = jbox->getRootParent();

	if (obj == nullptr || (!obj->isStructureObject() && !obj->isPobShip())) {
		setRadius(OUTDOOR_RADIUS);
	} else {
		setRadius(INDOOR_RADIUS);
	}

	SortedVector<ManagedReference<SceneObject*> >* children = jbox->getChildObjects();

	for (int i = 0; i < children->size(); ++i) {
		ManagedReference<SceneObject*> child = children->get(i);

		if (child != nullptr && child->isActiveArea()) {
			ManagedReference<ActiveArea*> area = cast<ActiveArea*>(child.get());

			if (area != nullptr) {
				area->registerObserver(ObserverEventType::ENTEREDAREA, observer);
				area->registerObserver(ObserverEventType::EXITEDAREA, observer);
			}
		}
	}
}

void JukeboxImplementation::notifyInsert(TreeEntry* entry) {
	// info(true) << "JukeboxImplementation::notifyInsert -- called";

	auto sceneO = static_cast<SceneObject*>(entry);

	if (sceneO == nullptr || !sceneO->isPlayerCreature()) {
		return;
	}

	auto zone = getZone();

	if (zone == nullptr || !zone->isSpaceZone()) {
		return;
	}

	if (sceneO->getRootParent() != getRootParent()) {
		return;
	}

	// info(true) << "JukeboxImplementation::notifyInsert -- called for player: " << sceneO->getDisplayedName();

	playMusicToPlayer(sceneO->asCreatureObject(), curSong);
}

void JukeboxImplementation::notifyDissapear(TreeEntry* entry) {
	// info(true) << "JukeboxImplementation::notifyDissapear -- called";

	auto sceneO = static_cast<SceneObject*>(entry);

	if (sceneO == nullptr || !sceneO->isPlayerCreature()) {
		return;
	}

	// info(true) << "JukeboxImplementation::notifyDissapear -- called for player: " << sceneO->getDisplayedName();

	playMusicToPlayer(sceneO->asCreatureObject(), "sound/music_silence.snd");
}

void JukeboxImplementation::setRadius(float newRadius) {
	ManagedReference<Jukebox*> jbox = _this.getReferenceUnsafeStaticCast();

	SortedVector<ManagedReference<SceneObject*> >* children = jbox->getChildObjects();

	if (newRadius == radius)
		return;

	if (children == nullptr)
		return;

	radius = newRadius;

	for (int i = 0; i < children->size(); ++i) {
		ManagedReference<SceneObject*> child = children->get(i);

		if (child != nullptr && child->isActiveArea()) {
			ManagedReference<ActiveArea*> area = cast<ActiveArea*>(child.get());

			Locker clocker(area, jbox);
			area->setRadius(newRadius);
			return;
		}
	}
}

void JukeboxImplementation::doMusicSelection(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

	if (playerManager == nullptr)
		return;

	ManagedReference<SuiListBox*> listbox = new SuiListBox(player, SuiWindowType::JUKEBOX_SELECTION);
    listbox->setCallback(new JukeboxSelectionSuiCallback(server->getZoneServer()));
	listbox->setPromptTitle("@event_perk_jukebox_songs:songs_t"); // Music Select
	listbox->setPromptText("@event_perk_jukebox_songs:songs_d"); // Select a song to play from the list below.
	listbox->setUsingObject(_this.getReferenceUnsafeStaticCast());
	listbox->setForceCloseDistance(32.f);
	listbox->setCancelButton(true, "@cancel");

	int songListSize = playerManager->getNumJukeboxSongs();
	JukeboxSong* song = nullptr;

	for (int i = 0; i < songListSize; i++) {
		song = playerManager->getJukeboxSong(i);

		if (song != nullptr) {
			listbox->addMenuItem(song->getStringId());
		}
	}

	ghost->addSuiBox(listbox);
	player->sendMessage(listbox->generateMessage());
}

void JukeboxImplementation::playMusicToPlayer(CreatureObject* player, const String& song) {
	if (player == nullptr || !player->isPlayerCreature()) {
		return;
	}

	PlayMusicMessage* pmm = new PlayMusicMessage(song);

	player->sendMessage(pmm);
}

void JukeboxImplementation::changeMusic(const String& song) {
	Zone* zone = getZone();

	if (zone == nullptr) {
		return;
	}

	curSong = song;

	SortedVector<ManagedReference<TreeEntry*>> closeObjectsCopy(200, 50);

	if (zone->isSpaceZone()) {
		auto rootParent = getRootParent();

		if (rootParent != nullptr) {
			auto closeObjectsVector = rootParent->getCloseObjects();

			if (closeObjectsVector != nullptr) {
				closeObjectsVector->safeCopyReceiversTo(closeObjectsCopy, CloseObjectsVector::PLAYERTYPE);
			}
		}
	} else {
		zone->getInRangeObjects(getWorldPositionX(), getWorldPositionZ(), getWorldPositionY(), radius, &closeObjectsCopy, true);
	}

	PlayMusicMessage* pmm = new PlayMusicMessage(song);

#ifdef LOCKFREE_BCLIENT_BUFFERS
	Reference<BasePacket*> pack = pmm;
#endif

	for (int i = 0; i < closeObjectsCopy.size(); i++) {
		SceneObject* targetObject = static_cast<SceneObject*>(closeObjectsCopy.getUnsafe(i).get());

		if (targetObject == nullptr || !targetObject->isPlayerCreature()) {
			continue;
		}

		// info(true) << "sending music message to: " << targetObject->getDisplayedName();

#ifdef LOCKFREE_BCLIENT_BUFFERS
		targetObject->sendMessage(pack);
#else
		targetObject->sendMessage(pmm->clone());
#endif
	}

#ifndef LOCKFREE_BCLIENT_BUFFERS
	delete pmm;
#endif
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

	if (strongOwner != nullptr) {
		Locker clocker(strongOwner, _this.getReferenceUnsafeStaticCast());

		PlayerObject* ghost = strongOwner->getPlayerObject();

		if (ghost != nullptr) {
			ghost->removeEventPerk(_this.getReferenceUnsafeStaticCast());
		}
	}

	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void JukeboxImplementation::activateRemoveEvent(bool immediate) {
	if (removeEventPerkItemTask == nullptr) {
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
