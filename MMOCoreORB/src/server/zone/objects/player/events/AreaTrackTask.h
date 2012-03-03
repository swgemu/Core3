/*
 Copyright (C) 2007 <SWGEmu>

 This File is part of Core3.

 This program is free software; you can redistribute
 it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software
 Foundation; either version 3 of the License,
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

/**
 * AreaTrackTask.h
 *
 *  Created: Sat Feb 5
 *   Author: Kyle
 *
 */

#ifndef AREATRACKTASK_H_
#define AREATRACKTASK_H_

#include "server/zone/packets/player/LogoutMessage.h"

class AreaTrackTask: public Task {
	ManagedReference<CreatureObject*> player;
	int type;
	Coordinate initialPosition;

public:
	AreaTrackTask(CreatureObject* cr, int index) {
		player = cr;
		type = index;
		initialPosition.setPosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
	}

	void run() {
		try {

			player->removePendingTask("areatrack");

			if(!player->isPlayerCreature())
				return;

			SuiListBox* rangerTrackResults = new SuiListBox(player, SuiWindowType::RANGER_TRACK_RESULTS);

			rangerTrackResults->setPromptTitle("@skl_use:scan_results_t");
			rangerTrackResults->setPromptText("@skl_use:scan_results_d");
			StringBuffer results;

			bool canGetDirection = player->hasSkill("outdoors_ranger_harvest_01");
		    bool canGetDistance = player->hasSkill("outdoors_ranger_harvest_03");

			Zone* zone = player->getZone();
			if(zone == NULL)
				return;

			SortedVector<ManagedReference<QuadTreeEntry*> > objects(512, 512);
			zone->getInRangeObjects(player->getPositionX(), player->getPositionY(), 512, &objects, true);

			if(player->getDistanceTo(&initialPosition) < 2 && !player->isInCombat()) {

				for (int i = 0; i < objects.size(); ++i) {
					SceneObject* object = cast<SceneObject*>(objects.get(i).get());					results.deleteAll();

					if(object == player)
						continue;

					if (object->isCreatureObject()) {
						CreatureObject* creature = cast<CreatureObject*>(object);
						if(creature == NULL)
							continue;

						if(creature->isPlayerCreature()) {
							PlayerObject* ghost = cast<PlayerObject*>(creature->getSlottedObject("ghost"));
							if(ghost != NULL) {
								if(ghost->isInvisible())
									continue;
							}
						}

						if(type == 0) {
							if(!creature->isCreature())
								continue;
						} else if(type == 1) {
							if(!creature->isNonPlayerCreatureObject())
								continue;
						} else if(type == 2) {
							if(!creature->isPlayerCreature())
								continue;
						} else {
							continue;
						}


						results << creature->getDisplayedName();

						String direction = "", distance = "";

						if(canGetDirection)
							direction = getDirection(player, creature);
						if(canGetDistance)
							distance = getDistance(player, creature);

						if(!distance.isEmpty() || !direction.isEmpty()) {
							results << " (" << direction << distance << ")";
						}

						rangerTrackResults->addMenuItem(results.toString());
					}
				}
			} else {
				rangerTrackResults->addMenuItem("@skl_use:sys_scan_moved");
			}

			if(player->isInCombat()) {
				rangerTrackResults->addMenuItem("@skl_use:sys_scan_combat");
			}

			if(rangerTrackResults->getMenuSize() == 0)
				rangerTrackResults->addMenuItem("@skl_use:sys_scan_nothing");

			player->sendMessage(rangerTrackResults->generateMessage());

		} catch (Exception& e) {
			player->error("unreported exception caught in AreaTrackTask::run()");
		}
	}

	String getDirection(CreatureObject* tracker, CreatureObject* trackee) {
		String direction;
		float trackerX = tracker->getPositionX();
		float trackerY = tracker->getPositionY();
		float trackeeX = trackee->getPositionX();
		float trackeeY = trackee->getPositionY();

		// transform points so the origin is the tracker's position
		float transformedX = trackeeX - trackerX;
		float transformedY = trackeeY - trackerY;

		// normalize the transformed points which will give us points on the unit circle
		// in the direction of the trackee
		float length = sqrt(transformedX * transformedX + transformedY * transformedY);
		if(length > 0) {
			float pointOnUnitCircleX = transformedX / length;
			float pointOnUnitCircleY = transformedY / length;

			// inverse cos of the pointOnUnitCircleX will give the angle
			float directionAngleInDegrees = ((float)acos(pointOnUnitCircleX) * 180) / M_PI;

			// if the point is in the 3rd or 4th quadrant, 360 - directionAngleInDegrees will give the correct angle value
			// with the origin at (1,0) on the unit circle
			if(pointOnUnitCircleY < 0)
				directionAngleInDegrees = 360 - directionAngleInDegrees;

			if((directionAngleInDegrees >= 0 && directionAngleInDegrees <= 22.5) || (directionAngleInDegrees >= 337.5 && directionAngleInDegrees <= 360))
				direction = "east";
			else if(directionAngleInDegrees >= 22.5 && directionAngleInDegrees <= 67.5)
				direction = "northeast";
			else if(directionAngleInDegrees >= 67.5 && directionAngleInDegrees <= 112.5)
				direction = "north";
			else if(directionAngleInDegrees >= 112.5 && directionAngleInDegrees <= 157.5)
				direction = "northwest";
			else if(directionAngleInDegrees >= 157.5 && directionAngleInDegrees <= 202.5)
				direction = "west";
			else if(directionAngleInDegrees >= 202.5 && directionAngleInDegrees <= 247.5)
				direction = "southwest";
			else if(directionAngleInDegrees >= 247.5 && directionAngleInDegrees <= 292.5)
				direction = "south";
			else if(directionAngleInDegrees >= 292.5 && directionAngleInDegrees <= 337.5)
				direction = "southeast";
			else
				direction = "Error: Report this to Kyle Please";
		} else {
			direction = "north";  // this is for trackees that have the same position as the tracker's position
		}

		return direction;
	}

	String getDistance(CreatureObject* tracker, CreatureObject* trackee) {
		int distance = (int)tracker->getDistanceTo(trackee);

		StringBuffer strBuffer;
		strBuffer << " " << distance << "m";
		String result = strBuffer.toString();
		return result;
	}
};

#endif /* AREATRACKTASK_H_ */
