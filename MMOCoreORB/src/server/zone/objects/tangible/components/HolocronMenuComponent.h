/*
 * HolocronMenuComponent.h
 *
 *  Created on: 01/23/2012
 *      Author: xyborn
 */

#ifndef HOLOCRONMENUCOMPONENT_H_
#define HOLOCRONMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"
#include "system/platform.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server

class HolocronMenuComponent : public TangibleObjectMenuComponent {
public:
	int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;
};


#endif /* HOLOCRONMENUCOMPONENT_H_ */
