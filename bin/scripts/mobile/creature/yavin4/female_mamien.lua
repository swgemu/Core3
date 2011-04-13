female_mamien = Creature:new {
	objectName = "@mob/creature_names:mamien_female",
	socialGroup = "Mamien",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 3200,
	baseHAMmax = 3200,
	armor = 0,
	resists = {20,25,0,0,-1,0,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 45,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0.000000,
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

CreatureTemplates:addCreatureTemplate(female_mamien, "female_mamien")