giant_decay_mite_hatchliing = Creature:new {
	objectName = "@mob/creature_names:giant_decay_mite_hatchliing",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 187,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {10,10,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 5,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/decay_mite.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_hatchliing, "giant_decay_mite_hatchliing")