ancient_bull_rancor = Creature:new {
	objectName = "@mob/creature_names:ancient_bull_rancor",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 98,
	chanceHit = 0.950000,
	damageMin = 620,
	damageMax = 950,
	baseXp = 9336,
	baseHAM = 22500,
	baseHAMmax = 22500,
	armor = 0,
	resists = {50,65,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 950,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER,
	diet = CARNIVORE,

	templates = {"object/mobile/bull_rancor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(ancient_bull_rancor, "ancient_bull_rancor")