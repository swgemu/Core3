/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GOTOCOMMAND_H_
#define GOTOCOMMAND_H_

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/sui/callbacks/GotoSuiCallback.h"

class GotoCommand : public QueueCommand {
public:
	GotoCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Zone* zone = creature->getZone();

		if (zone == NULL)
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		String searchTerm = arguments.toString().toLowerCase();

		if (searchTerm != "") {
			try {
				int numWaypoints = ghost->getWaypointListSize();

				if(numWaypoints == 0) {
					creature->sendSystemMessage("You don't have any waypoints to search!");
					return SUCCESS;
				}

				int allWaypoints = 0;

				if (searchTerm == "?")
					allWaypoints = 1;

				VectorMap<float, ManagedReference<WaypointObject*> > waypointsFound;

				waypointsFound.setAllowDuplicateInsertPlan();

				for (int i = 0; i < numWaypoints; i++) {
					WaypointObject* wp = ghost->getWaypoint(i);

					if (wp == NULL)
						continue;

					Locker crlocker(wp, creature);

					float distance = calculateWaypointManhattanDistance(creature, wp);

					String name = wp->getDisplayedName();

					if (!allWaypoints && !name.toLowerCase().contains(searchTerm))
						continue;

					waypointsFound.put(distance, wp);
				}

				if (waypointsFound.size() < 1) {
					creature->sendSystemMessage("No waypoints were found that matched that filter.");
					return SUCCESS;
				}

				// If it only matches a single one just jump to it.. Nice for /goto HOME etc..
				if (waypointsFound.size() == 1) {
					WaypointObject* wp = waypointsFound.get(0);

					Locker crlocker(wp, creature);

					String planet = getPlanetNameByCRC(wp->getPlanetCRC());

					if (planet == "")
					    return SUCCESS;

					creature->sendSystemMessage("Found only one match, automatically going to " + wp->getDisplayedName() + ".");

					creature->switchZone(planet, wp->getPositionX(), wp->getPositionZ(), wp->getPositionY(), 0);

					return SUCCESS;
				}

				ManagedReference<SuiListBox*> gotoListBox = new SuiListBox(creature, SuiWindowType::GOTO_LIST, SuiListBox::HANDLETWOBUTTON);
				gotoListBox->setCallback(new GotoSuiCallback(server->getZoneServer()));
				gotoListBox->setPromptTitle("Goto Waypoint");
				gotoListBox->setPromptText("Here are your waypoints that match your search:");
				gotoListBox->setCancelButton(true, "");
				gotoListBox->setOkButton(true, "@go");

				for (int i = 0; i < waypointsFound.size(); i++) {
					WaypointObject* wp = waypointsFound.get(i);

					String planet = getPlanetNameByCRC(wp->getPlanetCRC());

					if(planet == "")
					    continue;

					String name = wp->getDisplayedName();

					StringBuffer menuText;

					menuText << name
					    << " (" << String::valueOf(wp->getWorldPositionX()) << ", " << String::valueOf(wp->getWorldPositionY())
					    << " on " << planet << ")";

					gotoListBox->addMenuItem(menuText.toString(), wp->getObjectID());
				}

				ghost->addSuiBox(gotoListBox);

				creature->sendMessage(gotoListBox->generateMessage());

				return SUCCESS;
			} catch (Exception& e) {
				creature->info(creature->getDisplayedName() + " /goto unexpected exception: " + e.getMessage(), true);
			}
		}

		creature->sendSystemMessage("SYNTAX: /goto {waypointSearchToken} or '?' for all");

		return SUCCESS;
	}

private:
	String getPlanetNameByCRC(uint32 planetCRC) const {
		// TODO Make a quick lookup map for planetCRC to name
		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == NULL || zoneServer->isServerLoading())
			return "";

		for (int i = 0; i < zoneServer->getZoneCount(); ++i) {
			Zone* zone = zoneServer->getZone(i);

			if (zone == NULL)
				continue;

			if (zone->getZoneName().hashCode() == planetCRC)
				return(zone->getZoneName());
		}

		return "";
	}

	float calculateWaypointManhattanDistance(CreatureObject* creature, WaypointObject* wp) const {
		if(creature == NULL || wp == NULL)
			return std::numeric_limits<float>::max();

		Zone* creatureZone = creature->getZone();

		if (creatureZone == NULL)
			return std::numeric_limits<float>::max();

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == NULL || zoneServer->isServerLoading())
			return std::numeric_limits<float>::max();

		uint32 planetCRC = wp->getPlanetCRC();

		float planetOffset = 0;

		// Player's planet sorts to top
		if (creatureZone->getZoneName().hashCode() != planetCRC) {
			for (int i = 0; i < zoneServer->getZoneCount(); ++i) {
				planetOffset += 100000;

				Zone* zone = zoneServer->getZone(i);

				if (zone == NULL)
					continue;

				if (zone->getZoneName().hashCode() == planetCRC)
					break;
			}
		}

		Vector3 origin = creature->getWorldPosition();

		return planetOffset + fabs(origin.getX() - wp->getWorldPositionX()) + fabs(origin.getY() - wp->getWorldPositionY());
	}
};

#endif //GOTOCOMMAND_H_
