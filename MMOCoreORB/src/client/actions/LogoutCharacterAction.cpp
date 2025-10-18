/*
 * LogoutCharacterAction.cpp
 *
 * Cleanly logs out from zone server (cleanup action)
 */

#include "client/ActionBase.h"
#include "client/ActionResult.h"
#include "client/ActionManager.h"
#include "client/ClientCore.h"
#include "client/zone/Zone.h"

class LogoutCharacterAction : public ActionBase {
	// Result
	ActionResult result;
	bool skipped;

public:
	LogoutCharacterAction() :
		skipped(false) {
		setLogLevel(Logger::INFO);
		setLoggingName("LogoutCharacter");
	}

	const char* getName() const override {
		return "logoutCharacter";
	}

	void parseJSON(const JSONSerializationType& config) override {
		// No config needed
	}

	bool needsZone() const override {
		return true;  // Requires zone to logout from
	}

	bool needsCharacter() const override {
		return true;  // Must be zoned in as a character
	}

	void run(ClientCore& core) override {
		if (core.zone == nullptr || !core.zone->isStarted()) {
			// No zone connection, nothing to logout from
			result.setSuccess();
			return;
		}

		info() << "Logging out from zone...";

		// Disconnect from zone to stop receiving new packets
		core.zone->disconnect();

		// Wait for already-queued tasks to complete processing
		auto taskManager = Core::getTaskManager();
		int maxIterations = 20; // 20 x 50ms = 1 second max

		for (int i = 0; i < maxIterations; i++) {
			int executing = taskManager->getExecutingTaskSize();
			int scheduled = taskManager->getScheduledTaskSize();

			if (executing == 0 && scheduled == 0) {
				info() << "All tasks completed after " << (i * 50) << "ms";
				break;
			}

			Thread::sleep(50);
		}

		info() << "Processed " << core.zone->getZoneClient()->getPacketCount() << " total zone packets";

		result.setSuccess();
		info() << "Logout complete";
	}

	bool isOK() const override {
		return !skipped && result.isOK();
	}

	String getError() const override {
		return result.getError();
	}

	uint16 getErrorCode() const override {
		return result.getErrorCode();
	}

	void setSkipped() override {
		skipped = true;
	}

	JSONSerializationType toJSON() const override {
		JSONSerializationType json;
		json["action"] = getName();

		if (skipped) {
			json["status"] = "skipped";
		} else if (result.isOK()) {
			json["status"] = "ok";
		} else {
			json["status"] = "failed";
			json["error"] = result.getError().toCharArray();
			json["errorCode"] = result.getErrorCode();
		}

		return json;
	}

	String getHelpText() const override {
		return "";  // Auto-inserted, no user-facing options
	}

	// Factory function for static registration
	static ActionBase* factory() {
		return new LogoutCharacterAction();
	}
};

// Static registration (runs before main())
static bool _registered_logoutCharacter =
	(ActionManager::registerAction("logoutCharacter", LogoutCharacterAction::factory), true);
