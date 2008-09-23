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

#include "MountCreatureImplementation.h"
#include "MountCreature.h"

#include "../Creature.h"
#include "../CreatureImplementation.h"

#include "../../player/Player.h"

#include "../../intangible/IntangibleObject.h"
#include "../../intangible/IntangibleObjectImplementation.h"

#include "../../../packets.h"
#include "../../../packets/creature/CreatureObjectMessage3.h"

#include "../../../ZoneClientSession.h"

MountCreatureImplementation::MountCreatureImplementation(CreatureObject* linkCreature, const string& name,
		const string& stf, uint32 itnocrc, uint32 objCRC, uint64 oid) : MountCreatureServant(oid) {
	creatureLinkID = linkCreature->getObjectID();

	linkedCreature = linkCreature;

	mountType = 0;

	stfName = stf;
	speciesName = name;

	objectCRC = objCRC;

	setType(CreatureImplementation::MOUNT);

	creatureBitmask = 0x1080;
	pvpStatusBitmask = 0;

	speed = 21.9f;
	acceleration = 10.95f;

	conditionDamage = 0;
	maxCondition = 20000;

	itno = NULL;
	itnoCRC = itnocrc;

	instantMount = false;

	stringstream loggingname;
	loggingname << "Mount = 0x" << oid;
	setLoggingName(loggingname.str());

	setLogging(false);
	setGlobalLogging(true);
}

void MountCreatureImplementation::addToDatapad() {
	if (linkedCreature == NULL || !linkedCreature->isPlayer())
		return;

	Player* linkedPlayer = (Player*)linkedCreature;

	itno = new IntangibleObject((SceneObject*) linkedPlayer->getDatapad(),
			itnoCRC, linkedCreature->getNewItemID());

	itno->setName(speciesName);
	itno->setDetailName(stfName);
	itno->setWorldObject(_this);

	linkedPlayer->addDatapadItem((SceneObject*) itno);
}

void MountCreatureImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	create(client);

	BaseMessage* creo3 = new CreatureObjectMessage3(_this);
	client->sendMessage(creo3);

	BaseMessage* creo6 = new CreatureObjectMessage6(_this);
	client->sendMessage(creo6);

	sendFactionStatusTo(player);

	if (isRidingCreature()) {
		linkedCreature->sendTo(player);
		linkedCreature->sendItemsTo(player);
	}

	if (doClose)
		close(client);
}

void MountCreatureImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if (player->getMount() == _this) {
		omr->addRadialItem(0, 205, 1, "@pet/pet_menu:menu_enter_exit");
		omr->addRadialItem(0, 61, 3);
	}

	omr->finish();

	player->sendMessage(omr);
}

void MountCreatureImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage(_this);

	CreatureObject* owner = getLinkedCreature();
	if (owner != NULL) {
		unicode name = unicode("");
		name = owner->getCharacterName();
		string strname = name.c_str();

		alm->insertAttribute("@obj_attr_n:crystal_owner", strname); //Owner: Name
	}

	player->sendMessage(alm);
}

void MountCreatureImplementation::call() {
	if (isInQuadTree())
		return;

	try {
		linkedCreature->wlock(_this);

		if (linkedCreature->getParent() != NULL) {
			linkedCreature->unlock();
			return;
		}


		if (linkedCreature->getMount() != NULL) {
			linkedCreature->unlock();
			return;
		}

		if (linkedCreature->isInCombat()) {
			linkedCreature->unlock();
			return;
		}

		// Jet Pack
		if(isJetpack()) {
			//initializePosition(linkedCreature->getPositionX(), linkedCreature->getPositionZ() + 4, linkedCreature->getPositionY());
			setAppearanceAttribute("index_hover_height", 40); // 32 = 9m, 64 = 12m
			//setHeight(4.0f);
		}
		//else
			initializePosition(linkedCreature->getPositionX(), linkedCreature->getPositionZ(), linkedCreature->getPositionY());

		zone = linkedCreature->getZone();

		if (zone == NULL) {
			linkedCreature->unlock();
			return;
		}

		linkedCreature->setMount(_this);

		linkedCreature->unlock();

		if (itno != NULL) {
			itno->wlock();

			itno->updateStatus(1);

			itno->unlock();
		}

		insertToZone(zone);

		if (instantMount) {
			linkedCreature->wlock(_this);

			linkedCreature->mountCreature(_this, false);

			linkedCreature->unlock();
		}
	} catch (Exception& e) {
		linkedCreature->unlock();

		error("calling MountCreature");
		error(e.getMessage());
	}
}

void MountCreatureImplementation::store(bool doLock) {
	if (zone == NULL || linkedCreature == NULL || !isInQuadTree())
		return;

	try {
		if (doLock)
			linkedCreature->wlock(_this);

		if (linkedCreature->isMounted())
			linkedCreature->dismount(false, true);

		linkedCreature->setMount(NULL);

		if (doLock)
			linkedCreature->unlock();

		if (itno != NULL) {
			itno->wlock();

			itno->updateStatus(0);

			itno->unlock();
		}

		removeFromZone();
	} catch (Exception& e) {
		if (doLock)
			linkedCreature->unlock();

		error("storing MountCreature");
		error(e.getMessage());
	}
}

IntangibleObject* MountCreatureImplementation::getITNO() {
	if (itno == NULL) {
		if (!linkedCreature->isPlayer())
			return NULL;

		Player* player = (Player*) linkedCreature;

		itno = new IntangibleObject((SceneObject*) player->getDatapad(),
				itnoCRC, linkedCreature->getNewItemID());

		itno->setName(stfName);
		itno->setDetailName(speciesName);
		itno->setWorldObject(_this);
	}

	return itno;
}
