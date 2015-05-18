/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

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
		Locker locker(player);

		try {

			player->removePendingTask("areatrack");

			if(!player->isPlayerCreature())
				return;

			if (player->getDistanceTo(&initialPosition) > 1) {
				player->sendSystemMessage("@skl_use:sys_scan_moved"); // Your attempt to gather information has been disrupted by moving around too much.
				return;
			}

			if (player->isInCombat()) {
				player->sendSystemMessage("@skl_use:sys_scan_combat"); // Your attempt to gather information has been disrupted by combat!
				return;
			}

			int maxType = 0;
			if (player->hasSkill("outdoors_ranger_harvest_04")) {
				maxType = 2;
			} else if (player->hasSkill("outdoors_ranger_harvest_02")) {
				maxType = 1;
			}

			if (type > maxType) {
				return;
			}

			ManagedReference<SuiListBox*> rangerTrackResults = new SuiListBox(player, SuiWindowType::RANGER_TRACK_RESULTS);

			rangerTrackResults->setPromptTitle("@skl_use:scan_results_t"); // Area Track Results
			rangerTrackResults->setPromptText("@skl_use:scan_results_d"); // You have examined the tracks and clues in the area for information about what kinds of creatures might be nearby. This is what you have determined.
			StringBuffer results;

			bool canGetDirection = player->hasSkill("outdoors_ranger_harvest_01");
		    bool canGetDistance = player->hasSkill("outdoors_ranger_harvest_03");

			Zone* zone = player->getZone();
			if(zone == NULL)
				return;

			SortedVector<ManagedReference<QuadTreeEntry*> > objects(512, 512);
			zone->getInRangeObjects(player->getPositionX(), player->getPositionY(), 512, &objects, true);

			for (int i = 0; i < objects.size(); ++i) {
				SceneObject* object = cast<SceneObject*>(objects.get(i).get());
				results.deleteAll();

				if(object == player || !object->isCreatureObject()) {
					continue;
				}

				CreatureObject* creature = cast<CreatureObject*>(object);
				if(creature == NULL || creature->isInvisible())
					continue;

				if(type == 0) {
					if(!creature->isCreature())
						continue;
					if (creature->isDroidSpecies() || creature->isWalkerSpecies())
						continue;
				} else if(type == 1) {
					if(!creature->isNonPlayerCreatureObject())
						continue;
					if(creature->isVendor()||creature->isJunkDealer())
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

			if(rangerTrackResults->getMenuSize() == 0) {
				player->sendSystemMessage("@skl_use:sys_scan_nothing"); // You aren't able to determine anything from the tracks in the area.
			} else {
				player->sendMessage(rangerTrackResults->generateMessage());
			}

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
