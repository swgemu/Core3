droopy_mccool = Creature:new {
	objectName = "@mob/creature_names:droopy_mccool",
	socialGroup = "jabba",
	faction = "jabba",
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/droopy_mccool.iff"},
	lootGroups = {},
	weapons = {},
	outfit = "band_flute_droopy_outfit",
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(droopy_mccool, "droopy_mccool")
