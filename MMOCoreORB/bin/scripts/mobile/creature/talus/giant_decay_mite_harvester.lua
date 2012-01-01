giant_decay_mite_harvester = Creature:new {
	objectName = "@mob/creature_names:giant_decay_mite_harvester",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 514,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {15,15,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 12,
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
	}
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_harvester, "giant_decay_mite_harvester")