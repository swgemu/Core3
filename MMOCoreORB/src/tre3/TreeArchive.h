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
	HashTable<String, Reference<TreeDirectory*> > nodeMap;

public:
	TreeArchive() {
		setLoggingName("TreeArchive");
		setLogging(true);

		nodeMap.setNullValue(NULL);

		//nodeMap.setNoDuplicateInsertPlan();
	}

	void unpackFile(const String& file) {
		TreeFile* treeFile = new TreeFile(this);
		treeFile->read(file);
		delete treeFile;
	}

	void addRecord(const String& path, TreeFileRecord* record) {
		try {
			int pos = path.lastIndexOf("/");

			String dir = path.subString(0, pos);
			String fileName = path.subString(pos+1, path.length());

			record->setRecordName(fileName);

			if (nodeMap.containsKey(dir)) {
				Reference<TreeDirectory*> records = nodeMap.get(dir);
				records->put(record);
			} else {
				Reference<TreeDirectory*> records = new TreeDirectory();
				records->put(record);

				nodeMap.put(dir, records);
			}
		} catch (Exception& e) {
			error("Invalid path: " + path);
		}
	}

	TreeDirectory* getTreeDirectory(const String& path) {
		return nodeMap.get(path);
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

		TreeDirectory* treeDir = nodeMap.get(dir);
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
		return nodeMap.get(path);
	}

	Vector<String>* getFilesAndSubDirectoryFiles(const String& directory) {
		HashTableIterator<String, Reference<TreeDirectory*> > iterator = nodeMap.iterator();
		Vector<String>* files = NULL;

		while (iterator.hasNext()) {
			//String directoryName = iterator.getNextKey();
			String directoryName;
			Reference<TreeDirectory*> directoryEntry;
			iterator.getNextKeyAndValue(directoryName, directoryEntry);

			if (directoryName.contains(directory)) {
				if (files == NULL)
					files = new Vector<String>();

				for (int i = 0; i < directoryEntry->size(); ++i) {
					TreeFileRecord* fileRecord = directoryEntry->get(i);

					files->add(directoryName + "/" + fileRecord->getRecordName());
				}
			}
		}

		return files;
	}
};


#endif /* TREEARCHIVE_H_ */
