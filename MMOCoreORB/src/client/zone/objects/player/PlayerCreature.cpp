#include "PlayerCreature.h"
#include "client/zone/Zone.h"
//#include "server/zone/SpaceZone.h"
//#include "client/zone/SpaceZone.h" //// << need to make this
#include "server/zone/packets/object/ObjectControllerMessage.h"

PlayerCreature::PlayerCreature(LuaObject* templateData) : CreatureObject(templateData) {
	setLoggingName("PlayerCreature");

	follow = nullptr;
}

void PlayerCreature::updatePosition(float x, float z, float y) {
	if (client == nullptr)
		return;

	setPosition(x, z, y);

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
	PlayerCreature::spaceZone = nullptr;

	/*Event * positionUpdateEvent = new PositionUpdateEvent ( this );
	zone->addEvent ( positionUpdateEvent, 250 );*/
}

void PlayerCreature::insertToZone(SpaceZone* zone) {
	PlayerCreature::spaceZone = zone;
	PlayerCreature::zone = nullptr;
}

void PlayerCreature::activatePositionUpdate() {
	/*System::out << hex << "moving PlayerCreature [" << objectID << "] to (" << dec << getPositionX() << ", "
		 << getPositionZ() << ", " << getPositionY() << ")\n";*/

	/*ZoneClient * client = zone->getZoneClient ( );
	if  ( client != nullptr ) {
		Message * dataupd = new DataTransformMessage ( this );
		client->sendMessage ( dataupd );

		Event * positionUpdateEvent = new PositionUpdateEvent ( this );
		zone->addEvent ( positionUpdateEvent, 250 );
	}*/
}
