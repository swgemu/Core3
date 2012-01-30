fiend_of_lord_nyax = Creature:new {
	objectName = "@mob/creature_names:lord_nyax_fiend",
	socialGroup = "Lord Nyax",
	pvpFaction = "Lord Nyax",
	faction = "",
	level = 29,
	chanceHit = 0.36,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3005,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {30,45,0,50,-1,-1,50,-1,-1},
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

	templates = {},
	lootGroups = {
		{
			groups = {
				{group = "nyax", chance = 2000000},
				{group = "pistols", chance = 4000000},
				{group = "rifles", chance = 4000000}
			},
			lootChance = 4900000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(fiend_of_lord_nyax, "fiend_of_lord_nyax")