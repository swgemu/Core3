/*
 * PostureChangedObserver.h
 *
 *  Created on: 23/05/2010
 *      Author: victor
 */

#ifndef POSTURECHANGEDOBSERVER_H_
#define POSTURECHANGEDOBSERVER_H_

#include "server/zone/objects/scene/Observer.h"

namespace server {
 namespace zone {
	 namespace objects {
	  namespace creature {
		  class CreatureObject;
	  }
	 }
 }
}

using namespace server::zone::objects::creature;

class PostureChangeObserver : public Observer {
public:
	/**
	 * @return 0 to not deattach the observer after running
	 * @return 1 to deattach the observer after running
	 */
	virtual int notifyPostureChange(CreatureObject* object, int newPosture) = 0;

};


#endif /* POSTURECHANGEDOBSERVER_H_ */
