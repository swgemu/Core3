veermok_cannibal = Creature:new {
	objectName = "@mob/creature_names:veermok_cannibal",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1257,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {115,-1,5,5,5,5,5,5,-1},
	meatType = "meat_carnivore",
	meatAmount = 150,
	hideType = "hide_bristley",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 150,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/veermok_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/veermok_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(veermok_cannibal, "veermok_cannibal")
