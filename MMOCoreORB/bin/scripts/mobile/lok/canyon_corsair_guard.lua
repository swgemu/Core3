canyon_corsair_guard = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_guard",
	socialGroup = "canyon_corsair",
	pvpFaction = "canyon_corsair",
	faction = "canyon_corsair",
	level = 36,
	chanceHit = 0.42,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3642,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {25,60,25,-1,-1,-1,25,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_corsair_guard_hum_f.iff",
		"object/mobile/dressed_corsair_guard_hum_m.iff",
		"object/mobile/dressed_corsair_guard_nikto_m.iff",
		"object/mobile/dressed_corsair_guard_rod_m.iff"
		},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(canyon_corsair_guard, "canyon_corsair_guard")