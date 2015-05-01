#ifndef FSEXPERIENCETYPES_H_
#define FSEXPERIENCETYPES_H_

#include "engine/engine.h"

class FsExperienceTypes : public Singleton<FsExperienceTypes>,  public Object {
public:
	// Ratios
	VectorMap<String, int> xpRatiosCombat;
	VectorMap<String, int> xpRatiosSenses;
	VectorMap<String, int> xpRatiosCrafting;
	VectorMap<String, int> xpNull;

	Vector<String> tableNames;

public:
	FsExperienceTypes() : Object() {
		// These MUST match up with your Lua file specified below!!!
		tableNames.add("combat");
		tableNames.add("senses");
		tableNames.add("crafting");

		xpNull.put("", -1);

	}

	void loadLuaConfig() {
		Logger::console.info("Loading experience for Force Sensitive conversion ratios..", true);

		Lua* lua = new Lua();
		lua->init();

		// Load the file.
		lua->runFile("scripts/screenplays/village/convos/convohelpers/force_sensititive_experience_types.lua");


		for (int i=0; i < tableNames.size(); ++i) {
			LuaObject tableObject = lua->getGlobalObject(tableNames.get(i));
			loadLuaTableObject(tableObject, i);
		}

		delete lua;
		lua = NULL;
	}

	void loadLuaTableObject(LuaObject table, int type) {

		if(table.isValidTable()){
			for(int i = 1; i <= table.getTableSize(); ++i){
				LuaObject ratio = table.getObjectAt(i);
				if(ratio.isValidTable()){
					String searchString = ratio.getStringAt(1);
					int ratioConversion = ratio.getIntAt(2);
					switch (type) {
					case 0:
						xpRatiosCombat.put(searchString, ratioConversion);
						break;
					case 1:
						xpRatiosSenses.put(searchString, ratioConversion);
						break;
					case 2:
						xpRatiosCrafting.put(searchString, ratioConversion);
						break;
					default:
						// Shouldn't get here
						return;
						break;
					}
				}
				ratio.pop();
			}
		}
		table.pop();
	}

	// Getting ratios for conversion.

	int getRatio(String typeOfExperience, int typeForConversion) {
		switch (typeForConversion) {
		case 0: // FS Combat
		case 3: // FS Reflex
			for (int i=0; i < xpRatiosCombat.size(); ++i) {
				if (typeOfExperience.contains(xpRatiosCombat.elementAt(i).getKey())) {
					return xpRatiosCombat.elementAt(i).getValue();
				}
			}
			break;
		case 1: // FS Crafting
			for (int i=0; i < xpRatiosCrafting.size(); ++i) {
				if (typeOfExperience.contains(xpRatiosCrafting.elementAt(i).getKey())) {
					return xpRatiosCrafting.elementAt(i).getValue();
				}
			}
			break;
		case 2: // FS Senses
			for (int i=0; i < xpRatiosSenses.size(); ++i) {
				if (typeOfExperience.contains(xpRatiosSenses.elementAt(i).getKey())) {
					return xpRatiosSenses.elementAt(i).getValue();
				}
			}
			break;
		default:
			return -1;
		}

		return -1;
	}

	VectorMap<String, int> getFsEligibleExperienceType(int typeForConversion) {

		switch (typeForConversion) {
		case 0: // FS Combat
		case 3: // FS Reflex
			return xpRatiosCombat;
			break;
		case 1: // FS Crafting
			return xpRatiosCrafting;
			break;
		case 2: // FS Senses
			return xpRatiosSenses;
			break;
		default:
			return xpNull;
			break;
		}

		return xpNull;
	}

};

#endif /* FSEXPERIENCETYPES */
