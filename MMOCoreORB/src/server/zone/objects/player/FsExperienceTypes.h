#ifndef FSEXPERIENCETYPES_H_
#define FSEXPERIENCETYPES_H_

#include "engine/engine.h"

class FsExperienceTypes : public Singleton<FsExperienceTypes>,  public Object {
public:
	// Ratios
	VectorMap<String, int> xpRatiosCombat;
	VectorMap<String, int> xpRatiosSenses;
	VectorMap<String, int> xpRatiosCrafting;
	VectorMap<String, int> xpRatiosNotValid;

public:
	FsExperienceTypes() : Object() {
		xpRatiosCombat.put("combat_general", 3);
		xpRatiosCombat.put("squadleader", 90);
		xpRatiosCombat.put("bountyhunter", 1);
		xpRatiosCombat.put("combat_melee", 30);
		xpRatiosCombat.put("combat_ranged", 30);

		xpRatiosSenses.put("bio_engineer_dna_harvesting", 3);
		xpRatiosSenses.put("political", 3);
		xpRatiosSenses.put("slicing", 3);
		xpRatiosSenses.put("merchant", 4);
		xpRatiosSenses.put("resource_harvesting_inorganic", 5);
		xpRatiosSenses.put("imagedesigner", 7);
		xpRatiosSenses.put("scout", 8);
		xpRatiosSenses.put("creaturehandler", 9);
		xpRatiosSenses.put("dance", 10);
		xpRatiosSenses.put("music", 10);
		xpRatiosSenses.put("entertainer_healing", 10);
		xpRatiosSenses.put("camp", 10);
		xpRatiosSenses.put("medical", 10);
		xpRatiosSenses.put("trapping", 25);

		xpRatiosCrafting.put("crafting_bio_engineer_creature", 4);
		xpRatiosCrafting.put("crafting_bio_engineer_tissue", 5);
		xpRatiosCrafting.put("crafting_c", 5);
		xpRatiosCrafting.put("crafting_d", 5);
		xpRatiosCrafting.put("crafting_f", 5);
		xpRatiosCrafting.put("crafting_m", 5);
		xpRatiosCrafting.put("crafting_sc", 5);
		xpRatiosCrafting.put("crafting_sp", 5);
		xpRatiosCrafting.put("crafting_w", 5);
		xpRatiosCrafting.put("crafting_general", 8);
		xpRatiosCrafting.put("crafting_structure_general", 35);

		xpRatiosNotValid.put("", -1);
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
			return xpRatiosNotValid;
			break;
		}

		return xpRatiosNotValid;
	}

};

#endif /* FSEXPERIENCETYPES */
