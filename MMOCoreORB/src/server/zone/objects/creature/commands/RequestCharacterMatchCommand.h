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

	RequestCharacterMatchCommand(const String& name, ZoneProcessServer* server)
: QueueCommand(name, server) {

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

		if (zone != NULL) {
			SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
			CloseObjectsVector* actualCloseObjects = (CloseObjectsVector*) creature->getCloseObjects();

			if (actualCloseObjects != NULL) {
				actualCloseObjects->safeCopyTo(closeObjects);
			} else {
				zone->getInRangeObjects(creature->getWorldPositionX(), creature->getWorldPositionY(), ZoneServer::CLOSEOBJECTRANGE, &closeObjects, true);
			}

			PlayersNearYouMessage* pny = new PlayersNearYouMessage(creature);
			uint32 counter = 0;

			if (!closeObjects.isEmpty()) {
				String guildName, charName;
				for (int i = 0; i < closeObjects.size(); ++i) {
					SceneObject* obj = cast<SceneObject*>(closeObjects.get(i).get());
					if (obj != NULL && (obj->isPlayerCreature() || (obj->isMount() || obj->isVehicleObject()))) {
						ManagedReference<CreatureObject*> playerCreature;
						if (obj->isMount() || obj->isVehicleObject()) {
							SceneObject* rider = obj->getSlottedObject("rider");
							if (rider == NULL)
								continue;

							playerCreature = cast<CreatureObject*>(rider);
						} else
							playerCreature = cast<CreatureObject*>(obj);

						PlayerObject* ghost = playerCreature->getPlayerObject();

						if (ghost == NULL || ghost->isAnonymous())
							continue;

						guildName = "";
						if (playerCreature->isInGuild())
							guildName = playerCreature->getGuildObject()->getGuildName().toLowerCase();

						charName = playerCreature->getDisplayedName().toLowerCase();

						if (wildcard != "\"\"" && !guildName.contains(wildcard) && !charName.contains(wildcard))
							continue;

						// Don't allow non privileged characters to search for admin skills
						if (profession.contains("admin") && !ghost->isPrivileged())
							continue;

						// Dont show invisible admins
						if (playerCreature->isInvisible())
							continue;

						if ((playerFlags & 0x04) && !ghost->isRoleplayer()) // Command looking for roleplayer flag
							continue;

						if ((playerFlags & 0x02) && !ghost->isNewbieHelper()) // Command looking for helper flag
							continue;

						if ((playerFlags & 0x01) && !ghost->isLFG()) // Command looking for lfg flag
							continue;

						// Search window sends a 0 for both "Any" and "Neutral", no way to differentiate
						if (faction != 0 && faction != 1 && playerCreature->getFaction() != faction) // Command looking for faction, /who sends a 1 but search window sends 0
							continue;

						if (species != -1 && playerCreature->getSpecies() != species) // Command looking for species
							continue;

						// Handles both title and profession search (arguments give no way to differentiate between profession and title search)
						// _novice check handles if player is searching for profession but no title
						if (profession != "\"\"" && !playerCreature->hasSkill(profession) && ghost->getTitle() != profession && !playerCreature->hasSkill(profession + "_novice") )
							continue;

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
