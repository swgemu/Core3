#include "engine/engine.h"

#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/ReactionFinePaymentSuiCallback.h"

void ReactionManagerImplementation::loadLuaConfig() {
	Lua* lua = new Lua();
	lua->init();

	if (!lua->runFile("scripts/managers/reaction_manager.lua")) {
		error("Cannot read reaction manager data.");
		return;
	}

	LuaObject emoteReactions = lua->getGlobalObject("emoteReactionLevels");

	if (!emoteReactions.isValidTable()) {
		error("Invalid emoteReactionLevels table.");
	} else {

		for(int i = 1; i <= emoteReactions.getTableSize(); ++i) {
			LuaObject entry = emoteReactions.getObjectAt(i);

			String emote = entry.getStringAt(1);
			int level = entry.getIntAt(2);

			reactionEmotes.put(emote, level);

			entry.pop();
		}

		emoteReactions.pop();
	}

	LuaObject reactionRanks = lua->getGlobalObject("imperialReactionRanks");

	if (reactionRanks.isValidTable()) {
		for(int i = 1; i <= reactionRanks.getTableSize(); ++i) {
			LuaObject entry = reactionRanks.getObjectAt(i);

			String name = entry.getStringAt(1);
			int min = entry.getIntAt(2);
			int max = entry.getIntAt(3);

			Reference<ReactionRankData*> data = new ReactionRankData(name, min, max);

			reactionRankData.add(data);

			entry.pop();
		}

		reactionRanks.pop();
	}

	LuaObject luaObject = lua->getGlobalObject("emoteReactionFines");

	if (luaObject.isValidTable()) {
		for (int i = 1; i <= luaObject.getTableSize(); ++i) {
			LuaObject reactionData = luaObject.getObjectAt(i);

			if (reactionData.isValidTable()) {
				int reactLevel = reactionData.getIntAt(1);
				bool isImperial = reactionData.getBooleanAt(2);
				bool isHuman = reactionData.getBooleanAt(3);
				int rankCompare = reactionData.getIntAt(4);
				int creditFine = reactionData.getIntAt(5);
				int factionFine = reactionData.getIntAt(6);
				bool doKnockdown = reactionData.getBooleanAt(7);
				int minQuip = reactionData.getIntAt(8);
				int maxQuip = reactionData.getIntAt(9);
				String responseEmote = reactionData.getStringAt(10);

				Reference<EmoteReactionFine*> data = new EmoteReactionFine(reactLevel, isImperial, isHuman, rankCompare, creditFine, factionFine, doKnockdown, minQuip, maxQuip, responseEmote);

				emoteReactionFines.add(data);
			}

			reactionData.pop();
		}

		luaObject.pop();
	}

	info("Loaded " + String::valueOf(emoteReactionFines.size()) + " emote reaction records.", true);
}

void ReactionManagerImplementation::emoteReaction(CreatureObject* emoteUser, AiAgent* emoteTarget, int emoteid) {
	if (emoteUser == NULL || emoteTarget == NULL)
		return;

	Zone* zone = emoteUser->getZone();

	if (zone == NULL)
		return;

	// Only Imperials react to emotes (non droids)
	if (!emoteTarget->isImperial() || emoteTarget->isDroidObject())
		return;

	ChatManager* chatManager = zoneServer->getChatManager();
	PlayerObject* playerObject = emoteUser->getPlayerObject();

	if (playerObject == NULL)
		return;

	if (emoteTarget->getDistanceTo(emoteUser) > 16.f)
		return;

	String socialType = chatManager->getSocialType(emoteid);

	// Handle hail if player has existing fines
	if (socialType == "hail" && playerObject->getReactionFines() != 0) {
		StringBuffer suiFineMsg;
		suiFineMsg << "@stormtrooper_attitude/st_response:pay_outstanding_fine_prefix \n \n @stormtrooper_attitude/st_response:pay_fine_total_suffix ";
		suiFineMsg << String::valueOf(playerObject->getReactionFines()) << " @stormtrooper_attitude/st_response:imperial_fine_credits";

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(emoteUser, SuiWindowType::REACTION_FINE);
		box->setPromptTitle("@stormtrooper_attitude/st_response:imperial_fine_t"); // Imperial Fine
		box->setPromptText(suiFineMsg.toString());
		box->setCallback(new ReactionFinePaymentSuiCallback(zoneServer));
		box->setUsingObject(emoteTarget);
		box->setForceCloseDistance(16.f);
		playerObject->addSuiBox(box);
		emoteUser->sendMessage(box->generateMessage());

		return;
	}

	int reactionLevel = getReactionLevel(socialType);

	if (reactionLevel == 0)
		return;

	EmoteReactionFine* reactionFine = getEmoteReactionFine(emoteUser, emoteTarget, reactionLevel);

	// No reaction if there is no fine data
	if (reactionFine == NULL)
		return;

	int randomQuip = reactionFine->getRandomQuip();

	if (randomQuip != -1) {
		StringIdChatParameter param(getReactionQuip(randomQuip));
		param.setTT(emoteUser->getObjectID());
		chatManager->broadcastMessage(emoteTarget, param, 0, 0, 0);
	}

	if (reactionFine->getFactionFine() != 0)
		playerObject->decreaseFactionStanding("imperial", reactionFine->getFactionFine());

	if (reactionFine->shouldKnockdown()) {
		// TODO: add knockdown functionality
	}

	if (reactionFine->getCreditFine() != 0) {
		StringBuffer suiFineMsg;
		suiFineMsg << "@stormtrooper_attitude/st_response:imperial_fine_" << String::valueOf(reactionFine->getCreditFine());
		if (playerObject->getReactionFines() != 0) {
			suiFineMsg << " @stormtrooper_attitude/st_response:imperial_fine_outstanding " << String::valueOf(playerObject->getReactionFines() + reactionFine->getCreditFine()) << " @stormtrooper_attitude/st_response:imperial_fine_credits";
		}
		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(emoteUser, SuiWindowType::REACTION_FINE);
		box->setPromptTitle("@stormtrooper_attitude/st_response:imperial_fine_t"); // Imperial Fine
		box->setPromptText(suiFineMsg.toString());

		playerObject->addSuiBox(box);
		emoteUser->sendMessage(box->generateMessage());

		playerObject->addToReactionFines(reactionFine->getCreditFine());

	}
}

EmoteReactionFine* ReactionManagerImplementation::getEmoteReactionFine(CreatureObject* emoteUser, AiAgent* emoteTarget, int level) {
	if (emoteUser == NULL)
		return NULL;

	int rankCompare = 0;

	if (emoteUser->isImperial()) {
		int userFactionRank = emoteUser->getFactionRank();
		int targetReactionRank = emoteTarget->getReactionRank();

		if (targetReactionRank == 0) {
			Reference<ReactionRankData*> rankData = getReactionRankData(emoteTarget->getCreatureTemplate()->getTemplateName());

			if (rankData == NULL)
				return NULL;

			targetReactionRank = rankData->getRandomRank();

			// No reaction if the target has no reaction rank
			if (targetReactionRank == 0)
				return NULL;

			// Set rank to creature object so that it isnt randomized on every emote
			emoteTarget->setReactionRank(targetReactionRank);
		}

		if (userFactionRank > targetReactionRank) {
			rankCompare = 1;
		} else if (userFactionRank < targetReactionRank) {
			rankCompare = -1;
		} else if (userFactionRank == targetReactionRank) {
			rankCompare = 0;
		}

	}

	for (int i = 0; i < emoteReactionFines.size(); i++) {
		Reference<EmoteReactionFine*> data = emoteReactionFines.get(i);

		if (level == data->getReactionLevel() && emoteUser->isImperial() == data->isImperial() && data->isHuman() == (emoteUser->getSpecies() == 0)) {
			if (data->isImperial()) {
				if (rankCompare == data->getRankComparison()) {
					return data;
				} else {
					continue;
				}
			} else {
				return data;
			}
		}
	}

	return NULL;
}

ReactionRankData* ReactionManagerImplementation::getReactionRankData(const String& name) {
	for (int i = 0; i < reactionRankData.size(); i++) {
		Reference<ReactionRankData*> data = reactionRankData.get(i);

		if (data->getTemplateName() == name)
			return data;
	}

	return NULL;
}

String ReactionManagerImplementation::getReactionQuip(int num) {
	StringBuffer quip;
	quip << "@stormtrooper_attitude/st_response:st_response_";

	if (num < 10)
		quip << "0";

	quip << String::valueOf(num);

	return quip.toString();
}
