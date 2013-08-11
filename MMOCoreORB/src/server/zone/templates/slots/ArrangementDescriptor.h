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
	bool optional;

public:
	ArrangementDescriptor() {
		optional = false;
	}

	void readObject(IffStream* iffStream) {
		iffStream->openForm('ARGD');
		uint32 version = iffStream->getNextFormType();
		Chunk* versionForm = iffStream->openForm(version);

		optional = (iffStream->getSubChunksNumber() > 1);

		switch (version) {
		case '0000':
		{

			//for (int i = 0; i < versionForm->getChunksSize(); ++i) {
			//for (int i = 0; i < MIN(versionForm->getChunksSize(), 1); ++i) { // TODO:figure out different arrangement groups
			while(iffStream->getRemainingSubChunksNumber() > 0) {
				Chunk* arg = iffStream->openChunk('ARG ');

				while (arg->hasData()) {
					String slotName;
					arg->readString(slotName);
					arrangementSlots.add(slotName);
				}

				iffStream->closeChunk('ARG ');
			}
			//}
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

	bool isOptional(){
		return optional;
	}

};


#endif /* ARRANGEMENTDESCRIPTOR_H_ */
