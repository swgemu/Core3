gruthashaal = Creature:new {
	objectName = "",
	socialGroup = "",
	faction = "",
	level = 40,
	chanceHit = 10,
	damageMin = 240,
	damageMax = 350,
	baseXp = 3250,
	baseHAM = 4500,
	baseHAMmax = 7800,
	armor = 3,
	resists = {5,5,5,5,5,5,5,5,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = { "object/mobile/dressed_commoner_naboo_human_female_08.iff"
		},

	lootGroups = {
		{
			groups = {
				{group = "task_loot_ancient_lightsaber", chance = 10000000},
				
			},
			lootChance = 10000000
		},
	},
	weapons = {},
	conversationTemplate = "",
	attacks = merge(tkamaster, brawlermaster)
}

CreatureTemplates:addCreatureTemplate(gruthashaal, "gruthashaal")
