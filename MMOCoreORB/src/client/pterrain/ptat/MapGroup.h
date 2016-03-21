/*
 * MapGroup.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef MAPGROUP_H_
#define MAPGROUP_H_

#include "MapFractal.h"
#include "MapFamily.h"

class MapGroup : public TemplateVariable<'MGRP'> {
	Vector<MapFamily*> mfams;
	VectorMap<uint32, MapFractal*> mfrcs;

public:

	MapGroup() {
		mfrcs.setNullValue(NULL);
		mfrcs.setNoDuplicateInsertPlan();
	}

	~MapGroup() {
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
			MapFamily* sfam = new MapFamily();
			sfam->readObject(iffStream);
			mfams.add(sfam);
			mfrcs.put(sfam->getVar1(), sfam->getMfrc());
		}
	}

	inline MapFractal* getMfrc(int index) {
		return mfrcs.get((uint32)index);
	}

};



#endif /* MAPGROUP_H_ */
