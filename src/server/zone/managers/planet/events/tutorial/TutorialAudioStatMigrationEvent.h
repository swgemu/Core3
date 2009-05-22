/*
 * TutorialAudioStatMigrationEvent.h
 *
 *  Created on: Jan 21, 2009
 *      Author: swgemu
 */

#ifndef TUTORIALAUDIOSTATMIGRATIONEVENT_H_
#define TUTORIALAUDIOSTATMIGRATIONEVENT_H_

#include "../../PlanetManagerImplementation.h"

class TutorialAudioStatMigrationEvent : public Event {
	PlanetManager* planet;
	Player* player;

public:
	TutorialAudioStatMigrationEvent(PlanetManager* Planet, Player* pl) : Event() {
		planet = Planet;
		player = pl;

		setKeeping(true);
	}

	bool activate() {
		planet->tutorialStepStatMigration(player);

		return true;
	}

};

#endif /* TUTORIALAUDIOSTATMIGRATIONEVENT_H_ */
