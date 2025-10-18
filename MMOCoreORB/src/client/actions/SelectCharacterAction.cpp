/*
 * SelectCharacterAction.cpp
 *
 * Selects a character to zone in (sends SelectCharacter packet)
 * Requires active zone connection
 */

#include "client/ActionBase.h"
#include "client/ActionResult.h"
#include "client/ActionManager.h"
#include "client/ClientCore.h"
#include "client/login/LoginSession.h"
#include "client/zone/Zone.h"
#include "server/zone/packets/zone/SelectCharacter.h"

class SelectCharacterAction : public ActionBase {
	// Configuration (optional - uses global options if not specified)
	uint64 characterOid;
	String characterFirstname;

	// Result
	ActionResult result;
	bool skipped;

public:
	SelectCharacterAction() :
		characterOid(0),
		skipped(false) {
		setLogLevel(Logger::INFO);
		setLoggingName("SelectCharacter");
	}

	const char* getName() const override {
		return "selectCharacter";
	}

	void parseJSON(const JSONSerializationType& config) override {
		if (config.contains("characterOid")) {
			characterOid = config["characterOid"].get<uint64>();
		}
		if (config.contains("characterFirstname")) {
			characterFirstname = String(config["characterFirstname"].get<std::string>().c_str());
		}
	}

	bool needsZone() const override {
		return true;  // Requires zone connection
	}

	void run(ClientCore& core) override {
		// Validate prerequisites
		if (core.zone == nullptr) {
			result.setError("No zone object (need ConnectToZone first)", 1);
			return;
		}

		if (core.loginSession == nullptr) {
			result.setError("No login session", 2);
			return;
		}

		auto numCharacters = core.loginSession->getCharacterListSize();
		if (numCharacters == 0) {
			result.setError("No characters on account", 3);
			return;
		}

		// Select character
		uint64 selectedOid = 0;

		// Use action-specific config if provided, otherwise fall back to global options
		uint64 oidToUse = characterOid != 0 ? characterOid : core.options.get<uint64>("/characterOid", 0);
		String firstnameToUse = !characterFirstname.isEmpty() ? characterFirstname :
			String(core.options.get<std::string>("/characterFirstname", "").c_str());

		if (oidToUse != 0) {
			auto character = core.loginSession->selectCharacterByOID(oidToUse);
			if (!character) {
				result.setError("Character OID not found in account", 4);
				return;
			}
			selectedOid = character->getObjectID();
			info() << "Selected character by OID: " << character->getFirstName() << " (" << selectedOid << ")";
		} else if (!firstnameToUse.isEmpty()) {
			auto character = core.loginSession->selectCharacterByFirstname(firstnameToUse);
			if (!character) {
				result.setError("Character firstname not found in account", 5);
				return;
			}
			selectedOid = character->getObjectID();
			info() << "Selected character by name: " << character->getFirstName() << " (" << selectedOid << ")";
		} else {
			// Select random character
			auto character = core.loginSession->selectRandomCharacter();
			if (!character) {
				result.setError("Failed to select any character", 6);
				return;
			}
			selectedOid = character->getObjectID();
			info() << "Selected random character: " << character->getFirstName() << " (" << selectedOid << ")";
		}

		// Set the character ID on zone for tracking
		core.zone->setCharacterID(selectedOid);

		// Send SelectCharacter packet
		info() << "Sending SelectCharacter(" << selectedOid << ")";
		BaseMessage* selectMsg = new SelectCharacter(selectedOid);
		core.zone->getZoneClient()->sendMessage(selectMsg);

		// Wait for scene to be ready
		int zoneTimeout = ClientCore::getZoneTimeout() * 1000;
		if (!core.zone->waitForSceneReady(zoneTimeout)) {
			result.setError("Zone scene timeout", 7);
			return;
		}

		// Success - character selected and scene ready
		result.setSuccess();
		info() << "Character selected and scene ready - OID: " << selectedOid;
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
		return new SelectCharacterAction();
	}
};

// Static registration (runs before main())
static bool _registered_selectCharacter =
	(ActionManager::registerAction("selectCharacter", SelectCharacterAction::factory), true);
