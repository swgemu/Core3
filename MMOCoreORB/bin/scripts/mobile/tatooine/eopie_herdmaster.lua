eopie_herdmaster = Creature:new {
	objectName = "@mob/creature_names:eopie_herdmaster",
	socialGroup = "eopie",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 55,
	damageMax = 65,
	baseXp = 292,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,110,110,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 315,
	hideType = "hide_leathery",
	hideAmount = 250,
	boneType = "bone_mammal",
	boneAmount = 150,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/eopie.iff"},
	controlDeviceTemplate = "object/intangible/pet/eopie_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(eopie_herdmaster, "eopie_herdmaster")
