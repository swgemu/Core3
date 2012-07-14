rhoa_kwi_pack_leader = Creature:new {
	objectName = "@mob/creature_names:rhoa_kwi_pack_leader",
	socialGroup = "kwi",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.47,
	damageMin = 380,
	damageMax = 470,
	baseXp = 4916,
	baseHAM = 9900,
	baseHAMmax = 12100,
	armor = 0,
	resists = {35,65,30,60,30,30,30,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 86,
	boneType = "bone_mammal",
	boneAmount = 76,
	milk = 0,
	tamingChance = 0.1,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rhoa_kwi_pack_leader, "rhoa_kwi_pack_leader")