#ifndef ENCLAVEVOTINGTERMINALSUICALLBACK_H_
#define ENCLAVEVOTINGTERMINALSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/frs/FrsManager.h"

class EnclaveVotingTerminalSuiCallback : public SuiCallback {
private:
	short suiType, enclaveType;
	int rank;
	bool selectingRank;
public:
	EnclaveVotingTerminalSuiCallback(ZoneServer* server, short type, short enclave, int rnk, bool selectRank)
		: SuiCallback(server) {
		enclaveType = enclave;
		suiType = type;
		rank = rnk;
		selectingRank = selectRank;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed || player == NULL)
			return;

		ManagedReference<SceneObject*> terminal = suiBox->getUsingObject().get();

		if (terminal == NULL)
			return;

		ManagedReference<SceneObject*> parent = terminal->getParentRecursively(SceneObjectType::BUILDING);

		if (parent == NULL)
			return;

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(parent.get());

		if (building == NULL)
			return;

		FrsManager* frsMan = player->getZoneServer()->getFrsManager();

		if (frsMan == NULL)
			return;

		int enclaveType = frsMan->getEnclaveType(building);

		if (enclaveType == 0)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index < 0)
			return;

		Locker locker(player);

		if (selectingRank) {
			int selectedRank = index + 1;

			if (suiType == FrsManager::SUI_VOTE_RECORD) {
				frsMan->sendVoteRecordSui(player, terminal, enclaveType, selectedRank);
			} else if (suiType == FrsManager::SUI_VOTE_DEMOTE) {
				frsMan->sendVoteDemoteSui(player, terminal, enclaveType, selectedRank);
			} else if (suiType == FrsManager::SUI_VOTE_ACCEPT_PROMOTE) {
				frsMan->handleAcceptPromotionSui(player, terminal, enclaveType, selectedRank);
			} else if (suiType == FrsManager::SUI_VOTE_PETITION) {
				frsMan->handleVotePetitionSui(player, terminal, enclaveType, selectedRank);
			} else if (suiType == FrsManager::SUI_VOTE_STATUS) {
				frsMan->handleVoteStatusSui(player, terminal, enclaveType, selectedRank);
			} else if (suiType == FrsManager::SUI_FORCE_PHASE_CHANGE) {
				PlayerObject* ghost = player->getPlayerObject();

				if (ghost == nullptr || !ghost->isPrivileged())
					return;

				locker.release();

				frsMan->forcePhaseChange(player, enclaveType, selectedRank);
			}
		} else {
			uint64 playerID = 0;

			SuiListBox* listBox = cast<SuiListBox*>( suiBox);

			if (listBox != nullptr)
				playerID = listBox->getMenuObjectID(index);

			if (suiType == FrsManager::SUI_VOTE_RECORD) {
				frsMan->handleVoteRecordSui(player, terminal, enclaveType, rank, playerID);
			} if (suiType == FrsManager::SUI_VOTE_DEMOTE) {
				frsMan->handleVoteDemoteSui(player, terminal, enclaveType, rank, playerID);
			} else if (suiType == FrsManager::SUI_CHAL_VOTE_STATUS) {
				frsMan->handleChallengeVoteStatusSui(player, terminal, playerID);
			} else if (suiType == FrsManager::SUI_CHAL_VOTE_RECORD) {
				frsMan->handleChallengeVoteRecordSui(player, terminal, playerID);
			} else if (suiType == FrsManager::SUI_CHAL_VOTE_RECORD_CONFIRM) {
				frsMan->handleChallengeVoteRecordConfirmSui(player, terminal, index, playerID);
			} else if (suiType == FrsManager::SUI_CHAL_VOTE_ISSUE) {
				frsMan->handleChallengeVoteIssueSui(player, terminal, playerID);
			} else if (suiType == FrsManager::SUI_ARENA_CHAL_VIEW) {
				frsMan->handleArenaChallengeViewSui(player, terminal, suiBox, index);
			} else if (suiType == FrsManager::SUI_ARENA_CHAL_ISSUE) {
				frsMan->handleArenaChallengeIssueSui(player);
			} else if (suiType == FrsManager::SUI_ARENA_CHAL_ACCEPT) {
				frsMan->sendArenaChallengeSUI(player, terminal, FrsManager::SUI_ARENA_CHAL_ACCEPT_LIST, enclaveType);
			} else if (suiType == FrsManager::SUI_ARENA_CHAL_ACCEPT_LIST) {
				locker.release();
				frsMan->acceptArenaChallenge(player, playerID);
			}
		}
	}
};

#endif /* ENCLAVEVOTINGTERMINALSUICALLBACK_H_ */
