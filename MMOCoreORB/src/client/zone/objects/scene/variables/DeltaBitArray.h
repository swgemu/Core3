/*
 * DeltaBitArray.h
 *
 *  Created on: 15/11/2013
 *      Author: victor
 */

#ifndef DELTABITARRAY_H_
#define DELTABITARRAY_H_

#include "DeltaVector.h"
#include "engine/engine.h"

class DeltaBitArray : public DeltaVector<byte> {
public:
	DeltaBitArray() : DeltaVector<byte>(1, 1) {
	}

	DeltaBitArray(int initsize, int incr) : DeltaVector<byte>(initsize, incr) {
	}

	DeltaBitArray(const DeltaBitArray& v) : Object(), DeltaVector<byte>(v) {
	}

	DeltaBitArray& operator=(const DeltaBitArray& v) {
		if (this == &v)
			return *this;

		DeltaVector<byte>::operator =(v);

		return *this;
	}

	void setBit(uint32 bitIndex, byte value) {
		int vectorIndex = bitIndex / 8;
		byte vectorBitIndex = 1 << (bitIndex % 8);

		while (size() <= vectorIndex)
			add(0);

		byte currentVal = get(vectorIndex);

		if (value) {
			if (!(currentVal & vectorBitIndex)) {
				currentVal |= vectorBitIndex;
			}
		} else {
			if (currentVal & vectorBitIndex) {
				currentVal &= ~vectorBitIndex;
			}
		}

		set(vectorIndex, currentVal);
	}

	bool getBitValue(uint32 bitIndex) {
		int vectorIndex = bitIndex / 8;
		byte vectorBitIndex = 1 << (bitIndex % 8);

		if (vectorIndex >= size())
			return false;

		byte val = get(vectorIndex);

		return val & vectorBitIndex;
	}

	void clearBit(int bitIndex) {
		setBit(bitIndex, 0);
	}

	int bitCount() {
		return size() * 8;
	}
};


#endif /* DELTABITARRAY_H_ */
