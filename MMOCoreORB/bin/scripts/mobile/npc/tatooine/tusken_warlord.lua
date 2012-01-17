tusken_warlord = Creature:new {
	objectName = "@mob/creature_names:tusken_warlord",
	socialGroup = "Tusken Raider",
	pvpFaction = "Tusken Raider",
	faction = "",
	level = 62,
	chanceHit = 0.62,
	damageMin = 455,
	damageMax = 620,
	baseXp = 6013,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {45,25,15,80,-1,40,-1,15,-1},
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
	lootChance = 6000000,

	templates = {"object/mobile/tusken_raider.iff"},
	lootgroups = {
		{group = "tusken", chance = 6500000},
		{group = "rifles", chance = 1750000},
		{group = "pistols", chance = 1750000}
	},
	weapons = {"tusken_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(tusken_warlord, "tusken_warlord")