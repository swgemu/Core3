/*
 * DataTableCell.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef DATATABLECELL_H_
#define DATATABLECELL_H_

#include "engine/engine.h"

class DataTableCell {
public:
	DataTableCell() {
	}

	virtual void parse(Chunk* chunk) = 0;

	virtual void getValue(String& out) {
		out = "";
	}

	virtual void getValue(float& out) {
		out = 0.f;
	}

	virtual void getValue(int& out) {
		out = 0;
	}

	virtual void getValue(uint32& out) {
		out = 0;
	}

	virtual void getValue(bool& out) {
		out = false;
	}
};

class DataTableCellString : public DataTableCell {
	String value;

public:
	DataTableCellString() {
	}

	void parse(Chunk* chunk) {
		chunk->readString(value);
	}

	void getValue(String& out) {
		out = value;
	}
};

class DataTableCellInt : public DataTableCell {
	int value;

public:
	DataTableCellInt() {
		value = 0;
	}

	void parse(Chunk* chunk) {
		value = chunk->readSignedInt();
	}

	void getValue(int& out) {
		out = value;
	}
};

class DataTableCellHex : public DataTableCell {
	uint32 value;

public:
	DataTableCellHex() {
		value = 0;
	}

	void parse(Chunk* chunk) {
		value = chunk->readInt();
	}

	void getValue(uint32& out) {
		out = value;
	}
};

class DataTableCellFloat : public DataTableCell {
	float value;

public:
	DataTableCellFloat() {
			value = 0.f;
	}

	void parse(Chunk* chunk) {
		value = chunk->readFloat();
	}

	void getValue(float& out) {
		out = value;
	}
};

class DataTableCellBinary : public DataTableCell {
	bool value;

public:
	DataTableCellBinary() {
		value = false;
	}

	void parse(Chunk* chunk) {
		value = (bool) chunk->readInt();
	}

	void getValue(bool& out) {
		out = value;
	}
};

#endif /* DATATABLECELL_H_ */
