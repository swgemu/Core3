/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef CREATEFACTORYOBJECTTASK_H_
#define CREATEFACTORYOBJECTTASK_H_

#include "server/zone/objects/installation/factory/FactoryObject.h"

class CreateFactoryObjectTask : public Task {

	ManagedReference<FactoryObject* > factoryObject;

public:
	CreateFactoryObjectTask(FactoryObject* factory) : Task() {
		factoryObject = factory;
	}

	void run() {

		Locker _locker(factoryObject);

		factoryObject->createNewObject();
	}
};

#endif /*CREATEFACTORYOBJECTTASK_H_*/
