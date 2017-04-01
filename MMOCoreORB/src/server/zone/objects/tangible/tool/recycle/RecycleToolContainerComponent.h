
#ifndef RECYCLETOOLCONTAINERCOMPONENT_H_
#define RECYCLETOOLCONTAINERCOMPONENT_H_

#include "RecycleResourceTask.h"
#include "server/zone/objects/scene/components/ContainerComponent.h"

class RecycleToolContainerComponent : public ContainerComponent {
public:
	int notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) const {
		RecycleTool* recycler = cast <RecycleTool* >(sceneObject);

		TangibleObject* tano = cast <TangibleObject* >(object);

		if (recycler != NULL && tano != NULL) {
			RecycleResourceTask* task = new RecycleResourceTask(recycler, tano);

			if (task != NULL) {
				task->run();
			}
		}

		return ContainerComponent::notifyObjectInserted(sceneObject, object);
	}

	bool removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient) const {

		return ContainerComponent::removeObject(sceneObject, object, destination, notifyClient);
	}

	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const {
		ManagedReference<SceneObject*> parent = sceneObject->getParentRecursively(SceneObjectType::PLAYERCREATURE);

		if (parent == NULL)
			return TransferErrorCode::MUSTBEINPLAYERINVENTORY;

		if (parent != object->getParentRecursively(SceneObjectType::PLAYERCREATURE))
			return TransferErrorCode::MUSTBEINPLAYERINVENTORY;

		int containerObjects = parent->getSlottedObject("inventory")->getContainerObjectsSize();

		if (containerObjects >= parent->getSlottedObject("inventory")->getContainerVolumeLimit()) {
			errorDescription = "@error_message:inv_full"; // Your inventory is full.

			return TransferErrorCode::CONTAINERFULL;
		}

		return ContainerComponent::canAddObject(sceneObject, object, containmentType, errorDescription);
	}
};

#endif /* RECYCLETOOLCONTAINERCOMPONENT_H_ */
