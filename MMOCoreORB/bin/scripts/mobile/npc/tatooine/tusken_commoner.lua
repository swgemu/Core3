tusken_commoner = Creature:new {
	objectName = "@mob/creature_names:tusken_commoner",
	socialGroup = "Tusken Raider",
	pvpFaction = "Tusken Raider",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {5,5,5,5,5,5,5,5,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,
	lootChance = 3500000,

	templates = {"object/mobile/tusken_raider.iff"},
	lootgroups = {
		{group = "tusken", chance = 10000000}
	},
	weapons = {"tusken_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(tusken_commoner, "tusken_commoner")