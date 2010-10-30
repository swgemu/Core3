mawgax_youth = Creature:new {
	objectName = "@mob/creature_names:mawgax_youth",
	socialGroup = "Mawgax",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.340000,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1803,
	baseHAM = 6000,
	baseHAMmax = 6000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 650,
	hideType = "hide_leathery",
	hideAmount = 60,
	boneType = "bone_avian",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/mawgax_youth.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(mawgax_youth, "mawgax_youth")