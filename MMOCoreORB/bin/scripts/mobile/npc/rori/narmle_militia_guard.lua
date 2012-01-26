narmle_militia_guard = Creature:new {
	objectName = "@mob/creature_names:narmle_guard",
	socialGroup = "Narmle",
	pvpFaction = "Narmle",
	faction = "",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_narmle_guard_rodian_male_01.iff"},
	lootgroups = {},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(narmle_militia_guard, "narmle_militia_guard")