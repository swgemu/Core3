#ifndef FRSRANKINGDATA_H_
#define FRSRANKINGDATA_H_

namespace server {
namespace zone {
namespace managers {
namespace frs {

class FrsRankingData : public Object {

protected:
	int rank, requiredXp, playerCap;
	String skillName;

public:
	FrsRankingData(int frsRank, String skill, int reqExp, int cap) : Object() {
		rank = frsRank;
		skillName = skill;
		requiredXp = reqExp;
		playerCap = cap;
	}

	~FrsRankingData() {
	}

	int getRequiredExperience() {
		return requiredXp;
	}

	int getPlayerCap() {
		return playerCap;
	}

	int getRank() {
		return rank;
	}

	const String& getSkillName() {
		return skillName;
	}

};

}
}
}
}

#endif /* FRSRANKINGDATA_H_ */
