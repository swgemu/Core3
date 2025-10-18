#include "Zone.h"
#include "ZonePacketHandler.h"
#include "ClientCore.h"
#include "client/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/zone/SelectCharacter.h"
#include "server/zone/packets/zone/CmdSceneReady.h"
#include "client/zone/managers/object/ObjectManager.h"
#include "client/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/packets/charcreation/ClientCreateCharacter.h"

ZonePacketHandler::ZonePacketHandler(const String& s, Zone * z) : Logger(s) {
	zone = z;

	setLogging(true);
	setGlobalLogging(true);
	setLogLevel(static_cast<Logger::LogLevel>(ClientCore::getLogLevel()));
}

#define CASE_OPCODE(str) case STRING_HASHCODE(str): what = str

void ZonePacketHandler::handleMessage(Message* pack) {
	Locker lock(this);

	sys::uint16 opcount = pack->parseShort();
	sys::uint32 opcode = pack->parseInt();

	String what;

	switch (opcount) {
	case 1:
		switch (opcode) {
		CASE_OPCODE("CmdSceneReady");
			handleCmdSceneReady(pack);
			break;
		}
	case 2:
		switch (opcode) {
		CASE_OPCODE("ClientCreateCharacterSuccess");
			handleClientCreateCharacterSuccess(pack);
			break;
		CASE_OPCODE("SceneEndBaselines");
			break;
		CASE_OPCODE("ChatPersistentMessageToClient");
			break;
		CASE_OPCODE("ChatServerStatus");
			break;
		CASE_OPCODE("ParametersMessage");
			break;
		CASE_OPCODE("ServerTimeMessage");
			break;
		CASE_OPCODE("ChatRoomList");
			break;
		}
		break;
	case 3:
		switch (opcode) {
		CASE_OPCODE("ClientCreateCharacterFailed");
			handleClientCreateCharacterFailed(pack);
			break;
		CASE_OPCODE("UpdateCellPermissionMessage");
			break;
		CASE_OPCODE("ServerWeatherMessage");
			break;
		CASE_OPCODE("ChatOnGetFriendsList");
			break;
		CASE_OPCODE("ChatOnGetIgnoreList");
			break;
		CASE_OPCODE("ChatOnLeaveRoom");
			break;
		CASE_OPCODE("SceneDestroyObject");
			break;
		}
		break;

	case 4:
		switch (opcode) {
		CASE_OPCODE("ClientPermissionsMessage");
			handleClientPermissionsMessage(pack);
			break;

		CASE_OPCODE("UpdateContainmentMessage");
			handleUpdateContainmentMessage(pack);
			break;

		CASE_OPCODE("ChatSystemMessage");
			handleChatSystemMessage(pack);
			break;

		CASE_OPCODE("UpdatePvpStatusMessage");
			break;
		}
		break;
	case 5:
		switch (opcode) {
		CASE_OPCODE("SceneCreateObjectByCrc");
			handleSceneObjectCreateMessage(pack);
			break;

		CASE_OPCODE("BaselinesMessage");
			handleBaselineMessage(pack);
			break;

		CASE_OPCODE("ChatInstantMessageToClient");
			handleChatInstantMessageToClient(pack);
			break;

		CASE_OPCODE("ObjControllerMessage");
			handleObjectControllerMessage(pack);
			break;

		CASE_OPCODE("DeltasMessage");
			break;

		CASE_OPCODE("ChatOnDestroyRoom");
			break;

		CASE_OPCODE("ChatOnEnteredRoom");
			break;
		}
		break;
	case 9:
		switch (opcode) {
		CASE_OPCODE("CmdStartScene");
			handleCmdStartScene(pack);
			break;
		}
		break;
	}

	if (what.isEmpty()) {
		uint32 count = unknownOpcodes.contains(opcode) ? unknownOpcodes.get(opcode) : 0;
		unknownOpcodes.put(opcode, count + 1);
		what = "unknown";
	}

	debug() << __FUNCTION__ << ": " << what << "(opcount=" << opcount << ", opcode=0x" << uppercase << hex << opcode << ")";
}

void ZonePacketHandler::handleClientPermissionsMessage(Message* pack) {
	info(true) << __FUNCTION__;

	bool canLogin = pack->parseByte();
	bool canCreateRegularCharacter = pack->parseByte();
	bool canCreateJediCharacter = pack->parseByte();
	bool canSkipTutorial = pack->parseByte();

	// Store permissions on zone for actions to check
	zone->setPermissions(canLogin, canCreateRegularCharacter, canCreateJediCharacter, canSkipTutorial);

	info(true) << "Client permissions received:";
	info(true) << "    canLogin = " << canLogin;
	info(true) << "    canCreateCharacter = " << canCreateRegularCharacter;
	info(true) << "    canCreateJedi = " << canCreateJediCharacter;
	info(true) << "    canSkipTutorial = " << canSkipTutorial;
}

void ZonePacketHandler::handleCmdStartScene(Message* pack) {
	info(true) << __FUNCTION__;

	BaseClient* client = (BaseClient*) pack->getClient();

	uint8 unknown = pack->parseByte();
	uint64 selfPlayerObjectID = pack->parseLong();
	String terrain;
	pack->parseAscii(terrain);

	float x = pack->parseFloat();
	float z = pack->parseFloat();
	float y = pack->parseFloat();

	String race;
	pack->parseAscii(race);

	uint64 galacticTime = pack->parseLong();

	// Server confirms our character OID
	Core* instance = Core::getCoreInstance();
	if (instance) {
		ClientCore* clientCore = static_cast<ClientCore*>(instance);
		clientCore->selectedCharacterOid = selfPlayerObjectID;
		clientCore->info(true) << "Server confirmed character OID: " << selfPlayerObjectID;
	}

	BaseMessage* msg = new CmdSceneReady();
	client->sendPacket(msg);

	zone->setSceneStarted();
}

void ZonePacketHandler::handleSceneObjectCreateMessage(Message* pack) {
	BaseClient* client = (BaseClient*) pack->getClient();
	uint64 objectID = pack->parseLong();
	pack->shiftOffset(16);

	float x = pack->parseFloat();
	float z = pack->parseFloat();
	float y = pack->parseFloat();

	uint32 crc = pack->parseInt();

	ObjectManager* objectManager = zone->getObjectManager();
	if (objectManager == nullptr) {
		error("object manager was nullptr");
		return;
	}

	SceneObject* object = objectManager->createObject(crc, objectID);

	if (object == nullptr) {
		client->debug() << "unknown crc 0x" << hex << crc << " received in SceneObjectCreateMessage";
		return;
	}

	object->setClient(zone->getZoneClient());
}

void ZonePacketHandler::handleBaselineMessage(Message* pack) {
	BaseClient* client = (BaseClient*) pack->getClient();

	uint64 oid = pack->parseLong();
	uint32 nametype = pack->parseInt();
	uint8 type = pack->parseByte();

	uint32 size = pack->parseInt();

	uint16 opcount = pack->parseShort();

	SceneObject* object = zone->getObject(oid);

	if (object == nullptr) {
		client->debug("received baseline for null object");
		return;
	}

	Locker objectLocker(object);

	switch (type) {
	case 3:
		object->parseBaseline3(pack);
		break;
	case 6:
		object->parseBaseline6(pack);
		break;
	default:
		break;
	}
}

void ZonePacketHandler::handleChatInstantMessageToClient(Message* pack) {
	BaseClient* client = (BaseClient*) pack->getClient();

	String game, galaxy, name;
	UnicodeString message;

	pack->parseAscii(game);
	pack->parseAscii(galaxy);
	pack->parseAscii(name);
	pack->parseUnicode(message);

	StringBuffer infoMsg;
	infoMsg << "instant message from [" << name << "] : " << message.toString();
	client->info(infoMsg.toString());
}

void ZonePacketHandler::handleChatSystemMessage(Message* pack) {
	info(true) << __FUNCTION__;

	BaseClient* client = (BaseClient*) pack->getClient();

	uint8 type = pack->parseByte();

	UnicodeString message;
	pack->parseUnicode(message);

	info(true) << "type=" << type << "; len=" << message.length();

	StringTokenizer lines(message.toString());
	lines.setDelimeter("\n");

	while (lines.hasMoreTokens()) {
		String line;
		lines.getStringToken(line);
		info(true) << "> " << line;
	}
}

void ZonePacketHandler::handleObjectControllerMessage(Message* pack) {
	uint32 header1 = pack->parseInt();
	uint32 header2 = pack->parseInt();

	uint64 objectID = pack->parseLong();

	pack->parseInt();

	SceneObject* object = zone->getObject(objectID);

	if (object != nullptr) {
		// No object controller handling needed
	}
}

void ZonePacketHandler::handleUpdateContainmentMessage(Message* pack) {
	uint64 obj = pack->parseLong();
	uint64 par = pack->parseLong();

	int type = pack->parseInt();

	SceneObject* object = zone->getObject(obj);
	SceneObject* parent = zone->getObject(par);

	if (object == nullptr)
		return;

	if (par == 0) {
		// remove object from parent
		parent = object->getParent();

		if (parent != nullptr) {
			// No container removal needed
		} else {
			object->setParent(nullptr);
		}

		return;
	} else if (parent == nullptr) {
		return;
	}

	// No container transfer needed
}

void ZonePacketHandler::handleCmdSceneReady(Message* pack) {
	info(true) << __FUNCTION__;

	zone->setSceneReady();
}

void ZonePacketHandler::handleClientCreateCharacterSuccess(Message* pack) {
	info(true) << __FUNCTION__;

	uint64 newCharacterOID = pack->parseLong();

	info(true) << "Character creation SUCCESS - OID: " << newCharacterOID;

	zone->setCharacterCreated(newCharacterOID);

	// Now send SelectCharacter with the new OID
	BaseClient* client = (BaseClient*) pack->getClient();
	info(true) << "Sending SelectCharacter(" << newCharacterOID << ")";

	BaseMessage* selectChar = new SelectCharacter(newCharacterOID);
	client->sendPacket(selectChar);
}

void ZonePacketHandler::handleClientCreateCharacterFailed(Message* pack) {
	info(true) << __FUNCTION__;

	uint32 unicodeLength = pack->parseInt();
	String uiFile;
	pack->parseAscii(uiFile);
	uint32 spacer = pack->parseInt();
	String errorCode;
	pack->parseAscii(errorCode);

	error() << "Character creation FAILED";
	error() << "  Error code: " << errorCode;
	error() << "  UI file: " << uiFile;

	zone->setCharacterCreationFailed();
}
