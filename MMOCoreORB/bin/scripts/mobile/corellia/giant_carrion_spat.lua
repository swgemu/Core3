giant_carrion_spat = Creature:new {
	objectName = "@mob/creature_names:giant_carrion_spat",
	socialGroup = "carrion_spat",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1426,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {-1,25,5,45,45,-1,-1,-1,-1},
	meatType = "meat_avian",
	meatAmount = 350,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 295,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/giant_carrion_spat.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_carrion_spat, "giant_carrion_spat")