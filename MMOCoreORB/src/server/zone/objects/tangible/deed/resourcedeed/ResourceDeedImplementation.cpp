
#include "../../../../objects.h"
#include "../../../../packets.h"

#include "../../../../ZoneClientSessionImplementation.h"

#include "../../../../managers/resource/ResourceManager.h"
#include "../../../../managers/resource/ResourceManagerImplementation.h"

#include "../../../../managers/item/ItemManager.h"

ResourceDeedImplementation::ResourceDeedImplementation(CreatureObject* creature, uint32 objcrc, const UnicodeString& customname, const String& stfname)
		: ResourceDeedServant(creature, objcrc, customname, stfname) {

	init();
}

ResourceDeedImplementation::ResourceDeedImplementation(uint64 objid, uint32 objcrc, const UnicodeString& customname, const String& stfname)
		: ResourceDeedServant(objid, objcrc, customname, stfname) {

	init();
}

ResourceDeedImplementation::~ResourceDeedImplementation() {

}

void ResourceDeedImplementation::init() {
	objectSubType = RESOURCEDEED;

	setTargetStfFile(""); //TODO: What file are the resource names in.
}

void ResourceDeedImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	//omr->addRadialParent(20, 3, "@ui_radial:item_use");

	omr->finish();

	player->sendMessage(omr);
}

int ResourceDeedImplementation::useObject(Player* player) {

	ResourceManager* resourceManager = player->getZone()->getZoneServer()->getResourceManager();

	SuiListBox* sui1 = new SuiListBox(player, SuiWindowType::FREE_RESOURCE);//beginning of sui chain

	sui1->setPromptTitle("Resources");
	sui1->setPromptText("Choose resource class.");
	sui1->setCancelButton(true, "");
	player->addSuiBox(sui1);
	resourceManager->generateSUI(player, sui1);

	player->setResourceDeedID(_this->getObjectID());
	uint64 objID = player->getResourceDeedID();
	player->sendMessage(sui1->generateMessage());

	return 1;
}

SceneObject* ResourceDeedImplementation::generateObject(Player* player) {
	return NULL;
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

			_this->finalize();
		}
	}
}
