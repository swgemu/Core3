local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")

local realHasJediProgressionScreenPlayState
local realSetJediProgressionScreenPlayState

local VillageJediManagerCommonMocks = VillageJediManagerCommon
VillageJediManagerCommonMocks.mocks = {}

-- Function to be called in the setup method for a test to prepare the mocks.
function VillageJediManagerCommonMocks.mocks.setup()
	realHasJediProgressionScreenPlayState = VillageJediManagerCommonMocks.hasJediProgressionScreenPlayState
	realSetJediProgressionScreenPlayState = VillageJediManagerCommonMocks.setJediProgressionScreenPlayState
end

-- Function to be called in the teardown method for a test to clean up the mocks.
function VillageJediManagerCommonMocks.mocks.teardown()
	VillageJediManagerCommon.hasJediProgressionScreenPlayState = realHasJediProgressionScreenPlayState
	VillageJediManagerCommon.setJediProgressionScreenPlayState = realSetJediProgressionScreenPlayState
end

-- Function to be called in the before_each method for a test to prepare the mocks.
function VillageJediManagerCommonMocks.mocks.before_each()
	VillageJediManagerCommon.hasJediProgressionScreenPlayState = spy.new(function() end)
	VillageJediManagerCommon.setJediProgressionScreenPlayState = spy.new(function() end)
end

-- Function to be called in the after_each method for a test to verify the mocks.
function VillageJediManagerCommonMocks.mocks.after_each()
end

return VillageJediManagerCommonMocks
