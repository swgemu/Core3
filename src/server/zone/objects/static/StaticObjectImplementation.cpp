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

#include "../../ZoneClient.h"
#include "../creature/CreatureObject.h"

#include "../player/Player.h"
#include "../scene/SceneObjectImplementation.h"

#include "../../Zone.h"

#include "../../packets.h"

#include "StaticObjectImplementation.h"

#include "../building/BuildingObject.h"
#include "../building/cell/CellObject.h"


StaticObjectImplementation::StaticObjectImplementation(uint64 oid, int tp)
		: StaticObjectServant(oid, STATIC) {
	initialize();
}

void StaticObjectImplementation::initialize() {
	zone = NULL;

	objectType = SceneObjectImplementation::STATIC;
}

void StaticObjectImplementation::insertToZone(Zone* zone) {
	StaticObjectImplementation::zone = zone;

	try {
		zone->lock();

		zone->registerObject((StaticObject*) _this);

		zone->insert(this);
		zone->inRange(this, 128);

		zone->unlock();
	} catch (...) {
		cout << "exception StaticObject::insertToZone(Zone* zone)\n";

		zone->unlock();
	}
}

void StaticObjectImplementation::removeFromZone() {
	if (zone == NULL)
		return;

	try {
		zone->lock();

    	for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);

			if (obj != this)
				obj->removeInRangeObject(this);
		}

		removeInRangeObjects();

		zone->remove(this);
		zone->deleteObject(objectID);

		zone->unlock();

		zone = NULL;
	} catch (...) {
		cout << "exception StaticObject::removeFromZone(bool doLock)\n";

		zone->unlock();
	}
}

void StaticObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	BaseMessage* stao3 = new StaticObjectMessage3((StaticObject*) _this);
	client->sendMessage(stao3);

	BaseMessage* stao6 = new StaticObjectMessage6((StaticObject*) _this);
	client->sendMessage(stao6);

	if (doClose)
		SceneObjectImplementation::close(client);

}

void StaticObjectImplementation::sendDestroyTo(Player* player) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	destroy(client);
}

void StaticObjectImplementation::close(Player* player) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::close(client);
}
