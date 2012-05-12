borvos_soldier = Creature:new {
	objectName = "",
	customName = "Borvo's Soldier",
	socialGroup = "borvo",
	pvpFaction = "borvo",
	faction = "borvo",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
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
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_borvos_soldier.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "color_crystals", chance = 500000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kits", chance = 1500000},
				{group = "rilfes", chance = 1750000},
				{group = "carbines", chance = 1750000}
			},
			lootChance = 4800000
		}				
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(borvos_soldier, "borvos_soldier")