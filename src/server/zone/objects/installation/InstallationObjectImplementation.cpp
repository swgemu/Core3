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

#include "engine/engine.h"

#include "../../objects.h"

#include "events/InstallationSyncUIEvent.h"

#include "../../managers/planet/PlanetManager.h"
#include "../../managers/structure/StructureManager.h"



InstallationObjectImplementation::InstallationObjectImplementation(uint64 oid) : InstallationObjectServant(oid, INSTALLATION) {
	objectID = oid;

	init();
}

InstallationObjectImplementation::InstallationObjectImplementation(uint64 oid, DeedObject * deed) : InstallationObjectServant(oid, INSTALLATION) {
	// Global Init
	init();

	objectID = oid;
	objectCRC = deed->getTargetFile().hashCode();
	objectSubType = getObjectSubType();
	name = deed->getTargetName();
	file = deed->getTargetFile();
	templateName = deed->getTargetTemplate();

	/*maintenance = deed->getSurplusMaintenance();
	energy = deed->getSurplusPower();
	maintenanceRate = deed->getMaintenanceRate();*/
}

InstallationObjectImplementation::~InstallationObjectImplementation() {

	if (syncEvent != NULL) {
		if (syncEvent->isQueued())
			server->removeEvent(syncEvent);

		delete syncEvent;
		syncEvent = NULL;
	}

}

void InstallationObjectImplementation::init() {
	container = NULL;
	zone = NULL;

	persistent = false;
	updated = false;

	ownerID = 0;

	building = NULL;

	// INSO6 operands
	defenderUpdateCounter = 0;
	defenderID = 0;

	objectCount = 0;
	setLotSize(1); // everything defaults to 1

	structureStatus = "private";

	setSurplusPower(0);
	setPowerRate(45);

	setSurplusMaintenance(3000);
	setMaintenanceRate(45);

	setOperating(false);

	conditionDamage = 0;
	maxCondition = 1000;

	objectType = SceneObjectImplementation::TANGIBLE;
	objectSubType = TangibleObjectImplementation::INSTALLATION;

	equipped = false;

	pvpStatusBitmask = 0;



	syncEvent = new InstallationSyncUIEvent(this);
}

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

void InstallationObjectImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if(getOwnerID() == player->getCharacterID())
	{
		omr->addRadialItem(0, 122, 1, "@player_structure:management");
		omr->addRadialItem(2, 132, 3, "@player_structure:permission_destroy");
		omr->addRadialItem(2, 128, 3, "@player_structure:management_status");
		omr->addRadialItem(2, 131, 3, "Set Name"); //"@player_structure:set_name"
		omr->addRadialItem(2, 133, 3, "@player_structure:management_pay");
		if (objectSubType == TangibleObjectImplementation::HARVESTER ||
				objectSubType == TangibleObjectImplementation::GENERATOR)
			omr->addRadialItem(2, 82, 3, "@harvester:manage");
		if(objectSubType == TangibleObjectImplementation::HARVESTER)
			omr->addRadialItem(2, 77, 3, "@player_structure:management_power");
	}

	omr->finish();
	player->sendMessage(omr);
}


void InstallationObjectImplementation::handleStructureRedeed(Player * player) {
	try {

		player->setCurrentStructureID(this->getObjectID());

		StringBuffer sscan, sscond, ssmain;
		String willRedeed;

		if ((conditionDamage == 0) && (getSurplusMaintenance() >= (getMaintenanceRate() * 100))) {

			sscan << "CAN REDEED: \\#32CD32YES\\#";
			willRedeed = "\\#32CD32YES\\#";

			sscond << dec << "- CONDITION: \\#32CD32" << maxCondition - conditionDamage << "/" << maxCondition << "\\#";
			ssmain << dec << "- MAINTENANCE: \\#32CD32" << static_cast<int>(getSurplusMaintenance()) << "/" << static_cast<int>((getMaintenanceRate() * 100)) << "\\#";

		}
		else {

			sscan << "CAN REDEED: \\#FF6347NO\\#";
			willRedeed = "\\#FF6347NO\\##";

			if ((conditionDamage == 0)) {

				sscond << dec << "- CONDITION: \\#32CD32"<< maxCondition - conditionDamage << "/" << maxCondition << "\\#";
				ssmain << dec << "- MAINTENANCE: \\#FF6347" << static_cast<int>(getSurplusMaintenance()) << "/" << static_cast<int>((getMaintenanceRate() * 100)) << "\\#";

			}
			else {

				sscond << dec << "- CONDITION: \\#FF6347" << maxCondition - conditionDamage << "/" << maxCondition << "\\#";
				ssmain << dec << "- MAINTENANCE: \\#FF6347" << static_cast<int>(getSurplusMaintenance()) << "/" << static_cast<int>((getMaintenanceRate() * 100)) << "\\#";

			}
		}

		SuiListBox* redeedBox = new SuiListBox(player, SuiWindowType::INSTALLATION_REDEED, 0x02);

		redeedBox->setPromptTitle(this->getName().toString());

		redeedBox->setPromptText("You have elected to destroy a structure.  Pertinent structure"
				" data can be found in the list below.  Please complete the following steps"
				" to confirm structure deletion.\n\nIf you wish to redeed your structure, all"
				" structure data must be \\#32CD32GREEN\\#       \\#93F5FFTo continue with structure deletion"
				", click YES.  Otherwise, please click NO.\nWILL REDEED: " + willRedeed);

		redeedBox->addMenuItem(sscan.toString());
		redeedBox->addMenuItem(sscond.toString());
		redeedBox->addMenuItem(ssmain.toString());

		player->addSuiBox(redeedBox);
		player->sendMessage(redeedBox->generateMessage());

	}
	catch(...) {
		System::out << "unreported exception in InstallationObjectImplementation::handleStructureRedeed\n";
	}
}

void InstallationObjectImplementation::handleStructureRedeedConfirm(Player * player) {
	try {
		String status;
		StringBuffer prompt;

		destroyCode = (System::random(999999) + 100000);

		SuiInputBox * confirmRedeed = new SuiInputBox(player, SuiWindowType::INSTALLATION_REDEED_CONFIRM, 0x00);

		confirmRedeed->setPromptTitle("Confirm Structure Destruction");

		if ((conditionDamage == 0) && (getSurplusMaintenance() >= (getMaintenanceRate() * 100))) {
			status = "\\#32CD32WILL\\#       \\#93F5FF";
		}
		else{
			status = "\\#FF6347WILL NOT\\#       \\#93F5FF";
		}

		prompt << dec << "Your structure " << status << " be redeeded.  If you wish"
		<< " to continue with destroying your structure, please enter the following code"
		<<" into the input box.\n\nCode: " << destroyCode;

		confirmRedeed->setPromptText(prompt.toString());

		player->addSuiBox(confirmRedeed);
		player->sendMessage(confirmRedeed->generateMessage());

	}
	catch(...) {
		System::out << "unreported exception in InstallationObjectImplementation::handleStructureRedeedConfirm\n";
	}

}

void InstallationObjectImplementation::handleMakeDeed(Player* player) {
	info("InstallationObjectImplementation::handleMakeDeed");

	if ((conditionDamage == 0) && (getSurplusMaintenance() >= (getMaintenanceRate() * 100)))
	{
		DeedObject* deed = NULL;
		// create a deed

		switch(getObjectSubType()) {
		case TangibleObjectImplementation::GENERATOR:
		case TangibleObjectImplementation::HARVESTER:
		{
			deed = new HarvesterDeed((CreatureObject*)player, (HarvesterObject*)_this);
		}
		case TangibleObjectImplementation::FACTORY:
		default:
			break;
			//HarvesterDeedImplementation(CreatureObject* creature, HarvesterObject* hino)
		}

		if(deed == NULL)
			return;


		player->addInventoryItem(deed);
		deed->sendTo(player);
	}

	int lots = player->getLotsRemaining();
	lots += getLotSize();
	player->setLotsRemaining(lots);

	//player->clearTarget();

	Zone *zn = getZone();
	if(zn == NULL)
	{
		info("zone is null...bleh");
	} else {
		PlanetManager* planetManager = zn->getPlanetManager();
		StructureManager* structureManager = planetManager->getStructureManager();
		structureManager->deleteInstallation(_this);
	}

	//deleteInstallation does these:
	//removeFromZone(true);
	//finalize();
}

void InstallationObjectImplementation::handleStructureStatus(Player* player) {
	try
	{
		player->setCurrentStructureID(this->getObjectID());

		StringBuffer sscond, ssmpool, ssmrate, ssppool, ssprate;

		SuiListBox* statusBox = new SuiListBox(player, SuiWindowType::INSTALLATION_STATUS, 0x01);
		statusBox->setPromptTitle("@player_structure:structure_status_t");
		statusBox->setPromptText("Structure Name: " + getName().toString());

		statusBox->addMenuItem("Owner: " + owner);
		statusBox->addMenuItem("This structure is " + structureStatus);

		sscond << dec << "Condition: " << ((int) (((maxCondition - conditionDamage) / maxCondition) * 100)) << "%";
		statusBox->addMenuItem(sscond.toString());

		ssmpool << dec << "Maintenance Pool: " << (int) getSurplusMaintenance();
		statusBox->addMenuItem(ssmpool.toString());

		ssmrate << dec << "Maintenance Rate: " << (int) getMaintenanceRate() << " cr/hr";
		statusBox->addMenuItem(ssmrate.toString());

		ssppool << dec << "Power Reserves: " << (int) getSurplusPower();
		statusBox->addMenuItem(ssppool.toString());

		ssprate << dec << "Power Consumption " << (int) getPowerRate() << " units/hr";
		statusBox->addMenuItem(ssprate.toString());

		player->addSuiBox(statusBox);
		player->sendMessage(statusBox->generateMessage());
	} catch(...) {
		System::out << "unreported exception in InstallationObjectImplementation::handleStructureStatus\n";
	}
}

void InstallationObjectImplementation::handleStructureManageMaintenance(Player* player) {
	try {
		StringBuffer sstext, sscash, ssmaintenance;

		player->setCurrentStructureID(this->getObjectID());

		SuiTransferBox* maintenanceBox = new SuiTransferBox(player, SuiWindowType::MANAGE_MAINTENANCE);
		maintenanceBox->setPromptTitle("Select Amount");

		sstext << "Select the total amount you would like to pay the existing"
			   <<" maintenace pool.\n\nCurrent maintanence pool: " << (int)getSurplusMaintenance() << "cr.";
		maintenanceBox->setPromptText(sstext.toString());

		sscash << player->getCashCredits();
		ssmaintenance << getSurplusMaintenance();

		maintenanceBox->addFrom("@player_structure:total_funds", sscash.toString(), sscash.toString(), "1");
		maintenanceBox->addTo("@player_structure:to_pay", ssmaintenance.toString(), ssmaintenance.toString(), "1");

		player->addSuiBox(maintenanceBox);
		player->sendMessage(maintenanceBox->generateMessage());

	}
	catch(...) {
		System::out << "unreported exception in InstallationObjectImplementation::handleStructureManageMaintenance\n";
	}
}
void InstallationObjectImplementation::handleStructureAddEnergy(Player* player) {
	try
	{
		StringBuffer sstext, ssTotalEnergy;

		player->setCurrentStructureID(this->getObjectID());

		SuiTransferBox* energyBox = new SuiTransferBox(player, SuiWindowType::ADD_ENERGY);
		energyBox->setPromptTitle("Add Power");

		sstext	<< "Select the amount of power you would like to deposit."
				<<"\n\nCurrent power Value: " << (int)getSurplusPower();

		energyBox->setPromptText(sstext.toString());

		ssTotalEnergy << player->getAvailablePower();

		energyBox->addFrom("@player_structure:total_energy", ssTotalEnergy.toString(), ssTotalEnergy.toString(), "1");
		energyBox->addTo("@player_structure:to_deposit", "0", "0", "1");

		player->addSuiBox(energyBox);
		player->sendMessage(energyBox->generateMessage());

	}
	catch(...) {
		System::out << "unreported exception in InstallationObjectImplementation::handleStructureAddEnergy\n";
	}
}




void InstallationObjectImplementation::setCombatState() {
	/*lastCombatAction.update();

	if (!(stateBitmask & COMBAT_STATE)) {
		stateBitmask |= COMBAT_STATE;

		if (stateBitmask & PEACE_STATE)
			stateBitmask &= ~PEACE_STATE;

		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->update06Operand(0x80);
		dcreo3->updateState();
		dcreo3->close();

		broadcastMessage(dcreo3);

		if (postureState == SITTING_POSTURE)
			setPosture(UPRIGHT_POSTURE);
	}*/
}


void InstallationObjectImplementation::setDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	setCombatState();

	ManagedReference<SceneObject> temp = NULL;

	int i = 0;
	for (; i < defenderList.size(); i++) {
		if (defenderList.get(i) == defender) {
			if (i == 0)
				return;

			temp = defenderList.get(0);

			defenderList.set(0, defender);
			defenderList.set(i, temp);

			break;
		}
	}

	InstallationObjectDeltaMessage6* dinso6 = new InstallationObjectDeltaMessage6((InstallationObject*) _this);
	if (temp != NULL) {
		dinso6->startDefenderUpdate(2);
		dinso6->setDefender(i, temp->getObjectID());
		dinso6->setDefender(0, defender->getObjectID());
	} else {
		dinso6->startDefenderUpdate(1);
		dinso6->addDefender(defenderList.size(), defender->getObjectID());

		defenderList.add(defender);
	}

	dinso6->close();

	broadcastMessage(dinso6);
}

void InstallationObjectImplementation::addDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	setCombatState();

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defender == defenderList.get(i))
			return;
	}

	info("adding defender");

	defenderList.add(defender);

	InstallationObjectDeltaMessage6* dinso6 = new InstallationObjectDeltaMessage6((InstallationObject*) _this);
	dinso6->startDefenderUpdate(1);
	dinso6->addDefender(defenderList.size() - 1, defender->getObjectID());
	dinso6->close();

	broadcastMessage(dinso6);
}

void InstallationObjectImplementation::removeDefenders() {
	info("removing all defenders");
	if (defenderList.size() == 0) {
		//info("no defenders in list");
		return;
	}

	InstallationObjectDeltaMessage6* dinso6 = new InstallationObjectDeltaMessage6((InstallationObject*) _this);
	dinso6->startDefenderUpdate(1);

	dinso6->removeDefenders();
	dinso6->close();

	broadcastMessage(dinso6);

	defenderList.removeAll();

	info("removed all defenders");
}

void InstallationObjectImplementation::removeDefender(SceneObject* defender) {
	if (zone == NULL)
		return;

	//info("trying to remove defender");
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender) {
			defenderList.remove(i);

			info("removing defender");

			InstallationObjectDeltaMessage6* dinso6 = new InstallationObjectDeltaMessage6((InstallationObject*) _this);
			dinso6->startDefenderUpdate(1);

			if (defenderList.size() == 0)
				dinso6->removeDefenders();
			else
				dinso6->removeDefender(i);

			dinso6->close();

			broadcastMessage(dinso6);

			//info("defender found and removed");
			break;
		}
	}

	if (defenderList.size() == 0)
		clearCombatState(false);

	//info("finished removing defender");
}

bool InstallationObjectImplementation::hasDefender(SceneObject* defender) {
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender)
			return true;
	}
	return false;
}


void InstallationObjectImplementation::clearCombatState(bool removedefenders) {
	//info("trying to clear CombatState");
	/*if (stateBitmask & COMBAT_STATE) {
		if (stateBitmask & PEACE_STATE)
			stateBitmask &= ~PEACE_STATE;

		stateBitmask &= ~COMBAT_STATE;

		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->update06Operand(0x80);
		dcreo3->updateState();
		dcreo3->close();

		broadcastMessage(dcreo3);
	}*/

	if (removedefenders)
		removeDefenders();

	//info("finished clearCombatState");
}

void InstallationObjectImplementation::activateSync() {
	if (syncEvent != NULL && !syncEvent->isQueued())
		server->addEvent(syncEvent, 5000); // 5 seconds
}

int InstallationObjectImplementation::getObjectSubType() {

	switch(objectCRC) {
		case 0x4C850DFE: //object/installation/generators/shared_power_generator_fusion_style_1.iff
		case 0x8CE44BBB: //object/installation/generators/shared_power_generator_photo_bio_style_1.iff
		case 0x3341B027: //object/installation/generators/shared_power_generator_solar_style_1.iff
		case 0xAED007BF: //object/installation/generators/shared_power_generator_wind_style_1.iff
			return TangibleObjectImplementation::GENERATOR;
		case 0x796D7553: //object/installation/manufacture/shared_clothing_factory.iff
		case 0x941776B2: //object/installation/manufacture/shared_food_factory.iff
		case 0x5CC7670B: //object/installation/manufacture/shared_structure_factory.iff
		case 0x4DBD9DFC: //object/installation/manufacture/shared_weapon_factory.iff
		case 0x18C4BED3: //object/installation/manufacture/shared_weapon_installation.iff
			return TangibleObjectImplementation::FACTORY;
		case 0xCD68D9C7: //object/installation/mining_gas/shared_mining_gas_harvester_style_1.iff
		case 0x167F7150: //object/installation/mining_gas/shared_mining_gas_harvester_style_2.iff
		case 0x5F7216DD: //object/installation/mining_gas/shared_mining_gas_harvester_style_3.iff
		case 0x7824E0B0: //object/installation/mining_liquid/shared_mining_liquid_harvester_style_1.iff
		case 0xA3334827: //object/installation/mining_liquid/shared_mining_liquid_harvester_style_2.iff
		case 0xEA3E2FAA: //object/installation/mining_liquid/shared_mining_liquid_harvester_style_3.iff
		case 0x8540F576: //object/installation/mining_liquid/shared_mining_liquid_moisture_harvester.iff
		case 0x4DD087FE: //object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_heavy.iff
		case 0xBBE35A9A: //object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_medium.iff
		case 0x85ADD4EA: //object/installation/mining_ore/construction/shared_construction_mining_ore_harvester_style_1.iff
		case 0x5EBA7C7D: //object/installation/mining_ore/construction/shared_construction_mining_ore_harvester_style_2.iff
		case 0x41C7616F: //object/installation/mining_ore/construction/shared_construction_mining_ore_harvester_style_heavy.iff
		case 0x403FD0B1: //object/installation/mining_ore/shared_mining_ore_harvester_heavy.iff
		case 0x667FADDA: //object/installation/mining_ore/shared_mining_ore_harvester_style_1.iff
		case 0xBD68054D: //object/installation/mining_ore/shared_mining_ore_harvester_style_2.iff
		case 0xCCFA21C4: //object/installation/mining_organic/shared_mining_organic_flora_farm.iff
		case 0x3481BD07: //object/installation/mining_organic/shared_mining_organic_flora_farm_heavy.iff
		case 0x28A44E72: //object/installation/mining_organic/shared_mining_organic_flora_farm_medium.iff
			return TangibleObjectImplementation::HARVESTER;

		case 0x84425787: //object/installation/faction_perk/covert_detector/shared_detector_base.iff
		case 0x4EC91AA6: //object/installation/faction_perk/minefield/base/shared_minefield_base.iff
		case 0x757889EA: //object/installation/faction_perk/minefield/shared_field_1x1.iff
		case 0x6EE2514F: //object/installation/faction_perk/turret/base/shared_faction_turret_base.iff
		case 0x884DC0A5: //object/installation/faction_perk/turret/shared_block_lg.iff
		case 0x6F719708: //object/installation/faction_perk/turret/shared_block_med.iff
		case 0x75678B26: //object/installation/faction_perk/turret/shared_block_sm.iff
		case 0x5E3D2244: //object/installation/faction_perk/turret/shared_dish_lg.iff
		case 0xA31769C7: //object/installation/faction_perk/turret/shared_dish_sm.iff
		case 0xD6D6D17D: //object/installation/faction_perk/turret/shared_tower_lg.iff
		case 0xB0794405: //object/installation/faction_perk/turret/shared_tower_med.iff
		case 0x2BFC9AFE: //object/installation/faction_perk/turret/shared_tower_sm.iff
		case 0xE8896311: //object/installation/turret/shared_turret_block_large.iff
		case 0x627BA6F8: //object/installation/turret/shared_turret_block_med.iff
		case 0xE7461E17: //object/installation/turret/shared_turret_block_sm.iff
		case 0xFC1FD7F: //object/installation/turret/shared_turret_dish_large.iff
		case 0xD94A7699: //object/installation/turret/shared_turret_dish_sm.iff
		case 0x73909C46: //object/installation/turret/shared_turret_tower_large.iff
		case 0xBD7375F5: //object/installation/turret/shared_turret_tower_med.iff
		case 0xB9DD0FCF: //object/installation/turret/shared_turret_tower_sm.iff
			return TangibleObjectImplementation::TURRET;

		case 0x2073410C: //object/installation/base/shared_construction_installation_base.iff
		case 0x5FFEAE33: //object/installation/base/shared_installation_base.iff
		case 0xF6A8B139: //object/installation/base/shared_installation_default.iff
		case 0x1F8F9631: //object/installation/battlefield/destructible/barracks/shared_bfield_gungan_barracks.iff
		case 0x2C6E39C8: //object/installation/battlefield/destructible/barracks/shared_bfield_nightsister_barracks.iff
		case 0xE5C2212C: //object/installation/battlefield/destructible/barracks/shared_rebel_infantry_barracks.iff
		case 0xD5CCDFE2: //object/installation/battlefield/destructible/barracks/shared_storm_trooper_barracks.iff
		case 0xB6863EB5: //object/installation/battlefield/destructible/base/shared_base_destructible_building.iff
		case 0x86973547: //object/installation/battlefield/destructible/base/shared_construction_base_destructible_building.iff
		case 0x3C3D91E3: //object/installation/battlefield/destructible/shared_antenna_tatt_style_1.iff
		case 0xE72A3974: //object/installation/battlefield/destructible/shared_antenna_tatt_style_2.iff
		case 0x94A22382: //object/installation/battlefield/destructible/shared_battlefield_constructor.iff
		case 0x79931BD3: //object/installation/battlefield/destructible/shared_bfield_banner_freestand_impl.iff
		case 0x1F0DAF59: //object/installation/battlefield/destructible/shared_bfield_banner_freestand_rebl.iff
		case 0x9C0B080B: //object/installation/battlefield/destructible/shared_bfield_base_gate_impl.iff
		case 0x9E3CA589: //object/installation/battlefield/destructible/shared_bfield_column_imperial.iff
		case 0x4CB0BE85: //object/installation/battlefield/destructible/shared_bfield_column_impl_med.iff
		case 0xA613F447: //object/installation/battlefield/destructible/shared_bfield_column_impl_weak.iff
		case 0xC15435A1: //object/installation/battlefield/destructible/shared_bfield_column_rebel.iff
		case 0xFDB36A1B: //object/installation/battlefield/destructible/shared_bfield_column_rebl_med.iff
		case 0x83478B5B: //object/installation/battlefield/destructible/shared_bfield_column_rebl_strong.iff
		case 0x1C38FA8E: //object/installation/battlefield/destructible/shared_bfield_column_rebl_weak.iff
		case 0xDE11CE25: //object/installation/battlefield/destructible/shared_bfield_column_strong.iff
		case 0xCEADD0B7: //object/installation/battlefield/destructible/shared_bfield_gungan_cleft_wall_lg.iff
		case 0x7B865016: //object/installation/battlefield/destructible/shared_bfield_gungan_damaged_narrow_arch.iff
		case 0xBA6D6964: //object/installation/battlefield/destructible/shared_bfield_gungan_damaged_wall_lg.iff
		case 0xBBB0FEC9: //object/installation/battlefield/destructible/shared_bfield_gungan_damaged_wide_arch.iff
		case 0xAA8B1323: //object/installation/battlefield/destructible/shared_bfield_gungan_pillar_damaged.iff
		case 0xB59C0185: //object/installation/battlefield/destructible/shared_bfield_gungan_pillar_ruined.iff
		case 0xC5BEDD83: //object/installation/battlefield/destructible/shared_bfield_gungan_relic.iff
		case 0xC257877B: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s01a.iff
		case 0x19402FEC: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s01b.iff
		case 0xEF2F90F3: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s02a.iff
		case 0x34383864: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s02b.iff
		case 0x8FB419A7: //object/installation/battlefield/destructible/shared_bfield_gungan_target_shield_gen.iff
		case 0xFFAAF535: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_lg_s01.iff
		case 0x24BD5DA2: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_lg_s02.iff
		case 0x271B66BB: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_sm_s01.iff
		case 0xFC0CCE2C: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_sm_s02.iff
		case 0x4768C16F: //object/installation/battlefield/destructible/shared_bfield_nightsister_fence.iff
		case 0x2A73874F: //object/installation/battlefield/destructible/shared_bfield_nightsister_freestand_banner01.iff
		case 0xF1642FD8: //object/installation/battlefield/destructible/shared_bfield_nightsister_freestand_banner02.iff
		case 0xB8694855: //object/installation/battlefield/destructible/shared_bfield_nightsister_freestand_banner03.iff
		case 0xA6382D47: //object/installation/battlefield/destructible/shared_bfield_nightsister_gate.iff
		case 0x5614507D: //object/installation/battlefield/destructible/shared_bfield_nightsister_hut.iff
		case 0xB97E20DA: //object/installation/battlefield/destructible/shared_bfield_nightsister_target_sith_altar.iff
		case 0x1CD51413: //object/installation/battlefield/destructible/shared_bfield_nightsister_target_sith_crystal.iff
		case 0xE25046B9: //object/installation/battlefield/destructible/shared_bfield_nightsister_target_tower.iff
		case 0x8EA83D5F: //object/installation/battlefield/destructible/shared_bfield_target_power_generator.iff
		case 0xDA25F494: //object/installation/battlefield/destructible/shared_bfield_target_power_transformer_01.iff
		case 0x1325C03: //object/installation/battlefield/destructible/shared_bfield_target_power_transformer_02.iff
		case 0xFDFBCE11: //object/installation/battlefield/destructible/shared_bfield_wall_barbed.iff
		case 0x7E7DBA97: //object/installation/battlefield/destructible/shared_bfield_wall_connector.iff
		case 0xB721EDA7: //object/installation/battlefield/destructible/shared_bfield_wall_impl_weak.iff
		case 0xA88680EF: //object/installation/battlefield/destructible/shared_bfield_wall_med.iff
		case 0xDD3A7BB4: //object/installation/battlefield/destructible/shared_bfield_wall_rebl_med.iff
		case 0x855F876A: //object/installation/battlefield/destructible/shared_bfield_wall_rebl_strong.iff
		case 0xD0AE36E: //object/installation/battlefield/destructible/shared_bfield_wall_rebl_weak.iff
		case 0x57B0C19F: //object/installation/battlefield/destructible/shared_bfield_wall_strong.iff
		case 0x95EBC3AD: //object/installation/battlefield/destructible/shared_gungan_sacred_head.iff
		case 0xF92C990B: //object/installation/battlefield/destructible/shared_imperial_gate_house.iff
		case 0xD8C935AC: //object/installation/battlefield/destructible/shared_rebel_gate_house.iff
		case 0x192CFC8C: //object/installation/battlefield/destructible/shared_small_turret.iff
		case 0xC7D47F9: //object/installation/battlefield/destructible/shared_turret_dish_small.iff
		case 0x2AD09AFA: //object/installation/battlefield/destructible/shared_turret_tower_small.iff
		default:
			return TangibleObjectImplementation::INSTALLATION;

	}
}

uint32 InstallationObjectImplementation::getDeedCRC() {
	switch(objectCRC) {
		// Generators
		case 0x4C850DFE: //object/installation/generators/shared_power_generator_fusion_style_1.iff
			return 0xE5A0F395; //object/tangible/deed/generator_deed/shared_generator_fusion_deed.iff
		case 0x8CE44BBB: //object/installation/generators/shared_power_generator_photo_bio_style_1.iff
			return 0x26D63643; //object/tangible/deed/generator_deed/shared_generator_photo_bio_deed.iff
		case 0x3341B027: //object/installation/generators/shared_power_generator_solar_style_1.iff
			return 0x4669B528; //object/tangible/deed/generator_deed/shared_generator_solar_deed.iff
		case 0xAED007BF: //object/installation/generators/shared_power_generator_wind_style_1.iff
			return 0xE6C711A7; //object/tangible/deed/generator_deed/shared_generator_wind_deed.iff

		// Factories
		case 0x796D7553: //object/installation/manufacture/shared_clothing_factory.iff
			return 0x6C0893E5; //object/tangible/deed/factory_deed/shared_factory_clothing_deed.iff
		case 0x941776B2: //object/installation/manufacture/shared_food_factory.iff
			return 0xCFEC24E5; //object/tangible/deed/factory_deed/shared_factory_food_deed.iff
		case 0x5CC7670B: //object/installation/manufacture/shared_structure_factory.iff
			return 0x8E331C08; //object/tangible/deed/factory_deed/shared_factory_structure_deed.if
		case 0x4DBD9DFC: //object/installation/manufacture/shared_weapon_factory.iff
		case 0x18C4BED3: //object/installation/manufacture/shared_weapon_installation.iff
			return 0xFD1EF87A; //object/tangible/deed/factory_deed/shared_factory_item_deed.iff

		// Harvesters
		case 0xCD68D9C7: //object/installation/mining_gas/shared_mining_gas_harvester_style_1.iff
			return 0x85020A19; //object/tangible/deed/harvester_deed/shared_harvester_gas_deed.iff
		case 0x167F7150: //object/installation/mining_gas/shared_mining_gas_harvester_style_2.iff
			return 0xB247C54E; //object/tangible/deed/harvester_deed/shared_harvester_gas_deed_medium.iff
		case 0x5F7216DD: //object/installation/mining_gas/shared_mining_gas_harvester_style_3.iff
			return 0x1090794C; //object/tangible/deed/harvester_deed/shared_harvester_gas_deed_heavy.iff
		case 0x7824E0B0: //object/installation/mining_liquid/shared_mining_liquid_harvester_style_1.iff
			return 0xC6CF0E82; //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed.iff
		case 0xA3334827: //object/installation/mining_liquid/shared_mining_liquid_harvester_style_2.iff
			return 0xC42B47F4; //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_medium.iff
		case 0xEA3E2FAA: //object/installation/mining_liquid/shared_mining_liquid_harvester_style_3.iff
			return 0x4FA6CDD8; //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_heavy.iff
		case 0x8540F576: //object/installation/mining_liquid/shared_mining_liquid_moisture_harvester.iff
			return 0x5E1B48A7; //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed.iff
		case 0xBBE35A9A: //object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_medium.iff
			return 0x2D4A2C89; //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_medium.iff
		case 0x4DD087FE: //object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_heavy.iff
			return 0x0147A463; //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_heavy.iff
		case 0x667FADDA: //object/installation/mining_ore/shared_mining_ore_harvester_style_1.iff
			return 0x7EB8541F; //object/tangible/deed/harvester_deed/shared_harvester_ore_s1_deed.iff
		case 0xBD68054D: //object/installation/mining_ore/shared_mining_ore_harvester_style_2.iff
			return 0xFBC8A901; //object/tangible/deed/harvester_deed/shared_harvester_ore_s2_deed.iff
		case 0x403FD0B1: //object/installation/mining_ore/shared_mining_ore_harvester_heavy.iff
			return 0xC02EBAB3; //object/tangible/deed/harvester_deed/shared_harvester_ore_heavy_deed.iff
		case 0xCCFA21C4: //object/installation/mining_organic/shared_mining_organic_flora_farm.iff
			return 0xA9557114; //object/tangible/deed/harvester_deed/shared_harvester_flora_deed.iff
		case 0x28A44E72: //object/installation/mining_organic/shared_mining_organic_flora_farm_medium.iff
			return 0x522BE74D; //object/tangible/deed/harvester_deed/shared_harvester_flora_deed_medium.iff
		case 0x3481BD07: //object/installation/mining_organic/shared_mining_organic_flora_farm_heavy.iff
			return 0xEEC52333; //object/tangible/deed/harvester_deed/shared_harvester_flora_deed_heavy.iff

		// Faction
		case 0x84425787: //object/installation/faction_perk/covert_detector/shared_detector_base.iff
			return 0xC786298D; //object/tangible/deed/faction_perk/covert_detector/shared_detector_32m_deed.iff

		case 0x4EC91AA6: //object/installation/faction_perk/minefield/base/shared_minefield_base.iff
		case 0x757889EA: //object/installation/faction_perk/minefield/shared_field_1x1.iff
			return 0x5D30CDF7; //object/tangible/deed/faction_perk/minefield/shared_field_1x1_deed.iff
		case 0x6EE2514F: //object/installation/faction_perk/turret/base/shared_faction_turret_base.iff

		case 0x884DC0A5: //object/installation/faction_perk/turret/shared_block_lg.iff
			return 0xF07B2F6E; //object/tangible/deed/faction_perk/turret/shared_dish_lg_deed.iff
		case 0x6F719708: //object/installation/faction_perk/turret/shared_block_med.iff
			return 0xFBA00806; //object/tangible/deed/faction_perk/turret/shared_block_med_deed.iff
		case 0x75678B26: //object/installation/faction_perk/turret/shared_block_sm.iff
			return 0xA3878091; //object/tangible/deed/faction_perk/turret/shared_block_sm_deed.iff

		case 0x5E3D2244: //object/installation/faction_perk/turret/shared_dish_lg.iff
			return 0xF07B2F6E; //object/tangible/deed/faction_perk/turret/shared_dish_lg_deed.iff
		case 0xA31769C7: //object/installation/faction_perk/turret/shared_dish_sm.iff
			return 0x767B073F; //object/tangible/deed/faction_perk/turret/shared_dish_sm_deed.iff

		case 0xD6D6D17D: //object/installation/faction_perk/turret/shared_tower_lg.iff
			return 0xDE76DCB5; //object/tangible/deed/faction_perk/turret/shared_tower_lg_deed.iff
		case 0xB0794405: //object/installation/faction_perk/turret/shared_tower_med.iff
			return 0xA8274B6E; //object/tangible/deed/faction_perk/turret/shared_tower_med_deed.iff
		case 0x2BFC9AFE: //object/installation/faction_perk/turret/shared_tower_sm.iff
			return 0x5876F4E4; //object/tangible/deed/faction_perk/turret/shared_tower_sm_deed.iff

		case 0x2073410C: //object/installation/base/shared_construction_installation_base.iff
		case 0x5FFEAE33: //object/installation/base/shared_installation_base.iff
		case 0xF6A8B139: //object/installation/base/shared_installation_default.iff
		case 0x1F8F9631: //object/installation/battlefield/destructible/barracks/shared_bfield_gungan_barracks.iff
		case 0x2C6E39C8: //object/installation/battlefield/destructible/barracks/shared_bfield_nightsister_barracks.iff
		case 0xE5C2212C: //object/installation/battlefield/destructible/barracks/shared_rebel_infantry_barracks.iff
		case 0xD5CCDFE2: //object/installation/battlefield/destructible/barracks/shared_storm_trooper_barracks.iff
		case 0xB6863EB5: //object/installation/battlefield/destructible/base/shared_base_destructible_building.iff
		case 0x86973547: //object/installation/battlefield/destructible/base/shared_construction_base_destructible_building.iff
		case 0x3C3D91E3: //object/installation/battlefield/destructible/shared_antenna_tatt_style_1.iff
		case 0xE72A3974: //object/installation/battlefield/destructible/shared_antenna_tatt_style_2.iff
		case 0x94A22382: //object/installation/battlefield/destructible/shared_battlefield_constructor.iff
		case 0x79931BD3: //object/installation/battlefield/destructible/shared_bfield_banner_freestand_impl.iff
		case 0x1F0DAF59: //object/installation/battlefield/destructible/shared_bfield_banner_freestand_rebl.iff
		case 0x9C0B080B: //object/installation/battlefield/destructible/shared_bfield_base_gate_impl.iff
		case 0x9E3CA589: //object/installation/battlefield/destructible/shared_bfield_column_imperial.iff
		case 0x4CB0BE85: //object/installation/battlefield/destructible/shared_bfield_column_impl_med.iff
		case 0xA613F447: //object/installation/battlefield/destructible/shared_bfield_column_impl_weak.iff
		case 0xC15435A1: //object/installation/battlefield/destructible/shared_bfield_column_rebel.iff
		case 0xFDB36A1B: //object/installation/battlefield/destructible/shared_bfield_column_rebl_med.iff
		case 0x83478B5B: //object/installation/battlefield/destructible/shared_bfield_column_rebl_strong.iff
		case 0x1C38FA8E: //object/installation/battlefield/destructible/shared_bfield_column_rebl_weak.iff
		case 0xDE11CE25: //object/installation/battlefield/destructible/shared_bfield_column_strong.iff
		case 0xCEADD0B7: //object/installation/battlefield/destructible/shared_bfield_gungan_cleft_wall_lg.iff
		case 0x7B865016: //object/installation/battlefield/destructible/shared_bfield_gungan_damaged_narrow_arch.iff
		case 0xBA6D6964: //object/installation/battlefield/destructible/shared_bfield_gungan_damaged_wall_lg.iff
		case 0xBBB0FEC9: //object/installation/battlefield/destructible/shared_bfield_gungan_damaged_wide_arch.iff
		case 0xAA8B1323: //object/installation/battlefield/destructible/shared_bfield_gungan_pillar_damaged.iff
		case 0xB59C0185: //object/installation/battlefield/destructible/shared_bfield_gungan_pillar_ruined.iff
		case 0xC5BEDD83: //object/installation/battlefield/destructible/shared_bfield_gungan_relic.iff
		case 0xC257877B: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s01a.iff
		case 0x19402FEC: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s01b.iff
		case 0xEF2F90F3: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s02a.iff
		case 0x34383864: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s02b.iff
		case 0x8FB419A7: //object/installation/battlefield/destructible/shared_bfield_gungan_target_shield_gen.iff
		case 0xFFAAF535: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_lg_s01.iff
		case 0x24BD5DA2: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_lg_s02.iff
		case 0x271B66BB: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_sm_s01.iff
		case 0xFC0CCE2C: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_sm_s02.iff
		case 0x4768C16F: //object/installation/battlefield/destructible/shared_bfield_nightsister_fence.iff
		case 0x2A73874F: //object/installation/battlefield/destructible/shared_bfield_nightsister_freestand_banner01.iff
		case 0xF1642FD8: //object/installation/battlefield/destructible/shared_bfield_nightsister_freestand_banner02.iff
		case 0xB8694855: //object/installation/battlefield/destructible/shared_bfield_nightsister_freestand_banner03.iff
		case 0xA6382D47: //object/installation/battlefield/destructible/shared_bfield_nightsister_gate.iff
		case 0x5614507D: //object/installation/battlefield/destructible/shared_bfield_nightsister_hut.iff
		case 0xB97E20DA: //object/installation/battlefield/destructible/shared_bfield_nightsister_target_sith_altar.iff
		case 0x1CD51413: //object/installation/battlefield/destructible/shared_bfield_nightsister_target_sith_crystal.iff
		case 0xE25046B9: //object/installation/battlefield/destructible/shared_bfield_nightsister_target_tower.iff
		case 0x8EA83D5F: //object/installation/battlefield/destructible/shared_bfield_target_power_generator.iff
		case 0xDA25F494: //object/installation/battlefield/destructible/shared_bfield_target_power_transformer_01.iff
		case 0x1325C03: //object/installation/battlefield/destructible/shared_bfield_target_power_transformer_02.iff
		case 0xFDFBCE11: //object/installation/battlefield/destructible/shared_bfield_wall_barbed.iff
		case 0x7E7DBA97: //object/installation/battlefield/destructible/shared_bfield_wall_connector.iff
		case 0xB721EDA7: //object/installation/battlefield/destructible/shared_bfield_wall_impl_weak.iff
		case 0xA88680EF: //object/installation/battlefield/destructible/shared_bfield_wall_med.iff
		case 0xDD3A7BB4: //object/installation/battlefield/destructible/shared_bfield_wall_rebl_med.iff
		case 0x855F876A: //object/installation/battlefield/destructible/shared_bfield_wall_rebl_strong.iff
		case 0xD0AE36E: //object/installation/battlefield/destructible/shared_bfield_wall_rebl_weak.iff
		case 0x57B0C19F: //object/installation/battlefield/destructible/shared_bfield_wall_strong.iff
		case 0x95EBC3AD: //object/installation/battlefield/destructible/shared_gungan_sacred_head.iff
		case 0xF92C990B: //object/installation/battlefield/destructible/shared_imperial_gate_house.iff
		case 0xD8C935AC: //object/installation/battlefield/destructible/shared_rebel_gate_house.iff
		case 0x192CFC8C: //object/installation/battlefield/destructible/shared_small_turret.iff
		case 0xC7D47F9: //object/installation/battlefield/destructible/shared_turret_dish_small.iff
		case 0x2AD09AFA: //object/installation/battlefield/destructible/shared_turret_tower_small.iff
		default:
			return 0;

	}
}

/*
String& InstallationObjectImplementation::getDefaultTemplateName() {
	switch(objectCRC) {
		// Generators
		case 0x4C850DFE: //object/installation/generators/shared_power_generator_fusion_style_1.iff
			return 0xE5A0F395; //object/tangible/deed/generator_deed/shared_generator_fusion_deed.iff
		case 0x8CE44BBB: //object/installation/generators/shared_power_generator_photo_bio_style_1.iff
			return 0x26D63643; //object/tangible/deed/generator_deed/shared_generator_photo_bio_deed.iff
		case 0x3341B027: //object/installation/generators/shared_power_generator_solar_style_1.iff
			return 0x4669B528; //object/tangible/deed/generator_deed/shared_generator_solar_deed.iff
		case 0xAED007BF: //object/installation/generators/shared_power_generator_wind_style_1.iff
			return 0xE6C711A7; //object/tangible/deed/generator_deed/shared_generator_wind_deed.iff

		// Factories
		case 0x796D7553: //object/installation/manufacture/shared_clothing_factory.iff
			return 0x6C0893E5; //object/tangible/deed/factory_deed/shared_factory_clothing_deed.iff
		case 0x941776B2: //object/installation/manufacture/shared_food_factory.iff
			return 0xCFEC24E5; //object/tangible/deed/factory_deed/shared_factory_food_deed.iff
		case 0x5CC7670B: //object/installation/manufacture/shared_structure_factory.iff
			return 0x8E331C08; //object/tangible/deed/factory_deed/shared_factory_structure_deed.if
		case 0x4DBD9DFC: //object/installation/manufacture/shared_weapon_factory.iff
		case 0x18C4BED3: //object/installation/manufacture/shared_weapon_installation.iff
			return 0xFD1EF87A; //object/tangible/deed/factory_deed/shared_factory_item_deed.iff

		// Harvesters
		case 0xCD68D9C7: //object/installation/mining_gas/shared_mining_gas_harvester_style_1.iff
			return 0x85020A19; //object/tangible/deed/harvester_deed/shared_harvester_gas_deed.iff
		case 0x167F7150: //object/installation/mining_gas/shared_mining_gas_harvester_style_2.iff
			return 0xB247C54E; //object/tangible/deed/harvester_deed/shared_harvester_gas_deed_medium.iff
		case 0x5F7216DD: //object/installation/mining_gas/shared_mining_gas_harvester_style_3.iff
			return 0x1090794C; //object/tangible/deed/harvester_deed/shared_harvester_gas_deed_heavy.iff
		case 0x7824E0B0: //object/installation/mining_liquid/shared_mining_liquid_harvester_style_1.iff
			return 0xC6CF0E82; //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed.iff
		case 0xA3334827: //object/installation/mining_liquid/shared_mining_liquid_harvester_style_2.iff
			return 0xC42B47F4; //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_medium.iff
		case 0xEA3E2FAA: //object/installation/mining_liquid/shared_mining_liquid_harvester_style_3.iff
			return 0x4FA6CDD8; //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_heavy.iff
		case 0x8540F576: //object/installation/mining_liquid/shared_mining_liquid_moisture_harvester.iff
			return 0x5E1B48A7; //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed.iff
		case 0xBBE35A9A: //object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_medium.iff
			return 0x2D4A2C89; //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_medium.iff
		case 0x4DD087FE: //object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_heavy.iff
			return 0x0147A463; //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_heavy.iff
		case 0x667FADDA: //object/installation/mining_ore/shared_mining_ore_harvester_style_1.iff
			return 0x7EB8541F; //object/tangible/deed/harvester_deed/shared_harvester_ore_s1_deed.iff
		case 0xBD68054D: //object/installation/mining_ore/shared_mining_ore_harvester_style_2.iff
			return 0xFBC8A901; //object/tangible/deed/harvester_deed/shared_harvester_ore_s2_deed.iff
		case 0x403FD0B1: //object/installation/mining_ore/shared_mining_ore_harvester_heavy.iff
			return 0xC02EBAB3; //object/tangible/deed/harvester_deed/shared_harvester_ore_heavy_deed.iff
		case 0xCCFA21C4: //object/installation/mining_organic/shared_mining_organic_flora_farm.iff
			return 0xA9557114; //object/tangible/deed/harvester_deed/shared_harvester_flora_deed.iff
		case 0x28A44E72: //object/installation/mining_organic/shared_mining_organic_flora_farm_medium.iff
			return 0x522BE74D; //object/tangible/deed/harvester_deed/shared_harvester_flora_deed_medium.iff
		case 0x3481BD07: //object/installation/mining_organic/shared_mining_organic_flora_farm_heavy.iff
			return 0xEEC52333; //object/tangible/deed/harvester_deed/shared_harvester_flora_deed_heavy.iff

		// Faction
		case 0x84425787: //object/installation/faction_perk/covert_detector/shared_detector_base.iff
			return 0xC786298D; //object/tangible/deed/faction_perk/covert_detector/shared_detector_32m_deed.iff

		case 0x4EC91AA6: //object/installation/faction_perk/minefield/base/shared_minefield_base.iff
		case 0x757889EA: //object/installation/faction_perk/minefield/shared_field_1x1.iff
			return 0x5D30CDF7; //object/tangible/deed/faction_perk/minefield/shared_field_1x1_deed.iff
		case 0x6EE2514F: //object/installation/faction_perk/turret/base/shared_faction_turret_base.iff

		case 0x884DC0A5: //object/installation/faction_perk/turret/shared_block_lg.iff
			return 0xF07B2F6E; //object/tangible/deed/faction_perk/turret/shared_dish_lg_deed.iff
		case 0x6F719708: //object/installation/faction_perk/turret/shared_block_med.iff
			return 0xFBA00806; //object/tangible/deed/faction_perk/turret/shared_block_med_deed.iff
		case 0x75678B26: //object/installation/faction_perk/turret/shared_block_sm.iff
			return 0xA3878091; //object/tangible/deed/faction_perk/turret/shared_block_sm_deed.iff

		case 0x5E3D2244: //object/installation/faction_perk/turret/shared_dish_lg.iff
			return 0xF07B2F6E; //object/tangible/deed/faction_perk/turret/shared_dish_lg_deed.iff
		case 0xA31769C7: //object/installation/faction_perk/turret/shared_dish_sm.iff
			return 0x767B073F; //object/tangible/deed/faction_perk/turret/shared_dish_sm_deed.iff

		case 0xD6D6D17D: //object/installation/faction_perk/turret/shared_tower_lg.iff
			return 0xDE76DCB5; //object/tangible/deed/faction_perk/turret/shared_tower_lg_deed.iff
		case 0xB0794405: //object/installation/faction_perk/turret/shared_tower_med.iff
			return 0xA8274B6E; //object/tangible/deed/faction_perk/turret/shared_tower_med_deed.iff
		case 0x2BFC9AFE: //object/installation/faction_perk/turret/shared_tower_sm.iff
			return 0x5876F4E4; //object/tangible/deed/faction_perk/turret/shared_tower_sm_deed.iff

		case 0x2073410C: //object/installation/base/shared_construction_installation_base.iff
		case 0x5FFEAE33: //object/installation/base/shared_installation_base.iff
		case 0xF6A8B139: //object/installation/base/shared_installation_default.iff
		case 0x1F8F9631: //object/installation/battlefield/destructible/barracks/shared_bfield_gungan_barracks.iff
		case 0x2C6E39C8: //object/installation/battlefield/destructible/barracks/shared_bfield_nightsister_barracks.iff
		case 0xE5C2212C: //object/installation/battlefield/destructible/barracks/shared_rebel_infantry_barracks.iff
		case 0xD5CCDFE2: //object/installation/battlefield/destructible/barracks/shared_storm_trooper_barracks.iff
		case 0xB6863EB5: //object/installation/battlefield/destructible/base/shared_base_destructible_building.iff
		case 0x86973547: //object/installation/battlefield/destructible/base/shared_construction_base_destructible_building.iff
		case 0x3C3D91E3: //object/installation/battlefield/destructible/shared_antenna_tatt_style_1.iff
		case 0xE72A3974: //object/installation/battlefield/destructible/shared_antenna_tatt_style_2.iff
		case 0x94A22382: //object/installation/battlefield/destructible/shared_battlefield_constructor.iff
		case 0x79931BD3: //object/installation/battlefield/destructible/shared_bfield_banner_freestand_impl.iff
		case 0x1F0DAF59: //object/installation/battlefield/destructible/shared_bfield_banner_freestand_rebl.iff
		case 0x9C0B080B: //object/installation/battlefield/destructible/shared_bfield_base_gate_impl.iff
		case 0x9E3CA589: //object/installation/battlefield/destructible/shared_bfield_column_imperial.iff
		case 0x4CB0BE85: //object/installation/battlefield/destructible/shared_bfield_column_impl_med.iff
		case 0xA613F447: //object/installation/battlefield/destructible/shared_bfield_column_impl_weak.iff
		case 0xC15435A1: //object/installation/battlefield/destructible/shared_bfield_column_rebel.iff
		case 0xFDB36A1B: //object/installation/battlefield/destructible/shared_bfield_column_rebl_med.iff
		case 0x83478B5B: //object/installation/battlefield/destructible/shared_bfield_column_rebl_strong.iff
		case 0x1C38FA8E: //object/installation/battlefield/destructible/shared_bfield_column_rebl_weak.iff
		case 0xDE11CE25: //object/installation/battlefield/destructible/shared_bfield_column_strong.iff
		case 0xCEADD0B7: //object/installation/battlefield/destructible/shared_bfield_gungan_cleft_wall_lg.iff
		case 0x7B865016: //object/installation/battlefield/destructible/shared_bfield_gungan_damaged_narrow_arch.iff
		case 0xBA6D6964: //object/installation/battlefield/destructible/shared_bfield_gungan_damaged_wall_lg.iff
		case 0xBBB0FEC9: //object/installation/battlefield/destructible/shared_bfield_gungan_damaged_wide_arch.iff
		case 0xAA8B1323: //object/installation/battlefield/destructible/shared_bfield_gungan_pillar_damaged.iff
		case 0xB59C0185: //object/installation/battlefield/destructible/shared_bfield_gungan_pillar_ruined.iff
		case 0xC5BEDD83: //object/installation/battlefield/destructible/shared_bfield_gungan_relic.iff
		case 0xC257877B: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s01a.iff
		case 0x19402FEC: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s01b.iff
		case 0xEF2F90F3: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s02a.iff
		case 0x34383864: //object/installation/battlefield/destructible/shared_bfield_gungan_statue_s02b.iff
		case 0x8FB419A7: //object/installation/battlefield/destructible/shared_bfield_gungan_target_shield_gen.iff
		case 0xFFAAF535: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_lg_s01.iff
		case 0x24BD5DA2: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_lg_s02.iff
		case 0x271B66BB: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_sm_s01.iff
		case 0xFC0CCE2C: //object/installation/battlefield/destructible/shared_bfield_gungan_wall_ruined_sm_s02.iff
		case 0x4768C16F: //object/installation/battlefield/destructible/shared_bfield_nightsister_fence.iff
		case 0x2A73874F: //object/installation/battlefield/destructible/shared_bfield_nightsister_freestand_banner01.iff
		case 0xF1642FD8: //object/installation/battlefield/destructible/shared_bfield_nightsister_freestand_banner02.iff
		case 0xB8694855: //object/installation/battlefield/destructible/shared_bfield_nightsister_freestand_banner03.iff
		case 0xA6382D47: //object/installation/battlefield/destructible/shared_bfield_nightsister_gate.iff
		case 0x5614507D: //object/installation/battlefield/destructible/shared_bfield_nightsister_hut.iff
		case 0xB97E20DA: //object/installation/battlefield/destructible/shared_bfield_nightsister_target_sith_altar.iff
		case 0x1CD51413: //object/installation/battlefield/destructible/shared_bfield_nightsister_target_sith_crystal.iff
		case 0xE25046B9: //object/installation/battlefield/destructible/shared_bfield_nightsister_target_tower.iff
		case 0x8EA83D5F: //object/installation/battlefield/destructible/shared_bfield_target_power_generator.iff
		case 0xDA25F494: //object/installation/battlefield/destructible/shared_bfield_target_power_transformer_01.iff
		case 0x1325C03: //object/installation/battlefield/destructible/shared_bfield_target_power_transformer_02.iff
		case 0xFDFBCE11: //object/installation/battlefield/destructible/shared_bfield_wall_barbed.iff
		case 0x7E7DBA97: //object/installation/battlefield/destructible/shared_bfield_wall_connector.iff
		case 0xB721EDA7: //object/installation/battlefield/destructible/shared_bfield_wall_impl_weak.iff
		case 0xA88680EF: //object/installation/battlefield/destructible/shared_bfield_wall_med.iff
		case 0xDD3A7BB4: //object/installation/battlefield/destructible/shared_bfield_wall_rebl_med.iff
		case 0x855F876A: //object/installation/battlefield/destructible/shared_bfield_wall_rebl_strong.iff
		case 0xD0AE36E: //object/installation/battlefield/destructible/shared_bfield_wall_rebl_weak.iff
		case 0x57B0C19F: //object/installation/battlefield/destructible/shared_bfield_wall_strong.iff
		case 0x95EBC3AD: //object/installation/battlefield/destructible/shared_gungan_sacred_head.iff
		case 0xF92C990B: //object/installation/battlefield/destructible/shared_imperial_gate_house.iff
		case 0xD8C935AC: //object/installation/battlefield/destructible/shared_rebel_gate_house.iff
		case 0x192CFC8C: //object/installation/battlefield/destructible/shared_small_turret.iff
		case 0xC7D47F9: //object/installation/battlefield/destructible/shared_turret_dish_small.iff
		case 0x2AD09AFA: //object/installation/battlefield/destructible/shared_turret_tower_small.iff
		default:
			return 0;

	}
}
*/

void InstallationObjectImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}

void InstallationObjectImplementation::parseItemAttributes() {
	String attr = "operating";
	setOperating(itemAttributes->getBooleanAttribute(attr));

	attr = "owner";
	setOwner(itemAttributes->getStringAttribute(attr));

	attr = "ownerID";
	setOwnerID(itemAttributes->getUnsignedLongAttribute(attr));

	attr = "surplusMaintenance";
	setSurplusMaintenance(itemAttributes->getFloatAttribute(attr));

	attr = "maintenanceRate";
	setMaintenanceRate(itemAttributes->getFloatAttribute(attr));

	attr = "surplusPower";
	setSurplusPower(itemAttributes->getFloatAttribute(attr));

	attr = "powerRate";
	setPowerRate(itemAttributes->getFloatAttribute(attr));
}

void InstallationObjectImplementation::addHeaderAttributes(AttributeListMessage* alm) {
	alm->insertAttribute("volume", "1");

	/*if (craftersName != ""){
		alm->insertAttribute("crafter", craftersName);
	}

	if (craftedSerial != ""){
		alm->insertAttribute("serial_number", craftedSerial);
	}*/
}

void InstallationObjectImplementation::addFooterAttributes(AttributeListMessage* alm) {
	//alm->insertAttribute("healing_ability", getMedicineUseRequired());
}

void InstallationObjectImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);

	/*
	alm->insertAttribute("examine_maintenance", (int)getSurplusMaintenance());
	alm->insertAttribute("examine_maintenance_rate", (float)getMaintenanceRate());
	alm->insertAttribute("examine_power", (int)getSurplusPower());
	alm->insertAttribute("examine_extractionrate", (float)getExtractionRate());
	alm->insertAttribute("examine_hoppersize", (float)getHopperSize());
	*/

	addFooterAttributes(alm);
}

// structureManager->deleteInstallation(InstallationObject *inso);
