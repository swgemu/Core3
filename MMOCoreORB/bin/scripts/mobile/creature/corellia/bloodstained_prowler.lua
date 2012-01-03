bloodstained_prowler = Creature:new {
	objectName = "@mob/creature_names:wrix_bloodstained_prowler",
	socialGroup = "Wrix",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {35,30,10,50,10,35,-1,10,-1},
	meatType = "meat_carnivore",
	meatAmount = 70,
	hideType = "hide_bristley",
	hideAmount = 40,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gurreck.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bloodstained_prowler, "bloodstained_prowler")