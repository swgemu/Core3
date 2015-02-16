librarian = Creature:new {
	objectName = "@mob/creature_names:trivia_librarian",
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 1,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 180,
	baseHAMmax = 220,
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
	creatureBitmask = NONE,
	optionsBitmask = 136,
	diet = HERBIVORE,

	-- TODO: Find correct template
	templates = {"object/mobile/dressed_theed_palace_chamberlain.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "librarian_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(librarian, "librarian")
