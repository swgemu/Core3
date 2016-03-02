tabage = Creature:new {
	objectName = "@mob/creature_names:tabage",
	socialGroup = "tabage",
	faction = "",
	level = 11,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 356,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {0,0,0,110,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 18,
	hideType = "hide_bristley",
	hideAmount = 24,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/tabage.iff"},
	controlDeviceTemplate = "object/intangible/pet/langlatch_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(tabage, "tabage")
