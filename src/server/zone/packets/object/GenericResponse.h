/*
 * GenericResponse.h
 *
 *  Created on: Oct 11, 2008
 *      Author: swgemu
 */

#ifndef GENERICRESPONSE_H_
#define GENERICRESPONSE_H_

class GenericResponse : public ObjectControllerMessage {
public:
	GenericResponse(PlayerCreature* play, uint32 msg, uint8 byte1, uint8 byte2)
			: ObjectControllerMessage(play->getObjectID(), 0x0B, 0xEE) {
		insertInt(msg);
		insertByte(byte1);
		insertByte(byte2);
		//setSize();
	}

};
#endif /* GENERICRESPONSE_H_ */
