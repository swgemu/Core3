/*
 * DataArchiveStore.cpp
 *
 *  Created on: 06/09/2013
 *      Author: victor
 */

#include "DataArchiveStore.h"
#include "tre3/TreeArchive.h"

DataArchiveStore::DataArchiveStore() : Logger("DataArchiveStore") {
	treeDirectory = nullptr;
}

DataArchiveStore::~DataArchiveStore() {
	delete treeDirectory;
	treeDirectory = nullptr;
}

byte* DataArchiveStore::getData(const String& path, int& size) const {
	//read from local dir else from tres
	File file(path);
	byte* data = nullptr;
	size = 0;

	try {
		FileReader test(&file);

		if (file.exists()) {
			size = file.size();
			data = new byte[size];

			test.read((char*)data, size);
			test.close();

			return data;
		}
	} catch (const Exception& e) {
	}

	ReadLocker locker(this);

	if (treeDirectory == nullptr)
		return nullptr;

	data = treeDirectory->getBytes(path, size);

	if (size == 0) {
		delete [] data;
		return nullptr;
	}

	return data;
}

int DataArchiveStore::loadTres(const String& path, const Vector<String>& treFilesToLoad) {
	Locker locker(this);

	if (treeDirectory != nullptr) {
		//error("tree directory already loaded");

		return 0;
	}

	if (path.length() <= 1)
		return 2;

	if (treFilesToLoad.size() == 0)
		return 3;

	debug("Loading TRE archives...");

	treeDirectory = new TreeArchive();

	int j = 0;


	for (int i = 0; i < treFilesToLoad.size(); ++i) {
		const String& file = treFilesToLoad.get(i);
		String fullPath = path + "/" + file;

		treeDirectory->unpackFile(fullPath);
	}

	debug("Finished loading TRE archives.");

	return 0;
}

IffStream* DataArchiveStore::openIffFile(const String& fileName) const {
	if (fileName.isEmpty())
		return nullptr;

	debug() << "requesting iff file: " << fileName;

	IffStream* iffStream = nullptr;

	int size = 0;

	byte* data = getData(fileName, size);

	if (size == 0) {
		E3_ASSERT(!data);
		return nullptr;
	}

	iffStream = new IffStream();

	if (iffStream != nullptr) {
		try {
			if (!iffStream->parseChunks(data, size, fileName)) {
				delete iffStream;
				iffStream = nullptr;
			}
		} catch (const Exception& e) {
			delete iffStream;
			iffStream = nullptr;

			error() << "could not parse into iffStream " << fileName << "  " << e.getMessage();
		}
	}

	delete [] data;

	return iffStream;
}

