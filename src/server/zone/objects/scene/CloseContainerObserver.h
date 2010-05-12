/*
 * CloseContainerObserver.h
 *
 *  Created on: 12/05/2010
 *      Author: victor
 */

#ifndef CLOSECONTAINEROBSERVER_H_
#define CLOSECONTAINEROBSERVER_H_


namespace server {
 namespace zone {
	 namespace objects {
	  namespace scene {
		  class SceneObject;
	  }

	  namespace player {
		  class PlayerCreature;
	  }
	 }
 }
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::player;

class CloseContainerObserver {
public:
	/**
	 * @return 0 to not deattach the observer after running
	 * @return 1 to deattach the observer after running
	 */
	virtual int notifyCloseContainer(PlayerCreature* player, SceneObject* container) = 0;

	int compareTo(CloseContainerObserver* obj) {
		if (this < obj) {
			return 1;
		} else if (this > obj) {
			return -1;
		} else
			return 0;
	}
};



#endif /* CLOSECONTAINEROBSERVER_H_ */
