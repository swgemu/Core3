
#ifndef GARAGEDATACOMPONENT_H_
#define GARAGEDATACOMPONENT_H_

#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/objects/area/ActiveArea.h"

class GarageDataComponent : public DataObjectComponent {
protected:
	ManagedReference<ActiveArea*> garageArea;

public:
	GarageDataComponent() {
		garageArea = NULL;
	}

	virtual ~GarageDataComponent() {
	}

	void notifyObjectdestroyingFromDatabase();
	void createGarageArea();
	ManagedReference<ActiveArea*> getGarageArea();
};

#endif /* GARAGEDATACOMPONENT_H_ */
