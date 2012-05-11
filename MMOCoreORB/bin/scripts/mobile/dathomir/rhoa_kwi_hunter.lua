rhoa_kwi_hunter = Creature:new {
	objectName = "@mob/creature_names:rhoa_kwi_hunter",
	socialGroup = "kwi",
	pvpFaction = "",
	faction = "",
	level = 43,
	chanceHit = 0.44,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4279,
	baseHAM = 9000,
	baseHAMmax = 10900,
	armor = 0,
	resists = {40,55,30,80,30,30,-1,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 86,
	boneType = "bone_mammal",
	boneAmount = 76,
	milk = 0,
	tamingChance = 0,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rhoa_kwi_hunter, "rhoa_kwi_hunter")