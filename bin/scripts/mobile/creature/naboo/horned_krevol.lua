horned_krevol = Creature:new {
	objectName = "@monster_name:horned_krevol",
	socialGroup = "Horned Krevol",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 200,
	baseHAMmax = 200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 3,
	hideType = "hide_scaley",
	hideAmount = 15,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/horned_krevol.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(horned_krevol, "horned_krevol")