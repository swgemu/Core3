#include "UpdateNearestMissionForGroupTask.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"

// #define DEBUG_GROUPS

UpdateNearestMissionForGroupTask::UpdateNearestMissionForGroupTask(GroupObject* group, const unsigned int planetCRC) : Task() {
	setLoggingName("UpdateNearestMissionForGroupTask");

	this->groupRef = group;
	this->planetCRC = planetCRC;
}

void UpdateNearestMissionForGroupTask::run() {
	Reference<GroupObject*> group = groupRef.get();
	if (group == nullptr) {
		return;
	}

#ifdef DEBUG_GROUPS
	info(true) << "UpdateNearestMissionForGroupTask called for Group ID: " << group->getObjectID();
#endif

	Locker locker(group);

	// Filter the group by planet.
	Vector<Reference<CreatureObject*> > groupMembersOnPlanet;
	for (int i = 0; i < group->getGroupSize(); i++) {
		Reference<CreatureObject*> groupMember = group->getGroupMember(i);

		if (groupMember != nullptr && groupMember->isPlayerCreature()) {
			Zone* zone = groupMember->getZone();

			if (zone != nullptr && zone->getZoneCRC() == planetCRC) {
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

	for (int i = 0; i < groupMembersOnPlanet.size(); i++) {
		if (groupMembersOnPlanet.get(i) != nullptr) {
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

	for (int i = 0; i < groupMembersOnPlanet.size(); i++) {
		CreatureObject* groupMember = groupMembersOnPlanet.get(i);

		if (groupMember != nullptr) {
			SceneObject* datapad = groupMember->getSlottedObject("datapad");
			if (datapad == nullptr) {
				continue;
			}

			int numberOfMissionsForMember = 0;

			Locker clocker(groupMember, group);

			for (int k = 0; k < datapad->getContainerObjectsSize(); k++) {
				if (datapad->getContainerObject(k) != nullptr && datapad->getContainerObject(k)->isMissionObject()) {
					numberOfMissionsForMember++;
					Reference<MissionObject*> mission = datapad->getContainerObject(k).castTo<MissionObject*>();

					if (mission->getWaypointToMission() != nullptr && mission->getWaypointToMission()->getPlanetCRC() == planetCRC) {
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
	Reference<MissionObject*> nearestMission = nullptr;

	if (missionsOnPlanet.size() == 1) {
		nearestMission = missionsOnPlanet.get(0);
	} else {
		float shortestDistanceSoFar = std::numeric_limits<float>::max();

		for (int i = 0; i < missionsOnPlanet.size(); i++) {
			float disstanceToMission = calculateManhattanDistanceToMission(averageGroupMemberLocation, missionsOnPlanet.get(i));

			if (disstanceToMission < shortestDistanceSoFar) {
				shortestDistanceSoFar = disstanceToMission;
				nearestMission = missionsOnPlanet.get(i);
			}
		}
	}

	// If a mission was found, add the nearest mission waypoint for all members. Otherwise if a mission
	// was not found then remove the nearest mission waypoint for all members.
	for (int i = 0; i < groupMembersOnPlanet.size(); i++) {
		CreatureObject* groupMember = groupMembersOnPlanet.get(i);

		Locker clocker(groupMember, group);

		if (groupMember->getPlayerObject() != nullptr) {
			PlayerObject* ghost = groupMember->getPlayerObject();

			setPlayersNearestMissionForGroupWaypoint(ghost, nearestMission);
		}
	}
}

float UpdateNearestMissionForGroupTask::calculateManhattanDistanceToMission(const Vector3& position, MissionObject* mission) {
	// The Manhattan distance will give us a "good enough" value for comparing the relative distance
	// to two missions.  It can fail if two missions are very close to each other but that's fine for
	// the purposes of this waypoint.
	if (mission == nullptr || mission->getWaypointToMission() == nullptr) {
		return std::numeric_limits<float>::max();
	}

	return fabs(position.getX() - mission->getWaypointToMission()->getWorldPositionX())
		+ fabs(position.getY() - mission->getWaypointToMission()->getWorldPositionY());
}

void UpdateNearestMissionForGroupTask::setPlayersNearestMissionForGroupWaypoint(PlayerObject* ghost, MissionObject* nearestMissionForGroup) {
	if (ghost == nullptr) {
		return;
	}

	if (nearestMissionForGroup == nullptr) {
		ghost->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP, true);
	} else {
		Zone* zone = nearestMissionForGroup->getZone();
		uint32 crc = zone ? zone->getZoneCRC() : 0;

		ManagedReference<WaypointObject*> waypoint = ghost->getWaypointBySpecialType(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP);
		if (waypoint == nullptr) {
			ZoneServer* zoneServer = ghost->getZoneServer();
			waypoint = zoneServer->createObject(0xc456e788, 1).castTo<WaypointObject*>();
		}

		Locker locker(waypoint);

		waypoint->setCustomObjectName("@group:groupwaypoint", false); // Nearest mission for group
		waypoint->setSpecialTypeID(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP);
		waypoint->setPlanetCRC(crc);
		waypoint->setPosition(nearestMissionForGroup->getWaypointToMission()->getPositionX(), nearestMissionForGroup->getWaypointToMission()->getPositionZ(), nearestMissionForGroup->getWaypointToMission()->getPositionY());
		waypoint->setColor(WaypointObject::COLOR_YELLOW);
		waypoint->setActive(true);

		ghost->addWaypoint(waypoint, false);
	}
}