/*
 * TreeFileRecord.h
 *
 *  Created on: Apr 6, 2011
 *      Author: crush
 */

#ifndef TREEFILERECORD_H_
#define TREEFILERECORD_H_

#include "engine/engine.h"

class TreeFileRecord : public Object {
	String recordName;

	uint32 checksum;
	uint32 uncompressedSize;
	uint32 fileOffset;
	uint32 compressionType;
	uint32 compressedSize;
	uint32 nameOffset;

	byte md5Sum[16];

public:
	TreeFileRecord() : Object() {

	}

	TreeFileRecord(const TreeFileRecord& tfr) : Object() {
		checksum = tfr.checksum;
		uncompressedSize = tfr.uncompressedSize;
		fileOffset = tfr.fileOffset;
		compressionType = tfr.compressionType;
		compressedSize = tfr.compressedSize;
		nameOffset = tfr.nameOffset;
		memcpy(md5Sum, tfr.md5Sum, 16);
	}

	TreeFileRecord& operator= (const TreeFileRecord& tfr) {
		if (this == &tfr)
			return *this;

		checksum = tfr.checksum;
		uncompressedSize = tfr.uncompressedSize;
		fileOffset = tfr.fileOffset;
		compressionType = tfr.compressionType;
		compressedSize = tfr.compressedSize;
		nameOffset = tfr.nameOffset;
		memcpy(md5Sum, tfr.md5Sum, 16);

		return *this;
	}

	int compareTo(const TreeFileRecord& tfr) const {
		return recordName.compareTo(tfr.recordName);
	}

	void read(FileInputStream& fileStream) {
		fileStream.read((byte*) &checksum, 4);
		fileStream.read((byte*) &uncompressedSize, 4);
		fileStream.read((byte*) &fileOffset, 4);
		fileStream.read((byte*) &compressionType, 4);
		fileStream.read((byte*) &compressedSize, 4);
		fileStream.read((byte*) &nameOffset, 4);
	}

	uint32 readFromBuffer(const char* buffer) {
	    uint32 bufferOffset = 0;

	    memcpy(&checksum, buffer + bufferOffset, sizeof(checksum));
	    bufferOffset += sizeof(checksum);

	    memcpy(&uncompressedSize, buffer + bufferOffset, sizeof(uncompressedSize));
	    bufferOffset += sizeof(uncompressedSize);

	    memcpy(&fileOffset, buffer + bufferOffset, sizeof(fileOffset));
	    bufferOffset += sizeof(fileOffset);

	    memcpy(&compressionType, buffer + bufferOffset, sizeof(compressionType));
	    bufferOffset += sizeof(compressionType);

	    memcpy(&compressedSize, buffer + bufferOffset, sizeof(compressedSize));
	    bufferOffset += sizeof(compressedSize);

	    memcpy(&nameOffset, buffer + bufferOffset, sizeof(nameOffset));
	    bufferOffset += sizeof(nameOffset);

	    return bufferOffset;
	}

	String toString() const {
		StringBuffer str;
		str << "Checksum: " << checksum;
		str << " UncompressedSize: " << uncompressedSize;
		str << " FileOffset: " << fileOffset;
		str << " CompressionType: " << compressionType;
		str << " FileSize: " << compressedSize;
		str << " NameOffset: " << nameOffset;

		return str.toString();
	}

	inline void setMD5Sum(byte sum[16]) {
		memcpy(&md5Sum, sum, 16);
	}

	inline uint32 getNameOffset() {
		return nameOffset;
	}

	inline uint32 getCompressionType() {
		return compressionType;
	}

	inline void setRecordName(const String& name) {
		recordName = name;
	}

	inline String& getRecordName() {
		return recordName;
	}
};


#endif /* TREEFILERECORD_H_ */
