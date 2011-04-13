male_mamien = Creature:new {
	objectName = "@mob/creature_names:mamien_male",
	socialGroup = "Mamien",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1426,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {20,15,0,0,-1,-1,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 45,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/mamien.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(male_mamien, "male_mamien")