/*
 * Observer.h
 *
 *  Created on: 18/04/2010
 *      Author: victor
 */

#ifndef SCENEOBJECTOBSERVER_H_
#define SCENEOBJECTOBSERVER_H_

#include "Observer.h"

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

class SceneObjectObserver : public Observer {
public:
	/**
	 * @return 0 to not deattach the observer after running
	 * @return 1 to deattach the observer after running
	 */
	virtual int notify(SceneObject* object) = 0;
};


#endif /* OBSERVER_H_ */
