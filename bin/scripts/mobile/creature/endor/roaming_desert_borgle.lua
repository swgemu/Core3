roaming_desert_borgle = Creature:new {
	objectName = "@mob/creature_names:borgle_desert_roamer",
	socialGroup = "Borgle",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.380000,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3188,
	baseHAM = 9200,
	baseHAMmax = 9200,
	armor = 0,
	resists = {30,40,0,55,-1,70,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/borgle.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(roaming_desert_borgle, "roaming_desert_borgle")