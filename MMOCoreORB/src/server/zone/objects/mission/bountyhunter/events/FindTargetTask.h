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

#ifndef FINDTARGETTASK_H_
#define FINDTARGETTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/mission/BountyMissionObjective.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/Zone.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace bountyhunter {
namespace events {

class FindTargetTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> droid;
	ManagedWeakReference<CreatureObject*> player;
	ManagedWeakReference<BountyMissionObjective*> objective;
	int timeLeft;
	bool success;
	bool track;
	bool arakyd;
	int trackingsLeft;

	enum states { Init, DroidSent, Searching, Tracking, Completed};

	states state;

public:
	FindTargetTask(CreatureObject* droid, CreatureObject* player, BountyMissionObjective* objective, bool track, bool arakyd) :
		Logger("FindTargetTask") {
		this->droid = droid;
		this->player = player;
		this->objective = objective;
		this->track = track;
		this->arakyd = arakyd;
		state = Init;

		if (objective == NULL) {
			error("No objective.");
		}

		timeLeft = calculateTime();

		success = getSuccess();

		trackingsLeft = 0;
		if (track) {
			trackingsLeft = player->getSkillMod("droid_tracks");
		}
	}

	~FindTargetTask() {
		cancel();
	}

	void run() {
		ManagedReference<CreatureObject*> strongDroidRef = droid.get();
		ManagedReference<CreatureObject*> playerRef = player.get();

		if (strongDroidRef == NULL || playerRef == NULL)
			return;

		switch(state) {
		case Init: {
			Locker locker(player);
			Locker clocker(droid, player);

			droid->setPosture(CreaturePosture::SITTING, true);
			if (arakyd) {
				player->sendSystemMessage("@mission/mission_generic:probe_droid_takeoff");
			} else {
				player->sendSystemMessage("@mission/mission_generic:seeker_droid_launched");
			}
			reschedule(10 * 1000);
			timeLeft -= 10;
			state = DroidSent;
			break;
		} case DroidSent: {
			Locker locker(droid);

			droid->destroyObjectFromWorld(true);
			state = Searching;
			reschedule(timeLeft * 1000);
			break;
		} case Searching: {
			if (success) {
				findAndTrackSuccess();
			} else {
				int randomNumber = System::random(5) + 1;
				player->sendSystemMessage("@mission/mission_generic:target_not_found_" + String::valueOf(randomNumber));
				state = Completed;
				clearActiveDroid();
			}
			break;
		} case Tracking: {
			findAndTrackSuccess();
			break;
		} case Completed:
			break;
		default:
			error("Incorrect state.");
			break;
		}
	}

	void clearActiveDroid() {
		ManagedReference<BountyMissionObjective*> objectiveRef = objective.get();

		if (objectiveRef == NULL) {
			return;
		}

		objectiveRef->setArakydDroid(NULL);
	}

	void findAndTrackSuccess() {
		ManagedReference<CreatureObject*> playerRef = player.get();

		if (playerRef == NULL) {
			return;
		}

		ManagedReference<BountyMissionObjective*> objectiveRef = objective.get();

		if (objectiveRef == NULL) {
			return;
		}

		Locker locker(player);

		if (objective != NULL) {
			if (objective->getPlayerOwner() == NULL)
				return;

			objective->updateMissionStatus(3);
		}

		if (arakyd) {
			player->sendSystemMessage("@mission/mission_generic:" + getTargetZoneName());
		} else {
			if (getTargetZoneName() == droid->getZone()->getZoneName()) {
				StringIdChatParameter message("@mission/mission_generic:assassin_target_location");
				message.setDI(getDistanceToTarget());
				message.setTO("mission/mission_generic", getDirectionToTarget());
				player->sendSystemMessage(message);
			} else {
				player->sendSystemMessage("@mission/mission_generic:target_not_on_planet");
			}
		}
		if (track) {
			if (trackingsLeft > 0) {
				player->sendSystemMessage("@mission/mission_generic:target_continue_tracking");
				reschedule(calculateTime() * 1000);
				trackingsLeft--;
				state = Tracking;
			} else {
				player->sendSystemMessage("@mission/mission_generic:target_track_lost");
				clearActiveDroid();
				state = Completed;
			}
		} else {
			clearActiveDroid();
			state = Completed;
		}
	}

	String getTargetZoneName() {
		ManagedReference<BountyMissionObjective*> objectiveRef = objective.get();

		if (objectiveRef == NULL) {
			int randomNumber = System::random(5) + 1;
			return "target_not_found_" + String::valueOf(randomNumber);
		}

		return "target_located_" + objectiveRef->getTargetZoneName();
	}

	bool getSuccess() {
		ManagedReference<CreatureObject*> playerRef = player.get();

		if (playerRef == NULL) {
			return 0;
		}

		String skillToUse = "droid_find_chance";
		int maximumSkillMod = 155;
		if (track) {
			skillToUse = "droid_track_chance";
			maximumSkillMod = 125;
		}

		long long skillMods = playerRef->getSkillMod(skillToUse) + playerRef->getSkillModFromBuffs(skillToUse);

		int checkedSkillMods = skillMods;
		if (checkedSkillMods < 0) {
			checkedSkillMods = 0;
		} else if (checkedSkillMods > maximumSkillMod) {
			checkedSkillMods = maximumSkillMod;
		}

		int checkValue = checkedSkillMods - getTargetLevel();
		if (checkValue < 5) {
			checkValue = 5;
		} else if (checkValue > 95) {
			checkValue = 95;
		}

		int randomValue = System::random(100);

		return randomValue < checkValue;
	}

	int calculateTime() {
		ManagedReference<CreatureObject*> playerRef = player.get();

		if (playerRef == NULL) {
			return 0;
		}

		String skillToUse = "droid_find_speed";

		if (track) {
			skillToUse = "droid_track_speed";
		}

		long long skillMod = playerRef->getSkillMod(skillToUse) + playerRef->getSkillModFromBuffs(skillToUse);

		int checkedSkillMod = skillMod;
		if (checkedSkillMod < 0) {
			checkedSkillMod = 0;
		} else if (checkedSkillMod > 120) {
			checkedSkillMod = 120;
		}

		int time = 150 - checkedSkillMod;

		return time + System::random(time / 2);
	}

	int getTargetLevel() {
		ManagedReference<MissionObjective*> objectiveRef = objective.get();

		if (objectiveRef == NULL) {
			return 0;
		}

		String targetTemplateName = objectiveRef->getMissionObject()->getTargetOptionalTemplate();

		CreatureTemplate* creoTempl = CreatureTemplateManager::instance()->getTemplate(targetTemplateName.hashCode());

		if (creoTempl != NULL) {
			return creoTempl->getLevel();
		} else {
			error("Could not find template for target.");
			return 0;
		}
	}

	int getDistanceToTarget() {
		ManagedReference<CreatureObject*> playerRef = player.get();

		if (playerRef == NULL) {
			return 0;
		}

		ManagedReference<BountyMissionObjective*> objectiveRef = objective.get();

		if (objectiveRef != NULL) {
			Vector3 playerCoordinate;
			playerCoordinate.setX(playerRef->getPositionX());
			playerCoordinate.setY(playerRef->getPositionY());

			Vector3 targetCoordinate = objectiveRef->getTargetPosition();

			return playerCoordinate.distanceTo(targetCoordinate);
		} else {
			return 0;
		}
	}

	String getDirectionToTarget() {
		ManagedReference<CreatureObject*> playerRef = player.get();

		if (playerRef == NULL) {
			return "unknown_direction";
		}

		ManagedReference<BountyMissionObjective*> objectiveRef = objective.get();

		if (objectiveRef != NULL) {
			Vector3 targetCoordinate = objectiveRef->getTargetPosition();
			float dx = targetCoordinate.getX() - playerRef->getPositionX();
			float dy = targetCoordinate.getY() - playerRef->getPositionY();

			if (dx > 0) {
				if (dy > 0) {
					if (dx < dy * 0.5) {
						return "north";
					} else if (dx > dy * 2) {
						return "east";
					} else {
						return "northeast";
					}
				} else {
					if (dx < -dy * 0.5) {
						return "south";
					} else if (dx > -dy * 2) {
						return "east";
					} else {
						return "southeast";
					}
				}
			} else {
				if (dy > 0) {
					if (-dx < dy * 0.5) {
						return "north";
					} else if (-dx > dy * 2) {
						return "west";
					} else {
						return "northwest";
					}
				} else {
					if (-dx < -dy * 0.5) {
						return "south";
					} else if (-dx > -dy * 2) {
						return "west";
					} else {
						return "southwest";
					}
				}
			}
		} else {
			return "unknown_direction";
		}
	}
};

} // namespace events
} // namespace bountyhunter
} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission::bountyhunter::events;

#endif /* FINDTARGETTASK_H_ */
