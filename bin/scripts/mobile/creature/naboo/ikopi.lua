ikopi = Creature:new {
	objectName = "@monster_name:ikopi",
	socialGroup = "Ikopi",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 450,
	baseHAMmax = 450,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 70,
	hideType = "hide_bristley",
	hideAmount = 60,
	boneType = "bone_mammal",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/ikopi.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(ikopi, "ikopi")