/*
 * StructureFootprint.h
 *
 *  Created on: Apr 30, 2011
 *      Author: crush
 */

#ifndef STRUCTUREFOOTPRINT_H_
#define STRUCTUREFOOTPRINT_H_

#include "engine/engine.h"
#include "../IffTemplate.h"

class StructureFootprint : public IffTemplate {
	int rowSize;
	int colSize;

	int centerX;
	int centerY;

	float rowChunkSize;
	float colChunkSize;

	Vector<String> rows;

public:
	StructureFootprint() {
		rowSize = 0;
		colSize = 0;

		centerX = 0;
		centerY = 0;

		rowChunkSize = 0.f;
		colChunkSize = 0.f;
	}

	StructureFootprint(const StructureFootprint& sfp) : Object(), TemplateData(), IffTemplate() {
		rowSize = sfp.rowSize;
		colSize = sfp.colSize;

		centerX = sfp.centerX;
		centerY = sfp.centerY;

		rowChunkSize = sfp.rowChunkSize;
		colChunkSize = sfp.colChunkSize;
	}

	StructureFootprint& operator= (const StructureFootprint& sfp) {
		if (this == &sfp)
			return *this;

		rowSize = sfp.rowSize;
		colSize = sfp.colSize;

		centerX = sfp.centerX;
		centerY = sfp.centerY;

		rowChunkSize = sfp.rowChunkSize;
		colChunkSize = sfp.colChunkSize;

		return *this;
	}

	void readObject(IffStream* iffStream) {
		iffStream->openForm('FOOT');

		uint32 version = iffStream->getNextFormType();
		iffStream->openForm(version);

		switch (version) {
			case '0000':
			{
				Chunk* info = iffStream->openChunk('INFO');
				rowSize = info->readInt();
				colSize = info->readInt();
				centerX = info->readInt();
				centerY = info->readInt();
				rowChunkSize = info->readFloat();
				colChunkSize = info->readFloat();
				iffStream->closeChunk('INFO');

				//TODO: Parse chunk PRNT
			}
			break;
		}

		iffStream->closeForm(version);
		iffStream->closeForm('FOOT');
	}

	String toString() const {
		StringBuffer str;
		str << "{rowSize=" << rowSize << ";colSize=" << colSize << ";rowChunkSize=" << rowChunkSize << ";colChunkSize=" << colChunkSize << "}";

		return str.toString();
	}

	/**
	 * Gets the length of the StructureFootprint rectangle.
	 * Length is along the x axis in geometry.
	 * @return Returns the length as a float.
	 */
	inline float getLength() {
		return rowSize * rowChunkSize;
	}

	/**
	 * Gets the width of the StructureFootprint rectangle.
	 * Width is along the y axis in geometry.
	 * @return Returns the width as a float.
	 */
	inline float getWidth() {
		return colSize * colChunkSize;
	}
};


#endif /* STRUCTUREFOOTPRINT_H_ */
