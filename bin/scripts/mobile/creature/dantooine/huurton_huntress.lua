huurton_huntress = Creature:new {
	objectName = "@mob/creature_names:huurton_huntress",
	socialGroup = "Huurton",
	pvpFaction = "",
	faction = "",
	level = 28,
	chanceHit = 0.370000,
	damageMin = 270,
	damageMax = 280,
	range = 0,
	baseXp = 2914,
	baseHAM = 9100,
	armor = 0,
	resists = {0,0,0,40,100,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 15,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(huurton_huntress, "huurton_huntress")
