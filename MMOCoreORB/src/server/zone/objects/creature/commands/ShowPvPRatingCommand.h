/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHOWPVPRATINGCOMMAND_H_
#define SHOWPVPRATINGCOMMAND_H_

class ShowPvPRatingCommand : public QueueCommand {
public:

	ShowPvPRatingCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		ManagedReference<CreatureObject*> targetObj = NULL;
		StringTokenizer args(arguments.toString());

		if (creature->getTargetID() != 0) {
			targetObj = server->getZoneServer()->getObject(creature->getTargetID()).castTo<CreatureObject*>();
		} else {
			if (args.hasMoreTokens()) {
				String targetName = "";
				args.getStringToken(targetName);
				targetObj = playerManager->getPlayer(targetName);
			}
		}

		if (targetObj != NULL) {
			PlayerObject* targetGhost = targetObj->getPlayerObject();

			if (targetGhost != NULL) {
				StringIdChatParameter ratingMsg;
				ratingMsg.setStringId("pvp_rating", "pvp_rating_target");
				ratingMsg.setTT(targetObj->getFirstName());
				ratingMsg.setDI(targetGhost->getPvpRating());

				creature->sendSystemMessage(ratingMsg);
				return SUCCESS;
			}
		}

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost != NULL) {
			StringIdChatParameter ratingMsg;
			ratingMsg.setStringId("pvp_rating", "pvp_rating");
			ratingMsg.setDI(ghost->getPvpRating());
			creature->sendSystemMessage(ratingMsg);
		}

		return SUCCESS;
	}

};

#endif //SHOWPVPRATINGCOMMAND_H_
