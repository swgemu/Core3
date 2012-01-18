dark_adept = Creature:new {
	objectName = "@mob/creature_names:Dark_adept",
	socialGroup = "Dark Jedi",
	pvpFaction = "",
	faction = "",
	level = 140,
	chanceHit = 4.75,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 13178,
	baseHAM = 50000,
	baseHAMmax = 61000,
	armor = 3,
	resists = {80,80,80,80,80,80,80,80,-1},
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
	lootChance = 4500000,

	templates = {"object/mobile/dressed_dark_jedi_human_male_01.iff"},
	lootgroups = {
		{group = "holocron_light", chance = 3500000},
		{group = "holocron_dark", chance = 3500000},
		{group = "rifles", chance = 1500000},
		{group = "pistols", chance = 1500000}
	},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dark_adept, "dark_adept")