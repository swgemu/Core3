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

#include "CreatureObjectImplementation.h"

#include "../../../packets/creature/CreatureObjectDeltaMessage6.h"

CreatureObjectImplementation::CreatureObjectImplementation(uint64 objectid, int type)
		: CreatureObjectServant(objectid, type) {
	complexity = 10.0f;
	volume = 0x0085E5CA; //TODO: Why is it this value?

	height = 1.0f;
	pvpStatusBitmask = 0x10;
	factionRank = 0;

	speed = DEFAULT_SPEED;
	turnRadius = 1.0f;
	terrainNegotiation = 1.0f;
	acceleration = DEFAULT_ACCEL;
	deceleration = 1.0f;

	attributes[CreatureAttribute::HEALTH] = 1000;
	attributes[CreatureAttribute::STRENGTH] = 1000;
	attributes[CreatureAttribute::CONSTITUTION] = 1000;
	attributes[CreatureAttribute::ACTION] = 1000;
	attributes[CreatureAttribute::QUICKNESS] = 1000;
	attributes[CreatureAttribute::STAMINA] = 1000;
	attributes[CreatureAttribute::MIND] = 1000;
	attributes[CreatureAttribute::FOCUS] = 1000;
	attributes[CreatureAttribute::WILLPOWER] = 1000;
}

CreatureObjectImplementation::~CreatureObjectImplementation() {
}

/**
 * Updates the creatures current target and updates all nearby players.
 * \param targetid The objectid of the new target.
 */
void CreatureObjectImplementation::updateTargetObject(uint64 targetid, bool updateclients) {
	if (zone == NULL)
		return;

	if (targetObject != NULL && targetid == targetObject->getObjectID())
		return;

	SceneObject* targetobj = zone->lookupObject(targetid);

	if (targetobj == NULL)
		return;

	info("Updating target.");

	targetObject = targetobj;

	if (updateclients) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateTargetID(targetid);
		dcreo6->close();

		broadcastMessage(dcreo6);
	}
}

void CreatureObjectImplementation::updateTargetObject(SceneObject* target, bool updateclients) {
	if (target == NULL || targetObject == target)
		return;

	info("Updating target.");

	targetObject = target;

	if (updateclients) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateTargetID(target->getObjectID());
		dcreo6->close();

		broadcastMessage(dcreo6);
	}
}
