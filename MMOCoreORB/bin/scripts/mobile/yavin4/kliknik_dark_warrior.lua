kliknik_dark_warrior = Creature:new {
	objectName = "@mob/creature_names:kliknik_dark_warrior",
	socialGroup = "kliknik",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.43,
	damageMin = 340,
	damageMax = 390,
	baseXp = 4006,
	baseHAM = 9200,
	baseHAMmax = 11200,
	armor = 0,
	resists = {60,40,25,25,25,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.15,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "kliknik_common", chance = 3300000}
			},
			lootChance = 4300000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_dark_warrior, "kliknik_dark_warrior")