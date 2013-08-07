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

#ifndef GMREVIVECOMMAND_H_
#define GMREVIVECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GmReviveCommand : public QueueCommand {
public:

	GmReviveCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		try {
			StringTokenizer args(arguments.toString());
			ManagedReference<CreatureObject*> player = NULL;

			ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(creature->getTargetID());

			PlayerManager* pm = server->getZoneServer()->getPlayerManager();

			if (!args.hasMoreTokens()) { // No arguments passed

				if (object != NULL && object->isPlayerCreature()) { // Target is a player, rez target
					player = cast<CreatureObject*>( object.get());
					revivePlayer(creature, player);

				} else if (object == NULL) { // No target, rez self
					player = creature;
					revivePlayer(creature, player);

				} else { // Target is not a player
					creature->sendSystemMessage("Syntax: /gmrevive [buff] [name]|[area [range]]");
					return INVALIDTARGET;
				}

			} else { // Has arguments

				String firstArg;
				String firstName = "";
				bool buff = false;
				args.getStringToken(firstArg);

				if (firstArg.toLowerCase() == "buff") { // First argument is buff, get second argument
					buff = true;
					if (args.hasMoreTokens())
						args.getStringToken(firstName);

				} else { // First argument is not buff, must be a name or area
					firstName = firstArg;
				}

				if (firstName != "") { // There's an argument for a name or area

					if (firstName.toLowerCase() == "area") { // Area argument found, check for range argument
						int range = 32;

						if (args.hasMoreTokens()) // Must be range
							range = args.getIntToken();

						if (range > 50) // We don't want the range to get crazy, so hard caps of 5-50
							range = 50;
						else if (range < 5)
							range = 5;

						SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
						Zone* zone = creature->getZone();

						if (creature->getCloseObjects() == NULL) {
							zone->getInRangeObjects(creature->getPositionX(), creature->getPositionY(), range, &closeObjects, true);
						} else {
							CloseObjectsVector* closeVector = (CloseObjectsVector*) creature->getCloseObjects();
							closeVector->safeCopyTo(closeObjects);
						}

						for (int i = 0; i < closeObjects.size(); ++i) {
							SceneObject* sceneObject = cast<SceneObject*>(closeObjects.get(i).get());

							if (sceneObject->isPlayerCreature() && creature->isInRange(sceneObject, range)) {
								ManagedReference<CreatureObject*> playerObject = cast<CreatureObject*>(sceneObject);

								if (playerObject != NULL) {
									if (buff) {
										Locker clocker(playerObject, creature);
										pm->enhanceCharacter(playerObject);

									} else {
										revivePlayer(creature, playerObject);
									}
								}
							}
						}

					} else { // Not area
						player = server->getZoneServer()->getChatManager()->getPlayer(firstName);

						if (player != NULL) {
							if (buff) {
								Locker clocker(player, creature);
								pm->enhanceCharacter(player);

							} else {
								revivePlayer(creature, player);
							}
						}
					}

				} else if (buff) {  // Buff was the only argument

					if (object != NULL && object->isPlayerCreature()) { // Target is a player, buff target
						player = cast<CreatureObject*>( object.get());
						Locker clocker(player, creature);
						pm->enhanceCharacter(player);

					} else if (object == NULL) { // No target, buff self
						pm->enhanceCharacter(creature);

					} else { // Target is not a player
						creature->sendSystemMessage("Syntax: /gmrevive [buff] [name]|[area [range]]");
						return INVALIDTARGET;
					}

				} else { // Shouldn't ever end up here
					creature->sendSystemMessage("Syntax: /gmrevive [buff] [name]|[area [range]]");
					return INVALIDTARGET;
				}
			}

		} catch (Exception& e) {
			creature->sendSystemMessage("Syntax: /gmrevive [buff] [name]|[area [range]]");
		}

		return SUCCESS;
	}

	void revivePlayer(CreatureObject* creature, CreatureObject* player) {
		Locker clocker(player, creature);

		player->healDamage(creature, CreatureAttribute::HEALTH, 5000);
		player->healDamage(creature, CreatureAttribute::ACTION, 5000);
		player->healDamage(creature, CreatureAttribute::MIND, 5000);

		for (int i = 0; i < 9; ++i) {
			player->setWounds(i, 0);
		}

		player->setShockWounds(0);

		player->setPosture(CreaturePosture::UPRIGHT);

		player->broadcastPvpStatusBitmask();

		player->sendSystemMessage("You have been restored.");

		creature->sendSystemMessage(player->getFirstName() + " has been restored.");
	}
};

#endif //GMREVIVECOMMAND_H_
