/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLAIMVETERANREWARDCOMMAND_H_
#define CLAIMVETERANREWARDCOMMAND_H_

class ClaimVeteranRewardCommand : public QueueCommand {
public:

	ClaimVeteranRewardCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if( !creature->isPlayerCreature() )
			return GENERALERROR;

		PlayerManager* playerManager = creature->getZoneServer()->getPlayerManager();
		if( playerManager == NULL )
			return GENERALERROR;

		playerManager->claimVeteranRewards( creature );

		return SUCCESS;
	}

};

#endif //CLAIMVETERANREWARDCOMMAND_H_
