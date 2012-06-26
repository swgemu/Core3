janta_herbalist = Creature:new {
	objectName = "@mob/creature_names:janta_herbalist",
	socialGroup = "janta_tribe",
	pvpFaction = "janta_tribe",
	faction = "janta_tribe",
	level = 27,
	chanceHit = 0.39,
	damageMin = 305,
	damageMax = 320,
	baseXp = 2730,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {-1,25,-1,25,25,25,25,-1,-1},
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
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dantari_male.iff",
		"object/mobile/dantari_female.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 6000000},
				{group = "janta_common", chance = 1000000},
				{group = "loot_kit_parts", chance = 3000000}
			},
			lootChance = 3500000
		}	
	},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(janta_herbalist, "janta_herbalist")
