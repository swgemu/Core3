vile_korga_battlelord = Creature:new {
	objectName = "@mob/creature_names:vile_korga_battlelord",
	socialGroup = "korga_tribe",
	pvpFaction = "korga_tribe",
	faction = "korga_tribe",
	level = 38,
	chanceHit = 0.43,
	damageMin = 375,
	damageMax = 460,
	baseXp = 3824,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 1,
	resists = {65,-1,10,50,50,-1,10,-1,-1},
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
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(vile_korga_battlelord, "vile_korga_battlelord")
