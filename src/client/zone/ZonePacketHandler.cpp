//#include "Zone.h"
#include "ZonePacketHandler.h"

/*#include "packets/scene/SceneObjectCreateMessage.h"
#include "packets/scene/UpdateTransformMessage.h"*/

ZonePacketHandler::ZonePacketHandler() : Logger() {
	zone = NULL;
}

ZonePacketHandler::ZonePacketHandler(const String& s, Zone * z) : Logger(s) {
	zone = z;
}

void ZonePacketHandler::handleMessage(Message* pack) {
	info("parsing " + pack->toString(), true);

	sys::uint16 opcount = pack->parseShort();
	sys::uint32 opcode = pack->parseInt();

	switch (opcount) {
	case 02:
		switch (opcode) {
		case 0x1DB575CC: // char create success
			handleCharacterCreateSucessMessage(pack);
			break;
		}
		break;
	case 03:
		/*switch (opcode) {
		case 0x1DB575CC: // char create success
			handleCharacterCreateSucessMessage(pack);
			break;
		}*/
		break;
	case 05:
		switch (opcode) {
		case 0xFE89DDEA: // scene create
			handleSceneObjectCreateMessage(pack);
			break;
		}
		break;
	case 8:
		switch (opcode) {
		case 0x1B24F808: // update transform message
			handleUpdateTransformMessage(pack);
			break;
		}
		break;
	default:
		//error("unhandled operand count" + pack->toString());
		break;
	}
}

void ZonePacketHandler::handleSceneObjectCreateMessage(Message* pack) {
	/*uint64 playerID = pack->parseLong ( );

	Player * player;

	if (zone->hasSelfPlayer())
		player = zone->createPlayer(playerID);
	else
		player = zone->createPlayer(playerID);
		//player = zone->createLocalPlayer(playerID);

	SceneObjectCreateMessage::parseMessage(pack, player);

	zone->insertPlayer(player);
	System::out << "SceneObject [" << hex << playerID << "] created\n";*/
}

void ZonePacketHandler::handleCharacterCreateSucessMessage(Message* pack) {
	/*uint64 charid = pack->parseLong();
	System::out << "Character succesfully created - ID = " << hex << charid << "\n";

	zone->setCharacterID(charid);*/
}

void ZonePacketHandler::handleUpdateTransformMessage(Message* pack) {
	/*uint64 objid = pack->parseLong();

	SceneObject* scno = zone->getObject(objid);

	if (zone->isSelfPlayer((Player*) scno))
		return;

	UpdateTransformMessage::parse(pack, scno);*/
}
