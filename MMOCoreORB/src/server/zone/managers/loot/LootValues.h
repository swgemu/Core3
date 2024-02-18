#ifndef LOOTVALUES_H_
#define LOOTVALUES_H_

#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/managers/loot/LootAttributeType.h"
#include "templates/LootItemTemplate.h"

#ifndef LOOTVALUES_DEBUG
//#define LOOTVALUES_DEBUG
#endif // LOOTVALUES_DEBUG

class LootValues: public CraftingValues, public LootAttributeType {
public:
	constexpr static float EPSILON = 5e-7f;
	constexpr static float DISTMAX = 0.95f;
	constexpr static float DISTMIN = 0.15f;
	constexpr static float LEVELMAX = 350;
	constexpr static float LEVELMIN = 0;

	enum BonusType : int {
		LEGENDARY = 9,
		EXCEPTIONAL = 8,
		ENHANCED = 2,
		EXPERIMENTAL = 1,
		STATIC = 0,
	};

protected:
	AttributesMap staticValues;
	uint32 objectType;

	int dynamicValues;
	int modifier;
	int level;

public:
	LootValues(const LootItemTemplate* lootTemplate, int lootLevel, float lootModifier);

	uint32 getObjectType() const {
		return objectType;
	}

	int getDynamicValues() const {
		return dynamicValues;
	}

	int getModifier() const {
		return modifier;
	}

	int getLevel() const {
		return level;
	}

	void setModifier(int lootModifier) {
		modifier = Math::clamp((int)(STATIC), lootModifier, (int)(LEGENDARY+EXPERIMENTAL));
	}

	void setLevel(int lootLevel) {
		level = Math::clamp((int)(LEVELMIN), lootLevel, (int)(LEVELMAX));
	}

	void setModifier(const LootItemTemplate* lootTemplate, float lootModifier);

	void setLevel(const LootItemTemplate* lootTemplate, int lootLevel);

	void recalculateValues(bool initial);

private:
	inline void setStaticValues();

	inline void setRandomValues();

	inline void setDamageValues();

	inline void setStaticValue(const String& attribute);

	template<typename Auto = float>
	inline void setUniformValue(const String& attribute);

	template<typename Auto = float>
	inline void setDynamicValue(const String& attribute, float percentageMax);

	inline void setModifierValue(const String& attribute, float percentageMax);

public:
	static float getModifierValue(float min, float max, float percentageMax);

	static float getPercentageValue(float min, float max, float percentage);

	static float getValuePercentage(float min, float max, float value);

	static float getRandomValue(float min, float max);

	static int getRandomValue(int min, int max);

	static float getDistributedValue(float min, float max, int level, float distMin = 0.f, float distMax = 1.f);

	static int getDistributedValue(int min, int max, int level, float distMin = 0.f, float distMax = 1.f);

	static float getLevelRankValue(int level, float distMin = 0.f, float distMax = 1.f);

#ifdef LOOTVALUES_DEBUG
	void debugAttributes(TangibleObject* prototype, const LootItemTemplate* itemTemplate) {
		if (modifier <= 0.f && dynamicValues <= 0) {
			return;
		}

		prototype->setCustomObjectName(itemTemplate->getCustomObjectName(), false);

		if (modifier > EXCEPTIONAL+1) {
			prototype->setCustomObjectName(prototype->getDisplayedName() + " (Legendary)", false);
		} else if (modifier > ENHANCED+1) {
			prototype->setCustomObjectName(prototype->getDisplayedName() + " (Exceptional)", false);
		} else if (modifier > EXPERIMENTAL+1) {
			prototype->setCustomObjectName(prototype->getDisplayedName() + " (Enhanced)", false);
		} else if (modifier > STATIC) {
			prototype->setCustomObjectName(prototype->getDisplayedName() + " (Experimental)", false);
		}

		StringBuffer msg;

		msg << prototype->getDisplayedName() << endl << endl
			<< "LootItemTemplate: " << endl
			<< "  LootItemName:   " << itemTemplate->getTemplateName() << endl
			<< "  ObjectPath:     " << itemTemplate->getDirectObjectTemplate() << endl
			<< "  ObjectType:     " << "0x" << String::hexvalueOf(itemTemplate->getObjectType()) << endl
			<< "  LevelMax:       " << itemTemplate->getLevelMax() << endl
			<< "  LevelMin:       " << itemTemplate->getLevelMin() << endl << endl
			<< "-------------------------------------------------------------------------------------" << endl
			<< toDebugString();

		prototype->setCustomObjectName(msg.toString(), false);
	}

	String toDebugString() {
		StringBuffer msg, buf;

		for (int i = 1; i < RandomType::SIZE; ++i) {
			String typeStr = randomTypeToString(i);

			for (int ii = 0; ii < getTotalExperimentalAttributes(); ++ii) {
				const String& attribute = getAttribute(ii);
				if (!staticValues.hasExperimentalAttribute(attribute)) {
					continue;
				}

				int randomType = getCombineType(attribute);
				if (randomType != i) {
					continue;
				}

				float minMin = staticValues.getMinValue(attribute);
				float minMax = staticValues.getMaxValue(attribute);

				float maxMin = getMinValue(attribute);
				float maxMax = getMaxValue(attribute);

				float value = getCurrentValue(attribute);
				float percent = getCurrentPercentage(attribute);
				float percentMax = getMaxPercentage(attribute);

				String tab = getPrecision(attribute) % 10 ? "    " : "      ";

				buf << "  " << typeStr
					<< "    " << attribute
					<< tab << ((int)(minMin * 100) * 0.01f)
					<< tab << ((int)(minMax * 100) * 0.01f)
					<< tab << ((int)(maxMin * 100) * 0.01f)
					<< tab << ((int)(maxMax * 100) * 0.01f)
					<< tab << ((int)(value * 100) * 0.01f)
					<< tab << ((int)(percent * 100)) << "%"
					<< tab << ((int)(percentMax * 100)) << "%" << endl;
			}
		}

		if (buf.length() > 0) {
			msg << "AttributeValues: " << endl
				<< "  Level:         " << level << endl
				<< "  Modifier:      " << modifier << endl
				<< "  Attributes:    " << staticValues.getSize() << endl
				<< "  DynamicValues: " << dynamicValues << endl << endl
				<< "-------------------------------------------------------------------------------------" << endl
				<< "  randomType  attribute  minMin  minMax  maxMin  maxMax  value  percent  percentMax  " << endl
				<< "-------------------------------------------------------------------------------------" << endl
				<< buf.toString()
				<< "-------------------------------------------------------------------------------------" << endl;
		}

		return msg.toString();
	}
#endif // LOOTVALUES_DEBUG
};

#endif // LOOTVALUES_H_
