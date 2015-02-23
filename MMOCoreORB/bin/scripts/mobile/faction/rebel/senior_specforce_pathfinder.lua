senior_specforce_pathfinder = Creature:new {
	objectName = "@mob/creature_names:senior_specforce_pathfinder",
	socialGroup = "rebel",
	faction = "rebel",
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_rebel_specforce_pathfinder_human_male_01.iff",
	             "object/mobile/dressed_rebel_specforce_pathfinder_moncal_female_01.iff",
	             "object/mobile/dressed_rebel_specforce_pathfinder_rodian_female_01.iff",
	             "object/mobile/dressed_rebel_specforce_pathfinder_twk_female_01.iff",
	             "object/mobile/dressed_rebel_specforce_pathfinder_twk_male_01.iff",
	             "object/mobile/dressed_rebel_specforce_pathfinder_zabrak_female_fat_01.iff",},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 4700000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000},
				{group = "wearables_common", chance = 1000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"imperial_weapons_medium"},
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",			
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(senior_specforce_pathfinder, "senior_specforce_pathfinder")
