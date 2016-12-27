/*
 * ShuttleInstallationZoneComponent.h
 *
 *  Created on: Apr 7, 2012
 *      Author: TragD
 */

#ifndef SHUTTLEINSTALLATIONZONECOMPONENT_H_
#define SHUTTLEINSTALLATIONZONECOMPONENT_H_

#include "engine/engine.h"

#include "server/zone/objects/structure/components/StructureZoneComponent.h"

namespace server {
	namespace zone {
		namespace objects {
			namespace scene {
				class SceneObject;
			}
		}
		class Zone;
	}
}

using namespace server::zone::objects::scene;
using namespace server::zone;

class ShuttleInstallationZoneComponent : public StructureZoneComponent {

public:
	void notifyInsertToZone(SceneObject* sceneObject, Zone* zone) const;
	void notifyRemoveFromZone(SceneObject* sceneObject) const;
	void destroyObjectFromWorld(SceneObject* sceneObject, bool sendSelfDestroy) const;
};

#endif /* SHUTTLEINSTALLATIONZONECOMPONENT_H_ */
