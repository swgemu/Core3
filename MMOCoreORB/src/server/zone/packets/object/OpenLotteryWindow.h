/*
 * OpenLotteryWindow.h
 *
 *  Created on: Mar 16, 2015
 *      Author: swgemu
 */

#ifndef OPENLOTTERYWINDOW_H_
#define OPENLOTTERYWINDOW_H_


#include "ObjectControllerMessage.h"

class OpenLotteryWindow : public ObjectControllerMessage {
public:
	OpenLotteryWindow(CreatureObject* creo, SceneObject* inventory)
			: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0x43C) {
		insertLong(inventory->getObjectID());
	}

};


#endif /* OPENLOTTERYWINDOW_H_ */
