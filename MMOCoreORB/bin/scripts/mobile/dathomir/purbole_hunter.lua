purbole_hunter = Creature:new {
	objectName = "@mob/creature_names:purbole_hunter",
	socialGroup = "purbole",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 2006,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {125,125,5,-1,-1,145,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/purbole_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/purbole_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(purbole_hunter, "purbole_hunter")
