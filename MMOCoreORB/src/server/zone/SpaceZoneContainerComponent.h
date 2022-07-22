/*
 * SpaceZoneContainerComponent.h
 *
 *  Created on: 03/09/2011
 *      Author: TheAnswer
 */

#ifndef SPACEZONECONTAINERCOMPONENT_H_
#define SPACEZONECONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

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

class SpaceZoneContainerComponent : public ContainerComponent {
protected:
	bool insertActiveArea(SpaceZone* zone, ActiveArea* activeArea) const;
	bool removeActiveArea(SpaceZone* zone, ActiveArea* activeArea) const;
public:
	virtual bool transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient = false, bool allowOverflow = false, bool notifyRoot = true) const;

	virtual bool removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient) const;
};

#endif /* SpaceZoneContainerCOMPONENT_H_ */
