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

	byte* getBytes(const String& recordPath, int& size) {
		int pos = recordPath.lastIndexOf("/");
		String dir = recordPath.subString(0, pos);
		String fileName = recordPath.subString(pos+1, recordPath.length());

		TreeDirectory* treeDir = &nodeMap.get(dir);

		if (treeDir == NULL) {
			error("Path does not exist.");
			return NULL;
		}

		int idx = treeDir->find(fileName);

		if (idx == -1) {
			error("Did not find fileName: " + fileName);
			return NULL;
		}

		Reference<TreeFileRecord*> record = treeDir->get(idx);
		size = record->getUncompressedSize();

		return record->getBytes();
	}

	void printNodesByPath(const String& path) {
		TreeDirectory* records = &nodeMap.get(path);

		if (records == NULL) {
			error("No files at specified path.");
			return;
		}

		for (int i = 0; i < records->size(); ++i) {
			Reference<TreeFileRecord*> record = records->elementAt(i);

			String recordName = record->getRecordName();

			if (recordName.indexOf(".trn") != -1)
				info(recordName);
		}
	}
};


#endif /* TREEARCHIVE_H_ */
