
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

	int getSpeciesID() const {
		return speciesID;
	}

	const String& getSkeleton() const {
		return skeleton;
	}

	bool canSitDown() const {
		return canSit;
	}

	bool canLieDown() const {
		return canLie;
	}
};

}
}
}
}

#endif /* AISPECIESDATA_H_ */
