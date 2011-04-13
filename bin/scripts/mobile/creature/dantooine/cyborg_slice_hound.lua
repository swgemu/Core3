cyborg_slice_hound = Creature:new {
	objectName = "@mob/creature_names:warren_cyborg_slicehound",
	socialGroup = "Warren Cyborg",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3370,
	baseHAM = 9700,
	baseHAMmax = 9700,
	armor = 0,
	resists = {35,40,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 70,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER,
	diet = CARNIVORE,

	templates = {"object/mobile/warren_cyborg_slicehound.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cyborg_slice_hound, "cyborg_slice_hound")