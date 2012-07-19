kliknik_hunter = Creature:new {
	objectName = "@mob/creature_names:kliknik_hunter",
	socialGroup = "kliknik",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.39,
	damageMin = 300,
	damageMax = 310,
	baseXp = 3279,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {40,35,20,20,20,-1,-1,-1,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_hue.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "kliknik_common", chance = 10000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_hunter, "kliknik_hunter")