rhoa_kwi_pack_leader = Creature:new {
	objectName = "rhoa kwi pack leader",
	socialGroup = "Rhoa Kwi",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.470000,
	damageMin = 380,
	damageMax = 470,
	baseXp = 4916,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {35,65,0,60,0,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 86,
	boneType = "bone_mammal",
	boneAmount = 76,
	milk = 0,
	tamingChance = 0.100000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rhoa_kwi_pack_leader, "rhoa_kwi_pack_leader")