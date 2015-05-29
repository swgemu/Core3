#include "engine/engine.h"

#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
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

	if (!reactionRanks.isValidTable()) {
		error("Invalid imperialReactionRanks table.");
	} else {
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

	if (!luaObject.isValidTable()) {
		error("Invalid emoteReactionFines table.");
	} else {
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

void ReactionManagerImplementation::sendChatReaction(AiAgent* npc, int type, int state, bool force) {
	StringBuffer message;

	if (npc->getReactionStf() != "") {
		message << npc->getReactionStf();
	} else {
		return;
	}

	int chance = 0;
	String typeString;

	switch(type) {
	case ReactionManager::ALERT: // TODO: add trigger
		chance = 25;
		typeString = "alert_";
		break;
	case ReactionManager::ALLY: // TODO: add trigger
		chance = 25;
		typeString = "ally_";
		break;
	case ReactionManager::ASSIST:
		chance = 25;
		typeString = "assist_";
		break;
	case ReactionManager::ATTACKED:
		chance = 25;
		typeString = "attacked_";
		break;
	case ReactionManager::BYE:
		chance = 25;
		typeString = "bye_";
		break;
	case ReactionManager::CALM:
		chance = 25;
		typeString = "calm_";
		break;
	case ReactionManager::DEATH:
		chance = 50;
		typeString = "death_";
		break;
	case ReactionManager::FLEE:
		chance = 25;
		typeString = "flee_";
		break;
	case ReactionManager::GLOAT:
		chance = 100;
		typeString = "gloat_";
		break;
	case ReactionManager::HELP:
		chance = 10;
		typeString = "help_";
		break;
	case ReactionManager::HI:
		chance = 25;
		typeString = "hi_";
		break;
	case ReactionManager::HIT:
		chance = 10;
		typeString = "hit_";
		break;
	case ReactionManager::HITTARGET:
		chance = 10;
		typeString = "hit_target_";
		break;
	case ReactionManager::THREAT: // TODO: add trigger
		chance = 25;
		typeString = "threat_";
		break;
	default:
		return;
		break;
	}

	switch (state) {
	case ReactionManager::NONE:
		break;
	case ReactionManager::NICE:
		typeString = typeString + "nice_";
		break;
	case ReactionManager::MID:
		typeString = typeString + "mid_";
		break;
	case ReactionManager::MEAN:
		typeString = typeString + "mean_";
		break;
	default:
		return;
		break;
	}

	if (force || System::random(99) < chance) {
		int num = System::random(15) + 1;

		// All of the reaction stfs are missing attacked_15
		if (type == ReactionManager::ATTACKED && num == 15)
			return;

		message << ":" << typeString << num;
		StringIdChatParameter chat;
		chat.setStringId(message.toString());
		zoneServer->getChatManager()->broadcastMessage(npc,chat,0,0,0);

		npc->getCooldownTimerMap()->updateToCurrentAndAddMili("reaction_chat", 60000); // 60 second cooldown
	}
}

void ReactionManagerImplementation::emoteReaction(CreatureObject* emoteUser, AiAgent* emoteTarget, int emoteid) {
	if (emoteUser == NULL || emoteTarget == NULL)
		return;

	Zone* zone = emoteUser->getZone();

	if (zone == NULL)
		return;

	if (emoteTarget->isIncapacitated() || emoteTarget->isDead() || emoteTarget->isInCombat())
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
		doKnockdown(emoteUser, emoteTarget);
	}

	if (reactionFine->getCreditFine() != 0) {
		StringBuffer suiFineMsg;
		suiFineMsg << "@stormtrooper_attitude/st_response:imperial_fine_" << String::valueOf(reactionFine->getCreditFine());
		if (playerObject->getReactionFines() != 0) {
			suiFineMsg << " @stormtrooper_attitude/st_response:imperial_fine_outstanding " << String::valueOf(playerObject->getReactionFines() + reactionFine->getCreditFine()) << " @stormtrooper_attitude/st_response:imperial_fine_credits";
		} else {
			playerObject->updateReactionFineTimestamp();
		}
		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(emoteUser, SuiWindowType::REACTION_FINE);
		box->setPromptTitle("@stormtrooper_attitude/st_response:imperial_fine_t"); // Imperial Fine
		box->setPromptText(suiFineMsg.toString());
		box->setCallback(new ReactionFinePaymentSuiCallback(zoneServer));
		box->setUsingObject(emoteTarget);
		box->setForceCloseDistance(16.f);

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

void ReactionManagerImplementation::doKnockdown(CreatureObject* victim, AiAgent* attacker) {
	String knockdownAnim = "";

	WeaponObject* weapon = attacker->getWeapon();

	if (weapon != NULL && weapon->isRangedWeapon())
		knockdownAnim = "ranged_melee_light";
	else
		knockdownAnim = "attack_high_center_light_0";

	// TODO: Get knockdown animation working
	//attacker->doCombatAnimation(victim, knockdownAnim.hashCode(), 0, 0xFF);

	victim->inflictDamage(attacker, CreatureAttribute::MIND, victim->getHAM(CreatureAttribute::MIND) + 200, true);

}

void ReactionManagerImplementation::doReactionFineMailCheck(CreatureObject* player) {
	if (player == NULL)
		return;

	PlayerObject* playerObject = player->getPlayerObject();

	if (playerObject == NULL)
		return;

	ChatManager* chatManager = zoneServer->getChatManager();

	if (chatManager == NULL)
		return;

	if (playerObject->getReactionFines() == 0)
		return;

	int weekLength = 7 * 24 * 60 * 60 * 1000;
	int dayLength = 24 * 60 * 60 * 1000;

	Time currentTime;

	uint32 timeDiff = currentTime.getMiliTime() - playerObject->getReactionFineTimestamp()->getMiliTime();

	// Don't send mail until fine is a week overdue
	if (timeDiff < weekLength)
		return;

	uint32 mailTimeDiff = currentTime.getMiliTime() - playerObject->getReactionFineMailTimestamp()->getMiliTime();

	// Don't send more than one mail a day
	if (mailTimeDiff < dayLength)
		return;

	// Mail has been sent at least once since player received fine, send overdue notice
	if (playerObject->getReactionFineMailTimestamp()->getMiliTime() > playerObject->getReactionFineTimestamp()->getMiliTime()) {
		chatManager->sendMail("@stormtrooper_attitude/st_response:imperial_collection_email_t", "@stormtrooper_attitude/st_response:st_overdue_fine_warning_02", "@stormtrooper_attitude/st_response:st_overdue_fine_warning_01", player->getFirstName());
	} else {
		chatManager->sendMail("@stormtrooper_attitude/st_response:imperial_collection_email_t", "@stormtrooper_attitude/st_response:st_overdue_fine_warning_02", "@stormtrooper_attitude/st_response:st_overdue_fine_warning_00", player->getFirstName());
	}

	playerObject->updateReactionFineMailTimestamp();
}
