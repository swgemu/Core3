female_snorbal_calf = Creature:new {
	objectName = "@mob/creature_names:female_snorbal_calf",
	socialGroup = "Snorbal",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1257,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {20,0,-1,0,0,0,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 500,
	hideType = "hide_leathery",
	hideAmount = 400,
	boneType = "bone_mammal",
	boneAmount = 350,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/female_snorbal_calf.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_snorbal_calf, "female_snorbal_calf")