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

#include "server/ServerCore.h"

#include "server/zone/objects/scene/SceneObject.h"

class TestClass : public Object {
	int values[1000];

public:
	TestClass(int value) {
		for (int i = 0; i < 1000; ++i)
			values[i] = value;
	}

	TestClass(TestClass& obj) {
		for (int i = 0; i < 1000; ++i)
			values[i] = obj.values[i];
	}

	void increment() {
		for (int i = 0; i < 1000; ++i)
			values[i] += 1;
	}

	int get() {
		int value = values[0];

		for (int i = 0; i < 1000; ++i) {
			if (values[i] != value)
				assert(0 && "inconsistency in object");
		}

		return value;
	}

	Object* clone() {
		return new TestClass(*this);
	}
};

class TestTask : public Task {
	TransactionalObjectHeader<TestClass*>* reference1;
	TransactionalObjectHeader<TestClass*>* reference2;

public:
	TestTask(TransactionalObjectHeader<TestClass*>* ref1, TransactionalObjectHeader<TestClass*>* ref2) {
		reference1 = ref1;
		reference2 = ref2;
	}

	void run() {
		TestClass* object1 = reference1->getForUpdate();
		TestClass* object2 = reference2->getForUpdate();

		object1->increment();
		object2->increment();
	}
};

void testTransactions() {
	TransactionalObjectHeader<TestClass*> reference1;
	TransactionalObjectHeader<TestClass*> reference2;

	reference1 = new TestClass(1);
	reference2 = new TestClass(2);

	Core::commitTask();

	for (int i = 0; i < 100000; ++i) {
		Task* task = new TestTask(&reference1, &reference2);

		//Core::getTaskManager()->scheduleTask(task, 1000);
		Core::getTaskManager()->executeTask(task);
	}

	Core::commitTask();

	while(Core::getTaskManager()->getExecutingTaskSize() != 0) {
		Thread::sleep(1000);
	}

	Thread::sleep(1000);

	TestClass* object1 = reference1.get();
	TestClass* object2 = reference2.get();

	printf("%i\n", object1->get());
	printf("%i\n", object2->get());
}

int main(int argc, char* argv[]) {
	try {
		Vector<String> arguments;
		for (int i = 1; i < argc; ++i) {
			arguments.add(argv[i]);
		}

		ServerCore core;

		core.init();

		core.run();

		//testTransactions();
	} catch (Exception& e) {
		System::out << e.getMessage() << "\n";
		e.printStackTrace();
	} catch (...) {
		System::out << "unreported exception caught main()\n";
	}

	return 0;
}

