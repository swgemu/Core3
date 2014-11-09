/*
 * DataStorageUnitDataComponent.h
 *
 *  Created on: 11/8/2014
 *      Author: Klivian
 */

#ifndef DATASTORAGEUNITDATACOMPONENT_H_
#define DATASTORAGEUNITDATACOMPONENT_H_

#include "server/zone/objects/scene/components/DataObjectComponent.h"

class DataStorageUnitDataComponent : public DataObjectComponent {
protected:
	byte id;
public:
	DataStorageUnitDataComponent() {

		// There are 12 text options (1-12).  Pick one at random
		id = System::random(11) + 1;
		addSerializableVariables();
	}

	virtual ~DataStorageUnitDataComponent() {

	}

	byte getId() {
		return id;
	}

	bool isDataStorageUnitData() {
		return true;
	}

private:
	void addSerializableVariables() {
		addSerializableVariable("id", &id);
	}
};


#endif /* DATASTORAGEUNITDATACOMPONENT_H_ */
