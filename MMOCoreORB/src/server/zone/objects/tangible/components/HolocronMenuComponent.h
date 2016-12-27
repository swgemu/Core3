/*
 * HolocronMenuComponent.h
 *
 *  Created on: 01/23/2012
 *      Author: xyborn
 */

#ifndef HOLOCRONMENUCOMPONENT_H_
#define HOLOCRONMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

class HolocronMenuComponent : public TangibleObjectMenuComponent {
public:
	int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;
};


#endif /* HOLOCRONMENUCOMPONENT_H_ */
