kliknik_dark_hunter = Creature:new {
	objectName = "@mob/creature_names:kliknik_dark_hunter",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.430000,
	damageMin = 350,
	damageMax = 410,
	baseXp = 3824,
	baseHAM = 9800,
	baseHAMmax = 9800,
	armor = 0,
	resists = {40,40,0,-1,0,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"strongpoison",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_dark_hunter, "kliknik_dark_hunter")