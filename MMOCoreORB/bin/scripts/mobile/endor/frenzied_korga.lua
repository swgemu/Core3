frenzied_korga = Creature:new {
	objectName = "@mob/creature_names:frenzied_korga",
	socialGroup = "korga_tribe",
	pvpFaction = "korga_tribe",
	faction = "korga_tribe",
	level = 35,
	chanceHit = 0.41,
	damageMin = 355,
	damageMax = 420,
	baseXp = 3551,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {0,0,0,60,60,-1,0,-1,-1},
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

	templates = {
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(frenzied_korga, "frenzied_korga")