
#ifndef DUNGEONTICKETOBJECTATTIBUTELISTCOMPONENT_H_
#define DUNGEONTICKETOBJECTATTIBUTELISTCOMPONENT_H_

#include "server/zone/objects/scene/components/AttributeListComponent.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"

class DungeonTicketObjectAttributeListComponent: public AttributeListComponent {
public:

	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) const {

		ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object);

		TicketObject* ticketObject = tano.castTo<TicketObject*>();

		String dep = ticketObject->getDeparturePlanet();
		String point = ticketObject->getDeparturePoint();
		String arrive = ticketObject->getArrivalPoint();

		alm->insertAttribute("travel_departure_planet", "@planet_n:" + dep);
		alm->insertAttribute("travel_departure_point", "@dungeon/space_dungeon:corvette_" + point + "_pilot");
		alm->insertAttribute("travel_arrival_point", "@dungeon/space_dungeon:corvette_" + arrive);
	}

};

#endif /* ATTIBUTELISTCOMPONENT_H_ */
