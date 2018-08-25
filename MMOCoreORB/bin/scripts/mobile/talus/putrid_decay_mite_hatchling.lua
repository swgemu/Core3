putrid_decay_mite_hatchling = Creature:new {
	objectName = "@mob/creature_names:putrid_decay_mite_hatchling",
	socialGroup = "mite",
	faction = "",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 147,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 4,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/putrid_decay_mite_hatchling.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 0.75,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(putrid_decay_mite_hatchling, "putrid_decay_mite_hatchling")
