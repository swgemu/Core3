/*
 * CityManagementMenuComponent.cpp
 *
 *  Created on: Feb 12, 2012
 *      Author: xyborn
 */

#include "CityManagementMenuComponent.h"
#include "../CityRegion.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/city/CityManager.h"

void CityManagementMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	CityRegion* city = sceneObject->getCityRegion();

	if (city == NULL)
		return;

	//City Information is available to anyone using the terminal and includes the options
		//Status Report, Citizenship Report, Structure Report, City Advancement, Maintenance Report, Treasury Report
	//and Treasury Deposit

	//

	menuResponse->addRadialMenuItem(211, 3, "@city/city:city_info"); //City Information
	menuResponse->addRadialMenuItemToRadialID(211, 212, 3, "@city/city:city_status"); //Status Report
	menuResponse->addRadialMenuItemToRadialID(211, 213, 3, "@city/city:city_citizens"); //Citizenship Report
	menuResponse->addRadialMenuItemToRadialID(211, 214, 3, "@city/city:city_structures"); //Structure Report
	menuResponse->addRadialMenuItemToRadialID(211, 223, 3, "@city/city:city_rank"); //City Advancement
	menuResponse->addRadialMenuItemToRadialID(211, 224, 3, "@city/city:city_maint"); //Maintenance Report
	menuResponse->addRadialMenuItemToRadialID(211, 215, 3, "@city/city:treasury_status"); //Treasury Report
	menuResponse->addRadialMenuItemToRadialID(211, 220, 3, "@city/city:treasury_deposit"); //Treasury Deposit

	if (!city->isMayor(player->getObjectID()))
		return;

	menuResponse->addRadialMenuItem(216, 3, "@city/city:city_management"); //City Management
	menuResponse->addRadialMenuItemToRadialID(216, 217, 3, "@city/city:city_name"); //Change City Name

	//TODO: This should be a toggle.
	menuResponse->addRadialMenuItemToRadialID(216, 222, 3, "@city/city:city_unregister"); //Unregister City
	//menuResponse->addRadialMenuItemToRadialID(216, 222, 3, "@city/city:city_register"); //Register City

	if (city->isZoningEnabled()) {
		menuResponse->addRadialMenuItemToRadialID(216, 226, 3, "@city/city:unzone"); //Disable Zoning
	} else {
		menuResponse->addRadialMenuItemToRadialID(216, 226, 3, "@city/city:zone"); //Enable Zoning
	}

	menuResponse->addRadialMenuItemToRadialID(216, 218, 3, "@city/city:city_militia"); //Manage Militia

	menuResponse->addRadialMenuItemToRadialID(216, 219, 3, "@city/city:treasury_taxes"); //Adjust Taxes

	menuResponse->addRadialMenuItemToRadialID(216, 221, 3, "@city/city:treasury_withdraw"); //Treasury Withdraw

	menuResponse->addRadialMenuItemToRadialID(216, 225, 3, "@city/city:city_specializations"); //City Specialization
}

int CityManagementMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectID) {
	CityRegion* city = sceneObject->getCityRegion();

	if (city == NULL)
		return 1;

	Locker lock(city, player);

	Zone* zone = sceneObject->getZone();

	if (zone == NULL)
		return 1;

	CityManager* cityManager = zone->getCityManager();

	switch (selectID) {
	case 212: //Status Report
		cityManager->sendStatusReport(city, player, sceneObject);
		break;
	case 215: //Treasury Report
		break;
	case 220: //Treasury Deposit
		cityManager->promptDepositCityTreasury(city, player, sceneObject);
		break;
	case 221: //Withdraw Treasury
		cityManager->promptWithdrawCityTreasury(city, player, sceneObject);
		break;
	case 225: //Set City Specialization
		cityManager->promptCitySpecialization(city, player, sceneObject);
		break;
	case 226: //Toggle Zoning Enabled
		cityManager->toggleZoningEnabled(city, player);
		break;
	}
	return 0;
}
