tamvar_senzen_missions =
  {
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "shandara", planetName = "naboo", npcName = "Shandara" }
      },
      secondarySpawns = {},
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    },
  }

npcMapTamvarSenzen =
  {
    {
      spawnData = { planetName = "naboo", npcTemplate = "tamvar_senzen", x = 20.9, z = 1.3, y = 10.4, direction = 173, cellID = 1741478, position = STAND },
      worldPosition = { x = 5188, y = 6819 },
      npcNumber = 1,
      stfFile = "@static_npc/naboo/tamvar_senzen",
      missions = tamvar_senzen_missions
    },

  }

TamvarSenzen = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapTamvarSenzen,
  className = "TamvarSenzen",
  screenPlayState = "tamvar_senzen_quest",
  distance = 600
}

registerScreenPlay("TamvarSenzen", true)

tamvar_senzen_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = TamvarSenzen
}
tamvar_senzen_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = TamvarSenzen
}