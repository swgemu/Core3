kliknik_hunter = Creature:new {
	objectName = "@mob/creature_names:kliknik_hunter",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.390000,
	damageMin = 300,
	damageMax = 310,
	baseXp = 3279,
	baseHAM = 9400,
	baseHAMmax = 9400,
	armor = 0,
	resists = {40,35,0,0,0,-1,-1,-1,-1},
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
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_hunter, "kliknik_hunter")