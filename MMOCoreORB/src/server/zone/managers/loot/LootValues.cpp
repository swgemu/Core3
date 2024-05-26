#include "server/zone/managers/loot/LootValues.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/managers/loot/LootAttributeType.h"
#include "templates/LootItemTemplate.h"

LootValues::LootValues(const LootItemTemplate* lootTemplate, int lootLevel, float lootModifier) : CraftingValues(lootTemplate->getAttributesMapCopy()) {
	setLoggingName("LootValues: " + lootTemplate->getTemplateName());

	staticValues = lootTemplate->getAttributesMapCopy();
	objectType = lootTemplate->getObjectType();

	dynamicValues = 0;
	modifier = 0.f;
	level = 0;

	setLevel(lootTemplate, lootLevel);
	setModifier(lootTemplate, lootModifier);

	recalculateValues(true);

	addExperimentalAttribute("creatureLevel", "null", level, level, 0, true, RandomType::STATIC);
	setCurrentValue("creatureLevel", level);

	addExperimentalAttribute("modifier", "null", modifier, modifier, 0, true, RandomType::STATIC);
	setCurrentValue("modifier", modifier);
}

void LootValues::setLevel(const LootItemTemplate* lootTemplate, int lootLevel) {
	int levelMax = lootTemplate->getLevelMax();
	int levelMin = lootTemplate->getLevelMin();

	if (levelMax == 0 && levelMin == 0) {
		return;
	}

	if (levelMax > LEVELMAX || levelMax == -1) {
		levelMax = LEVELMAX;
	}

	if (levelMin < LEVELMIN) {
		levelMin = LEVELMIN;
	}

	float levelRank = getLevelRankValue(lootLevel);

	level = levelMax == levelMin ? levelMin : getPercentageValue(levelMin, levelMax, levelRank);
}

void LootValues::setModifier(const LootItemTemplate* lootTemplate, float lootModifier) {
	int levelMax = lootTemplate->getLevelMax();
	int levelMin = lootTemplate->getLevelMin();

	if (levelMax == 0 && levelMin == 0) {
		return;
	}

	int modLvl = levelMin == 0 ? BonusType::STATIC : BonusType::EXPERIMENTAL;
	int modMax = modLvl;
	int modMin = modLvl;

	if (lootModifier > EXCEPTIONAL) {
		modMax = BonusType::LEGENDARY;
		modMin = BonusType::EXCEPTIONAL;
	} else if (lootModifier > ENHANCED) {
		modMax = BonusType::EXCEPTIONAL;
		modMin = BonusType::ENHANCED;
	} else if (lootModifier > EXPERIMENTAL) {
		modMax = BonusType::ENHANCED;
		modMin = BonusType::EXPERIMENTAL;
	} else if (lootModifier > STATIC) {
		modMax = BonusType::EXPERIMENTAL;
		modMin = BonusType::STATIC;
	}

	modifier = modMax == modMin ? modMin : getDistributedValue(modMin, modMax, level) + BonusType::EXPERIMENTAL;
}

void LootValues::recalculateValues(bool initial) {
	setStaticValues();
	setRandomValues();
	setDamageValues();
}

void LootValues::setStaticValues() {
	dynamicValues = 0;

	for (int i = 0; i < getTotalExperimentalAttributes(); ++i) {
		setStaticValue(getAttribute(i));
	}
}

void LootValues::setRandomValues() {
	Vector<String> attributeIndex;

	for (int i = 0; i < getTotalExperimentalAttributes(); ++i) {
		const String& attribute = getAttribute(i);

		float min = getMinValue(attribute);
		float max = getMaxValue(attribute);

		int precision = getPrecision(attribute) % 10;
		int randomType = getCombineType(attribute);

		if (randomType == RandomType::STATIC || min == max) {
			setStaticValue(attribute);
			continue;
		}

		if (randomType == RandomType::DYNAMIC) {
			attributeIndex.add(attribute);
			continue;
		}

		if (randomType == RandomType::UNIFORM) {
			if (precision == 0) {
				setUniformValue<int>(attribute);
			} else {
				setUniformValue<float>(attribute);
			}
		}
	}

	if (modifier <= 0.f || level <= 0 || attributeIndex.size() == 0) {
		return;
	}

	dynamicValues = attributeIndex.size();

	if (modifier <= BonusType::ENHANCED) {
		dynamicValues = getDistributedValue(1, attributeIndex.size(), level) * modifier;
		dynamicValues = Math::min(dynamicValues, attributeIndex.size());
	}

	float bonusValue = Math::max(1, modifier);

	for (int i = dynamicValues; -1 < --i;) {
		int key = System::random(attributeIndex.size()-1);

		String attribute = attributeIndex.get(key);
		int precision = getPrecision(attribute) % 10;

		if (precision == 0) {
			setDynamicValue<int>(attribute, bonusValue);
		} else {
			setDynamicValue<float>(attribute, bonusValue);
		}

		bonusValue = getDistributedValue(1, modifier, level);
		attributeIndex.remove(key);
	}
}

void LootValues::setDamageValues() {
	if (!hasExperimentalAttribute("mindamage") || !hasExperimentalAttribute("maxdamage")) {
		return;
	}

	if (objectType & SceneObjectType::WEAPON) {
		float maxPercent = getCurrentPercentage("maxdamage");
		float minPercent = getCurrentPercentage("mindamage");

		if (maxPercent > 0.f || minPercent > 0.f) {
			float maxPercentMax = getMaxPercentage("maxdamage");
			float minPercentMax = getMaxPercentage("mindamage");

			float percent = Math::max(minPercent, maxPercent);
			float percentMax = Math::max(minPercentMax, maxPercentMax);

			setCurrentPercentage("maxdamage", percent, percentMax);
			setModifierValue("maxdamage", percentMax);

			setCurrentPercentage("mindamage", percent, percentMax);
			setModifierValue("mindamage", percentMax);
		}
	} else if (objectType & SceneObjectType::COMPONENT) {
		float maxValue = getCurrentValue("maxdamage");
		float minValue = getCurrentValue("mindamage");

		if (maxValue < minValue) {
			float maxPercent = getCurrentPercentage("maxdamage");
			float maxPercentMax = getMaxPercentage("maxdamage");

			float minPercent = getCurrentPercentage("mindamage");
			float minPercentMax = getMaxPercentage("mindamage");

			setCurrentValue("maxdamage", minValue);
			setCurrentPercentage("maxdamage", minPercent, minPercentMax);

			setCurrentValue("mindamage", maxValue);
			setCurrentPercentage("mindamage", maxPercent, maxPercentMax);
		}
	}
}

void LootValues::setStaticValue(const String& attribute) {
	float min = 0.f;
	float max = 0.f;

	if (staticValues.hasExperimentalAttribute(attribute)) {
		min = staticValues.getMinValue(attribute);
		max = staticValues.getMaxValue(attribute);
	}

	setCurrentValue(attribute, min, min, max);
	setCurrentPercentage(attribute, 0.f, 0.f);
}

template<typename Auto>
void LootValues::setUniformValue(const String& attribute) {
	Auto min = staticValues.getMinValue(attribute);
	Auto max = staticValues.getMaxValue(attribute);
	Auto value = getRandomValue(min, max);

	float percent = getValuePercentage(min, max, value);

	setCurrentValue(attribute, value, min, max);
	setCurrentPercentage(attribute, percent, 1.f);
}

template<typename Auto>
void LootValues::setDynamicValue(const String& attribute, float percentageMax) {
	Auto min = staticValues.getMinValue(attribute);
	Auto max = staticValues.getMaxValue(attribute);
	Auto value = getDistributedValue(min, max, level, DISTMIN, DISTMAX);

	float percent = getValuePercentage(min, max, value);
	float percentMax = Math::max(1.f, percentageMax);

	setCurrentValue(attribute, value, min, max);
	setCurrentPercentage(attribute, percent, percentMax);

	setModifierValue(attribute, percentMax);
}

void LootValues::setModifierValue(const String& attribute, float percentageMax) {
	float min = staticValues.getMinValue(attribute);
	float max = staticValues.getMaxValue(attribute);

	if (fabs(min) < EPSILON || fabs(max) < EPSILON) {
		return;
	}

	float percent = getCurrentPercentage(attribute);
	float percentMax = Math::max(1.f, percentageMax);

	float valueMin = getModifierValue(min, max, percentMax - 1.f);
	float valueMax = getModifierValue(min, max, percentMax);
	float value = getPercentageValue(valueMin, valueMax, percent);

	setCurrentValue(attribute, value, valueMin, valueMax);
	setCurrentPercentage(attribute, percent, percentMax);
}

float LootValues::getModifierValue(float min, float max, float percentageMax) {
	if (fabs(max - min) < EPSILON || percentageMax <= 1.f) {
		return getPercentageValue(min, max, percentageMax);
	}

	bool inverted = min >= max;
	bool positive = max >= 0.f;

	float signBit = positive ? 1.f : -1.f;
	float fabsMax = fabs(max);
	float fabsMin = fabs(min);

	float value = std::min(fabsMin, fabsMax) * signBit;

	if (inverted != positive) {
		return (value * (percentageMax - 1.f)) + max;
	} else {
		return value / percentageMax;
	}
}

int LootValues::getModifierValue(int min, int max, float percentageMax) {
	return round(getModifierValue((float)min, (float)max, percentageMax));
}

float LootValues::getPercentageValue(float min, float max, float percentage) {
	if (fabs(max - min) < EPSILON) {
		return min;
	}

	float percent = Math::clamp(0.f, percentage, 1.f);

	return ((max - min) * percent) + min;
}

int LootValues::getPercentageValue(int min, int max, float percentage) {
	return round(getPercentageValue((float)min, (float)max, percentage));
}

float LootValues::getValuePercentage(float min, float max, float value) {
	if (fabs(max - min) < EPSILON) {
		return 0.f;
	}

	float percent = 0.f;

	if (max > min) {
		percent = (value - min) / (max - min);
	} else {
		percent = (min - value) / (min - max);
	}

	return Math::clamp(0.f, percent, 1.f);
}

float LootValues::getRandomValue(float min, float max) {
	if (fabs(max - min) < EPSILON) {
		return min;
	}

	float valueMin = Math::min(min, max);
	float valueMax = Math::max(min, max);
	float value = System::frandom(valueMax - valueMin) + valueMin;

	return Math::clamp(valueMin, value, valueMax);
}

int LootValues::getRandomValue(int min, int max) {
	if (max == min) {
		return min;
	}

	float valueMin = Math::min(min, max);
	float valueMax = Math::max(min, max);
	float value = System::random(valueMax - valueMin) + valueMin;

	return Math::clamp(valueMin, value, valueMax);
}

float LootValues::getDistributedValue(float min, float max, int level, float distMin, float distMax) {
	if (fabs(max - min) < EPSILON) {
		return min;
	}

	float rank = Math::clamp(-1.f, getLevelRankValue(level, distMin, distMax), 2.f);
	bool inverted = max < min;

	float valueMin = min;
	float valueMax = max;

	if (inverted) {
		min = valueMax;
		max = valueMin;
	}

	float mid = ((max - min) * rank) + min;

	if (mid < min) {
		max += (mid - min);
		mid = min;
	}

	if (mid > max) {
		min += (mid - max);
		mid = max;
	}

	float randomMin = getRandomValue(min, mid);
	float randomMax = getRandomValue(mid, max);
	float randomVal = getRandomValue(randomMin, randomMax);

	if (inverted) {
		randomVal = (valueMax - randomVal) + valueMin;
	}

	return Math::clamp(min, randomVal, max);
}

int LootValues::getDistributedValue(int min, int max, int level, float distMin, float distMax) {
	if (max == min) {
		return min;
	}

	float rank = Math::clamp(-1.f, getLevelRankValue(level, distMin, distMax), 2.f);
	bool inverted = max < min;

	int valueMin = min;
	int valueMax = max;

	if (inverted) {
		min = valueMax;
		max = valueMin;
	}

	int mid = round(((max - min) * rank) + min);

	if (mid < min) {
		max += (mid - min);
		mid = min;
	}

	if (mid > max) {
		min += (mid - max);
		mid = max;
	}

	int randomMin = getRandomValue(min, mid);
	int randomMax = getRandomValue(mid, max);
	int randomVal = getRandomValue(randomMin, randomMax);

	if (inverted) {
		randomVal = (valueMax - randomVal) + valueMin;
	}

	return Math::clamp(min, randomVal, max);
}

float LootValues::getLevelRankValue(int level, float distMin, float distMax) {
	float rank = Math::clamp(0.f, (level - LEVELMIN) / (float)(LEVELMAX - LEVELMIN), 1.f);

	return Math::linearInterpolate(distMin, distMax, rank);
}
