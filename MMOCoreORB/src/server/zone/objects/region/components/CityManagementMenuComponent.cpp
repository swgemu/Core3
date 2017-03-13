/*
 * CityManagementMenuComponent.cpp
 *
 *  Created on: Feb 12, 2012
 *      Author: xyborn
 */

#include "CityManagementMenuComponent.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/player/PlayerObject.h"

#ifndef CITY_DEBUG
#define CITY_DEBUG
#endif

void CityManagementMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	ManagedReference<CityRegion*> city = sceneObject->getCityRegion().get();

	if (city == NULL) {
		sceneObject->error("city region null in CityManagementMenuComponent::fillObjectMenuResponse");
		return;
	}

	PlayerObject* ghost = player->getPlayerObject();
	if (ghost == NULL) {
		return;
	}

	menuResponse->addRadialMenuItem(211, 3, "@city/city:city_info"); //City Information
	menuResponse->addRadialMenuItemToRadialID(211, 212, 3, "@city/city:city_status"); //Status Report
	menuResponse->addRadialMenuItemToRadialID(211, 213, 3, "@city/city:city_citizens"); //Citizenship Report
	menuResponse->addRadialMenuItemToRadialID(211, 214, 3, "@city/city:city_structures"); //Structure Report
	menuResponse->addRadialMenuItemToRadialID(211, 223, 3, "@city/city:city_rank"); //City Advancement
	menuResponse->addRadialMenuItemToRadialID(211, 224, 3, "@city/city:city_maint"); //Maintenance Report

	menuResponse->addRadialMenuItem(210, 3, "@city/city:treasury_management"); // City Treasury
	menuResponse->addRadialMenuItemToRadialID(210, 215, 3, "@city/city:treasury_status"); //Treasury Report
	menuResponse->addRadialMenuItemToRadialID(210, 220, 3, "@city/city:treasury_deposit"); //Treasury Deposit

#ifdef CITY_DEBUG
	if(ghost->isPrivileged()) {
		menuResponse->addRadialMenuItem(227,3,"@city/city:city_hacks"); // City Hacks (GODMODE ONLY)
		menuResponse->addRadialMenuItemToRadialID(227,228,3,"@city/city:rank_up"); // 	Force Rank Up
		menuResponse->addRadialMenuItemToRadialID(227,229,3,"@city/city:rank_down"); // Force Rank Down
		menuResponse->addRadialMenuItemToRadialID(227,230,3,"@city/city:force_update"); // Force City Update or Election
	}
#endif

	if (!city->isMayor(player->getObjectID()) && !ghost->isStaff())
		return;

	menuResponse->addRadialMenuItem(216, 3, "@city/city:city_management"); //City Management
	menuResponse->addRadialMenuItemToRadialID(216, 217, 3, "@city/city:city_name"); //Change City Name

	if (!city->isMayor(player->getObjectID()) && !ghost->isAdmin())
		return;

	if (city->isRegistered()) {
		menuResponse->addRadialMenuItemToRadialID(216, 222, 3, "@city/city:city_unregister"); //Unregister City
	} else {
		menuResponse->addRadialMenuItemToRadialID(216, 222, 3, "@city/city:city_register"); //Register City
	}

	if (city->isZoningEnabled()) {
		menuResponse->addRadialMenuItemToRadialID(216, 226, 3, "@city/city:unzone"); //Disable Zoning
	} else {
		menuResponse->addRadialMenuItemToRadialID(216, 226, 3, "@city/city:zone"); //Enable Zoning
	}

	menuResponse->addRadialMenuItemToRadialID(216, 218, 3, "@city/city:city_militia"); //Manage Militia

	menuResponse->addRadialMenuItemToRadialID(216, 225, 3, "@city/city:city_specializations"); //City Specialization

	if (!city->isMayor(player->getObjectID()))
		return;

	menuResponse->addRadialMenuItemToRadialID(210, 221, 3, "@city/city:treasury_withdraw"); //Treasury Withdraw

	menuResponse->addRadialMenuItemToRadialID(216, 219, 3, "@city/city:treasury_taxes"); //Adjust Taxes
}

int CityManagementMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectID) const {
	ManagedReference<CityRegion*> city = sceneObject->getCityRegion().get();

	if (city == NULL)
		return 1;

	PlayerObject* ghost = player->getPlayerObject();
	if (ghost == NULL) {
		return 1;
	}

	sceneObject->unlock();

	Locker lock(city, player);

	CityManager* cityManager = player->getZoneServer()->getCityManager();

	switch (selectID) {
	case 211: // City Information
	case 212: //Status Report
		cityManager->sendStatusReport(city, player, sceneObject);
		break;
	case 213: //Citizenship Report
		cityManager->sendCitizenshipReport(city, player, sceneObject);
		break;
	case 214: // Structure Report
		cityManager->sendStructureReport(city, player, sceneObject);
		break;
	case 210: // City Treasury
	case 215: //Treasury Report
		cityManager->sendTreasuryReport(city, player, sceneObject);
		break;
	case 217:  // Change Name
		cityManager->sendChangeCityName(city, player);
		break;
	case 218: //Manage Militia
		cityManager->sendManageMilitia(city, player, sceneObject);
		break;
	case 219: //Adjust Taxes
		if (city->isMayor(player->getObjectID())) {
			cityManager->promptAdjustTaxes(city, player, sceneObject);
		}
		break;
	case 220: //Treasury Deposit
		cityManager->promptDepositCityTreasury(city, player, sceneObject);
		break;
	case 221: //Withdraw Treasury
		cityManager->promptWithdrawCityTreasury(city, player, sceneObject);
		break;
	case 222: //Register/Unregister
		if (city->isRegistered())
			cityManager->promptUnregisterCity(city, player, sceneObject);
		else
			cityManager->promptRegisterCity(city, player, sceneObject);
		break;
	case 223: //City Advancement
		cityManager->sendCityAdvancement(city, player, sceneObject);
		break;
	case 224: //Maintenance Report
		cityManager->sendMaintenanceReport(city, player, sceneObject);
		break;
	case 225: //Set City Specialization
		cityManager->promptCitySpecialization(city, player, sceneObject);
		break;
	case 226: //Toggle Zoning Enabled
		cityManager->promptToggleZoningEnabled(city, player);
		break;

#ifdef CITY_DEBUG
	case 228:
		if(ghost->isPrivileged()) {
			cityManager->promptForceRank(city, player, true);
		}
		break;
	case 229:
		if(ghost->isPrivileged()) {
			cityManager->promptForceRank(city, player, false);
		}
		break;
	case 230:
		if(ghost->isPrivileged()) {
			cityManager->promptForceUpdate(city, player);
		}
		break;
#endif

	}

	lock.release();

	sceneObject->wlock(player);

	return 0;
}
