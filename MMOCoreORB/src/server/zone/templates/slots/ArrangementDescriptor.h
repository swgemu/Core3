/*
 * ArrangementDescriptor.h
 *
 *  Created on: May 25, 2011
 *      Author: crush
 */

#ifndef ARRANGEMENTDESCRIPTOR_H_
#define ARRANGEMENTDESCRIPTOR_H_

#include "engine/engine.h"
#include "../IffTemplate.h"

class ArrangementDescriptor : public IffTemplate {
	Vector<String> arrangementSlots;

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

				if (!arg->hasData())
					continue;

				String slotName;
				arg->readString(slotName);
				arrangementSlots.add(slotName);
				iffStream->closeChunk('ARG ');
			}
		}

		break;
		}

		iffStream->closeForm(version);
		iffStream->closeForm('ARGD');
	}

	void clone(Vector<String>& copyVec) {
		arrangementSlots.clone(copyVec);
	}

	Vector<String>* getArrangementSlots() {
		return &arrangementSlots;
	}
};


#endif /* ARRANGEMENTDESCRIPTOR_H_ */
