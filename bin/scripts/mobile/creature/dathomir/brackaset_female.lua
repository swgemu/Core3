brackaset_female = Creature:new {
	objectName = "@mob/creature_names:brackaset_female",
	socialGroup = "Brackaset",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.370000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2914,
	baseHAM = 9200,
	baseHAMmax = 9200,
	armor = 0,
	resists = {30,30,20,0,0,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 90,
	boneType = "bone_mammal",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/brackaset.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(brackaset_female, "brackaset_female")