dark_jedi_sentinel = Creature:new {
	objectName = "@mob/creature_names:Dark_jedi_sentinel",
	socialGroup = "self",
	pvpFaction = "self",
	faction = "",
	level = 300,
	chanceHit = 30,
	damageMin = 2645,
	damageMax = 5000,
	baseXp = 28532,
	baseHAM = 1106000,
	baseHAMmax = 1352000,
	armor = 3,
	resists = {95,95,95,95,95,95,95,95,-1},
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
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,
	lootChance = 500000,

	templates = {"object/mobile/dressed_dark_jedi_human_male_01.iff"},
	lootgroups = {
		{group = "holocron_dark", chance = 10000000}
	},
	weapons = {"dark_jedi_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dark_jedi_sentinel, "dark_jedi_sentinel")