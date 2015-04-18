/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file SurveyTask.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef SURVEYTASK_H_
#define SURVEYTASK_H_

#include "engine/engine.h"
#include "server/zone/packets/resource/SurveyMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

class ResourceSpawner;

class SurveyTask : public Task {
	ManagedReference<CreatureObject* > playerCreature;
	SurveyMessage* surveyMessage;
	ManagedReference<WaypointObject*> waypoint;
	float density;
	ManagedReference<ResourceSpawn*> resourceSpawn;

public:
	SurveyTask(ManagedReference<CreatureObject* > play, SurveyMessage* surveyM, ManagedReference<WaypointObject*> way, float density, ManagedReference<ResourceSpawn*> resourceSpawn) {
		playerCreature = play;
		surveyMessage = surveyM;
		waypoint = way;
		this->density = density;
		this->resourceSpawn = resourceSpawn;
	}

	void run() {
		Locker playerLocker(playerCreature);

		// Send Survey Results
		playerCreature->sendMessage(surveyMessage);

		if (waypoint != NULL) {
			playerCreature->getPlayerObject()->addWaypoint(waypoint, false, true);

			// Send Waypoint System Message
			playerCreature->sendSystemMessage("@survey:survey_waypoint");

			//Notify any survey mission observers.
			playerCreature->notifyObservers(ObserverEventType::SURVEY, resourceSpawn, density);
		}

		playerCreature->removePendingTask("survey");
	}
};

#endif /* SURVEYTASK_H_ */
