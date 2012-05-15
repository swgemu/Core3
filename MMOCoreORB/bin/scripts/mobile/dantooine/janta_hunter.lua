janta_hunter = Creature:new {
	objectName = "@mob/creature_names:janta_hunter",
	socialGroup = "janta_tribe",
	pvpFaction = "janta_tribe",
	faction = "janta_tribe",
	level = 50,
	chanceHit = 0.5,
	damageMin = 415,
	damageMax = 540,
	baseXp = 4916,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {5,5,-1,-1,5,60,-1,-1,-1},
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
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dantari_male.iff",
		"object/mobile/dantari_female.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "janta_common", chance = 5000000},
				{group = "loot_kits", chance = 5000000}
			},
			lootChance = 4800000
		}	
	},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(janta_hunter, "janta_hunter")
