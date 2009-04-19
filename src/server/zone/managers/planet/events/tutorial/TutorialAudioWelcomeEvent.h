/*
 * TutorialAudioWelcomeEvent.h
 *
 *  Created on: Jan 21, 2009
 *      Author: swgemu
 */

#ifndef TUTORIALAUDIOWELCOMEEVENT_H_
#define TUTORIALAUDIOWELCOMEEVENT_H_

class TutorialAudioWelcomeEvent : public Event {
	PlanetManager* planet;
	Player* player;

public:
	TutorialAudioWelcomeEvent(PlanetManager* Planet, Player* pl) : Event() {
		planet = Planet;
		player = pl;
		setKeeping(true);
	}

	bool activate() {
		planet->tutorialStepWelcome(player);

		return true;
	}

};
#endif /* TUTORIALAUDIOWELCOMEEVENT_H_ */
