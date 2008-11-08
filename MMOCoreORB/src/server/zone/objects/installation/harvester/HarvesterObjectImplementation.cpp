#include "../../../ZoneClientSession.h"
#include "../../player/Player.h"
#include "../../../Zone.h"
#include "../../../packets.h"
#include "../../../objects.h"

#include "../../../managers/resource/ResourceHarvestType.h"


HarvesterObjectImplementation::HarvesterObjectImplementation(uint64 oid) : HarvesterObjectServant(oid) {
	objectID = oid;

	//(InstallationObject*)_this
	InstallationObjectImplementation::init();
	init();
}


HarvesterObjectImplementation::HarvesterObjectImplementation(uint64 oid, HarvesterDeed* deed) : HarvesterObjectServant(oid, deed) {
	objectID = oid;

	InstallationObjectImplementation::init();
	init();

	objectCRC = String::hashCode(deed->getTargetFile());
	name = deed->getTargetName();
	file = deed->getTargetFile();
	templateName = deed->getTargetTemplate();


	setSurplusMaintenance(deed->getSurplusMaintenance());
	setMaintenanceRate(deed->getMaintenanceRate());
	setSurplusPower(deed->getSurplusPower());
	setPowerRate(getMaintenanceRate());
	setHopperSizeMax(deed->getHopperSize());
	setExtractionRate(deed->getExtractionRate());
}

void HarvesterObjectImplementation::parseItemAttributes() {

	try {
	InstallationObjectImplementation::parseItemAttributes();

	string attr = "hopperSizeMax";
	setHopperSizeMax(itemAttributes->getFloatAttribute(attr));

	attr = "extractionRate";
	setExtractionRate(itemAttributes->getFloatAttribute(attr));

	attr = "activeResourceID";
	setActiveResourceID(itemAttributes->getUnsignedLongAttribute(attr));

	attr = "activeSpawnID";
	setActiveSpawnID(itemAttributes->getUnsignedLongAttribute(attr));

	attr = "spawnExpireTimestamp";
	setSpawnExpireTimestamp(itemAttributes->getUnsignedLongAttribute(attr));

	attr = "resourceHopperTimestamp";
	setResourceHopperTimestamp(itemAttributes->getUnsignedLongAttribute(attr));

	attr = "spawnDensity";
	setSpawnDensity(itemAttributes->getIntAttribute(attr));


	attr = "resourceHopper";
	string hopper = itemAttributes->getStringAttribute(attr);
	unserializeResourceHopper(hopper);


	} catch (Exception& e) {
		cout << "HarvesterObjectImplementation::parseItemAttributes(): " << e.getMessage() << endl;
		e.printStackTrace();
		throw("HarvesterObjectImplementation::parseItemAttributes()!!!");
	}
}

HarvesterObjectImplementation::~HarvesterObjectImplementation(){

}

void HarvesterObjectImplementation::init() {
	objectSubType = TangibleObjectImplementation::HARVESTER;

	//resourceHopper.setNullValue(NULL);
	resourceHopper.setInsertPlan(SortedVector<uint64>::NO_DUPLICATE);

	// Init to Zero
	hopperResourceUpdateCounter = 0;
	setHopperSizeMax(59000.0f);
	setExtractionRate(10.0f);
	setOperating(false);
	harvesterType = 0;

}

/*
void HarvesterObjectImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	omr->addRadialItem(0, 122, 1, "@player_structure:management");

	omr->addRadialItem(2, 132, 3, "@player_structure:permission_destroy");
	omr->addRadialItem(2, 128, 3, "@player_structure:management_status");
	omr->addRadialItem(2, 131, 3, "Set Name"); //"@player_structure:set_name"
	omr->addRadialItem(2, 133, 3, "@player_structure:management_pay");
	omr->addRadialItem(2, 82, 3, "@harvester:manage");
	omr->addRadialItem(2, 77, 3, "@player_structure:management_power");

	omr->finish();

	player->sendMessage(omr);
}
*/

void HarvesterObjectImplementation::verifyOperators() {
	if(operatorList.size() <= 0)
		return;

	// won't fully clean up at once because indexes would change once you remove one - but should clean up
	for(int i = 0; i < operatorList.size(); i++)
	{
		SceneObject *obj = operatorList.get(i);
		if(!obj->isPlayer() || (obj->isPlayer() && !((Player*)obj)->isOnline())) {
			operatorList.remove(i);

		}
	}

}

void HarvesterObjectImplementation::updateOperatorsAddBlankActiveRescource() {
	if(operatorList.size() <= 0)
		return;

	verifyOperators();

	for(int i = 0; i < operatorList.size(); i++)
	{
		SceneObject *obj = operatorList.get(i);

		// Will get cleaned up next event
		if(!obj->isPlayer())
			 continue;
		Player *play = (Player*)obj;

		if(!play->isOnline())
			continue;

		InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7((InstallationObject*)_this);
		dinso7->updateHopper();
		dinso7->addHopperItem(getActiveResourceID());
		dinso7->updateHopperSize();
		dinso7->close();
		play->sendMessage(dinso7);
	}
}

void HarvesterObjectImplementation::updateOperatorsEmptyHopper() {

	if(operatorList.size() <= 0)
		return;

	verifyOperators();

	for(int i = 0; i < operatorList.size(); i++)
	{
		SceneObject *obj = operatorList.get(i);

		// Will get cleaned up next event
		if(!obj->isPlayer())
			 continue;
		Player *play = (Player*)obj;

		InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7((InstallationObject*)_this);
		dinso7->updateHopper();
		dinso7->addHopperItem(getActiveResourceID());
		dinso7->updateHopperSize();
		dinso7->close();
		play->sendMessage(dinso7);


	}

}

void HarvesterObjectImplementation::updateOperators() {
	if(operatorList.size() <= 0)
		return;

	verifyOperators();

	for(int i = 0; i < operatorList.size(); i++)
	{
		SceneObject *obj = operatorList.get(i);

		// Will get cleaned up next event
		if(!obj->isPlayer())
			 continue;
		Player *play = (Player*)obj;

		if(!play->isOnline())
			continue;


		InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7((InstallationObject*)_this);
		dinso7->updateHopper();
		dinso7->updateHopperItem(getActiveResourceID());
		dinso7->updateHopperSize();
		dinso7->close();
		play->sendMessage(dinso7);


	}

}

void HarvesterObjectImplementation::updateHopper() {
	// Nothing to update if we're not operating
	if(!isOperating())
		return;

	// the spawn expired before we updated hopper last - don't update the hopper
	if (spawnExpireTimestamp.compareTo(resourceHopperTimestamp) > 0)
	{ // if (t1 < t2) return 1;
		cout << "HarvesterObjectImplementation::updateHopper(" << hex << activeResourceID << dec << ") resource expired!! (why do we have expired resources in the list?) spawnExpireTimestamp: " << dec << spawnExpireTimestamp.getTime() << "  resourceHopperTimestamp: " << resourceHopperTimestamp.getTime() << endl;
		return;
	}

    Time currentTime;
    // if (t1 < t2) return 1 - if spawnTime is sooner currentTime, use spawnTime, else use spawn time
    Time harvestUntil = (spawnExpireTimestamp.compareTo(currentTime) > 0) ? spawnExpireTimestamp : currentTime;

	float elapsedTime = (harvestUntil.getTime() - resourceHopperTimestamp.getTime());

	float harvestAmount = (elapsedTime / 60.0) * ( (spawnDensity * 1.0 / 100.0) * getExtractionRate());

	int availableCapacity = (int)(getHopperSizeMax() - getHopperSize());
	harvestAmount = harvestAmount > availableCapacity ? availableCapacity : harvestAmount;

	if(resourceHopper.contains(activeResourceID)) {
		float currentQuantity = resourceHopper.get(activeResourceID);
		resourceHopper.drop(activeResourceID);
		resourceHopper.put((uint64)activeResourceID, currentQuantity + harvestAmount);
	} else {
		resourceHopper.put((uint64)activeResourceID, harvestAmount);
	}

	serializeResourceHopper(); // update attribute
	// Update Timestamp
	resourceHopperTimestamp = currentTime;
}


// need activate code
// If hopper size is zero for the resource + is operating, send a packet to the operators to add a zero element for delta packets

void HarvesterObjectImplementation::changeActiveResourceID(uint64 rid) {

	// Logic:
	// 1) If operating, and already has an active resource ID - make sure the hopper gets updated
	// 2) Get the spawn information & set the active resource id
	// 3) If hopper size is zero for the resource + is operating, send a packet to the operators to add a zero element for delta packets

	if(isOperating() && getActiveResourceID() != 0)
	{
		updateHopper();
	}

	Time currentTime;
	setActiveResourceID(rid);
	setResourceHopperTimestamp(currentTime.getTime()); // ReInit

	ResourceManager* resourceManager = getZone()->getZoneServer()->getResourceManager();
	if(resourceManager == NULL)
	{
		cout << "resourceManager was NULL OMFG!" << endl;
		setActiveSpawnID(0);
		setSpawnExpireTimestamp(getResourceHopperTimestamp());
		setSpawnDensity(0);
		return;
	}

	ResourceList* list = resourceManager->getResourceListAtLocation(getZone()->getZoneID(), getPositionX(), getPositionY(), getHarvesterType());
	for (int x = 0; x < list->size(); x++)
	{
		ResourceItem *ri = list->get(x);
		if(ri->getObjectID() == rid)
		{
			setActiveSpawnID(ri->getSpawnID());
			setSpawnExpireTimestamp((uint32)ri->getSpawnExpireTimestamp());
			setSpawnDensity(ri->getDensity());
		}
	}

	if(getHopperItemQuantity(getActiveResourceID()) == 0)
		updateOperatorsAddBlankActiveRescource();
}

float HarvesterObjectImplementation::getActualRate() {
	if(!isOperating())
		return 0.0f;

	ResourceManager* resourceManager = getZone()->getZoneServer()->getResourceManager();
	if(resourceManager == NULL)
		return 0.0f;

	ResourceList* list = resourceManager->getResourceListAtLocation(getZone()->getZoneID(), getPositionX(), getPositionY(), getHarvesterType());
	for (int x = 0; x < list->size(); x++)
	{
		ResourceItem *ri = list->get(x);
		if(ri->getObjectID() == getActiveResourceID())
			return getExtractionRate() * ((ri->getDensity() * 1.0f) / 100.0f);
	}

	return 0.0f;
}


void HarvesterObjectImplementation::serializeResourceHopper() {
	stringstream hopperstr;

	for (int i = 0; i < getHopperItemCount(); i++) {
		hopperstr << getHopperItemID(i) << "|" << getHopperItemQuantity(i) << ";";
	}

	string attr("resourceHopper");
	string val = hopperstr.str();
	itemAttributes->setStringAttribute(attr, val);
}

void HarvesterObjectImplementation::unserializeResourceHopper(const string& hopper) {

	if(hopper.empty())
		return;

	StringTokenizer resources(hopper);
	resources.setDelimeter(";");

	while(resources.hasMoreTokens()) {
		string item("");
		resources.getStringToken(item);
		if(item.empty())
			continue;

		StringTokenizer pieces(item);
		pieces.setDelimeter("|");

		uint64 oid = pieces.getLongToken();
		float quantity = pieces.getFloatToken();

		if(!resourceHopper.contains(oid)) {
			resourceHopper.put((uint64)oid, quantity);
		}

	}
}

int HarvesterObjectImplementation::getHarvesterType() {
	switch(objectCRC) {
		case 0x4C850DFE: //	object/installation/generators/shared_power_generator_fusion_style_1.iff
			return ResourceHarvestType::FUSION;
		//case 0x8CE44BBB: //	object/installation/generators/shared_power_generator_photo_bio_style_1.iff
		case 0x3341B027: //	object/installation/generators/shared_power_generator_solar_style_1.iff
			return ResourceHarvestType::SOLAR;
		case 0xAED007BF: //	object/installation/generators/shared_power_generator_wind_style_1.iff
			return ResourceHarvestType::WIND;
		case 0xCD68D9C7: //	object/installation/mining_gas/shared_mining_gas_harvester_style_1.iff
		case 0x167F7150: //	object/installation/mining_gas/shared_mining_gas_harvester_style_2.iff
		case 0x5F7216DD: //	object/installation/mining_gas/shared_mining_gas_harvester_style_3.iff
			return ResourceHarvestType::GAS;
		case 0x7824E0B0: //	object/installation/mining_liquid/shared_mining_liquid_harvester_style_1.iff
		case 0xA3334827: //	object/installation/mining_liquid/shared_mining_liquid_harvester_style_2.iff
		case 0xEA3E2FAA: //	object/installation/mining_liquid/shared_mining_liquid_harvester_style_3.iff
			return ResourceHarvestType::CHEMICAL;
		case 0x8540F576: //	object/installation/mining_liquid/shared_mining_liquid_moisture_harvester.iff
		case 0x4DD087FE: //	object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_heavy.iff
		case 0xBBE35A9A: //	object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_medium.iff
			return ResourceHarvestType::WATER;
		case 0x403FD0B1: //	object/installation/mining_ore/shared_mining_ore_harvester_heavy.iff
		case 0x667FADDA: //	object/installation/mining_ore/shared_mining_ore_harvester_style_1.iff
		case 0xBD68054D: //	object/installation/mining_ore/shared_mining_ore_harvester_style_2.iff
			return ResourceHarvestType::MINERAL;
		//case 0xD33E6DF2: //	object/installation/mining_organic/shared_mining_organic_creature_farm.iff
			//return ResourceHarvestType::CREATURE;
		case 0xCCFA21C4: //	object/installation/mining_organic/shared_mining_organic_flora_farm.iff
		case 0x3481BD07: //	object/installation/mining_organic/shared_mining_organic_flora_farm_heavy.iff
		case 0x28A44E72: //	object/installation/mining_organic/shared_mining_organic_flora_farm_medium.iff
			return ResourceHarvestType::FLORA;
		default:
			return 0;
	}
}
