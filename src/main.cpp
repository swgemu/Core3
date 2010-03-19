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

#include "system/lang/SignalException.h"

#include "server/ServerCore.h"

#include "server/zone/managers/planet/HeightMap.h"

class TestClassReference;

class TestClass : public TransactionalObject {
	int value;

	long value2;

	TestClass* otherValue;

public:
	TestClass(int val) {
		value = val;
		value2 = 4;
		otherValue = NULL;
	}

	int getValue2() {
		return value2;
	}

	void setValue2(int val) {
		value2 = val;
	}

	int size() {
		return sizeof(TestClass);
	}

	static Vector<TestClassReference*> references;
};

Vector<TestClassReference*> TestClass::references;

class TestClassReference {
	TransactionalObjectHeader<TestClass>* header;

public:
	TestClassReference() {
		header = NULL;
	}

	TestClassReference(const TestClassReference& ref) {
		header = ref.header;
	}

	TestClassReference(TestClass* object) {
		header = new TransactionalObjectHeader<TestClass>(object);
	}

	void operator=(TestClass* object) {
		header = new TransactionalObjectHeader<TestClass>(object);
	}

	TestClass* get() {
		return (TestClass*) header->get();
	}

	TestClass* getForUpdate() {
		return (TestClass*) header->getForUpdate();
	}
};

class TestTask : public Thread {
	int taskID;

public:
	TestTask(int id) {
		taskID = id;
	}

	void run() {
		uint64 starttime, endtime;
		int attempts = 0;

		while (true) {
			starttime = System::getMikroTime();

			testMethod();

			endtime = System::getMikroTime();

			//System::out.println("Transaction " + String::valueOf(taskID) + " time: " + Long::toString(endtime - starttime) + " usec");

			starttime = System::getMikroTime();

			engine::stm::Transaction* transaction =
					engine::stm::Transaction::currentTransaction();

			if (transaction->commit())
				break;
			else
				++attempts;

			System::out.println("Transaction " + String::valueOf(taskID) + " aborted");

			transaction->reset();
		}

		endtime = System::getMikroTime();
		System::out.println("Transaction " + String::valueOf(taskID) + " commited: " + Long::toString(endtime - starttime) + " usec in "
				+ String::valueOf(attempts) + " attempts");
	}

	void testMethod() {
		for (int i = 0; i < TestClass::references.size(); ++i) {
			TestClassReference* reference = TestClass::references.get(i);

			if (System::random(10) == 0)
				Thread::sleep(1);

			TestClass* object = NULL;

			if (System::random(10) < 6) {
				object = reference->getForUpdate();
				object->setValue2(i);
			} else {
				object = reference->get();
				object->getValue2();
			}

			int size = object->size();
			if (size != sizeof(TestClass))
				System::out.println("CONSISTENCY ERROR");
		}
	}
};

int main(int argc, char* argv[]) {
	/*for (int i = 0; i < 100; ++i) {
		TestClass* object = new TestClass(i);
		TestClassReference* reference = new TestClassReference(object);

		TestClass::references.add(reference);
	}

	Vector<Thread*> threads;

	for (int i = 0; i < 25; ++i) {
		Thread* thread = new TestTask(i + 1);
		threads.add(thread);
	}

	for (int i = 0; i < threads.size(); ++i) {
		Thread* thread = threads.get(i);

		thread->start();
	}

	for (int i = 0; i < threads.size(); ++i) {
		Thread* thread = threads.get(i);

		thread->join();
	}

	return 0;*/

	try {
		Vector<String> arguments;
		for (int i = 1; i < argc; ++i) {
			arguments.add(argv[i]);
		}

		ServerCore core;

		core.init();

		core.run();
	} catch (Exception& e) {
		System::out << e.getMessage() << "\n";
		e.printStackTrace();
	} catch (...) {
		System::out << "unreported exception caught main()\n";
	}


	return 0;
}

