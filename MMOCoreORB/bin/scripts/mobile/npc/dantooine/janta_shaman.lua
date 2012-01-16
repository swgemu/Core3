janta_shaman = Creature:new {
	objectName = "@mob/creature_names:janta_shaman",
	socialGroup = "Janta Tribe",
	pvpFaction = "Janta Tribe",
	faction = "",
	level = 60,
	chanceHit = 0.65,
	damageMin = 470,
	damageMax = 650,
	baseXp = 5830,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {-1,40,-1,20,100,100,20,-1,-1},
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
	creatureBitmask = PACK + HERD + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dantari_male.iff"},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(janta_shaman, "janta_shaman")