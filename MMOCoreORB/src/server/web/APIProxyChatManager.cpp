/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyChatManager.cpp
 * @created     : Sun Mar  8 19:23:02 UTC 2020
 */

#ifdef WITH_REST_API

#include "engine/engine.h"
#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"
#include "server/login/account/AccountManager.h"
#include "server/chat/ChatManager.h"
#include "server/zone/packets/chat/ChatInstantMessageToClient.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/credits/CreditObject.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/chat/PersistentMessage.h"

#include "APIProxyChatManager.h"
#include "APIRequest.h"

/**
 * Example calls:
 *
 * POST /v1/chat/message { "body": "Test from API", "from": "externalGhost", "to": "playerOne" }
 * - Send chat message (whisper) to playerOne from externalGhost
 *
 * POST /v1/chat/message { "body": "Test from API", "from": "externalGhost", "to": "playerOne;playerTwo" }
 * - Send chat message to list of players (playerOne, playerTwo)
 *
 * POST /v1/chat/message { "body": "This is a test email.", "from": "Darth Vader", "to": "guild:Feds" }
 * - Send chat message to all members of guild abbrev "Feds" from Darth Vader.
 *
 * POST /v1/chat/message { "body": "Test from API", "from": "externalGhost", "to": "@online" }
 * - Send chat message (whisper) to all online players from externalGhost
 *
 * POST /v1/chat/mail { "body": "This is a test email.", "from": "Imperial Tax Authority", "subject": "API Test", "to": "playerOne" }
 * - Send mail to playerOne
 *
 * POST /v1/chat/mail{ "body": "Test from API", "from": "externalGhost", "subject": "multi-test", "to": "playerOne;playerTwo" }
 * - Send mail to list of players (playerOne, playerTwo)
 *
 * POST /v1/chat/mail { "body": "This is a test email.", "from": "Darth Vader", "subject": "API Test", "to": "guild:Feds" }
 * - Send mail to all members of guild abbrev "Feds" from Darth Vader.
 *
 * POST /v1/chat/mail { "body": "This is a test email.", "from": "Darth Vader", "subject": "API Test", "to": "@online" }
 * - Send mail to all online players from Darth Vader.
 *
 * POST /v1/chat/galaxy { "body": "Test broadcast to galaxy", "from": "playerOne" }
 * - Send broadcast to galaxy
 */

namespace server {
 namespace web3 {

String APIProxyChatManager::expandTo(String toExpr, Function<String(String playerName)> process, bool skipOffline) const {
	auto server = getZoneServer();

	if (server == nullptr) {
		return "getZoneServer failed.";
	}

	auto playerManager = server->getPlayerManager();
	Vector<String> players;

	if (toExpr.contains(";")) {
		StringTokenizer tokenizer(toExpr);
		tokenizer.setDelimeter(";");

		while (tokenizer.hasMoreTokens()) {
			String playerName;
			tokenizer.getStringToken(playerName);
			players.emplace(playerName);
		}
	} else if (toExpr == "@online") {
		auto playerList = playerManager->getOnlinePlayerList();

		for (int i = 0; i < playerList.size(); i++) {
			auto playerID = playerList.get(i);
			auto playerName = playerManager->getPlayerName(playerID);

			if (!playerName.isEmpty()) {
				players.emplace(playerName);
			}
		}
	} else if (toExpr.beginsWith("guild:")) {
		auto guildAbbrev = toExpr.subString(toExpr.indexOf(":") + 1);
		auto guild = server->getGuildManager()->getGuildFromAbbrev(guildAbbrev);

		if (guild == nullptr) {
			return "Did not find guild [" + guildAbbrev + "]";
		}

		Locker lock(guild);
		auto memberList = guild->getGuildMemberList();

		if (memberList == nullptr) {
			return "Did not find members for guild [" + guildAbbrev + "]";
		}

		for (int i = 0;i < memberList->size(); ++i) {
			auto memberInfo = &memberList->get(i);

			if (memberInfo != nullptr) {
				auto playerName = playerManager->getPlayerName(memberInfo->getPlayerID());

				if (!playerName.isEmpty()) {
					players.emplace(playerName);
				}
			}
		}
	} else {
		players.emplace(toExpr);
	}

	auto chatManager = getChatManager();

	for (const auto& playerName : players) {
		if (skipOffline && chatManager->getPlayer(playerName) == nullptr) {
			continue;
		}

		auto errMsg = process(playerName);

		if (!errMsg.isEmpty()) {
			return errMsg;
		}
	}

	return "";
}

void APIProxyChatManager::handle(APIRequest& apiRequest) {
	if (!apiRequest.isMethodPOST()) {
		apiRequest.fail("Only supports POST");
		return;
	}

	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		apiRequest.fail("zoneServer not found.");
		return;
	}

	if (zoneServer->isServerLoading()) {
		apiRequest.fail("zoneServer is loading.");
		return;
	}

	auto msgType = apiRequest.getPathFieldString("msgType", true);

	if (msgType.isEmpty()) {
		apiRequest.fail("Invalid request, missing message type!");
		return;
	}

	msgType = msgType.toLowerCase();

	if (msgType != "mail" && msgType != "message" && msgType != "galaxy") {
		apiRequest.fail("Invalid request, unsupported type: " + msgType);
		return;
	}

	if (!apiRequest.parseRequestJSON())
		return;

	auto from = apiRequest.getRequestFieldString("from", false, "SKYNET");

	auto to = apiRequest.getRequestFieldString("to", false, "");

	if (to.isEmpty() && msgType != "galaxy") {
		apiRequest.fail("Invalid request, to is empty.");
		return;
	}

	auto body = apiRequest.getRequestFieldString("body", true);

	if (body.isEmpty()) {
		apiRequest.fail("Invalid request, body is empty.");
		return;
	}

	auto chatManager = getChatManager();

	if (chatManager == nullptr) {
		apiRequest.fail("Unable to get chatManager");
		return;
	}

	JSONSerializationType result;

	result["request"] = apiRequest.getRequestJSON();

	if (msgType == "galaxy") {
		Reference<CreatureObject*> player = chatManager->getPlayer(from);
		chatManager->broadcastGalaxy(player, body);
		result["count_sent"] = chatManager->getPlayerCount();
		result["action_result"] = "SUCCESS";
	} else if (msgType == "mail") {
		StringIdChatParameterVector stringIdParameters;
		WaypointChatParameterVector waypointParameters;

		int countSent = 0;
		auto subject = apiRequest.getRequestFieldString("subject", true);

		if (subject.isEmpty()) {
			apiRequest.fail("Invalid request, subject is empty.");
			return;
		}

		JSONSerializationType sent;

		auto errMsg = expandTo(to, [&] (String playerName) -> String {

			Reference<PersistentMessage*> msg;

			auto ret = chatManager->sendMail(from, subject, body, playerName, &stringIdParameters, &waypointParameters, &msg);

			if (ret != ChatManager::IM_SUCCESS) {
				return "sendMail [" + playerName + "] failed, ret=0x" + String::hexvalueOf(ret);
			}

			auto mail = msg.get();

			if (mail != nullptr) {
				sent[playerName] = mail->getObjectID();
			}

			countSent++;
			return "";
		}, false);

		result["count_sent"] = countSent;
		result["action_result"] = errMsg.isEmpty() ? "SUCCESS" : "FAILED";
		result["sent"] = sent;

		if (!errMsg.isEmpty()) {
			result["action_error"] = errMsg;
		}
	} else if (msgType == "message") {
		int countSent = 0;
		auto errMsg = expandTo(to, [&] (String playerName) -> String {
			Reference<CreatureObject*> player = chatManager->getPlayer(playerName);

			if (player == nullptr) {
				auto msg = "Invalid request, player [" + playerName + "] not found";
				apiRequest.fail(msg);
				return msg;
			}

			Locker lock(player);
			player->sendMessage(new ChatInstantMessageToClient("SWG", getZoneServer()->getGalaxyName(), from, body));
			countSent++;
			return "";
		}, true);

		result["count_sent"] = countSent;
		result["action_result"] = errMsg.isEmpty() ? "SUCCESS" : "FAILED";

		if (!errMsg.isEmpty()) {
			result["action_error"] = errMsg;
		}
	}

	apiRequest.info(true)
		<< msgType << " from: "
		<< from << "; to: "
		<< to << "; body: "
		<< body.replaceAll("\n", "\\n") << "; "
		<< "result = " << result["action_result"].get<std::string>();

	apiRequest.success(result);
}

server::chat::ChatManager *APIProxyChatManager::getChatManager() const {
	auto server = getZoneServer();

	if (server == nullptr) {
		return nullptr;
	}

	return server->getChatManager();
}

}
}

#endif // WITH_REST_API
