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
	}

	/**
	 * Gets a byte buffer from the specified path.
	 * Don't forget to delete the pointer when finished.
	 */
	byte* getBytes(const String& recordPath, int& size) {
		int pos = recordPath.lastIndexOf("/");
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

	/**
	 * Prints a list of all the files at this path based on the filter passed.
	 * @param path The path at which to search.
	 * @param filter The filter, which accepts wildcards in the form of *. Default is *.
	 */
	void printNodesByPath(const String& path, const String& filter) {
		TreeDirectory* records = &nodeMap.get(path);

		for (int i = 0; i < records->size(); ++i) {
			Reference<TreeFileRecord*> record = records->elementAt(i);

			String recordName = record->getRecordName();
			info(recordName); //TODO: Filter matching.
		}
	}
};


#endif /* TREEARCHIVE_H_ */
