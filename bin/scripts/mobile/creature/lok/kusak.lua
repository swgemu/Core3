kusak = Creature:new {
	objectName = "@monster_name:kusak",
	socialGroup = "Kusak",
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
	resists = {15,15,30,-1,20,20,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 20,
	hideType = "hide_bristley",
	hideAmount = 14,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kusak.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kusak, "kusak")