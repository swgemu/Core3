/*
 * ForceCrystalMenuComponent.h
 */

#ifndef FORCECRYSTALMENUCOMPONENT_H_
#define FORCECRYSTALMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

class ForceCrystalMenuComponent : public TangibleObjectMenuComponent {
public:
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;

	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;

};


#endif /* FORCECRYSTALMENUCOMPONENT_H_ */
