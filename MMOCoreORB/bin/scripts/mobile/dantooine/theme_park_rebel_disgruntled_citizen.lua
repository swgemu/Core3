theme_park_rebel_disgruntled_citizen = Creature:new {
	objectName = "@mob/creature_names:bounty_hunter",
	socialGroup = "Mercenary",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2443,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {20,20,0,0,0,0,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_bountyhunter_trainer_01.iff",
				 "object/mobile/dressed_bountyhunter_trainer_02.iff",
				 "object/mobile/dressed_bountyhunter_trainer_03.iff"},
	lootGroups = 
	{
		{
			groups = {
				{group = "theme_park_loot_rebel_disgruntled_citizen", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(theme_park_rebel_disgruntled_citizen, "theme_park_rebel_disgruntled_citizen")