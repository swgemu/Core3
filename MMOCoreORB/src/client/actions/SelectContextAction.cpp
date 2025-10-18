/*
 * SelectContextAction.cpp
 *
 * Selects the target context (character + galaxy) for subsequent operations
 * Stores selection in core.targetCharacterOid and core.targetGalaxyId
 */

#include "client/ActionBase.h"
#include "client/ActionResult.h"
#include "client/ActionManager.h"
#include "client/ClientCore.h"
#include "client/login/LoginSession.h"

class SelectContextAction : public ActionBase {
	// Configuration
	uint32 galaxyId;
	String galaxyName;
	uint64 characterOid;
	String characterFirstname;

	// Result
	ActionResult result;
	bool skipped;

public:
	SelectContextAction() :
		galaxyId(0),
		characterOid(0),
		skipped(false) {
		setLogLevel(Logger::INFO);
		setLoggingName("SelectContext");
	}

	const char* getName() const override {
		return "selectContext";
	}

	int parseArgs(const Vector<String>& args, int startIndex) override {
		if (startIndex >= args.size()) return 0;

		if (args.get(startIndex) == "--galaxy" && startIndex + 1 < args.size()) {
			String val = args.get(startIndex + 1);
			// Try parsing as number first, otherwise treat as name
			try {
				galaxyId = UnsignedInteger::valueOf(val);
			} catch (...) {
				galaxyName = val;
			}
			return 2;
		}

		if (args.get(startIndex) == "--character-oid" && startIndex + 1 < args.size()) {
			characterOid = UnsignedLong::valueOf(args.get(startIndex + 1));
			return 2;
		}

		if (args.get(startIndex) == "--character-firstname" && startIndex + 1 < args.size()) {
			characterFirstname = args.get(startIndex + 1);
			return 2;
		}

		return 0;
	}

	void parseJSON(const JSONSerializationType& config) override {
		if (config.contains("galaxyId")) {
			galaxyId = config["galaxyId"].get<uint32>();
		}
		if (config.contains("galaxyName")) {
			galaxyName = String(config["galaxyName"].get<std::string>().c_str());
		}
		if (config.contains("characterOid")) {
			characterOid = config["characterOid"].get<uint64>();
		}
		if (config.contains("characterFirstname")) {
			characterFirstname = String(config["characterFirstname"].get<std::string>().c_str());
		}
	}

	bool needsZone() const override {
		return false;  // Login-phase metadata selection
	}

	void run(ClientCore& core) override {
		if (core.loginSession == nullptr || !core.loginSession->isLoggedIn()) {
			result.setError("No active login session", 1);
			return;
		}

		// Resolve galaxy
		uint32 resolvedGalaxyId = 0;

		if (galaxyId != 0) {
			// Explicit galaxy ID
			resolvedGalaxyId = galaxyId;
		} else if (!galaxyName.isEmpty()) {
			// Galaxy by name
			auto& galaxies = core.loginSession->getGalaxies();
			bool found = false;
			for (int i = 0; i < galaxies.size(); i++) {
				if (galaxies.get(i).getName() == galaxyName) {
					resolvedGalaxyId = galaxies.get(i).getID();
					found = true;
					break;
				}
			}
			if (!found) {
				result.setError("Galaxy name not found: " + galaxyName, 2);
				return;
			}
		}

		// Resolve character
		uint64 resolvedCharacterOid = 0;

		if (characterOid != 0) {
			// Explicit character OID
			auto character = core.loginSession->selectCharacterByOID(characterOid);
			if (!character) {
				result.setError("Character OID not found", 3);
				return;
			}
			resolvedCharacterOid = character->getObjectID();
			uint32 charGalaxyId = character->getGalaxyID();

			// Validate galaxy matches if both specified
			if (resolvedGalaxyId != 0 && resolvedGalaxyId != charGalaxyId) {
				result.setError("Character is on galaxy " + String::valueOf(charGalaxyId) +
				                " but you specified galaxy " + String::valueOf(resolvedGalaxyId), 4);
				return;
			}

			resolvedGalaxyId = charGalaxyId;
			info() << "Selected character: " << character->getFirstName() << " (OID: " << resolvedCharacterOid << ")";

		} else if (!characterFirstname.isEmpty()) {
			// Character by firstname
			auto character = core.loginSession->selectCharacterByFirstname(characterFirstname);
			if (!character) {
				result.setError("Character firstname not found: " + characterFirstname, 5);
				return;
			}
			resolvedCharacterOid = character->getObjectID();
			uint32 charGalaxyId = character->getGalaxyID();

			// Validate galaxy matches if both specified
			if (resolvedGalaxyId != 0 && resolvedGalaxyId != charGalaxyId) {
				result.setError("Character '" + characterFirstname + "' is on galaxy " + String::valueOf(charGalaxyId) +
				                " but you specified galaxy " + String::valueOf(resolvedGalaxyId), 6);
				return;
			}

			resolvedGalaxyId = charGalaxyId;
			info() << "Selected character: " << characterFirstname << " (OID: " << resolvedCharacterOid << ")";

		} else {
			// Default: pick first/random character (if any exist)
			auto numCharacters = core.loginSession->getCharacterListSize();
			if (numCharacters > 0) {
				auto character = core.loginSession->selectRandomCharacter();
				if (character) {
					resolvedCharacterOid = character->getObjectID();
					uint32 charGalaxyId = character->getGalaxyID();

					// If galaxy not specified, use character's galaxy
					if (resolvedGalaxyId == 0) {
						resolvedGalaxyId = charGalaxyId;
					}

					info() << "Auto-selected character: " << character->getFirstName() << " (OID: " << resolvedCharacterOid << ")";
				}
			}
		}

		// If still no galaxy, pick first available
		if (resolvedGalaxyId == 0) {
			auto& galaxies = core.loginSession->getGalaxies();
			if (galaxies.size() > 0) {
				resolvedGalaxyId = galaxies.get(0).getID();
				info() << "Auto-selected galaxy: " << galaxies.get(0).getName() << " (ID: " << resolvedGalaxyId << ")";
			} else {
				result.setError("No galaxies available", 7);
				return;
			}
		}

		// Store resolved context (merge with any previous selectContext calls)
		if (resolvedGalaxyId != 0) {
			if (core.targetGalaxyId != 0 && core.targetGalaxyId != resolvedGalaxyId) {
				warning() << "Changing target galaxy from " << core.targetGalaxyId << " to " << resolvedGalaxyId;
			}
			core.targetGalaxyId = resolvedGalaxyId;
		}

		if (resolvedCharacterOid != 0) {
			if (core.targetCharacterOid != 0 && core.targetCharacterOid != resolvedCharacterOid) {
				warning() << "Changing target character from " << core.targetCharacterOid << " to " << resolvedCharacterOid;
			}
			core.targetCharacterOid = resolvedCharacterOid;
		}

		result.setSuccess();
		info() << "Context selected - Galaxy: " << core.targetGalaxyId << ", Character: " << core.targetCharacterOid;
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
		return new SelectContextAction();
	}
};

// Static registration (runs before main())
static bool _registered_selectContext =
	(ActionManager::registerAction("selectContext", SelectContextAction::factory), true);
