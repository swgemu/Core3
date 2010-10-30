sickly_decay_mite_queen = Creature:new {
	objectName = "@mob/creature_names:sickly_decay_mite_queen",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 1609,
	baseHAM = 3900,
	baseHAMmax = 3900,
	armor = 0,
	resists = {0,25,-1,-1,-1,-1,30,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/decay_mite.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"blindattack","blindChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(sickly_decay_mite_queen, "sickly_decay_mite_queen")