/*
 * CloseContainerObserver.h
 *
 *  Created on: 12/05/2010
 *      Author: victor
 */

#ifndef CLOSECONTAINEROBSERVER_H_
#define CLOSECONTAINEROBSERVER_H_

#include "Observer.h"

class CloseContainerObserver : public Observer {
public:
	/**
	 * @return 0 to not deattach the observer after running
	 * @return 1 to deattach the observer after running
	 */
	virtual int notifyCloseContainer(PlayerCreature* player, SceneObject* container) = 0;
};



#endif /* CLOSECONTAINEROBSERVER_H_ */
