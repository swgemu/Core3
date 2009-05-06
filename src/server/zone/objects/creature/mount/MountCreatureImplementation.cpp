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
#include "VehicleObject.h"
MountCreatureImplementation::MountCreatureImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& customname, const String& stfname, Player* linkedcreature)
	: MountCreatureServant(objid), VehicleObject(linkedcreature) {

	creatureLinkID = linkedcreature->getObjectID();

	objectCRC = tempcrc;

	customName = customname;
	stfFile = "monster_name";
	stfName = stfname;

	StringBuffer loggingname;
	loggingname << "Mount = 0x" << objid;
	setLoggingName(loggingname.toString());

	init();
}

MountCreatureImplementation::~MountCreatureImplementation() {

	delete itemAttributes;

	itemAttributes = NULL;
}

void MountCreatureImplementation::init(){
	objectType = TangibleObjectImplementation::NONPLAYERCREATURE;
	objectSubType = TangibleObjectImplementation::VEHICLE;

	parent = NULL;

	//setType(CreatureImplementation::MOUNT);

	optionsBitmask = 0x1080;
	pvpStatusBitmask = 0x01;

	speed = 21.9f;
	acceleration = 10.95f;

	conditionDamage = 0;
	maxCondition = 20000;

	itemAttributes = new ItemAttributes();
	attackable = true;
	setLogging(false);
	setGlobalLogging(true);

}

bool MountCreatureImplementation::isAttackable() {
	return !isDisabled();
}

bool MountCreatureImplementation::isAttackableBy(CreatureObject* creature) {
	return getLinkedCreature()->isAttackableBy(creature);
}

void MountCreatureImplementation::repair() {
	if (getLinkedCreature() == NULL || !getLinkedCreature()->isPlayer())
		return;

	Player* linkedPlayer = (Player*)getLinkedCreature();

	ZoneClientSession* client = linkedPlayer->getClient();
	if (client == NULL)
		return;

	conditionDamage = 0;
	speed = 21.9f;
	acceleration = 10.95f;
	StringBuffer cond;

	cond << "condition=" << (maxCondition-conditionDamage) << "/" << maxCondition << ":";

	String attr = cond.toString();
	setAttributes(attr);

	BaseMessage* creo3 = new CreatureObjectMessage3(_this);
	client->sendMessage(creo3);

	try {
		zone->lock();

		for (int i = 0; i < linkedPlayer->inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) linkedPlayer->getInRangeObject(i))->_getStub());

			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (player != linkedPlayer && linkedPlayer->isInRange(player, 128)) {
					ZoneClientSession* playerClient = player->getClient();

					if (playerClient != NULL) {
						BaseMessage* creo3 = new CreatureObjectMessage3(_this);
						playerClient->sendMessage(creo3);
					}
				}
			}
		}

		zone->unlock();

	} catch (...) {
		zone->unlock();
	}
}

void MountCreatureImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if (player == getLinkedCreature()) {
		omr->addRadialParent(205, 1, "@pet/pet_menu:menu_enter_exit");
		omr->addRadialParent(61, 3, "");

		//TODO:Remove this when garages are functioning
		omr->addRadialParent(62, 3, "Repair");
	}

	omr->finish();

	player->sendMessage(omr);
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
		getLinkedCreature()->sendTo(player);
		getLinkedCreature()->sendItemsTo(player);
	}

	if (doClose)
		SceneObjectImplementation::close(client);
}

void MountCreatureImplementation::parseItemAttributes() {

	maxCondition = itemAttributes->getMaxCondition();
	conditionDamage = maxCondition - itemAttributes->getCurrentCondition();

	//String temp = "objectFileName";
	//setObjectFileName(itemAttributes->getStringAttribute(temp));
}


void MountCreatureImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage(_this);

	CreatureObject* owner = getLinkedCreature();
	if (owner != NULL) {
		UnicodeString name = UnicodeString("");
		name = owner->getCharacterName();
		String strname = name.toString();

		alm->insertAttribute("@obj_attr_n:crystal_owner", strname); //Owner: Name
	}

	addAttributes(alm);

	player->sendMessage(alm);
}

void MountCreatureImplementation::addAttributes(AttributeListMessage* alm) {
	StringBuffer cond;
	cond << (maxCondition-conditionDamage) << "/" << maxCondition;

	alm->insertAttribute("condition", cond);
}

void MountCreatureImplementation::call() {
	if (isInQuadTree())
		return;
	try {

		if (getLinkedCreature() == NULL)
			return;

		parent = NULL;

		getLinkedCreature()->wlock(_this);

		if (getLinkedCreature()->getParent() != NULL) {
			getLinkedCreature()->unlock();
			return;
		}

		if (getLinkedCreature()->getMount() != NULL) {
			((VehicleObject*)getLinkedCreature()->getMount())->store(false);
		}

		if (getLinkedCreature()->isInCombat()) {
			getLinkedCreature()->unlock();
			return;
		}

		// Jet Pack
		if (isJetpack()) {
			setCustomizationVariable("index_hover_height", 40); // 32 = 9m, 64 = 12m
		}

		initializePosition(getLinkedCreature()->getPositionX(), getLinkedCreature()->getPositionZ(), getLinkedCreature()->getPositionY());

		zone = getLinkedCreature()->getZone();

		if (zone == NULL) {
			getLinkedCreature()->unlock();
			return;
		}

		getLinkedCreature()->unlock();

		if (getDatapadItem() != NULL) {
			getDatapadItem()->wlock();

			getDatapadItem()->updateStatus(1);

			getDatapadItem()->unlock();
		}

		setFaction(getLinkedCreature()->getFaction());

		if (getObjectCRC()==0xAF6D9F4F)//swoop
			changeConditionDamage(25);
		else if (getObjectCRC()==0x729517EF)//speederbike
			changeConditionDamage(12);
		else if (getObjectCRC()==0x4EC3780C)//x34 landspeeder
			changeConditionDamage(7);
		else
			changeConditionDamage(25);

		StringBuffer cond;

		cond << "condition=" << (maxCondition-conditionDamage) << "/" << maxCondition << ":";

		String attr = cond.toString();
		setAttributes(attr);

		insertToZone(zone);

		if (isJetpack()) {
			getLinkedCreature()->wlock(_this);

			getLinkedCreature()->mountCreature(_this, false);

			getLinkedCreature()->unlock();
		}

	} catch (Exception& e) {
		getLinkedCreature()->unlock();

		error("calling MountCreature");
		error(e.getMessage());
	}
}

void MountCreatureImplementation::store(bool doLock) {
	if (zone == NULL || getLinkedCreature() == NULL || !isInQuadTree())
		return;

	try {
		if (doLock)
			getLinkedCreature()->wlock(_this);

		if (getLinkedCreature()->isMounted())
			getLinkedCreature()->dismount(false, true);

		getLinkedCreature()->setMount(NULL);
		if (doLock)
			getLinkedCreature()->unlock();

		if (getDatapadItem() != NULL) {
			getDatapadItem()->wlock();
			getDatapadItem()->updateStatus(0);
			getDatapadItem()->unlock();
		}

		removeFromZone();
	} catch (Exception& e) {
		if (doLock)
			getLinkedCreature()->unlock();

		error("storing MountCreature");
		error(e.getMessage());
	}
}
