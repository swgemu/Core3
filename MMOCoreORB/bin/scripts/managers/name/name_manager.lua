package.path = package.path .. ";scripts/managers/name/?.lua"

DECLINED_DEVELOPER = 1;
DECLINED_FICT_RESERVED = 2;
DECLINED_PROFANE = 3;
DECLINED_RESERVED = 6;

require("species.bothan")
require("species.human")
require("species.ithorian")
require("species.moncal")
require("species.rodian")
require("species.sullustan")
require("species.trandoshan")
require("species.twilek")
require("species.wookiee")
require("species.zabrak")

require("resource.energy")
require("resource.mineral")
require("resource.plain")
require("resource.reactiveGas")

-- Imperial Trooper Prefixes
stormtrooperPrefixes = { "GK", "LK", "RK", "TK", "VK" };
scouttrooperPrefixes = { "SX", "GX", "VX", "CX", "NX" };
darktrooperPrefixes = { "JLB", "RAR", "KNP", "BCP", "RTZ" };
swamptrooperPrefixes = { "GL", "TL", "RL", "NL", "CL" };

filterWords = {
	{ "\\b[a@][a@]rrb[a@]\\b", DECLINED_FICT_RESERVED }, -- Aarrba
	{ "\\b[a@][a@]k\\b", DECLINED_FICT_RESERVED }, -- Aak
	{ "\\b[a@]be[1l][0o]th\\b", DECLINED_FICT_RESERVED }, -- Abeloth
	{ "\\b[a@]ckb[a@]r\\b", DECLINED_FICT_RESERVED }, -- Ackbar
	{ "\\b[a@]ckm[e3]n[a@]\\b", DECLINED_FICT_RESERVED }, -- Ackmena
	{ "\\b[a@]cr[o0][s5]-?krik\\b", DECLINED_FICT_RESERVED }, -- Acros-Krik
	{ "\\b[a@]diss\\b", DECLINED_FICT_RESERVED }, -- Adiss
	{ "\\b[a@][g6]ir[a@]\\b", DECLINED_FICT_RESERVED }, -- Agira
	{ "\\b[a@]g[o0][lL]er[g6][a@]\\b", DECLINED_FICT_RESERVED }, -- Agolerga
	{ "\\b[a@]jun[t7][a@]\\b", DECLINED_FICT_RESERVED }, -- Ajunta
	{ "\\b[a@]k-?r[e3]v\\b", DECLINED_FICT_RESERVED }, -- Ak-rev
	{ "\\b[a@]l[a@]v[a@]r\\b", DECLINED_FICT_RESERVED }, -- Alavar
	{ "\\b[a@]lli[e3]\\b", DECLINED_FICT_RESERVED }, -- Allie
	{ "\\b[a@]maiz[a@]\\b", DECLINED_FICT_RESERVED }, -- Amaiza
	{ "\\b[a@]m[e3]dd[a@]\\b", DECLINED_FICT_RESERVED }, -- Amedda
	{ "\\b[a@]m[i1]d[a@]l[a@]\\b", DECLINED_FICT_RESERVED }, -- Amidala
	{ "\\b[a@]nd[o0]r\\b", DECLINED_FICT_RESERVED }, -- Andor
	{ "\\b[a@]nduv[i1]l\\b", DECLINED_FICT_RESERVED }, -- Anduvil
	{ "\\b[a@]n[o0]r\\b", DECLINED_FICT_RESERVED }, -- Anor
	{ "\\b[a@]n[t7][i1]ll[e3][s5]\\b", DECLINED_FICT_RESERVED }, -- Antilles
	{ "\\b[a@]p[a@][i1]l[a@]n[a@]\\b", DECLINED_FICT_RESERVED }, -- Apailana
	{ "\\b[a@]r[g6][e3]n[t7][e3]\\b", DECLINED_FICT_RESERVED }, -- Argente
	{ "\\b[a@]rr[o0][g6][a@]n[t7]us\\b", DECLINED_FICT_RESERVED }, -- Arrogantus
	{ "\\b[a@][s5][h4]l[a@]\\b", DECLINED_FICT_RESERVED }, -- Ashla
	{ "\\b[a@]u[t7][e3]m\\b", DECLINED_FICT_RESERVED }, -- Autem
	{ "\\b[a@]xm[i1][s5]\\b", DECLINED_FICT_RESERVED }, -- Axmis
	{ "\\b[a@][z2][a@]d[i1]\\b", DECLINED_FICT_RESERVED }, -- Azadi
	{ "\\bb[@a][a@]b\\b", DECLINED_FICT_RESERVED }, -- Baab
	{ "\\bb[@a]b[a@]\\b", DECLINED_FICT_RESERVED }, -- Baba
	{ "\\bb[@aA]c[@a]r[a@]\\b", DECLINED_FICT_RESERVED }, -- Bacara
	{ "\\bb[@aA][g6]w[a@]\\b", DECLINED_FICT_RESERVED }, -- Bagwa
	{ "\\bb[@a]nd[o0]n\\b", DECLINED_FICT_RESERVED }, -- Bandon
	{ "\\bb[@a]n[e3]\\b", DECLINED_FICT_RESERVED }, -- Bane
	{ "\\bb[@a][oO0]b[a@]b\\b", DECLINED_FICT_RESERVED }, -- Baobab
	{ "\\bb[@a]r[@a]d[@a]\\b", DECLINED_FICT_RESERVED }, -- Barada
	{ "\\bb[@aA]r[r][e3]k\\b", DECLINED_FICT_RESERVED }, -- Barrek
	{ "\\bbb-?8\\b", DECLINED_FICT_RESERVED }, -- BB-8
	{ "\\bb[e3][e3]d[o0]\\b", DECLINED_FICT_RESERVED }, -- Beedo
	{ "\\bb[e3][e3][n5s]?\\b", DECLINED_FICT_RESERVED }, -- Been/Bees
	{ "\\bb[e3][il]{1,2}\\b", DECLINED_FICT_RESERVED }, -- Bel/Bell
	{ "\\bb[e3]q\\b", DECLINED_FICT_RESERVED }, -- Beq
	{ "\\bb[e3]ndu\\b", DECLINED_FICT_RESERVED }, -- Bendu
	{ "\\bb[i1l]bbl[e3]\\b", DECLINED_FICT_RESERVED }, -- Bibble
	{ "\\bb[i1l][i1l][@a]b[@a]\\b", DECLINED_FICT_RESERVED }, -- Bilaba
	{ "\\bb[i1l]nd[o0]\\b", DECLINED_FICT_RESERVED }, -- Bindo
	{ "\\bb[i1l]nks\\b", DECLINED_FICT_RESERVED }, -- Binks
	{ "\\bb[il1]u[e3]\\b", DECLINED_FICT_RESERVED }, -- Blue
	{ "\\bb[ll1]y\\b", DECLINED_FICT_RESERVED }, -- Bly
	{ "\\bb[o0][e3]d[o0]n[a@]w[il1][e3][e3]d[o0]\\b", DECLINED_FICT_RESERVED }, -- Boedonawieedo
	{ "\\bb[o0]nk[il1]k\\b", DECLINED_FICT_RESERVED }, -- Bonkik
	{ "\\bb[o0][s5][s5]k\\b", DECLINED_FICT_RESERVED }, -- Bossk
	{ "\\bbr[a@]k[il1][s5][s5]\\b", DECLINED_FICT_RESERVED }, -- Brakiss
	{ "\\bbr[e3][e3]mu\\b", DECLINED_FICT_RESERVED }, -- Breemu
	{ "\\bb[r][il1]d[g6][e3]r\\b", DECLINED_FICT_RESERVED }, -- Bridger
	{ "\\bbr[il1]qu[a@][il1][o0]n\\b", DECLINED_FICT_RESERVED }, -- Briqualon
	{ "\\bbulq\\b", DECLINED_FICT_RESERVED }, -- Bulq
	{ "\\bbu[s5]hf[o0]rb\\b", DECLINED_FICT_RESERVED }, -- Bushforb
	{ "\\bc[\\-\\s]?*3p[o0]\\b", DECLINED_FICT_RESERVED }, -- C-3PO
	{ "\\bc[']?b[a@][o0]th\\b", DECLINED_FICT_RESERVED }, -- C'baoth
	{ "\\bc[a@]ll[i1][s5]t[a@]\\b", DECLINED_FICT_RESERVED }, -- Callista
	{ "\\bc[a@]lr[i1][s5][s5][i1][a@]n\\b", DECLINED_FICT_RESERVED }, -- Calrissian
	{ "\\bc[a@]pt[i1][s5][o0]n\\b", DECLINED_FICT_RESERVED }, -- Captison
	{ "\\bc[a@]rr[i1]ck\\b", DECLINED_FICT_RESERVED }, -- Carrick
	{ "\\bch[a@]r[a@]l\\b", DECLINED_FICT_RESERVED }, -- Charal
	{ "\\bch[e3]wb[a@]cc[a@]\\b", DECLINED_FICT_RESERVED }, -- Chewbacca
	{ "\\bch[i1][o0]n\\b", DECLINED_FICT_RESERVED }, -- Chion
	{ "\\bch[i1]rp[a@]\\b", DECLINED_FICT_RESERVED }, -- Chirpa
	{ "\\bchukh[a@][\\-]?tr[o0]k\\b", DECLINED_FICT_RESERVED }, -- Chukha-Trok
	{ "\\bchyl[e3]r\\b", DECLINED_FICT_RESERVED }, -- Chyler
	{ "\\bc[o0][o0r][rd][re3]\\b", DECLINED_FICT_RESERVED }, -- Coorr/Corde
	{ "\\bc[o0]r[o0]bb\\b", DECLINED_FICT_RESERVED }, -- Corobb
	{ "\\bcr[a@]ck[e3]n\\b", DECLINED_FICT_RESERVED }, -- Cracken
	{ "\\bcrumb\\b", DECLINED_FICT_RESERVED }, -- Crumb
	{ "\\b(d+[a@]+n+k+[f]+[e3]+r+r+i+k+|f+[e3]+r+r+i+k+)\\b", DECLINED_FICT_RESERVED }, -- Dank Ferrik
	{ "\\bd['][a@]n\\b", DECLINED_FICT_RESERVED }, -- D'an
	{ "\\bd[a@][a@]l[a@]\\b", DECLINED_FICT_RESERVED }, -- Daala
	{ "\\bd[a@]m[e3]r[o0]n\\b", DECLINED_FICT_RESERVED }, -- Dameron
	{ "\\bd[a@]nl[e3]?|d[a@]nu\\b", DECLINED_FICT_RESERVED }, -- Danle\\Danu
	{ "\\bd[a@]rk[l1][i1][g6]ht[e3]r\\b", DECLINED_FICT_RESERVED }, -- Darklighter
	{ "\\bd[a@]rth\\b", DECLINED_FICT_RESERVED }, -- Darth
	{ "\\bd[a@][s5][s5]yn[e3]\\b", DECLINED_FICT_RESERVED }, -- Dassyne
	{ "\\bd[e3]ll[s5][o0]\\b", DECLINED_FICT_RESERVED }, -- Dellso
	{ "\\bd[e3]n[g6][a@]r\\b", DECLINED_FICT_RESERVED }, -- Dengar
	{ "\\bd[e3]r[l1][i1]n\\b", DECLINED_FICT_RESERVED }, -- Derlin
	{ "\\bd[e3][s5][a@][n3][n3]\\b", DECLINED_FICT_RESERVED }, -- Desann
	{ "\\bd[i1][o0]\\b", DECLINED_FICT_RESERVED }, -- Dio
	{ "\\bdj[a@]r[i1]n\\b", DECLINED_FICT_RESERVED }, -- Djarin
	{ "\\bd[o0]d[o0]nn[a@]\\b", DECLINED_FICT_RESERVED }, -- Dodonna
	{ "\\bd[o0]f[i1]n[e3]\\b", DECLINED_FICT_RESERVED }, -- Dofine
	{ "\\bd[o0]k[e3][s5]\\b", DECLINED_FICT_RESERVED }, -- Dokes
	{ "\\bd[o0][o0]ku\\w*\\b", DECLINED_FICT_RESERVED }, -- Dooku
	{ "\\bd[o0]rm[e3]\\b", DECLINED_FICT_RESERVED }, -- Dorme
	{ "\\bd[o0]wm[e3][i1][a@]\\b", DECLINED_FICT_RESERVED }, -- Dowmeia
	{ "\\bd[o0]z[a@]\\b", DECLINED_FICT_RESERVED }, -- Doza
	{ "\\bdum[e3]|dun[e3]|dur[a@]l|dur[g6]e|durr[o0]n\\w*\\b", DECLINED_FICT_RESERVED }, -- Dume\Dune\Dural\Durge\Durron
	{ "\\b[e3][e3]kw[a@]y\\w*\\b", DECLINED_FICT_RESERVED }, -- Eekway
	{ "\\b[e3][l1]d[a@]r\\w*\\b", DECLINED_FICT_RESERVED }, -- Eldar
	{ "\\b[e3][l1][s5]b[e3]th\\b", DECLINED_FICT_RESERVED }, -- Elsbeth
	{ "\\b[e3]nd[o0]c[o0]tt\\w*\\b", DECLINED_FICT_RESERVED }, -- Endocott
	{ "\\b[e3]r[s5][o0]\\b", DECLINED_FICT_RESERVED }, -- Erso
	{ "\\b[e3]v[a@]z[a@]n\\w*\\b", DECLINED_FICT_RESERVED }, -- Evazan
	{ "\\bf[a@]rnm[i1]r\\w*\\b", DECLINED_FICT_RESERVED }, -- Farnmir
	{ "\\bf[a@]rr\\w*\\b", DECLINED_FICT_RESERVED }, -- Farr
	{ "\\bf[a@]yt[o0]nn[i1]\\w*\\b", DECLINED_FICT_RESERVED }, -- Faytonni
	{ "\\bf[a@]z[o0]n\\w*\\b", DECLINED_FICT_RESERVED }, -- Fazon
	{ "\\bf[e3]l|f[e3]tt\\w*\\b", DECLINED_FICT_RESERVED }, -- Fel\Fett
	{ "\\bf[e3]y['][l1]y[a@]\\b", DECLINED_FICT_RESERVED }, -- Fey'lya
	{ "\\bf[i1][e3][s5][o0]\\b", DECLINED_FICT_RESERVED }, -- Fieso
	{ "\\bf[i1]nn\\b", DECLINED_FICT_RESERVED }, -- Finn
	{ "\\bf[i1][o0][l1][l1][a@]\\b", DECLINED_FICT_RESERVED }, -- Fiolla
	{ "\\bf[i1][s5]t[o0]\\b", DECLINED_FICT_RESERVED }, -- Fisto
	{ "\\bf[o0]rtun[a@]\\b", DECLINED_FICT_RESERVED }, -- Fortuna
	{ "\\bfr[i1]x\\b", DECLINED_FICT_RESERVED }, -- Frix
	{ "\\bfr[o0][o0][l1]\\b", DECLINED_FICT_RESERVED }, -- Frool
	{ "\\bfu[l1]crum\\b", DECLINED_FICT_RESERVED }, -- Fulcrum
	{ "\\bg[a@]ff\\b", DECLINED_FICT_RESERVED }, -- Gaff
	{ "\\bg[a@][l1][l1][a@]ndr[o0]\\b", DECLINED_FICT_RESERVED }, -- Gallandro
	{ "\\bg[a@][l1][l1][i1][a@]\\b", DECLINED_FICT_RESERVED }, -- Gallia
	{ "\\bg[a@]r[g6][a@]n\\b|\\bg[a@]r[i1]nd[a@]n\\b", DECLINED_FICT_RESERVED }, -- Gargan\Garindan
	{ "\\bg[a@][s5]g[a@]n[o0]\\b", DECLINED_FICT_RESERVED }, -- Gasgano
	{ "\\bg[e3]rr[e3]r[a@]\\b", DECLINED_FICT_RESERVED }, -- Gerrera
	{ "\\bgh[e3]nt\\b", DECLINED_FICT_RESERVED }, -- Ghent
	{ "\\bg[o0]d[a@][l1]h[i1]\\b", DECLINED_FICT_RESERVED }, -- Godalhi
	{ "\\bg[o0]rr\\b", DECLINED_FICT_RESERVED }, -- Gorr
	{ "\\bgr[a@]gr[a@]|gr[a@]hrk|gr[a@]mm[e3][l1]\\b", DECLINED_FICT_RESERVED }, -- Gragra\Grahrk\Grammel
	{ "\\bgr[ea3@]?[ey]?j?a?t?u?s?\\b|\\bgr[e3][e3](do)|([a@]t[a@])\\b", DECLINED_FICT_RESERVED }, -- Gree\Greeata\Greedo\Greejatus\Grey
	{ "\\bgr[i1][e3]v[o0]u[s5]\\b", DECLINED_FICT_RESERVED }, -- Grievous
	{ "\\bgr[o0]gu\\b", DECLINED_FICT_RESERVED }, -- Grogu
	{ "\\bgunr[a@]y\\b", DECLINED_FICT_RESERVED }, -- Gunray
	{ "\\bgu[o0]\\b", DECLINED_FICT_RESERVED }, -- Guo
	{ "\\bh[a@][a@]k[o0]\\b", DECLINED_FICT_RESERVED }, -- Haako
	{ "\\bh[a@]ll([a@]|[o0]r[a@]n)?\\b", DECLINED_FICT_RESERVED }, -- Halla\Halloran
	{ "\\bh[a@]t[i1]\\b", DECLINED_FICT_RESERVED }, -- Hati
	{ "\\bh[i1]d[a@]\\b", DECLINED_FICT_RESERVED }, -- Hida
	{ "\\bh[i1][l1][l1]\\b", DECLINED_FICT_RESERVED }, -- Hill
	{ "\\bHk-\\d+\\b", DECLINED_FICT_RESERVED }, -- HK-47\HK-50
	{ "\\bh[o0][l1]df[a@][s5]t|h[o0][l1]d[o0]\\b", DECLINED_FICT_RESERVED }, -- Holdfast\Holdo
	{ "\\bh[o0][o0r][dn]\\b", DECLINED_FICT_RESERVED }, -- Hood\Hord\Horn
	{ "\\bhu(?:x|y[a@]ng)\\b", DECLINED_FICT_RESERVED }, -- Hux\Huyang
	{ "\\bIg-\\d+\\b", DECLINED_FICT_RESERVED }, -- IG-88
	{ "\\bimw[e3]\\b", DECLINED_FICT_RESERVED }, -- Imwe
	{ "\\bi[s5][a@]rd\\b", DECLINED_FICT_RESERVED }, -- Isard
	{ "\\bi[s5][o0][l1]d[e3]r\\b", DECLINED_FICT_RESERVED }, -- Isolder
	{ "\\bizr[i1]n[a@]\\b", DECLINED_FICT_RESERVED }, -- Izrina
	{ "\\bj[a@]bb[a@]\\b", DECLINED_FICT_RESERVED }, -- Jabba
	{ "\\bj[a@]m[i1][l1][l1][i1][a@]\\b", DECLINED_FICT_RESERVED }, -- Jamillia
	{ "\\bj[a@]n[s5][o0]n\\b", DECLINED_FICT_RESERVED }, -- Janson
	{ "\\bj[a@]rru[s5]\\b", DECLINED_FICT_RESERVED }, -- Jarrus
	{ "\\bj[a@][s5]k[a@]\\b", DECLINED_FICT_RESERVED }, -- Jaska
	{ "\\bj[a@]xx[o0]n\\b", DECLINED_FICT_RESERVED }, -- Jaxxon
	{ "\\bj[e3]d[i1]\\b", DECLINED_FICT_RESERVED }, -- Jedi
	{ "\\bj[e3]r[e3]c\\b", DECLINED_FICT_RESERVED }, -- Jerec
	{ "\\bj[e3]rj[e3]rr[o0]d\\b", DECLINED_FICT_RESERVED }, -- Jerjerrod
	{ "\\bj[e3][s5][s5][a@]\\b", DECLINED_FICT_RESERVED }, -- Jessa
	{ "\\bj[e3]tt[s5]t[e3]r\\b", DECLINED_FICT_RESERVED }, -- Jettster
	{ "\\bj[i1]nn\\b", DECLINED_FICT_RESERVED }, -- Jinn
	{ "\\bj[i1]r[a@]\\b", DECLINED_FICT_RESERVED }, -- Jira
	{ "\\bj[o0]w[i1]l\\b", DECLINED_FICT_RESERVED }, -- Jowil
	{ "\\bjuh[a@]n[i1]\\b", DECLINED_FICT_RESERVED }, -- Juhani
	{ "\\bjuk[a@][s5][s5][a@]\\b", DECLINED_FICT_RESERVED }, -- Jukassa
	{ "\\bju[l1]p[a@]\\b", DECLINED_FICT_RESERVED }, -- Julpa
	{ "\\bk[-']?[2]?[5s]?[0o]\\b", DECLINED_FICT_RESERVED }, -- K-2SO
	{ "\\bk'kruhk\\b", DECLINED_FICT_RESERVED }, -- K'Kruhk
	{ "\\bk[a@]b[e3]\\b", DECLINED_FICT_RESERVED }, -- Kabe
	{ "\\bk[a@][i1]nk\\b", DECLINED_FICT_RESERVED }, -- Kaink
	{ "\\bk[a@][l1][l1]u[s5]\\b", DECLINED_FICT_RESERVED }, -- Kallus
	{ "\\bk[a@]n[a@]t[a@]\\b", DECLINED_FICT_RESERVED }, -- Kanata
	{ "\\bk[a@]ng\\b", DECLINED_FICT_RESERVED }, -- Kang
	{ "\\bk[a@]n[o0][s5]\\b", DECLINED_FICT_RESERVED }, -- Kanos
	{ "\\bk(?:[a@]r[a@]th|[a@]rg[a@]|[a@]rrd[e3])?\\b", DECLINED_FICT_RESERVED }, -- Karath\Karga\Karrde
	{ "\\bk[a@]t[a@]rn\\b", DECLINED_FICT_RESERVED }, -- Katarn
	{ "\\bk[e3](?:e|en|ed['’]k[a@]k)\\b", DECLINED_FICT_RESERVED }, -- Kee\Keed'kak
	{ "\\bk[e3][nm][o0][beiy1!]+\\b", DECLINED_FICT_RESERVED }, -- Kenobi
	{ "\\bk[e3]tw[o0]l\\b", DECLINED_FICT_RESERVED }, -- Ketwol
	{ "\\bk[i1]?[-_]?ad[i1]?[-_]?mund[i1]\\b", DECLINED_FICT_RESERVED }, -- Ki-Adi-Mundi
	{ "\\bk[i1]t[s5]t[e3]r\\b", DECLINED_FICT_RESERVED }, -- Kitster
	{ "\\bk[o0]l[a@]r\\b", DECLINED_FICT_RESERVED }, -- Kolar
	{ "\\bk[o0][o0]ng?\\b", DECLINED_FICT_RESERVED }, -- Koon\Koong
	{ "\\bko[trh]+\\b", DECLINED_FICT_RESERVED }, -- Korr\Koth
	{ "\\bkr[e3]nn[i1]c\\b", DECLINED_FICT_RESERVED }, -- Krennic
	{ "\\bkry[z3][e3]\\b", DECLINED_FICT_RESERVED }, -- Kryze
	{ "\\bku[a@]t\\b", DECLINED_FICT_RESERVED }, -- Kuat
	{ "\\bkun\\b", DECLINED_FICT_RESERVED }, -- Kun
	{ "\\bl[a@]h\\b", DECLINED_FICT_RESERVED }, -- Lah
	{ "\\bl[a@]r[s5]\\b", DECLINED_FICT_RESERVED }, -- Lars
	{ "\\bl[e3][e3]k[T][a@]r\\b", DECLINED_FICT_RESERVED }, -- Leektar
	{ "\\bl[e3][i1][a@]\\b", DECLINED_FICT_RESERVED }, -- Leia
	{ "\\bl[o0]b[o0]t\\b", DECLINED_FICT_RESERVED }, -- Lobot
	{ "\\bl[o0]gr[a@]y\\b", DECLINED_FICT_RESERVED }, -- Logray
	{ "\\b(?:l[0o@]tt\\s?dod)\\b", DECLINED_FICT_RESERVED }, -- Lott Dod
	{ "\\blufb[a@]\\b", DECLINED_FICT_RESERVED }, -- Lufba
	{ "\\blum[i1]y[a@]\\b", DECLINED_FICT_RESERVED }, -- Lumiya
	{ "\\bm[a@]d[i1]n[e3]\\b", DECLINED_FICT_RESERVED }, -- Madine
	{ "\\bm[a@]g[a@][l1][o0][o0]f\\b", DECLINED_FICT_RESERVED }, -- Magaloof
	{ "\\bma[i1!l@]+k\\b|\\bma[l1!]+[ae@]*r\\b|\\bm[a@][il1!@]ar\\b|\\bmai\\b|\\bmak\\b|\\bmal[a@]k\\b|\\bmal[a@]r\\b", DECLINED_FICT_RESERVED }, -- Mai/Mak/Malak/Malar
	{ "\\bm[a@][l1]bu[s5]|m[a@][l1]c[o0]m\\b", DECLINED_FICT_RESERVED }, -- Malbus\Malcom
	{ "\\bm[a@][l1][e3]?[-_]?d[e3][e3]\\b", DECLINED_FICT_RESERVED }, -- Male-Dee
	{ "\\bm[a@][l1]gu[s5]\\b", DECLINED_FICT_RESERVED }, -- Malgus
	{ "\\bm[a@]ndr[e3][l1][l1]\\b", DECLINED_FICT_RESERVED }, -- Mandrell
	{ "\\bm[ae@4]+r[ae@4]?[-_]?j[ae@4]+d[ae@4]?\\b", DECLINED_FICT_RESERVED }, -- Mara-Jade
	{ "\\bm[a@]u[l1]\\b", DECLINED_FICT_RESERVED }, -- Maul
	{ "\\bm[a@]wh[o0]n[i1]c\\b", DECLINED_FICT_RESERVED }, -- Mawhonic
	{ "\\bmcc[o0][o0][lL]\\b", DECLINED_FICT_RESERVED }, -- McCool
	{ "\\bmckn[i1]v[e3][s5]\\b", DECLINED_FICT_RESERVED }, -- McKnives
	{ "\\bm[e3][a@]d[e3]\\b", DECLINED_FICT_RESERVED }, -- Meade
	{ "\\bm[e3]d?[-_]?b[e3]q\\b", DECLINED_FICT_RESERVED }, -- Med-Beq
	{ "\\bm[e3]d[o0]n\\b", DECLINED_FICT_RESERVED }, -- Medon
	{ "\\bm[e3][l1][a@][s5]\\b", DECLINED_FICT_RESERVED }, -- Melas
	{ "\\bm[e3][l1][e3][e3]\\b", DECLINED_FICT_RESERVED }, -- Melee
	{ "\\bm[e3]rum[e3]ru\\b", DECLINED_FICT_RESERVED }, -- Merumeru
	{ "\\bm[e3]t[o0]n[a@][e3]\\b", DECLINED_FICT_RESERVED }, -- Metonae
	{ "\\bm[i1]d[a@]ny[l1]\\b", DECLINED_FICT_RESERVED }, -- Midanyl
	{ "\\bm[i1]n|m[o0][e3]|m[o0]n\\b", DECLINED_FICT_RESERVED }, -- Min\Moe\Mon
	{ "\\bm[o0][o0]r[e3]\\b", DECLINED_FICT_RESERVED }, -- Moore
	{ "\\bm[o0]thm[a@]\\b", DECLINED_FICT_RESERVED }, -- Mothma
	{ "\\bm[o0]tt[i1]\\b", DECLINED_FICT_RESERVED }, -- Motti
	{ "\\bm[o0]ud[a@]m[a@]\\b", DECLINED_FICT_RESERVED }, -- Moudama
	{ "\\bmuft[a@]k\\b", DECLINED_FICT_RESERVED }, -- Muftak
	{ "\\bn[a@]b[e3]rr[i1][e3]\\b", DECLINED_FICT_RESERVED }, -- Naberrie
	{ "\\bn[a@]dd|n[a@]d[o0]n\\b", DECLINED_FICT_RESERVED }, -- Nadd\Nadon
	{ "\\bn[a@][s5][s5]\\b", DECLINED_FICT_RESERVED }, -- Nass
	{ "\\bn[e3][e3]d[a@]\\b", DECLINED_FICT_RESERVED }, -- Needa
	{ "\\bn[e3]y[o0]\\b", DECLINED_FICT_RESERVED }, -- Neyo
	{ "\\bnh[i1][lL1][iI1]u[s5]\\b", DECLINED_FICT_RESERVED }, -- Nhilius
	{ "\\bn[i1][l1][o0]\\b", DECLINED_FICT_RESERVED }, -- Nilo
	{ "\\bn[o0]d\\b", DECLINED_FICT_RESERVED }, -- Nod
	{ "\\bn[o0]rd\\b", DECLINED_FICT_RESERVED }, -- Nord
	{ "\\bnud[o0]|nunb\\b", DECLINED_FICT_RESERVED }, -- Nudo\Nunb
	{ "\\bnym\\b", DECLINED_FICT_RESERVED }, -- Nym
	{ "\\bob[i1]?[-]?w[a@]n\\b", DECLINED_FICT_RESERVED }, -- Obi-Wan
	{ "\\bod[l1][e3]\\b", DECLINED_FICT_RESERVED }, -- Odle
	{ "\\bodum[i1]n\\b", DECLINED_FICT_RESERVED }, -- Odumin
	{ "\\boff[e3][e3]\\b", DECLINED_FICT_RESERVED }, -- Offee
	{ "\\bo[i1]cunn\\b", DECLINED_FICT_RESERVED }, -- Oicunn
	{ "\\bo[l1][i1][e3]\\b", DECLINED_FICT_RESERVED }, -- Olie
	{ "\\bon[a@][s5][i1]\\b", DECLINED_FICT_RESERVED }, -- Onasi
	{ "\\bo[o0][l1][a@]|[o0]rd[o0]\\b", DECLINED_FICT_RESERVED }, -- Oola\Ordo
	{ "\\borg[a@]n[a@]\\b", DECLINED_FICT_RESERVED }, -- Organa
	{ "\\born\\s*fr[e3]+(\\s*t[ae@4]+)?\\s*taa\\b", DECLINED_FICT_RESERVED }, -- Orn Free Taa
	{ "\\borr[e3][i1][l1][o0][s5]\\b", DECLINED_FICT_RESERVED }, -- Orreilos
	{ "\\borr[i1]m[a@][a@]rk[o0]\\b", DECLINED_FICT_RESERVED }, -- Orrimaarko
	{ "\\bor[s5]\\b", DECLINED_FICT_RESERVED }, -- Ors
	{ "\\bozz[e3][l1]\\b", DECLINED_FICT_RESERVED }, -- Ozzel
	{ "\\bp[a@]b[l1][o0]?[-]?j[i1][l1][l1]\\b", DECLINED_FICT_RESERVED }, -- Pablo-Jill
	{ "\\bp[a@]dd[i1][e3]\\b", DECLINED_FICT_RESERVED }, -- Paddie
	{ "\\bp[a@]dm[e3]\\b", DECLINED_FICT_RESERVED }, -- Padme
	{ "\\bp[a@]g[a@][l1][i1][e3][s5]\\b", DECLINED_FICT_RESERVED }, -- Pagalies
	{ "\\bp[a@][l1]p[a@]t[i1]n[e3]\\b", DECLINED_FICT_RESERVED }, -- Palpatine
	{ "\\bp[a@]n[a@]k[a@]\\b", DECLINED_FICT_RESERVED }, -- Panaka
	{ "\\bp[a@]p[a@]n[o0][i1]d[a@]\\b", DECLINED_FICT_RESERVED }, -- Papanoida
	{ "\\bp[a@]p[l1][o0][o0]\\b", DECLINED_FICT_RESERVED }, -- Paploo
	{ "\\bp[e3][a@]c[e3]br[i1]ng[e3]r\\b", DECLINED_FICT_RESERVED }, -- Peacebringer
	{ "\\bp[e3][l1][l1][a@][e3][o0]n\\b", DECLINED_FICT_RESERVED }, -- Pellaeon
	{ "\\bp[e3]n[i1]n\\b", DECLINED_FICT_RESERVED }, -- Penin
	{ "\\bph[a@][s5]m[a@]\\b", DECLINED_FICT_RESERVED }, -- Phasma
	{ "\\bp[i1][e3][l1][l1]|p[i1][e3]tt\\b", DECLINED_FICT_RESERVED }, -- Piell\Piett
	{ "\\bp[l1][a@]gu[e3][i1][s5]\\b", DECLINED_FICT_RESERVED }, -- Plagueis
	{ "\\bp[l1]utt\\b", DECLINED_FICT_RESERVED }, -- Plutt
	{ "\\bp[o0][e3]\\b", DECLINED_FICT_RESERVED }, -- Poe
	{ "\\bp[o0]gg[l1][e3]\\b", DECLINED_FICT_RESERVED }, -- Poggle
	{ "\\bp[o0][o0]f\\b", DECLINED_FICT_RESERVED }, -- Poof
	{ "\\bp[o0]rk[i1]n[s5]\\b", DECLINED_FICT_RESERVED }, -- Porkins
	{ "\\bpr[a@]j[i1]\\b", DECLINED_FICT_RESERVED }, -- Praji
	{ "\\bq[e3][l1]?[-_]?dr[o0]m[a@]\\b", DECLINED_FICT_RESERVED }, -- Qel-Droma
	{ "\\bqu[a@]d[i1]n[a@]r[o0][s5]\\b", DECLINED_FICT_RESERVED }, -- Quadinaros
	{ "\\bqu[i1]?[-]?g[o0]n\\b", DECLINED_FICT_RESERVED }, -- Qui-Gon
	{ "\\br2?[-_]?d2\\b", DECLINED_FICT_RESERVED }, -- R2-D2
	{ "\\br[a@]hn\\b", DECLINED_FICT_RESERVED }, -- Rahn
	{ "\\br[a@][l1]t[e3]r\\b", DECLINED_FICT_RESERVED }, -- Ralter
	{ "\\br[a@]nc[i1][s5][i1][s5]\\b", DECLINED_FICT_RESERVED }, -- Rancisis
	{ "\\br[a@]pp[e3]rtun[i1][e3]\\b", DECLINED_FICT_RESERVED }, -- Rappertunie
	{ "\\br[a@]u\\b", DECLINED_FICT_RESERVED }, -- Rau
	{ "\\br[e3]b[o0]\\b", DECLINED_FICT_RESERVED }, -- Rebo
	{ "\\br[e3][e3]?[-_]?y[e3][e3][s5]\\b", DECLINED_FICT_RESERVED }, -- Ree-Yees
	{ "\\br[e3]k[a@]b\\b", DECLINED_FICT_RESERVED }, -- Rekab
	{ "\\br[e3]kk[o0]n\\b", DECLINED_FICT_RESERVED }, -- Rekkon
	{ "\\br[e3]nd[a@]r\\b", DECLINED_FICT_RESERVED }, -- Rendar
	{ "\\br[e3]t[i1]\\b", DECLINED_FICT_RESERVED }, -- Reti
	{ "\\br[e3]v[a@]n\\w*\\b", DECLINED_FICT_RESERVED }, -- Revan
	{ "\\br[e3]y\\b", DECLINED_FICT_RESERVED }, -- Rey
	{ "\\brh[o0]\\b", DECLINED_FICT_RESERVED }, -- Rho
	{ "\\br[i1][e3][e3]k[a@]n\\b", DECLINED_FICT_RESERVED }, -- Rieekan
	{ "\\br[o0][o0]k|r[o0][o0]r\\b", DECLINED_FICT_RESERVED }, -- Rook\Roor
	{ "\\br[o0][o0][s5][e3]\\b", DECLINED_FICT_RESERVED }, -- Roose
	{ "\\bruck[l1][i1]n\\b", DECLINED_FICT_RESERVED }, -- Rucklin
	{ "\\brukh\\b", DECLINED_FICT_RESERVED }, -- Rukh
	{ "\\bry[s5]t[a@][l1][l1]\\b", DECLINED_FICT_RESERVED }, -- Rystall
	{ "\\bryyd[e3]r\\b", DECLINED_FICT_RESERVED }, -- Ryyder
	{ "\\bs[a@]b[e3]\\b", DECLINED_FICT_RESERVED }, -- Sabe
	{ "\\bs[a@][e3][l1]t?[-_]?m[a@]r[a@][e3]\\b", DECLINED_FICT_RESERVED }, -- Saelt-Marae
	{ "\\bs[a@][l1]p[o0]r[i1]n\\b", DECLINED_FICT_RESERVED }, -- Salporin
	{ "\\b[s$5]+[a@4]+n(?:d[a@4]+g[ae@4]?)?\\b", DECLINED_FICT_RESERVED }, -- San\Sandage
	{ "\\bs[a@]t[o0]\\b", DECLINED_FICT_RESERVED }, -- Sato
	{ "\\bs[a@]x[o0]n\\b", DECLINED_FICT_RESERVED }, -- Saxon
	{ "\\bscr[a@]mb[a@][s5]\\b", DECLINED_FICT_RESERVED }, -- Scrambas
	{ "\\bscr[e3][e3]d\\b", DECLINED_FICT_RESERVED }, -- Screed
	{ "\\bs[e3]bu[l1]b[a@]\\b", DECLINED_FICT_RESERVED }, -- Sebulba
	{ "\\bs[e3]cur[a@]\\b", DECLINED_FICT_RESERVED }, -- Secura
	{ "\\bs[e3][i1]rr\\b", DECLINED_FICT_RESERVED }, -- Seirr
	{ "\\bs[e3]n[e3][s5]c[a@]\\b", DECLINED_FICT_RESERVED }, -- Senesca
	{ "\\b[s$5]+[h#]+[a@4]+[a@4]+[k#]+[t7]+[i1!]+\\b", DECLINED_FICT_RESERVED }, -- Shaak Ti
	{ "\\bsh[a@][l1][i1]qu[a@]\\b", DECLINED_FICT_RESERVED }, -- Shaliqua
	{ "\\bsh[a@]n\\b", DECLINED_FICT_RESERVED }, -- Shan
	{ "\\bsh[e3][s5][s5][a@]un\\b", DECLINED_FICT_RESERVED }, -- Shessaun
	{ "\\bs[h][i1][r][e3]\\b", DECLINED_FICT_RESERVED }, -- Shire
	{ "\\bs[h][o0][d][u]\\b", DECLINED_FICT_RESERVED }, -- Shodu
	{ "\\bs[i1][d][i1][o0][uv][s5$]\\b", DECLINED_FICT_RESERVED }, -- Sidious
	{ "\\b[s5$[i1][n][g]|[s5$][i1][o0][n]|[s5$][i1][t][h]\\b", DECLINED_FICT_RESERVED }, -- Sing\Sion\Sith
	{ "\\bs[i1][vu][r][aA@][k]\\b", DECLINED_FICT_RESERVED }, -- Sivrak
	{ "\\bs[k][o][l1i][l1i]\\b", DECLINED_FICT_RESERVED }, -- Skoll
	{ "\\bs[k][y][w][a@][l11][k][e3][r]\\b", DECLINED_FICT_RESERVED }, -- Skywalker
	{ "\\bs[l1][e3][a@][z][e3][b][a@][g][g][a@][n][o0]\\b", DECLINED_FICT_RESERVED }, -- Sleazebaggano
	{ "\\bs[n][i1l][t][k][i1l][n]\\b", DECLINED_FICT_RESERVED }, -- Snitkin
	{ "\\bs[n][o0][k][e3]\\b", DECLINED_FICT_RESERVED }, -- Snoke
	{ "\\bs[n][o0][o0][t][l1][e3][s5$]\\b", DECLINED_FICT_RESERVED }, -- Snootles
	{ "\\bs[o0][l1][o0]\\b", DECLINED_FICT_RESERVED }, -- Solo
	{ "\\bs[t][a@][r][k]\\b", DECLINED_FICT_RESERVED }, -- Stark
	{ "\\b[s$5]+[uüû]+[r]+[i1!]+[k]+\\b|\\bs[uüû]+[nr]+[i1!]+[d]+[e3]+[r]+\\b|\\bs[uüû]+\\b", DECLINED_FICT_RESERVED }, -- Su/Sunrider/Surik
	{ "\\bsw[a@]n\\b", DECLINED_FICT_RESERVED }, -- Swan
	{ "\\bsy[l1][o0]\\b", DECLINED_FICT_RESERVED }, -- Sylo
	{ "\\bsyndu[l1][lL][a@]\\b", DECLINED_FICT_RESERVED }, -- Syndulla
	{ "\\bt[e3]?[-_]?m[4fF]\\b", DECLINED_FICT_RESERVED }, -- T3-M4
	{ "\\bt[a@]ch[i1]\\b", DECLINED_FICT_RESERVED }, -- Tachi
	{ "\\bt[a@]gg[e3]\\b", DECLINED_FICT_RESERVED }, -- Tagge
	{ "\\bt[a@]mb[o0]r\\b", DECLINED_FICT_RESERVED }, -- Tambor
	{ "\\bt[a@]n[e3][e3][l1]\\b", DECLINED_FICT_RESERVED }, -- Taneel
	{ "\\bt[a@]n[o0]\\b", DECLINED_FICT_RESERVED }, -- Tano
	{ "\\bt[a@]rffu[l1]\\b", DECLINED_FICT_RESERVED }, -- Tarfful
	{ "\\bt[a@]r[i1][a@]|t[a@]rk[i1]n|t[a@]rk[o0]v\\b", DECLINED_FICT_RESERVED }, -- Taria\Tarkin\Tarkov
	{ "\\bt[a@]rp[a@][l1][s5]\\b", DECLINED_FICT_RESERVED }, -- Tarpals
	{ "\\bt[e3]ck[l1][a@]\\b", DECLINED_FICT_RESERVED }, -- Teckla
	{ "\\bt[e3][e3]k|t[e3][e3]r[s5]\\b", DECLINED_FICT_RESERVED }, -- Teek\Teers
	{ "\\bt[e3]kk[a@]\\b", DECLINED_FICT_RESERVED }, -- Tekka
	{ "\\bt[e3]n[e3]br[o0]u[s5]\\b", DECLINED_FICT_RESERVED }, -- Tenebrous
	{ "\\bt[e3]r[a@]k\\b", DECLINED_FICT_RESERVED }, -- Terak
	{ "\\bt[e3][s5][s5][e3]k\\b", DECLINED_FICT_RESERVED }, -- Tessek
	{ "\\bth[a@]r[e3]n\\b", DECLINED_FICT_RESERVED }, -- Tharen
	{ "\\bth[i1]r[e3]\\b", DECLINED_FICT_RESERVED }, -- Thire
	{ "\\bthr[a@]wn\\b", DECLINED_FICT_RESERVED }, -- Thrawn
	{ "\\bt[i1]c[o0]\\b", DECLINED_FICT_RESERVED }, -- Tico
	{ "\\bt[i1][i1]n\\b", DECLINED_FICT_RESERVED }, -- Tiin
	{ "\\bt[i1]kk[e3][s5]\\b", DECLINED_FICT_RESERVED }, -- Tikkes
	{ "\\bt[i1][l1][l1][s5]\\b", DECLINED_FICT_RESERVED }, -- Tills
	{ "\\bt[o0][o0]r[a@]\\b", DECLINED_FICT_RESERVED }, -- Toora
	{ "\\bt[o0][s5][h]\\b", DECLINED_FICT_RESERVED }, -- Tosh
	{ "\\bt[o0]w[a@]n[i1]\\b", DECLINED_FICT_RESERVED }, -- Towani
	{ "\\btr[a@]y[a@]\\b", DECLINED_FICT_RESERVED }, -- Traya
	{ "\\btr[e3]b[l1][a@]nc\\b", DECLINED_FICT_RESERVED }, -- Treblanc
	{ "\\btr[e3]b[o0]r\\b", DECLINED_FICT_RESERVED }, -- Trebor
	{ "\\bty[e3]r[e3][l1][l1]\\b", DECLINED_FICT_RESERVED }, -- Tyerell
	{ "\\btyph[o0]\\b", DECLINED_FICT_RESERVED }, -- Typho
	{ "\\btz[i1]zvvt\\b", DECLINED_FICT_RESERVED }, -- Tzizvvt
	{ "\\bump[a@][s5][s5]?[-_]?[s5]t[a@]y\\b", DECLINED_FICT_RESERVED }, -- Umpass-stay
	{ "\\bundu[l1][i1]\\b", DECLINED_FICT_RESERVED }, -- Unduli
	{ "\\bv[a@]d[e3]r\\b", DECLINED_FICT_RESERVED }, -- Vader
	{ "\\bv[a@][l1][o0]rum\\b", DECLINED_FICT_RESERVED }, -- Valorum
	{ "\\bv[a@][o0]\\b", DECLINED_FICT_RESERVED }, -- Vao
	{ "\\bv[e3][e3]k[a@]n\\b", DECLINED_FICT_RESERVED }, -- Veekan
	{ "\\bv[e3][e3]r[s5]\\b", DECLINED_FICT_RESERVED }, -- Veers
	{ "\\bv[e3][l1]d\\b", DECLINED_FICT_RESERVED }, -- Veld
	{ "\\bv[e3]ntr[e3][s5][s5]\\b", DECLINED_FICT_RESERVED }, -- Ventress
	{ "\\bv[e3]rg[e3]r[e3]\\b", DECLINED_FICT_RESERVED }, -- Vergere
	{ "\\bv[i1]d[a@]\\b", DECLINED_FICT_RESERVED }, -- Vida
	{ "\\bv[i1]t[i1][a@]t[e3]\\b", DECLINED_FICT_RESERVED }, -- Vitiate
	{ "\\bv[i1]z[s5][l1][a@]\\b", DECLINED_FICT_RESERVED }, -- Vizsla
	{ "\\bv[o0][s5]\\b", DECLINED_FICT_RESERVED }, -- Vos
	{ "\\bv[o0][s5][a@]\\b|\\bv[o0][z][o0]\\b", DECLINED_FICT_RESERVED }, -- Vosa\Vozo
	{ "\\bw[a@][l1]d\\b", DECLINED_FICT_RESERVED }, -- Wald
	{ "\\bw[a@]rr[i1]ck\\b", DECLINED_FICT_RESERVED }, -- Warrick
	{ "\\bw[a@]tt[o0]\\b", DECLINED_FICT_RESERVED }, -- Watto
	{ "\\bw[e3][s5][e3][l1][l1]\\b|\\bw[e3]\\b", DECLINED_FICT_RESERVED }, -- We\Wesell
	{ "\\bw[i1][l1][l1]huff\\b|\\bw[i1][l1][l1]y\\b", DECLINED_FICT_RESERVED }, -- Willhuff\Willy
	{ "\\bw[i1]ndu\\b", DECLINED_FICT_RESERVED }, -- Windu
	{ "\\bw[i1]nt[e3]r\\b", DECLINED_FICT_RESERVED }, -- Winter
	{ "\\bwr[e3]n\\b", DECLINED_FICT_RESERVED }, -- Wren
	{ "\\bwuh[e3]r\\b", DECLINED_FICT_RESERVED }, -- Wuher
	{ "\\bx[i1][o0]n[o0]\\b", DECLINED_FICT_RESERVED }, -- Xiono
	{ "\\bx[i1]z[o0]r\\b", DECLINED_FICT_RESERVED }, -- Xizor
	{ "\\by[a@]dd[l1][e3]\\b", DECLINED_FICT_RESERVED }, -- Yaddle
	{ "\\by[a@]v[i1]d\\b", DECLINED_FICT_RESERVED }, -- Yavid
	{ "\\by[e3][a@]g[e3]r\\b", DECLINED_FICT_RESERVED }, -- Yeager
	{ "\\by[o0]d[a@]\\b", DECLINED_FICT_RESERVED }, -- Yoda
	{ "\\by[o0]mm\\b", DECLINED_FICT_RESERVED }, -- Yomm
	{ "\\by[o0]wz[a@]\\b", DECLINED_FICT_RESERVED }, -- Yowza
	{ "\\by[o0]xg[i1]t\\b", DECLINED_FICT_RESERVED }, -- Yoxgit
	{ "\\by[s5][a@]nn[a@]\\b", DECLINED_FICT_RESERVED }, -- Ysanna
	{ "\\bz[a@][a@][l1]b[a@]r\\b", DECLINED_FICT_RESERVED }, -- Zaalbar
	{ "\\bz[a@]nn[a@]h\\b", DECLINED_FICT_RESERVED }, -- Zannah
	{ "\\bz[a@]r\\b", DECLINED_FICT_RESERVED }, -- Zar
	{ "\\bz[e3][l1][l1][o0]ck\\b", DECLINED_FICT_RESERVED }, -- Zellock
	{ "\\bz[e3]nd\\b", DECLINED_FICT_RESERVED }, -- Zend
	{ "\\bzucku[s5][s5]\\b", DECLINED_FICT_RESERVED }, -- Zuckuss
	{ "\\b5[0o][1I]st\\b", DECLINED_FICT_RESERVED }, -- 501st
	{ "\\b[a]+[c]+[k]+[l]+[a]+[yYsS$]\\b", DECLINED_RESERVED }, -- acklay
	{ "\\b[k]+[i]+[i]+[n]+[']+[d]+[r]+[a]+[y]\\b", DECLINED_RESERVED }, -- kiin'dray
	{ "\\b[a]+[x]+[k]+[v]+[a]\\b", DECLINED_RESERVED }, -- axkva
	{ "\\badam.?driver\\b", DECLINED_RESERVED }, -- Adam Driver
	{ "\\b[@a]dmira[lL].*", DECLINED_RESERVED }, -- Admiral
	{ "\\bahch.?to\\b", DECLINED_RESERVED }, -- Ahch-To
	{ "\\bahto.?city\\b", DECLINED_RESERVED }, -- Ahto City
	{ "\\ball\\b", DECLINED_RESERVED }, -- all
	{ "\\ball+(a|h)+\\b", DECLINED_RESERVED }, -- Allah
	{ "\\bandy.?serkis\\b", DECLINED_RESERVED }, --\ Serkis
	{ "\\banoat.?city\\b", DECLINED_RESERVED }, -- Anoat City
	{ "\\bbank\\b", DECLINED_RESERVED }, -- bank
	{ "\\bbel.?city\\b", DECLINED_RESERVED }, -- Bel City
	{ "\\bbothan\\b", DECLINED_RESERVED }, -- bothan
	{ "\\bbuddha\\b", DECLINED_RESERVED }, -- Buddha
	{ "\\bb[i1l]d[e3]n|t[r5][uv]mp|c[l1i][il1]nt[o0]n\\b", DECLINED_RESERVED }, --Biden/Trump/Clinton
	{ "\\bcanto.?bright\\b", DECLINED_RESERVED }, -- Canto Bight
	{ "\\bc[@a]ptain.*\\b", DECLINED_RESERVED }, -- captain
	{ "\\bcarrie.?fisher\\b", DECLINED_RESERVED }, -- Carrie Fisher
	{ "\\bchancellor.*\\b", DECLINED_RESERVED }, -- Chancellor
	{ "\\bchrist.*\\b", DECLINED_RESERVED }, -- christ
	{ "\\bchristopher.?lee\\b", DECLINED_RESERVED }, -- Christopher Lee
	{ "\\bcitizens.*\\b", DECLINED_RESERVED }, -- citizens
	{ "\\bcity.*\\b", DECLINED_RESERVED }, -- City
	{ "\\bcloud.?city\\b", DECLINED_RESERVED }, -- Cloud City
	{ "\\bcommander.*\\b", DECLINED_RESERVED }, -- Commander
	{ "\\bcorellia.*\\b", DECLINED_RESERVED }, -- Corellia
	{ "\\bc[o0]r[s5][e3]c\\b", DECLINED_RESERVED }, --Corsec
	{ "\\bdac.?city\\b", DECLINED_RESERVED }, -- Dac City
	{ "\\bdagobah.*\\b", DECLINED_RESERVED }, -- Dagobah
	{ "\\bdaisey.?riddley\\b", DECLINED_RESERVED }, -- Daisey Riddley
	{ "\\bdantooine.*\\b", DECLINED_RESERVED }, -- Dantooine
	{ "\\b^d[AaEe]rklord.*$\\b", DECLINED_RESERVED }, -- DARKLORD
	{ "\\bdathomir.*\\b", DECLINED_RESERVED }, -- Dathomir
	{ "\\bdevil.*\\b", DECLINED_RESERVED }, -- Devil
	{ "\\bdoctor.*\\b", DECLINED_RESERVED }, -- doctor
	{ "\\bdump\\b", DECLINED_RESERVED }, -- dump
	{ "\\b[ei]mp[oea]r[oea]r\\b", DECLINED_RESERVED }, -- Emperor
	{ "\\bendor.*\\b", DECLINED_RESERVED }, -- Endor
	{ "\\bewan.?mcgregor\\b", DECLINED_RESERVED }, -- Ewan McGregor
	{ "\\bfire?spider.*\\b", DECLINED_RESERVED }, -- firespider
	{ "\\bgalactic.?city\\b", DECLINED_RESERVED }, -- Galactic City
	{ "\\bgeneral.*\\b", DECLINED_RESERVED }, -- General
	{ "\\bgeorge.?lucas\\b", DECLINED_RESERVED }, -- George Lucas
	{ "\\b^g[o0]d$\\b", DECLINED_RESERVED }, -- God
	{ "\\bgroup.*\\b", DECLINED_RESERVED }, -- group
	{ "\\bguild.*\\b", DECLINED_RESERVED }, -- guild
	{ "\\bgunga.?city\\b", DECLINED_RESERVED }, -- Gunga City
	{ "\\bgwendoline.?christie\\b", DECLINED_RESERVED }, -- Gwendoline Christie
	{ "\\bharrison.?ford\\b", DECLINED_RESERVED }, -- Harrison Ford
	{ "\\bhayden.?christiansen\\b", DECLINED_RESERVED }, -- Hayden Christiansen
	{ "\\bhosnian.*\\b", DECLINED_RESERVED }, -- Hosnian
	{ "\\bhoth.*\\b", DECLINED_RESERVED }, -- Hoth
	{ "\\bhuman.*\\b", DECLINED_RESERVED }, -- human
	{ "\\bithorian.*\\b", DECLINED_RESERVED }, -- Ithorian
	{ "\\biziz.*\\b", DECLINED_RESERVED }, -- Iziz
	{ "\\bjakku.*\\b", DECLINED_RESERVED }, -- Jakku
	{ "\\bjames.?earl.?jones\\b", DECLINED_RESERVED }, -- James Earl Jones
	{ "\\bj[e3]dh[a@]\\b", DECLINED_RESERVED }, -- Jedha
	{ "\\b^j[ie]*di.*\\b", DECLINED_RESERVED }, -- jedi\Jeedi
	{ "\\bjehov[ah].*\\b", DECLINED_RESERVED }, -- Jehova\Jehovah
	{ "\\bjes[ui]s.*\\b", DECLINED_RESERVED }, -- jesus
	{ "\\bje[w|s]+.*\\b", DECLINED_RESERVED }, -- Jew
	{ "\\bkaas.?city\\b", DECLINED_RESERVED }, -- Kaas City
	{ "\\bkryat\\b", DECLINED_RESERVED }, -- kryat
	{ "\\blaura.?dern\\b", DECLINED_RESERVED }, -- Laura Dern
	{ "\\bliam.?neeson\\b", DECLINED_RESERVED }, -- Liam Neeson
	{ "\\blieutenant.*\\b", DECLINED_RESERVED }, -- lieutenant
	{ "\\blok.*\\b", DECLINED_RESERVED }, -- Lok
	{ "\\b^lord*.\\b", DECLINED_RESERVED }, -- Lord
	{ "\\b^major*.\\b", DECLINED_RESERVED }, -- Major
	{ "\\bmark.?hammel\\b", DECLINED_RESERVED }, -- Mark Hammel
	{ "\\bmarshal.*\\b", DECLINED_RESERVED }, -- Marshal
	{ "\\b(m[&e3]|me)\\b", DECLINED_RESERVED }, -- me
	{ "\\bm[e3]d[i1]c\\b", DECLINED_RESERVED }, -- medic
	{ "\\bmoff*.\\b", DECLINED_RESERVED }, -- Moff
	{ "\\bcala.?city\\b", DECLINED_RESERVED }, -- Mon Cala City
	{ "\\bmoncalamari*.\\b", DECLINED_RESERVED }, -- moncalamari
	{ "\\bm[uv][s$5][i1l][i1l]m[s5$]?\\b", DECLINED_RESERVED}, --Muslim\Muslims"}
	{ "\\bmustafar*.\\b", DECLINED_RESERVED }, -- Mustafar
	{ "\\bnaboo*.\\b", DECLINED_RESERVED }, -- Naboo
	{ "\\bnatalie.?portman\\b", DECLINED_RESERVED }, -- Natalie Portman
	{ "\\bniima*.\\b", DECLINED_RESERVED }, -- Niima
	{ "\\bofficer*.\\b", DECLINED_RESERVED }, -- Officer
	{ "\\boscar.?isaac\\b", DECLINED_RESERVED }, -- Oscar Isaac
	{ "\\botoh.?gunga\\b", DECLINED_RESERVED }, -- Otoh Gunga
	{ "\\bpau.?city\\b", DECLINED_RESERVED }, -- Pau City
	{ "\\bpeter.?mayhew\\b", DECLINED_RESERVED }, -- Peter Mayhew
	{ "\\bprivate*.\\b", DECLINED_RESERVED }, -- Private
	{ "\\brodian*.\\b", DECLINED_RESERVED }, -- Rodian
	{ "\\brori*.\\b", DECLINED_RESERVED }, -- Rori
	{ "\\bsamuel.?jackson\\b", DECLINED_RESERVED }, -- Samuel Jackson
	{ "\\b[s5][a@]t[a@]n.*\\b", DECLINED_RESERVED }, -- Satan
	{ "\\bscariff*.\\b", DECLINED_RESERVED }, -- Scariff
	{ "\\bself*.\\b", DECLINED_RESERVED }, -- self
	{ "\\bsullistan.*\\b", DECLINED_RESERVED }, -- Sullistan
	{ "\\b^swg+[e/a][m/n][u/h]*\\b", DECLINED_RESERVED }, -- swganh\SWGEmu
	{ "sys*.", DECLINED_RESERVED }, -- sys\System
	{ "\\btakodana.*\\b", DECLINED_RESERVED }, -- Takodana
	{ "talus.*", DECLINED_RESERVED }, -- Talus
	{ "tatooine.*", DECLINED_RESERVED }, -- Tatooine
	{ "^th[i1]s.*", DECLINED_RESERVED }, -- this
	{ "^ti[p|s5]+$", DECLINED_RESERVED }, -- tip
	{ "tipoca.?city", DECLINED_RESERVED }, -- Tipoca City
	{ "trandoshan.*", DECLINED_RESERVED }, -- Trandoshan
	{ "tuanul.*", DECLINED_RESERVED }, -- Tuanul
	{ "twi'lek.*", DECLINED_RESERVED }, -- twi'lek
	{ "warrant.*", DECLINED_RESERVED }, -- Warrant Officers
	{ "whill[sS/zZ]*", DECLINED_RESERVED }, -- Whills
	{ "wookie,*", DECLINED_RESERVED }, -- Wookie
	{ "yah[vVwW]eh.*", DECLINED_RESERVED }, -- Yahveh\Yahweh
	{ "zabrak.*", DECLINED_RESERVED }, -- Zabrak
	{ "zeran.?town", DECLINED_RESERVED }, -- Zeran Town
	{ "\\b[i!1l\\|]+\\b", DECLINED_RESERVED }, -- ilil
	{ "\\b[d†][e3][v†](eloper)?\\b", DECLINED_DEVELOPER }, -- DEV
	{ "\\b(gm|g[a@]m[e3]m[a@][s5]t[e3]r)\\b", DECLINED_DEVELOPER }, -- GM
	{ "\\bc[s5]r\\b", DECLINED_DEVELOPER }, -- CSR
	{ "\\bq[a@][i1]?\\b", DECLINED_DEVELOPER }, -- QA
	{ "\\b[e3]c[i1]?\\b", DECLINED_DEVELOPER }, -- EC\ECI
	{ "\\bct\\b", DECLINED_DEVELOPER }, -- CT
	{ "\\bmo(d(erator)?)?\\b", DECLINED_DEVELOPER }, -- MOD
	{ "\\b[s5$]t[a@]ff\\b", DECLINED_DEVELOPER}, --STAFF
	{ "\\b2girl[s5]1cup\\b|\\b2g1c\\b|\\b[a@]2m\\b", DECLINED_PROFANE }, -- 2 girls 1 cup\2g1c\a2m
	{ "\\b(?:a[c@]r[o0]t[o0]m[o0]phili[a@]|n[e3]cr[o0]phili[a@])\\b", DECLINED_PROFANE }, --acrotomophilia\necrophilia
	{ "\\b(?:[a@]id[s5](?!h[e3][a@]r[il1]ng)\\w*)\\b", DECLINED_PROFANE }, -- aids
	{ "\\ba[i1!]rb[l1][@a][s5]t", DECLINED_PROFANE }, -- Air blast
	{ "\\b(?:[a@]l[a@]b[a@]m[a@]\\s?|\\ba[l1i!]+)\\s?(?:h[o0]t\\s?p[o0]cke?t|hcp)\\b", DECLINED_PROFANE }, -- alabama hot pocket
	{ "\\b(?:[a@]l[a@][s5]k[a@][nm]\\s?p(?:[il1!]+p)?(?:l|1)?i?n[e3]|[a@]l[a@][s5]k[a@]np[i1l]p[e3][i1l]in[e3])\\b", DECLINED_PROFANE }, -- alaskan pipeline
	{ "\\b(?:a[n4][a@]+l(?:[il1]mp[a@][11l][e3]r|l[e3][a@]k[a@]g[e3])?)\\b", DECLINED_PROFANE }, -- anal/analleakage/analimpaler
	{ "\\b(?:a|@)nil(?:in|ing|1n)us\\b", DECLINED_PROFANE }, -- anilingus
	{ "\\b[a@]nu[s\\$]\\b", DECLINED_PROFANE }, -- anus
	{ "\\b(a|@)[p3][e3][s\\$][h4][i1!]t\\b", DECLINED_PROFANE }, -- apeshit
	{ "\\b[a@]r[s\\$z][e3][ho0][o0][l1][e3]\\b", DECLINED_PROFANE }, -- arsehole
	{ "\\b([a@][s5\\$]{2}|ass(?:munch|hole)?)|[a@][_-][s5$][_-][s5$]|[a@]r[s5$][e3]|(?:dumb)?[a@][s5][s5]\\b", DECLINED_PROFANE }, -- Ass/Assmunch/Asshole/a_s_s/arse
	{ "\\b[a@4]u[t7][o0][\\s-]*[e3]r[o0][t7][i1][ck]\\b", DECLINED_PROFANE }, -- auto erotic
	{ "\\b(?:a[us]+w[i1!]+tz+ch|a[us]+chwi[ts]+z)\\b", DECLINED_PROFANE }, -- auschwitz
	{ "\\b[b6][a@4][b6][y7][b6][a@4][t7][t7][e3][rR]\\b|\\b[b6][a@4][b6][y7][jg9][uU][i1][cC][e3]\\b", DECLINED_PROFANE }, -- baby batter/baby juice
	{ "\\b(b|8)[a@][b]+[e3]+[l1!][a@][nñ][d]+\\b", DECLINED_PROFANE }, -- babeland
	{ "\\bball(?:[gb][a@]g|gr[a@]vy|[lk][il1]ck[il1]ng|[s5$][a@]ck|[s$5]uck[il1]ng)\\b", DECLINED_PROFANE }, -- ball gag\ball bag\ball gravy\ball kicking\ball licking\ball sack\ball sucking
	{ "\\bb[a@]ngbr[o0]|b[a@]ngbu[s5]\\b", DECLINED_PROFANE }, -- bangbros\bangbus
	{ "\\b(?:b[a@]r[e3][bl][a@]ck|b[a@]r[3e]lyl[e3]g[a@]l|b[a@]r[e3][nm][a@]k[e3]d)\\b", DECLINED_PROFANE }, -- bareback\barely legal\barenaked
	{ "\\b[b4][a@][s5]t[a@]rd[ao0]?\\b|\\b[b4][a@][s5]t[i1]n[a@]d[o0]\\b", DECLINED_PROFANE }, -- bastard\bastardo\bastinado
	{ "\\bbd[s5]m|b+b+w\\b", DECLINED_PROFANE }, -- bbw\bdsm
	{ "\\b[b6][e3][a@][n4][e3]r[s\\$]?\\b", DECLINED_PROFANE }, -- beaner\beaners
	{ "\\b(?:b[e3@]sti[ai@]lity|b[e3@]asti[ai@]lity|b[e3@]asti[ai@]l|b[e3@]sti[ai@]l)\\b", DECLINED_PROFANE }, --bestiality\beastiality\beastial\bestial
	{ "b[e3]+[a@][v]+[e3]+[r]+[c]+l+[e3]+[a@]+v+[e3]+r|b[e3]+[a@][v]+[e3]+[r]+[l]+[i1!]+[p]+[s$]", DECLINED_PROFANE }, -- beaver cleaver\beaver lips
	{ "\\b(?:benzos|B[e3]+nz[o0]+s)\\b", DECLINED_PROFANE }, -- Benzos
	{ "\\b[b4][i1!][g9][kK][nN][o0][cCkK][kK3][e3][rR][s5]\\b|\\bb[l1!][g9] [kK][nN][o0][cCkK][kK3][e3][rR][s5]\\b", DECLINED_PROFANE }, -- big knockers
	{ "\\bb[i1lLmM]+b[o0s\\$]{2,}\\b", DECLINED_PROFANE }, -- bimbos
	{ "\\bb[i1lLrR]{2,}d[l1o0cCkK]+\\b", DECLINED_PROFANE }, -- birdlock
	{ "\\b(?:b[i1!]+tch(?:es|ing|ed)?|l3[i1!]+tch|sonofab[i1!]+tch|13[i1!]+\\+ch|b17ch|bi\\+ch|biatch)\\b", DECLINED_PROFANE }, -- bitch
	{ "\\bb[l1!][o0]n[d3][e3]?[ ]*a[ck]t[iI][o0]n\\b", DECLINED_PROFANE }, -- blonde action
	{ "\\bbl[o0@e3]?w(?:j[o0@e3]?bs?|y[o0@e3]?ur(?:l[o0@e3]?ad)?|m[eu]d?)\\b", DECLINED_PROFANE }, -- blowme\blowmud\blow job\blow your load
	{ "\\b[b4][l1!][u4v][e3][a@4][nmu]g[e3][l1!][s5]\\b|\\bb[l1!][u4v][e3] [a@4][nmu]g[e3][l1!][s5]\\b", DECLINED_PROFANE }, -- Blue angels
	{ "\\b(?:blue\\s?w[a@]ffl[e3]|[b8][l1]ue\\s?[wv][a@]ffl[e3])\\b", DECLINED_PROFANE }, -- blue waffle
	{ "\\b[b6][l1i!][u4v][m][p][k][i1!][n]\\b", DECLINED_PROFANE }, -- blumpkin
	{ "\\b[bv]+[o0]+m[bv]+(?:ing|ed)?(?:e[re3]+r)?\\b", DECLINED_PROFANE }, --bomb/bombed/bomber/bombing
	{ "\\bb[o0]nd[a@]g[e3]\\b", DECLINED_PROFANE }, -- bondage
	{ "\\b(?:bo[n3]er|ra[g9]ingbo[n3]er)\\b", DECLINED_PROFANE }, -- boner\ragingboner
	{ "\\b(?:boob|boobs|booty|b[o0]+b|b[o0]+bs|b[o0]+ty)\\b", DECLINED_PROFANE }, -- boob\boobs\booty
	{ "\\b[bv][r8][e3a@][a@4]s?ts?\\b|\\bb[r8]ownsh[o0]wers\\b|\\bbr[uo0]nette[a@]ct[i1]on\\b", DECLINED_PROFANE }, -- breast\brown showers\brunette action
	{ "\\bb[uûv]kk[a@]k[e3]\\b", DECLINED_PROFANE }, -- bukkake
	{ "\\bb[uûv][il1][il1]dyk[e3]\\b", DECLINED_PROFANE }, -- bulldyke
	{ "\\b(?:b[uü]llet\\s*(?:v[iï1!]\\s*b[o0]lt)?|bullet)\\b", DECLINED_PROFANE }, --bulletbolt\bulletvibe
	{ "\\b(?:bullet bolt|bu[l1i!]+[e3]+t+bo[l1i!]+t+)\\b", DECLINED_PROFANE }, -- Bullet bolt
	{ "\\bb[uûv][il1][il1][e3]tv[il1]b[e3]\\b", DECLINED_PROFANE }, -- bullet vibe
	{ "\\b(b[uU]+[l1I!]+[s\\$]+h[i1!*]+t+)\\b", DECLINED_PROFANE }, -- bullshit
	{ "\\b(b[uU]+[nN]+[gG6]+[hHoO0]+l[eE3]+)\\b", DECLINED_PROFANE }, -- bung hole
	{ "\\b(b[uU]+[sS$]+[tT7]+[yYi1]+)\\b", DECLINED_PROFANE }, -- busty
	{ "\\b(?:b[uo@v0]+t+(?:tcheeks?|thole|tmuch|tplug)?)\\b", DECLINED_PROFANE }, -- butt\buttcheeks\butthole\buttmuch\buttplug
	{ "\\bc[a@]m[e3][il1][t7][o0][e3]\\b", DECLINED_PROFANE }, -- camel toe
	{ "\\b(?:cam[g6&]+irl|camsl[u*]t|camwh[o0@4]+re?)\\b", DECLINED_PROFANE }, -- camgirl\camslut\camwhore
	{ "\\b(c|k|ck|q)[a@]n(c|k|ck|q)[e3]r\\b", DECLINED_PROFANE }, --cancer
	{ "\\b(c|k|ck|q)[a@][rR][pP][e3][tT]\\s?(m|rn|rnch3r)\\b", DECLINED_PROFANE }, -- carpet muncher\carpetmuncher
	{ "\\bch[o0](?:|[a@]d[e3]|t[a@]b[a@]g[s$5])\\b", DECLINED_PROFANE }, --chode\chotabags
	{ "\\b[c]+[h4]+[o0]+[c]+[o0]+[l]+[a@4]+[t]+[e3]+[r]+[o0]+[s5]+[e3]+[b8]+[u]+[d]+[s5]+\\b", DECLINED_PROFANE }, -- chocolate rosebuds
	{ "\\bc[il1y][a@][l1][il1][s5]\\b", DECLINED_PROFANE }, -- cialis\cyalis
	{ "\\bc[il1]rc[l1][e3]j[e3]rk\\b", DECLINED_PROFANE }, -- circlejerk
	{ "\\bc[li1][e3]v[e3][l1i][a@]nd[s5]t[e3][a@]m[e3]r\\b", DECLINED_PROFANE }, -- cleveland steamer
	{ "\\b(?:.*c[l1][i1][t\\+].*|b[uü]ceta|fl[a@]ng[e3]|l[a@]b[il1][a@])\\b", DECLINED_PROFANE }, -- clit\buceta\flange\labia
	{ "\\bc[l1i][o0]v[e3]rc[l1i][a@]mp[s5]\\b", DECLINED_PROFANE }, -- clover clamps
	{ "\\b^(|Kk|c|C)ocaine$\\b", DECLINED_PROFANE }, -- cocaine
	{ "\\b.*[cckk]+[o0a@]+[cwkk]*.*|[s5]m[e3]gm[a@]\\b", DECLINED_PROFANE }, -- cocks\smegma
	{ "\\b.*[ck][ou0]nd[ou0]m[s\\$]?*.*\\b", DECLINED_PROFANE }, -- condom
	{ "\\b(c|k|ck|q)[o0](c|k|ck|q)[s\\$]?\\b", DECLINED_PROFANE }, -- coon\coons
	{ "\\b[c]+[o0]+[p]+[r]+[o0]+[l]+[a@4]+[g9]+[n]+[i1]+[a@4]+\\b|\\b[c]+[o0]+[p]+[r]+[o0]+[p]+[h]+[i1]+[l]+[i1]+[a@4]+\\b", DECLINED_PROFANE }, -- coprolagnia\coprophilia
	{ "\\b(c|k|ck|q)[o0]rn[h@4][o0]l[e3]\\w*\\b", DECLINED_PROFANE }, -- cornhole
	{ "\\b(c|k|ck|q)[r3][e3@4][a@4]m[ppl1][i1!l1][e3]\\w*\\b", DECLINED_PROFANE }, -- creampie
	{ "\\b[ck]+[u]+[m]+[a-z]*.*\\b", DECLINED_PROFANE }, -- cum\et all
	{ "\\b(?:c[uvuo0]+n{1,2}[i1!]+l[li1!]+ng[uo0]*s?|k[uo0]+n[i1!]+l[li1!]+ng[uo0]*s?)\\b", DECLINED_PROFANE }, -- cunilingus\cunillingus\cunnilingus
	{ "\\b.*[ckq](?:un[t+][s$]?|nut).*\\b", DECLINED_PROFANE }, -- cunt\cnut\et all
	{ "\\b[c][y][b][e3]r(ph|f)u(c|k|ck|q)\\b", DECLINED_PROFANE }, -- cyberfuck
	{ "\\b.*[d][a@][m][n]*.*\\b", DECLINED_PROFANE }, -- damn
	{ "\\b[dD][aA@][rR][kK]\\w*\\b", DECLINED_PROFANE }, -- darkie
	{ "\\b[d]+[e3]+[e3]+[p]+[t7]+[h]+[r]+[o0]+[a@4]+[t7]+\\b", DECLINED_PROFANE }, -- deep throat
	{ "\\b(d|de)[e3][n|rn][d|t][r|hr][o0][p|ph][h|l|i1a@]*[l1i1a@]*[i1l1a@]*\\b", DECLINED_PROFANE }, -- dendrophilia
	{ "\\b.*[d][i1l][c][k]*.*\\b", DECLINED_PROFANE }, -- dick
	{ "\\b(?:d[i1!]+l[d1!]+[o0]+s?)\\b", DECLINED_PROFANE }, -- dildo
	{ "\\bdingl(?:e|3)+berr(?:y|i1)?(?:ies)?\\b", DECLINED_PROFANE }, -- dingleberries\dingleberry
	{ "\\bd(?:[i1l]nk(?:[s5$])?|[uv]nk|[il1]r[s5$][a@])\\b", DECLINED_PROFANE }, -- dink/dunk/dirsa
	{ "\\bd[i1l]+rt[yi1l]*s[a4]+nch[e3z]+\\b|\\bd[i1]+rt[yi1l]*p[i1l]+llows\\b", DECLINED_PROFANE }, -- dirty pillows\dirty sanchez
	{ "\\b(?:dog(?:style|giestyle|gin|ging|gystyle))(?!\\S)", DECLINED_PROFANE }, -- dog style
	{ "\\b[d]+[o0]+[li1]+[c]+[e3]+[t7]+\\b", DECLINED_PROFANE }, -- dolcett
	{ "\\bdom(?:ination\\b|inatrix\\b|mes\\b)", DECLINED_PROFANE }, -- domination\dominatrix\dommes
	{ "\\b(d|d0|d[0o]|d[0o][n|i1l1][k|c][e3]?y?)[p|b][u|v]?[n|\\w]+\\b", DECLINED_PROFANE }, -- donkey punch
	{ "\\b(?:dou?b(?:ledong|ldong|lepenetration))|dp[a@]ct[il1][o0]n\\b", DECLINED_PROFANE }, -- double dong\double penetration
	{ "\\b(?:d[pb][a@4]+[cck]+[i1!l1]+o[o0]+n|[phd]+[pb][a@4]+[cck]+[i1!l1]+o[o0]+n)\\b", DECLINED_PROFANE }, -- dp action
	{ "\\b[d]+[r]+[y]+[h]+[u]+[m]+[p]+\\b", DECLINED_PROFANE }, -- dry hump
	{ "\\b(?:duch[e3]s?|d[o0][o0]sh|b[o0]ll[o0]c?ks?|b[e3]ll[e3]nd|b[uv][g6][g6][e3]r|[s5][a@]ndb[a@]r)\\b", DECLINED_PROFANE }, --duche\doosh\bollock\bellend\bugger\sandbar
	{ "\\bd[u]n(c|k|ck|q)[s\\$]\\b", DECLINED_PROFANE }, -- dunks
	{ "\\b[d]+[v]+[d]+[a]+\\b", DECLINED_PROFANE }, -- dvda
	{ "\\b[dD][yYiI1][kK3eE]+\\b", DECLINED_PROFANE }, -- dyke
	{ "\\b[e3]+[a@]+[t+]\\w*[m]+[y]+[a@]+[s\\$]+[s\\$]+\\b", DECLINED_PROFANE }, -- eat my ass
	{ "\\b[e3]+[c]+[h]+[i1l!]+\\b", DECLINED_PROFANE }, -- ecchi
	{ "[e3]j[a@]c*", DECLINED_PROFANE }, -- ejactulate
	{ "\\b(?:[e3]+r[o0]+t[i1lL]+c|[e3]+r[o0]+t[i1lL]+sm)\\b", DECLINED_PROFANE }, -- erotic\erotism
	{ "\\b[e3]+[s5]+[s5]+[e3]+[r]\\b", DECLINED_PROFANE }, -- esser
	{ "\\b[e3]+[u]+[n]+[u]+[c]+[h]+\\b", DECLINED_PROFANE }, -- eunuch
	{ "\\b(?:[il1][s5$][il1][s5$]|[qk][a@]n[o0]n)\\b", DECLINED_PROFANE }, --extremist groups
	{ "\\b(?:f[uü]r(?:f|ph)[a@]g|f(?:[a@]|@)g(?:ging|got|gs?)?|f(?:a|@)g(?:[o0]ts?|s)?|f[a@]ggitt)\\b", DECLINED_PROFANE }, -- furfag/fag/fagging/faggitt/faggot/faggs/fagot/fagots/fags
	{ "\\b(?:f(?:[a@4]nny|anyy|annyflaps?))\\b", DECLINED_PROFANE }, --fanny\f4nny\fannyflaps\fanyy
	{ "\\b(?:f[ae]c[ae]l|f[ae]ci[ae]l)\\b", DECLINED_PROFANE }, -- fecal
	{ "\\bf[e3]+l[cg]+h\\b", DECLINED_PROFANE }, -- felch
	{ "\\b(ph|f)[e3][l1][l1]?[a@][t\\+][i1][o0]\\b", DECLINED_PROFANE }, -- fellatio
	{ "\\bf[e3]+m[a@]+l[e3]+s[qk]+u[i1]+r[t\\+]+i[n9]+g\\b", DECLINED_PROFANE }, -- female squirting
	{ "\\bf[e3]+md[o0m]+\\b", DECLINED_PROFANE }, -- femdom
	{ "\\bf[i1l!]+g[g9i1l!]+ng\\b", DECLINED_PROFANE }, -- figging
	{ "\\b[f]+[i1l]+n[g]+[e3]+r[b]+a[n]+g\\b|\\bf[i1l]+n[g]+[e3]+r[i1l]+n[g]+\\b", DECLINED_PROFANE }, -- fingerbang\fingering
	{ "\\bf[i1l!]+[s$]+t[i1l!]+n[gq]+\\b", DECLINED_PROFANE }, -- fisting
	{ "\\bf[0o]ot[jb]ob|f[0o]otf[3e]t[i1l!]+[s$][h=]+\\b", DECLINED_PROFANE }, -- foot fetish\footjob
	{ "\\bf[r]+[o0]+[t]+[t][i1l!]+[n]+g\\b", DECLINED_PROFANE }, -- frotting
	{ "\\b(?:f[u*]c[kc](?:s|ing|tard)?|f[_-]u[_-]c[_-]k|[s5]cr[e3]w[il1]ng|fc[u*]k(?:er|ing)?|fe[c*]k(?:er)?|fo[o*]k(?:er)?|fux(?:0r)?)\\b", DECLINED_PROFANE }, -- fuck\fucking\fuxor\screwing
	{ "(phc|f)u(c|k|ck|q)[s\\$]?", DECLINED_PROFANE }, -- fucks\fucktards
	{ "\\b(f|ph)[u\\W]*dge[p\\W]*acker\\b", DECLINED_PROFANE }, -- fudgepacker
	{ "\\b(f|ph)[u\\W]*t[ua]n[aei][r\\W]*i\\b", DECLINED_PROFANE }, -- futanari
	{ "\\b[g]+[s$5]+p[o0]+t\\b|\\bg[-]?[s$5]+p[o0]+t\\b", DECLINED_PROFANE }, -- g-spot
	{ "\\b(?:g[a@]ngb(?:[a@4]ng|[a@]ng(?:[e3]d|s)?)|g[a@]ng-b[a@]ng)\\b", DECLINED_PROFANE }, -- gangbang\gangbanged\gang-bang
	{ "\\b(?:g[a@]y(?:l[o0]rd|s[e3]x)?|b[o0][i1!l][o0][i1l][a@][s5])\\b", DECLINED_PROFANE }, -- gay\gaylord\gaysex\boiolas
	{ "\\b[g9][e3][n]+[i1l!][t\\+]a[l1!][s\\$]?\\b", DECLINED_PROFANE }, -- genitals
	{ "\\b[g9][i1l!][r]+[l1!][o0][n]+[t\\+][o0p]+\\b", DECLINED_PROFANE }, -- girl on top
	{ "\\b[g9][i1l!][r]+[l1!][s\\$][g9][o0][n]+[e3][wv]+[i1l!][l1!][d\\$]+\\b", DECLINED_PROFANE }, -- girls gone wild
	{ "\\b[g9][o0][a@][t\\+][c][x]+|[g9][o0][a@][t\\+][s\\$][e3]\\b", DECLINED_PROFANE }, -- goatcx\goatse
	{ "\\b[g9][o0][d][d]+[a@][m]+n+\\b", DECLINED_PROFANE }, -- god damn
	{ "\\b[g9][o0][k]+u[n]+\\b", DECLINED_PROFANE }, -- gokkun
	{ "\\b[g9][o0][l1i!][d\\$][e3][n]+[s\\$h]+[o0][wv]+[e3][r]+\\b", DECLINED_PROFANE }, -- golden shower
	{ "\\b[g9][o0]+[g9]+[i1!l1]+[r]+[l1i!]+\\b", DECLINED_PROFANE }, -- googirl
	{ "\\b[g9][o0]+[o0]+[d]+[p]+[o0]+[o0]+[p]+\\b", DECLINED_PROFANE }, -- goodpoop
	{ "\\b[Gg][o0][o0]+[fph]+[e3][r]+[sz$]*|[Gg][uU]+[fph]+[e3][r]+[sz$]*\\b", DECLINED_PROFANE }, -- Goofers
	{ "\\b[g9][o0][r][e3]|g[o0]r[e3][g9][a@][s\\$][m]\\b", DECLINED_PROFANE }, -- goregasm
	{ "\\b[g][r][o0][il1][n]\\b", DECLINED_PROFANE }, -- groin
	{ "\\b[g9][r]+[o0]+[p]+[e3]+\\b", DECLINED_PROFANE }, -- grope
	{ "\\b(g|9)[u\\|]+r[o0]\\b", DECLINED_PROFANE }, -- guro
	{ "\\bh[a@]nd[jy1]ob\\b", DECLINED_PROFANE }, -- handjob
	{ "\\bh[a@]rd[cckq][o0][r]+[e3]*\\b", DECLINED_PROFANE }, -- hardcore
	{ "\\bh[e3][l1i][l1i][s5]?\\b", DECLINED_PROFANE}, --hell
	{ "\\bh[e3]+nt[a@i1]+\\b", DECLINED_PROFANE }, -- hentai
	{ "\\bh[e3][rR][o0][i1][nN]\\b", DECLINED_PROFANE }, -- heroin
	{ "\\bh[i1][t\\+]l[e3][rR]\\b", DECLINED_PROFANE }, -- hitler
	{ "h[o0]m?m[o0]", DECLINED_PROFANE }, -- homo
	{ "\\bh[o0]nk[e3]y\\b", DECLINED_PROFANE }, -- honkey
	{ "\\bh[o0]+[o0]k[e3]r\\b", DECLINED_PROFANE }, -- hooker
	{ "\\bh[o0@]*rn[yil1](?:est)?\\b", DECLINED_PROFANE }, -- horny\horniest
	{ "\\b(hot[c@]h[i1]c[kcq]|hotcarl)\\b", DECLINED_PROFANE }, -- hot carl\hot chick
	{ "\\bh[o0]t[ ]*p[o0]cke?t\\b", DECLINED_PROFANE }, -- hot pocket
	{ "\\b(?:h[o0@]wt[o0@]k[il1][li1][li1]|h[o0@]wt[o0@]murd[e3][rp]|[il1]wantt[o0]d[il1][e3])\\b", DECLINED_PROFANE }, --Iwanttodie\how to kill\how to murder\how to murderp
	{ "\\b[h][u][f]+\\b", DECLINED_PROFANE }, -- Huff
	{ "\\b(h[uû]gef[a@]t)\\b", DECLINED_PROFANE }, -- huge fat
	{ "\\b(h[uû]mp[i1!l1]ng)\\b", DECLINED_PROFANE }, -- humping
	{ "\\b(i[n1!l1]c[e3]st)\\b", DECLINED_PROFANE }, -- incest
	{ "\\b(i[n1!l1]t[e3]rc[o0u]urs[e3])\\b", DECLINED_PROFANE }, -- intercourse
	{ "\\b[il1][s5$]lam[o0]ph[o0]b[e3]|lgbtq?|r[a@]c[il1][s5]t\\b", DECLINED_PROFANE}, --islamphobe\lbgtq\racist
	{ "\\bj[a@](c|k|ck|q)\\-?[o0](ph|f)(ph|f)?\\b", DECLINED_PROFANE }, -- jackoff
	{ "\\b(j[a@]i[l1!][b@]+a[i1]t)\\b", DECLINED_PROFANE }, -- jail bait
	{ "\\b(j[e3]+l[l1!][yie3]+d[o0]nu[t+])\\b", DECLINED_PROFANE }, -- jelly donut
	{ "\\b(?:j[eu]rk(?:off)?|l[mo]a[o]+|l[mf]fa[o]+|pr[i1!]+cks|wtf)\\b", DECLINED_PROFANE }, --jerk/jerkoff/lmao/lmfao
	{ "\\b[j]+(?:i|1)[g]+(?:gaboo|ga[b6o0]+|ge[b6o0]+|ger[b6o0]+oo|ga[b6o0]+boo)\\b|\\bjigaboo\\b", DECLINED_PROFANE }, -- jigaboo\jiggaboo\jiggerboo
	{ "\\bj[i1][s\\$z][s\\$z]?m?\\b", DECLINED_PROFANE }, -- jizz
	{ "\\bju[g6][g6][s5\\$]\\b", DECLINED_PROFANE }, -- juggs
	{ "\\bk[e3][e3][p][y][o0]urs[e3][l1]f[s5][a4][f[e3]\\b", DECLINED_PROFANE }, -- keepyourselfsafe
	{ "\\bk[i1]k[e3]?\\b", DECLINED_PROFANE }, -- kike
	{ "\\b(k|k1|ki|k1l|kil|k[i1]ll|k1lly|killy|k1ll_y0u|kill_you|r_yourself)|kys\\b", DECLINED_PROFANE }, -- killyourself
	{ "\\b(k[i1]nb[a@]ku)\\b", DECLINED_PROFANE }, -- kinbaku
	{ "\\b[k]+[i1l]+n[k]+(?:y|[s5]t[ae3o0r]+)?\\b", DECLINED_PROFANE }, -- kinkster\kinky
	{ "\\b(?:kn[o0]b(?:[e3](?:d|nd|ad|[il1]ng)?)?|kn[o0]b(?:head|b[i1l]ng)?|kn[o0]bj(?:o(?:cky|k[e3]y)?)?)\\b", DECLINED_PROFANE }, -- knob\knobbing\knobend\knobead\knobjocky\knobjokey
	{ "\\b(?:l[e3][a@]th[e3]rr[e3][s5]tr[a@][il1]nt|l[e3][a@]th[e3]r[s5]tr[a@][il1]ghtj[a@]ck[e3]t)\\b", DECLINED_PROFANE }, -- leather restraint\leather straight jacket
	{ "\\b(l[e3]m[o0]np[a@i1]rty)\\b", DECLINED_PROFANE }, -- lemon party
	{ "\\b(?:l[o0]li(?:t?a|con)?)\\b", DECLINED_PROFANE }, --loli/lolita/lolicon
	{ "\\b(l[o0]v[e3]m[a@]k[i1]n[gq])\\b", DECLINED_PROFANE }, -- lovemaking
	{ "\\b(?:[l1i][o0u][s5]t|[1li][o0u][s5]t[il1]ng)\\b", DECLINED_PROFANE }, --lust/lusting
	{ "\\bl[s$z][d]+\\b", DECLINED_PROFANE }, -- lsd
	{ "\\b[m]+[a4]+k[e3]+m[e3]+c[o0]+m[e3]+\\b", DECLINED_PROFANE }, -- make me come
	{ "\\b[m]+[a4]+l[e3]+s[q9]+u[i1l]+r[t7]+i[n]+g\\b|\\bmalesquirting\\b", DECLINED_PROFANE }, -- male squirting
	{ "\\b(?:[ma@]+[g6a@]+|[m]+[a@]+[k]+[e3]+[a@]+[m3]+[e3]+[r]+[i1]+[c]+[a@]+[g6]+[r]+[e3]+[a@]+[t7]+[a@]+[g6]+[a@]+[i1]+[n]+|[a@]+[m3]+[e3]+[r]+[i1]+[c]+[a@]+[f]+[i1]+[r]+[s$]+[t7]+)\\b", DECLINED_PROFANE}, --maga\makeamericagreatagain\americafirst
	{ "\\bm[a@4][o0]+\\b", DECLINED_PROFANE }, -- mao
	{ "\\bm[a@]f[uv]gly\\b", DECLINED_PROFANE }, --mafugly
	{ "\\b(?:mast[ue]rb(?:at(?:e|[8*]|3|ing|ion(?:s)?)?)?|mast[ue]rbate?|master[ -]?bate?|m[ae4][s5]t[ue]rb[ae]t(?:e|[io0]n(?:s)?)?|ma[s54]terb[e38])\\b", DECLINED_PROFANE}, -- master-bate\masterb8\masterbat*\masterbation\masterbations\masterbate\masturbation\masturbating
	{ "\\b(?:m[a@]s[o0]ch[i1!]+st|s[a@]d[i1!]+st)\\b", DECLINED_PROFANE }, --masochist\sadist
	{ "\\bm[e3]d[uU]s[a@4]+\\b", DECLINED_PROFANE }, -- Medusa
	{ "\\bm[e3]n[a4]g[e3][a4]tr[o0][i1][s5]\\b", DECLINED_PROFANE }, -- menage a trois
	{ "\\bm[e3]th+\\b", DECLINED_PROFANE }, -- meth
	{ "\\bm[i1]lf\\b", DECLINED_PROFANE }, -- milf
	{ "\\bm[i1][s5][s5][i1][o0]n[a4]ry\\s*p[o0][s5][i1][t7][i1][o0]n\\b", DECLINED_PROFANE }, -- missionary position
	{ "\\b[m][o0]ng\\b", DECLINED_PROFANE }, -- mong
	{ "\\b(?:m[o0][li1][e3][s5]t|ch[il1][li1]dpr[e3]d[a@]t[o0]r|c[il1]p[a@])\\b", DECLINED_PROFANE }, --molest\childpreadtor\cipa
	{ "\\bm[o0][t7]h[e3]rfu[ck][e3]r|m[o0]f[o0]\\b", DECLINED_PROFANE }, -- motherfucker\mofo\m0fo\mof0
	{ "\\b[m]+[o0]+u[n]+d[o0]+[f]+v[e3]+n[u4]+s\\b", DECLINED_PROFANE }, -- mound of venus
	{ "\\bmrh[a@]nds\\b", DECLINED_PROFANE }, -- mr hands
	{ "\\b(?:m[o0uv]ff|m[o0uv]ffd[il1][vu][e3]r|m[o0uv]ffd[il1]v[il1]ng|m[o0u]ffp[uv]ff)\\b", DECLINED_PROFANE }, -- muff diver\muffdiving
	{ "\\b(?:m[o0]+u[n]+d[o0]+[f]+v[e3]+n[u4]+s|munch[e]r|c[a]rp[e3]tmunch[e3]r|p[o0][o0]ft[e3]r|bum(?:chum|bandit))|bum\\b", DECLINED_PROFANE }, -- muncher
	{ "\\b(?:m[uo0]th(?:a|afecker|er)?)\\b", DECLINED_PROFANE }, --mutha\muther\muthafecker
	{ "\\bn[a4]mb[l1][a@4]\\b", DECLINED_PROFANE }, -- nambla
	{ "\\bn[a4][wvu][a@4][s5\\$]h[i1l]\\b", DECLINED_PROFANE }, -- nawashi
	{ "\\b(n[e3]gr[0o@])\\b", DECLINED_PROFANE }, -- negro
	{ "\\bn[e3]mm[i1]e[s$z]+\\b", DECLINED_PROFANE }, -- Nemmies
	{ "\\b((neo)?n[a@4]z[i1!l])\\b", DECLINED_PROFANE }, -- nazi/neonazi
	{ "\\b[n]+[i1l]+g(?:n[o0]+g)?\\b", DECLINED_PROFANE }, -- nig nog
	{ "\\b(?:n[i1!]+g(?:[g9@e3h4]+[ra@h4s$z]+)?)\\b", DECLINED_PROFANE }, -- nigger
	{ "\\b[ny][i1l]mp[ho0][o0]m[a4][ni1l][i1l][a@4]ck\\b", DECLINED_PROFANE }, -- nimphomania
	{ "\\b[n]+[i1l]+[p]+l[e3]+(?:s\\b)?\\b", DECLINED_PROFANE }, -- nipple\nipples
	{ "\\b[n][i1l]qq[e3]r\\b", DECLINED_PROFANE }, -- niqqer
	{ "\\b(?:nob(?:head)?(?:jo(?:cky|key))?)\\b", DECLINED_PROFANE }, -- nob\nobhead\nobjocky\nobjokey
	{ "\\b[n]+[s5$]+[f]+[wvv]+\\b", DECLINED_PROFANE }, -- nsfw
	{ "\\b(?:nude|nud[il][t7]y+)\\b", DECLINED_PROFANE }, -- nude\nudity
	{ "\\b[n]+[u]+[t7]+t[e3n]+\\b|\\bn[yi1l]+m[pf]+h[o0]+(?:m[a4]+n[i1]+a)?\\b", DECLINED_PROFANE }, -- nutten\nympho\nymphomania
	{ "\\bnumbnuts?\\b|\\b(?:nu(?:mb|)bnuts?|nutbutter|nut(?:sack|ts)?)\\b", DECLINED_PROFANE }, --numbnuts\nutbutter\nutsack
	{ "\\b(o+[ck]+t+[op]+u+[sz]+s+y+)\\b", DECLINED_PROFANE }, -- octopussy
	{ "\\b[o0]m[o0]r[a@][s5]h[i1l]\\b", DECLINED_PROFANE }, -- omorashi
	{ "\\b(o+[n1i!l1e3c]+[u]+p+[t7]+[wv]+[o0]+[g9]+[i1!l1r]+[l1s\\$]+)\\b", DECLINED_PROFANE }, -- one cup two girls
	{ "\\b(o+[n1i!l1e3g]+[u]+y+[o0]+[n1i!l1e3j]+[a@]+[r]+)\\b", DECLINED_PROFANE }, -- one guy one jar
	{ "\\b[o0]rg[a@][s\\$][i1]?m[s\\$]?\\b", DECLINED_PROFANE }, -- orgasm
	{ "\\b[o0]+[r][g][y]\\b", DECLINED_PROFANE }, -- orgy
	{ "\\b(p[a@3]+[e3]+d[o0]ph[i1!l1]l[e3]+)\\b", DECLINED_PROFANE }, -- paedophile
	{ "\\b(p[a@]ki[e3])\\b", DECLINED_PROFANE }, -- paki
	{ "\\b(p[a@]nt[yi1!l1e3s\\$]+)\\b", DECLINED_PROFANE }, -- panties\panty
	{ "\\bp(a?e|ä)do(file|philer?)?s?\\b", DECLINED_PROFANE }, -- pedofile
	{ "\\b(p|ph|f)e*g(g|3)i*n*g\\b", DECLINED_PROFANE }, -- pegging
	{ "\\bp[e3]nn?[i1][s\\$]|w[il1][l1i][l1i][il1][e3][s5]?", DECLINED_PROFANE }, -- penis\willies
	{ "\\b(p[i1!|\\\\*3\\^]k[e3@]y)\\b", DECLINED_PROFANE }, -- pikey
	{ "p[i1][s\\$][s\\$]", DECLINED_PROFANE }, -- piss\pissing\pisspig\pissoff
	{ "\\bp[l1I!|a@]y[b8]o[yi1!|a@]\\b", DECLINED_PROFANE }, -- playboy
	{ "\\b(p(?:leasure)?(?:@|3)?)\\w*\\b", DECLINED_PROFANE }, -- pleasure chest
	{ "\\b(p(?:ole)?s?[mnr]o?k[e3]?[r@]s?)\\b", DECLINED_PROFANE }, -- pole smoker
	{ "\\bp[o0]rn[o0][s\\$]?\\b", DECLINED_PROFANE }, -- pons
	{ "\\b(p|pon)[o0]ypl[ai@]y\\b", DECLINED_PROFANE }, -- ponyplay
	{ "\\b(p|po|poo|po0|p00|poo[fv]|pu|puu|p[u\\*][fve\\*])\\b", DECLINED_PROFANE }, -- poof\poon\poontang
	{ "\\b(p|po|p00|p0o|p\\$\\$|p\\$\\$y)\\w*ch(u|oo|v)(t|d)e\\b", DECLINED_PROFANE }, -- poopchute
	{ "\\b(?:p(?:[o0]rn(?:[o0]gr[a@]phy)?|[o0]rno|[o0]rn0))\\b", DECLINED_PROFANE }, -- porn\porno
	{ "\\b(?:p[o0]rnh[uv]b|y[o0]up[o0]rn|r[e3]dt[u]b[e3])\\b", DECLINED_PROFANE }, --pornhub/youporn/redtube
	{ "\\b(pr[i1]nce\\s*albert\\s*p[i1]erc[i1]ng|p[a@]p|p[a@]q)\\b", DECLINED_PROFANE }, -- prince albert piercing
	{ "\\b[pP][tT][Hh][Cc]\\b", DECLINED_PROFANE }, -- pthc
	{ "\\b(p[uü]b[e3]s?)\\b", DECLINED_PROFANE }, -- pubes
	{ "\\b(pun|puna|pun@|pu\\dny|pu\\$\\$y)\\b", DECLINED_PROFANE }, -- punany
	{ "\\bpu[s\\$][s\\$][i1][e3][s\\$]\\b", DECLINED_PROFANE }, -- pussies
	{ "\\bpu[s\\$][s\\$]y[s\\$]?\\b", DECLINED_PROFANE }, -- pussy
	{ "\\bq[uv][e3][e3a4][fr]\\b", DECLINED_PROFANE }, -- queef/queer
	{ "\\bq[uv]+[a@][d]+[s5]\\b", DECLINED_PROFANE}, -- Quads
	{ "\\bq[uv][i1]m\\b", DECLINED_PROFANE }, -- quim
	{ "(\\bchin[ckg]s?(chong)?\\b|\\bk[iy]kes?\\b|\\bpoon(anie?|tang|tsee|tese)\\b|\\b[ck][o0][o0]n[s5]?\\b|\\bspi[ck]+s?\\b|\\bpik[e3]y|r[a@]gh[e3][a@]d|t[o0]w[e3]lh[e3][e3][a@]d|[s5]p[a@]c|jap|t[o0]w[e3]lh[e3][a@]d|m[o0]n[g6][o0][li1][o0][il1]d)", DECLINED_PROFANE }, -- racial slurs
	{ "(r|ra)[\\W_]*(a|@)[\\W_]*p(e|3|[\\W_]*)", DECLINED_PROFANE }, -- rape
	{ "\\b(r[e3]ct[uü]m)\\b", DECLINED_PROFANE }, -- rectum
	{ "\\b[rR][eE3][tT7][aA4][rR][dD]\\b", DECLINED_PROFANE }, -- retard
	{ "\\b(r[e3]v[e3]rs[e3]c[o0]wg[i1]r[l1])\\b", DECLINED_PROFANE }, -- reverse cowgirl
	{ "\\b(r[i1]mj[o0a@][bw])\\b", DECLINED_PROFANE }, -- rimjob\rimjaw
	{ "\\b(r[i1]mm[i1]ng)\\b", DECLINED_PROFANE }, -- rimming
	{ "\\b(r[o0]s[yi1]p[a@]lm)\\b", DECLINED_PROFANE }, -- rosy palm\rosy palm\her 5 sisters
	{ "\\b(r[uo0]st[yi1]tr[o0]mb[o0]ne)\\b", DECLINED_PROFANE }, -- rusty trombone
	{ "\\b[s\\$][&m]\\b", DECLINED_PROFANE }, -- s&m
	{ "\\b[s5][a@]d[il][s5]m\\b", DECLINED_PROFANE }, -- sadism
	{ "\\b[s\\$][a@]nt[o0]r[u\\^]m\\b", DECLINED_PROFANE }, -- santorum
	{ "\\b[s\\$][ck][@a4]t\\b", DECLINED_PROFANE }, -- scat
	{ "\\b(?:[s5$](?:chl[o0]ng|[a@]u[s5][a@]g[e3]qu[e3][e3]n))\\b", DECLINED_PROFANE }, -- schlong\sausagequeen
	{ "\\b[s\\$][ck][i1l!][s\\$][s\\$][o0][r9][i1l!][n\\#4a@][g9]\\b", DECLINED_PROFANE }, -- scissoring
	{ "\\b(?:scroa[t7]|scrot[eu]m?)\\b", DECLINED_PROFANE }, -- scrotum\scroat\scrote
	{ "\\b[s\\$][e3][m\\#4a@][e3][n\\#4a@]\\b", DECLINED_PROFANE }, -- semen
	{ "\\b(?:[s$]+[e3]+[m]+[i1]+[t7]+[i1]+[c]+|[s$]+[3e]+[m]+[i1]+[t7]+[i1]+[c]+)\\b", DECLINED_PROFANE }, -- Semetic
	{ "\\b.*[s\\$]+[e3]+[x]*.*\\b", DECLINED_PROFANE }, -- sex\groupsex\sexcam\sexo\sexual\sexually\sexy
	{ "\\b(?:b[uv][s5$]t[aA][li1][o0][a@]d|[a@]du[i1l]t|d[o0]nk[e3]yr[il1]bb[e3]r|[e3][a@]th[a@][il1]rp[il1][e3]|fl[o0]gth[e3]l[o0]g|h[a@]mfl[a@]p|b[e3][e3]fcurt[a@][il1]n)\\b", DECLINED_PROFANE }, --sexual slang
	{ "\\b(?:sh[a@4]+g(?:ger|gin(?:g)?)?)\\b", DECLINED_PROFANE }, --shag\shagger\shaggin\shagging
	{ "\\b(?:s[h\\#4a@][a@]ved[p\\$][u][s\\$][s\\$][y]|s[h\\#4a@][a@]ved[b8][e3][a@]ver)\\b", DECLINED_PROFANE }, -- shaved beaver\shaved pussy
	{ "\\b[s5$]h[e3]m[a@][li][e3]|h[e3][s5]h[e3]\\b", DECLINED_PROFANE }, -- shemale\heshe
	{ "\\b[s5$]h[il]b[a@]r[il]\\b", DECLINED_PROFANE }, -- shibari
	{ "\\b[s5\\$]h[i1][t\\+][s\\$]?|[s$]_h_[il1]_t|turd|cutr[o0]p[e3]\\b", DECLINED_PROFANE }, -- shit\shitblimp\shitblimp\turd\cutrope
	{ "\\b[s5]h[o0][o0]t(?:[il1]ng)?\\b", DECLINED_PROFANE }, -- Shoot\Shooting
	{ "\\b[s5$]h[o0]t[a@]\\b", DECLINED_PROFANE }, -- shota
	{ "\\b[sh$]hr[il]mp[il]ng\\b", DECLINED_PROFANE }, -- shrimping
	{ "\\b[s\\$][k\\+][e3][e3][t\\+]\\b", DECLINED_PROFANE }, -- skeet
	{ "\\b(s[l1i!]+a?nteye)\\b", DECLINED_PROFANE }, -- slanteye
	{ "[s\\$][l1]u[t\\+][s\\$]?", DECLINED_PROFANE }, -- sluts
	{ "\\b[s\\$]mu[t\\+][s\\$]?\\b", DECLINED_PROFANE }, -- smuts
	{ "\\b(s[nm]+[a@]+t[cck]+h)\\b", DECLINED_PROFANE }, -- snatch
	{ "\\b(snow[b6]+[a@]+ll[ing1i]+)\\b", DECLINED_PROFANE }, -- snowballing
	{ "\\b(s[o0]+d[o0]+m[1i!]+z[e3]+|s[o0]+d[o0]+m[yi1!]+)\\b", DECLINED_PROFANE }, -- sodomize\sodomy
	{ "\\b(s[p1!]+[a@4]+s[t7]+i[c\\*k]+)\\b", DECLINED_PROFANE }, -- spastic
	{ "\\b[s$]+p[l1o0]+[o0]+g[e3]+(?:m[o0]+[u5]+[s$]+e)?\\b|\\b[s5$]pl[o0][o0]g[e3]m[o0][o0][s5][e3]\\b", DECLINED_PROFANE }, -- splooge\sploogemoouse\spooge
	{ "\\bspr[e3][a@]dl[e3]g[s5$]\\b", DECLINED_PROFANE }, -- spread legs
	{ "\\b[s\\$]punk[s\\$]?\\b", DECLINED_PROFANE }, -- spunks
	{ "\\b(str[ae@]p[ao0]n|str[ae@]ppad[ao0])\\b", DECLINED_PROFANE }, -- strap on\strappado
	{ "\\bstr[i1!l1]p[ck]+l[uv]+b\\b", DECLINED_PROFANE }, -- strip club
	{ "\\b[s$5][t7][y][l1I!][e3][d][o0]ggy\\b", DECLINED_PROFANE }, -- style doggy
	{ "\\b(?:[s$5][uv]ck(?:[s5]|[e3]r)?)\\b", DECLINED_PROFANE }, -- suck\sucks
	{ "\\b[s$5][uv][il]c[il]d[e3][g9][il1]r[l1][$5s]\\b", DECLINED_PROFANE }, -- suicide girls
	{ "\\b[s$5]+[u5]+[l1]+[t7]+r[yi]+[wv]+[o0]+m[e3n]+\\b", DECLINED_PROFANE }, -- sultry women
	{ "\\b[s$5][wv][a4][s$5][t7y][i1]k[a@]\\b", DECLINED_PROFANE }, -- swastika
	{ "\\b[s$5][wv][i1!]n[g6][e3]r\\b", DECLINED_PROFANE }, -- swinger
	{ "\\b[t]+[a@][il]n[t7][e3]d[li1][o0][vu][e3]\\b", DECLINED_PROFANE }, -- tainted love
	{ "\\bt[o0]ng[uv][e3][il]n[a@]\\b", DECLINED_PROFANE}, --tongueina
	{ "\\b[t7][a@][s$5][t7][e3]my\\w*\\b", DECLINED_PROFANE }, -- taste my
	{ "\\b[t7][e3][a@][b8][a@][g6g9][g6g9][i1l!]\\w*\\b", DECLINED_PROFANE }, -- tea bagging
	{ "\\b[t][e3][r][f]|[t][h][o0][t]|[t][r][a@][d]\\b", DECLINED_PROFANE }, -- terf/thot/trad
	{ "\\bt[e3]rr[o0]r[il1][s5][tm]?\\b", DECLINED_PROFANE }, --terroist/terroism
	{ "\\btestic(?:a|4|@|k|x)?le?\\b", DECLINED_PROFANE }, --testical/testicle
	{ "\\b[t7][h4a@]r[e3][e3][s5][o0]m[e3]\\w*\\b", DECLINED_PROFANE }, -- threesome
	{ "\\b[t7][h4a@]r[o0][a@][t7][i1]n[g6]\\w*\\b", DECLINED_PROFANE }, -- throating
	{ "\\b[t+][h4a@][uv]m[b8][z2][il1][l1][l1][a@]\\w*\\b", DECLINED_PROFANE }, -- thumbzilla
	{ "\\b[t+][i1][e3]d[uv]p\\w*\\b", DECLINED_PROFANE }, -- tied up
	{ "\\b[t+][i1][g9]h[t+]\\s?[wW]\\S*\\b", DECLINED_PROFANE }, -- tight white
	{ "\\b(?:t[1i!]+[1i!e35y]*[sz]?\\b|t[i1]tt[i1][e3][s5]\\b|t[1i!]+[1i!e35y]*(?:w[aeiou]*n*k*|w*a*n*k*)\\b|tit(?:[s5]|wank)?\\b|titt(?:ie[35s]?|y)?\\b|teets\\b|tittywank\\b)", DECLINED_PROFANE }, -- tit\tits\titties\titty\t1tt1e5\tits\tittie5\titty\tittywank\teet\
	{ "\\b[t+][o0]un[g9]u[e3][i1]n[a@]\\S*\\b", DECLINED_PROFANE }, -- tongue in a
	{ "\\b[t+][o0]p[l1][e3]s\\S*\\b", DECLINED_PROFANE }, -- topless
	{ "\\b[t+][o0][s$5][s$5][e3]r\\S*\\b", DECLINED_PROFANE }, -- tosser
	{ "\\b[t][r][a@][n][n]+(ie|y)\\b", DECLINED_PROFANE }, -- tranny
	{ "\\b[t+]r[i1]b[a4@]d[i1][s$5]m\\S*\\b", DECLINED_PROFANE }, -- tribadism
	{ "\\b[t+]ub[g6][i1]rl\\S*\\b", DECLINED_PROFANE }, -- tubgirl
	{ "\\b[t+]u[s\\$]h[yi1l!]*\\b", DECLINED_PROFANE }, -- tushy
	{ "\\b(?:tw[a@4]t(?:s|head|ty)?|twu[n4@]t(?:er)?)\\b", DECLINED_PROFANE }, -- twat\twats\tw4t\twathead\twatty\twunt\twunter
	{ "\\b[t7]+w[i1]+n[k7]+(?:i[e3]+)?\\b", DECLINED_PROFANE }, -- twink\twinkie
	{ "\\b[t+]w[o0][gq][i1l!]r[l1!][s5$][o0]n[e3][ckq][uv]p\\b", DECLINED_PROFANE }, -- two girls one cup
	{ "\\b[uv]ndr[e3][s5$][s5$][i1l!]n[gq]\\b", DECLINED_PROFANE }, -- undressing
	{ "\\b[uv][pb][s5$][kx][i1l!]r[t7]+\\b", DECLINED_PROFANE }, -- upskirt
	{ "\\bur[e3][t7]hr[a@]p[l1][a@]y\\b", DECLINED_PROFANE }, -- urethra play
	{ "\\bur[o0]ph[i1l][l1][i1l][a@]\\b", DECLINED_PROFANE }, -- urophilia
	{ "\\b(?:v(?:a|1)gra|v[a@]gina)\\b", DECLINED_PROFANE }, -- vagina
	{ "\\b[v][e3]nu[s5$]m[o0][uv]nd\\b", DECLINED_PROFANE }, -- venus mound
	{ "\\b[v][i1][a@4][g6]r[a@4]\\b", DECLINED_PROFANE }, -- viagra
	{ "\\b[v][i1][b8]r[a@4][t7][o0]r\\b", DECLINED_PROFANE }, -- vibrator
	{ "\\b[v][i1][o0]l[e3][t7][wvv][a@4]nd\\b", DECLINED_PROFANE }, -- violet wand
	{ "\\b[v][o0]r[a@4]r[e3]ph[i1]l[i1][a@4]\\b", DECLINED_PROFANE }, -- vorarephilia
	{ "\\bv[o0]y([e3]ur|[e3]u[35]r|u[e3]r|[e3][uv]rw[e3]b)?\\b", DECLINED_PROFANE }, -- voyeur\voyeurweb\voyuer
	{ "\\b[v][u][l1]v[a@]\\b", DECLINED_PROFANE }, -- vulva
	{ "\\bwa[n@*]k(?:er|y?)?\\b|\\bw[a@*]ng\\b", DECLINED_PROFANE }, -- wank\wanker\wanky\wang
	{ "\\bw[e3]t\\s?dr[e3][a@]m\\b", DECLINED_PROFANE }, -- wet dream
	{ "\\bw[e3]t\\s?b[a@]ck\\b", DECLINED_PROFANE }, -- wetback
	{ "\\bwh[il1]t[e3]\\s?p[Oo]w[e3]r\\b", DECLINED_PROFANE }, -- white power
	{ "\\b(?:wh[0oa@e&r]?r[e3]?|ho[0oa@e&r]r[e3]?|wh[o0][a@]r|h[o0]r[e3])\\b", DECLINED_PROFANE }, -- whore\hoar\hoare\hoer\hore
	{ "\\b[wv][o0][rR][l1i!]d[s\\$5][e3]x\\b", DECLINED_PROFANE }, -- worldsex
	{ "\\b[wv]r[a@]pp[i!1]ngm[e3]n\\b", DECLINED_PROFANE }, -- wrapping men
	{ "\\b[wv]r[i!1][nk]k[l1!][e3]d[sS5\\$z][t7][a@]rf[i!1][s5\\$z]h[\\w\\W]*\\b", DECLINED_PROFANE }, -- wrinkled starfish
	{ "\\bx{1,3}[\\w\\W]*\\b", DECLINED_PROFANE }, -- xx\xxx
	{ "\\by[a@0][o0i1l]*\\b", DECLINED_PROFANE }, -- yaoi
	{ "\\by[e3][il1][il1][o0]w[s$]h[o0]w[e3]r[s$5]\\b", DECLINED_PROFANE }, -- yellow showers
	{ "\\by[i1!]f[fyi1!]y\\b", DECLINED_PROFANE }, -- yiffy
	{ "\\bz[o0][o0]ph[i1!]l[i1!][a@4]\\b", DECLINED_PROFANE }, -- zoophilia
}

oldFilterWords = {
	{ "dev", DECLINED_DEVELOPER },
	{ "developer", DECLINED_DEVELOPER },
	{ "csr", DECLINED_DEVELOPER },
	{ "gm", DECLINED_DEVELOPER },
	{ "ec", DECLINED_DEVELOPER },
	{ "qa", DECLINED_DEVELOPER },
	{ "ct", DECLINED_DEVELOPER },
	{ "mod", DECLINED_DEVELOPER },
	{ "staff", DECLINED_DEVELOPER },
	{ "swgemu", DECLINED_DEVELOPER },
	{ "swg", DECLINED_DEVELOPER },
	{ "anal", DECLINED_PROFANE },
	{ "ass", DECLINED_PROFANE },
	{ "arse", DECLINED_PROFANE },
	{ "biatch", DECLINED_PROFANE },
	{ "bitch", DECLINED_PROFANE },
	{ "bomb", DECLINED_PROFANE },
	{ "boob", DECLINED_PROFANE },
	{ "cancer", DECLINED_PROFANE },
	{ "chink", DECLINED_PROFANE },
	{ "christ", DECLINED_PROFANE },
	{ "clit", DECLINED_PROFANE },
	{ "cock", DECLINED_PROFANE },
	{ "coon", DECLINED_PROFANE },
	{ "cum", DECLINED_PROFANE },
	{ "cunt", DECLINED_PROFANE },
	{ "damn", DECLINED_PROFANE },
	{ "dick", DECLINED_PROFANE },
	{ "dingleberry", DECLINED_PROFANE },
	{ "dong", DECLINED_PROFANE },
	{ "ejaculat", DECLINED_PROFANE },
	{ "fag", DECLINED_PROFANE },
	{ "freak", DECLINED_PROFANE },
	{ "fuck", DECLINED_PROFANE },
	{ "fuk", DECLINED_PROFANE },
	{ "fuxxor", DECLINED_PROFANE },
	{ "gay", DECLINED_PROFANE },
	{ "george lucas", DECLINED_PROFANE },
	{ "gook", DECLINED_PROFANE },
	{ "homo", DECLINED_PROFANE },
	{ "hooker", DECLINED_PROFANE },
	{ "islam", DECLINED_PROFANE },
	{ "isis", DECLINED_PROFANE },
	{ "jackoff", DECLINED_PROFANE },
	{ "jesus", DECLINED_PROFANE },
	{ "jew", DECLINED_PROFANE },
	{ "jizz", DECLINED_PROFANE },
	{ "kike", DECLINED_PROFANE },
	{ "kunt", DECLINED_PROFANE },
	{ "labia", DECLINED_PROFANE },
	{ "lgbt", DECLINED_PROFANE },
	{ "lick", DECLINED_PROFANE },
	{ "masturba", DECLINED_PROFANE },
	{ "murder", DECLINED_PROFANE },
	{ "molest", DECLINED_PROFANE },
	{ "muslim", DECLINED_PROFANE },
	{ "nazi", DECLINED_PROFANE },
	{ "negro", DECLINED_PROFANE },
	{ "nigg", DECLINED_PROFANE },
	{ "nipple", DECLINED_PROFANE },
	{ "rape", DECLINED_PROFANE },
	{ "penis", DECLINED_PROFANE },
	{ "piss", DECLINED_PROFANE },
	{ "prick", DECLINED_PROFANE },
	{ "puss", DECLINED_PROFANE },
	{ "racist", DECLINED_PROFANE },
	{ "retard", DECLINED_PROFANE },
	{ "satan", DECLINED_PROFANE },
	{ "semitic", DECLINED_PROFANE },
	{ "sex", DECLINED_PROFANE },
	{ "shit", DECLINED_PROFANE },
	{ "skank", DECLINED_PROFANE },
	{ "slut", DECLINED_PROFANE },
	{ "spawnthemonkey", DECLINED_PROFANE },
	{ "spick", DECLINED_PROFANE },
	{ "sucks", DECLINED_PROFANE },
	{ "system", DECLINED_PROFANE },
	{ "thot", DECLINED_PROFANE },
	{ "tit", DECLINED_PROFANE },
	{ "twat", DECLINED_PROFANE },
	{ "vagina", DECLINED_PROFANE },
	{ "whore", DECLINED_PROFANE },
	{ "wtf", DECLINED_PROFANE },
	{ "Admiral", DECLINED_PROFANE },
	{ "Admirals", DECLINED_PROFANE },
	{ "Allah", DECLINED_PROFANE },
	{ "Anakin", DECLINED_PROFANE },
	{ "asshole", DECLINED_PROFANE },
	{ "ballbeater", DECLINED_PROFANE },
	{ "ballhitter", DECLINED_PROFANE },
	{ "balllicker", DECLINED_PROFANE },
	{ "ballsucker", DECLINED_PROFANE },
	{ "bangher", DECLINED_PROFANE },
	{ "bastard", DECLINED_PROFANE },
	{ "bastid", DECLINED_PROFANE },
	{ "bitch", DECLINED_PROFANE },
	{ "blowme", DECLINED_PROFANE },
	{ "Bobba", DECLINED_PROFANE },
	{ "Bodhisattva", DECLINED_PROFANE },
	{ "boobie", DECLINED_PROFANE },
	{ "Bothan", DECLINED_PROFANE },
	{ "breast", DECLINED_PROFANE },
	{ "Buddha", DECLINED_PROFANE },
	{ "captain", DECLINED_PROFANE },
	{ "captains", DECLINED_PROFANE },
	{ "Chewbackka", DECLINED_PROFANE },
	{ "Christ", DECLINED_PROFANE },
	{ "cock", DECLINED_PROFANE },
	{ "Commander", DECLINED_PROFANE },
	{ "Commanders", DECLINED_PROFANE },
	{ "coonass", DECLINED_PROFANE },
	{ "cracka", DECLINED_PROFANE },
	{ "crap", DECLINED_PROFANE },
	{ "CSR", DECLINED_PROFANE },
	{ "cum", DECLINED_PROFANE },
	{ "cunt", DECLINED_PROFANE },
	{ "Darth", DECLINED_PROFANE },
	{ "dick", DECLINED_PROFANE },
	{ "Diq", DECLINED_PROFANE },
	{ "Donkeypunch", DECLINED_PROFANE },
	{ "fack", DECLINED_PROFANE },
	{ "fag", DECLINED_PROFANE },
	{ "Fett", DECLINED_PROFANE },
	{ "feck", DECLINED_PROFANE },
	{ "fuck", DECLINED_PROFANE },
	{ "fuk", DECLINED_PROFANE },
	{ "Fuqu", DECLINED_PROFANE },
	{ "General", DECLINED_PROFANE },
	{ "Generals", DECLINED_PROFANE },
	{ "ghey", DECLINED_PROFANE },
	{ "-GM", DECLINED_PROFANE },
	{ "_GM", DECLINED_PROFANE },
	{ "GM-", DECLINED_PROFANE },
	{ "GM_", DECLINED_PROFANE },
	{ "god", DECLINED_PROFANE },
	{ "HillBilly", DECLINED_PROFANE },
	{ "Human", DECLINED_PROFANE },
	{ "Isuccacocc", DECLINED_PROFANE },
	{ "Ithorian", DECLINED_PROFANE },
	{ "Jango", DECLINED_PROFANE },
	{ "Jedi", DECLINED_PROFANE },
	{ "Jehovah", DECLINED_PROFANE },
	{ "Jehova", DECLINED_PROFANE },
	{ "Jesus", DECLINED_PROFANE },
	{ "klukluxklan", DECLINED_PROFANE },
	{ "KneeGrow", DECLINED_PROFANE },
	{ "kunt", DECLINED_PROFANE },
	{ "Lando", DECLINED_PROFANE },
	{ "Leia", DECLINED_PROFANE },
	{ "lesbian", DECLINED_PROFANE },
	{ "lieutenant", DECLINED_PROFANE },
	{ "Lieutenant", DECLINED_PROFANE },
	{ "lieutenants", DECLINED_PROFANE },
	{ "Major", DECLINED_PROFANE },
	{ "Majors", DECLINED_PROFANE },
	{ "Marshal", DECLINED_PROFANE },
	{ "Marshals", DECLINED_PROFANE },
	{ "Messiah", DECLINED_PROFANE },
	{ "MonCalomari", DECLINED_PROFANE },
	{ "nazi", DECLINED_PROFANE },
	{ "niga", DECLINED_PROFANE },
	{ "nigga", DECLINED_PROFANE },
	{ "nigger", DECLINED_PROFANE },
	{ "nympho", DECLINED_PROFANE },
	{ "Officer", DECLINED_PROFANE },
	{ "Officers", DECLINED_PROFANE },
	{ "Padme", DECLINED_PROFANE },
	{ "Penis", DECLINED_PROFANE },
	{ "Panis", DECLINED_PROFANE },
	{ "Player", DECLINED_PROFANE },
	{ "poon", DECLINED_PROFANE },
	{ "prick", DECLINED_PROFANE },
	{ "Private", DECLINED_PROFANE },
	{ "Privates", DECLINED_PROFANE },
	{ "pubic", DECLINED_PROFANE },
	{ "pussy", DECLINED_PROFANE },
	{ "Quirfag", DECLINED_PROFANE },
	{ "qunt", DECLINED_PROFANE },
	{ "raghead", DECLINED_PROFANE },
	{ "redneck", DECLINED_PROFANE },
	{ "Rodian", DECLINED_PROFANE },
	{ "seaman", DECLINED_PROFANE },
	{ "seamans", DECLINED_PROFANE },
	{ "seeman", DECLINED_PROFANE },
	{ "seemen", DECLINED_PROFANE },
	{ "semen", DECLINED_PROFANE },
	{ "Sith", DECLINED_PROFANE },
	{ "skank", DECLINED_PROFANE },
	{ "skanq", DECLINED_PROFANE },
	{ "Skywalker", DECLINED_PROFANE },
	{ "slut", DECLINED_PROFANE },
	{ "snatch", DECLINED_PROFANE },
	{ "Solo", DECLINED_PROFANE },
	{ "spoog", DECLINED_PROFANE },
	{ "STFU", DECLINED_PROFANE },
	{ "suck", DECLINED_PROFANE },
	{ "suckme", DECLINED_PROFANE },
	{ "Sullistan", DECLINED_PROFANE },
	{ "swganh", DECLINED_PROFANE },
	{ "SWGEmu", DECLINED_PROFANE },
	{ "tarbaby", DECLINED_PROFANE },
	{ "testicle", DECLINED_PROFANE },
	{ "Trandoshan", DECLINED_PROFANE },
	{ "twi'lek", DECLINED_PROFANE },
	{ "Vader", DECLINED_PROFANE },
	{ "vagina", DECLINED_PROFANE },
	{ "wanker", DECLINED_PROFANE },
	{ "Warrant Officers", DECLINED_PROFANE },
	{ "Warrants", DECLINED_PROFANE },
	{ "wetback", DECLINED_PROFANE },
	{ "whore", DECLINED_PROFANE },
	{ "Wookie", DECLINED_PROFANE },
	{ "Yoda", DECLINED_PROFANE },
	{ "Yahweh", DECLINED_PROFANE },
	{ "Yahveh", DECLINED_PROFANE },
	{ "Zabrak", DECLINED_PROFANE },
	{ "skiiwalker", DECLINED_PROFANE },
	{ "Jedi", DECLINED_PROFANE },
	{ "Jeedi", DECLINED_PROFANE },
	{ "jedii", DECLINED_PROFANE },
	{ "jiidi", DECLINED_PROFANE },
	{ "Hitler", DECLINED_PROFANE },
	{ "lootmeh", DECLINED_PROFANE },
	{ "loot", DECLINED_PROFANE },
	{ "lawlicake", DECLINED_PROFANE },
	{ "lawli", DECLINED_PROFANE },
	{ "medirty", DECLINED_PROFANE },
	{ "lester", DECLINED_PROFANE },
	{ "mohlester", DECLINED_PROFANE },
	{ "moelester", DECLINED_PROFANE },
	{ "EyeP", DECLINED_PROFANE },
	{ "eyepfreely", DECLINED_PROFANE },
	{ "airmarshall", DECLINED_PROFANE },
	{ "medic", DECLINED_PROFANE },
	{ "doctor", DECLINED_PROFANE },
	{ "sittstain", DECLINED_PROFANE },
	{ "shitstain", DECLINED_PROFANE },
	{ "sitt", DECLINED_PROFANE },
	{ "stain", DECLINED_PROFANE },
	{ "Emperor", DECLINED_PROFANE },
	{ "palpatine", DECLINED_PROFANE },
	{ "Palpatin", DECLINED_PROFANE },
	{ "DARKLORD", DECLINED_PROFANE },
	{ "DerkLord", DECLINED_PROFANE },
	{ "Lord", DECLINED_PROFANE },
	{ "Sith", DECLINED_PROFANE },
	{ "Siith", DECLINED_PROFANE },
	{ "Sithlord", DECLINED_PROFANE },
	{ "Aarrba", DECLINED_FICT_RESERVED },
	{ "Aayla Secura", DECLINED_FICT_RESERVED },
	{ "Achk Med-Beq", DECLINED_FICT_RESERVED },
	{ "Ackmena", DECLINED_FICT_RESERVED },
	{ "Acros-Krik", DECLINED_FICT_RESERVED },
	{ "Adi Gallia", DECLINED_FICT_RESERVED },
	{ "Admiral Ozzel", DECLINED_FICT_RESERVED },
	{ "Admiral Ackbar", DECLINED_FICT_RESERVED },
	{ "Admiral Daala", DECLINED_FICT_RESERVED },
	{ "Admiral Piett", DECLINED_FICT_RESERVED },
	{ "Admiral Screed", DECLINED_FICT_RESERVED },
	{ "Admiral Thrawn", DECLINED_FICT_RESERVED },
	{ "Agen Kolar", DECLINED_FICT_RESERVED },
	{ "Ak-rev", DECLINED_FICT_RESERVED },
	{ "Aks Moe", DECLINED_FICT_RESERVED },
	{ "Aldar Beedo", DECLINED_FICT_RESERVED },
	{ "Amaiza", DECLINED_FICT_RESERVED },
	{ "Anakin Skywalker", DECLINED_FICT_RESERVED },
	{ "Anakin Solo", DECLINED_FICT_RESERVED },
	{ "Anchor Blue", DECLINED_FICT_RESERVED },
	{ "Anduvil", DECLINED_FICT_RESERVED },
	{ "Antidar Williams", DECLINED_FICT_RESERVED },
	{ "Ark Roose", DECLINED_FICT_RESERVED },
	{ "Aron Peacebringer", DECLINED_FICT_RESERVED },
	{ "Asajj Ventress", DECLINED_FICT_RESERVED },
	{ "Ask Aak", DECLINED_FICT_RESERVED },
	{ "Augara Jowil", DECLINED_FICT_RESERVED },
	{ "Auren Yomm", DECLINED_FICT_RESERVED },
	{ "Aurra Sing", DECLINED_FICT_RESERVED },
	{ "Ayy Vida", DECLINED_FICT_RESERVED },
	{ "Axkva Min", DECLINED_FICT_RESERVED },
	{ "Bail Organa", DECLINED_FICT_RESERVED },
	{ "Bana Breemu", DECLINED_FICT_RESERVED },
	{ "Bane Malar", DECLINED_FICT_RESERVED },
	{ "Barada", DECLINED_FICT_RESERVED },
	{ "Baron Papanoida", DECLINED_FICT_RESERVED },
	{ "Barquin D'an", DECLINED_FICT_RESERVED },
	{ "Barriss Offee", DECLINED_FICT_RESERVED },
	{ "Bastila Shan", DECLINED_FICT_RESERVED },
	{ "Ben Kenobi", DECLINED_FICT_RESERVED },
	{ "Ben Quadinaros", DECLINED_FICT_RESERVED },
	{ "Beru Lars", DECLINED_FICT_RESERVED },
	{ "Bib Fortuna", DECLINED_FICT_RESERVED },
	{ "Biggs Darklighter", DECLINED_FICT_RESERVED },
	{ "Boba Fett", DECLINED_FICT_RESERVED },
	{ "Boles Roor", DECLINED_FICT_RESERVED },
	{ "Borsk Fey'lya", DECLINED_FICT_RESERVED },
	{ "Boss Nass", DECLINED_FICT_RESERVED },
	{ "Bossk", DECLINED_FICT_RESERVED },
	{ "Brakiss", DECLINED_FICT_RESERVED },
	{ "Bren Derlin", DECLINED_FICT_RESERVED },
	{ "Bria Tharen", DECLINED_FICT_RESERVED },
	{ "Bultar Swan", DECLINED_FICT_RESERVED },
	{ "Callista", DECLINED_FICT_RESERVED },
	{ "Calo Nord", DECLINED_FICT_RESERVED },
	{ "Canderous Ordo", DECLINED_FICT_RESERVED },
	{ "Cane Adiss", DECLINED_FICT_RESERVED },
	{ "Captain Needa", DECLINED_FICT_RESERVED },
	{ "Captain Panaka", DECLINED_FICT_RESERVED },
	{ "Captain Rekab", DECLINED_FICT_RESERVED },
	{ "Captain Tarpals", DECLINED_FICT_RESERVED },
	{ "Captain Typho", DECLINED_FICT_RESERVED },
	{ "Captain-Supervisor Grammel", DECLINED_FICT_RESERVED },
	{ "Carl", DECLINED_FICT_RESERVED },
	{ "Carlist Rieekan", DECLINED_FICT_RESERVED },
	{ "Carth Onasi", DECLINED_FICT_RESERVED },
	{ "Cebann Veekan", DECLINED_FICT_RESERVED },
	{ "Chancellor Valorum", DECLINED_FICT_RESERVED },
	{ "Charal", DECLINED_FICT_RESERVED },
	{ "Chewbacca", DECLINED_FICT_RESERVED },
	{ "Chi Eekway", DECLINED_FICT_RESERVED },
	{ "Chief Chirpa", DECLINED_FICT_RESERVED },
	{ "Chukha-Trok", DECLINED_FICT_RESERVED },
	{ "Chyler", DECLINED_FICT_RESERVED },
	{ "Cindel Towani", DECLINED_FICT_RESERVED },
	{ "Clegg Holdfast", DECLINED_FICT_RESERVED },
	{ "Cliegg Lars", DECLINED_FICT_RESERVED },
	{ "Coleman Trebor", DECLINED_FICT_RESERVED },
	{ "Commander Bacara", DECLINED_FICT_RESERVED },
	{ "Commander Bly", DECLINED_FICT_RESERVED },
	{ "Commander Cody", DECLINED_FICT_RESERVED },
	{ "Commander Gree", DECLINED_FICT_RESERVED },
	{ "Commander Neyo", DECLINED_FICT_RESERVED },
	{ "Commander Thire", DECLINED_FICT_RESERVED },
	{ "Conan Motti", DECLINED_FICT_RESERVED },
	{ "Corde", DECLINED_FICT_RESERVED },
	{ "Corla Metonae", DECLINED_FICT_RESERVED },
	{ "Corran Horn", DECLINED_FICT_RESERVED },
	{ "Count Dooku", DECLINED_FICT_RESERVED },
	{ "Crix Madine", DECLINED_FICT_RESERVED },
	{ "Daakman Barrek", DECLINED_FICT_RESERVED },
	{ "Dack Ralter", DECLINED_FICT_RESERVED },
	{ "Dannl Faytonni", DECLINED_FICT_RESERVED },
	{ "Darth Bandon", DECLINED_FICT_RESERVED },
	{ "Darth Malak", DECLINED_FICT_RESERVED },
	{ "Darth Maul", DECLINED_FICT_RESERVED },
	{ "Darth Sidious", DECLINED_FICT_RESERVED },
	{ "Darth Vader", DECLINED_FICT_RESERVED },
	{ "Dash Rendar", DECLINED_FICT_RESERVED },
	{ "Daultay Dofine", DECLINED_FICT_RESERVED },
	{ "Davik Kang", DECLINED_FICT_RESERVED },
	{ "Deej Warrick", DECLINED_FICT_RESERVED },
	{ "Dengar", DECLINED_FICT_RESERVED },
	{ "Depa Billaba", DECLINED_FICT_RESERVED },
	{ "Dexter Jettster", DECLINED_FICT_RESERVED },
	{ "Diva Shaliqua", DECLINED_FICT_RESERVED },
	{ "Doc", DECLINED_FICT_RESERVED },
	{ "Doctor Evazan", DECLINED_FICT_RESERVED },
	{ "Doda Boedonawieedo", DECLINED_FICT_RESERVED },
	{ "Dorme", DECLINED_FICT_RESERVED },
	{ "Droopy McCool", DECLINED_FICT_RESERVED },
	{ "Dud Bolt", DECLINED_FICT_RESERVED },
	{ "Durge", DECLINED_FICT_RESERVED },
	{ "Ebe Endocott", DECLINED_FICT_RESERVED },
	{ "Eeth Koth", DECLINED_FICT_RESERVED },
	{ "Elan Mak", DECLINED_FICT_RESERVED },
	{ "Elan Sleazebaggano", DECLINED_FICT_RESERVED },
	{ "Ephant Mon", DECLINED_FICT_RESERVED },
	{ "Even Piell", DECLINED_FICT_RESERVED },
	{ "Exar Kun", DECLINED_FICT_RESERVED },
	{ "Fang Zar", DECLINED_FICT_RESERVED },
	{ "Fema Baab", DECLINED_FICT_RESERVED },
	{ "Fiolla", DECLINED_FICT_RESERVED },
	{ "Foul Moudama", DECLINED_FICT_RESERVED },
	{ "Gaeriel Captison", DECLINED_FICT_RESERVED },
	{ "Gaff", DECLINED_FICT_RESERVED },
	{ "Gallandro", DECLINED_FICT_RESERVED },
	{ "Garindan", DECLINED_FICT_RESERVED },
	{ "Garm Bel", DECLINED_FICT_RESERVED },
	{ "Gasgano", DECLINED_FICT_RESERVED },
	{ "General Grievous", DECLINED_FICT_RESERVED },
	{ "General Tagge", DECLINED_FICT_RESERVED },
	{ "General Veers", DECLINED_FICT_RESERVED },
	{ "General Yavid", DECLINED_FICT_RESERVED },
	{ "Ghent", DECLINED_FICT_RESERVED },
	{ "Giddean Danu", DECLINED_FICT_RESERVED },
	{ "Gilad Pellaeon", DECLINED_FICT_RESERVED },
	{ "Gizor Dellso", DECLINED_FICT_RESERVED },
	{ "Governor Koong", DECLINED_FICT_RESERVED },
	{ "Gragra", DECLINED_FICT_RESERVED },
	{ "Greeata", DECLINED_FICT_RESERVED },
	{ "Greedo", DECLINED_FICT_RESERVED },
	{ "Grizz Frix", DECLINED_FICT_RESERVED },
	{ "Halla", DECLINED_FICT_RESERVED },
	{ "Han Solo", DECLINED_FICT_RESERVED },
	{ "Hermi Odle", DECLINED_FICT_RESERVED },
	{ "Hermione Bagwa", DECLINED_FICT_RESERVED },
	{ "Horox Ryyder", DECLINED_FICT_RESERVED },
	{ "Iaco Stark", DECLINED_FICT_RESERVED },
	{ "Indiana Jones", DECLINED_FICT_RESERVED },
	{ "Isolder", DECLINED_FICT_RESERVED },
	{ "Ister Paddie", DECLINED_FICT_RESERVED },
	{ "Jabba", DECLINED_FICT_RESERVED },
	{ "Jacen Solo", DECLINED_FICT_RESERVED },
	{ "Jaina Solo", DECLINED_FICT_RESERVED },
	{ "Jan Dodonna", DECLINED_FICT_RESERVED },
	{ "Jango Fett", DECLINED_FICT_RESERVED },
	{ "Jann Tosh", DECLINED_FICT_RESERVED },
	{ "Janu Godalhi", DECLINED_FICT_RESERVED },
	{ "Janus Greejatus", DECLINED_FICT_RESERVED },
	{ "Jar-Jar Binks", DECLINED_FICT_RESERVED },
	{ "Jasper McKnives", DECLINED_FICT_RESERVED },
	{ "Jaxxon", DECLINED_FICT_RESERVED },
	{ "Jek Porkins", DECLINED_FICT_RESERVED },
	{ "Jem Ysanna", DECLINED_FICT_RESERVED },
	{ "Jessa", DECLINED_FICT_RESERVED },
	{ "Jessica Meade", DECLINED_FICT_RESERVED },
	{ "Jira", DECLINED_FICT_RESERVED },
	{ "Jobal Naberrie", DECLINED_FICT_RESERVED },
	{ "Jocasta Nu", DECLINED_FICT_RESERVED },
	{ "Joh Yowza", DECLINED_FICT_RESERVED },
	{ "Jolee Bindo", DECLINED_FICT_RESERVED },
	{ "Joruus C'baoth", DECLINED_FICT_RESERVED },
	{ "Juhani", DECLINED_FICT_RESERVED },
	{ "K'Kruhk", DECLINED_FICT_RESERVED },
	{ "Kabe", DECLINED_FICT_RESERVED },
	{ "Kaink", DECLINED_FICT_RESERVED },
	{ "Kalyn Farnmir", DECLINED_FICT_RESERVED },
	{ "Ketwol", DECLINED_FICT_RESERVED },
	{ "Ki-Adi-Mundi", DECLINED_FICT_RESERVED },
	{ "Kir Kanos", DECLINED_FICT_RESERVED },
	{ "Kit Fisto", DECLINED_FICT_RESERVED },
	{ "Kitik Keed'kak", DECLINED_FICT_RESERVED },
	{ "Kitster", DECLINED_FICT_RESERVED },
	{ "Kleb Zellock", DECLINED_FICT_RESERVED },
	{ "Komari Vosa", DECLINED_FICT_RESERVED },
	{ "Kybo Ren-Cha", DECLINED_FICT_RESERVED },
	{ "Kyp Durron", DECLINED_FICT_RESERVED },
	{ "Lama Su", DECLINED_FICT_RESERVED },
	{ "Lando Calrissian", DECLINED_FICT_RESERVED },
	{ "Lars Needa", DECLINED_FICT_RESERVED },
	{ "Leektar", DECLINED_FICT_RESERVED },
	{ "Leia Organa", DECLINED_FICT_RESERVED },
	{ "Lexi Dio", DECLINED_FICT_RESERVED },
	{ "Lieutenant Oicunn", DECLINED_FICT_RESERVED },
	{ "Lobot", DECLINED_FICT_RESERVED },
	{ "Logray", DECLINED_FICT_RESERVED },
	{ "Lott Dod", DECLINED_FICT_RESERVED },
	{ "Luke Skywalker", DECLINED_FICT_RESERVED },
	{ "Luminara Unduli", DECLINED_FICT_RESERVED },
	{ "Lumiya", DECLINED_FICT_RESERVED },
	{ "Lushros Dofine", DECLINED_FICT_RESERVED },
	{ "Lyn Me", DECLINED_FICT_RESERVED },
	{ "Mace Towani", DECLINED_FICT_RESERVED },
	{ "Mace Windu", DECLINED_FICT_RESERVED },
	{ "Magaloof", DECLINED_FICT_RESERVED },
	{ "Male-Dee", DECLINED_FICT_RESERVED },
	{ "Mara-Jade Skywalker", DECLINED_FICT_RESERVED },
	{ "Mars Guo", DECLINED_FICT_RESERVED },
	{ "Mas Amedda", DECLINED_FICT_RESERVED },
	{ "Mawhonic", DECLINED_FICT_RESERVED },
	{ "Max Rebo", DECLINED_FICT_RESERVED },
	{ "Maxiron Agolerga", DECLINED_FICT_RESERVED },
	{ "Meena Tills", DECLINED_FICT_RESERVED },
	{ "Melas", DECLINED_FICT_RESERVED },
	{ "Melee", DECLINED_FICT_RESERVED },
	{ "Merumeru", DECLINED_FICT_RESERVED },
	{ "Mission Vao", DECLINED_FICT_RESERVED },
	{ "Moff Jerjerrod", DECLINED_FICT_RESERVED },
	{ "Moff Tarkin", DECLINED_FICT_RESERVED },
	{ "Momaw Nadon", DECLINED_FICT_RESERVED },
	{ "Mon Julpa", DECLINED_FICT_RESERVED },
	{ "Mon Mothma", DECLINED_FICT_RESERVED },
	{ "Muftak", DECLINED_FICT_RESERVED },
	{ "Mungo Baobab", DECLINED_FICT_RESERVED },
	{ "Myhr Rho", DECLINED_FICT_RESERVED },
	{ "Nar Hida", DECLINED_FICT_RESERVED },
	{ "Nee Alavar", DECLINED_FICT_RESERVED },
	{ "Nem Bees", DECLINED_FICT_RESERVED },
	{ "Neva Kee", DECLINED_FICT_RESERVED },
	{ "Niai Fieso", DECLINED_FICT_RESERVED },
	{ "Nien Nunb", DECLINED_FICT_RESERVED },
	{ "Nilo", DECLINED_FICT_RESERVED },
	{ "Noa Briqualon", DECLINED_FICT_RESERVED },
	{ "Nom Anor", DECLINED_FICT_RESERVED },
	{ "Nute Gunray", DECLINED_FICT_RESERVED },
	{ "Nym", DECLINED_FICT_RESERVED },
	{ "Nyrat Agira", DECLINED_FICT_RESERVED },
	{ "Oakie Dokes", DECLINED_FICT_RESERVED },
	{ "Obi-Wan Kenobi", DECLINED_FICT_RESERVED },
	{ "Odumin", DECLINED_FICT_RESERVED },
	{ "Ody Mandrell", DECLINED_FICT_RESERVED },
	{ "Olana Chion", DECLINED_FICT_RESERVED },
	{ "Onaconda Farr", DECLINED_FICT_RESERVED },
	{ "Onara Kuat", DECLINED_FICT_RESERVED },
	{ "Oola", DECLINED_FICT_RESERVED },
	{ "Oppo Rancisis", DECLINED_FICT_RESERVED },
	{ "Orn Free Taa", DECLINED_FICT_RESERVED },
	{ "Oro Dassyne", DECLINED_FICT_RESERVED },
	{ "Orrimaarko", DECLINED_FICT_RESERVED },
	{ "Ottegru Grey", DECLINED_FICT_RESERVED },
	{ "Owen Lars", DECLINED_FICT_RESERVED },
	{ "Pablo-Jill", DECLINED_FICT_RESERVED },
	{ "Padme Amidala", DECLINED_FICT_RESERVED },
	{ "Palpatine", DECLINED_FICT_RESERVED },
	{ "Paploo", DECLINED_FICT_RESERVED },
	{ "Pash Cracken", DECLINED_FICT_RESERVED },
	{ "Passel Argente", DECLINED_FICT_RESERVED },
	{ "Pax Bonkik", DECLINED_FICT_RESERVED },
	{ "Paxi Sylo", DECLINED_FICT_RESERVED },
	{ "Pello Scrambas", DECLINED_FICT_RESERVED },
	{ "Plo Koon", DECLINED_FICT_RESERVED },
	{ "Po Nudo", DECLINED_FICT_RESERVED },
	{ "Poggle", DECLINED_FICT_RESERVED },
	{ "Ponda Baba", DECLINED_FICT_RESERVED },
	{ "Pooja Naberrie", DECLINED_FICT_RESERVED },
	{ "Pote Snitkin", DECLINED_FICT_RESERVED },
	{ "Prince Xizor", DECLINED_FICT_RESERVED },
	{ "Princess Leia", DECLINED_FICT_RESERVED },
	{ "Queen Apailana", DECLINED_FICT_RESERVED },
	{ "Queen Izrina", DECLINED_FICT_RESERVED },
	{ "Queen Jamillia", DECLINED_FICT_RESERVED },
	{ "Qui-Gon Jinn", DECLINED_FICT_RESERVED },
	{ "Quinlan Vos", DECLINED_FICT_RESERVED },
	{ "Rappertunie", DECLINED_FICT_RESERVED },
	{ "Ratts Tyerell", DECLINED_FICT_RESERVED },
	{ "Red", DECLINED_FICT_RESERVED },
	{ "Ree-Yees", DECLINED_FICT_RESERVED },
	{ "Rekkon", DECLINED_FICT_RESERVED },
	{ "Rep Been", DECLINED_FICT_RESERVED },
	{ "Rep Teers", DECLINED_FICT_RESERVED },
	{ "Reti", DECLINED_FICT_RESERVED },
	{ "Ric Olie", DECLINED_FICT_RESERVED },
	{ "Romeo Treblanc", DECLINED_FICT_RESERVED },
	{ "Ronet Coorr", DECLINED_FICT_RESERVED },
	{ "Roron Corobb", DECLINED_FICT_RESERVED },
	{ "Rukh", DECLINED_FICT_RESERVED },
	{ "Rune Haako", DECLINED_FICT_RESERVED },
	{ "Ruwee Naberrie", DECLINED_FICT_RESERVED },
	{ "Ryoo Naberrie", DECLINED_FICT_RESERVED },
	{ "Rystall", DECLINED_FICT_RESERVED },
	{ "Sabe", DECLINED_FICT_RESERVED },
	{ "Saelt-Marae", DECLINED_FICT_RESERVED },
	{ "Saesee Tiin", DECLINED_FICT_RESERVED },
	{ "Sagoro Autem", DECLINED_FICT_RESERVED },
	{ "Salacious Crumb", DECLINED_FICT_RESERVED },
	{ "Salla Zend", DECLINED_FICT_RESERVED },
	{ "Salporin", DECLINED_FICT_RESERVED },
	{ "San Hill", DECLINED_FICT_RESERVED },
	{ "Saul Karath", DECLINED_FICT_RESERVED },
	{ "Sebulba", DECLINED_FICT_RESERVED },
	{ "Sei Taria", DECLINED_FICT_RESERVED },
	{ "Seib Nod", DECLINED_FICT_RESERVED },
	{ "Sena Midanyl", DECLINED_FICT_RESERVED },
	{ "Serji-X Arrogantus", DECLINED_FICT_RESERVED },
	{ "Sha'a Gi", DECLINED_FICT_RESERVED },
	{ "Shaak Ti", DECLINED_FICT_RESERVED },
	{ "Shmi Skywalker", DECLINED_FICT_RESERVED },
	{ "Shodu", DECLINED_FICT_RESERVED },
	{ "Shu Mai", DECLINED_FICT_RESERVED },
	{ "Silya Shessaun", DECLINED_FICT_RESERVED },
	{ "Sio Bibble", DECLINED_FICT_RESERVED },
	{ "Siri Tachi", DECLINED_FICT_RESERVED },
	{ "Sly Moore", DECLINED_FICT_RESERVED },
	{ "Slyther Bushforb", DECLINED_FICT_RESERVED },
	{ "Sola Naberrie", DECLINED_FICT_RESERVED },
	{ "Sora Bulq", DECLINED_FICT_RESERVED },
	{ "Stass Allie", DECLINED_FICT_RESERVED },
	{ "Swilla Corey", DECLINED_FICT_RESERVED },
	{ "Sy Snootles", DECLINED_FICT_RESERVED },
	{ "Talon Karrde", DECLINED_FICT_RESERVED },
	{ "Tanith Shire", DECLINED_FICT_RESERVED },
	{ "Tannon Praji", DECLINED_FICT_RESERVED },
	{ "Tarfful", DECLINED_FICT_RESERVED },
	{ "Tarkov", DECLINED_FICT_RESERVED },
	{ "Tarr Seirr", DECLINED_FICT_RESERVED },
	{ "Tas Kee", DECLINED_FICT_RESERVED },
	{ "Taun We", DECLINED_FICT_RESERVED },
	{ "Teckla", DECLINED_FICT_RESERVED },
	{ "Teek", DECLINED_FICT_RESERVED },
	{ "Teemto Pagalies", DECLINED_FICT_RESERVED },
	{ "Terak", DECLINED_FICT_RESERVED },
	{ "Terr Taneel", DECLINED_FICT_RESERVED },
	{ "Tessek", DECLINED_FICT_RESERVED },
	{ "Theomet Danle", DECLINED_FICT_RESERVED },
	{ "Tikkes", DECLINED_FICT_RESERVED },
	{ "Tion Medon", DECLINED_FICT_RESERVED },
	{ "Toonbuck Toora", DECLINED_FICT_RESERVED },
	{ "Toryn Farr", DECLINED_FICT_RESERVED },
	{ "Tru Veld", DECLINED_FICT_RESERVED },
	{ "Tsavong Lah", DECLINED_FICT_RESERVED },
	{ "Tundra Dowmeia", DECLINED_FICT_RESERVED },
	{ "Tzizvvt", DECLINED_FICT_RESERVED },
	{ "Ulic Qel-Droma", DECLINED_FICT_RESERVED },
	{ "Umpass-stay", DECLINED_FICT_RESERVED },
	{ "Vergere", DECLINED_FICT_RESERVED },
	{ "Vilmarh Grahrk", DECLINED_FICT_RESERVED },
	{ "Voolvif Monn", DECLINED_FICT_RESERVED },
	{ "Wald", DECLINED_FICT_RESERVED },
	{ "Wam Lufba", DECLINED_FICT_RESERVED },
	{ "Wan Sandage", DECLINED_FICT_RESERVED },
	{ "Wat Tambor", DECLINED_FICT_RESERVED },
	{ "Watto", DECLINED_FICT_RESERVED },
	{ "Wedge Antilles", DECLINED_FICT_RESERVED },
	{ "Wes Janson", DECLINED_FICT_RESERVED },
	{ "Wicket Warrick", DECLINED_FICT_RESERVED },
	{ "Willrow Hood", DECLINED_FICT_RESERVED },
	{ "Willy", DECLINED_FICT_RESERVED },
	{ "Winter", DECLINED_FICT_RESERVED },
	{ "Wuher", DECLINED_FICT_RESERVED },
	{ "Yaddle", DECLINED_FICT_RESERVED },
	{ "Yarael Poof", DECLINED_FICT_RESERVED },
	{ "Yarna D'al Gargan", DECLINED_FICT_RESERVED },
	{ "Yoda", DECLINED_FICT_RESERVED },
	{ "Yoxgit", DECLINED_FICT_RESERVED },
	{ "Ysanne Isard", DECLINED_FICT_RESERVED },
	{ "Zaalbar", DECLINED_FICT_RESERVED },
	{ "Zam Wesell", DECLINED_FICT_RESERVED },
	{ "Zett Jukassa", DECLINED_FICT_RESERVED },
	{ "Zev Senesca", DECLINED_FICT_RESERVED },
	{ "Zuckuss", DECLINED_FICT_RESERVED },
	{ "kryat", DECLINED_RESERVED },
	{ "human", DECLINED_RESERVED },
	{ "twi'lek", DECLINED_RESERVED },
	{ "moncalamari", DECLINED_RESERVED },
	{ "wookiee", DECLINED_RESERVED },
	{ "zabrak", DECLINED_RESERVED },
	{ "bothan", DECLINED_RESERVED },
	{ "rodian", DECLINED_RESERVED },
	{ "trandoshan", DECLINED_RESERVED },
	{ "bank", DECLINED_RESERVED },
	{ "city", DECLINED_RESERVED },
	{ "guild", DECLINED_RESERVED },
	{ "tip", DECLINED_RESERVED },
	{ "citizens", DECLINED_RESERVED },
	{ "self", DECLINED_RESERVED }
}