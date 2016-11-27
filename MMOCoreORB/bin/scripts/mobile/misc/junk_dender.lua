junk_dender = Creature:new {
	objectName = "@mob/creature_names:junk_dealer",
	customName = "Dender",
	planetMapCategory = "junkshop",
	socialGroup = "townsperson",
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
	optionsBitmask = INVULNERABLE + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/creature/npc/base/whiphid_base_male.iff"}, -- object/mobile/junk_dender.iff has a typo in it's appearanceFilename
	lootGroups = {},
	weapons = {},
	conversationTemplate = "junkDealerDenderConvoTemplate",
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(junk_dender, "junk_dender")
