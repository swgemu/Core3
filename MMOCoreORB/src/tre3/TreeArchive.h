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

class TreeArchive : public Logger {
	VectorMap<String, SortedVector<Reference<TreeFileRecord*> > > nodeMap;

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
			SortedVector<Reference<TreeFileRecord*> >* records = &nodeMap.get(dir);
			records->put(record);
		} else {
			SortedVector<Reference<TreeFileRecord*> > records;
			records.setNoDuplicateInsertPlan();
			records.put(record);

			nodeMap.put(dir, records);
		}
	}

	void printNodesByPath(const String& path) {
		SortedVector<Reference<TreeFileRecord*> >* records = &nodeMap.get(path);

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
