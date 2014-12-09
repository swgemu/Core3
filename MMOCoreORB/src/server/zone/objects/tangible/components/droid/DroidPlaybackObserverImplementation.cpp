/*
 * DroidPlaybackObserverImplementation.cpp
 */

#include "server/zone/objects/tangible/components/droid/DroidPlaybackObserver.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"

int DroidPlaybackObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	// check params we should have the player around here
	SceneObject* sceno = dynamic_cast<SceneObject*>(arg1);
	if (sceno == NULL) {
		return 1;
	}
	if(!sceno->isPlayerCreature()) {
		return 1;
	}
	CreatureObject* player = dynamic_cast<CreatureObject*>(sceno);
	if (player == NULL) {
		return 1;
	}

	if (eventType == ObserverEventType::STARTENTERTAIN) {
		ManagedReference<EntertainingSession*> playingSession = player->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();
		if(playingSession == NULL) {
			return 1;
		}
		if(!playingSession->isPlayingMusic()) {
			return 1;
		}
		String song = playingSession->getPerformanceName();
		int instrument = playingSession->getInstrument(player)->getInstrumentType();
		module->setTrack(player,song,instrument);
	}
	if (eventType == ObserverEventType::CHANGEENTERTAIN) {
		module->songChanged(player);
	}
	if (eventType == ObserverEventType::STOPENTERTAIN) {
		module->songStopped(player);
	}
	return 0;
}
