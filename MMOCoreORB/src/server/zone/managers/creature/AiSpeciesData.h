
#ifndef AISPECIESDATA_H_
#define AISPECIESDATA_H_

namespace server {
namespace zone {
namespace managers {
namespace creature {

class AiSpeciesData : public Object {

protected:
	int speciesID;
	String skeleton;
	bool canSit;
	bool canLie;

public:
	AiSpeciesData(int species, String skel, bool sit, bool liedown) : Object() {
		speciesID = species;
		skeleton = skel;
		canSit = sit;
		canLie = liedown;
	}

	~AiSpeciesData() {
	}

	int getSpeciesID() {
		return speciesID;
	}

	String getSkeleton() {
		return skeleton;
	}

	bool canSitDown() {
		return canSit;
	}

	bool canLieDown() {
		return canLie;
	}
};

}
}
}
}

#endif /* AISPECIESDATA_H_ */
