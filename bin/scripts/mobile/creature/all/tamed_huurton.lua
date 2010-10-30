tamed_huurton = Creature:new {
	objectName = "@mob/creature_names:rebel_tamed_huurton",
	socialGroup = "Rebel",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1300,
	baseHAMmax = 1300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(tamed_huurton, "tamed_huurton")