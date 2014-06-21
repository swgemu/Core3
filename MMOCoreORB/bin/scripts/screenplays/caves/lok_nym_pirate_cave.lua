NymPirateCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NymPirateCaveScreenPlay",

}

registerScreenPlay("NymPirateCaveScreenPlay", true)

function NymPirateCaveScreenPlay:start()
	if (isZoneEnabled("lok")) then
		self:spawnMobiles()
	end
end

function NymPirateCaveScreenPlay:spawnMobiles()

	-- Lok -2996 -668
		
	-- cell 5126310
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -22.507, -29.527, -33.041, 10.593, 5126310)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -24.037, -29.542, -32.678, 76.703, 5126310)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -28.992, -28.804, -27.014, 84.877, 5126310)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -26.044, -28.678, -28.925, 151.278, 5126310)
	
	-- cell 5126314
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -118.569, -49.131, -55.562, 105.691, 5126314)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -118.854, -49.317, -59.401, 91.773, 5126314)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -110.311, -50.808, -65.861, 99.266, 5126314)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -108.371, -51.828, -62.559, 46.777, 5126314)
	
	-- cell 5126316
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -151.682, -50.876, -40.273, -143.347, 5126316)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -149.986, -51.006, -40.755, 106.820, 5126316)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -154.725, -51.110, -41.754, 83.341, 5126316)
	
	-- cell 5126318
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -175.886, -49.661, -72.289, 33.308, 5126318)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -175.566, -49.846, -66.372, 3.528, 5126318)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -173.209, -49.795, -68.485, 116.292, 5126318)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -161.283, -49.395, -68.428, 127.465, 5126318)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -160.702, -49.773, -72.901, 168.067, 5126318)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -159.611, -49.939, -80.932, -142.532, 5126318)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -160.840, -49.844, -84.741, 45.496, 5126318)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -163.026, -49.547, -82.952, 29.849, 5126318)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -161.717, -49.784, -88.849, 22.345, 5126318)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -166.617, -49.619, -91.654, 21.182, 5126318)
	
	-- cell 5126320
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -159.404, -55.963, -118.992, 268.777, 5126320)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -159.619, -55.652, -123.032, 269.345, 5126320)
	
	-- cell 5126319
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -141.241, -53.967, -81.423, -174.942, 5126319)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -137.861, -54.139, -82.762, 147.513, 5126319)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -125.185, -53.773, -84.779, -135.320, 5126319)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -125.809, -53.754, -86.661, 44.129, 5126319)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -102.535, -54.960, -82.728, 161.606, 5126319)
	
	-- cell 5126322
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -84.720, -57.354, -42.726, 116.234, 5126322)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -84.242, -57.385, -37.810, 109.753, 5126322)
	
	-- cell 5126325
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -107.195, -42.953, -13.692, 66.756, 5126325)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -107.649, -42.955, -11.175, 6.815, 5126325)
	
	-- cell 5126323
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -101.517, -37.508, -48.844, 0.606, 5126323)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -106.282, -37.421, -48.892, -184.412, 5126323)
	
	-- cell 5126314
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -101.205, -37.033, -61.743, 81.201, 5126314)
	
	-- cell 5126321
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -129.482, -33.582, -69.037, 2.452, 5126321)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -125.354, -33.382, -68.972, 41.872, 5126321)
	
	-- cell 5126319
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -93.973, -39.163, -86.023, -124.912, 5126319)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -93.081, -38.753, -87.891, -63.611, 5126319)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -97.511, -38.883, -89.287, 17.858, 5126319)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -101.707, -38.238, -95.142, 9.986, 5126319)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -106.264, -38.591, -95.975, -68.194, 5126319)
	
	-- cell 5126317
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -87.056, -37.264, -120.502, 4.058, 5126317)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -85.058, -37.264, -120.501, 51.576, 5126317)
	
	-- cell 5126313
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -73.449, -31.653, -60.220, -170.764, 5126313)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -74.453, -31.751, -62.189, 78.088, 5126313)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -80.296, -30.949, -43.507, 94.359, 5126313)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -77.416, -30.340, -38.742, 124.972, 5126313)
	
	-- cell 5126311
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -55.970, -30.168, -38.361, -92.563, 5126311)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -56.069, -30.309, -43.260, 87.158, 5126311)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -47.012, -29.646, -39.248, 18.264, 5126311)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -44.064, -29.468, -40.729, -170.570, 5126311)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -42.928, -29.859, -42.862, 19.876, 5126311)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -39.576, -30.192, -44.178, 81.460, 5126311)
	
	-- cell 5126310
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -8.409, -30.398, -47.800, 73.279, 5126310)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -11.520, -30.236, -49.861, -177.412, 5126310)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -10.152, -30.365, -43.723, -177.286, 5126310)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -17.257, -30.101, -40.213, 177.530, 5126310)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -12.058, -29.319, -38.272, 163.294, 5126310)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -18.518, -29.522, -36.250, 0.999, 5126310)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -12.874, -29.001, -35.671, 4.367, 5126310)
	
	-- cell 5126328
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, 14.483, -35.378, -77.630, 0.281, 5126328)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, 16.469, -35.164, -78.787, 6.899, 5126328)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, 10.175, -35.827, -78.671, 12.550, 5126328)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -7.621, -34.929, -70.512, 98.512, 5126328)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -12.742, -34.768, -65.028, 66.416, 5126328)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -10.617, -34.892, -66.724, -157.535, 5126328)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -16.876, -34.710, -65.800, -176.949, 5126328)
	
	-- cell 5126330
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -9.750, -43.643, -94.602, 57.268, 5126330)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -10.521, -43.633, -99.816, 58.492, 5126330)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -13.799, -44.020, -101.136, 46.580, 5126330)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -18.839, -44.313, -103.013, 59.815, 5126330)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -27.344, -44.082, -97.624, 34.850, 5126330)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -62.523, -52.260, -115.315, 71.922, 5126330)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -62.465, -52.476, -110.589, 68.940, 5126330)
	
	-- cell 5126317
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -108.431, -69.582, -105.625, 52.868, 5126317)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -104.163, -69.532, -103.505, -141.757, 5126317)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -102.262, -69.705, -104.892, -103.113, 5126317)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -97.453, -70.432, -104.474, 89.353, 5126317)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, -90.556, -71.460, -105.361, -105.852, 5126317)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -76.379, -70.682, -102.405, 61.243, 5126317)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -77.091, -71.311, -108.814, 80.001, 5126317)
	
	-- Start Cage
	spawnMobile("lok", "trained_veermok", 300, -70.572, -69.615, -122.314, -66.309, 5126317)
	spawnMobile("lok", "trained_veermok", 300, -72.134, -70.473, -119.819, -54.116, 5126317)
	spawnMobile("lok", "trained_veermok", 300, -69.814, -70.418, -115.726, -51.236, 5126317)
	-- End Cage
	
	-- cell 5126336
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -61.648, -65.694, -147.225, 2.024, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -67.677, -65.284, -147.202, 3.446, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -61.440, -65.506, -164.336, 0.537, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -65.271, -66.055, -164.774, 86.350, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -76.473, -65.874, -157.770, 15.728, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -47.420, -66.686, -157.356, 78.816, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -48.362, -66.326, -177.353, 18.530, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -44.792, -66.460, -175.548, 9.645, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -41.077, -66.167, -178.641, 5.726, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -51.955, -65.886, -198.878, 19.196, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -59.471, -66.292, -198.935, 1.413, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -79.883, -66.002, -173.156, 38.809, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -83.716, -66.392, -172.311, 70.377, 5126336)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -85.054, -66.365, -178.006, 7.666, 5126336)
	
	-- cell 5126337
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, -56.754, -65.431, -224.578, 17.827, 5126337)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -50.633, -65.217, -223.649, 17.261, 5126337)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -52.371, -65.309, -229.234, 27.292, 5126337)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, -65.073, -65.386, -225.944, 81.210, 5126337)
	
	-- cell 5126334
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, 5.607, -71.955, -113.840, 64.139, 5126334)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, 4.539, -71.920, -114.186, -108.265, 5126334)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, 5.568, -71.858, -109.649, 129.503, 5126334)
	
	-- cell 5126328
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, 15.007, -67.357, -67.588, -111.868, 5126328)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, 14.820, -67.120, -73.814, -91.839, 5126328)
	
	-- cell 5126335
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, 33.184, -67.059, -62.617, -160.723, 5126335)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, 37.546, -67.032, -63.414, -129.393, 5126335)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, 40.535, -66.836, -63.051, 70.580, 5126335)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, 49.864, -67.030, -69.826, -139.248, 5126335)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, 53.485, -65.643, -85.256, -170.730, 5126335)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, 55.398, -66.246, -91.202, -140.704, 5126335)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, 53.679, -65.967, -89.926, 68.783, 5126335)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, 35.305, -69.052, -104.476, 7.544, 5126335)
	spawnMobile("lok", "sulfur_lake_pirate_cutthroat", 300, 30.039, -69.028, -104.620, 62.253, 5126335)
	spawnMobile("lok", "sulfur_lake_pirate_initiate", 300, 25.517, -66.546, -87.685, 84.165, 5126335)
	spawnMobile("lok", "sulfur_lake_pirate_lieutenant", 300, 24.666, -66.085, -83.231, 167.443, 5126335)

end
