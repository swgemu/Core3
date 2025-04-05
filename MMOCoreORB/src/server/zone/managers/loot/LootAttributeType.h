#ifndef LOOTATTRIBUTETYPE_H_
#define LOOTATTRIBUTETYPE_H_

#include "server/zone/objects/tangible/TangibleObject.h"

class LootAttributeType {
public:
	enum RandomType : uint32 {
		STATIC,
		UNIFORM,
		DYNAMIC,
		NORMAL,
		SIZE,
	};

	static String randomTypeToString(uint32 type) {
		switch (type) {
			case RandomType::STATIC: return "static";
			case RandomType::UNIFORM: return "uniform";
			case RandomType::DYNAMIC: return "dynamic";
			case RandomType::NORMAL: return "normal";
			default: return "null";
		}
	}

	static int getAttributeType(uint32 objectType, const String& attribute) {
		uint32 attributeCRC = attribute.toLowerCase().hashCode();

		if (objectType & SceneObjectType::COMPONENT) {
			return getComponentAttributeType(objectType, attribute);
		} else {
			return getObjectAttributeType(objectType, attribute);
		}
	}

	static int getComponentAttributeType(uint32 objectType, const String& attribute) {
		uint32 attributeCRC = attribute.toLowerCase().hashCode();

		if (objectType == SceneObjectType::ARMORCOMPONENT) {
			switch (attributeCRC) {
				case String::hashCode("armor_effectiveness"):			return RandomType::DYNAMIC;
				case String::hashCode("armor_integrity"):				return RandomType::DYNAMIC;
				case String::hashCode("armor_health_encumbrance"):		return RandomType::DYNAMIC;
				case String::hashCode("armor_action_encumbrance"):		return RandomType::DYNAMIC;
				case String::hashCode("armor_mind_encumbrance"):		return RandomType::DYNAMIC;
				case String::hashCode("armor_special_effectiveness"):	return RandomType::DYNAMIC;
				case String::hashCode("kineticeffectiveness"):			return RandomType::DYNAMIC;
				case String::hashCode("energyeffectiveness"):			return RandomType::DYNAMIC;
				case String::hashCode("electricaleffectiveness"):		return RandomType::DYNAMIC;
				case String::hashCode("stuneffectiveness"):				return RandomType::DYNAMIC;
				case String::hashCode("blasteffectiveness"):			return RandomType::DYNAMIC;
				case String::hashCode("heateffectiveness"):				return RandomType::DYNAMIC;
				case String::hashCode("coldeffectiveness"):				return RandomType::DYNAMIC;
				case String::hashCode("acideffectiveness"):				return RandomType::DYNAMIC;
				case String::hashCode("restraineffectiveness"):			return RandomType::DYNAMIC;
				case String::hashCode("usecount"):						return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType == SceneObjectType::CHEMISTRYCOMPONENT) {
			switch (attributeCRC) {
				case String::hashCode("power"):							return RandomType::DYNAMIC;
				case String::hashCode("charges"):						return RandomType::DYNAMIC;
				case String::hashCode("area"):							return RandomType::DYNAMIC;
				case String::hashCode("range"):							return RandomType::DYNAMIC;
				case String::hashCode("potency"):						return RandomType::DYNAMIC;
				case String::hashCode("duration"):						return RandomType::DYNAMIC;
				case String::hashCode("usecount"):						return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType == SceneObjectType::MELEEWEAPONCOMPONENT) {
			switch (attributeCRC) {
				case String::hashCode("armor_effectiveness"):			return RandomType::DYNAMIC;
				case String::hashCode("armor_integrity"):				return RandomType::DYNAMIC;
				case String::hashCode("armor_health_encumbrance"):		return RandomType::DYNAMIC;
				case String::hashCode("armor_action_encumbrance"):		return RandomType::DYNAMIC;
				case String::hashCode("armor_mind_encumbrance"):		return RandomType::DYNAMIC;
				case String::hashCode("hitpoints"):						return RandomType::DYNAMIC;
				case String::hashCode("mindamage"):						return RandomType::DYNAMIC;
				case String::hashCode("maxdamage"):						return RandomType::DYNAMIC;
				case String::hashCode("attackspeed"):					return RandomType::DYNAMIC;
				case String::hashCode("woundchance"):					return RandomType::DYNAMIC;
				case String::hashCode("zerorangemod"):					return RandomType::DYNAMIC;
				case String::hashCode("maxrangemod"):					return RandomType::DYNAMIC;
				case String::hashCode("midrangemod"):					return RandomType::DYNAMIC;
				case String::hashCode("attackhealthcost"):				return RandomType::DYNAMIC;
				case String::hashCode("attackactioncost"):				return RandomType::DYNAMIC;
				case String::hashCode("attackmindcost"):				return RandomType::DYNAMIC;
				case String::hashCode("usecount"):						return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType == SceneObjectType::MUNITIONCOMPONENT) {
			switch (attributeCRC) {
				case String::hashCode("hitpoints"):						return RandomType::DYNAMIC;
				case String::hashCode("mindamage"):						return RandomType::DYNAMIC;
				case String::hashCode("maxdamage"):						return RandomType::DYNAMIC;
				case String::hashCode("attackspeed"):					return RandomType::DYNAMIC;
				case String::hashCode("woundchance"):					return RandomType::DYNAMIC;
				case String::hashCode("zerorangemod"):					return RandomType::DYNAMIC;
				case String::hashCode("maxrangemod"):					return RandomType::DYNAMIC;
				case String::hashCode("midrangemod"):					return RandomType::DYNAMIC;
				case String::hashCode("attackhealthcost"):				return RandomType::DYNAMIC;
				case String::hashCode("attackactioncost"):				return RandomType::DYNAMIC;
				case String::hashCode("attackmindcost"):				return RandomType::DYNAMIC;
				case String::hashCode("usecount"):						return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType == SceneObjectType::RANGEDWEAPONCOMPONENT) {
			switch (attributeCRC) {
				case String::hashCode("hitpoints"):						return RandomType::DYNAMIC;
				case String::hashCode("mindamage"):						return RandomType::DYNAMIC;
				case String::hashCode("maxdamage"):						return RandomType::DYNAMIC;
				case String::hashCode("attackspeed"):					return RandomType::DYNAMIC;
				case String::hashCode("woundchance"):					return RandomType::DYNAMIC;
				case String::hashCode("midrangemod"):					return RandomType::DYNAMIC;
				case String::hashCode("attackhealthcost"):				return RandomType::DYNAMIC;
				case String::hashCode("attackactioncost"):				return RandomType::DYNAMIC;
				case String::hashCode("attackmindcost"):				return RandomType::DYNAMIC;
				case String::hashCode("usecount"):						return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType == SceneObjectType::DE10BARRELCOMPONENT) {
			switch (attributeCRC) {
				case String::hashCode("hitpoints"):						return RandomType::DYNAMIC;
				case String::hashCode("mindamage"):						return RandomType::DYNAMIC;
				case String::hashCode("maxdamage"):						return RandomType::DYNAMIC;
				case String::hashCode("attackspeed"):					return RandomType::DYNAMIC;
				case String::hashCode("woundchance"):					return RandomType::DYNAMIC;
				case String::hashCode("midrangemod"):					return RandomType::DYNAMIC;
				case String::hashCode("attackhealthcost"):				return RandomType::DYNAMIC;
				case String::hashCode("attackactioncost"):				return RandomType::DYNAMIC;
				case String::hashCode("attackmindcost"):				return RandomType::DYNAMIC;
				case String::hashCode("usecount"):						return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType == SceneObjectType::LIGHTSABERCRYSTAL) {
			switch (attributeCRC) {
				case String::hashCode("color"):							return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType == SceneObjectType::COMPONENT) {
			switch (attributeCRC) {
				case String::hashCode("usecount"):						return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		return RandomType::STATIC;
	}

	static int getObjectAttributeType(uint32 objectType, const String& attribute) {
		uint32 attributeCRC = attribute.toLowerCase().hashCode();

		if (objectType & SceneObjectType::WEAPON) {
			switch (attributeCRC) {
				case String::hashCode("mindamage"):						return RandomType::DYNAMIC;
				case String::hashCode("maxdamage"):						return RandomType::DYNAMIC;
				case String::hashCode("attackspeed"):					return RandomType::DYNAMIC;
				case String::hashCode("woundchance"):					return RandomType::DYNAMIC;
				case String::hashCode("attackhealthcost"):				return RandomType::DYNAMIC;
				case String::hashCode("attackactioncost"):				return RandomType::DYNAMIC;
				case String::hashCode("attackmindcost"):				return RandomType::DYNAMIC;
				default:												return RandomType::STATIC;
			}
		}

		if ((objectType & SceneObjectType::ARMOR)) {
			switch (attributeCRC) {
				case String::hashCode("armor_effectiveness"):			return RandomType::DYNAMIC;
				case String::hashCode("armor_integrity"):				return RandomType::DYNAMIC;
				case String::hashCode("armor_health_encumbrance"):		return RandomType::DYNAMIC;
				case String::hashCode("armor_action_encumbrance"):		return RandomType::DYNAMIC;
				case String::hashCode("armor_mind_encumbrance"):		return RandomType::DYNAMIC;
				case String::hashCode("armor_special_effectiveness"):	return RandomType::DYNAMIC;
				case String::hashCode("kineticeffectiveness"):			return RandomType::DYNAMIC;
				case String::hashCode("energyeffectiveness"):			return RandomType::DYNAMIC;
				case String::hashCode("electricaleffectiveness"):		return RandomType::DYNAMIC;
				case String::hashCode("stuneffectiveness"):				return RandomType::DYNAMIC;
				case String::hashCode("blasteffectiveness"):			return RandomType::DYNAMIC;
				case String::hashCode("heateffectiveness"):				return RandomType::DYNAMIC;
				case String::hashCode("coldeffectiveness"):				return RandomType::DYNAMIC;
				case String::hashCode("acideffectiveness"):				return RandomType::DYNAMIC;
				case String::hashCode("restraineffectiveness"):			return RandomType::DYNAMIC;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType == SceneObjectType::PHARMACEUTICAL) {
			switch (attributeCRC) {
				case String::hashCode("power"):							return RandomType::DYNAMIC;
				case String::hashCode("charges"):						return RandomType::DYNAMIC;
				case String::hashCode("area"):							return RandomType::DYNAMIC;
				case String::hashCode("range"):							return RandomType::DYNAMIC;
				case String::hashCode("potency"):						return RandomType::DYNAMIC;
				case String::hashCode("duration"):						return RandomType::DYNAMIC;
				case String::hashCode("usecount"):						return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType == SceneObjectType::RESOURCECONTAINER) {
			switch (attributeCRC) {
				case String::hashCode("quantity"):						return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType == SceneObjectType::FISHINGBAIT) {
			switch (attributeCRC) {
				case String::hashCode("quantity"):						return RandomType::UNIFORM;
				default:												return RandomType::STATIC;
			}
		}

		if (objectType & SceneObjectType::SHIPATTACHMENT) {
			switch (attributeCRC) {
				case String::hashCode("reverseengineeringlevel"):		return RandomType::STATIC;
				default:												return RandomType::NORMAL;
			}
		}

		return RandomType::STATIC;
	}
};

#endif //LOOTATTRIBUTETYPE_H_
