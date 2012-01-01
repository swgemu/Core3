kliknik_queen = Creature:new {
	objectName = "@mob/creature_names:kliknik_queen",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3642,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {60,35,25,35,35,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 7,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_queen.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_queen, "kliknik_queen")