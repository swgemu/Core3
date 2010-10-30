mawgax_raptor = Creature:new {
	objectName = "@mob/creature_names:mawgax_raptor",
	socialGroup = "Mawgax",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 3005,
	baseHAM = 9200,
	baseHAMmax = 9200,
	armor = 0,
	resists = {20,20,0,-1,0,0,30,-1,-1},
	meatType = "",
	meatAmount = 90,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_avian",
	boneAmount = 55,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/mawgax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mawgax_raptor, "mawgax_raptor")