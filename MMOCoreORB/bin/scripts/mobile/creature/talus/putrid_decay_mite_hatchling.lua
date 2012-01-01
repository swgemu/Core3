putrid_decay_mite_hatchling = Creature:new {
	objectName = "@mob/creature_names:putrid_decay_mite_hatchling",
	socialGroup = "Decay Mite",
	pvpFaction = "",
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/putrid_decay_mite_hatchling.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(putrid_decay_mite_hatchling, "putrid_decay_mite_hatchling")