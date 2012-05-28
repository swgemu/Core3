flail_boss = Creature:new {
	objectName = "@mob/creature_names:flail_boss",
	socialGroup = "flail",
	pvpFaction = "flail",
	faction = "flail",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2730,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {20,25,0,-1,-1,0,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_thug_human_male_01.iff",
		"object/mobile/dressed_criminal_thug_human_male_02.iff",
		"object/mobile/dressed_criminal_thug_trandoshan_female_01.iff",
		"object/mobile/dressed_criminal_thug_trandoshan_male_01.iff",
		"object/mobile/dressed_criminal_thug_zabrak_female_01.iff",
		"object/mobile/dressed_criminal_thug_zabrak_male_01.iff"},
	lootGroups = {
			{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "rifles", chance = 1000000},
				{group = "color_crystals", chance = 500000}
			},
			lootChance = 5000000
		}
	},
	weapons = {"pirate_weapons_medium"},
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(flail_boss, "flail_boss")
