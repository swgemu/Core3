/*
 * BitmapGroup.h
 *
 *  Created on: 06/09/2013
 *      Author: victor
 */

#ifndef BITMAPGROUP_H_
#define BITMAPGROUP_H_

#include "MapFamily.h"
#include "BitmapFamily.h"

#include "TargaBitmap.h"

class BitmapGroup : public TemplateVariable<'MGRP'> {
	Vector<BitMapFamily*> mfams;
	VectorMap<uint32, TargaBitmap*> mfrcs;

public:
	BitmapGroup() {
	}

	~BitmapGroup() {
		while (mfams.size() > 0)
			delete mfams.remove(0);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown MGRP version " << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		int number = iffStream->getSubChunksNumber();

		for (int i = 0; i < number; ++i) {
			BitMapFamily* sfam = new BitMapFamily();
			sfam->readObject(iffStream);
			mfams.add(sfam);
			mfrcs.put(sfam->getVar1(), sfam->getMap());
		}
	}

	inline TargaBitmap* getBitmap(int index) {
		return mfrcs.get((uint32)index);
	}

};


#endif /* BITMAPGROUP_H_ */
