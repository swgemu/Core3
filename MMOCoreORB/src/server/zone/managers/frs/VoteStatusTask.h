#ifndef VOTESTATUSTASK_H_
#define VOTESTATUSTASK_H_

#include "server/zone/managers/frs/FrsManager.h"

namespace server {
namespace zone {
namespace managers {
namespace frs {

class VoteStatusTask: public Task {
	ManagedWeakReference<FrsManager*> frsManager;

public:
	VoteStatusTask(FrsManager* frs) {
		frsManager = frs;
	}

	void run() {
		ManagedReference<FrsManager*> strongRef = frsManager.get();

		if (strongRef == nullptr)
			return;

		Locker locker(strongRef);

		strongRef->updateLastVoteStatus();

		locker.release();

		// Iterates lightside/darkside
		for (int j = 1; j <= 2; j++) {
			//Iterates each rank in rank type
			for (int i = 1; i <= 11; i++) {
				ManagedReference<FrsRank*> rankData = strongRef->getFrsRank(j, i);

				if (rankData == nullptr)
					continue;

				Locker locker(rankData);

				short voteStatus = rankData->getVoteStatus();
				uint64 tickDiff = rankData->getLastUpdateTickDiff();
				uint64 interval = strongRef->getVotingInterval(voteStatus);

				if (tickDiff + 30000 < interval)
					continue;

				Core::getTaskManager()->scheduleTask([strongRef, rankData]{
					Locker locker(rankData);
					strongRef->runVotingUpdate(rankData);
				}, "frsVotingTask", i * j * 10);
			}
		}

		Core::getTaskManager()->scheduleTask([strongRef]{
			strongRef->runChallengeVoteUpdate();
			strongRef->performArenaMaintenance();
		}, "frsUpdateTask", 5000);

		reschedule(FrsManager::VOTE_STATUS_TICK);
	}
};

}
}
}
}

#endif /* VOTESTATUSTASK_H_ */
