kliknik_dark_queen = Creature:new {
	objectName = "@mob/creature_names:kliknik_dark_queen",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3915,
	baseHAM = 10300,
	baseHAMmax = 10300,
	armor = 0,
	resists = {45,45,0,35,35,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 7,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_queen.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_dark_queen, "kliknik_dark_queen")