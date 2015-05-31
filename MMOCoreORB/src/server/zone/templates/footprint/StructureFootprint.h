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

		rows = sfp.rows;
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

		rows = sfp.rows;

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
				colSize = info->readInt();
				rowSize = info->readInt();
				centerX = info->readInt();
				centerY = info->readInt();
				colChunkSize = info->readFloat();
				rowChunkSize = info->readFloat();
				iffStream->closeChunk('INFO');

				//TODO: Parse chunk PRNT
			}
			break;
		}

		iffStream->closeForm(version);
		iffStream->closeForm('FOOT');
	}

	String toString() {
		StringBuffer str;
		str << "{rowSize=" << rowSize << ";colSize=" << colSize << ";centerX=" << centerX << ";centerY=" << centerY << ";rowChunkSize=" << rowChunkSize << ";colChunkSize=" << colChunkSize << "}";

		return str.toString();
	}

	inline float getRowSize() {
		return rowSize;
	}

	inline float getColSize() {
		return colSize;
	}

	inline float getCenterX() {
		return centerX;
	}

	inline float getCenterY() {
		return centerY;
	}

	inline float getRowChunkSize() {
		return rowChunkSize;
	}

	inline float getColChunkSize() {
		return colChunkSize;
	}
};


#endif /* STRUCTUREFOOTPRINT_H_ */
