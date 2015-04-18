/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.caught in void SceneObjectImplementation::createChildObjects()!");
				e.printStackTrace();
			}
		} else {
			//Create the object outdoors in relation to its parent.
			Vector3 position = getPosition();

			float angle = direction.getRadians();

			float x = (Math::cos(angle) * childPosition.getX()) + (childPosition.getY() * Math::sin(angle));
			float y = (Math::cos(angle) * childPosition.getY()) - (childPosition.getX() * Math::sin(angle));

			x += position.getX();
			y += position.getY();

			float z = position.getZ() + childPosition.getZ();

			float degrees = direction.getDegrees();

			Quaternion dir = child->getDirection();

			obj->initializePosition(x, z, y);
			obj->setDirection(dir.rotate(Vector3(0, 1, 0), degrees));

			if (!getZone()->transferObject(obj, -1, false)) {
				obj->destroyObjectFromDatabase(true);
				continue;
			}
		}

		//childObjects.put(obj);
		ContainerPermissions* permissions = obj->getContainerPermissions();
		permissions->setOwner(getObjectID());
		permissions->setInheritPermissionsFromParent(false);
		permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
		permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);

		obj->initializeChildObject(_this.get());
	}
}

bool SceneObjectImplementation::isFacingObject(SceneObject* obj) {
	Vector3 thisPos = getPosition();
	Vector3 targetPos = obj->getPosition();

	float directionangle = atan2(targetPos.getX() - thisPos.getX(), targetPos.getY() - thisPos.getY());

	if (directionangle < 0) {
		float a = M_PI + directionangle;
		directionangle = M_PI + a;
	}

	return fabs(directionangle - direction.getRadians()) < (M_PI / 2);
}

void SceneObjectImplementation::faceObject(SceneObject* obj) {
	Vector3 thisPos = getPosition();
	Vector3 targetPos = obj->getPosition();

	float directionangle = atan2(targetPos.getX() - thisPos.getX(), targetPos.getY() - thisPos.getY());

	if (directionangle < 0) {
		float a = M_PI + directionangle;
		directionangle = M_PI + a;
	}

	float err = fabs(directionangle - direction.getRadians());

	if (err < 0.05) {
		//info("not updating " + String::valueOf(directionangle), true);
		return;
	}

	direction.setHeadingDirection(directionangle);
}

void SceneObjectImplementation::getContainerObjects(VectorMap<uint64, ManagedReference<SceneObject*> >& objects) {
	containerObjects.loadObjects();

	ReadLocker locker(&containerLock);

	objects = *containerObjects.getContainerObjects();
}

void SceneObjectImplementation::getSlottedObjects(VectorMap<String, ManagedReference<SceneObject*> >& objects) {
	ReadLocker locker(&containerLock);

	objects = slottedObjects;
}

Reference<SceneObject*> SceneObjectImplementation::getSlottedObject(const String& slot) {
	ManagedReference<SceneObject*> obj = NULL;

	ReadLocker locker(&containerLock);

	obj = slottedObjects.get(slot);

	return obj;
}

Reference<SceneObject*> SceneObjectImplementation::getSlottedObject(int idx) {
	ManagedReference<SceneObject*> obj = NULL;

	ReadLocker locker(&containerLock);

	obj = slottedObjects.get(idx);

	return obj;
}

void SceneObjectImplementation::dropSlottedObject(const String& arrengementDescriptor) {
	Locker locker(&containerLock);

	slottedObjects.drop(arrengementDescriptor);
}

void SceneObjectImplementation::removeSlottedObject(int index) {
	Locker locker(&containerLock);

	slottedObjects.remove(index);
}

void SceneObjectImplementation::setZone(Zone* zone) {
	this->zone = zone;
}

void SceneObjectImplementation::showFlyText(const String& file, const String& aux, uint8 red, uint8 green, uint8 blue) {
	ShowFlyText* fly = new ShowFlyText(_this.get(), file, aux, red, green, blue);

	broadcastMessage(fly, true);
}

/*SortedVector<ManagedReference<SceneObject*> >* SceneObjectImplementation::getOutdoorChildObjects() {
	return &outdoorChildObjects;
}*/

void SceneObjectImplementation::initializeChildObject(SceneObject* controllerObject) {
}

void SceneObjectImplementation::setParent(QuadTreeEntry* entry) {
	Locker locker(&parentLock);

	QuadTreeEntryImplementation::setParent(entry);
}

ManagedWeakReference<SceneObject*> SceneObjectImplementation::getParent() {
	Locker locker(&parentLock);

	ManagedReference<QuadTreeEntry*> parent = this->parent.get();

	if (parent == NULL)
		return NULL;

	assert(parent != _this.get());

	return ManagedWeakReference<SceneObject*>(parent.castTo<SceneObject*>());
}

SortedVector<ManagedReference<Observer* > > SceneObjectImplementation::getObservers(unsigned int eventType) {
	return observerEventMap.getObservers(eventType);
}

bool SceneObjectImplementation::isInWater() {
	if (getZone() == NULL) {
		error("Zone is NULL SceneObjectImplementation::isInWater");
		return false;
	}

	ManagedReference<PlanetManager*> planetManager = getZone()->getPlanetManager();

	if (planetManager == NULL) {
		error("Unable to get PlanetManager SceneObjectImplementation::isInWater");
		return false;
	}

	return planetManager->isInWater(getPositionX(), getPositionY());
}

bool SceneObjectImplementation::containsNoTradeObjectRecursive() {

	Locker locker(&containerLock);

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		if (obj->isNoTrade()){
			return true;
		}

		if (obj->containsNoTradeObjectRecursive()) {
			return true;
		}

	}

	return false;

}
String SceneObjectImplementation::getDisplayedName() {
	if(!customName.isEmpty())
		return customName.toString();

	return StringIdManager::instance()->getStringId(objectName.getFullPath().hashCode()).toString();
}

bool SceneObjectImplementation::setTransformForCollisionMatrixIfNull(Matrix4* mat) {
	return transformForCollisionMatrix.compareAndSet(NULL, mat);
}

int SceneObjectImplementation::getCountableObjectsRecursive() {
	int count = 0;

	Locker locker(&containerLock);

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		if (obj != NULL) {
			++count;

			count += obj->getCountableObjectsRecursive();
		}
	}

	return count;
}

int SceneObjectImplementation::getContainedObjectsRecursive() {
	int count = 0;

	Locker locker(&containerLock);

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		++count;

		count += obj->getContainedObjectsRecursive();
	}

	return count;
}

int SceneObjectImplementation::getSizeOnVendorRecursive() {
	int count = 0;

	Locker locker(&containerLock);

	if (containerObjects.size() == 0)
		++count;

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		count += obj->getSizeOnVendorRecursive();
	}

	return count;
}

bool SceneObjectImplementation::isDecoration(){
	return (templateObject != NULL &&
			(templateObject->getFullTemplateString().contains("object/tangible/furniture/city") ||
					templateObject->getFullTemplateString().contains("object/building/player/city/garden")));
}

Reference<SceneObject*> SceneObjectImplementation::getContainerObjectRecursive(uint64 oid) {
	ManagedReference<SceneObject*> obj = containerObjects.get(oid);

	if (obj != NULL)
		return obj;

	for (int i = 0; i < containerObjects.size(); ++i) {
		Locker locker(&containerLock);

		ManagedReference<SceneObject*> inContainerObject = containerObjects.get(i);

		obj = inContainerObject->getContainerObjectRecursive(oid);

		if (obj != NULL)
			break;
	}

	return obj;
}

Vector<String> SceneObjectImplementation::getArrangementDescriptor(int idx) {
	return templateObject->getArrangementDescriptors().get(idx);
}

bool SceneObjectImplementation::hasObjectInSlottedContainer(SceneObject* object) {
	int arrangementSize = object->getArrangementDescriptorSize();

	if (arrangementSize == 0) {
		return false;
	}

	ManagedReference<SceneObject* > obj = NULL;

	Locker _locker((&containerLock));

	for (int i = 0; i < arrangementSize; ++i) {
		Vector<String> descriptors = object->getArrangementDescriptor(i);

		for (int j = 0; j < descriptors.size(); ++j) {
			if (slottedObjects.get(descriptors.get(j)) != NULL)
				return true;
		}
	}

	return false;
}

int SceneObjectImplementation::getArrangementDescriptorSize() {
	return templateObject->getArrangementDescriptors().size();
}

bool SceneObjectImplementation::isDataPad() {
	return templateObject->getFullTemplateString().contains("datapad");
}

float SceneObjectImplementation::getTemplateRadius() {
	if (templateObject == NULL || templateObject->getAppearanceTemplate() == NULL)
		return 0.f;

	MeshAppearanceTemplate* app = cast<MeshAppearanceTemplate*>(templateObject->getAppearanceTemplate());

	if (app == NULL || app->getBoundingSphere() == NULL)
		return 0.f;

	// we currently don't scale these, so we have no scale variable
	return app->getBoundingSphere()->getRadius();
}

void SceneObjectImplementation::playEffect(const String& file,
		const String& aux) {
	PlayClientEffectObjectMessage* effect = new PlayClientEffectObjectMessage(
			_this.get(), file, aux);

	broadcastMessage(effect, true);
}
