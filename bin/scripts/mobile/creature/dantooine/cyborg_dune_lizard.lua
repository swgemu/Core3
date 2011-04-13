cyborg_dune_lizard = Creature:new {
	objectName = "@mob/creature_names:warren_cyborg_dunelizard",
	socialGroup = "Warren Cyborg",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.370000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 3005,
	baseHAM = 9100,
	baseHAMmax = 9100,
	armor = 0,
	resists = {40,30,0,75,-1,-1,-1,-1,-1},
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

	templates = {"object/mobile/warren_cyborg_dunelizard.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cyborg_dune_lizard, "cyborg_dune_lizard")