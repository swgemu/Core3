#include "server/zone/objects/tangible/eventperk/FlagGame.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/params/creature/CreatureFlag.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/components/FlagGameDataComponent.h"
#include "server/zone/objects/tangible/tasks/FlagGamePulseTask.h"

void FlagGameImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();
}

void FlagGameImplementation::notifyInsertToZone(Zone* zone) {
	if (rebScore > impScore)
		changeFlag(Factions::FACTIONREBEL);
	else if (impScore > rebScore)
		changeFlag(Factions::FACTIONIMPERIAL);
	else
		changeFlag(0);
}

uint32 FlagGameImplementation::getFlagTemplate(uint32 faction) {
	switch (faction) {
	case Factions::FACTIONREBEL:
		return 0x1C517D16; // STRING_HASHCODE("object/tangible/furniture/all/event_flag_game_reb_banner.iff")
	case Factions::FACTIONIMPERIAL:
		return 0xA5EBEFBE; // STRING_HASHCODE("object/tangible/furniture/all/event_flag_game_imp_banner.iff")
	case 0:
	default:
		return 0x21C1197C; // STRING_HASHCODE("object/tangible/furniture/all/event_flag_game_neut_banner.iff")
	}
}

void FlagGameImplementation::changeFlag(uint32 faction) {
	removeCurFlag();

	ManagedReference<ZoneServer*> zoneServer = getZoneServer();

	if (zoneServer == NULL)
		return;

	ManagedReference<TangibleObject*> flag = zoneServer->createObject(getFlagTemplate(faction), "playerstructures", 1).castTo<TangibleObject*>();

	if (flag == NULL)
		return;

	Locker locker(flag);

	FlagGameDataComponent* data = cast<FlagGameDataComponent*>(flag->getDataObjectComponent()->get());

	if (data == NULL) {
		error("No dataObjectComponent.");
		flag->destroyObjectFromDatabase(true);
		return;
	}

	data->setFlagGame(_this.getReferenceUnsafeStaticCast());

	flag->initializePosition(getPositionX(), getPositionZ(), getPositionY());
	flag->setDirection(Math::deg2rad(getDirectionAngle()));
	zone->transferObject(flag, -1, true);

	curFlag = flag;
	factionControl = faction;
	lastFlagChange.updateToCurrentTime();
}

void FlagGameImplementation::removeCurFlag() {
	ManagedReference<TangibleObject*> flag = curFlag.get();

	if (flag != NULL) {
		Locker locker(flag);
		flag->destroyObjectFromWorld(true);
		flag->destroyObjectFromDatabase();
	}
}

void FlagGameImplementation::tryFlagChange(CreatureObject* player) {
	Time currentTime;
	int timeDiff = currentTime.getMiliTime() - lastFlagChange.getMiliTime();

	if (timeDiff < 15000) {
		player->sendSystemMessage("@event_perk:flag_game_cannot_switch_yet");
		return;
	}

	if (player->getFaction() == 0 || player->getFaction() == factionControl || gameStatus == 0 || gameStatus == 2) {
		return;
	}

	if (player->getFaction() == Factions::FACTIONREBEL) {
		announceToPlayers("flag_game_rebel_capture");
	} else if (player->getFaction() == Factions::FACTIONIMPERIAL) {
		announceToPlayers("flag_game_imperial_capture");
	} else {
		return;
	}

	changeFlag(player->getFaction());
}

bool FlagGameImplementation::canUseFlag(CreatureObject* player) {
	if ((player->getPvpStatusBitmask() & CreatureFlag::OVERT) && player->getFaction() != factionControl)
		return true;

	return false;
}

void FlagGameImplementation::startGame() {
	if (timeLimit == 0)
		timeLimit = 10 * 60 * 1000; // 10 minute default

	gameStatus = 1;
	impScore = 0;
	rebScore = 0;
	gameStartTime.updateToCurrentTime();
	lastFlagChange.updateToCurrentTime();
	announceToPlayers("flag_game_game_starting");
	activateGamePulse();
}

void FlagGameImplementation::endGame() {
	if (rebScore > impScore) {
		changeFlag(Factions::FACTIONREBEL);
		doVictoryEffects(Factions::FACTIONREBEL);
		announceToPlayers("flag_game_over_reb_win");
	} else if (impScore > rebScore) {
		changeFlag(Factions::FACTIONIMPERIAL);
		doVictoryEffects(Factions::FACTIONIMPERIAL);
		announceToPlayers("flag_game_over_imp_win");
	} else {
		changeFlag(0);
		announceToPlayers("flag_game_over_tie");
	}

	gameStatus = 2;
}

void FlagGameImplementation::activateGamePulse() {
	if (gamePulse == NULL) {
		gamePulse = new FlagGamePulseTask(_this.getReferenceUnsafeStaticCast());
		gamePulse->reschedule(15 * 1000); // 15 second pulse
	} else {
		gamePulse->reschedule(15 * 1000);
	}
}

void FlagGameImplementation::announceToPlayers(const String& message) {
	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
	zone->getInRangeObjects(getPositionX(), getPositionY(), 256, &closeObjects,	true);

	for (int i = 0; i < closeObjects.size(); i++) {
		SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());
		if (targetObject != NULL && targetObject->isPlayerCreature()) {
			ManagedReference<CreatureObject*> player = cast<CreatureObject*>(targetObject);

			if (player != NULL)
				player->sendSystemMessage("@event_perk:" + message);
		}
	}
}

void FlagGameImplementation::showScores(CreatureObject* player) {
	if (gameStatus != 2)
		return;

	StringIdChatParameter msg;
	msg.setStringId("@event_perk:flag_game_score_1");
	msg.setDI(impScore);
	player->sendSystemMessage(msg);

	msg.setStringId("@event_perk:flag_game_score_2");
	msg.setDI(rebScore);
	player->sendSystemMessage(msg);
}

void FlagGameImplementation::doVictoryEffects(uint32 faction) {
	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
	zone->getInRangeObjects(getPositionX(), getPositionY(), 256, &closeObjects,	true);

	for (int i = 0; i < closeObjects.size(); i++) {
		SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());
		if (targetObject != NULL && targetObject->isPlayerCreature()) {
			ManagedReference<CreatureObject*> player = cast<CreatureObject*>(targetObject);

			if (player != NULL && player->getFaction() == faction && (player->getPvpStatusBitmask() & CreatureFlag::OVERT)) {
				if (player->getFaction() == Factions::FACTIONREBEL) {
					player->playEffect("clienteffect/holoemote_rebel.cef", "head");
				} else if (player->getFaction() == Factions::FACTIONIMPERIAL) {
					player->playEffect("clienteffect/holoemote_imperial.cef", "head");
				}
			}
		}
	}
}

void FlagGameImplementation::destroyObjectFromWorld(bool sendSelfDestroy) {
	removeCurFlag();

	TangibleObjectImplementation::destroyObjectFromWorld(sendSelfDestroy);
}
