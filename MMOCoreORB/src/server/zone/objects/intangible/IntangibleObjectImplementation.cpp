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

#include "IntangibleObjectImplementation.h"
#include "IntangibleObject.h"

#include "../../packets.h"
#include "../../objects.h"

#include "../../ZoneClient.h"


IntangibleObjectImplementation::IntangibleObjectImplementation(SceneObject* container, uint32 objCRC, uint64 id) : IntangibleObjectServant(id, INTANGIBLE) {
	objectType = SceneObjectImplementation::INTANGIBLE;
	objectCRC = objCRC;

	linkType = 0xFFFFFFFF;
	parent = container;

	worldObject = NULL;

	status = 0;
}

IntangibleObjectImplementation::~IntangibleObjectImplementation() {
	if (worldObject != NULL) {
		worldObject->finalize();
		worldObject = NULL;
	}
}

void IntangibleObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (parent != NULL)
		client->sendMessage(link(parent));

	IntangibleObjectMessage3* itno3 = new IntangibleObjectMessage3(_this);
	client->sendMessage(itno3);

	IntangibleObjectMessage6* itno6 = new IntangibleObjectMessage6(_this);
	client->sendMessage(itno6);

	if (doClose)
		SceneObjectImplementation::close(client);
}

void IntangibleObjectImplementation::sendDestroyTo(Player* player) {
	SceneObjectImplementation::destroy(player->getClient());
}

void IntangibleObjectImplementation::updateStatus(uint32 stat) {
	status = stat;

	SceneObject* object = parent->getParent();
	if (object == NULL)
		return;

	if (!object->isPlayer())
		return;

	Player* player = (Player*) object;

	IntangibleObjectDeltaMessage3* itno3 = new IntangibleObjectDeltaMessage3(_this);
	itno3->updateStatus(status);
	itno3->close();

	player->sendMessage(itno3);
}
