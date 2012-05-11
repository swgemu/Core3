patron_chiss = Creature:new {
	objectName = "@mob/creature_names:patron_chiss_male",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_patron_chiss_m_01.iff",
		"object/mobile/dressed_patron_chiss_f_01.iff"
	},
	lootGroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(patron_chiss, "patron_chiss")