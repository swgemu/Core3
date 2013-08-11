morgo_one_shot = Creature:new {
	objectName = "",
	customName = "Morgo One-Shot",
	socialGroup = "corsec",
	pvpFaction = "corsec",
	faction = "corsec",
	level = 17,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 264,
	diet = HERBIVORE,
	templates = {
		"object/mobile/dressed_corsec_pilot_human_male_01.iff"
	},
	lootGroups = { },
	weapons = {},
	conversationTemplate = "diktatTargetConvo",
	attacks = { }
}

CreatureTemplates:addCreatureTemplate(morgo_one_shot, "morgo_one_shot")
