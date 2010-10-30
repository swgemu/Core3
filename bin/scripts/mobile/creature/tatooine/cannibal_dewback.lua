cannibal_dewback = Creature:new {
	objectName = "@mob/creature_names:dewback_cannibal",
	socialGroup = "Dewback",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 1609,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {0,0,0,-1,0,-1,0,-1,-1},
	meatType = "",
	meatAmount = 340,
	hideType = "hide_leathery",
	hideAmount = 260,
	boneType = "bone_mammal",
	boneAmount = 185,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER,
	diet = CARNIVORE,

	templates = {"object/mobile/dewback.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cannibal_dewback, "cannibal_dewback")