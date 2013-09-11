/*
 * TreeFileRecord.h
 *
 *  Created on: Apr 6, 2011
 *      Author: crush
 */

#ifndef TREEFILERECORD_H_
#define TREEFILERECORD_H_

#include "engine/engine.h"
#include "TreeDataBlock.h"

class TreeFileRecord : public Object, public Logger {
	String recordName;
	String treeFilePath;

	uint32 checksum;
	uint32 uncompressedSize;
	uint32 fileOffset;
	uint32 compressionType;
	uint32 compressedSize;
	uint32 nameOffset;

	byte md5Sum[16];

public:
	TreeFileRecord() : Object(), Logger() {
		setLoggingName("TreeFileRecord");
		setLogging(true);
	}

	TreeFileRecord(const TreeFileRecord& tfr) : Object(), Logger() {
		recordName = tfr.recordName;
		treeFilePath = tfr.treeFilePath;
		checksum = tfr.checksum;
		uncompressedSize = tfr.uncompressedSize;
		fileOffset = tfr.fileOffset;
		compressionType = tfr.compressionType;
		compressedSize = tfr.compressedSize;
		nameOffset = tfr.nameOffset;
		memcpy(md5Sum, tfr.md5Sum, 16);

		setLoggingName("TreeFileRecord " + recordName);
		setLogging(true);
	}

	TreeFileRecord& operator= (const TreeFileRecord& tfr) {
		if (this == &tfr)
			return *this;

		recordName = tfr.recordName;
		treeFilePath = tfr.treeFilePath;
		checksum = tfr.checksum;
		uncompressedSize = tfr.uncompressedSize;
		fileOffset = tfr.fileOffset;
		compressionType = tfr.compressionType;
		compressedSize = tfr.compressedSize;
		nameOffset = tfr.nameOffset;
		memcpy(md5Sum, tfr.md5Sum, 16);

		setLoggingName("TreeFileRecord " + recordName);

		return *this;
	}

	int compareTo(const TreeFileRecord& tfr) const {
		return recordName.compareTo(tfr.recordName);
	}

	int compareTo(const String& fileName) const {
		return recordName.compareTo(fileName);
	}

	void read(FileInputStream* fileStream) {
		fileStream->read((byte*) &checksum, 4);
		fileStream->read((byte*) &uncompressedSize, 4);
		fileStream->read((byte*) &fileOffset, 4);
		fileStream->read((byte*) &compressionType, 4);
		fileStream->read((byte*) &compressedSize, 4);
		fileStream->read((byte*) &nameOffset, 4);
	}

	uint32 readFromBuffer(const byte* buffer) {
	    uint32 bufferOffset = 0;

	    checksum = *(uint32*)(buffer + bufferOffset);
	    bufferOffset += sizeof(checksum);

	    uncompressedSize = *(uint32*)(buffer + bufferOffset);
	    bufferOffset += sizeof(uncompressedSize);

	    fileOffset = *(uint32*)(buffer + bufferOffset);
	    bufferOffset += sizeof(fileOffset);

	    compressionType = *(uint32*)(buffer + bufferOffset);
	    bufferOffset += sizeof(compressionType);

	    compressedSize = *(uint32*)(buffer + bufferOffset);
	    bufferOffset += sizeof(compressedSize);

	    nameOffset = *(uint32*)(buffer + bufferOffset);
	    bufferOffset += sizeof(nameOffset);

	    return bufferOffset;
	}

	byte* getBytes() {
		File* file = new File(treeFilePath);

		FileInputStream fileStream(file);

		if (!file->exists()) {
			error("Tree File does not exist: " + treeFilePath);
			delete file;
			return NULL;
		}

		fileStream.skip(fileOffset);

		TreeDataBlock db;
		db.setCompressedSize(compressedSize);
		db.setUncompressedSize(uncompressedSize);
		db.setCompressionType(compressionType);

		byte* buffer = db.uncompress(&fileStream);

		fileStream.close();

		delete file;

		return buffer;
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

	inline uint32 getUncompressedSize() {
		return uncompressedSize;
	}

	inline void setRecordName(const String& name) {
		recordName = name;
	}

	inline String& getRecordName() {
		return recordName;
	}

	inline void setTreeFilePath(const String& path) {
		treeFilePath = path;
	}
};


#endif /* TREEFILERECORD_H_ */
