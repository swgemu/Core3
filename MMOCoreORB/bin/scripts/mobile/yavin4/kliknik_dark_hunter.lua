kliknik_dark_hunter = Creature:new {
	objectName = "@mob/creature_names:kliknik_dark_hunter",
	socialGroup = "kliknik",
	faction = "",
	level = 38,
	chanceHit = 0.43,
	damageMin = 350,
	damageMax = 410,
	baseXp = 3824,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {140,140,25,-1,25,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.15,
	lootGroups = {
		{
			groups = {
				{group = "kliknik_common", chance = 10000000}
			},
			lootChance = 1760000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_dark_hunter, "kliknik_dark_hunter")
