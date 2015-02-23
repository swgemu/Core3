stout_ikopi_buck = Creature:new {
	objectName = "@mob/creature_names:ikopi_stout_stallion",
	socialGroup = "ikopi",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {110,0,-1,0,0,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 70,
	hideType = "hide_bristley",
	hideAmount = 60,
	boneType = "bone_mammal",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/ikopi_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/ikopi_hue.iff",
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(stout_ikopi_buck, "stout_ikopi_buck")
