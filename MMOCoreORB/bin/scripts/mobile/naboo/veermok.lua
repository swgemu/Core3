veermok = Creature:new {
	objectName = "@mob/creature_names:veermok",
	socialGroup = "veermok",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 609,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {115,115,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 150,
	hideType = "hide_bristley",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 60,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/veermok.iff"},
	controlDeviceTemplate = "object/intangible/pet/veermok_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(veermok, "veermok")
