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

#ifndef UPDATENEARESTMISSIONFORGROUPTASK_H_
#define UPDATENEARESTMISSIONFORGROUPTASK_H_

#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"

namespace server {
namespace zone {
namespace objects {
namespace group {
namespace tasks {

class UpdateNearestMissionForGroupTask : public Task {
	ManagedWeakReference<GroupObject*> groupRef;
	unsigned int planetCRC;

public:
	UpdateNearestMissionForGroupTask(GroupObject* group, const unsigned int planetCRC)
		: Task() {
		this->groupRef = group;
		this->planetCRC = planetCRC;
	}

	void run() {
		Reference<GroupObject*> group = groupRef.get();
		if (group == NULL) {
			return;
		}
		Locker locker(group);

		// Filter the group by planet.
		Vector<Reference<CreatureObject*> > groupMembersOnPlanet;
		for(int i = 0; i < group->getGroupSize(); i++) {
			if (group->getGroupMember(i) != NULL && group->getGroupMember(i)->isPlayerCreature()) {
				Reference<CreatureObject*> groupMember = (group->getGroupMember(i)).castTo<CreatureObject*>();
				if (groupMember->getPlanetCRC() == planetCRC) {
					groupMembersOnPlanet.add(groupMember);
				}
			}
		}

		if (groupMembersOnPlanet.size() == 0) {
			return;
		}

		// Find the average location for all members on the planet.
		float totalX = 0;
		float totalY = 0;
		float totalZ = 0;
		for(int i = 0; i< groupMembersOnPlanet.size(); i++) {
			if (groupMembersOnPlanet.get(i) != NULL) {
				CreatureObject* groupMember = groupMembersOnPlanet.get(i);
				Vector3 groupMemberPostion = groupMember->getWorldPosition();
				totalX += groupMemberPostion.getX();
				totalY += groupMemberPostion.getY();
				totalZ += groupMemberPostion.getZ();
			}
		}
		Vector3 averageGroupMemberLocation = Vector3(totalX / groupMembersOnPlanet.size(), totalY / groupMembersOnPlanet.size(), totalZ / groupMembersOnPlanet.size());

		// Find all of the missions for the group members on the planet.
		Vector<Reference<MissionObject*> > missionsOnPlanet;
		for(int i = 0; i< groupMembersOnPlanet.size(); i++) {
			CreatureObject* groupMember = groupMembersOnPlanet.get(i);
			if (groupMember != NULL) {
				SceneObject* datapad = groupMember->getSlottedObject("datapad");
				if (datapad == NULL) {
					continue;
				}
				int numberOfMissionsForMember = 0;
				Locker clocker(groupMember, group);
				for(int k = 0; k < datapad->getContainerObjectsSize(); k++) {
					if (datapad->getContainerObject(k) != NULL && datapad->getContainerObject(k)->isMissionObject()) {
						numberOfMissionsForMember++;
						Reference<MissionObject*> mission = datapad->getContainerObject(k).castTo<MissionObject*>();
						if (mission->getWaypointToMission() != NULL && mission->getWaypointToMission()->getPlanetCRC() == planetCRC) {
							missionsOnPlanet.add(mission);
						}
					}
				}
				if (numberOfMissionsForMember >= 2) {
					continue;
				}
			}
		}

		// Finally find the closest mission.
		Reference<MissionObject*> nearestMission = NULL;
		if (missionsOnPlanet.size() == 1) {
			nearestMission = missionsOnPlanet.get(0);
		}
		else {
			float shortestDistanceSoFar = std::numeric_limits<float>::max();
			for(int i = 0; i< missionsOnPlanet.size(); i++) {
				float disstanceToMission = calculateManhattanDistanceToMission(averageGroupMemberLocation, missionsOnPlanet.get(i));
				if (disstanceToMission < shortestDistanceSoFar) {
					shortestDistanceSoFar = disstanceToMission;
					nearestMission = missionsOnPlanet.get(i);
				}
			}
		}

		// If a mission was found, add the nearest mission waypoint for all members. Otherwise if a mission
		// was not found then remove the nearest mission waypoint for all members.
		for(int i = 0; i< groupMembersOnPlanet.size(); i++) {
			CreatureObject* groupMember = groupMembersOnPlanet.get(i);

			Locker clocker(groupMember, group);

			if (groupMember->getPlayerObject() != NULL) {
				PlayerObject* ghost = groupMember->getPlayerObject();

				setPlayersNearestMissionForGroupWaypoint(ghost, nearestMission);
			}
		}
	}

private:
	float calculateManhattanDistanceToMission(const Vector3& position, MissionObject* mission) {
		// The Manhattan distance will give us a "good enough" value for comparing the relative distance
		// to two missions.  It can fail if two missions are very close to each other but that's fine for
		// the purposes of this waypoint.
		if (mission == NULL || mission->getWaypointToMission() == NULL) {
			return std::numeric_limits<float>::max();
		}

		return fabs(position.getX() - mission->getWaypointToMission()->getWorldPositionX())
				+ fabs(position.getY() - mission->getWaypointToMission()->getWorldPositionY());
	}

	void setPlayersNearestMissionForGroupWaypoint(PlayerObject* ghost, MissionObject* nearestMissionForGroup) {
		if (ghost == NULL) {
			return;
		}

		if (nearestMissionForGroup == NULL) {
			ghost->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP, true);
		}

		else {
			Zone* zone = nearestMissionForGroup->getZone();
			uint32 crc = zone ? zone->getZoneCRC() : 0;

			ManagedReference<WaypointObject*> waypoint = ghost->getWaypointBySpecialType(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP);
			if (waypoint == NULL) {
				ZoneServer* zoneServer = ghost->getZoneServer();
				waypoint = zoneServer->createObject(0xc456e788, 1).castTo<WaypointObject*>();
			}
			waypoint->setCustomObjectName(UnicodeString("Nearest mission for group"), false);
			waypoint->setSpecialTypeID(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP);
			waypoint->setPlanetCRC(crc);
			waypoint->setPosition(nearestMissionForGroup->getWaypointToMission()->getPositionX(),
					nearestMissionForGroup->getWaypointToMission()->getPositionZ(),
					nearestMissionForGroup->getWaypointToMission()->getPositionY());
			waypoint->setColor(WaypointObject::COLOR_YELLOW);
			waypoint->setActive(true);
			ghost->addWaypoint(waypoint, false);
		}
	}
};

} // namespace tasks
} // namespace group
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::group::tasks;

#endif /* UPDATENEARESTMISSIONFORGROUPTASK_H_ */
