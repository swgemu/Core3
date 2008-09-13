#include "engine\engine.h"

#include "..\..\Zone.h"

#include "Player.h"

Player::Player() : CreatureObject(0) {
	characterID = 0;
}

Player::Player(uint64 oid) : CreatureObject(oid) {
	characterID = oid;
}

void Player::insertToZone(Zone* zone) {
	Player::zone = zone;

	/*Event * positionUpdateEvent = new PositionUpdateEvent ( this );
	zone->addEvent ( positionUpdateEvent, 250 );*/
}

void Player::activatePositionUpdate() {
	/*cout << hex << "moving Player [" << objectID << "] to (" << dec << getPositionX() << ", "
		 << getPositionZ() << ", " << getPositionY() << ")\n";*/

	/*ZoneClient * client = zone->getZoneClient ( );
	if  ( client != NULL ) {
		Message * dataupd = new DataTransformMessage ( this );
		client->sendMessage ( dataupd );

		Event * positionUpdateEvent = new PositionUpdateEvent ( this );
		zone->addEvent ( positionUpdateEvent, 250 );
	}*/
}
