twisted_pubam_scavenger = Creature:new {
	objectName = "@mob/creature_names:twisted_pubam_scavenger",
	socialGroup = "pubam",
	pvpFaction = "pubam",
	faction = "pubam",
	level = 34,
	chanceHit = 0.41,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3460,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,20,20,20,20,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
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

CreatureTemplates:addCreatureTemplate(twisted_pubam_scavenger, "twisted_pubam_scavenger")