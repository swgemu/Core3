bren_kingal = Creature:new {
	objectName = "@mob/creature_names:mos_taike_guard_young",
	customName = "Bren Kingal",
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 20,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/mos_taike_guard_young.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "bren_kingal_mission_giver_convotemplate",
	outfit = "mos_taike_guard_outfit",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(bren_kingal, "bren_kingal")
