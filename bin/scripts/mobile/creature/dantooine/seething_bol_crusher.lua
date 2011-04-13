seething_bol_crusher = Creature:new {
	objectName = "@mob/creature_names:seething_bol_crusher",
	socialGroup = "Bol",
	pvpFaction = "",
	faction = "",
	level = 44,
	chanceHit = 0.440000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 4279,
	baseHAM = 10300,
	baseHAMmax = 10300,
	armor = 0,
	resists = {65,45,80,-1,0,0,0,100,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/seething_bol_crusher.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mediumdisease",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(seething_bol_crusher, "seething_bol_crusher")