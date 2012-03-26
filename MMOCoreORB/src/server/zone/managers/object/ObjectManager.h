/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "engine/engine.h"

#include "ObjectMap.h"

#include "server/zone/ZoneProcessServer.h"

#include "server/zone/objects/scene/SceneObject.h"

#include "SceneObjectFactory.h"

class TemplateManager;
class UpdateModifiedObjectsThread;

namespace engine {
namespace db {
namespace berkley {
	class Transaction;
}
}
}

namespace server {
namespace zone {

	namespace managers {
	namespace object {

	class ObjectManager : public DOBObjectManager, public Logger, public Singleton<ObjectManager>, public Object {
		ManagedReference<ZoneProcessServer*> server;

		ObjectDatabaseManager* databaseManager;

		TemplateManager* templateManager;

		Reference<Task*> updateModifiedObjectsTask;

		Vector<UpdateModifiedObjectsThread*> updateModifiedObjectsThreads;

		bool objectUpdateInProcess;

		AtomicInteger totalUpdatedObjects;

	public:
		SceneObjectFactory<SceneObject* (), uint32> objectFactory;

		const static int UPDATETODATABASETIME = 300000;
		const static int INITIALUPDATEMODIFIEDOBJECTSTHREADS = 10;
		const static int MAXOBJECTSTOUPDATEPERTHREAD = 7000;

	private:
		/**
		 * Loads the highest object id without the highest 16 bits that specify the table.
		 */
		void loadLastUsedObjectID();

		void registerObjectTypes();
		SceneObject* loadObjectFromTemplate(uint32 objectCRC);
		void deSerializeObject(ManagedObject* object, ObjectInputStream* data);

		SceneObject* instantiateSceneObject(uint32 objectCRC, uint64 oid, bool createComponents);

		UpdateModifiedObjectsThread* createUpdateModifiedObjectsThread();

		int deployUpdateThreads(Vector<DistributedObject*>* objectsToUpdate, Vector<DistributedObject*>* objectsToDelete, engine::db::berkley::Transaction* transaction);

		//ManagedObject* cloneManagedObject(ManagedObject* object, bool makeTransient = false);


	public:
		ObjectManager();
		~ObjectManager();

		bool contains(uint32 objectCRC) {
			return objectFactory.containsObject(objectCRC);
		}

		void loadStaticObjects();

		// object methods
		SceneObject* createObject(uint32 objectCRC, int persistenceLevel, const String& database, uint64 oid = 0);

		ManagedObject* createObject(const String& className, int persistenceLevel, const String& database, uint64 oid = 0, bool initializeTransientMembers = true);

		void createObjectID(const String& name, DistributedObjectStub* object);

		/**
		 * Returns a clone of the passed object with new object id
		 * if the passed object is persistent, the new object will be too
		 */
		SceneObject* cloneObject(SceneObject* object, bool makeTransient = false);

		/**
		 * Assigns a new persistent object id, stores in the specified database
		 */
		void persistObject(ManagedObject* object, int persistenceLevel, const String& database);

		void printInfo();
		String getInfo();

		DistributedObjectStub* loadPersistentObject(uint64 objectID);
		int updatePersistentObject(DistributedObject* object);
		int destroyObjectFromDatabase(uint64 objectID);

		uint64 getNextObjectID(const String& database);

		uint64 getNextFreeObjectID();

		ObjectDatabase* loadTable(const String& database, uint64 objectID = 0);
		ObjectDatabase* getTable(uint64 objectID);

		void updateModifiedObjectsToDatabase(bool startTask);
		void finishObjectUpdate(bool startNew);

		inline void scheduleUpdateToDatabase() {
			updateModifiedObjectsTask->schedule(UPDATETODATABASETIME);
		}

		void updateObjectVersion();

		//used internally
		int commitUpdatePersistentObjectToDB(DistributedObject* object);
		int commitDestroyObjectToDB(uint64 objectID);

		void cancelUpdateModifiedObjectsTask();

		inline void setZoneProcessor(ZoneProcessServer* srv) {
			server = srv;
		}



	};

}
}
}
}

using namespace server::zone::managers::object;

#endif /*OBJECTMANAGER_H_*/
