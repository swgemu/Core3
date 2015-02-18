pathfinder = Creature:new {
	objectName = "",
	costumName = "Pathfinder",
	socialGroup = "wilder",
	faction = "",
	level = 21,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 2006,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {0,0,0,35,35,35,35,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_thug_aqualish_male_01.iff",
			"object/mobile/dressed_criminal_thug_aqualish_male_02.iff",
			"object/mobile/dressed_criminal_thug_aqualish_female_01.iff",
			"object/mobile/dressed_criminal_thug_aqualish_female_02.iff",
			"object/mobile/dressed_criminal_thug_rodian_male_01.iff",
			"object/mobile/dressed_criminal_thug_rodian_female_01.iff", },
	lootGroups = {
      	{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 3000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
			},
			lootChance = 3000000
		}
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/townperson",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(pathfinder, "pathfinder")
