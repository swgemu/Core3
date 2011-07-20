/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef FISHINGSESSION_H_
#define FISHINGSESSION_H_


#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {
class FishingEvent;
}
}
}
}
}


namespace server {
namespace zone {
namespace managers {
namespace minigames {

class FishingSession {
	ManagedReference<CreatureObject*> player;
	Reference<FishingEvent*> event;
	ManagedReference<SceneObject*> marker;

	int nextAction;
	int fish;
	uint32 boxID;
	int fishingState;
	String mood;

public:
	FishingSession(CreatureObject* player, FishingEvent* event, SceneObject* marker, int nextAction, int fish, uint32 boxID, int fishingState, String mood) {
		this->player = player;
		this->event = event;
		this->marker = marker;
		this->nextAction = nextAction;
		this->fish = fish;
		this->boxID = boxID;
		this->fishingState = fishingState;
		this->mood = mood;
	}

	void setEvent(FishingEvent* event) {
		this->event = event;
	}

	FishingEvent* getEvent() {
		return event;
	}

	void setNextAction(int nextAction) {
		this->nextAction = nextAction;
	}

	int getNextAction() {
		return nextAction;
	}

	void setFishBoxID(uint32 boxID) {
		this->boxID = boxID;
	}

	uint32 getFishBoxID() {
		return boxID;
	}

	SceneObject* getMarker() {
		return marker;
	}

	void setMarker(SceneObject* marker) {
		this->marker = marker;
	}

	int getFish() {
		return fish;
	}

	void setFish(int fish) {
		this->fish = fish;
	}

	int getFishingState() {
		return fishingState;
	}

	void setFishingState(int fishingState) {
		this->fishingState = fishingState;
	}

	void update(int nextAction, SceneObject* marker, int fish, uint32 boxID, int fishingState) {
		setNextAction(nextAction);
		setMarker(marker);
		setFish(fish);
		setFishBoxID(boxID);
		setFishingState(fishingState);
	}

	String getMoodString() {
		return mood;
	}
};

}
}
}
}

#endif /* FISHINGSESSION_H_ */
