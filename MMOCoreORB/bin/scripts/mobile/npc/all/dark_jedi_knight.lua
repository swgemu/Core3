dark_jedi_knight = Creature:new {
	objectName = "@mob/creature_names:Dark_jedi_knight",
	socialGroup = "Dark Jedi",
	pvpFaction = "",
	faction = "",
	level = 265,
	chanceHit = 23.5,
	damageMin = 1645,
	damageMax = 3000,
	baseXp = 25266,
	baseHAM = 261000,
	baseHAMmax = 320000,
	armor = 3,
	resists = {90,90,90,90,90,90,90,90,-1},
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
	creatureBitmask = KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,
	lootChance = 5000000,

	templates = {"object/mobile/dressed_dark_jedi_human_male_01.iff"},
	lootgroups = {
		{group = "holocron_light", chance = 3500000},
		{group = "holocron_dark", chance = 3500000},
		{group = "rifles", chance = 1500000},
		{group = "pistols", chance = 1500000}
	},
	weapons = {"dark_jedi_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dark_jedi_knight, "dark_jedi_knight")