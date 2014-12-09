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
	SceneObject* sceno = dynamic_cast<SceneObject*>(observable);

	if (sceno == NULL)
		return 1;
	if(!sceno->isPlayerCreature()) {
		return 1;
	}
	CreatureObject* creature = dynamic_cast<CreatureObject*>(sceno);
	PlayerObject* player = creature->getPlayerObject();
	ManagedReference<EntertainingSession*> playingSession = player->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();
	if(!playingSession->isPlayingMusic())
		return 1;

	if (eventType == ObserverEventType::STARTENTERTAIN) {
		String song = playingSession->getPerformanceName();
		int instrument = playingSession->getInstrument(creature)->getInstrumentType();
		module->setTrack(song,instrument,slot);
	}
	if (eventType == ObserverEventType::CHANGEENTERTAIN) {
		module->songChanged();
	}
	if (eventType == ObserverEventType::STOPENTERTAIN) {
		module->songStopped();
	}
	return 0;
}
