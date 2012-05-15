janta_harvester = Creature:new {
	objectName = "@mob/creature_names:janta_harvester",
	socialGroup = "janta_tribe",
	pvpFaction = "janta_tribe",
	faction = "janta_tribe",
	level = 40,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3915,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {0,0,-1,0,0,60,0,0,-1},
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

CreatureTemplates:addCreatureTemplate(janta_harvester, "janta_harvester")
