rhoa_kwi_hunter = Creature:new {
	objectName = "rhoa kwi hunter",
	socialGroup = "Rhoa Kwi",
	pvpFaction = "",
	faction = "",
	level = 43,
	chanceHit = 0.440000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4279,
	baseHAM = 9900,
	baseHAMmax = 9900,
	armor = 0,
	resists = {40,55,0,80,0,0,-1,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 86,
	boneType = "bone_mammal",
	boneAmount = 76,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rhoa_kwi_hunter, "rhoa_kwi_hunter")