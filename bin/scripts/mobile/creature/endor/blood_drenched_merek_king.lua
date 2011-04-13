blood_drenched_merek_king = Creature:new {
	objectName = "@mob/creature_names:blood_drenched_merek_king",
	socialGroup = "Merek",
	pvpFaction = "",
	faction = "",
	level = 56,
	chanceHit = 0.550000,
	damageMin = 420,
	damageMax = 550,
	baseXp = 5464,
	baseHAM = 12000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {0,35,0,0,0,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 55,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/blood_drenched_merek_king.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blood_drenched_merek_king, "blood_drenched_merek_king")