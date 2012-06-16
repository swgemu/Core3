enraged_defender = Creature:new {
	objectName = "@mob/creature_names:piket_enraged_defender",
	socialGroup = "piket",
	pvpFaction = "",
	faction = "",
	level = 49,
	chanceHit = 0.47,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4734,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 1,
	resists = {40,40,20,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/piket.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_defender, "enraged_defender")