herald_corellia_karin = Creature:new {
	objectName = "@npc_name:corellia_herald_02",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_herald_corellia_02.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "heraldConvoTemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(herald_corellia_karin, "herald_corellia_karin")
