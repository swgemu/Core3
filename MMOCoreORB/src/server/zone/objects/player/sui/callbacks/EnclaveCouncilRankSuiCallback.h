#ifndef ENCLAVECOUNCILRANKSUICALLBACK_H_
#define ENCLAVECOUNCILRANKSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/frs/FrsManager.h"

class EnclaveCouncilRankSuiCallback : public SuiCallback {
private:
	int councilType;
public:
	EnclaveCouncilRankSuiCallback(ZoneServer* server, int type)
		: SuiCallback(server) {
		councilType = type;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed || player == nullptr)
			return;

		FrsManager* frsMan = player->getZoneServer()->getFrsManager();

		if (frsMan == NULL)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index < 0)
			return;

		frsMan->sendRankPlayerList(player, councilType, index + 1);

	}
};

#endif /* ENCLAVECOUNCILRANKSUICALLBACK_H_ */
