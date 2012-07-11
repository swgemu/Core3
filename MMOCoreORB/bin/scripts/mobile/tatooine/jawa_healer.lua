jawa_healer = Creature:new {
	objectName = "@mob/creature_names:jawa_healer",
	socialGroup = "jawa",
	pvpFaction = "jawa",
	faction = "jawa",
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
	creatureBitmask = PACK + HERD + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/jawa_male.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 7000000},
				{group = "tailor_components", chance = 1300000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "color_crystals", chance = 200000}
			},
			lootChance = 2900000
		}						
	},
	weapons = {"novice_weapons"},
	conversationTemplate = "",
	attacks = merge(marksmannovice)
}

CreatureTemplates:addCreatureTemplate(jawa_healer, "jawa_healer")
