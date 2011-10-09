/*
 * CityTerminalImplementation.cpp
 *
 *  Created on: Aug 23, 2010
 *      Author: crush
 */

#include "CityTerminal.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/building/city/CityHallObject.h"
#include "server/zone/managers/city/CityManager.h"

void CityTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (controlledObject == NULL || !controlledObject->isBuildingObject())
		return;

	BuildingObject* building = cast<BuildingObject*>( controlledObject.get());

	if (!building->isCityHallBuilding())
		return;

	CityHallObject* cityHall = cast<CityHallObject*>( building);

	Locker _locker(cityHall);

	menuResponse->addRadialMenuItem(211, 3, "@city/city:city_info"); //City Info
	menuResponse->addRadialMenuItemToRadialID(211, 212, 3, "@city/city:city_status"); //Status Report
	menuResponse->addRadialMenuItemToRadialID(211, 213, 3, "@city/city:city_citizens"); //Citizenship Report
	menuResponse->addRadialMenuItemToRadialID(211, 214, 3, "@city/city:city_structures"); //Structure Report
	menuResponse->addRadialMenuItemToRadialID(211, 223, 3, "@city/city:city_rank"); //City Advancement
	menuResponse->addRadialMenuItemToRadialID(211, 224, 3, "@city/city:city_maint"); //Maintenance Report
	menuResponse->addRadialMenuItemToRadialID(211, 215, 3, "@city/city:treasury_status"); //Treasury Report

	if (!cityHall->isMayor(player->getObjectID()))
		return;

	menuResponse->addRadialMenuItem(216, 3, "@city/city:city_management"); //City Management
	menuResponse->addRadialMenuItemToRadialID(216, 217, 3, "@city/city:city_name"); //Change City Name

	//TODO: This should be a toggle.
	menuResponse->addRadialMenuItemToRadialID(216, 222, 3, "@city/city:city_unregister"); //Unregister City
	//menuResponse->addRadialMenuItemToRadialID(216, 222, 3, "@city/city:city_register"); //Register City

	if (!cityHall->isZoningEnabled())
		menuResponse->addRadialMenuItemToRadialID(216, 226, 3, "@city/city:zone"); //Enable Zoning
	else
		menuResponse->addRadialMenuItemToRadialID(216, 226, 3, "@city/city:unzone"); //Disable Zoning

	menuResponse->addRadialMenuItemToRadialID(216, 218, 3, "@city/city:city_militia"); //Manage Militia

	menuResponse->addRadialMenuItemToRadialID(216, 219, 3, "@city/city:treasury_taxes"); //Adjust Taxes

	menuResponse->addRadialMenuItemToRadialID(216, 220, 3, "@city/city:treasury_deposit"); //Treasury Deposit
	menuResponse->addRadialMenuItemToRadialID(216, 221, 3, "@city/city:treasury_withdraw"); //Treasury Withdraw

	menuResponse->addRadialMenuItemToRadialID(216, 225, 3, "@city/city:city_specializations"); //City Specialization
}

int CityTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (getZone() == NULL)
		return 0;

	ManagedReference<CityManager*> cityManager = getZone()->getCityManager();

	if (controlledObject == NULL || !controlledObject->isBuildingObject())
		return 0;

	BuildingObject* building = cast<BuildingObject*>( controlledObject.get());

	if (!building->isCityHallBuilding())
		return 0;

	CityHallObject* cityHallObject = cast<CityHallObject*>( building);

	Locker _locker(cityHallObject);

	cityManager->handleCityAdvancement(cityHallObject);

	switch (selectedID) {
	case 211:
	case 212: //Status Report
		cityHallObject->sendStatusTo(player);
		break;

	case 213: //Citizenship Report
		cityHallObject->sendCitizenshipReportTo(player);
		break;

	case 214: //Structure Report
		cityHallObject->sendStructureReportTo(player);
		break;

	case 223: //City Advancement
		cityHallObject->sendCityAdvancementTo(player);
		break;

	case 215: //Treasury Report
		cityHallObject->sendTreasuryReportTo(player);
		break;

	case 216:
	case 217: //Change City Name
		cityHallObject->sendChangeCityNameTo(player);
		break;

	case 222: //Unregister/Register
		cityHallObject->toggleCityRegistration(player);
		break;

	case 218: //Manage Militia
		cityHallObject->sendManageMilitiaTo(player);
		break;

	case 219: //Adjust Taxes
		cityHallObject->sendAdjustTaxesTo(player);
		break;

	case 220: //Treasury Deposit
		cityHallObject->sendTreasuryDepositTo(player);
		break;

	case 221: //Treasure Withdrawal
		cityHallObject->sendTreasuryWithdrawalTo(player);
		break;

	case 224: //Maintenance Report
		cityHallObject->sendMaintenanceReportTo(player);
		break;

	case 225: //City Specialization
		cityHallObject->sendCitySpecializationSelectionTo(player);
		break;

	case 226: //Enable Zoning
		cityHallObject->sendEnableZoningTo(player);

	default:
		TerminalImplementation::handleObjectMenuSelect(player, selectedID);
		break;
	}

	return 0;
}
