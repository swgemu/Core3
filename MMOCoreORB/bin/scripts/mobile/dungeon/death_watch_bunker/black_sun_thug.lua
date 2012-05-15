black_sun_thug = Creature:new {
	objectName = "@mob/creature_names:mand_bunker_blksun_thug",
	socialGroup = "death_watch",
	pvpFaction = "death_watch",
	faction = "",
	level = 86,
	chanceHit = 0.85,
	damageMin = 570,
	damageMax = 850,
	baseXp = 8130,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 1,
	resists = {40,40,60,35,55,70,35,40,-1},
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

	templates = {"object/mobile/dressed_black_sun_thug.iff"},
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

CreatureTemplates:addCreatureTemplate(black_sun_thug, "black_sun_thug")