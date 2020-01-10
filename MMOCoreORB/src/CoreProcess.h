/**
 * @author      : theanswer (theanswer@hyperv)
 * @file        : CoreProcess
 * @created     : Wednesday Nov 27, 2019 10:43:44 UTC
 */

#ifndef C3COREPROCESS_H
#define C3COREPROCESS_H

#include "engine/engine.h"

#ifndef PLATFORM_WIN

#include "system/thread/ChildProcess.h"

#include "server/ServerCore.h"

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

#endif

#endif /* end of include guard COREPROCESS_H */

