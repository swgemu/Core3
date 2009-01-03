
#include "../../../../objects.h"
#include "../../../../packets.h"

#include "../../../../ZoneClientSessionImplementation.h"

#include "../../../../managers/resource/ResourceManager.h"
#include "../../../../managers/resource/ResourceManagerImplementation.h"
#include "../../../../managers/resource/ResourceTemplate.h"

#include "../../../../managers/item/ItemManager.h"

ResourceDeedImplementation::ResourceDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn)
	: ResourceDeedServant(creature, tempcrc, n, tempn, DEED) {

	objectID = creature->getNewItemID();
	objectCRC = tempcrc;
	name = n;
	templateName = tempn;
	init();
}

ResourceDeedImplementation::ResourceDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn)
	: ResourceDeedServant(objid, tempcrc, n, tempn, DEED) {

	objectID = objid;
	objectCRC = tempcrc;
	name = n;
	templateName = tempn;
	init();
}

ResourceDeedImplementation::~ResourceDeedImplementation() {

}

void ResourceDeedImplementation::init() {

	//deedSubType = DEED;
	objectSubType = DEED;

}

void ResourceDeedImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	//TODO:Cell permission check
	if (_this->getParent() != NULL) {
		bool cellPermission = true;

		if (_this->getParent()->isCell() && cellPermission) {
			if (_this->isTangible())
			omr->addRadialItem(0, 10, 3, "Pickup");
		}
	}

	omr->addRadialItem(0, 20, 3, "@ui_radial:item_use");

	omr->finish();

	player->sendMessage(omr);
}

int ResourceDeedImplementation::useObject(Player* player) {

	ResourceManager* resourceManager = player->getZone()->getZoneServer()->getResourceManager();

	SuiListBox* sui1 = new SuiListBox(player, SuiBoxType::FREE_RESOURCE);//beginning of sui chain

	sui1->setPromptTitle("Resources");
	sui1->setPromptText("Choose resource class.");
	sui1->setCancelButton(true);
	player->addSuiBox(sui1);
	resourceManager->generateSUI(player, sui1);

	player->setResourceDeedID(_this->getObjectID());
	uint64 objID = player->getResourceDeedID();
	player->sendMessage(sui1->generateMessage());

	return 1;
}

void ResourceDeedImplementation::destroyDeed(Player* player) {
	_this->sendDestroyTo(player);

	Zone* zone = player->getZone();
	if (zone != NULL) {
		ZoneServer* zoneServer = zone->getZoneServer();

		ItemManager* itemManager;

		if (zoneServer != NULL && ((itemManager = zoneServer->getItemManager()) != NULL)) {
			player->removeInventoryItem(objectID);
			itemManager->deletePlayerItem(player, _this, false);
			finalize();
		}
	}
}
