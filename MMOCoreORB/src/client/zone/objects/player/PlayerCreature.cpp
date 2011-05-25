#include "engine/engine.h"

#include "zone/Zone.h"

#include "PlayerCreature.h"
#include "../../../../server/zone/packets/object/ObjectControllerMessage.h"


PlayerCreature::PlayerCreature(LuaObject* templateData) : CreatureObject(templateData) {
	setLoggingName("PlayerCreature");

	follow = NULL;
}

void PlayerCreature::updatePosition(float x, float z, float y) {
	if (client == NULL)
		return;

	coordinates.setPosition(x, z, y);

	BaseMessage* message = new ObjectControllerMessage(objectID, 0x23, 0x71);
	message->insertInt(++movementCounter);

	message->insertFloat(direction.getX());
	message->insertFloat(direction.getY());
	message->insertFloat(direction.getZ());
	message->insertFloat(direction.getW());

	message->insertFloat(x);
	message->insertFloat(z);
	message->insertFloat(y);

	message->insertInt(0);

	client->sendMessage(message);
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
