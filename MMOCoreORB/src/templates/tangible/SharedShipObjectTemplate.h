/*
 * SharedShipObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDSHIPOBJECTTEMPLATE_H_
#define SHAREDSHIPOBJECTTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"
#include "server/zone/objects/ship/ComponentSlots.h"

class SharedShipObjectTemplate : public SharedTangibleObjectTemplate {
	StringParam interiorLayoutFileName;
	StringParam cockpitFilename;

	StringParam chassisDataName;
	StringParam chassisTypeName;

	VectorMap<String, String> componentNames;
	VectorMap<String, VectorMap<String, float>> componentValues;

	BoolParam hasWings;
	BoolParam playerControlled;

	FloatParam chassisHitpoints;
	FloatParam chassisSlipRate;
	FloatParam chassisSpeed;
	FloatParam chassisMass;

	StringParam conversationTemplate;
	StringParam conversationMobile;
	StringParam conversationMessage;
	StringParam shipDifficulty;
	StringParam shipFaction;

public:
	SharedShipObjectTemplate() {

	}

	~SharedShipObjectTemplate() {

	}

	const VectorMap<String, String>& getComponentNames() const {
		return componentNames;
	}

	const VectorMap<String, VectorMap<String, float>>& getComponentValues() const {
		return componentValues;
	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
		//if (!templateData->isValidTable())
			//return;

		chassisDataName = templateData->getStringField("name");
		chassisTypeName = templateData->getStringField("type");

		if (chassisTypeName == "") {
			chassisTypeName = chassisDataName;
		}

		chassisHitpoints = templateData->getFloatField("chassisHitpoints", 100.f);
		chassisSlipRate = templateData->getFloatField("slideFactor", 1.75f);
		chassisSpeed = templateData->getFloatField("chassisSpeed", 1.f);
		chassisMass = templateData->getFloatField("chassisMass", 10000.f);

		shipDifficulty = templateData->getStringField("difficulty");
		shipFaction = templateData->getStringField("faction");

		conversationTemplate = templateData->getStringField("conversationTemplate");
		conversationMobile = templateData->getStringField("conversationMobile");
		conversationMessage = templateData->getStringField("conversationMessage");

		try {
			const static char* components[] = { "reactor", "engine",  "shield_0", "shield_1", "armor_0", "armor_1", "capacitor", "booster", "droid_interface",
					"bridge", "hangar", "targeting_station", "weapon_0", "weapon_1", "weapon_2", "weapon_3", "weapon_4", "weapon_5", "weapon_6", "weapon_7" };

			for (int i = 0; i < 20; i++) {
				String key = components[i];
				LuaObject component = templateData->getObjectField(key);

				if (!component.isValidTable()) {
					component.pop();
					continue;
				}

				String name = component.getStringField("name", "");
				VectorMap<String, float> map;
				map.setNullValue(0.f);

				switch (i) {
					case Components::REACTOR: {
						const char *fields[] = {"hitpoints", "armor"};
						loadMap(fields, 2, map, component);
						break;
					}

					case Components::ENGINE: {
						const char *fields[] = {"hitpoints", "armor", "speed", "pitch", "roll", "yaw", "acceleration", "deceleration", "pitchRate", "rollRate", "yawRate"};
						loadMap(fields, 11, map, component);
						break;
					}

					case Components::SHIELD0: {
						const char *fields[] = {"hitpoints", "armor", "front", "back", "regen"};
						loadMap(fields, 5, map, component);
						break;
					}

					case Components::SHIELD1: {
						const char *fields[] = {"hitpoints", "armor", "front", "back", "regen"};
						loadMap(fields, 5, map, component);
						break;
					}

					case Components::ARMOR0: {
						const char *fields[] = {"hitpoints", "armor"};
						loadMap(fields, 2, map, component);
						break;
					}

					case Components::ARMOR1: {
						const char *fields[] = {"hitpoints", "armor"};
						loadMap(fields, 2, map, component);
						break;
					}

					case Components::CAPACITOR: {
						const char *fields[] = {"hitpoints", "armor", "rechargeRate", "energy"};
						loadMap(fields, 4, map, component);
						break;
					}

					case Components::BOOSTER: {
						const char *fields[] = {"hitpoints", "armor", "energy", "acceleration", "speed", "energyUsage", "rechargeRate"};
						loadMap(fields, 7, map, component);
						break;
					}

					case Components::DROID_INTERFACE: {
						const char *fields[] = {"hitpoints", "armor"};
						loadMap(fields, 2, map, component);
						break;
					}

					case Components::BRIDGE: {
						const char *fields[] = {"hitpoints", "armor"};
						loadMap(fields, 2, map, component);
						break;
					}

					case Components::HANGAR: {
						const char *fields[] = {"hitpoints", "armor"};
						loadMap(fields, 2, map, component);
						break;
					}

					case Components::TARGETING_STATION: {
						const char *fields[] = {"hitpoints", "armor"};
						loadMap(fields, 2, map, component);
						break;
					}

					case Components::WEAPON_START:
					default: {
						const char *fields[] = {"hitpoints", "armor", "rate", "drain", "maxDamage", "minDamage", "shieldEfficiency", "armorEfficiency", "ammo", "ammo_type"};
						loadMap(fields, 10, map, component);
						break;
					}
				};

				componentNames.put(key, name);
				componentValues.put(key, map);

				component.pop();
			}
		} catch (Exception& e) {
			e.printStackTrace();
		}
	}

	inline const String& getShipName() const {
		return chassisDataName.get();
	}

	inline const String& getShipType() const {
		return chassisTypeName.get();
	}

	inline float getChassisHitpoints() const {
		return chassisHitpoints;
	}

	inline float getChassisSlipRate() const {
		return chassisSlipRate;
	}

	inline float getChassisSpeed() const {
		return chassisSpeed;
	}

	inline float getChassisMass() const {
		return chassisMass;
	}

	inline bool shipHasWings() const {
		return hasWings;
	}

	inline const String& getConversationTemplate() const {
		return conversationTemplate.get();
	}

	inline const String& getConversationMobile() const {
		return conversationMobile.get();
	}

	inline const String& getConversationMessage() const {
		return conversationMessage.get();
	}

	inline const String& getShipDifficulty() const {
		return shipDifficulty.get();
	}

	inline const String& getShipFaction() const {
		return shipFaction.get();
	}

	void parseVariableData(const String& varName, Chunk* data) {
		if (varName == "interiorLayoutFileName") {
			interiorLayoutFileName.parse(data);
		} else if (varName == "cockpitFilename") {
			cockpitFilename.parse(data);
		} else if (varName == "hasWings") {
			hasWings.parse(data);
		} else if (varName == "playerControlled") {
			playerControlled.parse(data);
		}
	}

	void loadMap(const char** fields, int fieldsLen, VectorMap<String, float>& map, LuaObject& obj) {
		for (int i=0; i<fieldsLen; i++) {
			map.put(fields[i], obj.getFloatField(fields[i]));
		}
	}

	void parseFileData(IffStream* iffStream) {
		iffStream->openChunk('PCNT');

		int variableCount = iffStream->getInt();

		iffStream->closeChunk('PCNT');

		for (int i = 0; i < variableCount; ++i) {
			//while (iffStream->getRemainingSubChunksNumber() > 0) {
			Chunk* chunk = iffStream->openChunk('XXXX');

			if (chunk == nullptr)
				continue;

			String varName;

			iffStream->getString(varName);

			//std::cout << "parsing wtf shit:[" << varName.toStdString() << "]\n";
			parseVariableData(varName, chunk);

			iffStream->closeChunk();
		}
	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SSHP') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedTangibleObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SSHP');

		uint32 derv = iffStream->getNextFormType();

		if (derv == 'DERV') {
			loadDerv(iffStream);

			derv = iffStream->getNextFormType();
		}

		iffStream->openForm(derv);

		try {
			parseFileData(iffStream);
		} catch (Exception& e) {
			String msg;
			msg += "exception caught parsing file data ->";
			msg += e.getMessage();

			Logger::console.error(msg);
		}

		iffStream->closeForm(derv);

		if (iffStream->getRemainingSubChunksNumber() > 0) {
			readObject(iffStream);
		}

		iffStream->closeForm('SSHP');
	}
};

#endif /* SHAREDSHIPOBJECTTEMPLATE_H_ */
