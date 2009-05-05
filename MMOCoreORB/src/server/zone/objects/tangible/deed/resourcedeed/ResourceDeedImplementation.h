#ifndef RESOURCEDEEDIMPLEMENTATION_H_
#define RESOURCEDEEDIMPLEMENTATION_H_

#include "ResourceDeed.h"

class ResourceDeedImplementation : public ResourceDeedServant {
protected:
	String resourceFile;

	void init();

public:
	ResourceDeedImplementation(CreatureObject* creature, uint32 objcrc, const UnicodeString& customname, const String& stfname);
	ResourceDeedImplementation(uint64 objid, uint32 objcrc, const UnicodeString& customname, const String& stfname);
	~ResourceDeedImplementation();

	int useObject(Player* player);

	SceneObject* generateObject(Player* player);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void destroyDeed(Player* player);

	//Setters

	//Getters
};

#endif /*RESOURCEDEEDIMPLEMENTATION_H_*/

