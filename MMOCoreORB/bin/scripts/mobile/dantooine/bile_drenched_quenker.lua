bile_drenched_quenker = Creature:new {
	objectName = "@mob/creature_names:bile_drenched_quenker",
	socialGroup = "quenker",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.41,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3370,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {30,30,30,30,-1,30,30,-1,-1},
	meatType = "meat_wild",
	meatAmount = 65,
	hideType = "hide_scaley",
	hideAmount = 35,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bile_drenched_quenker.iff"},
	controlDeviceTemplate = "object/intangible/pet/quenker_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {"creature_spit_small_green"},
	conversationTemplate = "",
	attacks = {
		{"defaultattack",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bile_drenched_quenker, "bile_drenched_quenker")
