#ifndef RESOURCEDEEDIMPLEMENTATION_H_
#define RESOURCEDEEDIMPLEMENTATION_H_

#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

class DeedObject;
class TangibleObject;
class MountCreature;
class Player;
class CreatureObject;

class ResourceDeedImplementation : public ResourceDeedServant {
protected:
	string resourceFile;

public:

public:

	ResourceDeedImplementation(CreatureObject* creature, uint32 tempcrc, const unicode& n, const string& tempn);
	ResourceDeedImplementation(uint64 objid, uint32 tempcrc, const unicode& n, const string& tempn);
	~ResourceDeedImplementation();

	void init();

	int useObject(Player* player);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void destroyDeed(Player* player);

private:

};

#endif /*RESOURCEDEEDIMPLEMENTATION_H_*/

