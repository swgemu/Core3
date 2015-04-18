/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "system/thread/ChildProcess.h"

#include "server/ServerCore.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/tests/TestCore.h"

#include "gtest/gtest.h"

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
		} else if (arguments.contains("runUnitTests")) {
			printf("Running unit tests...\n");
			TestCore core;

			testing::InitGoogleTest(&argc, argv);

			return RUN_ALL_TESTS();
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

	return 0;
}

