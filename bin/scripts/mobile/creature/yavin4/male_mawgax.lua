male_mawgax = Creature:new {
	objectName = "@mob/creature_names:mawgax_male",
	socialGroup = "Mawgax",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2543,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {20,20,0,-1,0,0,30,-1,-1},
	meatType = "",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_avian",
	boneAmount = 55,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/mawgax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(male_mawgax, "male_mawgax")