brackaset_male = Creature:new {
	objectName = "@mob/creature_names:brackaset_male",
	socialGroup = "Brackaset",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3005,
	baseHAM = 9400,
	baseHAMmax = 9400,
	armor = 0,
	resists = {30,30,20,0,0,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 91,
	boneType = "bone_mammal",
	boneAmount = 81,
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
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(brackaset_male, "brackaset_male")