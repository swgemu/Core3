blood_drenched_merek_king = Creature:new {
	objectName = "@mob/creature_names:blood_drenched_merek_king",
	socialGroup = "Merek",
	pvpFaction = "",
	faction = "",
	level = 56,
	chanceHit = 0.55,
	damageMin = 420,
	damageMax = 550,
	baseXp = 5464,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {10,35,10,10,10,10,10,10,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 55,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/blood_drenched_merek_king.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blood_drenched_merek_king, "blood_drenched_merek_king")