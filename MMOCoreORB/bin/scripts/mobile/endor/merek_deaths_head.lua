merek_deaths_head = Creature:new {
	objectName = "@mob/creature_names:merek_deaths_head",
	socialGroup = "merek",
	pvpFaction = "",
	faction = "",
	level = 56,
	chanceHit = 0.55,
	damageMin = 480,
	damageMax = 670,
	baseXp = 5464,
	baseHAM = 9900,
	baseHAMmax = 12100,
	armor = 0,
	resists = {10,10,10,10,10,10,10,10,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/merek.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongdisease",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(merek_deaths_head, "merek_deaths_head")