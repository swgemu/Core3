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

#include "engine/engine.h"

class TestClass : public Object {
	static const int ELEMENT_COUNT = 100;

	int values[ELEMENT_COUNT];

public:
	TestClass(int value) {
		for (int i = 0; i < ELEMENT_COUNT; ++i)
			values[i] = value;
	}

	TestClass(TestClass& obj) : Object() {
		for (int i = 0; i < ELEMENT_COUNT; ++i)
			values[i] = obj.values[i];
	}

	void increment() {
		for (int i = 0; i < ELEMENT_COUNT; ++i)
			values[i] += 1;
	}

	int get() {
		int value = values[0];

		for (int i = 0; i < ELEMENT_COUNT; ++i) {
			if (values[i] != value)
				assert(0 && "inconsistency in object");
		}

		return value;
	}

	int getz() {
		int value = values[0];

		return value;
	}

	Object* clone() {
		return new TestClass(*this);
	}
};

class TestTask : public Task {
	Vector<TransactionalReference<TestClass*> >* references;

public:
	TestTask(Vector<TransactionalReference<TestClass*> >* refs) {
		references = refs;
	}

	void run() {
		//Task* task = new TestTask(references);

		for (int i = 0; i < 25; ++i) {
			TestClass* object = references->get(System::random(references->size() - 1)).getForUpdate();

			/*char str[80];
			sprintf(str, "values %i\n", object->getz());

			Transaction::currentTransaction()->log(str);*/

			object->increment();
		}
	}
};

void testTransactions() {
	Vector<TransactionalReference<TestClass*> > references;

	printf("creating objects\n");

	for (int i = 0; i < 10000; ++i)
		references.add(new TestClass(1));

	printf("adding tasks\n");

	for (int i = 0; i < 10000; ++i) {
		Task* task = new TestTask(&references);

		//Core::getTaskManager()->scheduleTask(task, 1000);
		Core::getTaskManager()->executeTask(task);
	}

	TransactionalMemoryManager::commitPureTransaction();

	printf("starting tasks\n");

	Thread::sleep(3000);

	while(true) {
		Thread::sleep(1000);

		int scheduledTasks = Core::getTaskManager()->getScheduledTaskSize();
		int executedTasks = Core::getTaskManager()->getExecutingTaskSize();

		int taskToSchedule = 500;
		int taskToExecute = 1000;

		if (scheduledTasks > 20000)
			taskToSchedule = 0;
		else if (scheduledTasks < 1000)
			taskToSchedule = 5000;

		if (executedTasks > 20000)
			taskToExecute = 0;
		else if (executedTasks < 1000)
			taskToExecute = 5000;

		for (int i = 0; i < taskToSchedule; ++i) {
			Task* task = new TestTask(&references);

			Core::getTaskManager()->scheduleTask(task, System::random(2000));
		}

		for (int i = 0; i < taskToExecute; ++i) {
			Task* task = new TestTask(&references);

			Core::getTaskManager()->executeTask(task);
		}

		TransactionalMemoryManager::commitPureTransaction();
	}

	for (int i = 0; i < references.size(); ++i) {
		TestClass* object = references.get(i);

		printf("%i\n", object->get());
	}

	TransactionalMemoryManager::commitPureTransaction();

	Thread::sleep(1000);

	exit(0);
}
