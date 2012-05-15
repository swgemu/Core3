/*
 * ObjCtrlMessageQueueString.h
 *
 *  Created on: 10/01/2012
 *      Author: victor
 */

#ifndef OBJCTRLMESSAGEQUEUESTRING_H_
#define OBJCTRLMESSAGEQUEUESTRING_H_

#include "ObjectControllerMessage.h"

class ObjCtrlMessageQueueString : public ObjectControllerMessage {
public:
	ObjCtrlMessageQueueString(SceneObject* creo, const String& data, uint32 type)
			: ObjectControllerMessage(creo->getObjectID(), 0x1B, type, false) {

			insertAscii(data.toCharArray());
	}
};


#endif /* OBJCTRLMESSAGEQUEUESTRING_H_ */
