local realCreateEvent
local realGetCityRegionAt
local realGetSpawnPoint
local realReadData
local realSpawnMobile
local realWriteData

local DirectorManagerMocks = { }

-- Function to be called in the setup method for a test to prepare the mocks.
function DirectorManagerMocks.setup()
	realCreateEvent = createEvent
	realGetCityRegionAt = getCityRegionAt
	realGetSpawnPoint = getSpawnPoint
	realReadData = readData
	realSpawnMobile = spawnMobile
	realWriteData = writeData
end

-- Function to be called in the teardown method for a test to clean up the mocks.
function DirectorManagerMocks.teardown()
	createEvent = realCreateEvent
	getCityRegionAt = realGetCityRegionAt
	getSpawnPoint = realGetSpawnPoint
	readData = realReadData
	spawnMobile = realSpawnMobile
	writeData = realWriteData
end

-- Function to be called in the before_each method for a test to prepare the mocks.
function DirectorManagerMocks.before_each()
	createEvent = spy.new(function() end)
	getCityRegionAt = spy.new(function() return nil end)
	getSpawnPoint = spy.new(function() return nil end)
	readData = spy.new(function() return nil end)
	spawnMobile = spy.new(function() return nil end)
	writeData = spy.new(function() end)
end

-- Function to be called in the after_each method for a test to verify the mocks.
function DirectorManagerMocks.after_each()
end

return DirectorManagerMocks
