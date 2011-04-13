mountain_squill_guardian = Creature:new {
	objectName = "@mob/creature_names:mountain_squill_guardian",
	socialGroup = "Mtn. Squill",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.420000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3915,
	baseHAM = 9900,
	baseHAMmax = 9900,
	armor = 0,
	resists = {60,60,0,-1,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 3,
	hideType = "hide_leathery",
	hideAmount = 4,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/mountain_squill.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_squill_guardian, "mountain_squill_guardian")