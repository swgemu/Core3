dark_jedi_master = Creature:new {
	objectName = "@mob/creature_names:dark_jedi_master",
	socialGroup = "Dark Jedi",
	pvpFaction = "",
	faction = "",
	level = 291,
	chanceHit = 27.25,
	damageMin = 1800,
	damageMax = 3310,
	baseXp = 27849,
	baseHAM = 321000,
	baseHAMmax = 392000,
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

	templates = {"object/mobile/dressed_dark_jedi_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "holocron_light", chance = 3500000},
				{group = "holocron_dark", chance = 3500000},
				{group = "rifles", chance = 1500000},
				{group = "pistols", chance = 1500000}
			},
			lootChance = 5300000
		}
	},
	weapons = {"dark_jedi_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dark_jedi_master, "dark_jedi_master")