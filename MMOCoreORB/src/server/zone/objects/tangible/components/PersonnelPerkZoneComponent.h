#ifndef PERSONNELPERKZONECOMPONENT_H_
#define PERSONNELPERKZONECOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/components/SceneObjectComponent.h"
#include "engine/util/u3d/QuadTreeEntry.h"


class PersonnelPerkZoneComponent : public ZoneComponent {

public:
	void notifyInsertToZone(SceneObject* sceneObject, Zone* zne) const;
};


#endif /* PERSONNELPERKZONECOMPONENT_H_ */
