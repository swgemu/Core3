
#ifndef REACTIONRANKDATA_H_
#define REACTIONRANKDATA_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace managers {
namespace reaction {

class ReactionRankData : public Object {

protected:
	int minRank, maxRank;
	String templateName;

public:
	ReactionRankData(String name, int min, int max) : Object() {
		templateName = name;
		minRank = min;
		maxRank = max;
	}

	~ReactionRankData() {
	}

	String getTemplateName() {
		return templateName;
	}

	int getRandomRank() {
		return minRank + System::random(maxRank - minRank);
	}

};

}
}
}
}

#endif /* REACTIONRANKDATA_H_ */
