/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include <pthread.h>
#include <stdio.h>
#include <algorithm>

#include "server/ServerCore.h"
#include "server/zone/managers/collision/NavMeshManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "system/io/PrintStream.h"
#include "system/lang/Exception.h"
#include "system/lang/String.h"
#include "system/lang/System.h"
#include "system/thread/ChildProcess.h"
#include "system/util/SortedVector.h"

#ifdef COMPILE_CORE3_TESTS
#include "gtest/gtest.h"
#include "tests/TestCore.h"
#endif

class CoreProcess : public ChildProcess {
	SortedVector<String>& arguments;

public:
	CoreProcess(SortedVector<String>& args) : arguments(args) {
	}

	void run() {
		bool truncateData = arguments.contains("clean");

		ServerCore core(truncateData, arguments);
		core.start();
	}

	void handleCrash() {
		//TODO: implement
	}

	bool isDeadlocked() {
		//TODO: implement
		return false;
	}

	void handleDeadlock() {
		//TODO: implement
	}
};

int main(int argc, char* argv[]) {
	setbuf(stdout, 0);

	static int ret = 0;

	try {
		SortedVector<String> arguments;
		for (int i = 1; i < argc; ++i) {
			arguments.put(argv[i]);
		}

		if (arguments.contains("testScreenPlays")) {
			printf("Testing screen plays...\n");

			DirectorManager::DEBUG_MODE = 1;
			DirectorManager::instance()->getLuaInstance();

			printf("Done\n");
		} else if (arguments.contains("service")) {
			while (true) {
				CoreProcess core(arguments);
				core.start();

				core.wait();
			}
#ifdef COMPILE_CORE3_TESTS
		} else if (arguments.contains("runUnitTests")) {
			printf("Running unit tests...\n");
			TestCore core;

			testing::InitGoogleTest(&argc, argv);

			ret = RUN_ALL_TESTS();
#endif
		} else if (arguments.contains("dumpNavMeshesToFile")) {
			printf("Dumping nav meshes to files...\n");

			NavMeshManager::instance()->dumpMeshesToFiles();
		} else {
			bool truncateData = arguments.contains("clean");

			ServerCore core(truncateData, arguments);
			core.start();
		}

	} catch (Exception& e) {
		System::out << e.getMessage() << "\n";
		e.printStackTrace();
	} catch (...) {
		System::out << "unreported exception caught main()\n";
	}

	pthread_exit(&ret);

	return 0;
}

