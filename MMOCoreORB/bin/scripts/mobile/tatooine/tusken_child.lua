tusken_child = Creature:new {
	objectName = "@mob/creature_names:tusken_child",
	socialGroup = "tusken_raider",
	faction = "tusken_raider",
	level = 8,
	chanceHit = 0.31,
	damageMin = 65,
	damageMax = 70,
	baseXp = 195,
	baseHAM = 410,
	baseHAMmax = 440,
	armor = 0,
	resists = {0,0,5,0,0,5,0,0,-1},
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

	templates = {"object/mobile/tusken_raider.iff"},
	scale = .65;
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3500000},
				{group = "tusken_common", chance = 3000000},
				{group = "wearables_common", chance = 2000000},				
				{group = "bone_armor", chance = 750000},
				{group = "chitin_armor", chance = 750000},
			},
			lootChance = 2200000
		}
	},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(tusken_child, "tusken_child")
