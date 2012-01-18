zealot_of_lord_nyax = Creature:new {
	objectName = "@mob/creature_names:zealot_of_Lord_Nyax",
	socialGroup = "Lord Nyax",
	pvpFaction = "Lord Nyax",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2637,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {10,50,-1,40,-1,-1,40,-1,-1},
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
	lootChance = 4500000,

	templates = {},
	lootgroups = {
		{group = "nyax", chance = 2000000},
		{group = "pistols", chance = 4000000},
		{group = "rifles", chance = 4000000},
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(zealot_of_lord_nyax, "zealot_of_lord_nyax")