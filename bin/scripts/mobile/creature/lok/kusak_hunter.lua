kusak_hunter = Creature:new {
	objectName = "@mob/creature_names:kusak_hunter",
	socialGroup = "Kusak",
	pvpFaction = "",
	faction = "",
	level = 73,
	chanceHit = 0.750000,
	damageMin = 570,
	damageMax = 850,
	baseXp = 7023,
	baseHAM = 13500,
	baseHAMmax = 13500,
	armor = 0,
	resists = {40,0,0,-1,-1,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 20,
	hideType = "hide_bristley",
	hideAmount = 14,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kusak.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kusak_hunter, "kusak_hunter")