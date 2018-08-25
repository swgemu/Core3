kliknik_hunter = Creature:new {
	objectName = "@mob/creature_names:kliknik_hunter",
	socialGroup = "kliknik",
	faction = "",
	level = 32,
	chanceHit = 0.39,
	damageMin = 300,
	damageMax = 310,
	baseXp = 3279,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {140,135,20,20,20,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/kliknik_hue.iff",
	scale = 1.1,
	lootGroups = {
	 {
	        groups = {
				{group = "kliknik_common", chance = 10000000}
			},
			lootChance = 1640000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_hunter, "kliknik_hunter")
