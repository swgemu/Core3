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

#include "ShipObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/ship/ShipObjectMessage1.h"
#include "server/zone/packets/ship/ShipObjectMessage3.h"
#include "server/zone/packets/ship/ShipObjectMessage4.h"
#include "server/zone/packets/ship/ShipObjectMessage6.h"
#include "server/zone/packets/tangible/TangibleObjectMessage8.h"
#include "server/zone/packets/tangible/TangibleObjectMessage9.h"

void ShipObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	//info("testing");
	TangibleObjectImplementation::sendTo(player, doClose);
}

void ShipObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();
}

uint16 ShipObjectImplementation::getUniqueID() {
	uint32 hash = UnsignedLong::hashCode(getObjectID());
	uint16 id = (uint16) (hash ^ (hash >> 16));

	//info("uniqueId: 0x" + String::hexvalueOf(id), true);

	return id;
}

void ShipObjectImplementation::sendBaselinesTo(SceneObject* player) {
	//info("sending ship baselines", true);

	BaseMessage* ship3 = new ShipObjectMessage3(_this.get());
	player->sendMessage(ship3);

	if (player->getParent().get() == _this.get() || getRootParent().get() == player) {
		BaseMessage* ship4 = new ShipObjectMessage4(_this.get());
		player->sendMessage(ship4);
	
		BaseMessage* ship1 = new ShipObjectMessage1(_this.get());
		player->sendMessage(ship1);
	}

	BaseMessage* ship6 = new ShipObjectMessage6(_this.get());
	player->sendMessage(ship6);
/*
	BaseMessage* ship8 = new TangibleObjectMessage8(_this);
	player->sendMessage(ship8);

	BaseMessage* ship9 = new TangibleObjectMessage9(_this);
	player->sendMessage(ship9);*/
}
