forest_mite = Creature:new {
	objectName = "@mob/creature_names:forest_mite",
	socialGroup = "mite",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 160,
	damageMax = 170,
	baseXp = 714,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {0,25,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 5,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/forest_mite.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(forest_mite, "forest_mite")