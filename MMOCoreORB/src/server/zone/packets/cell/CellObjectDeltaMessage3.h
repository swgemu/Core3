/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#ifndef CELLOBJECTDELTAMESSAGE3_H_
#define CELLOBJECTDELTAMESSAGE3_H_

#include "../../packets/DeltaMessage.h"

#include "../../objects/building/cell/CellObject.h"

class CellObjectDeltaMessage3 : public DeltaMessage {
	CellObject* cell;

public:
	CellObjectDeltaMessage3(CellObject* co)
			: DeltaMessage(co->getObjectID(), 0x53434C54, 3) {
		cell = co;
	}

	void updateCellNumber(int cellNumber) {
		addIntUpdate(5, cellNumber);
	}
};


#endif /* CELLOBJECTDELTAMESSAGE3_H_ */
