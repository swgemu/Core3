/*
 * Observer.h
 *
 *  Created on: 29/05/2010
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

	  namespace tangible {
		  class TangibleObject;
	  }

	  namespace player {
		  class PlayerCreature;
	  }
	 }
 }
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::player;
using namespace server::zone::objects::tangible;

class Observer {
public:
	int compareTo(Observer* obj) {
		if (this < obj) {
			return 1;
		} else if (this > obj) {
			return -1;
		} else
			return 0;
	}
};


#endif /* OBSERVER_H_ */
