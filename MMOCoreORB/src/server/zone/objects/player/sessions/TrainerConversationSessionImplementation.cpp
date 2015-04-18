/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/player/sessions/TrainerConversationSession.h"

void TrainerConversationSessionImplementation::clearTrainableSkills() {
	while (trainableSkills.size() > 0) {
		trainableSkills.remove(0);
	}
}

void TrainerConversationSessionImplementation::clearNextSkills() {
	while (nextSkills.size() > 0) {
		nextSkills.remove(0);
	}
}
