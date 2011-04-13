kliknik_warrior = Creature:new {
	objectName = "@mob/creature_names:kliknik_warrior",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.340000,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2443,
	baseHAM = 6000,
	baseHAMmax = 6000,
	armor = 0,
	resists = {30,30,0,0,0,0,0,-1,-1},
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
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_warrior, "kliknik_warrior")