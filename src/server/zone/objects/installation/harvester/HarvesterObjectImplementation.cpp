#include "../../../ZoneClientSession.h"

#include "../../player/Player.h"

#include "../../../Zone.h"

#include "../../../packets.h"

#include "../../../objects.h"

//#include "../building/BuildingObject.h"
//#include "../building/cell/CellObject.h"


HarvesterObjectImplementation::HarvesterObjectImplementation(uint64 oid) : HarvesterObjectServant(oid) {

	objectID = oid;

	initialize();

	pvpStatusBitmask = 0;
}


HarvesterObjectImplementation::HarvesterObjectImplementation(uint64 oid, DeedObject * deed) : HarvesterObjectServant(oid, deed) {

	cout << "HarvesterObjectImplementation constructor" << endl;
	harvesterType = deed->getDeedSubType();

	objectID = oid;

	initialize();

	pvpStatusBitmask = 0;
}

HarvesterObjectImplementation::~HarvesterObjectImplementation(){

}

void HarvesterObjectImplementation::initialize() {

	objectSubType = TangibleObjectImplementation::HARVESTER;
	operating = 0;
	capacity = 0;
}

void HarvesterObjectImplementation::insertToZone(Zone* zone) {
	HarvesterObjectImplementation::zone = zone;

	/*if (container != NULL) {
		if (container->isCell())
			building = (BuildingObject*) container->getParent();
	}*/

	try {
		zone->lock();

		cout << "HarvesterObjectImplementation::insertToZone" << endl;
		zone->registerObject((HarvesterObject*) _this);

		zone->insert(this);
		zone->inRange(this, 128);

		zone->unlock();
	} catch (...) {
		cout << "exception HarvesterObject::insertToZone(Zone* zone)\n";

		zone->unlock();
	}
}
void HarvesterObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	cout << "HarvesterObjectImplementation::endTo" << endl;

	SceneObjectImplementation::create(client);

	if (container != NULL)
		link(client, container);

	BaseMessage* hino3 = new HarvesterObjectMessage3((HarvesterObject*) _this);
	client->sendMessage(hino3);

	BaseMessage* hino6 = new HarvesterObjectMessage6((HarvesterObject*) _this);
	client->sendMessage(hino6);

	if (pvpStatusBitmask != 0) {
		UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
		client->sendMessage(hino6);
	}

	if (doClose)
		SceneObjectImplementation::close(client);
}

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

void HarvesterObjectImplementation::update() {
}

int HarvesterObjectImplementation::getAvailableResourcesCount() {
	return 0;
}

