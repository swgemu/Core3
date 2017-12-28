/*
 * DataArchive.h
 *
 *  Created on: 06/09/2013
 *      Author: victor
 */

#ifndef DATAARCHIVESTORE_H_
#define DATAARCHIVESTORE_H_

#include "engine/log/Logger.h"
#include "engine/util/Singleton.h"
#include "engine/util/iffstream/IffStream.h"
#include "system/lang/Object.h"
#include "system/lang/String.h"
#include "system/platform.h"
#include "system/thread/Locker.h"
#include "system/thread/ReadLocker.h"
#include "system/thread/ReadWriteLock.h"
#include "system/util/Vector.h"

class TreeArchive;
namespace engine {
namespace util {
class IffStream;
}  // namespace util
}  // namespace engine

class DataArchiveStore : public Singleton<DataArchiveStore>, public Logger, public ReadWriteLock, public Object {
	TreeArchive* treeDirectory;

public:
	DataArchiveStore();

	~DataArchiveStore();

	byte* getData(const String& path, int& size);

	int loadTres(const String& path, const Vector<String>& treFilesToLoad);

	IffStream* openIffFile(const String& fileName);

	TreeArchive* getTreeArchive() {
		return treeDirectory;
	}


};


#endif /* DATAARCHIVE_H_ */
