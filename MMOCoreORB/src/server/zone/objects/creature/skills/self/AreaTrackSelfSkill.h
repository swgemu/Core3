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

#ifndef AREATRACKSELFSKILL_H_
#define AREATRACKSELFSKILL_H_

#include "../SelfSkill.h"

class AreaTrackSelfSkill : public SelfSkill {
protected:
	String anim;
	int cooldownTime;
	String trackingBox1;
	String trackingBox2;
	String trackingBox3;
	String trackingBox4;
public:
	AreaTrackSelfSkill(const String& Name, const String& Anim, ZoneProcessServerImplementation* serv) : SelfSkill(Name, "", OTHER, serv) {
		anim = Anim;
		cooldownTime = 0;
		trackingBox1 = "outdoors_ranger_harvest_01";
		trackingBox2 = "outdoors_ranger_harvest_02";
		trackingBox3 = "outdoors_ranger_harvest_03";
		trackingBox4 = "outdoors_ranger_harvest_04";
	}

	void doSkill(CreatureObject* ranger, String& modifier) {
		if(ranger->isPlayer()) {
			Player* player = (Player*) ranger;
			SuiListBox* rangerWhatToTrack = new SuiListBox(player, SuiWindowType::RANGER_WHAT_TO_TRACK);

			rangerWhatToTrack->setPromptTitle("@skl_use:scan_type_t");
			rangerWhatToTrack->setPromptText("What do you want to track?");

			rangerWhatToTrack->addMenuItem("@cmd_n:areatrack_animal");

			if(player->hasSkillBox(trackingBox2))
				rangerWhatToTrack->addMenuItem("@cmd_n:areatrack_npc");

			if(player->hasSkillBox(trackingBox4))
				rangerWhatToTrack->addMenuItem("@cmd_n:areatrack_player");

			rangerWhatToTrack->setCancelButton(true, "");

			player->addSuiBox(rangerWhatToTrack);
			player->sendMessage(rangerWhatToTrack->generateMessage());
		}
	}

	void showTrackedObjects(CreatureObject* ranger, int type) {
		if(ranger->isPlayer()) {
			Player* tracker = (Player*) ranger;
			SuiListBox* rangerTrackResults = new SuiListBox(tracker, SuiWindowType::RANGER_WHAT_TO_TRACK);

			rangerTrackResults->setPromptTitle("@skl_use:scan_results_t");
			rangerTrackResults->setPromptText("The results of your search:\n\n");
			StringBuffer results;

			bool canGetDirection = tracker->hasSkillBox(trackingBox1);
			bool canGetDistance = tracker->hasSkillBox(trackingBox3);

			try {
				Zone* zone = tracker->getZone();
				zone->lock();

				for (int i = 0; i < tracker->inRangeObjectCount(); ++i) {
					SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) tracker->getInRangeObject(i))->_this);
					results.deleteAll();

					if (object->isNonPlayerCreature()) {
						CreatureObject* trackee = (CreatureObject*) object;

						if(type == 0 && trackee->isCreature()) {
							results << "@mob/creature_names:" << trackee->getTemplateName();

							if(trackee->isBaby())
								results << " (baby)";
							if(canGetDirection)
								results << " | " << getDirection(tracker, trackee);
							if(canGetDistance)
								results << " | " << getDistance(tracker, trackee);

							rangerTrackResults->addMenuItem(results.toString());
						} else if(type == 1 && trackee->isNPC()) {
							results << "@mob/creature_names:" << trackee->getTemplateName();

							if(canGetDirection)
								results << " | " + getDirection(tracker, trackee);
							if(canGetDistance)
								results << " | " + getDistance(tracker, trackee);

							rangerTrackResults->addMenuItem(results.toString());
						}
					} else if (type == 2 && object->isPlayer() && object != (SceneObject*)tracker) {
						Player* trackee = (Player*) object;
						results << trackee->getCharacterName().toString();

						if(canGetDirection)
							results << " | " + getDirection(tracker, trackee);
						if(canGetDistance)
							results << " | " + getDistance(tracker, trackee);

						rangerTrackResults->addMenuItem(results.toString());
					}
				}

				zone->unlock();
			} catch(...) {
				System::out << "Error in AreaTrackSelfSkill::doSkill\n";
				return;
			}

			tracker->sendMessage(rangerTrackResults->generateMessage());
			rangerTrackResults->finalize();

			tracker->addCooldown(skillName, cooldownTime);
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
				direction = "E";
			else if(directionAngleInDegrees >= 22.5 && directionAngleInDegrees <= 67.5)
				direction = "NE";
			else if(directionAngleInDegrees >= 67.5 && directionAngleInDegrees <= 112.5)
				direction = "N";
			else if(directionAngleInDegrees >= 112.5 && directionAngleInDegrees <= 157.5)
				direction = "NW";
			else if(directionAngleInDegrees >= 157.5 && directionAngleInDegrees <= 202.5)
				direction = "W";
			else if(directionAngleInDegrees >= 202.5 && directionAngleInDegrees <= 247.5)
				direction = "SW";
			else if(directionAngleInDegrees >= 247.5 && directionAngleInDegrees <= 292.5)
				direction = "S";
			else if(directionAngleInDegrees >= 292.5 && directionAngleInDegrees <= 337.5)
				direction = "SE";
			else
				direction = "Error: Report this to Link Please";
		} else {
			direction = "N";  // this is for tackees that have the same position as the tracker's position
		}

		return direction;
	}

	String getDistance(CreatureObject* tracker, CreatureObject* trackee) {
		float distance = tracker->getDistanceTo(trackee);

		StringBuffer strBuffer;
		strBuffer << distance << " meters";
		String result = strBuffer.toString();
		return result;
	}

	void doAnimations(CreatureObject* creature) {
	}

	virtual bool isUseful(CreatureObject* creature) {

		if(creature->isInCombat()) {
			creature->sendSystemMessage("jedi_spam", "not_while_in_combat"); // You cannot perform that action while in combat.
			return false;
		}

		if(creature->hasCooldownExpired(skillName)) {
			return true;
		} else {
			int timeRemaining = creature->getCooldownTimeRemaining(skillName);
			StringBuffer message;
			message << "You must wait " << timeRemaining << " seconds to perform Area Track.";
			creature->sendSystemMessage(message.toString());
			return false;
		}

		return true;
	}

	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

	void setCooldownTime(int valueInSeconds) {
		cooldownTime = valueInSeconds * 1000;
	}
};

#endif /*AREATRACKSELFSKILL_H_*/
