canyon_corsair_cutthroat = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_cutthroat",
	socialGroup = "Corsair",
	pvpFaction = "Corsair",
	faction = "",
	level = 35,
	chanceHit = 0.4,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3551,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,45,0,0,-1,0,0,-1,-1},
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

	templates = {"object/mobile/dressed_corsair_cutthroat_zab_m.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(canyon_corsair_cutthroat, "canyon_corsair_cutthroat")