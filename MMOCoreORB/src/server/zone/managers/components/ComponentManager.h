/*
 * ComponentManager.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include <stddef.h>

#include "engine/util/ObjectFactory.h"
#include "engine/util/Singleton.h"
#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/objects/scene/components/SceneObjectComponent.h"
#include "system/lang/Object.h"
#include "system/lang/String.h"
#include "system/lang/ref/Reference.h"
#include "system/thread/Locker.h"
#include "system/thread/ReadWriteLock.h"
#include "system/util/HashTable.h"

class DataObjectComponent;
class SceneObjectComponent;

class ComponentManager : public Singleton<ComponentManager>, public Object, public ReadWriteLock {
protected:
	HashTable<String, Reference<SceneObjectComponent*> > components;
	ObjectFactory<DataObjectComponent* (), String> dataObjectFactory;

public:
	ComponentManager();

	template<class K>
	K getComponent(const String& name) {
		K comp;

		rlock();

		try {
			comp = dynamic_cast<K>(components.get(name).get());
		} catch (...) {
			runlock();
			throw;
		}

		runlock();

		return comp;
	}

	DataObjectComponent* getDataObjectComponent(const String& name) {
		return dataObjectFactory.createObject(name);
	}

	void putComponent(const String& name, SceneObjectComponent* component) {
		Locker locker(this);

		if (component != NULL)
			components.put(name, component);
	}

	int size() {
		return components.size();
	}
};


#endif /* COMPONENTMANAGER_H_ */
