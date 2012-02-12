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
	ManagedWeakReference<CreatureObject*> weakDroid;
	ManagedWeakReference<CreatureObject*> weakPlayer;
	ManagedWeakReference<BountyMissionObjective*> weakObjective;
	int timeLeft;
	bool success;
	bool track;
	bool arakyd;
	int trackingsLeft;
	String zoneName;

	enum states { Init, DroidSent, Searching, Tracking, Completed};

	states state;

	void init(CreatureObject* player, CreatureObject* droid) {
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

		zoneName = droid->getZone()->getZoneName();

		state = DroidSent;
	}

	void droidSent(CreatureObject* droid) {
		Locker locker(droid);

		droid->destroyObjectFromWorld(true);

		reschedule(timeLeft * 1000);

		if (track) {
			state = Tracking;
		} else {
			state = Searching;
		}
	}

	void searching(CreatureObject* player, BountyMissionObjective* objective) {
		if (success) {
			findAndTrackSuccess(player, objective);
		} else {
			int randomNumber = System::random(5) + 1;
			player->sendSystemMessage("@mission/mission_generic:target_not_found_" + String::valueOf(randomNumber));
		}

		objective->setArakydDroid(NULL);
		state = Completed;
	}

	void tracking(CreatureObject* player, BountyMissionObjective* objective) {
		if (success) {
			findAndTrackSuccess(player, objective);

			if (trackingsLeft > 0) {
				player->sendSystemMessage("@mission/mission_generic:target_continue_tracking");
				reschedule(calculateTime(player) * 1000);
				trackingsLeft--;
				state = Tracking;
			} else {
				player->sendSystemMessage("@mission/mission_generic:target_track_lost");
				objective->setArakydDroid(NULL);
				state = Completed;
			}
		} else {
			int randomNumber = System::random(5) + 1;
			player->sendSystemMessage("@mission/mission_generic:target_not_found_" + String::valueOf(randomNumber));
			objective->setArakydDroid(NULL);
			state = Completed;
		}
	}

	void findAndTrackSuccess(CreatureObject* player, BountyMissionObjective* objective) {
		Locker locker(player);

		if (objective->getPlayerOwner() == NULL) {
			return;
		}

		objective->updateMissionStatus(2);

		if (arakyd) {
			player->sendSystemMessage("@mission/mission_generic:target_located_" + objective->getTargetZoneName());
		} else {
			if (objective->getTargetZoneName() == zoneName) {
				StringIdChatParameter message("@mission/mission_generic:assassin_target_location");
				message.setDI(getDistanceToTarget(player, objective));
				message.setTO("mission/mission_generic", getDirectionToTarget(player, objective));
				player->sendSystemMessage(message);
			} else {
				player->sendSystemMessage("@mission/mission_generic:target_not_on_planet");
			}
		}
	}

	bool getSuccess(CreatureObject* player, BountyMissionObjective* objective) {
		String skillToUse = "droid_find_chance";
		int maximumSkillMod = 155;
		if (track) {
			skillToUse = "droid_track_chance";
			maximumSkillMod = 125;
		}

		long long skillMods = player->getSkillMod(skillToUse) + player->getSkillModFromBuffs(skillToUse);

		int checkedSkillMods = skillMods;
		if (checkedSkillMods < 0) {
			checkedSkillMods = 0;
		} else if (checkedSkillMods > maximumSkillMod) {
			checkedSkillMods = maximumSkillMod;
		}

		int checkValue = checkedSkillMods - getTargetLevel(objective);
		if (checkValue < 5) {
			checkValue = 5;
		} else if (checkValue > 95) {
			checkValue = 95;
		}

		int randomValue = System::random(100);

		return randomValue < checkValue;
	}

	int calculateTime(CreatureObject* player) {
		String skillToUse = "droid_find_speed";
		int maximumSkillMod = 115;
		if (track) {
			skillToUse = "droid_track_speed";
			maximumSkillMod = 105;
		}

		long long skillMod = player->getSkillMod(skillToUse) + player->getSkillModFromBuffs(skillToUse);

		int checkedSkillMod = skillMod;
		if (checkedSkillMod < 0) {
			checkedSkillMod = 0;
		} else if (checkedSkillMod > maximumSkillMod) {
			checkedSkillMod = maximumSkillMod;
		}

		int time = 150 - checkedSkillMod;

		return time + System::random(time / 2);
	}

	int getTargetLevel(BountyMissionObjective* objective) {
		String targetTemplateName = objective->getMissionObject()->getTargetOptionalTemplate();

		CreatureTemplate* creoTempl = CreatureTemplateManager::instance()->getTemplate(targetTemplateName.hashCode());

		if (creoTempl != NULL) {
			return creoTempl->getLevel();
		} else {
			error("Could not find template for target.");
			return 0;
		}
	}

	int getDistanceToTarget(CreatureObject* player, BountyMissionObjective* objective) {
		Vector3 playerCoordinate;
		playerCoordinate.setX(player->getPositionX());
		playerCoordinate.setY(player->getPositionY());

		Vector3 targetCoordinate = objective->getTargetPosition();

		return playerCoordinate.distanceTo(targetCoordinate);
	}

	String getDirectionToTarget(CreatureObject* player, BountyMissionObjective* objective) {
		Vector3 targetCoordinate = objective->getTargetPosition();
		float dx = targetCoordinate.getX() - player->getPositionX();
		float dy = targetCoordinate.getY() - player->getPositionY();

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
	}

public:
	FindTargetTask(CreatureObject* droid, CreatureObject* player, BountyMissionObjective* objective, bool track, bool arakyd) :
		Logger("FindTargetTask") {
		weakDroid = droid;
		weakPlayer = player;
		weakObjective = objective;
		this->track = track;
		this->arakyd = arakyd;
		state = Init;

		timeLeft = calculateTime(player);

		success = getSuccess(player, objective);

		trackingsLeft = 0;
		if (track) {
			trackingsLeft = player->getSkillMod("droid_tracks");
		}
	}

	~FindTargetTask() {
		cancel();
	}

	void run() {
		ManagedReference<CreatureObject*> droid = weakDroid.get();
		ManagedReference<CreatureObject*> player = weakPlayer.get();
		ManagedReference<BountyMissionObjective*> objective = weakObjective.get();

		if (player == NULL || objective == NULL) {
			return;
		}

		switch(state) {
		case Init:
			if (droid == NULL) {
				return;
			}
			init(player, droid);
			break;
		case DroidSent:
			if (droid == NULL) {
				return;
			}
			droidSent(droid);
			break;
		case Searching:
			searching(player, objective);
			break;
		case Tracking:
			tracking(player, objective);
			break;
		case Completed:
			break;
		default:
			error("Incorrect state.");
			break;
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
