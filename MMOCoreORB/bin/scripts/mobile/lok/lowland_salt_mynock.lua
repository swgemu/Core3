lowland_salt_mynock = Creature:new {
	objectName = "@mob/creature_names:lowland_salt_mynock",
	socialGroup = "mynock",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2730,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {120,135,10,150,150,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 55,
	hideType = "hide_leathery",
	hideAmount = 73,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/salt_mynock_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/salt_mynock_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lowland_salt_mynock, "lowland_salt_mynock")
