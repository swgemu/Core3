canyon_corsair_elite_pirate = Creature:new {
	objectName = "@mob/creature_names:Canyon_Corsair_elite_pirate",
	socialGroup = "Corsair",
	pvpFaction = "Corsair",
	faction = "",
	level = 42,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4188,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {0,70,0,0,-1,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_corsair_pirate_elite_hum_f.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(canyon_corsair_elite_pirate, "canyon_corsair_elite_pirate")