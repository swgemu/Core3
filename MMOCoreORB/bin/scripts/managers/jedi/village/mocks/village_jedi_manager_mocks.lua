local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
require("managers.jedi.village.village_jedi_manager")

local realCheckForceStatusCommand
local realHasJediProgressionScreenPlayState
local realOnPlayerLoggedIn
local realSetJediProgressionScreenPlayState
local realUseHolocron

local VillageJediManagerMocks = {}

-- Function to be called in the setup method for a test to prepare the mocks.
function VillageJediManagerMocks.setup()
	DirectorManagerMocks.setup()

	realCheckForceStatusCommand = VillageJediManager.checkForceStatusCommand
	realHasJediProgressionScreenPlayState = VillageJediManager.hasJediProgressionScreenPlayState
	realOnPlayerLoggedIn = VillageJediManager.onPlayerLoggedIn
	realSetJediProgressionScreenPlayState = VillageJediManager.setJediProgressionScreenPlayState
	realUseHolocron = VillageJediManager.useHolocron
end

-- Function to be called in the teardown method for a test to clean up the mocks.
function VillageJediManagerMocks.teardown()
	DirectorManagerMocks.teardown()

	VillageJediManager.checkForceStatusCommand = realCheckForceStatusCommand
	VillageJediManager.hasJediProgressionScreenPlayState = realHasJediProgressionScreenPlayState
	VillageJediManager.onPlayerLoggedIn = realOnPlayerLoggedIn
	VillageJediManager.setJediProgressionScreenPlayState = realSetJediProgressionScreenPlayState
	VillageJediManager.useHolocron = realUseHolocron
end

-- Function to be called in the before_each method for a test to prepare the mocks.
function VillageJediManagerMocks.before_each()
	DirectorManagerMocks.before_each()

	VillageJediManager.checkForceStatusCommand = spy.new(function() end)
	VillageJediManager.hasJediProgressionScreenPlayState = spy.new(function() end)
	VillageJediManager.onPlayerLoggedIn = spy.new(function() end)
	VillageJediManager.setJediProgressionScreenPlayState = spy.new(function() end)
	VillageJediManager.useHolocron = spy.new(function() end)
end

-- Function to be called in the after_each method for a test to verify the mocks.
function VillageJediManagerMocks.after_each()
	DirectorManagerMocks.after_each()
end

return VillageJediManagerMocks
