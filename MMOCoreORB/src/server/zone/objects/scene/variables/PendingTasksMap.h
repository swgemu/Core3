/*
 * PendingTasksMap.h
 *
 *  Created on: 04/05/2010
 *      Author: victor
 */

#ifndef PENDINGTASKSMAP_H_
#define PENDINGTASKSMAP_H_

#include "engine/engine.h"

#include "system/util/SynchronizedVectorMap.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
class SceneObject;
}
}
}
}


class PendingTasksMap : public Object {
protected:
	Mutex mutex;

	VectorMap<String, Reference<Task*> > taskMap;

	ArrayList<Reference<Task*> > orderedTasks;

public:
	PendingTasksMap();

	PendingTasksMap(const PendingTasksMap& p);

	void put(const String& name, Task* task);

	void drop(const String& name);

	bool contains(const String& name);

	Reference<Task*> get(const String& name);

	void putOrdered(Task* task, server::zone::objects::scene::SceneObject* sceneObject);

	int getOrderedTasksSize();

	bool runMoreOrderedTasks(server::zone::objects::scene::SceneObject* sceneObject);

	Reference<Task*> getNextOrderedTask();
};


#define EXECUTE_ORDERED_TASK_1(SceneObject, Param1, Code) \
        { \
        class Param1##Param1 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
        public: \
                Param1##Param1(param1_type param1) : Param1##_p(param1) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Task* task = new Param1##Param1(Param1); \
        SceneObject->executeOrderedTask(task); \
        }


#define EXECUTE_ORDERED_TASK_2(SceneObject, Param1, Param2, Code) \
        { \
        class Param1##Param2 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param2) param2_type; \
				param2_type Param2##_p; \
        public: \
                Param1##Param2(param1_type param1, param2_type param2) : Param1##_p(param1), Param2##_p(param2) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Task* task = new Param1##Param2(Param1, Param2); \
        SceneObject->executeOrderedTask(task); \
        }


#define EXECUTE_ORDERED_TASK_3(SceneObject, Param1, Param2, Param3, Code) \
        { \
        class Param1##Param2##Param3 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param2) param2_type; \
                param2_type Param2##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param3) param3_type; \
				param3_type Param3##_p; \
        public: \
                Param1##Param2##Param3(param1_type param1, param2_type param2, param3_type param3) : Param1##_p(param1), Param2##_p(param2), Param3##_p(param3) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Task* task = new Param1##Param2##Param3(Param1, Param2, Param3); \
        SceneObject->executeOrderedTask(task); \
        }


#define EXECUTE_ORDERED_TASK_4(SceneObject, Param1, Param2, Param3, Param4, Code) \
        { \
        class Param1##Param2##Param3##Param4 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param2) param2_type; \
                param2_type Param2##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param3) param3_type; \
                param3_type Param3##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param4) param4_type; \
				param4_type Param4##_p; \
        public: \
                Param1##Param2##Param3##Param4(param1_type param1, param2_type param2, param3_type param3, param4_type param4) : Param1##_p(param1), Param2##_p(param2), Param3##_p(param3), Param4##_p(param4) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Task* task = new Param1##Param2##Param3##Param4(Param1, Param2, Param3, Param4); \
        SceneObject->executeOrderedTask(task); \
        }

#define EXECUTE_ORDERED_TASK_5(SceneObject, Param1, Param2, Param3, Param4, Param5, Code) \
        { \
        class Param1##Param2##Param3##Param4##Param5 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param2) param2_type; \
                param2_type Param2##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param3) param3_type; \
                param3_type Param3##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param4) param4_type; \
				param4_type Param4##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param5) param5_type; \
                param5_type Param5##_p; \
		\
        public: \
                Param1##Param2##Param3##Param4##Param5(param1_type param1, param2_type param2, param3_type param3, param4_type param4, param5_type param5) : Param1##_p(param1), Param2##_p(param2), Param3##_p(param3), Param4##_p(param4), Param5##_p(param5) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Task* task = new Param1##Param2##Param3##Param4##Param5(Param1, Param2, Param3, Param4, Param5); \
        SceneObject->executeOrderedTask(task); \
        }

#define EXECUTE_ORDERED_TASK_6(SceneObject, Param1, Param2, Param3, Param4, Param5, Param6, Code) \
        { \
        class Param1##Param2##Param3##Param4##Param5##Param6 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param2) param2_type; \
                param2_type Param2##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param3) param3_type; \
                param3_type Param3##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param4) param4_type; \
				param4_type Param4##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param5) param5_type; \
                param5_type Param5##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param6) param6_type; \
                param6_type Param6##_p; \
		\
        public: \
                Param1##Param2##Param3##Param4##Param5##Param6(param1_type param1, param2_type param2, param3_type param3, param4_type param4, param5_type param5, param6_type param6) : Param1##_p(param1), Param2##_p(param2), Param3##_p(param3), Param4##_p(param4), Param5##_p(param5), Param6##_p(param6) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Task* task = new Param1##Param2##Param3##Param4##Param5##Param6(Param1, Param2, Param3, Param4, Param5, Param6); \
        SceneObject->executeOrderedTask(task); \
        }



#endif /* PENDINGTASKSMAP_H_ */
