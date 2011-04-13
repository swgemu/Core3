corellian_butterfly_defender = Creature:new {
	objectName = "corellian butterfly defender",
	socialGroup = "Cor. Butterfly",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1257,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {0,15,-1,-1,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 16,
	hideType = "",
	hideAmount = 16,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_butterfly_defender.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(corellian_butterfly_defender, "corellian_butterfly_defender")