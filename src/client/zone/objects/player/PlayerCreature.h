#ifndef PLAYERCREATURE_H_
#define PLAYERCREATURE_H_

#include "../creature/CreatureObject.h"

class Zone;

class PlayerCreature : public CreatureObject {
protected:
	Zone* zone;

public:
	PlayerCreature(LuaObject* templateData);

	void insertToZone(Zone* zone);

	void activatePositionUpdate();

};

#endif /* PLAYER_H_ */
