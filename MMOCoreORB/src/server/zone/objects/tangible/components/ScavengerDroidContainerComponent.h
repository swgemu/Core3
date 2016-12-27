#ifndef SCAVENGERDROIDCONTAINERCOMPONENT_H_
#define SCAVENGERDROIDCONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

class ScavengerDroidContainerComponent : public ContainerComponent {
public:
	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const;
	bool transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient = false, bool allowOverflow = false, bool notifyRoot = true) const;
};

#endif /* SCAVENGERDROIDCONTAINERCOMPONENT_H_ */
