/*
 * TreeDataBlock.h
 *
 *  Created on: Apr 6, 2011
 *      Author: crush
 */

#ifndef TREEDATABLOCK_H_
#define TREEDATABLOCK_H_

#include "engine/engine.h"

namespace zlib {
	#include <zlib.h>
}

class TreeDataBlock {
	uint32 compressionType;

	unsigned long compressedSize;
	unsigned long uncompressedSize;

	//md5sum

public:
	const static int SIZE = 6 * sizeof(int);

public:
	TreeDataBlock() {
		compressionType = 0;
		compressedSize = 0;
		uncompressedSize = 0;
	}

	TreeDataBlock(const TreeDataBlock& tdb) {
		compressionType = tdb.compressionType;
		compressedSize = tdb.compressedSize;
		uncompressedSize = tdb.uncompressedSize;
	}

	TreeDataBlock& operator= (const TreeDataBlock& tdb) {
		if (this == &tdb)
			return *this;

		compressionType = tdb.compressionType;
		compressedSize = tdb.compressedSize;
		uncompressedSize = tdb.uncompressedSize;

		return *this;
	}

	void read(FileInputStream& fileStream, int offset) {

	}

	/**
	 * Uncompresses a block of data and returns it in a byte buffer.
	 * @param fileStream FileInputStream that has been advanced to the position of the compressedData and will be read for the compressedSize
	 */
	byte* uncompress(FileInputStream& fileStream) {
		byte* uncompressedData = new byte[uncompressedSize];

		switch (compressionType) {
		case 2: //Data is compressed
		{
			byte* compressedData = new byte[compressedSize];

			fileStream.read(compressedData, compressedSize);

			int result = zlib::uncompress(uncompressedData, &uncompressedSize, compressedData, compressedSize);

			delete [] compressedData;
		}
			break;
		case 0: //Data is uncompressed
		default:
			fileStream.read(uncompressedData, uncompressedSize);
		}

		return uncompressedData;
	}

	void compress() {

	}

	inline void setCompressionType(uint32 value) {
		compressionType = value;
	}

	inline void setCompressedSize(uint32 value) {
		compressedSize = value;
	}

	inline void setUncompressedSize(uint32 value) {
		uncompressedSize = value;
	}

	inline uint32 getCompressedSize() {
		return compressedSize;
	}

	inline uint32 getUncompressedSize() {
		return uncompressedSize;
	}
};


#endif /* TREEDATABLOCK_H_ */
