/*
 * TreeFile.h
 *
 *  Created on: Apr 5, 2011
 *      Author: crush
 */

#ifndef TREEFILE_H_
#define TREEFILE_H_

#include "engine/engine.h"
#include "TreeFileRecord.h"
#include "TreeDataBlock.h"

class TreeArchive;

class TreeFile : public Logger {
	TreeArchive* treeArchive;

	String filePath;
	int version;
	int totalRecords;
	int dataOffset;

	TreeDataBlock fileBlock;
	TreeDataBlock nameBlock;

	Vector<Reference<TreeFileRecord*> > records;

	void readHeader(FileInputStream* fileStream);
	void readFileBlock(FileInputStream* fileStream);
	void readNameBlock(FileInputStream* fileStream);
	void readMD5Sums(FileInputStream* fileStream);

public:
	TreeFile(TreeArchive* archive);
	~TreeFile();

	void read(const String& path);
	//void write(const String& filePath);
};

#endif /* TREEFILE_H_ */
