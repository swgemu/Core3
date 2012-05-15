famished_sludge_panther = Creature:new {
	objectName = "@mob/creature_names:famished_sludge_panther",
	socialGroup = "panther",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1609,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,20,5,-1,-1,-1,5,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_leathery",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 8,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/minor_sludge_panther.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(famished_sludge_panther, "famished_sludge_panther")