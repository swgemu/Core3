brigand_assassin = Creature:new {
	objectName = "@mob/creature_names:assassin",
	socialGroup = "brigand",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.32,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = 
		{
			"object/mobile/dressed_brigade_infiltrator_human_female_01.iff",
			"object/mobile/dressed_brigade_infiltrator_human_male_01.iff",
			"object/mobile/dressed_brigade_technician_human_female_01.iff",
			"object/mobile/dressed_brigade_technician_human_male_01.iff",
		},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 6000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000}
			},
			lootChance = 2400000
		}						
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(brigand_assassin, "brigand_assassin")
