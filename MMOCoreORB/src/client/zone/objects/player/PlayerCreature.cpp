#include "engine/engine.h"

#include "zone/Zone.h"

#include "PlayerCreature.h"

PlayerCreature::PlayerCreature(LuaObject* templateData) : CreatureObject(templateData) {

}

void PlayerCreature::insertToZone(Zone* zone) {
	PlayerCreature::zone = zone;

	/*Event * positionUpdateEvent = new PositionUpdateEvent ( this );
	zone->addEvent ( positionUpdateEvent, 250 );*/
}

void PlayerCreature::activatePositionUpdate() {
	/*System::out << hex << "moving PlayerCreature [" << objectID << "] to (" << dec << getPositionX() << ", "
		 << getPositionZ() << ", " << getPositionY() << ")\n";*/

	/*ZoneClient * client = zone->getZoneClient ( );
	if  ( client != NULL ) {
		Message * dataupd = new DataTransformMessage ( this );
		client->sendMessage ( dataupd );

		Event * positionUpdateEvent = new PositionUpdateEvent ( this );
		zone->addEvent ( positionUpdateEvent, 250 );
	}*/
}
