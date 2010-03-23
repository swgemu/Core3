/*
 * CreatureManagerImplementation.cpp
 *
 *  Created on: 24/02/2010
 *      Author: victor
 */

#include "CreatureManager.h"
#include "server/zone/ZoneServer.h"

CreatureObject* CreatureManagerImplementation::spawnCreature(uint32 templateCRC, float x, float y, uint64 parentID) {
	ManagedReference<SceneObject> object = server->createObject(templateCRC, 0);

	if (object == NULL) {
		StringBuffer errMsg;
		errMsg << "could not spawn creature... wrong template? 0x" << hex << templateCRC;

		error(errMsg.toString());

		return NULL;
	}

	if (!object->isCreatureObject()) {
		StringBuffer errMsg;
		errMsg << "server did not create a creature object wrong template? 0x" << hex << templateCRC;

		error(errMsg.toString());

		return NULL;
	}

	CreatureObject* creature = (CreatureObject*) object.get();

	SceneObject* cellParent = NULL;

	if (parentID != 0) {
		cellParent = server->getObject(parentID);

		if (cellParent != NULL && !cellParent->isCellObject()) {
			error("trying to set a parent that is not a cell to creature");
			cellParent = NULL;
		}
	}

	if (!createCreatureChildrenObjects(creature)) {
		StringBuffer errMsg;
		errMsg << "could not create children objects for creature... 0x" << templateCRC;
		error(errMsg.toString());

		return NULL;
	}

	if (cellParent != NULL) {
		cellParent->addObject(object, -1);
	}

	addCreatureToMap(creature);

	Locker _locker(creature);

	creature->initializePosition(x, 0, y);

	creature->insertToZone(zone);

	return creature;
}

bool CreatureManagerImplementation::createCreatureChildrenObjects(CreatureObject* creature) {
	uint32 defaultWeaponCRC = String("object/weapon/creature/creature_default_weapon.iff").hashCode();

	SceneObject* defaultWeapon = server->createObject(defaultWeaponCRC, 0);

	if (defaultWeapon == NULL) {
		error("could not create creature default weapon");

		return false;
	}

	creature->addObject(defaultWeapon, 4);

	return true;
}

