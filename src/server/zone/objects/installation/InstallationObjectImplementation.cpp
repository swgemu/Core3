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

//#include "../tangible/deed/DeedObject.h"

//#include "../tangible/TangibleObject.h"

//#include "../player/sui/inputbox/SuiInputBoxImplementation.h"

//#include "../../ZoneClient.h"

//#include "../player/Player.h"

//#include "../../Zone.h"

//#include "../../packets.h"

#include "../../objects.h"


InstallationObjectImplementation::InstallationObjectImplementation(uint64 oid) : InstallationObjectServant(oid, INSTALLATION) {

	cout << "InstallationObjectImplementation Constructor" << endl;
	objectID = oid;

	init();
}

InstallationObjectImplementation::InstallationObjectImplementation(uint64 oid, DeedObject * deed) : InstallationObjectServant(oid, INSTALLATION) {

	cout << "InstallationObjectImplementation Constructor" << endl;
	objectID = oid;

	objectCRC = String::hashCode(deed->getTargetFile());

	name = deed->getTargetName();

	file = deed->getTargetFile();

	templateName = deed->getTargetTemplate();

	init();
	cout << "InstallationObjectImplementation Constructor Completed" << endl;
}

InstallationObjectImplementation::~InstallationObjectImplementation(){

}

void InstallationObjectImplementation::init() {
	container = NULL;
	zone = NULL;

	persistent = false;
	updated = false;

	building = NULL;

	objectCount = 0;

	structureStatus = "private";

	energy = 0;
	energyRate = 45;

	maintenanceRate = 45;

	conditionDamage = 0;
	maxCondition = 1000;

	maintenance = 3000;
	minimumMaintenance = 3000;

	objectType = SceneObjectImplementation::TANGIBLE;
	objectSubType = TangibleObjectImplementation::INSTALLATION;

	equipped = false;

	pvpStatusBitmask = 0;
}

/*void InstallationObjectImplementation::insertToZone(Zone* zone) {
	InstallationObjectImplementation::zone = zone;
	zoneID = zone->getZoneID();

	try {
		zone->lock();

		cout << "InstallationObjectImplementation::insertToZone" << endl;
		zone->registerObject((InstallationObject*) _this);

		zone->insert(this);
		zone->inRange(this, 128);

		zone->unlock();
	} catch (...) {
		cout << "exception InstallationObject::insertToZone(Zone* zone)\n";

		zone->unlock();
	}
}*/

void InstallationObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (container != NULL)
		link(client, container);

	BaseMessage* inso3 = new InstallationObjectMessage3((InstallationObject*) _this);
	client->sendMessage(inso3);

	BaseMessage* inso6 = new InstallationObjectMessage6((InstallationObject*) _this);
	client->sendMessage(inso6);

	if (pvpStatusBitmask != 0) {
		UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
		client->sendMessage(inso6);
	}

	if (doClose)
		SceneObjectImplementation::close(client);

}

void InstallationObjectImplementation::handleStructureRedeed(Player * player) {
	try {

		player->setCurrentStructureID(this->getObjectID());

		stringstream sscan, sscond, ssmain;
		string willRedeed;

		if((conditionDamage == 0) && (maintenance >= minimumMaintenance)) {

			sscan << "CAN REDEED: \\#32CD32YES\\#";
			willRedeed = "\\#32CD32YES\\#";

			sscond << dec << "- CONDITION: \\#32CD32" << maxCondition - conditionDamage << "/" << maxCondition << "\\#";
			ssmain << dec << "- MAINTENANCE: \\#32CD32" << static_cast<int>(maintenance) << "/" << minimumMaintenance << "\\#";

		}
		else {

			sscan << "CAN REDEED: \\#FF6347NO\\#";
			willRedeed = "\\#FF6347NO\\##";

			if((conditionDamage == 0)) {

				sscond << dec << "- CONDITION: \\#32CD32"<< maxCondition - conditionDamage << "/" << maxCondition << "\\#";
				ssmain << dec << "- MAINTENANCE: \\#FF6347" << static_cast<int>(maintenance) << "/" << minimumMaintenance << "\\#";

			}
			else {

				sscond << dec << "- CONDITION: \\#FF6347" << maxCondition - conditionDamage << "/" << maxCondition << "\\#";
				ssmain << dec << "- MAINTENANCE: \\#FF6347" << static_cast<int>(maintenance) << "/" << minimumMaintenance << "\\#";

			}
		}

		SuiListBox* redeedBox = new SuiListBox(player, 0x7280, 0x02);

		redeedBox->setPromptTitle(this->getName().c_str());

		redeedBox->setPromptText("You have elected to destroy a structure.  Pertinent structure"
				" data can be found in the list below.  Please complete the following steps"
				" to confirm structure deletion.\n\nIf you wish to redeed your structure, all"
				" structure data must be \\#32CD32GREEN\\#       \\#93F5FFTo continue with structure deletion"
				", click YES.  Otherwise, please click NO.\nWILL REDEED: " + willRedeed);

		redeedBox->addMenuItem(sscan.str());
		redeedBox->addMenuItem(sscond.str());
		redeedBox->addMenuItem(ssmain.str());

		player->addSuiBox(redeedBox);
		player->sendMessage(redeedBox->generateMessage());

	}
	catch(...) {
		cout << "unreported exception in InstallationObjectImplementation::handleStructureRedeed\n";
	}
}

void InstallationObjectImplementation::handleStructureRedeedConfirm(
		Player * player) {
	try {
		string status;
		stringstream prompt;

		destroyCode = (System::random(999999) + 100000);

		SuiInputBox * confirmRedeed = new SuiInputBox(player, 0x7281, 0x00);

		confirmRedeed->setPromptTitle("Confirm Structure Destruction");

		if((conditionDamage == 0) && (maintenance >= minimumMaintenance)){
			status = "\\#32CD32WILL\\#       \\#93F5FF";
		}
		else{
			status = "\\#FF6347WILL NOT\\#       \\#93F5FF";
		}

		prompt << dec << "Your structure " << status << " be redeeded.  If you wish"
		<< " to continue with destroying your structure, please enter the following code"
		<<" into the input box.\n\nCode: " << destroyCode;

		confirmRedeed->setPromptText(prompt.str());

		player->addSuiBox(confirmRedeed);
		player->sendMessage(confirmRedeed->generateMessage());

	}
	catch(...) {
		cout << "unreported exception in InstallationObjectImplementation::handleStructureRedeedConfirm\n";
	}

}
void InstallationObjectImplementation::handleMakeDeed(Player * player) {
	cout<< "Im a deed now\n";
}
void InstallationObjectImplementation::handleStructureStatus(Player* player) {
	try
	{
		player->setCurrentStructureID(this->getObjectID());

		stringstream sscond, ssmpool, ssmrate, ssppool, ssprate;

		SuiListBox* statusBox = new SuiListBox(player, 0x7282, 0x01);
		statusBox->setPromptTitle("@player_structure:structure_status_t");
		statusBox->setPromptText("Structure Name: " + this->getName().c_str());

		statusBox->addMenuItem("Owner: " + owner);
		statusBox->addMenuItem("This structure is " + structureStatus);

		sscond << dec << "Condition: " << (static_cast<int>(((maxCondition - conditionDamage)/maxCondition) * 100)) << "%";
		statusBox->addMenuItem(sscond.str());

		ssmpool << dec << "Maintenance Pool: " << static_cast<int>(maintenance);
		statusBox->addMenuItem(ssmpool.str());

		ssmrate << dec << "Maintenance Rate: " << static_cast<int>(maintenanceRate) << " cr/hr";
		statusBox->addMenuItem(ssmrate.str());

		ssppool << dec << "Power Reserves: " << static_cast<int>(energy);
		statusBox->addMenuItem(ssppool.str());

		ssprate << dec << "Power Consumption " << static_cast<int>(energyRate) << " units/hr";
		statusBox->addMenuItem(ssprate.str());

		player->addSuiBox(statusBox);
		player->sendMessage(statusBox->generateMessage());

	}
	catch(...) {
		cout << "unreported exception in InstallationObjectImplementation::handleStructureStatus\n";
	}
}


void InstallationObjectImplementation::handleStructureAddMaintenance(Player* player) {
	try
	{
		stringstream sstext, sscash, ssmaintenance;

		player->setCurrentStructureID(this->getObjectID());

		SuiTransferBox* maintenanceBox = new SuiTransferBox(player, 0x7284);
		maintenanceBox->setPromptTitle("Select Amount");

		sstext << "Select the total amount you would like to pay the existing"
			<<" maintenace pool.\n\nCurrent maintanence pool: " << maintenance << "cr.";
		maintenanceBox->setPromptText(sstext.str());

		sscash << player->getCashCredits();
		ssmaintenance << maintenance;

		maintenanceBox->addFrom("@player_structure:total_funds", sscash.str(), sscash.str(), "1");
		maintenanceBox->addTo("@player_structure:to_pay", ssmaintenance.str(), ssmaintenance.str(), "1");

		player->addSuiBox(maintenanceBox);
		player->sendMessage(maintenanceBox->generateMessage());

	}
	catch(...) {
		cout << "unreported exception in InstallationObjectImplementation::handleStructureAddMaintenance\n";
	}
}
void InstallationObjectImplementation::handleStructureAddEnergy(Player* player) {
	try
	{
		stringstream ssTotalEnergy;

		player->setCurrentStructureID(this->getObjectID());

		SuiTransferBox* energyBox = new SuiTransferBox(player, 0x7285);
		energyBox->setPromptTitle("Add Power");

		energyBox->setPromptText("Select the amount of power you would like to deposit"
				"\n\nCurrent power Value: " + energy);

		ssTotalEnergy << "100";

		energyBox->addFrom("@player_structure:total_energy", ssTotalEnergy.str(), ssTotalEnergy.str(), "1");
		energyBox->addTo("@player_structure:to_deposit", "0", "0", "1");

		player->addSuiBox(energyBox);
		player->sendMessage(energyBox->generateMessage());

	}
	catch(...) {
		cout << "unreported exception in InstallationObjectImplementation::handleStructureAddEnergy\n";
	}
}

