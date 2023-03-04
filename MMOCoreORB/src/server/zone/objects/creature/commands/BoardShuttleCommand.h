/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/*
 * Updated on: Thu Oct 13 08:16:00 PDT 2011 by lordkator - Fixes to make travel debugging easier and fixed dialog timing
 */

#ifndef BOARDSHUTTLECOMMAND_H_
#define BOARDSHUTTLECOMMAND_H_

#include "QueueCommand.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/TicketSelectionSuiCallback.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/planet/PlanetTravelPoint.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/group/GroupObject.h"

//#define ENABLE_CITY_TRAVEL_LIMIT

class BoardShuttleCommand : public QueueCommand {
public:

	static int MAXIMUM_PLAYER_COUNT;
	const int MAXIMUM_POSITION_TRIES = 5;

	BoardShuttleCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<Zone*> zone = creature->getZone();

		if (zone == nullptr)
			return GENERALERROR;

		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		Reference<PlanetTravelPoint*> closestPoint = planetManager->getNearestPlanetTravelPoint(creature, 128.f);

		// Check to make sure the creature is within range of a PlanetTravelPoint
		if (closestPoint == nullptr) {
			// Could do @player_structure:boarding_too_far here but this allows you to know in-game that no point was found
			creature->sendSystemMessage("There is no shuttle nearby.");
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> shuttle = closestPoint->getShuttle();

		// Is there a shuttle object related to this point?
		if (shuttle == nullptr) {
			creature->error("No Shuttle Object assigned to " + closestPoint->toString());

			// Different error so it's obvious from in-game that the shuttle did not link to this travel point.
			creature->sendSystemMessage("Travel from this location is unavailable at this time.");
			return GENERALERROR;
		}

		if (!shuttle->isInRange(creature, 25.f)) {
			creature->sendSystemMessage("@player_structure:boarding_too_far"); //You are too far from the shuttle to board.
			return GENERALERROR;
		}

		if (creature->isRidingMount()) {
			creature->sendSystemMessage("@travel:no_pets"); //You cannot board the shuttle when you are riding on a pet or in a vehicle.
			return GENERALERROR;
		}

		// Get tickets user has in inventory for this location
		SortedVector<ManagedReference<TicketObject*> > tickets = findTicketsInInventory(creature, closestPoint);

		// Do they have any tickets for this location?
		if (tickets.size() == 0) {
			creature->sendSystemMessage("@travel:no_ticket"); //You do not have a ticket to board this shuttle.
			return GENERALERROR;
		}

		// Is shuttle ready to board yet?
		// Shuttle at Theed Spaceport, Naboo should always be available. Even when the shuttle isn't there.
		if (!closestPoint->isPoint("naboo","Theed Spaceport")){
			if (!planetManager->checkShuttleStatus(creature, shuttle))
				return GENERALERROR;
		}

		uint64 ticketoid = target;

		// If only one ticket, use the first ticket
		if (tickets.size() == 1) {
			ticketoid = tickets.get(0)->getObjectID();
		}

		ManagedReference<TicketObject*> ticketObject = server->getZoneServer()->getObject(ticketoid).castTo<TicketObject*>();

		//If no ticket was passed as the target, then send the selection box.
		if (ticketObject == nullptr) {
			sendTicketSelectionBoxTo(creature, tickets);
			return SUCCESS;
		}

		String departurePlanet = ticketObject->getDeparturePlanet();
		String departurePoint = ticketObject->getDeparturePoint();

		if (!closestPoint->isPoint(departurePlanet, departurePoint)) {
			creature->sendSystemMessage("@travel:no_ticket"); //You do not have a ticket to board this shuttle.
			return GENERALERROR;
		}

		String arrivalPlanet = ticketObject->getArrivalPlanet();
		String arrivalPointName = ticketObject->getArrivalPoint();

		ManagedReference<Zone*> arrivalZone = server->getZoneServer()->getZone(arrivalPlanet);

		if (arrivalZone == nullptr) {
			creature->sendSystemMessage("@travel:route_not_available"); //This ticket's route is no longer available.
			return GENERALERROR;
		}

		Reference<PlanetTravelPoint*> arrivalPoint = arrivalZone->getPlanetManager()->getPlanetTravelPoint(arrivalPointName);

		if (arrivalPoint == nullptr || !closestPoint->canTravelTo(arrivalPoint)) {
			creature->sendSystemMessage("@travel:wrong_shuttle"); //The ticket is not valid for the given shuttle.
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> targetShuttleObject = arrivalPoint->getShuttle();

		if (targetShuttleObject != nullptr) {
			ManagedReference<CityRegion*> region = targetShuttleObject->getCityRegion().get();

			if (region != nullptr) {
#ifdef ENABLE_CITY_TRAVEL_LIMIT
				if (region->getCurrentPlayerCount() >= MAXIMUM_PLAYER_COUNT) {
					creature->sendSystemMessage("Your destination is currently under maintenance, please try again later.");
					return GENERALERROR;
				}
#endif
				if (region->isBanned(creature->getObjectID())) {
					creature->sendSystemMessage("@city/city:banned_from_that_city"); // You have been banned from traveling to that city by the city militia
					return GENERALERROR;
				}
			}
		}

		ManagedReference<CityRegion*> departCity = shuttle->getCityRegion().get();

		if (departCity != nullptr){
			if (departCity->isBanned(creature->getObjectID())) {
				creature->sendSystemMessage("@city/city:city_cant_board"); // You are banned from using the services of this city.\nYou may not board the transport.
				return GENERALERROR;
			}
		}

		float arrivalPointZ = arrivalPoint->getArrivalPositionZ();
		Coordinate p;

		// Try and find a spot that is at same Z as arrival point.
		int tries = MAXIMUM_POSITION_TRIES;

		for (;tries > 0; --tries) {
			p = findRandomizedArrivalPoint(targetShuttleObject, arrivalZone, arrivalPoint, tries);

			if (fabs(p.getPositionZ() - arrivalPointZ) <= 1.5) {
				break;
			}

#if DEBUG_TRAVEL
			Logger::console.info(true) << "\033[45;30m" << __FUNCTION__ << "():" << __LINE__
				<< "Destination Z mismatch: "
				<< arrivalZone->getZoneName() << " (x:" << p.getPositionX() << ", y:" << p.getPositionY() << ", z:" << p.getPositionZ() << ")"
				<< " arrivalPointZ=" << arrivalPointZ
				<< ", trying " << (tries - 1) << " more times.\033[0m";
#endif // DEBUG_TRAVEL
		}

		if (tries <= 0) {
			creature->error() << "BoardShuttleCommand: Failed to find suitable arrival point at "
				<< arrivalZone->getZoneName() << " (x:" << p.getPositionX() << ", y:" << p.getPositionY() << ", z:" << p.getPositionZ() << ")"
				<< " arrivalPointZ=" << arrivalPointZ
				<< ", using raw arrival point: "
				<< arrivalZone->getZoneName()
				<< " (x:" << arrivalPoint->getArrivalPositionX()
				<< ", y:" << arrivalPoint->getArrivalPositionY()
				<< ", z:" << arrivalPoint->getArrivalPositionZ() << ")"
			;

			// Default to the raw arrival point
			p.initializePosition(arrivalPoint->getArrivalPosition());
		}

#if DEBUG_TRAVEL
		{
			float collisionZ = CollisionManager::getWorldFloorCollision(p.getPositionX(), p.getPositionY(), arrivalZone, false);

			Logger::console.info(true) << "\033[44;30m" << __FUNCTION__ << "():" << __LINE__
				<< " finalArrivalPoint = "
				<< arrivalZone->getZoneName() << " (x:" << p.getPositionX() << ", y:" << p.getPositionY() << ", z:" << p.getPositionZ() << ")"
				<< " collisionZ=" << collisionZ
				<< " arrivalPointZ = " << arrivalPointZ << "\033[0m";
		}
#endif // DEBUG_TRAVEL

		creature->switchZone(arrivalZone->getZoneName(), p.getPositionX(), p.getPositionZ(), p.getPositionY(), 0);

		// Update the nearest mission for group waypoint for both the arrival and departure planet.
		if (creature->isGrouped()) {
			GroupObject* group = creature->getGroup();

			Locker clocker(group, creature);

			group->scheduleUpdateNearestMissionForGroup(zone->getPlanetCRC());

			if(departurePlanet != arrivalPlanet) {
				group->scheduleUpdateNearestMissionForGroup(arrivalZone->getPlanetCRC());
			}
		}

		Locker ticketLocker(ticketObject);

		//remove the ticket from inventory and destroy it.
		ticketObject->destroyObjectFromWorld(true);
		ticketObject->destroyObjectFromDatabase(true);

		return SUCCESS;
	}

private:
	SortedVector<ManagedReference<TicketObject*> > findTicketsInInventory(CreatureObject* creature, PlanetTravelPoint* departurePoint) const {
		SortedVector<ManagedReference<TicketObject*> > tickets;

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory == nullptr)
			return tickets;

		int totalObjects = inventory->getContainerObjectsSize();

		if (totalObjects <= 0)
			return tickets;

		for (int i = 0; i < totalObjects; ++i) {
			ManagedReference<SceneObject*> obj = inventory->getContainerObject(i);

			if (!obj->isTangibleObject() || !(cast<TangibleObject*>(obj.get()))->isTicketObject())
				continue;

			TicketObject* ticket = cast<TicketObject*>( obj.get());

			//Check to see if the ticket is for this destination
			if (!departurePoint->isPoint(ticket->getDeparturePlanet(), ticket->getDeparturePoint()))
				continue;

			tickets.put(ticket);
		}

		return tickets;
	}

	void sendTicketSelectionBoxTo(CreatureObject* creature, SortedVector<ManagedReference<TicketObject*> > tickets) const {
		//Make sure it's a player before sending it a sui box...
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		ManagedReference<PlayerObject* > ghost = player->getPlayerObject();

		if (ghost == nullptr)
			return;

		if (ghost->hasSuiBoxWindowType(SuiWindowType::TRAVEL_TICKET_SELECTION))
		{
			ghost->closeSuiWindowType(SuiWindowType::TRAVEL_TICKET_SELECTION);
		}

		ManagedReference<SuiListBox*> suiListBox = new SuiListBox(player, SuiWindowType::TRAVEL_TICKET_SELECTION);
		creature->sendSystemMessage("@travel:boarding_ticket_selection"); //You must select a ticket to use before boarding.
		suiListBox->setPromptTitle("Select Destination");
		suiListBox->setPromptText("Select Destination");

		for (int i = 0; i < tickets.size(); ++i) {
			ManagedReference<TicketObject*> ticket = tickets.get(i);
			suiListBox->addMenuItem(ticket->getArrivalPoint(), ticket->getObjectID());
		}

		suiListBox->setCallback(new TicketSelectionSuiCallback(server->getZoneServer()));

		player->getPlayerObject()->addSuiBox(suiListBox);
		player->sendMessage(suiListBox->generateMessage());
	}

	Coordinate findRandomizedArrivalPoint(CreatureObject* targetShuttleObject, Zone* arrivalZone, PlanetTravelPoint* arrivalPoint, int tries) const {
		Coordinate pos;

		pos.initializePosition(arrivalPoint->getArrivalPosition());

#if DEBUG_TRAVEL
		{
			float collisionZ = CollisionManager::getWorldFloorCollision(pos.getPositionX(), pos.getPositionY(), arrivalZone, false);

			Logger::console.info(true) << "\033[45;30m" << __FUNCTION__ << "():" << __LINE__ << " try#" << tries
				<< " arrivalPoint = "
				<< arrivalZone->getZoneName() << " (x:" << pos.getPositionX() << ", y:" << pos.getPositionY() << ", z:" << pos.getPositionZ() << ")"
				" collisionZ = " << collisionZ << "\033[0m";
		}
#endif // DEBUG_TRAVEL

		ManagedReference<CityRegion*> region = targetShuttleObject != nullptr ? targetShuttleObject->getCityRegion().get() : nullptr;

		// Randomize the arrival a bit to try and avoid everyone zoning on top of each other
		// For NPC cities, use the generic method
		if (region == nullptr || region->isClientRegion()) {
			pos.randomizePosition(3);
#if DEBUG_TRAVEL
			Logger::console.info(true) << "\033[45;30m" << __FUNCTION__ << "():" << __LINE__ << " try#" << tries
				<< " randomized Position = "
				<< arrivalZone->getZoneName() << " (x:" << pos.getPositionX() << ", y:" << pos.getPositionY() << ", z:" << pos.getPositionZ() << ")"
				"\033[0m";
#endif // DEBUG_TRAVEL
		} else {

			// relative orientation of the shuttle
			float oy = targetShuttleObject->getDirection()->getY();
			float dirDegrees = (acos(oy) * 180 / M_PI) * 2;

			// the proper location for arrival is along a 36 degree arc centered on the shuttle's facing axis, between 13 and 16 meters out
			dirDegrees = dirDegrees - 18 + System::random(36);
			float dirRadians = dirDegrees * M_PI / 180;
			float distance = 13 + System::random(3);

			// update the X & Y positions accordingly
			pos.setPositionX(pos.getPositionX() + sin(dirRadians) * distance);
			pos.setPositionY(pos.getPositionY() + cos(dirRadians) * distance);
#if DEBUG_TRAVEL
			Logger::console.info(true) << "\033[45;30m" << __FUNCTION__ << "():" << __LINE__ << " try#" << tries
				<< " shuttle offset Position = "
				<< arrivalZone->getZoneName() << " (x:" << pos.getPositionX() << ", y:" << pos.getPositionY() << ", z:" << pos.getPositionZ() << ")"
				"\033[0m";
#endif // DEBUG_TRAVEL
		}

		pos.setPositionZ(CollisionManager::getWorldFloorCollision(pos.getPositionX(), pos.getPositionY(), arrivalZone, false));

		return pos;
	}
};

#endif //BOARDSHUTTLECOMMAND_H_
