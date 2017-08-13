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

		if (cancelPressed || !suiBox->isMessageBox() || player == NULL)
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

		int index = Integer::valueOf(args->get(1).toString());

		if (index < 0)
			return;

		if (selectingRank) {
			frsMan->sendVoteSUI(player, terminal, suiType, enclaveType);
		} else {
			if (suiType == FrsManager::SUI_VOTE_RECORD)
				frsMan->handleVoteRecordSui(player, terminal, enclaveType, rank, index);
			else if (suiType == FrsManager::SUI_VOTE_ACCEPT_PROMOTE)
				frsMan->handleAcceptPromotionSui(player, terminal, enclaveType, rank);
			else if (suiType == FrsManager::SUI_VOTE_PETITION)
				frsMan->handleVotePetitionSui(player, terminal, enclaveType, rank);
		}
	}
};

#endif /* ENCLAVEVOTINGTERMINALSUICALLBACK_H_ */
