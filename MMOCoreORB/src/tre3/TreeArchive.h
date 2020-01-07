/*
 * TreeArchive.h
 *
 *  Created on: Apr 7, 2011
 *      Author: crush
 */

#ifndef TREEARCHIVE_H_
#define TREEARCHIVE_H_

#include "TreeFile.h"
#include "TreeDirectory.h"

class TreeArchive : public Logger {
	HashTable<String, Reference<TreeDirectory*> > nodeMap;

public:
	TreeArchive() {
		setLoggingName("TreeArchive");
		setLogging(false);

		nodeMap.setNullValue(nullptr);

		//nodeMap.setNoDuplicateInsertPlan();
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

			auto entry = nodeMap.getEntry(dir);

			if (entry != nullptr) {
				auto& records = entry->getValue();
				records->put(record);
			} else {
				Reference<TreeDirectory*> records = new TreeDirectory();
				records->put(record);

				nodeMap.put(std::move(dir), std::move(records));
			}
		} catch (const Exception& e) {
			error("Invalid path: " + path);
		}
	}

	const TreeDirectory* getTreeDirectory(const String& path) const {
		return nodeMap.get(path);
	}

	/**
	 * Gets a byte buffer from the specified path.
	 * Don't forget to delete the pointer when finished.
	 */
	byte* getBytes(const String& recordPath, int& size) const {
		int pos = recordPath.lastIndexOf("/");

		//Only folders are allowed at the root level of TRE directories.
		if (pos == -1)
			return nullptr;

		String dir = recordPath.subString(0, pos);
		String fileName = recordPath.subString(pos + 1, recordPath.length());

		const TreeDirectory* treeDir = nodeMap.get(dir).get();

		size = 0;

		if (treeDir == nullptr)
			return nullptr;

		int idx = treeDir->find(fileName);

		if (idx == -1) {
			warning() << recordPath << " not found.";
			return nullptr;
		}

		const Reference<TreeFileRecord*>& record = treeDir->get(idx);
		size = record->getUncompressedSize();

		return record->getBytes();
	}

	const TreeDirectory* getDirectory(const String& path) const {
		return nodeMap.get(path);
	}

	Vector<String>* getFilesAndSubDirectoryFiles(const String& directory) const {
		HashTableIterator<String, Reference<TreeDirectory*> > iterator = nodeMap.iterator();
		Vector<String>* files = nullptr;

		while (iterator.hasNext()) {
			//String directoryName = iterator.getNextKey();
			String* directoryName;
			Reference<TreeDirectory*>* directoryEntry;
			iterator.getNextKeyAndValue(directoryName, directoryEntry);

			if (directoryName->contains(directory)) {
				if (files == nullptr)
					files = new Vector<String>();

				for (int i = 0; i < directoryEntry->get()->size(); ++i) {
					const TreeFileRecord* fileRecord = directoryEntry->get()->get(i);

					files->add(*directoryName + "/" + fileRecord->getRecordName());
				}
			}
		}

		return files;
	}
};

#endif /* TREEARCHIVE_H_ */
