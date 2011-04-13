giant_decay_mite_sentry = Creature:new {
	objectName = "@mob/creature_names:giant_decay_mite_sentry",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3200,
	baseHAMmax = 3200,
	armor = 0,
	resists = {20,20,-1,0,0,-1,-1,-1,-1},
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
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/decay_mite.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_sentry, "giant_decay_mite_sentry")