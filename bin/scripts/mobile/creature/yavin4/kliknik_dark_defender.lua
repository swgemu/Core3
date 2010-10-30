kliknik_dark_defender = Creature:new {
	objectName = "@mob/creature_names:kliknik_dark_defender",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 42,
	chanceHit = 0.440000,
	damageMin = 360,
	damageMax = 430,
	baseXp = 4097,
	baseHAM = 10000,
	baseHAMmax = 10000,
	armor = 0,
	resists = {55,45,50,50,50,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 7,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.150000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"mildpoison",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_dark_defender, "kliknik_dark_defender")