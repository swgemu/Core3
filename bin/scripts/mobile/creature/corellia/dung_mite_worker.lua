dung_mite_worker = Creature:new {
	objectName = "@mob/creature_names:sickening_dung_mite_worker",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 831,
	baseHAM = 2700,
	baseHAMmax = 2700,
	armor = 0,
	resists = {0,10,-1,0,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 11,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/dung_mite.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"stunattack","stunChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(dung_mite_worker, "dung_mite_worker")