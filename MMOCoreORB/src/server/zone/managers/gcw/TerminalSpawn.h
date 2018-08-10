#ifndef TERMINALSPAWN_H_
#define TERMINALSPAWN_H_

namespace server {
namespace zone {
namespace managers {
namespace gcw {

class TerminalSpawn : public Object {

protected:
	Vector3 spawnLoc;
	int cellID;
	String templateName;
	Quaternion rotation;

public:
	TerminalSpawn(String name, Vector3 loc, int cell, Quaternion rot) : Object() {
		templateName = name;
		cellID = cell;
		spawnLoc = loc;
		rotation = rot;
	}

	~TerminalSpawn() {
	}

	String getTemplateName() {
		return templateName;
	}

	int getCellID() {
		return cellID;
	}

	inline Vector3* getSpawnLoc() {
		return &spawnLoc;
	}

	Quaternion getRotation() const {
		return rotation;
	}

};

}
}
}
}

#endif /* TERMINALSPAWN_H_ */
