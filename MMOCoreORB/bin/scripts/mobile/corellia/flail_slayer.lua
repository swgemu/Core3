flail_slayer = Creature:new {
	objectName = "@mob/creature_names:flail_slayer",
	socialGroup = "flail",
	pvpFaction = "flail",
	faction = "flail",
	level = 20,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_ravager_human_female_01.iff",
		"object/mobile/dressed_ravager_human_male_01.iff",
		"object/mobile/dressed_raider_trandoshan_female_01.iff",
		"object/mobile/dressed_raider_trandoshan_male_01.iff",
		"object/mobile/dressed_villain_trandoshan_female_01.iff",
		"object/mobile/dressed_villain_trandoshan_male_01.iff"},
	lootGroups = {
	 	{
			groups = {
				{group = "junk", chance = 3500000},
				{group = "wearables_common", chance = 3000000},
				{group = "rifles", chance = 2000000},
				{group = "color_crystals", chance = 1000000},
				{group = "flail_common", chance = 500000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"pirate_weapons_medium"},
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(flail_slayer, "flail_slayer")
