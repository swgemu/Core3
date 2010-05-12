/*
 * Observer.h
 *
 *  Created on: 18/04/2010
 *      Author: victor
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

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

class SceneObjectObserver {
public:
	/**
	 * @return 0 to not deattach the observer after running
	 * @return 1 to deattach the observer after running
	 */
	virtual int notify(SceneObject* object) = 0;

	int compareTo(SceneObjectObserver* obj) {
		if (this < obj) {
			return 1;
		} else if (this > obj) {
			return -1;
		} else
			return 0;
	}
};


#endif /* OBSERVER_H_ */
