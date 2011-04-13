kliknik_worker = Creature:new {
	objectName = "@mob/creature_names:kliknik_worker",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2219,
	baseHAM = 7550,
	baseHAMmax = 7550,
	armor = 0,
	resists = {0,25,0,0,-1,-1,-1,-1,-1},
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

CreatureTemplates:addCreatureTemplate(kliknik_worker, "kliknik_worker")