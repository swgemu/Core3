/*
 * DeltaIntVariable.h
 *
 *  Created on: 18/10/2013
 *      Author: victor
 */

#ifndef DELTAINTVARIABLE_H_
#define DELTAINTVARIABLE_H_

#include "DeltaBasicVariable.h"

template<int BaselineName, uint8 Type, int DeltaID>
class DeltaIntVariable : public DeltaBasicVariable<int> {
public:
	void update(int newValue, bool broadcastStandalone = false, SceneObject* obj = NULL) {
		set(newValue);

		if (broadcastStandalone) {
			broadcastStandaloneDeltaMessage(obj);
		}
	}

	void broadcastStandaloneDeltaMessage(SceneObject* obj) {
		DeltaMessage* msg = new DeltaMessage(obj->getObjectID(), BaselineName, Type);
		addToDeltaMessage(msg);
		msg->close();

		obj->broadcastMessage(msg, true);
	}

	void addToDeltaMessage(DeltaMessage* msg) {
		msg->addIntUpdate(DeltaID, object);
	}
};


#endif /* DELTAINTVARIABLE_H_ */
