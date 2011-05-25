/*
 * TreeArchive.h
 *
 *  Created on: Apr 7, 2011
 *      Author: crush
 */

#ifndef TREEARCHIVE_H_
#define TREEARCHIVE_H_

#include "engine/engine.h"
#include "TreeFile.h"
#include "TreeDirectory.h"

class TreeArchive : public Logger {
	VectorMap<String, TreeDirectory> nodeMap;

public:
	TreeArchive() {
		setLoggingName("TreeArchive");
		setLogging(true);

		nodeMap.setNoDuplicateInsertPlan();
	}

	void unpackFile(const String& file) {
		TreeFile treeFile(this);
		treeFile.read(file);
	}

	void addRecord(const String& path, TreeFileRecord* record) {
		try {
			int pos = path.lastIndexOf("/");

			String dir = path.subString(0, pos);
			String fileName = path.subString(pos+1, path.length());

			record->setRecordName(fileName);

			if (nodeMap.contains(dir)) {
				TreeDirectory* records = &nodeMap.get(dir);
				records->put(record);
			} else {
				TreeDirectory records;
				records.put(record);

				nodeMap.put(dir, records);
			}
		} catch (Exception& e) {
			error("Invalid path: " + path);
		}
	}

	TreeDirectory* getTreeDirectory(const String& path) {
		return &nodeMap.get(path);
	}

	/**
	 * Gets a byte buffer from the specified path.
	 * Don't forget to delete the pointer when finished.
	 */
	byte* getBytes(const String& recordPath, int& size) {
		int pos = recordPath.lastIndexOf("/");

		//Only folders are allowed at the root level of TRE directories.
		if (pos == -1)
			return NULL;

		String dir = recordPath.subString(0, pos);
		String fileName = recordPath.subString(pos+1, recordPath.length());

		TreeDirectory* treeDir = &nodeMap.get(dir);
		int idx = treeDir->find(fileName);

		if (idx == -1) {
			error("Did not find fileName: " + fileName);
			return NULL;
		}

		Reference<TreeFileRecord*> record = treeDir->get(idx);
		size = record->getUncompressedSize();
		return record->getBytes();
	}


	TreeDirectory* getDirectory(const String& path) {
		if (!nodeMap.contains(path))
			return NULL;

		return &nodeMap.get(path);
	}
};


#endif /* TREEARCHIVE_H_ */
