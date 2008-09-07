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

#include "../../../../packets.h"
#include "../../../../objects.h"
#include "Component.h"
#include "ComponentImplementation.h"
#include "../../../../ZoneClient.h"
 
ComponentImplementation::ComponentImplementation(uint64 object_id, uint32 tempCRC, 
		const unicode& n, const string& tempn) : ComponentServant(object_id, tempCRC, n, tempn, 
				COMPONENT) {
	objectCRC = tempCRC;
	templateTypeName = "craft_weapon_ingredients_n";
	templateName = tempn;
	name = n;
	init();
}
 
ComponentImplementation::ComponentImplementation(CreatureObject* creature, uint32 tempCRC, 
		const unicode& n, const string& tempn) : ComponentServant(creature, tempCRC, n, tempn, 
				COMPONENT) {
	objectCRC = tempCRC;
	templateTypeName = "craft_weapon_ingredients_n";
	templateName = tempn;
	name = n;
	init();
}


ComponentImplementation::~ComponentImplementation(){

}

void ComponentImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	omr->finish();

	player->sendMessage(omr);
}

void ComponentImplementation::init() {

	objectSubType = TangibleObjectImplementation::COMPONENT;

}

int ComponentImplementation::useObject(Player* player) {

	return 0;
}

void ComponentImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (container != NULL)
		link(client, container);

	BaseMessage* fcty3 = new FactoryCrateObjectMessage3((TangibleObject*) _this);
	client->sendMessage(fcty3);

	BaseMessage* fcty6 = new FactoryCrateObjectMessage6((TangibleObject*) _this);
	client->sendMessage(fcty6);

	if (pvpStatusBitmask != 0) {
		UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
		client->sendMessage(msg);
	}

	if (doClose)
		SceneObjectImplementation::close(client);

}

void ComponentImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;
	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage(_this);
	alm->insertAttribute("volume", "1");

	player->sendMessage(alm);
}

Component* ComponentImplementation::cloneComponent(Component* oldComp, uint64 oid) {

	if (oldComp != NULL) {

		uint32 newCRC = _this->getObjectCRC();
		unicode newName = _this->getName();
		string newTemplate = _this->getTemplateName();

		return new Component(oid, newCRC, newName, newTemplate);
	} else {
		return NULL;
	}

}



