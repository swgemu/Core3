pigmy_pugoriss = Creature:new {
	objectName = "@mob/creature_names:pigmy_pugoriss",
	socialGroup = "Pugoriss",
	pvpFaction = "",
	faction = "",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 187,
	baseHAM = 200,
	baseHAMmax = 200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 300,
	hideType = "hide_leathery",
	hideAmount = 350,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/pigmy_pugoriss.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(pigmy_pugoriss, "pigmy_pugoriss")