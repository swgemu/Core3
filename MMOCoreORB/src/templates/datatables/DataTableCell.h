/*
 * DataTableCell.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef DATATABLECELL_H_
#define DATATABLECELL_H_

#include "system/lang.h"
#include "engine/util/iffstream/chunks/Chunk.h"

class DataTableCell {
public:
	DataTableCell() {
	}

	virtual ~DataTableCell() {

	}

	virtual void parse(Chunk* chunk) = 0;

	/*template<typename V>
	void getValue(V& out) {
		throw Exception("No valid type specified.");
	}*/

	virtual void getValue(Vector<String>& out) const {
		throw Exception(String("No valid type specified. Correct type is ").concat((char)getType()));
	}

	virtual void getValue(SortedVector<String>& out) const {
		throw Exception(String("No valid type specified. Correct type is ").concat((char)getType()));
	}

	virtual void getValue(String& out) const {
		throw Exception(String("No valid type specified. Correct type is ").concat((char)getType()));
	}

	virtual void getValue(int& out) const {
		throw Exception(String("No valid type specified. Correct type is ").concat((char)getType()));
	}

	virtual void getValue(uint32& out) const {
		throw Exception(String("No valid type specified. Correct type is ").concat((char)getType()));
	}

	virtual void getValue(float& out) const {
		throw Exception(String("No valid type specified. Correct type is ").concat((char)getType()));
	}

	virtual void getValue(bool& out) const {
		throw Exception(String("No valid type specified. Correct type is ").concat((char)getType()));
	}


	virtual byte getType() const = 0;

	virtual String toString() const = 0;
};

class DataTableCellString : public DataTableCell {
	String value;

public:
	DataTableCellString() {
	}

	void getValue(SortedVector<String>& out) const;
	void getValue(Vector<String>& out) const;

	void parse(Chunk* chunk) {
		chunk->readString(value);
	}

	void getValue(String& out) const {
		out = value;
	}

	byte getType() const {
		return 's';
	}

	String toString() const {
		return value;
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

	void getValue(int& out) const {
		out = value;
	}

	byte getType() const {
		return 'i';
	}

	String toString() const {
		return String::valueOf(value);
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

	void getValue(uint32& out) const {
		out = value;
	}

	byte getType() const {
		return 'h';
	}

	String toString() const {
		return String::valueOf(value);
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

	void getValue(float& out) const {
		out = value;
	}

	byte getType() const {
		return 'f';
	}

	String toString() const {
		return String::valueOf(value);
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

	void getValue(bool& out) const {
		out = value;
	}

	byte getType() const {
		return 'b';
	}

	String toString() const {
		return String::valueOf(value);
	}
};

#endif /* DATATABLECELL_H_ */
