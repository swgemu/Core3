etheli_drenel = Creature:new {
	objectName = "@npc_name:bothan_base_male",
	customName = "Etheli Dre'nel",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 8,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {5,5,5,0,0,0,0,-1,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/dressed_noble_bothan_male_01.iff"},
	lootGroups = { },
	conversationTemplate = "",
	attacks = {	}
}

CreatureTemplates:addCreatureTemplate(etheli_drenel, "etheli_drenel")