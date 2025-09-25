/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ZONEPACKETHANDLER_H_
#define ZONEPACKETHANDLER_H_

#include "engine/log/Logger.h"

class Zone;

class ZonePacketHandler : public Mutex, public Logger {
	Zone* zone;
	AtomicInteger packetCount;

public:
	ZonePacketHandler(const String& s, Zone * z);

	~ZonePacketHandler() {
	}

	int getPacketCount() {
		return packetCount.get();
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
	void handleCmdSceneReady(Message* pack);
};

#endif /* ZONEPACKETHANDLER_H_ */
