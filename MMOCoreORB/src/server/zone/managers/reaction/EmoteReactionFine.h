
#ifndef EMOTEREACTIONFINE_H_
#define EMOTEREACTIONFINE_H_

namespace server {
namespace zone {
namespace managers {
namespace reaction {

class EmoteReactionFine : public Object {

protected:
	int reactionLevel, rankComparison, creditFine, factionFine, minQuip, maxQuip;
	bool isImp, isHumanSpecies, doKnockdown;
	String emoteResponse;

public:
	EmoteReactionFine(int level, bool imperial, bool human, int rankCompare, int creditamount, int factionamount, bool knockdown, int minquip, int maxquip, String emoterespond) : Object() {
		reactionLevel = level;
		isImp = imperial;
		isHumanSpecies = human;
		rankComparison = rankCompare;
		creditFine = creditamount;
		factionFine = factionamount;
		doKnockdown = knockdown;
		minQuip = minquip;
		maxQuip = maxquip;
		emoteResponse = emoterespond;
	}

	~EmoteReactionFine() {

	}

	String getEmoteResponse() {
		return emoteResponse;
	}

	bool isImperial() {
		return isImp;
	}

	bool isHuman() {
		return isHumanSpecies;
	}

	bool shouldKnockdown() {
		return doKnockdown;
	}

	int getRankComparison() {
		return rankComparison;
	}

	int getReactionLevel() {
		return reactionLevel;
	}

	int getCreditFine() {
		return creditFine;
	}

	int getFactionFine() {
		return factionFine;
	}

	int getRandomQuip() {
		if (maxQuip == -1 || minQuip == -1)
			return -1;

		return minQuip + System::random(maxQuip - minQuip);
	}

};

}
}
}
}

#endif /* EMOTEREACTIONFINE_H_ */
