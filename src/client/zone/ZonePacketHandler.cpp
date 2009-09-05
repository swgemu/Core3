#include "Zone.h"
#include "ZonePacketHandler.h"

/*#include "packets/scene/SceneObjectCreateMessage.h"
#include "packets/scene/UpdateTransformMessage.h"*/
#include "ZoneClient.h"
#include "../../server/zone/packets/zone/SelectCharacter.h"


ZonePacketHandler::ZonePacketHandler(const String& s, Zone * z) : Logger(s) {
	zone = z;
}

void ZonePacketHandler::handleMessage(Message* pack) {
	info("parsing " + pack->toStringData(), true);

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
		switch (opcode) {

		case 0xDF333C6E: // char create failure
			handleCharacterCreateFailureMessage(pack);
			break;

		}
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
	ZoneClient* client = (ZoneClient*) pack->getClient();

	uint64 charid = pack->parseLong();

	StringBuffer msg;
	msg << "Character succesfully created - ID = 0x" << hex << charid;
	client->info(msg.toString(), true);

	zone->setCharacterID(charid);

	BaseMessage* selectChar = new SelectCharacter(charid);
	client->sendMessage(selectChar);
}

void ZonePacketHandler::handleUpdateTransformMessage(Message* pack) {
	/*uint64 objid = pack->parseLong();

	SceneObject* scno = zone->getObject(objid);

	if (zone->isSelfPlayer((Player*) scno))
		return;

	UpdateTransformMessage::parse(pack, scno);*/
}

void ZonePacketHandler::handleCharacterCreateFailureMessage(Message* pack) {
	ZoneClient* client = (ZoneClient*) pack->getClient();
	uint32 int1 = pack->parseInt();
	String ui;
	pack->parseAscii(ui);

	uint32 int2 = pack->parseInt();

	String error;
	pack->parseAscii(error);

	client->error(error);
}
