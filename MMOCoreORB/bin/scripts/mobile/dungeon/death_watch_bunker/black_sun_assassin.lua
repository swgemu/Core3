black_sun_assassin = Creature:new {
	objectName = "@mob/creature_names:mand_bunker_blksun_assassin",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 107,
	chanceHit = 1.75,
	damageMin = 670,
	damageMax = 1050,
	baseXp = 10081,
	baseHAM = 29000,
	baseHAMmax = 36000,
	armor = 2,
	resists = {55,55,70,45,75,80,55,45,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_black_sun_assassin.iff"},
	lootGroups = {
        {
			groups = {
				{group = "pistols", chance =   3100000},
				{group = "rifles", chance = 3100000},
				{group = "carbines", chance =  3100000},
				{group = "bounty_hunter_armor_looted",chance = 500000},
				{group = "jetpack_base", chance = 200000},
			},
			lootChance = 3500000
		}	
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(black_sun_assassin, "black_sun_assassin")