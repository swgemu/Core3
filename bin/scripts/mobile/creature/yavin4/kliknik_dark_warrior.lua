kliknik_dark_warrior = Creature:new {
	objectName = "@mob/creature_names:kliknik_dark_warrior",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.430000,
	damageMin = 340,
	damageMax = 390,
	baseXp = 4006,
	baseHAM = 10200,
	baseHAMmax = 10200,
	armor = 0,
	resists = {60,40,0,0,0,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.150000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_dark_warrior, "kliknik_dark_warrior")