/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef REQUESTCHARACTERMATCHCOMMAND_H_
#define REQUESTCHARACTERMATCHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/PlayersNearYou.h"
#include "server/zone/Zone.h"

class RequestCharacterMatchCommand : public QueueCommand {
public:

	RequestCharacterMatchCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		String profession, wildcard;
		UnicodeTokenizer tokenizer(arguments);

		int unk1 = tokenizer.getIntToken();
		int playerFlags = tokenizer.getIntToken();
		int unk2 = tokenizer.getIntToken();
		int unk3 = tokenizer.getIntToken();
		int unk4 = tokenizer.getIntToken();
		int faction = tokenizer.getIntToken();
		int species = tokenizer.getIntToken();
		tokenizer.getStringToken(profession);
		tokenizer.getStringToken(wildcard);

		ManagedReference<Zone*> zone = creature->getZone();

		if (zone != nullptr) {
			SortedVector<QuadTreeEntry*> closeObjects;
			CloseObjectsVector* actualCloseObjects = (CloseObjectsVector*) creature->getCloseObjects();

			if (actualCloseObjects != nullptr) {
				actualCloseObjects->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);
			} else {
				zone->getInRangeObjects(creature->getWorldPositionX(), creature->getWorldPositionY(), ZoneServer::CLOSEOBJECTRANGE, &closeObjects, true);
			}

			PlayersNearYouMessage* pny = new PlayersNearYouMessage(creature);
			uint32 counter = 0;

			if (!closeObjects.isEmpty()) {
				for (int i = 0; i < closeObjects.size(); ++i) {
					SceneObject* obj = cast<SceneObject*>(closeObjects.get(i));

					if (obj != nullptr && (obj->isPlayerCreature() || (obj->isMount() || obj->isVehicleObject()))) {
						ManagedReference<CreatureObject*> playerCreature = nullptr;

						if (obj->isMount() || obj->isVehicleObject()) {
							SceneObject* rider = obj->getSlottedObject("rider");

							if (rider == nullptr)
								continue;

							playerCreature = rider->asCreatureObject();
						} else {
							playerCreature = obj->asCreatureObject();
						}

						if (playerCreature == nullptr)
							continue;

						PlayerObject* targetGhost = playerCreature->getPlayerObject();

						if (targetGhost == nullptr || targetGhost->hasGodMode() || (targetGhost->isAnonymous() && playerCreature != creature))
							continue;

						String guildName = "";
						String charName = "";

						if (playerCreature->isInGuild()) {
							ManagedReference<GuildObject*> guild = playerCreature->getGuildObject().get();
							guildName = guild->getGuildName().toLowerCase();
						}

						charName = playerCreature->getDisplayedName().toLowerCase();

						// The client is always including the creature using the command in its count
						if (playerCreature != creature) {
							if (wildcard != "\"\"" && !guildName.contains(wildcard) && !charName.contains(wildcard))
								continue;

							if ((playerFlags & PlayerBitmasks::ROLEPLAYER) && !targetGhost->isRoleplayer()) // Command looking for roleplayer flag
								continue;

							if ((playerFlags & PlayerBitmasks::NEWBIEHELPER) && !targetGhost->isNewbieHelper()) // Command looking for helper flag
								continue;

							if ((playerFlags & PlayerBitmasks::LFG) && !targetGhost->isLFG()) // Command looking for lfg flag
								continue;

							// Search window sends a 0 for both "Any" and "Neutral", no way to differentiate
							if (faction != 0 && faction != 1 && playerCreature->getFaction() != faction) // Command looking for faction, /who sends a 1 but search window sends 0
								continue;

							if (species != -1 && playerCreature->getSpecies() != species) // Command looking for species
								continue;

							// Handles both title and profession search (arguments give no way to differentiate between profession and title search)
							// _novice check handles if player is searching for profession but no title
							if (profession != "\"\"" && !playerCreature->hasSkill(profession) && targetGhost->getTitle() != profession && !playerCreature->hasSkill(profession + "_novice") )
								continue;
						}

						pny->addFoundPlayer(playerCreature);
						counter++;

						if (counter == 32) // Limit of 32 results
							break;
					}
				}
			}

			if (counter > 0) {
				pny->insertPlayerCounter(counter);
			}

			creature->sendMessage(pny);

			return SUCCESS;
		} else {
			return GENERALERROR;
		}

		return SUCCESS;
	}

};

#endif //REQUESTCHARACTERMATCHCOMMAND_H_
