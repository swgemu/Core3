theme_park_smc_rancor_pygmy_maufel = Creature:new {
  objectName = "",
  customName = "Mau'fel",
  socialGroup = "rancor",
  faction = "mtn_clan",
  level = 50,
  chanceHit = 0.5,
  damageMin = 420,
  damageMax = 550,
  baseXp = 4370,
  baseHAM = 10000,
  baseHAMmax = 12000,
  armor = 1,
  resists = {130,130,-1,160,160,160,-1,-1,-1},
  meatType = "meat_carnivore",
  meatAmount = 500,
  hideType = "hide_leathery",
  hideAmount = 553,
  boneType = "bone_mammal",
  boneAmount = 453,
  milk = 0,
  tamingChance = 0,
  ferocity = 10,
  pvpBitmask = NONE,
  creatureBitmask = NONE,
  optionsBitmask = AIENABLED,
  diet = CARNIVORE,

  templates = {"object/mobile/rancor_hue.iff"},
  scale = 0.2,
  lootGroups = {},
  weapons = {},
  conversationTemplate = "",
  attacks = {
    {"stunattack",""},
    {"intimidationattack",""}
  }
}

CreatureTemplates:addCreatureTemplate(theme_park_smc_rancor_pygmy_maufel, "theme_park_smc_rancor_pygmy_maufel")