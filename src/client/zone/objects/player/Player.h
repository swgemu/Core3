#ifndef PLAYER_H_
#define PLAYER_H_

#include "../creature/CreatureObject.h"

class Zone;

class Player : public CreatureObject {
protected:
	Zone* zone;

	uint64 characterID;

public:
	Player();
	Player(uint64 oid);

	void insertToZone(Zone* zone);

	void activatePositionUpdate();

	inline uint64 getCharacterID() {
		return characterID;
	}

};

#endif /* PLAYER_H_ */
