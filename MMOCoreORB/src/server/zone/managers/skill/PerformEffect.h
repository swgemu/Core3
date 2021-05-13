#ifndef PERFORMEFFECT_H_
#define PERFORMEFFECT_H_

#include "templates/datatables/DataTableRow.h"

class PerformEffect {
	int effectIndex;
	String effectName;
	int effectId;
	int effectLevel;
	bool isDance;
	bool isMusic;
	int requiredSkillModValue;
	bool requiredPerform;
	int targetType;
	float effectDuration;
	int effectActionCost;
	String effectFile;
	String effectMessage;

public:
	enum {
		TARGET_STATIONARY = 1,
		TARGET_OTHER = 2,
		TARGET_SELF = 3
	};
	enum {
		DAZZLE = 1,
		DISTRACT = 2,
		SPOTLIGHT = 3,
		COLORLIGHTS = 4,
		SMOKEBOMB = 5,
		FIREJETS = 6,
		VENTRILOQUISM = 7
	};

	inline bool isDanceEffect() {
		return isDance;
	}

	inline bool isMusicEffect() {
		return isMusic;
	}

	inline String& getName() {
		return effectName;
	}

	inline String& getEffectFile() {
		return effectFile;
	}

	inline String& getEffectMessage() {
		return effectMessage;
	}

	inline int getEffectLevel() {
		return effectLevel;
	}

	inline int getEffectId() {
		return effectId;
	}

	inline int getRequiredSkillModValue() {
		return requiredSkillModValue;
	}

	inline bool isPerformRequired() {
		return requiredPerform;
	}

	inline int getTargetType() {
		return targetType;
	}

	inline float getEffectDuration() {
		return effectDuration;
	}

	inline int getEffectActionCost() {
		return effectActionCost;
	}


	void parseDataTableRow(int idx, DataTableRow* row) {
		effectIndex = idx;
		String tempString, tempString2;

		row->getValue(0, tempString);
		tempString2 = tempString.subString(tempString.length() - 1);
		effectLevel = Integer::valueOf(tempString2);
		tempString = tempString.replaceAll(tempString2, "");
		effectName = tempString.toLowerCase();

		if (effectName == "dazzle")
			effectId = DAZZLE;
		else if (effectName == "distract")
			effectId = DISTRACT;
		else if (effectName == "spotlight")
			effectId = SPOTLIGHT;
		else if (effectName == "colorlights")
			effectId = COLORLIGHTS;
		else if (effectName == "smokebomb")
			effectId = SMOKEBOMB;
		else if (effectName == "firejets")
			effectId = FIREJETS;
		else if (effectName == "ventriloquism")
			effectId = VENTRILOQUISM;

		row->getValue(1, tempString);

		if (tempString.contains("dance"))
			isDance = true;
		if (tempString.contains("music"))
			isMusic = true;

		row->getValue(2, requiredSkillModValue);
		row->getValue(3, requiredPerform);
		row->getValue(4, targetType);

		row->getValue(5, effectDuration);
		row->getValue(6, effectActionCost);

		if (effectId == DAZZLE) {
			effectFile = "clienteffect/entertainer_dazzle_level_" + String::valueOf(effectLevel) + ".cef";
			effectMessage = "effect_perform_dazzle";
		} else if (effectId == DISTRACT) {
			effectFile = "clienteffect/entertainer_distract_level_" + String::valueOf(effectLevel) + ".cef";
			effectMessage = "effect_perform_distract";
		} else if (effectId == SPOTLIGHT) {
			effectFile = "clienteffect/entertainer_spot_light_level_" + String::valueOf(effectLevel) + ".cef";
			effectMessage = "effect_perform_spot_light";
		} else if (effectId == COLORLIGHTS) {
			effectFile = "clienteffect/entertainer_color_lights_level_" + String::valueOf(effectLevel) + ".cef";
			effectMessage = "effect_perform_color_lights";
		} else if (effectId == SMOKEBOMB) {
			effectFile = "clienteffect/entertainer_smoke_bomb_level_" + String::valueOf(effectLevel) + ".cef";
			effectMessage = "effect_perform_smoke_bomb";
		} else if (effectId == FIREJETS) {
			effectFile = "clienteffect/entertainer_fire_jets_level_" + String::valueOf(effectLevel) + ".cef";
			effectMessage = "effect_perform_fire_jets";
		} else if (effectId == VENTRILOQUISM) {
			effectFile = "clienteffect/entertainer_ventriloquism_level_" + String::valueOf(effectLevel) + ".cef";
			effectMessage = "effect_perform_ventriloquism";
		}
	}
};



#endif /* PERFORMEFFECT_H_ */
