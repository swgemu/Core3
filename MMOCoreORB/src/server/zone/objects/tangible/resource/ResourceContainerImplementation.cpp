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

#include "ResourceContainerImplementation.h"
#include "ResourceContainer.h"

#include "../../../packets.h"
#include "../../../objects.h"

ResourceContainerImplementation::ResourceContainerImplementation(uint64 oid)
		: ResourceContainerServant(oid, RESOURCECONTAINER) {
	objectCRC = 741847407;

	stfFile = "kb/kb_resources_n"; //

	customName = UnicodeString("");
	stfName = "";

	init();
}

ResourceContainerImplementation::ResourceContainerImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n,
		const String& tempn) : ResourceContainerServant(oid, tempCRC, n, tempn, RESOURCECONTAINER) {
	stfFile = "kb/kb_resources_n";

	customName = n;
	stfName = tempn;

	init();
}

ResourceContainerImplementation::ResourceContainerImplementation(CreatureObject* creature, uint32 tempCRC,
		const UnicodeString& n, const String& tempn) : ResourceContainerServant(creature, tempCRC, n, tempn, RESOURCECONTAINER) {
	stfFile = "kb/kb_resources_n";

	customName = n;
	stfName = tempn;

	init();
}

ResourceContainerImplementation::~ResourceContainerImplementation() {
}

bool ResourceContainerImplementation::compare(ResourceContainer* inResource){

	//System::out << hex << _this->getObjectSubType() << "   " <<  inResource->getObjectSubType() << dec << endl;

	if (_this->getResourceName() == inResource->getResourceName() &&
			_this->getStfName() == inResource->getStfName() &&
			_this->getObjectSubType() == inResource->getObjectSubType() &&
			_this->getDecayResistance() == inResource->getDecayResistance() &&
			_this->getQuality() == inResource->getQuality() &&
			_this->getFlavor() == inResource->getFlavor() &&
			_this->getPotentialEnergy() == inResource->getPotentialEnergy() &&
			_this->getMalleability() == inResource->getMalleability() &&
			_this->getToughness() == inResource->getToughness() &&
			_this->getShockResistance() == inResource->getShockResistance() &&
			_this->getColdResistance() == inResource->getColdResistance() &&
			_this->getHeatResistance() == inResource->getHeatResistance() &&
			_this->getConductivity() == inResource->getConductivity() &&
			_this->getEntangleResistance() == inResource->getEntangleResistance())
		return true;
	else
		return false;

}

void ResourceContainerImplementation::init() {
	objectSubType = TangibleObjectImplementation::RESOURCECONTAINER;

	optionsBitmask = 1;

	maxCondition = 0x64;

	complexity = 1.f;

	setResourceID(0);
	setContents(0);
	setDecayResistance(0);
	setQuality(0);
	setFlavor(0);
	setPotentialEnergy(0);
	setMalleability(0);
	setToughness(0);
	setShockResistance(0);
	setColdResistance(0);
	setHeatResistance(0);
	setConductivity(0);
	setEntangleResistance(0);
	String temp = "";
	setClassSeven(temp);
	setResourceName(temp);
	setIsEnergy(false);

	setOptionsBitmask(1);
}

void ResourceContainerImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();

	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (parent != NULL) {
		link(client, parent);
	}

	BaseMessage* rcno3 = new ResourceContainerObjectMessage3(_this);
	client->sendMessage(rcno3);

	BaseMessage* rcno6 = new ResourceContainerObjectMessage6(_this);
	client->sendMessage(rcno6);

	//BaseMessage* rcno8 = new ResourceContainerObjectMessage8(_this);
	//client->sendMessage(rcno8);

	//BaseMessage* rcno9 = new ResourceContainerObjectMessage9(_this);
	//client->sendMessage(rcno9);

	if (doClose)
		SceneObjectImplementation::close(client);

	sendDeltas(player);
}

void ResourceContainerImplementation::sendDeltas(Player* player) {

	ResourceContainerObjectDeltaMessage3* rcnod3 = new ResourceContainerObjectDeltaMessage3(_this);

	rcnod3->setQuantity(_this->getContents());
	rcnod3->close();

	player->sendMessage(rcnod3);
	//Message* rcnod6 = new ResourceContainerObjectDeltaMessage6(_this);
	//client->sendMessage(rcnod6);
}

void ResourceContainerImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage(_this);
	addAttributes(alm);

	player->sendMessage(alm);
}

void ResourceContainerImplementation::splitContainer(Player* player, int newQuantity) {
	int oldQuantity = getContents();

	if (newQuantity < oldQuantity) {
		ResourceContainer* container = new ResourceContainer(player->getNewItemID(), getObjectCRC(), getCustomName(), getStfName());
		container->setResourceName(getResourceName());
		container->setContents(newQuantity);

		ResourceManager* resourceManager = player->getZone()->getZoneServer()->getResourceManager();
		resourceManager->setResourceData(container);

		((CreatureObject*)player)->addInventoryItem(container);

		container->sendTo(player);
		container->setPersistent(false);

		setContents(oldQuantity - newQuantity);
		sendDeltas(player);
		setUpdated(true);
	}
}

void ResourceContainerImplementation::transferContents(Player* player, ResourceContainer* fromRCO) {
    int fromContents = fromRCO->getContents();
    int toContents = getContents();

    if (fromContents + toContents <= getMaxContents()) {
    	setContents(fromContents + toContents);
    	sendDeltas(player);

    	player->getZone()->getZoneServer()->getItemManager()->deletePlayerItem(player, fromRCO, false);

    	player->removeInventoryItem(fromRCO->getObjectID());

    	fromRCO->destroy(player->getClient());

    	fromRCO->finalize();
    } else {
    	int canMove = getMaxContents() - toContents;

    	setContents(canMove + toContents);
    	sendDeltas(player);

    	fromRCO->setContents(fromContents - canMove);
    	fromRCO->sendDeltas(player);

    	fromRCO->setUpdated(true);
    }

    setUpdated(true);
}

void ResourceContainerImplementation::parseItemAttributes() {
	String temp = "quantity";
	quantity = itemAttributes->getIntAttribute(temp);

	temp = "resourceID";
	resourceID = itemAttributes->getUnsignedLongAttribute(temp);

	temp = "res_dr";
	res_dr = itemAttributes->getIntAttribute(temp);

	temp = "res_oq";
	res_oq = itemAttributes->getIntAttribute(temp);

	temp = "res_fl";
	res_fl = itemAttributes->getIntAttribute(temp);

	temp = "res_pe";
	res_pe = itemAttributes->getIntAttribute(temp);

	temp = "res_m";
	res_m = itemAttributes->getIntAttribute(temp);

	temp = "res_t";
	res_t = itemAttributes->getIntAttribute(temp);

	temp = "res_sr";
	res_sr = itemAttributes->getIntAttribute(temp);

	temp = "res_cr";
	res_cr = itemAttributes->getIntAttribute(temp);

	temp = "res_hr";
	res_hr = itemAttributes->getIntAttribute(temp);

	temp = "res_c";
	res_c = itemAttributes->getIntAttribute(temp);

	temp = "res_er";
	res_er = itemAttributes->getIntAttribute(temp);

	temp = "res_class7";
	res_class7 = itemAttributes->getStringAttribute(temp);

	temp = "res_name";
	res_name = itemAttributes->getStringAttribute(temp);

	temp = "subtype";
	objectSubType = itemAttributes->getUnsignedLongAttribute(temp);

	temp = "isEnergy";
	energy = itemAttributes->getBooleanAttribute(temp);

}

void ResourceContainerImplementation::addAttributes(AttributeListMessage* alm) {

	//alm->insertAttribute("condition", "100/100");
	//alm->insertAttribute("volume", "1");

	StringBuffer ssQuantity;
	ssQuantity << quantity << "/" << getMaxContents();

	alm->insertAttribute("resource_name", res_name);
	alm->insertAttribute("resource_contents", ssQuantity);

	alm->insertAttribute("resource_class", res_class7);

	if (res_cr > 0)
		alm->insertAttribute("res_cold_resist", res_cr);

	if (res_c > 0)
		alm->insertAttribute("res_conductivity", res_c);

	if (res_dr > 0)
		alm->insertAttribute("res_decay_resist", res_dr);

	if (res_hr > 0)
		alm->insertAttribute("res_heat_resist", res_hr);

	if (res_m > 0)
		alm->insertAttribute("res_malleability", res_m);

	if (res_fl > 0)
		alm->insertAttribute("res_flavor", res_fl);

	if (res_pe > 0)
		alm->insertAttribute("res_potential_energy", res_pe);

	if (res_oq > 0)
		alm->insertAttribute("res_quality", res_oq);

	if (res_sr > 0)
		alm->insertAttribute("res_shock_resistance", res_sr);

	if (res_t > 0)
		alm->insertAttribute("res_toughness", res_t);

	if (res_er > 0)
		alm->insertAttribute("entangle_resistance", res_er);

	alm->insertInt(0);
}


