janta_tribesman = Creature:new {
	objectName = "@mob/creature_names:janta_tribesman",
	socialGroup = "janta_tribe",
	pvpFaction = "janta_tribe",
	faction = "janta_tribe",
	level = 20,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {0,15,0,-1,0,0,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(janta_tribesman, "janta_tribesman")
