adept_jinda_shaman = Creature:new {
	objectName = "@mob/creature_names:adept_jinda_shaman",
	socialGroup = "jinda_tribe",
	pvpFaction = "jinda_tribe",
	faction = "",
	level = 32,
	chanceHit = 0.39,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3188,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {20,20,20,20,20,20,20,20,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {
			"object/mobile/jinda_male.iff",
			"object/mobile/jinda_male_01.iff",
			"object/mobile/jinda_female.iff",
			"object/mobile/jinda_female_01.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(adept_jinda_shaman, "adept_jinda_shaman")