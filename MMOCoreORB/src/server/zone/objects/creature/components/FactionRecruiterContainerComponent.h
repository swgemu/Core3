
#ifndef FACTIONRECRUITERCONTAINERCOMPONENT_H_
#define FACTIONRECRUITERCONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

class FactionRecruiterContainerComponent: public ContainerComponent {
public:

	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const;

	bool transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient = false, bool allowOverflow = false, bool notifyRoot = true) const;

};

#endif /* FACTIONRECRUITERCONTAINERCOMPONENT_H_ */
