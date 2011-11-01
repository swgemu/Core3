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

#include "TestClass.h"

#include <stdlib.h>

class MemoryPool {
	static const int POOL_SIZE = 50;

	void* addresses[POOL_SIZE];
public:
	MemoryPool() {
		memset(addresses, NULL, sizeof(void*) * POOL_SIZE);
	}

	bool add(void* mem) {
		for (int i = 0; i < POOL_SIZE; ++i) {
			if (addresses[i] == 0) {
				//printf("adding %p to %i slot\n", mem, i);
				addresses[i] = mem;
				return true;
			}
		}

		return false;
	}

	void* get() {
		int pos = System::random(POOL_SIZE - 1);
		for (int i = pos; i < POOL_SIZE; ++i) {
			void* mem = addresses[i];

			if (mem != NULL) {
				addresses[i] = NULL;

				//printf("got %p from %i slot\n", mem, i);

				return mem;
			}
		}

		for (int i = pos; i >= 0; --i) {
			void* mem = addresses[i];

			if (mem != NULL) {
				addresses[i] = NULL;

				//printf("got %p from %i slot\n", mem, i);

				return mem;
			}
		}

		return NULL;
	}
};

class TestThread : public Thread {
	int threadID;

public:
	TestThread(int id) {
		threadID = id;
	}

	void run() {
		MemoryPool memPool;

		for (int i = 0; i < 10000000; ++i) {
			int addressestoManipulate = System::random(10);

			void* mem = NULL;
			int size;

			for (int j = 0; j < addressestoManipulate; ++j) {
				switch (System::random(2)) {
				case 0:
					mem = memPool.get();
					if (mem != NULL) {
						printf("[thread %i] freed %p\n", threadID, mem);

						free(mem);
					}

					break;
				default:
					size = System::random(1000);
					mem = malloc(size);
					memset(mem, 0, size);

					if (!memPool.add(mem))
						free(mem);
					else
						printf("[thread %i] allocated %p %i\n", threadID, mem, size);

					break;
				}
			}

			Thread::yield();
		}
	}
};

void testSTMMemory() {
	Thread* thread1 = new TestThread(1);
	Thread* thread2 = new TestThread(2);
	Thread* thread3 = new TestThread(3);
	Thread* thread4 = new TestThread(4);

	thread1->start();
	thread2->start();
	/*thread3->start();
	thread4->start();*/

	thread1->join();
	thread2->join();
	/*thread3->join();
	thread4->join();*/

	return;

#ifdef WITH_STM
	TransactionalReference<TestClass*> object = new TestClass(1);

	TransactionalMemoryManager::commitPureTransaction();

	object = NULL;

	TransactionalMemoryManager::commitPureTransaction();
	TransactionalMemoryManager::commitPureTransaction();

	Thread::sleep(1000);
#endif

	exit(0);
}
