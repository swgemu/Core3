/*
 * SlotDescriptor.h
 *
 *  Created on: May 25, 2011
 *      Author: crush
 */

#ifndef SLOTDESCRIPTOR_H_
#define SLOTDESCRIPTOR_H_

#include "templates/IffTemplate.h"

class SlotDescriptor : public IffTemplate {
	Vector<String> slots;

public:
	SlotDescriptor() {
	}

	void readObject(IffStream* iffStream) {
		iffStream->openForm('SLTD');
		uint32 version = iffStream->getNextFormType();
		iffStream->openForm(version);

		switch (version) {
		case '0000':
		{
			Chunk* data = iffStream->openChunk('DATA');

			while (data->hasData()) {
				String slotName;
				data->readString(slotName);
				slots.add(slotName);
			}

			iffStream->closeChunk('DATA');
		}
			break;
		}

		iffStream->closeForm(version);
		iffStream->closeForm('SLTD');
	}

	void clone(Vector<String>& copyVec) {
		slots.clone(copyVec);
	}

	Vector<String>* getSlots() {
		return &slots;
	}
};

#endif /* SLOTDESCRIPTOR_H_ */
