/*
 * CreateCharacterAction.cpp
 *
 * Creates a new character on the zone server
 * Extracted from ZonePacketHandler for action framework
 */

#include "client/ActionBase.h"
#include "client/ActionResult.h"
#include "client/ActionManager.h"
#include "client/ClientCore.h"
#include "client/zone/Zone.h"
#include "server/zone/packets/charcreation/ClientCreateCharacter.h"

class CreateCharacterAction : public ActionBase {
	// Configuration
	String characterName;
	String race;
	String profession;
	float height;
	String customization;
	String hairTemplate;
	String hairCustomization;
	String biography;
	bool skipTutorial;

	// Result
	CreateCharacterResult result;
	bool skipped;

public:
	CreateCharacterAction() :
		height(1.0f),
		skipTutorial(true),
		skipped(false) {
		setLogLevel(Logger::INFO);
		setLoggingName("CreateCharacter");
	}

	const char* getName() const override {
		return "createCharacter";
	}

	int parseArgs(const Vector<String>& args, int startIndex) override {
		if (startIndex >= args.size()) return 0;

		// Check for --create-character flag
		if (args.get(startIndex) == "--create-character") {
			return 1;
		}

		// Parse character creation options
		if (args.get(startIndex) == "--char-name" && startIndex + 1 < args.size()) {
			characterName = args.get(startIndex + 1);
			return 2;
		}
		if (args.get(startIndex) == "--char-race" && startIndex + 1 < args.size()) {
			race = args.get(startIndex + 1);
			return 2;
		}
		if (args.get(startIndex) == "--char-profession" && startIndex + 1 < args.size()) {
			profession = args.get(startIndex + 1);
			return 2;
		}
		if (args.get(startIndex) == "--char-height" && startIndex + 1 < args.size()) {
			height = Float::valueOf(args.get(startIndex + 1));
			return 2;
		}
		if (args.get(startIndex) == "--char-customization" && startIndex + 1 < args.size()) {
			customization = args.get(startIndex + 1);
			return 2;
		}
		if (args.get(startIndex) == "--char-hair-template" && startIndex + 1 < args.size()) {
			hairTemplate = args.get(startIndex + 1);
			return 2;
		}
		if (args.get(startIndex) == "--char-hair-customization" && startIndex + 1 < args.size()) {
			hairCustomization = args.get(startIndex + 1);
			return 2;
		}
		if (args.get(startIndex) == "--char-biography" && startIndex + 1 < args.size()) {
			biography = args.get(startIndex + 1);
			return 2;
		}

		return 0;
	}

	void parseJSON(const JSONSerializationType& config) override {
		if (config.contains("name")) {
			characterName = String(config["name"].get<std::string>().c_str());
		}
		if (config.contains("race")) {
			race = String(config["race"].get<std::string>().c_str());
		}
		if (config.contains("profession")) {
			profession = String(config["profession"].get<std::string>().c_str());
		}
		if (config.contains("height")) {
			height = config["height"];
		}
		if (config.contains("customization")) {
			customization = String(config["customization"].get<std::string>().c_str());
		}
		if (config.contains("hairTemplate")) {
			hairTemplate = String(config["hairTemplate"].get<std::string>().c_str());
		}
		if (config.contains("hairCustomization")) {
			hairCustomization = String(config["hairCustomization"].get<std::string>().c_str());
		}
		if (config.contains("biography")) {
			biography = String(config["biography"].get<std::string>().c_str());
		}
		if (config.contains("skipTutorial")) {
			skipTutorial = config["skipTutorial"];
		}
	}

	bool needsZone() const override {
		return true;  // Zone-phase action
	}

	bool needsTarget() const override {
		return true;  // Needs targetGalaxyId to know where to create
	}

	void run(ClientCore& core) override {
		// Warn if targetCharacterOid is set (we're creating new, not using existing)
		if (core.targetCharacterOid != 0) {
			warning() << "Ignoring selected character OID " << core.targetCharacterOid
			          << " (createCharacter creates new character)";
		}
		// Validate prerequisites
		if (core.zone == nullptr || !core.zone->isConnected()) {
			result.setError("No active zone connection", 1);
			return;
		}

		if (!core.zone->isSceneReady()) {
			result.setError("Zone scene not ready", 2);
			return;
		}

		// Use configured values or defaults
		String charName = characterName;
		String charRace = race;
		String charProfession = profession;
		float charHeight = height;
		String charCustomization = customization;
		String charHairTemplate = hairTemplate;
		String charHairCustomization = hairCustomization;
		String charBiography = biography;

		// Generate default name if not provided
		if (charName.isEmpty()) {
			String username = String(core.options.config["username"].get<std::string>().c_str());
			charName = username + String::valueOf(System::random(9999));
		}

		// Default race if not provided
		if (charRace.isEmpty()) {
			charRace = "object/creature/player/human_male.iff";
		}

		// Default profession if not provided
		if (charProfession.isEmpty()) {
			charProfession = "crafting_artisan";
		}

		// Clamp height
		if (charHeight < 0.7f || charHeight > 1.5f) {
			warning("Height " + String::valueOf(charHeight) + " out of range, clamping to 1.0");
			charHeight = 1.0f;
		}

		info() << "Creating character:";
		info() << "  Name: " << charName;
		info() << "  Race: " << charRace;
		info() << "  Profession: " << charProfession;
		info() << "  Height: " << charHeight;
		info() << "  Skip Tutorial: " << skipTutorial;

		// Build and send character creation packet
		UnicodeString unicodeName(charName.toCharArray());
		UnicodeString unicodeBio(charBiography.toCharArray());

		BaseMessage* createPacket = new ClientCreateCharacter(
			unicodeName,
			charRace,
			charHeight,
			charCustomization,
			charHairTemplate,
			charHairCustomization,
			charProfession,
			unicodeBio,
			!skipTutorial  // Note: inverted
		);

		core.zone->getZoneClient()->sendMessage(createPacket);

		// Wait for character creation to complete
		// ZonePacketHandler will set characterCreated or characterCreationFailed
		int timeoutMs = 30000;  // 30 seconds
		Time startTime;
		startTime.updateToCurrentTime();

		while (startTime.miliDifference() < timeoutMs) {
			if (core.zone->isCharacterCreated()) {
				// Success!
				uint64 createdOid = core.zone->getCreatedCharacterOID();
				result.setSuccess();
				result.setCreatedCharacter(createdOid, charName);

				// Store OID in variables for potential use by other actions
				core.setVar("createdOid", String::valueOf(createdOid));
				core.setVar("createdCharacterName", charName);

				info() << "Character created successfully - OID: " << createdOid;
				return;
			}

			if (core.zone->hasCharacterCreationFailed()) {
				result.setError("Character creation failed - server rejected request", 3);
				return;
			}

			Thread::sleep(100);
		}

		// Timeout
		result.setError("Character creation timeout", 4);
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
			json["createdOid"] = result.getCreatedOid();
			json["characterName"] = result.getCharacterName().toCharArray();
		} else {
			json["status"] = "failed";
			json["error"] = result.getError().toCharArray();
			json["errorCode"] = result.getErrorCode();
		}

		return json;
	}

	String getHelpText() const override {
		return "--create-character  Create new character (uses --char-name, --char-race, --char-profession, etc.)";
	}

	// Factory function for static registration
	static ActionBase* factory() {
		return new CreateCharacterAction();
	}
};

// Static registration (runs before main())
static bool _registered_createCharacter =
	(ActionManager::registerAction("createCharacter", CreateCharacterAction::factory), true);
