elder_pulverizer = Creature:new {
	objectName = "@mob/creature_names:elder_pulverizer",
	socialGroup = "Bolle Bol",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.35,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3005,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {25,25,15,15,15,-1,15,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 450,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bolle_bol.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_pulverizer, "elder_pulverizer")