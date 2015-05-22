wallaw_bull_rancor = Creature:new {
  objectName = "@mob/creature_names:bull_rancor",
  socialGroup = "rancor",
  faction = "",
  level = 65,
  chanceHit = 0.6,
  damageMin = 455,
  damageMax = 620,
  baseXp = 6288,
  baseHAM = 11000,
  baseHAMmax = 14000,
  armor = 1,
  resists = {35,60,15,80,80,80,15,15,-1},
  meatType = "meat_carnivore",
  meatAmount = 1000,
  hideType = "hide_leathery",
  hideAmount = 900,
  boneType = "bone_mammal",
  boneAmount = 850,
  milk = 0,
  tamingChance = 0.01,
  ferocity = 11,
  pvpBitmask = ATTACKABLE,
  creatureBitmask = NONE,
  optionsBitmask = 136,
  diet = CARNIVORE,

  templates = {"object/mobile/bull_rancor.iff"},
  controlDeviceTemplate = "object/intangible/pet/rancor_hue.iff",
  lootGroups = {},
  weapons = {},
  conversationTemplate = "wallaw_loowobbli_mission_target_convotemplate",
  attacks = {
    {"creatureareadisease",""},
    {"dizzyattack",""}
  }
}

CreatureTemplates:addCreatureTemplate(wallaw_bull_rancor, "wallaw_bull_rancor")
