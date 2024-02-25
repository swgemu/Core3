#ifndef PERSONNELPERKZONECOMPONENT_H_
#define PERSONNELPERKZONECOMPONENT_H_

#include "server/zone/objects/scene/components/GroundZoneComponent.h"

class PersonnelPerkZoneComponent : public GroundZoneComponent {

public:
	void notifyInsertToZone(SceneObject* sceneObject, Zone* zne) const;
};


#endif /* PERSONNELPERKZONECOMPONENT_H_ */
