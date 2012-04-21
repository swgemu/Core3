fiend_of_lord_nyax = Creature:new {
	objectName = "@mob/creature_names:lord_nyax_fiend",
	socialGroup = "Lord Nyax",
	pvpFaction = "Lord Nyax",
	faction = "followers_of_lord_nyax",
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

	templates = {"object/mobile/dressed_dark_jedi_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 1000000},
				{group = "pistols", chance = 4500000},
				{group = "rifles", chance = 4500000}
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
