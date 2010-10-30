kliknik_queen = Creature:new {
	objectName = "@mob/creature_names:kliknik_queen",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3642,
	baseHAM = 9800,
	baseHAMmax = 9800,
	armor = 0,
	resists = {60,35,0,35,35,-1,-1,-1,-1},
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
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_queen, "kliknik_queen")