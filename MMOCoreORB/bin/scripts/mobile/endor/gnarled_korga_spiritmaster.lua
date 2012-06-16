gnarled_korga_spiritmaster = Creature:new {
	objectName = "@mob/creature_names:gnarled_korga_spiritmaster",
	socialGroup = "korga_tribe",
	pvpFaction = "korga_tribe",
	faction = "korga_tribe",
	level = 33,
	chanceHit = 0.4,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3370,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {0,35,0,0,0,-1,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(gnarled_korga_spiritmaster, "gnarled_korga_spiritmaster")