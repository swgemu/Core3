graul_mangler = Creature:new {
	objectName = "@mob/creature_names:graul_mangler",
	socialGroup = "graul",
	pvpFaction = "",
	faction = "",
	level = 39,
	chanceHit = 0.43,
	damageMin = 340,
	damageMax = 390,
	baseXp = 3915,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {140,115,160,160,160,25,-1,25,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 875,
	boneType = "bone_mammal",
	boneAmount = 775,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/graul_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/graul_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(graul_mangler, "graul_mangler")
