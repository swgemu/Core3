grungy_korga_laborer = Creature:new {
	objectName = "@mob/creature_names:grungy_korga_laborer",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "korga_tribe",
	faction = "korga_tribe",
	level = 26,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2730,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {20,25,0,50,50,-1,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dulok_male.iff",
		"object/mobile/dulok_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(grungy_korga_laborer, "grungy_korga_laborer")
