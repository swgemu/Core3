/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "system/thread/ChildProcess.h"

#include "server/ServerCore.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/collision/NavMeshManager.h"

#ifdef COMPILE_CORE3_TESTS
#include "tests/TestCore.h"

#include "gtest/gtest.h"
#endif

#include "engine/orb/db/DOBObjectManager.h"

class CoreProcess : public ChildProcess {
	const SortedVector<String>& arguments;

public:
	CoreProcess(const SortedVector<String>& args) : arguments(args) {
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

	if (argc) {
		StackTrace::setBinaryName(argv[0]);
	} else {
		Logger::console.warning("empty argv list");
	}

	static int ret = 0;

	try {
		SortedVector<String> arguments;
		arguments.setNoDuplicateInsertPlan();

		for (int i = 1; i < argc; ++i) {
			arguments.put(argv[i]);
		}

		if (arguments.contains("testScreenPlays")) {
			DirectorManager::DEBUG_MODE = 1;

			ConfigManager::instance()->loadConfigData();

			DirectorManager::instance()->info("Testing screen plays...", true);

			auto elapsed = Timer().run([]() { DirectorManager::instance()->getLuaInstance(); });

			DirectorManager::instance()->info(true) << "Done in " << elapsed / 1000000 << "ms";
		} else if (arguments.contains("service")) {
			while (true) {
				CoreProcess core(arguments);
				core.start();

				core.wait();
			}
#ifdef COMPILE_CORE3_TESTS
		} else if (arguments.contains("runUnitTests")) {
			TestCore core;
			core.info("Running unit tests...", true);

			testing::InitGoogleTest(&argc, argv);

			ret = RUN_ALL_TESTS();
#endif
		} else if (arguments.contains("dumpNavMeshesToFile")) {
			NavMeshManager::instance()->info("Dumping nav meshes to files...", true);

			NavMeshManager::instance()->dumpMeshesToFiles();
		} else {
			bool truncateData = arguments.contains("clean");

			ServerCore core(truncateData, arguments);
			core.start();
		}

	} catch (const Exception& e) {
		e.printStackTrace();
	} catch (...) {
		System::out << "unreported exception caught main()" << endl;
	}

	pthread_exit(&ret);

	return 0;
}

