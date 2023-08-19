BartendersScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "BartendersScreenPlay",

	CHAT_LISTEN_DELAY = 30000,

	-- {"bartender_name", "zoneName", cellID}
	bartenderSpawns = {
		{"wuher", "tatooine", 1082877}, -- Tatooine Mos Eisely
		{"bartender", "tatooine", 1256058}, -- Tatooine Mos Espa
		{"bartender", "tatooine", 1134560}, -- Tatooine Wayfar
		{"bartender", "tatooine", 1028647}, -- Tatooine Bestine
		{"bartender", "lok", 8145378}, -- Lok Nym's Stronghold
		{"bartender", "naboo", 91}, -- Naboo Theed
		{"bartender", "naboo", 64}, -- Naboo Kaadara
		{"bartender", "naboo", 5}, -- Naboo Keren
		{"bartender", "naboo", 111}, -- Naboo Moenia
		{"bartender", "corellia", 8105496}, -- Corellia Coronet
		{"bartender", "corellia", 3005697}, -- Corellia Vreni Island
		{"bartender", "corellia", 3375355}, -- Corellia Bela Vistal
		{"bartender", "corellia", 2625355}, -- Corellia Tyrena
		{"bartender", "corellia", 3005399}, -- Corellia Kor Vella
		{"bartender", "corellia", 3075429}, -- Corellia Doaba Guerfel
		{"bartender", "talus", 3175391}, -- Talus Dearic
		{"bartender", "talus", 4265375}, -- Talus Nashal
	},

	patrolLocations = {
		{-11.1, -0.9, 2.4},
		{3.0, -0.9, 3.4},
		{7.2, -0.9, 2.6},
		{7.5, -0.9, -1.5},
		{8.2, -0.9, 1.4},
		{6.7, -0.9, -2.2},
		{7.2, -0.9, -1.8},
		{6.3, -0.9, -2.3},
		{1.4, -0.9, -2.4},
		{-7.2, -0.9, -2.2},
		{-10.5, -0.9, -2.2},
	},

	facingPlayerAnimations = {
		"worship",
		"greet",
		"nod_head_multiple",
		"nod",
		"applause_excited",
		"slow_down",
		"manipulate_medium",
		"point_left",
		"point_right",
		"beckon",
		"stretch",
		"bounce",
		"applause_polite",
		"2shot4u",
		"expect_tip",
		"he_dies",
		"he_lives",
		"hold_nose",
		"rub_chin_thoughtful",
		"thank",
		"udaman",
		"tiphat",
		"wtf",
		"entertained",
		"thumbs_up_double_fisted",
	},

	makeDrinkAnimations = {
		"tap_foot",
		"look_right",
		"look_left",
		"manipulate_high",
		"manipulate_medium",
		"scratch_head",
		"slump_head",
		"smell_armpit",
	},

	rumorWords = {"jedi", "spice", "pixie", "muon", "slice", "smuggler", "frs", "rebel", "rebellion", "giggledust", "neutron"},

	drinkOptions = {
		corellia = {{"aitha_protein_drink", 5}, {"lopez_softdrink", 5}, {"ardees_beverage", 5}, {"milk", 5}, {"hot_chocolate", 5}, {"ruby_bliel", 8}, {"imported_utozz", 8}},
		talus = {{"adumari_beer", 4}, {"lopez_softdrink", 5}, {"ardees_beverage", 5}, {"aitha_protein_drink", 5}, {"milk", 5}, {"imported_utozz", 9}},
		naboo = {{"lopez_softdrink", 5}, {"ardees_beverage", 5}, {"aitha_protein_drink", 6}, {"milk", 5}, {"eyeblaster" ,5}, {"hot_chocolate", 5}, {"imported_utozz", 9}, {"imported_tatooine_sunburn", 8}, {"jawa_beer", 8}},
		tatooine = {{"bantha_blood_fizz", 4}, {"jawa_juice", 3}, {"tatooine_sunburn", 4}, {"lopez_softdrink", 5}, {"ardees_beverage", 5}, {"aitha_protein_drink", 5}, {"milk", 5}, {"bantha_blaster", 6}, {"jawa_beer", 7}, {"imported_utozz", 9}},
		lok = {{"antakarian_fire_dancer", 4}, {"sith_scorcher", 4}, {"desert_bloom", 3}, {"ardees_beverage", 5}, {"aitha_protein_drink", 5}, {"milk", 5}, {"imported_jawa_beer", 9}},
	},

	drinkTemplates = {
		adumari_beer = "object/tangible/food/bartender_drinks/adumari_beer.iff",
		aitha_protein_drink = "object/tangible/food/bartender_drinks/aitha_protein_drink.iff",
		antakarian_fire_dancer = "object/tangible/food/bartender_drinks/antakarian_fire_dancer.iff",
		ardees_beverage = "object/tangible/food/bartender_drinks/drink_charde.iff",
		bantha_blaster = "object/tangible/food/bartender_drinks/bantha_blaster.iff",
		bantha_blood_fizz = "object/tangible/food/bartender_drinks/bantha_blaster.iff",
		desert_bloom = "object/tangible/food/bartender_drinks/desert_bloom.iff",
		eyeblaster = "object/tangible/food/bartender_drinks/eyeblaster.iff",
		hot_chocolate = "object/tangible/food/bartender_drinks/hot_chocolate.iff",
		imported_jawa_beer = "object/tangible/food/bartender_drinks/imported_jawa_beer.iff",
		imported_tatooine_sunburn = "object/tangible/food/bartender_drinks/imported_tatooine_sunburn.iff",
		imported_utozz = "object/tangible/food/bartender_drinks/imported_utozz.iff",
		jawa_beer = "object/tangible/food/bartender_drinks/jawa_beer.iff",
		jawa_juice = "object/tangible/food/bartender_drinks/jawa_juice.iff",
		lopez_softdrink = "object/tangible/food/bartender_drinks/lopez_softdrink.iff",
		milk = "object/tangible/food/bartender_drinks/milk.iff",
		ruby_bliel = "object/tangible/food/bartender_drinks/ruby_bliel.iff",
		sith_scorcher = "object/tangible/food/bartender_drinks/sith_scorcher.iff",
		tatooine_sunburn = "object/tangible/food/bartender_drinks/tatooine_sunburn.iff",
	}
}

registerScreenPlay("BartendersScreenPlay", true)

function BartendersScreenPlay:start()
	self:spawnBartenders()
end

function BartendersScreenPlay:spawnBartenders()
	local x = self.patrolLocations[1][1]
	local z = self.patrolLocations[1][2]
	local y = self.patrolLocations[1][3]

	local bartenders = self.bartenderSpawns

	for i = 1, #bartenders, 1 do
		local bartenderTable = bartenders[i]

		--print("BartendersScreenPlay:spawnBartenders -- spawning: " ..  bartenderTable[1] .. " on " .. bartenderTable[2] .. " Cell ID: " .. bartenderTable[3])

		local pNpc = spawnMobile(bartenderTable[2], bartenderTable[1], -1, x, z, y, 0, bartenderTable[3])

		if (pNpc ~= nil) then
			local npcID = SceneObject(pNpc):getObjectID()

			AiAgent(pNpc):addCreatureFlag(AI_STATIONARY)
			AiAgent(pNpc):setMovementState(AI_PATROLLING)

			createEvent(300 * 1000, "BartendersScreenPlay", "assignPatrolPoint", pNpc, "")

			-- Create Observers for arrival and chat
			createObserver(DESTINATIONREACHED, "BartendersScreenPlay", "reachedBartenderPoint", pNpc)

			-- 15% chance to be a rumor bartender
			if (getRandomNumber(100) <= 15) then
				createObserver(SPATIALCHAT, "BartendersScreenPlay", "chatListen", pNpc)

				writeData(npcID .. ":BartenderRumorFlag:", 1)

				local newStamp = getTimestampMilli() + self.CHAT_LISTEN_DELAY
				writeData(npcID .. ":BartenderChatListen:", newStamp)
			end
		end
	end
end

function BartendersScreenPlay:chatListen(pNpc, pChatMessage, playerID)
	if (pNpc == nil or pChatMessage == nil) then
		return 1
	end

	--print("BartendersScreenPlay:chatListen for " .. SceneObject(pNpc):getDisplayedName() .. " Player ID: " .. playerID)

	local pObject = getSceneObject(playerID)

	if (pObject == nil or not SceneObject(pObject):isPlayerCreature()) then
		return 0
	end

	local npcID = SceneObject(pNpc):getObjectID()
	local hasRumors = readData(npcID .. ":BartenderPlayerRumors:")

	if (hasRumors == 1) then
		return 0
	end

	local currentTime = getTimestampMilli()
	local lastObservation = readData(npcID .. ":BartenderChatListen:")

	if (lastObservation > currentTime) then
		return 0
	end

	local spatialMsg = getChatMessage(pChatMessage)

	if (spatialMsg == nil or spatialMsg == "") then
		return 0
	end

	local newStamp = currentTime + self.CHAT_LISTEN_DELAY

	deleteData(npcID .. ":BartenderChatListen:")
	writeData(npcID .. ":BartenderChatListen:", newStamp)

	local messageTable = {}
	for word in spatialMsg:gmatch("%w+") do table.insert(messageTable, word) end

	local tableSize = #messageTable

	if (tableSize < 10 or tableSize > 60) then
		return 0
	end

	local foundWord = false

	for i = 1, tableSize, 1 do
		local checkWord = messageTable[i]

		for j = 1, #self.rumorWords, 1 do
			local rumorWord = self.rumorWords[j]

			if (checkWord == rumorWord) then
				foundWord = true
				goto skip
			end
		end

		::skip::
	end

	if (foundWord == false) then
		return 0
	end

	spatialChat(pNpc, "Ya never know what ya'll hear 'round these parts...")

	writeStringData(npcID .. ":BartenderRumorMessage:", spatialMsg)
	writeStringData(npcID .. ":BartenderRumorPlayer:", CreatureObject(pObject):getFirstName())

	writeData(npcID .. ":BartenderPlayerRumors:", 1)

	return 0
end

function BartendersScreenPlay:reachedBartenderPoint(pNpc)
	if (pNpc == nil) then
		return 1
	end

	local randomTime = getRandomNumber(15, 45)

	-- schedule next movement
	createEvent(randomTime * 1000, "BartendersScreenPlay", "assignPatrolPoint", pNpc, "")

	-- Schedule an animation and bartender direction
	createEvent(5 * 1000, "BartendersScreenPlay", "doAnimation", pNpc, "")
	createEvent(2 * 1000, "BartendersScreenPlay", "updateDirection", pNpc, "")

	return 0
end

function BartendersScreenPlay:assignPatrolPoint(pNpc)
	if (pNpc == nil or AiAgent(pNpc):getPatrolPointsSize() > 0) then
		return
	end

	local randomPoint = getRandomNumber(#self.patrolLocations)
	local point = self.patrolLocations[randomPoint]
	local parentID = SceneObject(pNpc):getParentID()

	AiAgent(pNpc):setNextPosition(point[1], point[2], point[3], parentID)
end

function BartendersScreenPlay:updateDirection(pNpc)
	if (pNpc == nil) then
		return
	end

	local direction = getRandomNumber(360)
	local positionX = SceneObject(pNpc):getPositionX()
	local positionY = SceneObject(pNpc):getPositionY()

	if (positionX < -10.5) then
		direction = 90
	elseif (positionX > 7.3 and positionY < 3.0) then
		-- Front End of bar
		if (getRandomNumber(100) < 30) then
			direction = 270
		else
			direction = 90
		end
	elseif (positionY > 2.1) then
		-- Right side of bar, choose to face players or bar
		if (getRandomNumber(100) < 30) then
			direction = 180
		else
			direction = 0
		end
	else
		-- Left Side of Bar
		if (getRandomNumber(100) < 30) then
			direction = 0
		else
			direction = 180
		end
	end

	SceneObject(pNpc):updateDirection(math.rad(direction))
end

function BartendersScreenPlay:doAnimation(pNpc)
	if (pNpc == nil) then
		return
	end

	local animation = ""
	local facingPlayers = true

	local direction = CreatureObject(pNpc):getDirectionAngle()
	local positionX = SceneObject(pNpc):getPositionX()
	local positionY = SceneObject(pNpc):getPositionY()

	if (positionX < -10.5) then
		-- Back of End back
		facingPlayers = false
	elseif (positionX > 6.5 and positionY < 3.0) then
		-- Front End of bar
		if (direction > 260 and direction < 280) then
			facingPlayers = false
		end
	elseif (positionY > 2.1) then
		-- Right side of bar, choose to face players or bar
		if (direction > 175 and direction < 190) then
			facingPlayers = false
		end
	else
		-- Left Side of Bar
		if (direction > -10 and direction < 10) then
			facingPlayers = false
		end
	end

	if (facingPlayers) then
		local randomFacingAnim = getRandomNumber(#self.facingPlayerAnimations)
		animation = self.facingPlayerAnimations[randomFacingAnim]

		--print("facing players animation")
	else
		local randomBarAnim = getRandomNumber(#self.makeDrinkAnimations)
		animation = self.makeDrinkAnimations[randomBarAnim]

		--print("facing bar animation")
	end

	CreatureObject(pNpc):doAnimation(animation)
end

function BartendersScreenPlay:purchaseDrinkCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed or pPlayer == nil) then
		return
	end

	local zoneName = CreatureObject(pPlayer):getZoneName()
	local drinksTable = self.drinkOptions[zoneName]
	local argNum = tonumber(args) + 1

	local drinkName = drinksTable[argNum][1]
	local drinkCost = drinksTable[argNum][2]
	local messageString = "@food_name:" .. drinkName

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	if (CreatureObject(pPlayer):getCashCredits() < drinkCost) then
		local noCreditsMsg = LuaStringIdChatParameter("@bartender:prose_buy_fail") --"You were unable to purchase %TO. Perhaps you do not have enough credits?"
		noCreditsMsg:setTO(messageString)

		CreatureObject(pPlayer):sendSystemMessage(noCreditsMsg:_getObject())
		return;
	end

	if (SceneObject(pInventory):isContainerFullRecursive()) then
		local fullMsg = LuaStringIdChatParameter("@bartender:inv_full") --"The bartender was unable to hand you your %TO. It is likely your inventory is full."
		fullMsg:setTO(messageString)

		CreatureObject(pPlayer):sendSystemMessage(fullMsg:_getObject())
		return
	end

	local drinkTemplate = self.drinkTemplates[drinkName]

	local pItem = giveItem(pInventory, drinkTemplate, -1)

	if (pItem == nil) then
		local fullMsg = LuaStringIdChatParameter("@bartender:inv_full") --"The bartender was unable to hand you your %TO. It is likely your inventory is full."
		fullMsg:setTO(messageString)

		CreatureObject(pPlayer):sendSystemMessage(fullMsg:_getObject())
		return
	end

	-- Charge for drink
	CreatureObject(pPlayer):subtractCashCredits(drinkCost)

	SceneObject(pItem):setCustomObjectName(getStringId(messageString))

	local successMsg = LuaStringIdChatParameter("@bartender:prose_buy_pass") --"You successfully purchase a %TT for %DI credits."
	successMsg:setTT(messageString)
	successMsg:setDI(drinkCost)

	CreatureObject(pPlayer):sendSystemMessage(successMsg:_getObject())
end