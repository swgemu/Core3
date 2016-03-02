mamien_jungle_lord = Creature:new {
	objectName = "@mob/creature_names:mamien_junglelord",
	socialGroup = "mamien",
	faction = "",
	level = 24,
	chanceHit = 0.35,
	damageMin = 180,
	damageMax = 190,
	baseXp = 2443,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {10,120,10,10,10,10,10,-1,-1},
	meatType = "meat_wild",
	meatAmount = 18,
	hideType = "hide_wooly",
	hideAmount = 18,
	boneType = "bone_mammal",
	boneAmount = 18,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mamien_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/mamien_hue.iff",
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(mamien_jungle_lord, "mamien_jungle_lord")
