/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef PLATFORM_WIN
#include "CoreProcess.h"
#endif

#include "server/ServerCore.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/collision/NavMeshManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/object/ObjectManager.h"

#ifdef COMPILE_CORE3_TESTS
#include "tests/TestCore.h"

#include "gtest/gtest.h"
#endif

#include "engine/orb/db/DOBObjectManager.h"

int main(int argc, char* argv[]) {
	System::setStreamBuffer(stdout, nullptr);

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
#ifndef PLATFORM_WIN
			while (true) {
				CoreProcess core(arguments);
				core.start();

				core.wait();
			}
#endif
#ifdef COMPILE_CORE3_TESTS
		} else if (arguments.contains("runUnitTests")) {
			TestCore core;
			core.info("Running unit tests...", true);

			testing::InitGoogleTest(&argc, argv);

			ret = RUN_ALL_TESTS();

			ObjectManager::instance()->shutdown();
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
		System::err << "unreported exception caught main()" << endl;
	}

	pthread_exit(&ret);

	return 0;
}

