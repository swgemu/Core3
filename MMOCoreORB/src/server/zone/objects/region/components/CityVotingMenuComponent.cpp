/*
 * CityVotingMenuComponent.cpp
 *
 *  Created on: Feb 12, 2012
 *      Author: xyborn
 */

#include "CityVotingMenuComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void CityVotingMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	ManagedReference<CityRegion*> city = sceneObject->getCityRegion().get();

	if (city == NULL || (!city->isCitizen(player->getObjectID()) && !player->getPlayerObject()->isPrivileged()))
			return;

	Locker _lock(city);

	menuResponse->addRadialMenuItem(224, 3, "@city/city:mayoral_race"); //Mayoral Race
	menuResponse->addRadialMenuItemToRadialID(224, 225, 3, "@city/city:mayoral_standings"); //Mayoral Standings

	if (!city->isCitizen(player->getObjectID()))
			return;

	menuResponse->addRadialMenuItemToRadialID(224, 226, 3, "@city/city:mayoral_vote"); //Vote for Mayor

	if (!city->isCandidate(player->getObjectID()))
		menuResponse->addRadialMenuItemToRadialID(224, 227, 3, "@city/city:mayoral_register"); //Register to Run
	else
		menuResponse->addRadialMenuItemToRadialID(224, 228, 3, "@city/city:mayoral_unregister"); //Unregister from Race
}

int CityVotingMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectID) const {
	ManagedReference<CityRegion*> city = sceneObject->getCityRegion().get();

	if (city == NULL)
		return 0;

	sceneObject->unlock();

	Locker _lock(city, player);

	CityManager* cityManager = sceneObject->getZoneServer()->getCityManager();

	switch (selectID) {
	case 224: //Standings
	case 225:
		cityManager->sendMayoralStandings(city, player, sceneObject);
		break;
	case 226: //Vote
		cityManager->promptMayoralVote(city, player, sceneObject);
		break;
	case 227: //Register
		cityManager->registerForMayoralRace(city, player);
		break;
	case 228: //Unregister
		cityManager->unregisterFromMayoralRace(city, player, false);
		break;
	}

	_lock.release();

	sceneObject->wlock(player);

	return 0;
}
