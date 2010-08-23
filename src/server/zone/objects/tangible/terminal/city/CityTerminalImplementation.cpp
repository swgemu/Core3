/*
 * CityTerminalImplementation.cpp
 *
 *  Created on: Aug 23, 2010
 *      Author: crush
 */

#include "CityTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void CityTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	//TODO: Check to see if the player is the mayor or not.

	menuResponse->addRadialMenuItem(211, 3, "@city/city:city_info"); //City Info
	menuResponse->addRadialMenuItemToRadialID(211, 217, 3, "@city/city:city_name"); //Change City Name
	menuResponse->addRadialMenuItemToRadialID(211, 212, 3, "@city/city:city_status"); //Change City Name
	menuResponse->addRadialMenuItemToRadialID(211, 213, 3, "@city/city:city_citizens"); //Citizenship Report
	menuResponse->addRadialMenuItemToRadialID(211, 214, 3, "@city/city:city_structures"); //Structure Report
	menuResponse->addRadialMenuItemToRadialID(211, 215, 3, "@city/city:treasury_status"); //Treasury Report

	menuResponse->addRadialMenuItem(216, 3, "@city/city:city_management"); //City Management
	menuResponse->addRadialMenuItemToRadialID(216, 217, 3, "@city/city:city_name"); //Change City Name

	//TODO: This should be a toggle.
	menuResponse->addRadialMenuItemToRadialID(216, 222, 3, "@city/city:city_unregister"); //Unregister City
	//menuResponse->addRadialMenuItemToRadialID(216, 222, 3, "@city/city:city_register"); //Register City

	menuResponse->addRadialMenuItemToRadialID(216, 218, 3, "@city/city:manage_militia"); //Manage Militia

	menuResponse->addRadialMenuItemToRadialID(216, 219, 3, "@city/city:treasury_taxes"); //Adjust Taxes

	menuResponse->addRadialMenuItemToRadialID(216, 220, 3, "@city/city:treasury_deposit"); //Treasury Deposit
	menuResponse->addRadialMenuItemToRadialID(216, 221, 3, "@city/city:treasury_withdraw"); //Treasury Withdraw

	menuResponse->addRadialMenuItemToRadialID(216, 223, 3, "@city/city:city_specializations"); //City Specialization
}

int CityTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	return 0;
}
