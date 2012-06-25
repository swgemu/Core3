imperial_cadet = Creature:new {
	objectName = "@mob/creature_names:imperial_cadet",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_soldier_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3600000},
				{group = "tailor_components", chance = 1000000},
				{group = "loot_kit_parts", chance = 1000000},
			},
			lootChance = 4000000
		}					
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(imperial_cadet, "imperial_cadet")