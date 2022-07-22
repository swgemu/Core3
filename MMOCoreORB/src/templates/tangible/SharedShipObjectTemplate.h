/*
 * SharedShipObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDSHIPOBJECTTEMPLATE_H_
#define SHAREDSHIPOBJECTTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class SharedShipObjectTemplate : public SharedTangibleObjectTemplate {
	StringParam interiorLayoutFileName;
	StringParam cockpitFilename;
    String shipName;
    VectorMap<String, String> componentNames;
	VectorMap<String, VectorMap<String, float>> componentValues;

	BoolParam hasWings;
	BoolParam playerControlled;

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

		shipName = templateData->getStringField("name");

		const static char* components[] = {"reactor", "engine", "capacitor", "booster", "droid_interface", "bridge", "hangar",
								  "targeting_station", "armor_0", "armor_1", "shield_0", "shield_1", "weapon_0",
								  "weapon_1", "weapon_2", "weapon_3", "weapon_4", "weapon_5","weapon_6", "weapon_7"};
		const int numComponents = 20;
		try {
			for (int i = 0; i < 20; i++) {
				String k = components[i];
				LuaObject component = templateData->getObjectField(k);
				if (component.isValidTable()) {
					VectorMap<String, float> map;
					String name = component.getStringField("name", "");
					char **fields = NULL;
					switch (i) {
						case 0: {
							const char *fields[] = {"hitpoints", "armor"};
							loadMap(fields, 2, map, component);
							break;
						}
						case 1: {
							const char *fields[] = {"hitpoints", "armor", "speed", "pitch", "roll", "yaw",
													"acceleration",
													"deceleration", "pitchRate", "rollRate", "yawRate"};
							loadMap(fields, 11, map, component);
							break;
						}
						case 2: {
							const char *fields[] = {"hitpoints", "armor", "rechargeRate", "energy"};
							loadMap(fields, 4, map, component);
							break;
						}
						case 3: {
							const char *fields[] = {"hitpoints", "armor", "rechargeRate", "energy", "acceleration",
													"speed"};
							loadMap(fields, 6, map, component);
							break;
						}
						case 4:
						case 5:
						case 6:
						case 7:
						case 8:
						case 9: {
							const char *fields[] = {"hitpoints", "armor"};
							loadMap(fields, 2, map, component);
							break;
						}
						case 10:
						case 11: {
							const char *fields[] = {"hitpoints", "armor", "front", "back", "regen"};
							loadMap(fields, 5, map, component);
							break;
						}
						case 12:
						case 13:
						case 14:
						case 15:
						case 16:
						case 17:
						case 18:
						case 19: {
							const char *fields[] = {"hitpoints", "armor", "rate", "drain", "maxDamage", "minDamage",
													"shieldEfficiency", "armorEfficiency", "ammo", "ammo_type"};
							loadMap(fields, 10, map, component);
							break;
						}
					};
					componentValues.put(components[i], map);
					componentNames.put(components[i], name);
				}
				component.pop();
			}
		} catch (Exception& e) {
			e.printStackTrace();
		}
    }

    String getShipName() {
        return shipName;
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
