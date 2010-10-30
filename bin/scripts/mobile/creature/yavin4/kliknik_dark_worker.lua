kliknik_dark_worker = Creature:new {
	objectName = "@mob/creature_names:kliknik_dark_worker",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {0,0,0,0,0,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_dark_worker, "kliknik_dark_worker")