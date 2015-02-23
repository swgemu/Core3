elder_pulverizer = Creature:new {
	objectName = "@mob/creature_names:bolle_bol_elder_pulverizer",
	socialGroup = "bol",
	faction = "",
	level = 30,
	chanceHit = 0.35,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3005,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {125,125,15,15,115,-1,115,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 450,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bolle_bol_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/bolle_bol_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"knockdownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(elder_pulverizer, "elder_pulverizer")
