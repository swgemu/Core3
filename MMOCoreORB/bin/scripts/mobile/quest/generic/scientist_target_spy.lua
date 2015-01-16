scientist_target_spy = Creature:new {
	objectName = "@mob/creature_names:industrial_spy",
	socialGroup = "mercenary",
	pvpFaction = "",
	faction = "",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_criminal_smuggler_human_female_01.iff",
		"object/mobile/dressed_criminal_smuggler_human_male_01.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "task_loot_empty_cage", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"rebel_weapons_light"},
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(scientist_target_spy, "scientist_target_spy")