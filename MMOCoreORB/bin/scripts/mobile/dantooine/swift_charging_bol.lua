swift_charging_bol = Creature:new {
	objectName = "@mob/creature_names:bol_swift_charger",
	socialGroup = "bol",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.41,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3370,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {20,20,0,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 180,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milkType = "milk_wild",
	milk = 180,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bol_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(swift_charging_bol, "swift_charging_bol")
