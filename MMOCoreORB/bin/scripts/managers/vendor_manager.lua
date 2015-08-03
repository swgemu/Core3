function VendorSelectionNode(nn, np, sd, hr)
	return {
		nodeName = nn,
		nodePath = np,
		suiDisplay = sd,
		hiringRequired = hr,
		childNodes = {},
		
		addChildNode = function (self, node) table.insert(self.childNodes, node) end
	}
end

-- Root Select Vendor Type Menu
rootNode = VendorSelectionNode("root", "", "@player_structure:vendor_type_", 0)

-- RootMenu Vendor Type Selections
terminalNode = VendorSelectionNode("@player_structure:terminal", "object/tangible/vendor/vendor_terminal_", "@player_structure:terminal_type_", 10)
droidNode = VendorSelectionNode("@player_structure:droid", "object/tangible/vendor/vendor_droid_", "@player_structure:droid_type_", 20)
npcNode = VendorSelectionNode("@player_structure:npc", "object/mobile/vendor/", "@player_structure:race_type_", 30)

-- TerminalMenu - Selections 
terminalNode:addChildNode(VendorSelectionNode("@player_structure:terminal_bulky", "bulky.iff", "", 10))
terminalNode:addChildNode(VendorSelectionNode("@player_structure:terminal_standard", "standard.iff", "", 30))
terminalNode:addChildNode(VendorSelectionNode("@player_structure:terminal_small", "small.iff", "", 50))
terminalNode:addChildNode(VendorSelectionNode("@player_structure:terminal_fancy", "fancy.iff", "", 75))
terminalNode:addChildNode(VendorSelectionNode("@player_structure:terminal_slim", "slim.iff", "", 90))

-- DroidMenu - Selections
droidNode:addChildNode(VendorSelectionNode("@player_structure:droid_bartender", "bartender.iff", "", 20))
droidNode:addChildNode(VendorSelectionNode("@player_structure:droid_power", "power.iff", "", 50))
droidNode:addChildNode(VendorSelectionNode("@player_structure:droid_wed", "wed.iff", "", 60))
droidNode:addChildNode(VendorSelectionNode("@player_structure:droid_surgical", "surgical.iff", "", 90))
droidNode:addChildNode(VendorSelectionNode("@player_structure:droid_protocol", "protocol.iff", "", 100))

-- NpcMenu - Selections

-- Common Male / Female Node
maleNode = VendorSelectionNode("@player_structure:male", "male.iff", "", 50)
femaleNode = VendorSelectionNode("@player_structure:female", "female.iff", "", 50)

--npcNode:addChildNode(VendorSelectionNode("@player_structure:race_random", "", "", 30)) -- Figure this out.

--Bothan
bothanNode = VendorSelectionNode("@player_structure:race_bothan", "bothan_", "@player_structure:gender_", 50)
bothanNode:addChildNode(maleNode)
bothanNode:addChildNode(femaleNode)
npcNode:addChildNode(bothanNode)

--Human
humanNode = VendorSelectionNode("@player_structure:race_human", "human_", "@player_structure:gender_", 50)
humanNode:addChildNode(maleNode)
humanNode:addChildNode(femaleNode)
npcNode:addChildNode(humanNode)

--Moncal
moncalNode = VendorSelectionNode("@player_structure:race_moncal", "moncal_", "@player_structure:gender_", 50)
moncalNode:addChildNode(maleNode)
moncalNode:addChildNode(femaleNode)
npcNode:addChildNode(moncalNode)

--Rodian
rodianNode = VendorSelectionNode("@player_structure:race_rodian", "rodian_", "@player_structure:gender_", 50)
rodianNode:addChildNode(maleNode)
rodianNode:addChildNode(femaleNode)
npcNode:addChildNode(rodianNode)

--Trandoshan
trandoshanNode = VendorSelectionNode("@player_structure:race_trandoshan", "trandoshan_", "@player_structure:gender_", 50)
trandoshanNode:addChildNode(maleNode)
trandoshanNode:addChildNode(femaleNode)
npcNode:addChildNode(trandoshanNode)

--Twilek
twilekNode = VendorSelectionNode("@player_structure:race_twilek", "twilek_", "@player_structure:gender_", 50)
twilekNode:addChildNode(maleNode)
twilekNode:addChildNode(femaleNode)
npcNode:addChildNode(twilekNode)

--Wookiee
wookieeNode = VendorSelectionNode("@player_structure:race_wookiee", "wookiee_", "@player_structure:gender_", 50)
wookieeNode:addChildNode(maleNode)
wookieeNode:addChildNode(femaleNode)
npcNode:addChildNode(wookieeNode)

--Zabrak
zabrakNode = VendorSelectionNode("@player_structure:race_zabrak", "zabrak_", "@player_structure:gender_", 50)
zabrakNode:addChildNode(maleNode)
zabrakNode:addChildNode(femaleNode)
npcNode:addChildNode(zabrakNode)

--Aqualish (Male Only - Female model is bugged. Is not in game on live)
npcNode:addChildNode(VendorSelectionNode("@player_structure:race_aqualish", "aqualish_male.iff", "", 60))

--Bith (Male only - Female version is bugged redundant/identical as male and also doesn't accept ANY clothing/armor drag & drop customizations)
npcNode:addChildNode(VendorSelectionNode("@player_structure:race_bith", "bith_male.iff", "", 60))

--Devaronian
npcNode:addChildNode(VendorSelectionNode("@player_structure:race_devaronian", "devaronian_male.iff", "", 60))

--Gran
npcNode:addChildNode(VendorSelectionNode("@player_structure:race_gran", "gran_male.iff", "", 60))

-- Ishi Tib
npcNode:addChildNode(VendorSelectionNode("@player_structure:race_ishi_tib", "ishi_tib_male.iff", "", 60))

--Ithorian
ithorianNode = VendorSelectionNode("@player_structure:race_ithorian", "ithorian_", "@player_structure:gender_", 60)
ithorianNode:addChildNode(maleNode)
ithorianNode:addChildNode(femaleNode)
npcNode:addChildNode(ithorianNode)

--Nikto
npcNode:addChildNode(VendorSelectionNode("@player_structure:race_nikto", "nikto_male.iff", "", 60))

--Quarren
npcNode:addChildNode(VendorSelectionNode("@player_structure:race_quarren", "quarren_male.iff", "", 60))

--Sullustan
sullustanNode = VendorSelectionNode("@player_structure:race_sullustan", "sullustan_", "@player_structure:gender_", 60)
sullustanNode:addChildNode(maleNode)
sullustanNode:addChildNode(femaleNode)
npcNode:addChildNode(sullustanNode)

--Weequay
npcNode:addChildNode(VendorSelectionNode("@player_structure:race_weequay", "weequay_male.iff", "", 60))

-- Add the inital types to the root menu
rootNode:addChildNode(terminalNode)
rootNode:addChildNode(droidNode)
rootNode:addChildNode(npcNode)

VendorMenu = rootNode;
