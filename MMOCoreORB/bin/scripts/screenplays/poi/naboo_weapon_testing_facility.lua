WeaponFacilityScreenPlay = ScreenPlay:new { 
        numberOfActs = 1, 
} 
 
registerScreenPlay("WeaponFacilityScreenPlay", true) 
 
function WeaponFacilityScreenPlay:start() 
        self:spawnMobiles() 
end 
 
function WeaponFacilityScreenPlay:spawnMobiles() 
    --Cell [0] 
        spawnMobile("naboo", "dark_trooper", 300, -6502.1, 40.0, -3312.7, -1, 0) 
        spawnMobile("naboo", "stormtrooper",        300, -6509.6, 40.0, -3312.9, -1, 0) 
        spawnMobile("naboo", "imperial_officer",    300, -6512.7, 40.0, -3302.5, 71, 0) 
        spawnMobile("naboo", "stormtrooper",        300, -6496.0, -40.0, -3303.5, -104, 0) 
        spawnMobile("naboo", "dark_trooper",        300, -6486.6, 40.0, -3286.3, 76, 0) 
        spawnMobile("naboo", "stormtrooper",        300, -6495.7, 40.0, -3279.5, -165, 0) 
        spawnMobile("naboo", "imperial_colonel",    300, -6496.3, 40.0, -3290.1, -3, 0) 
        spawnMobile("naboo", "stormtrooper",        300, -6511.0, 40.0, -3281.4, 57, 0) 
        spawnMobile("naboo", "imperial_officer",    300, -6511.9, 40.0, -3274.4, 138, 0) 
        spawnMobile("naboo", "stormtrooper",        300, -6495.8, 40.0, -3272.4, 25, 0) 
        spawnMobile("naboo", "dark_trooper", 300, -6504.4, 40.0, -3262.2, 44, 0) 
 
    --Cell [6335640] 
        spawnMobile("naboo", "stormtrooper", 300, -4.2, 0.3, 3.8, 131, 6335640) 
        spawnMobile("naboo", "dark_trooper", 300, 0.5, 0.3, 2.0, -41, 6335640) 
        spawnMobile("naboo", "stormtrooper", 300, -4.6, 0.3, -4.7, 39, 6335640) 
 
    --Cell [6335641] 
        spawnMobile("naboo", "stormtrooper", 300, 4.0, 0.3, -4.0, -90, 6335641) 
 
    --Cell [6335642] 
        spawnMobile("naboo", "dark_trooper", 300, 2.7, -12.0, 20.6, -179, 6335642) 
        spawnMobile("naboo", "dark_trooper", 300, 4.6, -12.0, 20.8, -171, 6335642) 
 
    --Cell [6335643] 
        spawnMobile("naboo", "stormtrooper", 300, 9.7, -12.0, 31.0, 90, 6335643) 
        spawnMobile("naboo", "stormtrooper", 300, 3.3, -12.0, 30.4, 178, 6335643)  
        spawnMobile("naboo", "imperial_officer", 300, -2.6, -12.0, 31.0, -91, 6335643) 
        spawnMobile("naboo", "imperial_colonel", 300, 1.2, -12.0, 38.8, -177, 6335643) 
        spawnMobile("naboo", "imperial_first_lieutenant", 300, 9.6, -12.0, 47.0, -90, 6335643) 
        spawnMobile("naboo", "dark_trooper", 300, -2.9, -12.0, 63.2, -90, 6335643) 
        spawnMobile("naboo", "stormtrooper", 300, 3.6, -12.0, 65.5, 179, 6335643) 
        spawnMobile("naboo", "imperial_officer", 300, 5.9, -12.0, 63.1, -91, 6335643) 
        spawnMobile("naboo", "stormtrooper", 300, 3.7, -12.0, 60.7, 0, 6335643) 
        spawnMobile("naboo", "imperial_second_lieutenant", 300, 10.0, -12.0, 62.9, 90, 6335643) 
        spawnMobile("naboo", "dark_trooper", 300, 3.5, -12.0, 68.2, -1, 6335643) 
        spawnMobile("naboo", "dark_trooper", 300, -19.7, -12.0, 49.6, -92, 6335643) 
        spawnMobile("naboo", "imperial_officer", 300, -12.4, -12.0, 40.8, -178, 6335643) 
        spawnMobile("naboo", "stormtrooper", 300, -2.2, -12.0, 47.0, 90, 6335643) 
        spawnMobile("naboo", "imperial_first_lieutenant", 300, -13.7, -12.0, 47.1, 90, 6335643) 
         
    --Cell [6335644] 
        spawnMobile("naboo", "dark_trooper", 300, -42.8, -20.0, 46.3, 89, 6335644) 
        spawnMobile("naboo", "dark_trooper", 300, -42.8, -20.0, 47.7, 89, 6335644) 
 
 
    --Cell [6335645] 
        --WeaponTestingRoom-- 
        spawnMobile("naboo", "stormtrooper", 300, -50.6, -20.0, 28.0, -45, 6335645) 
        spawnMobile("naboo", "dark_trooper", 300, -54.5, -20.0, 28.6, 57, 6335645) 
        spawnMobile("naboo", "imperial_first_lieutenant", 300, -59.4, -20.0, 32.6, -8, 6335645) 
        spawnMobile("naboo", "dark_trooper", 300, -56.3, -20.0, 38.2, -92, 6335645) 
        spawnMobile("naboo", "stormtrooper", 300, -58.3, -20.0, -42.5, -164, 6335645) 
        spawnMobile("naboo", "dark_trooper", 300, -76.5, -20.0, 47.0, 89, 6335645) 
        spawnMobile("naboo", "imperial_officer", 300, -71.3, -20.0, 52.0, 47, 6335645) 
        spawnMobile("naboo", "stormtrooper", 300, -66.6, -20.0, 53.7, -66, 6335645) 
        spawnMobile("naboo", "stormtrooper", 300, -68.5, -20.0, 57.7, -162, 6335645) 
        spawnMobile("naboo", "dark_trooper", 300, -58.9, -20.0, 66.3, -2, 6335645) 
        spawnMobile("naboo", "imperial_officer", 300, -55.4, -20.0, 62.2, -75, 6335645) 
        spawnMobile("naboo", "imperial_colonel", 300, -67.9, -20.0, 23.6, -179, 6335645) 
        spawnMobile("naboo", "dark_trooper", 300, -75.7, -20.0, 29.5, 61, 6335645) 
 
    --Cell [6335646] 
        spawnMobile("naboo", "imperial_inquisitor", 600, -46.7, -20.0, 12.9, -84, 6335646) 
        spawnMobile("naboo", "imperial_second_lieutenant", 300, -68.2, -20.0, 18.0, 178, 6335646) 
        spawnMobile("naboo", "imperial_officer", 300, -76.0, -20.0, 17.8, -44, 6335646) 
        spawnMobile("naboo", "dark_trooper", 300, -63.6, -20.0, 13.0, 89, 6335646) 
        spawnMobile("naboo", "imperial_colonel", 300, -60.2, -20.0, 18.6, 1, 6335646) 
        spawnMobile("naboo", "dark_trooper", 300, -62.1, -20.0, 6.9, 177, 6335646) 
        spawnMobile("naboo", "imperial_officer", 300, -54.5, -20.0, 9.6, -89, 6335646) 
        spawnMobile("naboo", "stormtrooper", 300, -49.4, -20.0, 7.7, 131, 6335646) 
 
    --Cell [6335647] 
        spawnMobile("naboo", "dark_trooper", 300, -47.9, -20.0, 81.0, -89, 6335647) 
        spawnMobile("naboo", "imperial_first_lieutenant", 300, -50.5, -20.0, 78.4, -118, 6335647) 
        spawnMobile("naboo", "imperial_officer", 300, -77.1, -20.0, 78.3, -89, 6335647) 
        spawnMobile("naboo", "dark_trooper", 300, -75.5, -20.0, 86.0, 137, 6335647) 
        spawnMobile("naboo", "imperial_officer", 300, -70.4, -20.0, 88.3, -2, 6335647) 
        spawnMobile("naboo", "dark_trooper", 300, -71.4, -20.0, 82.1, -97, 6335647) 
        spawnMobile("naboo", "stormtrooper", 300, -54.5, -20.0, 88.1, 0, 6335647) 
 
    --Cell [6335652] 
        spawnMobile("naboo", "dark_trooper", 300, 37.5, -12.0, 11.1, -91, 6335652)
        spawnMobile("naboo", "stormtrooper", 300, 22.1, -12.0, 4.2, 171, 6335652) 
        spawnMobile("naboo", "imperial_warrant_officer_ii", 300, 25.5, -12.0, 0.3, -41, 6335652) 
        spawnMobile("naboo", "dark_trooper", 300, 20.6, -12.0, 0.2, 39, 6335652) 
        spawnMobile("naboo", "stormtrooper_major", 300, 61.7, -12.0, 1.8, -86, 6335652) 
        spawnMobile("naboo", "dark_trooper", 300, 37.9, -12.0, 1.5, -179, 6335652) 
        spawnMobile("naboo", "stormtrooper", 300, 51.2, -12.0, 12.8, -145, 6335652) 
        spawnMobile("naboo", "imperial_officer", 300, 49.8, -12.0, 9.7, 19, 6335652) 
        spawnMobile("naboo", "stormtrooper", 300, 41.3, -12.0, 22.8, 112, 6335652) 
        spawnMobile("naboo", "dark_trooper", 300, 45.0, -12.0, 19.5, -15, 6335652) 
 
 
    --Cell [6335654] 
        spawnMobile("naboo", "dark_trooper", 300, -22.5, -20.0, -1.8, 5, 6335654) 
        spawnMobile("naboo", "imperial_second_lieutenant", 300, -20.4, -20.0, -1.8, 0, 6335654) 
        spawnMobile("naboo", "imperial_warrant_officer_i", 300, -10.7, -20.0, 7.6, -179, 6335654) 
        spawnMobile("naboo", "dark_trooper", 300, -12.9, -20.0, 7.6, 178, 6335654) 
        spawnMobile("naboo", "imperial_officer", 300, -20.3, -20.0, 7.4, 179, 6335654) 
        spawnMobile("naboo", "stormtrooper", 300, -22.4, -20.0, 7.5, 177, 6335654) 
        spawnMobile("naboo", "dark_trooper", 300, -23.5, -20.0, 1.0, 81, 6335654) 
        spawnMobile("naboo", "dark_trooper", 300, -23.7, -20.0, 5.1, 118, 6335654) 
 
    --Cell [6335657] 
        spawnMobile("naboo", "dark_trooper", 300, -29.2, -20.0, 99.2, -173, 6335657) 
        spawnMobile("naboo", "dark_trooper", 300, -27.4, -20.0, 106.7, -1, 6335657) 
        spawnMobile("naboo", "imperial_first_lieutenant", 300, -7.2, -20.0, 100.8, 88, 6335657) 
        spawnMobile("naboo", "dark_trooper", 300, -12.5, -20.0, 104.7, 0, 6335657) 
        spawnMobile("naboo", "imperial_warrant_officer_ii", 300, -17.5, -20.0, 116.6, -176, 6335657) 
        spawnMobile("naboo", "imperial_officer", 300, -36.4, -20.0, 117.9, -177, 6335657) 
        spawnMobile("naboo", "dark_trooper", 300, -36.6, -20.0, 112.4, -4, 6335657) 
        spawnMobile("naboo", "imperial_officer", 300, -8.9, -20.0, 95.1, -54, 6335657) 
        spawnMobile("naboo", "stormtrooper", 300, -13.2, -20.0, 101.1, 138, 6335657) 
        spawnMobile("naboo", "stormtrooper", 300, -13.2, -20.0, 96.5, 48, 6335657) 
 
 
    --Cell [6335659] 
        spawnMobile("naboo", "imperial_warrant_officer_i", 300, -7.4, -20.0, 67.0, 19, 6335659) 
        spawnMobile("naboo", "dark_trooper", 300, -7.0, -20.0, 76.0, 124, 6335659) 
        spawnMobile("naboo", "imperial_colonel", 300, 2.3, -20.0, 74.5, -136, 6335659) 
        spawnMobile("naboo", "dark_trooper", 300, 2.2, -20.0, 67.2, -56, 6335659) 
 
    --Cell [6335650] 
        spawnMobile("naboo", "dark_trooper", 300, 73.7, -12.0, 58.6, 89, 6335650) 
        spawnMobile("naboo", "dark_trooper", 300, 63.8, -12.0, 60.4, -178, 6335650) 
        spawnMobile("naboo", "imperial_colonel", 300, 53.0, -12.0, 60.0, -3, 6335650) 
        spawnMobile("naboo", "dark_trooper", 300, 47.0, -12.0, 57.7, -168, 6335650) 
        spawnMobile("naboo", "imperial_second_lieutenant", 300, 44.8, -12.0, 65.1, -176, 6335650) 
 
    --Cell [6335649] 
        spawnMobile("naboo", "dark_trooper", 300, 45.0, -12.0, 77.3, -1, 6335649) 
        spawnMobile("naboo", "imperial_officer", 300, 45.0, -12.0, 89.6, -179, 6335649) 
        spawnMobile("naboo", "imperial_warrant_officer_i", 300, 61.0, -12.0, 82.1, -179, 6335649) 
        spawnMobile("naboo", "imperial_first_lieutenant", 300, 65.5, -12.0, 84.6, 6, 6335649) 
        spawnMobile("naboo", "dark_trooper", 300, 73.6, -12.0, 83.0, 89, 6335649) 
 
    --Cell [6335651] 
        spawnMobile("naboo", "stormtrooper", 300, 19.5, -20.0, 115.7, 179, 6335651) 
        spawnMobile("naboo", "imperial_officer", 300, 12.4, -20.0, 122.9, -90, 6335651) 
        spawnMobile("naboo", "imperial_first_lieutenant", 300, 12.2, -20.0, 138.9, -91, 6335651) 
        spawnMobile("naboo", "imperial_officer", 300, 37.1, -20.0, 128.5, 179, 6335651) 
        spawnMobile("naboo", "dark_trooper", 300, 33.5, -20.0, 139.7, 89, 6335651) 
        spawnMobile("naboo", "imperial_warrant_officer_ii", 300, 39.1, -20.0, 139.4, -89, 6335651) 
        spawnMobile("naboo", "dark_trooper", 300, 20.8, -20.0, 131.3, 88, 6335651) 
        spawnMobile("naboo", "dark_trooper", 300, 17.6, -20.0, 125.0, 90, 6335651) 
        spawnMobile("naboo", "stormtrooper", 300, 23.5, -20.0, 125.1, -89, 6335651) 
end
