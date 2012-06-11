/*
 * DataObjectComponent.h
 *
 *  Created on: 18/03/2012
 *      Author: victor
 */

#ifndef DATAOBJECTCOMPONENT_H_
#define DATAOBJECTCOMPONENT_H_

#include "SceneObjectComponent.h"

class DataObjectComponent : public SceneObjectComponent, public Serializable {
public:

	virtual void initializeTransientMembers() {

	}

	virtual void notifyObjectDestroyingFromDatabase() {

	}

	virtual bool isDiceData() {
		return false;
	}

	virtual bool isVendorData() {
		return false;
	}

	virtual bool isCreatureHabitatData() {
		return false;
	}


};


#endif /* DATAOBJECTCOMPONENT_H_ */
