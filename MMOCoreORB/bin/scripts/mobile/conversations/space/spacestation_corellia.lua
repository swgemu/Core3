spacestation_corellia_convotemplate = ConvoTemplate:new {
    initialScreen = "spacestation_corellia_greeting",
    templateType = "Lua",
    luaClassHandler = "spacestation_corellia_conv_handler",
    screens = {}
}

-- Initial Greeting
spacestation_corellia_greeting = ConvoScreen:new {
    id = "spacestation_corellia_greeting",
    leftDialog = "@conversation/station_corellia:s_87bb06cf", --You have entered CorSec space in the Corellia System.  Please identify yourself and state your business.
    stopConversation = "false",
    options = {
        {"@conversation/station_corellia:s_7e77cbe2", "spacestation_corellia_land"}, --I would like to land
        {"@conversation/station_corellia:s_c358d041", "spacestation_corellia_repair"}, --(Request Repairs)
    }
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_greeting);

--Start conversation to land
spacestation_corellia_land = ConvoScreen:new {
    id = "spacestation_corellia_land",
    leftDialog = "@conversation/station_corellia:s_108cc9eb", --There are four starports available to a ship of your class, %TU.  Please indicate your destination.
    stopConversation = "false",
    options = {
        {"@conversation/station_corellia:s_c3399297", "spacestation_corellia_land_coronet"}, --Coronet Starport.
        {"@conversation/station_corellia:s_ccc6f3ed", "spacestation_corellia_land_kor_vella"}, --Kor Vella Starport.
        {"@conversation/station_corellia:s_19bf16ff", "spacestation_corellia_land_doaba_guerfel"}, --Doaba Guerfel Starport.
        {"@conversation/station_corellia:s_63ccb695", "spacestation_corellia_land_tyrena"}, --Tyrena Starport.
    }
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land);

--Land at coronet
spacestation_corellia_land_coronet = ConvoScreen:new {
    id = "spacestation_corellia_land_coronet",
    leftDialog = "@conversation/station_corellia:s_d00437d0", --Very well, %TU, you are cleared for landing at the Coronet Starport.
    stopConversation = "false",
    options = {
        {"@conversation/station_corellia:s_2dc4697a", "spacestation_corellia_land_coronet_complete"}, --(Land)
        {"@conversation/station_corellia:s_851eb5fa", "spacestation_corellia_land_coronet_abort"}, --Disregard.
    }
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_coronet);

--Finishing landing at coronet
spacestation_corellia_land_coronet_complete = ConvoScreen:new {
    id = "spacestation_corellia_land_coronet_complete",
    leftDialog = "@conversation/station_corellia:s_f7203392", --Assigning you an operator. Transmitting data now.
    stopConversation = "true",
    options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_coronet_complete);

--Abort landing at coronet
spacestation_corellia_land_coronet_abort = ConvoScreen:new {
    id = "spacestation_corellia_land_coronet_abort",
    leftDialog = "@conversation/station_corellia:s_1bbaf71f", --Roger that, %TU.  Please clear the area for other traffic.
    stopConversation = "true",
    options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_coronet_abort);

--Land at kor_vella
spacestation_corellia_land_kor_vella = ConvoScreen:new {
    id = "spacestation_corellia_land_kor_vella",
    leftDialog = "@conversation/station_corellia:s_eec4dc6e", --Very well, %TU, you are cleared for landing at the Kor Vella Starport.
    stopConversation = "false",
    options = {
        {"@conversation/station_corellia:s_2dc4697a", "spacestation_corellia_land_kor_vella_complete"}, --(Land)
        {"@conversation/station_corellia:s_851eb5fa", "spacestation_corellia_land_kor_vella_abort"}, --Disregard.
    }
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_kor_vella);

--Finishing landing at kor_vella
spacestation_corellia_land_kor_vella_complete = ConvoScreen:new {
    id = "spacestation_corellia_land_kor_vella_complete",
    leftDialog = "@conversation/station_corellia:s_f7203392", --Assigning you an operator. Transmitting data now.
    stopConversation = "true",
    options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_kor_vella_complete);

--Abort landing at kor_vella
spacestation_corellia_land_kor_vella_abort = ConvoScreen:new {
    id = "spacestation_corellia_land_kor_vella_abort",
    leftDialog = "@conversation/station_corellia:s_1bbaf71f", --Roger that, %TU.  Please clear the area for other traffic.
    stopConversation = "true",
    options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_kor_vella_abort);

--Land at doaba_guerfel
spacestation_corellia_land_doaba_guerfel = ConvoScreen:new {
    id = "spacestation_corellia_land_doaba_guerfel",
    leftDialog = "@conversation/station_corellia:s_b596ece0", --Very well, %TU, you are cleared for landing at the Doaba Guerfel Starport.
    stopConversation = "false",
    options = {
        {"@conversation/station_corellia:s_2dc4697a", "spacestation_corellia_land_doaba_guerfel_complete"}, --(Land)
        {"@conversation/station_corellia:s_851eb5fa", "spacestation_corellia_land_doaba_guerfel_abort"}, --Disregard.
    }
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_doaba_guerfel);

--Finishing landing at doaba_guerfel
spacestation_corellia_land_doaba_guerfel_complete = ConvoScreen:new {
    id = "spacestation_corellia_land_doaba_guerfel_complete",
    leftDialog = "@conversation/station_corellia:s_f7203392", --Assigning you an operator. Transmitting data now.
    stopConversation = "true",
    options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_doaba_guerfel_complete);

--Abort landing at doaba_guerfel
spacestation_corellia_land_doaba_guerfel_abort = ConvoScreen:new {
    id = "spacestation_corellia_land_doaba_guerfel_abort",
    leftDialog = "@conversation/station_corellia:s_1bbaf71f", --Roger that, %TU.  Please clear the area for other traffic.
    stopConversation = "true",
    options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_doaba_guerfel_abort);

--Land at tyrena
spacestation_corellia_land_tyrena = ConvoScreen:new {
    id = "spacestation_corellia_land_tyrena",
    leftDialog = "@conversation/station_corellia:s_f0f7d52d", --Very well, %TU, you are cleared for landing at the Tyrena Starport.
    stopConversation = "false",
    options = {
        {"@conversation/station_corellia:s_2dc4697a", "spacestation_corellia_land_tyrena_complete"}, --(Land)
        {"@conversation/station_corellia:s_851eb5fa", "spacestation_corellia_land_tyrena_abort"}, --Disregard.
    }
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_tyrena);

--Finishing landing at tyrena
spacestation_corellia_land_tyrena_complete = ConvoScreen:new {
    id = "spacestation_corellia_land_tyrena_complete",
    leftDialog = "@conversation/station_corellia:s_f7203392", --Assigning you an operator. Transmitting data now.
    stopConversation = "true",
    options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_tyrena_complete);

--Abort landing at tyrena
spacestation_corellia_land_tyrena_abort = ConvoScreen:new {
    id = "spacestation_corellia_land_tyrena_abort",
    leftDialog = "@conversation/station_corellia:s_1bbaf71f", --Roger that, %TU.  Please clear the area for other traffic.
    stopConversation = "true",
    options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_tyrena_abort);

-- Repair Main
spacestation_corellia_repair = ConvoScreen:new {
    id = "spacestation_corellia_repair",
    leftDialog = "@conversation/station_corellia:s_13071055", --Roger, %TU.  We are a fully functional station and can provide you with whatever level of repairs that are necessary.  Please indicate your status.
    stopConversation = "false",
    options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_repair);

-- Add Template (EOF)
addConversationTemplate("spacestation_corellia_convotemplate", spacestation_corellia_convotemplate);
