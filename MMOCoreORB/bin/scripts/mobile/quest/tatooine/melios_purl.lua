melios_purl = Creature:new {
	objectName = "@theme_park_name:melious_purl",
	customName = "Melios Purl",
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 8,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
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
	optionsBitmask = INVULNERABLE + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/tatooine_npc/melios_purl.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "melios_purl_mission_giver_convotemplate",
	outfit = "melios_purl_outfit",
	scale = .85,
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(melios_purl, "melios_purl")
