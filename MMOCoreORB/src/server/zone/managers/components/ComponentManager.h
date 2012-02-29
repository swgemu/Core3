/*
 * ComponentManager.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/components/SceneObjectComponent.h"
#include "server/zone/objects/scene/components/LuaObjectMenuComponent.h"
#include "server/zone/objects/scene/components/LuaContainerComponent.h"

class ComponentManager : public Singleton<ComponentManager>, public Object, public ReadWriteLock {
protected:
	HashTable<String, Reference<SceneObjectComponent*> > components;

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
