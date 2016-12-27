/*
 * ArrangementDescriptor.h
 *
 *  Created on: May 25, 2011
 *      Author: crush
 */

#ifndef ARRANGEMENTDESCRIPTOR_H_
#define ARRANGEMENTDESCRIPTOR_H_

#include "templates/IffTemplate.h"

class ArrangementDescriptor : public IffTemplate {
	Vector< Vector<String> > arrangementSlots;

public:
	ArrangementDescriptor() {
	}

	void readObject(IffStream* iffStream) {
		iffStream->openForm('ARGD');
		uint32 version = iffStream->getNextFormType();
		Chunk* versionForm = iffStream->openForm(version);

		switch (version) {
		case '0000':
		{
			for (int i = 0; i < versionForm->getChunksSize(); ++i) {
				Chunk* arg = iffStream->openChunk('ARG ');
				Vector<String>  slot;

				while (arg->hasData()) {
					String slotName;
					arg->readString(slotName);

					slot.add(slotName);
				}

				arrangementSlots.add(slot);

				iffStream->closeChunk('ARG ');
			}
		}

		break;
		}

		iffStream->closeForm(version);
		iffStream->closeForm('ARGD');
	}

	void clone(Vector< Vector<String> >& copyVec) {
		arrangementSlots.clone(copyVec);
	}

	const Vector< Vector<String> >& getArrangementSlots() const {
		return arrangementSlots;
	}
};

#endif /* ARRANGEMENTDESCRIPTOR_H_ */
