rebel_specforce_pathfinder = Creature:new {
	objectName = "@mob/creature_names:rebel_specforce_pathfinder",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 18,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {10,10,5,5,5,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_specforce_pathfinder_human_male_01.iff",
		"object/mobile/dressed_rebel_specforce_pathfinder_moncal_female_01.iff",
		"object/mobile/dressed_rebel_specforce_pathfinder_rodian_female_01.iff",
		"object/mobile/dressed_rebel_specforce_pathfinder_twk_female_01.iff",
		"object/mobile/dressed_rebel_specforce_pathfinder_twk_male_01.iff",
		"object/mobile/dressed_rebel_specforce_pathfinder_zabrak_female_fat_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 3600000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 4000000
		}				
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(rebel_specforce_pathfinder, "rebel_specforce_pathfinder")