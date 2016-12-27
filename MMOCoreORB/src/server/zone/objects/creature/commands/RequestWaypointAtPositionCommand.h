/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTWAYPOINTATPOSITIONCOMMAND_H_
#define REQUESTWAYPOINTATPOSITIONCOMMAND_H_

class RequestWaypointAtPositionCommand : public QueueCommand {
public:

	RequestWaypointAtPositionCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		//'naboo 2527.300049 0.000000 1696.300049 parking garage general'

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		UnicodeTokenizer tokenizer(arguments);

		try {
			String planet;
			tokenizer.getStringToken(planet);

			float x = tokenizer.getFloatToken();
			float z = tokenizer.getFloatToken();
			float y = tokenizer.getFloatToken();

			UnicodeString name;
			tokenizer.finalToken(name);

			x = (x < -8192) ? -8192 : x;
			x = (x > 8192) ? 8192 : x;

			y = (y < -8192) ? -8192 : y;
			y = (y > 8192) ? 8192 : y;

			Reference<PlayerObject*> playerObject = creature->getSlottedObject("ghost").castTo<PlayerObject*>( );

			ManagedReference<WaypointObject*> obj = ( server->getZoneServer()->createObject(0xc456e788, 1)).castTo<WaypointObject*>();

			Locker locker(obj);

			obj->setPlanetCRC(planet.hashCode());
			obj->setPosition(x, z, y);
			obj->setCustomObjectName(name, false);
			obj->setActive(true);

			playerObject->addWaypoint(obj, false, true); // Should second argument be true, and waypoints with the same name thus remove their old version?

		} catch (Exception& e) {

		}

		return SUCCESS;
	}

};

#endif //REQUESTWAYPOINTATPOSITIONCOMMAND_H_
