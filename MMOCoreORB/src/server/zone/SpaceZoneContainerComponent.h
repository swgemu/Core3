/*
 * SpaceZoneContainerComponent.h
 *
 *  Created on: 03/09/2011
 *      Author: TheAnswer
 */

#ifndef SPACEZONECONTAINERCOMPONENT_H_
#define SPACEZONECONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "server/zone/SpaceZone.h"

namespace server {
	namespace zone {
		class SpaceZone;

		namespace objects {
			namespace area {
				class ActiveArea;
			}
		}
	}
}

using namespace server::zone;
using namespace server::zone::objects::area;

class SpaceZoneContainerComponent : public ContainerComponent, public Logger {
protected:
	bool insertActiveArea(Zone* zone, ActiveArea* activeArea) const;
	bool removeActiveArea(Zone* zone, ActiveArea* activeArea) const;
public:
	SpaceZoneContainerComponent() {
		setLoggingName("SpaceZoneContainerComponent");
	}

	virtual bool transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient = false, bool allowOverflow = false, bool notifyRoot = true) const;

	virtual bool removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient, bool nullifyParent) const;
};

#endif /* SpaceZoneContainerCOMPONENT_H_ */
