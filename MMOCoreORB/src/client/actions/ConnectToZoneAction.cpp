/*
 * ConnectToZoneAction.cpp
 *
 * Transitions from login phase to zone phase
 * Cleans up login connection and establishes zone connection
 */

#include "client/ActionBase.h"
#include "client/ActionResult.h"
#include "client/ActionManager.h"
#include "client/ClientCore.h"
#include "client/login/LoginSession.h"
#include "client/zone/Zone.h"
#include "server/login/objects/CharacterListEntry.h"

class ConnectToZoneAction : public ActionBase {
	ConnectToZoneResult result;
	bool skipped;

public:
	ConnectToZoneAction() : skipped(false) {
		setLogLevel(Logger::INFO);
		setLoggingName("ConnectToZone");
	}

	const char* getName() const override {
		return "connectToZone";
	}


	void parseJSON(const JSONSerializationType& config) override {
		// No JSON configuration needed
	}

	bool needsZone() const override {
		return false;  // This action CREATES the zone connection
	}

	bool needsTarget() const override {
		return false;  // Target is optional - falls back to first galaxy
	}

	void run(ClientCore& core) override {
		// Validate prerequisites
		if (core.loginSession == nullptr || !core.loginSession->isLoggedIn()) {
			result.setError("No active login session", 1);
			return;
		}

		// Cleanup login connection
		if (core.loginSession->isConnected()) {
			info() << "Cleaning up login connection...";
			core.loginSession->cleanup();
		}

		// Get target galaxy (from selectContext or default to first)
		auto& galaxyMap = core.loginSession->getGalaxies();
		if (galaxyMap.size() == 0) {
			result.setError("No galaxies available", 2);
			return;
		}

		// Use targetGalaxyId if set, otherwise first galaxy
		Galaxy galaxy;
		bool found = false;

		if (core.targetGalaxyId != 0) {
			galaxy = core.loginSession->getGalaxy(core.targetGalaxyId);
			if (!galaxy.getAddress().isEmpty()) {
				found = true;
				info() << "Using target galaxy: " << galaxy.getName() << " (ID: " << core.targetGalaxyId << ")";
			} else {
				warning() << "Target galaxy " << core.targetGalaxyId << " not found, using first galaxy";
			}
		}

		if (!found) {
			galaxy = galaxyMap.get(0);
			info() << "Using default galaxy: " << galaxy.getName() << " (ID: " << galaxy.getID() << ")";
		}

		if (galaxy.getAddress().isEmpty()) {
			result.setError("Invalid galaxy - missing IP address", 3);
			return;
		}

		info() << "Connecting to zone: " << galaxy.getName()
		       << " at " << galaxy.getAddress() << ":" << galaxy.getPort();

		// Create and start zone connection (just socket, no packets)
		// SelectCharacterAction or CreateCharacterAction will handle character selection
		uint32 accountId = core.loginSession->getAccountID();
		const String& sessionId = core.loginSession->getSessionID();

		core.zone = new Zone(accountId, sessionId, galaxy.getAddress(), galaxy.getPort());
		core.zone->start();

		// Wait briefly for connection to establish
		Thread::sleep(100);

		if (!core.zone->isConnected()) {
			result.setError("Zone connection failed", 4);
			return;
		}

		// Success - zone connection established
		result.setSuccess();
		result.setZoneInfo(galaxy.getAddress(), galaxy.getPort(), 0);

		info() << "Zone connection established";
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
			json["galaxyAddress"] = result.getGalaxyAddress().toCharArray();
			json["galaxyPort"] = result.getGalaxyPort();
			json["characterOid"] = result.getCharacterOid();
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
		return new ConnectToZoneAction();
	}
};

// Static registration (runs before main())
static bool _registered_connectToZone =
	(ActionManager::registerAction("connectToZone", ConnectToZoneAction::factory), true);
