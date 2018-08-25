mature_hanadak_rock_smasher = Creature:new {
	objectName = "@mob/creature_names:mature_hanadak_rock_smasher",
	socialGroup = "hanadak",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3460,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {20,160,20,-1,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 35,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/hanadak_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/hanadak_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(mature_hanadak_rock_smasher, "mature_hanadak_rock_smasher")
