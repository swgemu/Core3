reclusive_gurk_king = Creature:new {
	objectName = "@mob/creature_names:recluse_gurk_king",
	socialGroup = "gurk",
	faction = "",
	level = 45,
	chanceHit = 0.47,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4461,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 1,
	resists = {135,135,0,-1,0,0,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 300,
	hideType = "hide_leathery",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/recluse_gurk_king.iff"},
	scale = 1.4,
	lootGroups = {
	 {
	        groups = {
				{group = "gurk_king_common", chance = 10000000}
			},
			lootChance = 1900000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""},
		{"blindattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(reclusive_gurk_king, "reclusive_gurk_king")
