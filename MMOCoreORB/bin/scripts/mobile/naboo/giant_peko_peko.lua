giant_peko_peko = Creature:new {
	objectName = "@mob/creature_names:giant_peko_peko",
	socialGroup = "peko",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2219,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {10,25,50,-1,-1,50,-1,-1,-1},
	meatType = "meat_avian",
	meatAmount = 155,
	hideType = "hide_wooly",
	hideAmount = 70,
	boneType = "bone_avian",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0,
	ferocity = 8,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,
	scale = 1.4,

	templates = {"object/mobile/giant_peko_peko.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_peko_peko, "giant_peko_peko")