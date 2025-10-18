/*
 * LoginAccountAction.cpp
 *
 * Authenticates to login server and retrieves character list
 */

#include "client/ActionBase.h"
#include "client/ActionResult.h"
#include "client/ActionManager.h"
#include "client/ClientCore.h"
#include "client/login/LoginSession.h"

class LoginAccountAction : public ActionBase {
	LoginAccountResult result;
	bool skipped;

public:
	LoginAccountAction() : skipped(false) {
		setLogLevel(Logger::INFO);
		setLoggingName("LoginAccount");
	}

	const char* getName() const override {
		return "loginAccount";
	}

	void parseJSON(const JSONSerializationType& config) override {
		// JSON can override username/password if needed
		// For Phase 1, we just use ClientCoreOptions
	}

	bool needsZone() const override {
		return false;  // Login-phase action
	}

	void run(ClientCore& core) override {
		String username = String(core.options.config["username"].get<std::string>().c_str());
		String password = String(core.options.config["password"].get<std::string>().c_str());

		info() << "Authenticating account: " << username;

		// Create and run login session
		core.loginSession = new LoginSession(username, password);
		core.loginSession->run();

		// Check if authentication succeeded
		if (!core.loginSession->isLoggedIn()) {
			result.setError(
				core.loginSession->getLastError().isEmpty()
					? "Login failed - no account ID received"
					: core.loginSession->getLastError(),
				core.loginSession->getLastErrorCode() != 0
					? core.loginSession->getLastErrorCode()
					: 2
			);
			return;
		}

		// Success - store account info in result
		result.setSuccess();
		result.setAccountInfo(
			core.loginSession->getAccountID(),
			core.loginSession->getSessionID(),
			core.loginSession->getCharacterListSize()
		);

		info() << "Authentication successful - Account ID: " << result.getAccountId()
		       << ", Characters: " << result.getNumCharacters();
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
			json["accountId"] = result.getAccountId();
			json["sessionId"] = result.getSessionId().toCharArray();
			json["charactersFound"] = result.getNumCharacters();
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
		return new LoginAccountAction();
	}
};

// Static registration (runs before main())
static bool _registered_loginAccount =
	(ActionManager::registerAction("loginAccount", LoginAccountAction::factory), true);
