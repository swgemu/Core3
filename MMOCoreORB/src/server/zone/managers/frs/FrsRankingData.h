#ifndef FRSRANKINGDATA_H_
#define FRSRANKINGDATA_H_

namespace server {
namespace zone {
namespace managers {
namespace frs {

class FrsRankingData : public Object {

protected:
	int rank, requiredXp, playerCap;
	String skillName, robeTemplate;

public:
	FrsRankingData(int frsRank, String skill, int reqExp, int cap, String robeTemp) : Object() {
		rank = frsRank;
		skillName = skill;
		requiredXp = reqExp;
		playerCap = cap;
		robeTemplate = robeTemp;
	}

	~FrsRankingData() {
	}

	int getRequiredExperience() const {
		return requiredXp;
	}

	int getPlayerCap() const {
		return playerCap;
	}

	int getRank() const {
		return rank;
	}

	const String& getSkillName() const {
		return skillName;
	}

	const String& getRobeTemplate() const {
		return robeTemplate;
	}

};

}
}
}
}

#endif /* FRSRANKINGDATA_H_ */
