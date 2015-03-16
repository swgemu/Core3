/*
 * CloseLotteryWindow.h
 *
 *  Created on: Mar 16, 2015
 *      Author: swgemu
 */

#ifndef CLOSELOTTERYWINDOW_H_
#define CLOSELOTTERYWINDOW_H_


#include "ObjectControllerMessage.h"

class CloseLotteryWindow : public ObjectControllerMessage {
public:
	CloseLotteryWindow(CreatureObject* creo, SceneObject* inventory)
			: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0x43D) {
		insertLong(inventory->getObjectID());
	}

};


#endif /* CLOSELOTTERYWINDOW_H_ */
