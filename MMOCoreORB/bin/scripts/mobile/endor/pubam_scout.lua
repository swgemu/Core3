pubam_scout = Creature:new {
	objectName = "@mob/creature_names:pubam_scout",
	socialGroup = "pubam",
	pvpFaction = "pubam",
	faction = "pubam",
	level = 37,
	chanceHit = 0.47,
	damageMin = 370,
	damageMax = 450,
	baseXp = 3733,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {-1,-1,0,0,0,-1,-1,100,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(pubam_scout, "pubam_scout")