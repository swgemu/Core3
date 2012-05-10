strong_mercenary = Creature:new {
	objectName = "@mob/creature_names:mercenary_strong",
	socialGroup = "lok_mercenaries",
	pvpFaction = "lok_mercenaries",
	faction = "lok_mercenaries",
	level = 36,
	chanceHit = 0.42,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3642,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {40,35,25,-1,25,25,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dressed_mercenary_strong_hum_m.iff",
			"object/mobile/dressed_mercenary_strong_hum_f.iff",
			"object/mobile/dressed_mercenary_strong_rod_m.iff",
			"object/mobile/dressed_mercenary_strong_tran_m.iff"
			},
	lootGroups = {},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(strong_mercenary, "strong_mercenary")