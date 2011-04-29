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

#ifndef FINDCOMMAND_H_
#define FINDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/Zone.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/planet/MapLocationType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"

#include "server/zone/objects/creature/commands/sui/FindCommandSuiCallback.h"

class FindCommand: public QueueCommand {

public:

	FindCommand(const String& name, ZoneProcessServer* server) :
		QueueCommand(name, server) {

	}

	void clearWaypoint(PlayerCreature* player) {
		PlayerObject* pl = player->getPlayerObject();

		WaypointList* waypointlist = pl->getWaypointList();
		uint64 wpid = waypointlist->getWaypointBySpecialType(
				WaypointObject::SPECIALTYPE_FIND);

		if (wpid != 0) {
			pl->removeWaypoint(wpid, true);

		}

	}

	static int addWaypoint(PlayerCreature* player, float x, float y, const String& name) {
		PlayerObject* ghost = player->getPlayerObject();

		Zone* zone = player->getZone();
		String planet = zone->getZoneName();
		StringIdChatParameter msg;

		ManagedReference<WaypointObject*> wpt =
				(WaypointObject*) player->getZoneServer()->createObject(0xc456e788, 1);

		wpt->setPlanetCRC(planet.hashCode());
		wpt->setPosition(x, 0, y);
		wpt->setCustomName(name);
		wpt->setActive(true);
		wpt->setSpecialTypeID(WaypointObject::SPECIALTYPE_FIND);
		msg.setStringId("@base_player:prose_find_set"); // An active waypoint has be set to the nearest '%TO'.
		msg.setTO(name);

		ghost->addWaypoint(wpt, true, true);

		player->sendSystemMessage(msg);

		return SUCCESS;
	}

	static int findPlanetaryObject(PlayerCreature* player, String& maplocationtype) {
		Zone* zone = player->getZone();
		ManagedReference<SceneObject*> object = zone->getNearestPlanetaryObject(player, maplocationtype);

		if (object == NULL) {
			player->sendSystemMessage("@find_display:no_registered_locs"); // There currently are not registered map locations on this planet.
			return GENERALERROR;
		}

		ActiveArea* region = object->getActiveRegion();
		String regFullName = "";

		if (region != NULL) {
			StringId* regionName = region->getObjectName();
			regFullName = region->getCustomObjectName().toString();

			if (regFullName.isEmpty())
				regionName->getFullPath(regFullName);

		}

		String objFullName = "@map_loc_cat_n:" + maplocationtype;

		StringIdManager* stringManager = StringIdManager::instance();

		String regClientString = stringManager->getStringId(regFullName.hashCode());
		String objClientString = stringManager->getStringId(objFullName.hashCode());

		if (regClientString.isEmpty()) {
			regClientString = object->getZone()->getZoneName();
			regClientString[0] = toupper(regClientString[0]);
		}

		String wptName = regClientString + " (" + objClientString + ")"; // Region (BuildingType)

		float objX, objY;
		objX = object->getWorldPositionX();
		objY = object->getWorldPositionY();

		addWaypoint(player, objX, objY, wptName);

		return SUCCESS;
	}

	void createOptions(PlayerCreature* player) {
		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::COMMAND_FIND, 2);
		box->setCallback(new FindCommandSuiCallback(server->getZoneServer()));
		box->setPromptTitle("@base_player:find_title"); // /Find Category Selector
		box->setPromptText("@base_player:find_prompt"); // Select a category of planetary map locations to search for.
		box->setCancelButton(true, "@cancel");
		box->addMenuItem("@find_display:cantina");
		box->addMenuItem("@find_display:capitol");
		box->addMenuItem("@find_display:city");
		box->addMenuItem("@find_display:cloningfacility");
		box->addMenuItem("@find_display:guild_combat");
		box->addMenuItem("@find_display:guild_commerce");
		box->addMenuItem("@find_display:guild_theater");
		box->addMenuItem("@find_display:guild_university");
		box->addMenuItem("@find_display:salon");
		box->addMenuItem("@find_display:hotel");
		box->addMenuItem("@find_display:medicalcenter");
		box->addMenuItem("@find_display:garage");
		box->addMenuItem("@find_display:shuttleport");
		box->addMenuItem("@find_display:starport");
		box->addMenuItem("@find_display:vendor_junk");
		box->addMenuItem("@find_display:terminal_bank");
		box->addMenuItem("@find_display:terminal_bazaar");
		box->addMenuItem("@find_display:terminal_mission");
		box->addMenuItem("@find_display:trainer_brawler");
		box->addMenuItem("@find_display:trainer_artisan");
		box->addMenuItem("@find_display:trainer_scout");
		box->addMenuItem("@find_display:trainer_marksman");
		box->addMenuItem("@find_display:trainer_entertainer");
		box->addMenuItem("@find_display:trainer_medic");

		player->addSuiBox(box);
		player->sendMessage(box->generateMessage());
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		try {

			PlayerCreature* player = (PlayerCreature*) creature;
			StringTokenizer args(arguments.toString());
			String location;

			if (args.hasMoreTokens()) {
				args.getStringToken(location);
				location = location.toLowerCase();

				if (location == "clear") {
					clearWaypoint(player);
					return SUCCESS;
				}

			} else {
				if (!player->hasSuiBoxWindowType(SuiWindowType::COMMAND_FIND)) {
					createOptions(player);
					return SUCCESS;
				}
			}


			String mapLocType = location;

			if (!mapLocType.isEmpty()) {
				findPlanetaryObject(player, mapLocType);

			} else {
				StringIdChatParameter msg;
				msg.setStringId("@base_player:prose_find_unknown_arg"); // /Find was unable to parse a category for '%TO'.
				msg.setTO(location);

				player->sendSystemMessage(msg);

			}

		} catch (Exception& e) {
			creature->sendSystemMessage("@base_player:find_general_error"); // /Find was unable to complete your request. Please try again.

		}

		return SUCCESS;
	}

};

#endif //FINDCOMMAND_H_
