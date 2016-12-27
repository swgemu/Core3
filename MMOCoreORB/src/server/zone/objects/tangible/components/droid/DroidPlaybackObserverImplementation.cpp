/*
 * DroidPlaybackObserverImplementation.cpp
 */

#include "server/zone/objects/tangible/components/droid/DroidPlaybackObserver.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/creature/events/DroidPlaybackEvent.h"

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

	// make a task and lock the module to run it.

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

		Reference<Task*> task = new DroidPlaybackEvent(module.get(), player, song, instrument, DroidPlaybackEvent::SET_TRACK);
		task->execute();
	}
	else if (eventType == ObserverEventType::CHANGEENTERTAIN) {
		Reference<Task*> task = new DroidPlaybackEvent(module.get(), player, "", -1, DroidPlaybackEvent::CHANGE_SONG);
		task->execute();
	}
	else if (eventType == ObserverEventType::STOPENTERTAIN) {
		Reference<Task*> task = new DroidPlaybackEvent(module.get(), player, "", -1, DroidPlaybackEvent::STOP_PLAYING);
		task->execute();
	}

	return 0;
}
