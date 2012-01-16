haggard_pubam_battlelord = Creature:new {
	objectName = "@mob/creature_names:haggard_pubam_battlelord",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 44,
	chanceHit = 0.5,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4370,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {-1,-1,40,40,40,-1,-1,100,-1},
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

	templates = {"object/mobile/dulok_male.iff"},
	lootgroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(haggard_pubam_battlelord, "haggard_pubam_battlelord")