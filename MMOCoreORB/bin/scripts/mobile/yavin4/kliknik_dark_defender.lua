kliknik_dark_defender = Creature:new {
	objectName = "@mob/creature_names:kliknik_dark_defender",
	socialGroup = "kliknik",
	pvpFaction = "",
	faction = "",
	level = 42,
	chanceHit = 0.44,
	damageMin = 360,
	damageMax = 430,
	baseXp = 4097,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {55,45,50,50,50,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 7,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.15,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/kliknik.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "kliknik_common", chance = 3300000}
			},
			lootChance = 7000000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_dark_defender, "kliknik_dark_defender")