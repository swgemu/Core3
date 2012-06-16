vexed_voritor_lizard = Creature:new {
	objectName = "@mob/creature_names:vexed_voritor_lizard",
	socialGroup = "voritor",
	pvpFaction = "",
	faction = "",
	level = 52,
	chanceHit = 0.5,
	damageMin = 465,
	damageMax = 640,
	baseXp = 5007,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {35,-1,5,5,-1,-1,5,5,-1},
	meatType = "meat_carnivore",
	meatAmount = 50,
	hideType = "hide_leathery",
	hideAmount = 50,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 0,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/voritor_lizard.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(vexed_voritor_lizard, "vexed_voritor_lizard")