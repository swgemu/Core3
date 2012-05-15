/*
 * AiDummyComponent.h
 *
 *  Created on: Feb 15, 2012
 *      Author: da
 */

#ifndef AIDUMMYCOMPONENT_H_
#define AIDUMMYCOMPONENT_H_

#include "engine/engine.h"
#include "AiInterfaceComponent.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
    class SceneObject;
   }
  }
 }
}

using namespace server::zone::objects::scene;

class AiDummyComponent : public AiInterfaceComponent {
public:
	void notifyPositionUpdate(SceneObject* scno, QuadTreeEntry* entry) {
		if (scno == NULL || entry == NULL || scno == entry)
			return;

//#ifdef WITH_STM
		scno->notifyObservers(ObserverEventType::OBJECTINRANGEMOVED, entry);
//#else


		//Core::getTaskManager()->executeTask(new PositionUpdateTask(_this, entry));
//#endif
	}
};

#endif /* AIDUMMYCOMPONENT_H_ */
