#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/ReactionFinePaymentSuiCallback.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/planet/PlanetManager.h"

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

	delete lua;
	lua = nullptr;
}

void ReactionManagerImplementation::sendChatReaction(AiAgent* npc, SceneObject* object, int type, int state, bool force) {
	if (npc == nullptr)
		return;

	if (!force) {
		Zone* zone = npc->getZone();

		if (zone != nullptr) {
			PlanetManager* planetManager = zone->getPlanetManager();

			if (planetManager != nullptr) {
				bool failRoll = false;

				CityRegion* cityRegion = planetManager->getCityRegionAt(npc->getPositionX(), npc->getPositionY());

				if (cityRegion != nullptr) {
					if (cityRegion->isClientRegion() && System::random(100) > 1) {
						failRoll = true;
					}
				} else if (System::random(10) < 9) {
					failRoll = true;
				}

				if (failRoll) {
					npc->getCooldownTimerMap()->updateToCurrentAndAddMili("reaction_chat", (System::random(30) + 60) * 1000);
					return;
				}
			}

		}
	}

	StringBuffer message;

	if (npc->getReactionStf() != "") {
		message << npc->getReactionStf();
	} else {
		return;
	}

	String typeString;

	switch(type) {
	case ReactionManager::ALERT:
		typeString = "alert_";
		break;
	case ReactionManager::ALLY:
		typeString = "ally_";
		break;
	case ReactionManager::ASSIST:
		typeString = "assist_";
		break;
	case ReactionManager::ATTACKED:
		typeString = "attacked_";
		break;
	case ReactionManager::BYE:
		typeString = "bye_";
		break;
	case ReactionManager::CALM:
		typeString = "calm_";
		break;
	case ReactionManager::DEATH:
		typeString = "death_";
		break;
	case ReactionManager::FLEE:
		typeString = "flee_";
		break;
	case ReactionManager::GLOAT:
		typeString = "gloat_";
		break;
	case ReactionManager::HELP:
		typeString = "help_";
		break;
	case ReactionManager::HI:
		typeString = "hi_";
		break;
	case ReactionManager::HIT:
		typeString = "hit_";
		break;
	case ReactionManager::HITTARGET:
		typeString = "hit_target_";
		break;
	case ReactionManager::THREAT: // TODO: add trigger
		typeString = "threat_";
		break;
	default:
		return;
		break;
	}

	if (object != nullptr && object->isCreatureObject()) {
		CreatureObject* creoObject = object->asCreatureObject();

		if (creoObject == nullptr || creoObject->getActiveSession(SessionFacadeType::CONTRABANDSCAN) != nullptr) {
			npc->getCooldownTimerMap()->updateToCurrentAndAddMili("reaction_chat", 180 * 1000);
			return;
		}

		if (state == 0 && (type == ReactionManager::HI || type == ReactionManager::BYE)) {
			String factionString = npc->getFactionString();
			uint32 aiFaction = npc->getFaction();
			uint32 targetFaction = creoObject->getFaction();

			if (aiFaction != 0) {
				if (targetFaction == aiFaction)
					state = ReactionManager::NICE;
				else if (targetFaction == 0)
					state = ReactionManager::MID;
				else {
					state = ReactionManager::MEAN;
				}
			} else if (!factionString.isEmpty()) {
				PlayerObject* pGhost = creoObject->getPlayerObject();

				if (pGhost != nullptr) {
					int standing = pGhost->getFactionStanding(factionString);
					if (standing >= 3000)
						state = ReactionManager::NICE;
					else if (standing <= -3000)
						state = ReactionManager::MEAN;
					else
						state = ReactionManager::MID;
				}
			} else
				state = ReactionManager::MID;
		}
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

	int num = System::random(15) + 1;

	// All of the reaction stfs are missing attacked_15
	if (type == ReactionManager::ATTACKED && num == 15)
		return;

	message << ":" << typeString << num;
	StringIdChatParameter chat;
	chat.setStringId(message.toString());
	zoneServer->getChatManager()->broadcastChatMessage(npc, chat, 0, 0, npc->getMoodID());

	npc->getCooldownTimerMap()->updateToCurrentAndAddMili("reaction_chat", (System::random(30) + 60) * 1000);
}

void ReactionManagerImplementation::emoteReaction(CreatureObject* emoteUser, AiAgent* emoteTarget, int emoteid) {
	if (emoteUser == nullptr || emoteTarget == nullptr)
		return;

	Zone* zone = emoteUser->getZone();

	if (zone == nullptr || zone->getZoneName() == "tutorial")
		return;

	if (emoteTarget->isIncapacitated() || emoteTarget->isDead() || emoteTarget->isInCombat())
		return;

	// Only Imperials react to emotes (non droids)
	if (!emoteTarget->isImperial() || emoteTarget->isDroidObject())
		return;

	ChatManager* chatManager = zoneServer->getChatManager();
	PlayerObject* playerObject = emoteUser->getPlayerObject();

	if (chatManager == nullptr || playerObject == nullptr)
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
		box->setForceCloseDistance(20.f);
		playerObject->addSuiBox(box);
		emoteUser->sendMessage(box->generateMessage());

		return;
	}

	int reactionLevel = getReactionLevel(socialType);

	if (reactionLevel == 0)
		return;

	reactionFine(emoteUser, emoteTarget, reactionLevel);
}

void ReactionManagerImplementation::reactionFine(CreatureObject* emoteUser, AiAgent* emoteTarget, int reactionLevel) {
	if (emoteUser == nullptr || emoteTarget == nullptr)
		return;

	ZoneServer* zonerServer = emoteUser->getZoneServer();

	if (zoneServer == nullptr)
		return;

	PlayerObject* ghost = emoteUser->getPlayerObject();
	ChatManager* chatManager = zoneServer->getChatManager();

	if (ghost == nullptr)
		return;

	EmoteReactionFine* reactionFine = getEmoteReactionFine(emoteUser, emoteTarget, reactionLevel);

	// No reaction if there is no fine data
	if (reactionFine == nullptr)
		return;

	int randomQuip = reactionFine->getRandomQuip();

	if (randomQuip != -1) {
		StringIdChatParameter param(getReactionQuip(randomQuip));
		param.setTT(emoteUser->getObjectID());
		chatManager->broadcastChatMessage(emoteTarget, param, 0, 0, emoteTarget->getMoodID());
	}

	if (reactionFine->getFactionFine() != 0)
		ghost->decreaseFactionStanding("imperial", reactionFine->getFactionFine());

	if (reactionFine->shouldKnockdown()) {
		doKnockdown(emoteUser, emoteTarget);
	}

	if (reactionFine->getCreditFine() != 0) {
		StringBuffer suiFineMsg;
		suiFineMsg << "@stormtrooper_attitude/st_response:imperial_fine_" << String::valueOf(reactionFine->getCreditFine());
		if (ghost->getReactionFines() != 0) {
			suiFineMsg << " @stormtrooper_attitude/st_response:imperial_fine_outstanding " << String::valueOf(ghost->getReactionFines() + reactionFine->getCreditFine()) << " @stormtrooper_attitude/st_response:imperial_fine_credits";
		} else {
			ghost->updateReactionFineTimestamp();
		}
		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(emoteUser, SuiWindowType::REACTION_FINE);
		box->setPromptTitle("@stormtrooper_attitude/st_response:imperial_fine_t"); // Imperial Fine
		box->setPromptText(suiFineMsg.toString());
		box->setCallback(new ReactionFinePaymentSuiCallback(zoneServer));
		box->setUsingObject(emoteTarget);
		box->setForceCloseDistance(16.f);

		ghost->addSuiBox(box);
		emoteUser->sendMessage(box->generateMessage());

		ghost->addToReactionFines(reactionFine->getCreditFine());

	}
}

EmoteReactionFine* ReactionManagerImplementation::getEmoteReactionFine(CreatureObject* emoteUser, AiAgent* emoteTarget, int level) {
	if (emoteUser == nullptr)
		return nullptr;

	int rankCompare = 0;

	if (emoteUser->isImperial()) {
		int userFactionRank = emoteUser->getFactionRank();
		int targetReactionRank = emoteTarget->getReactionRank();

		if (targetReactionRank == 0) {
			Reference<ReactionRankData*> rankData = getReactionRankData(emoteTarget->getCreatureTemplate()->getTemplateName());

			if (rankData == nullptr)
				return nullptr;

			targetReactionRank = rankData->getRandomRank();

			// No reaction if the target has no reaction rank
			if (targetReactionRank == 0)
				return nullptr;

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

	return nullptr;
}

ReactionRankData* ReactionManagerImplementation::getReactionRankData(const String& name) {
	for (int i = 0; i < reactionRankData.size(); i++) {
		Reference<ReactionRankData*> data = reactionRankData.get(i);

		if (data->getTemplateName() == name)
			return data;
	}

	return nullptr;
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

	if (weapon != nullptr && weapon->isRangedWeapon())
		knockdownAnim = "ranged_melee_light";
	else
		knockdownAnim = "attack_high_center_light_0";


	victim->inflictDamage(attacker, CreatureAttribute::MIND, victim->getHAM(CreatureAttribute::MIND) + 200, true, true, true);


	victim->updatePostures(); // set posture, don't send posture message, but send DeltaCreo3

	attacker->doCombatAnimation(victim, knockdownAnim.hashCode(), HIT, 0xFF); // play attacker animation - This will update the victim's posture on the client
}

void ReactionManagerImplementation::doReactionFineMailCheck(CreatureObject* player) {
	if (player == nullptr)
		return;

	PlayerObject* playerObject = player->getPlayerObject();

	if (playerObject == nullptr)
		return;

	ChatManager* chatManager = zoneServer->getChatManager();

	if (chatManager == nullptr)
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
