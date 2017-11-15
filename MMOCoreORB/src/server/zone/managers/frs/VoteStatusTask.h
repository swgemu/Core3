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

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		strongRef->updateLastVoteStatus();

		// Iterates lightside/darkside
		for (int j = 1; j <= 2; j++) {
			//Iterates each rank in rank type
			for (int i = 1; i <= 11; i++) {
				FrsRank* rank = strongRef->getFrsRank(j, i);

				if (rank == NULL)
					continue;

				short voteStatus = rank->getVoteStatus();
				uint64 tickDiff = rank->getLastUpdateTickDiff();
				uint64 interval = strongRef->getVotingInterval(voteStatus);

				if (tickDiff + 30000 < interval)
					continue;

				Core::getTaskManager()->scheduleTask([strongRef, rank]{
					Locker locker(strongRef);
					strongRef->runVotingUpdate(rank);
				}, "frsVotingTask", i * j * 10);
			}
		}

		locker.release();

		reschedule(FrsManager::VOTE_STATUS_TICK);
	}
};

}
}
}
}

#endif /* VOTESTATUSTASK_H_ */
