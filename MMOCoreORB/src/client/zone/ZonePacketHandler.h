/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ZONEPACKETHANDLER_H_
#define ZONEPACKETHANDLER_H_

#include "engine/engine.h"

class Zone;

class ZonePacketHandler : public Logger {
	Zone* zone;

public:
	ZonePacketHandler(const String& s, Zone * z);

	~ZonePacketHandler() {
	}

	void handleMessage(Message* pack);
	void handleSceneObjectCreateMessage(Message* pack);
	void handleCharacterCreateSucessMessage(Message* pack);
	void handleUpdateTransformMessage(Message* pack);
	void handleCharacterCreateFailureMessage(Message* pack);
	void handleCmdStartScene(Message* pack);
	void handleBaselineMessage(Message* pack);
	void handleChatInstantMessageToClient(Message* pack);
	void handleChatSystemMessage(Message* pack);
	void handleObjectControllerMessage(Message* pack);
	void handleUpdateContainmentMessage(Message* pack);
	void handleSceneObejctDestroyMessage(Message* pack);
	void handleClientPermissionsMessage(Message* pack);

};

#endif /* ZONEPACKETHANDLER_H_ */
