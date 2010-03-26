<?php
 //SETUP
 $DB_ADDRESS = "127.0.0.1";
 $DB_NAME = "swgemu";
 $DB_USER = "swgemu";
 $DB_PASS = "123456"; 

 $DEFAULT_ITEMS_PER_PAGE = 20;
 //

 if (isset($_POST['js']) && $_POST['js'] != "enabled")
  die('Javascript is required!');
 
 $IPP = (isset($_POST['ipp']))? $_POST['ipp'] : $DEFAULT_ITEMS_PER_PAGE;
 $con = @mysql_connect($DB_ADDRESS,$DB_USER,$DB_PASS) or die('Could not connect: ' . mysql_error());
 mysql_select_db($DB_NAME, $con);

 if ($_POST['command'] == "Commit") {
  for ($i = 1; $i <= $_POST['numItems']; $i++) {
   $value = "item_" . $i . "_value";
   $id = "item_" . $i . "_id";
   $query = "UPDATE loottable SET itemMask = $_POST[$value] WHERE pix = $_POST[$id];";
   mysql_query($query) or die(mysql_error() . $query);
  }
 }

 $result = mysql_query("SELECT COUNT(*) FROM loottable") or die(mysql_error());
 $row = mysql_fetch_array($result);
 $numTotalItems = $row[0];
 $numPages = (is_int($numTotalItems / $IPP)) ? $numTotalItems / $IPP : floor($numTotalItems / $IPP) + 1;
 $pageNum = (isset($_POST['pageNum'])) ? $_POST['pageNum'] : 1; 
 	
 if($_POST['command'] == "<<")
  $pageNum = 1;
 else if ($_POST['command'] == "<")
  --$pageNum;
 else if ($_POST['command'] == ">")
  ++$pageNum;
 else if ($_POST['command'] == ">>")
  $pageNum = $numPages;

 if ($pageNum < 1 || $pageNum > $numPages)
  $pageNum = 1;
 
 $itemStart = ($pageNum - 1) * $IPP;

 $query = "SELECT pix,name,itemMask FROM loottable LIMIT " . $itemStart . "," . $IPP;
 $result = mysql_query($query) or die(mysql_error() . $query);
 $numItems = mysql_num_rows($result);

 $alt = 1;
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" >
<head>
<title>SWGemu Loot Table Permission Tool</title>

<script type="text/javascript">

var MALE = 0x01;
var FEMALE = 0x02;
var HUMAN = 0x004;
var TRANDOSHAN = 0x008;
var TWILEK = 0x010;
var BOTHAN = 0x020;
var ZABRAK = 0x040;
var RODIAN = 0x080;
var MONCALAMARI = 0x100;
var WOOKIEE = 0x200;
var SULLUSTAN = 0x400;
var ITHORIAN = 0x800;
var NEUTRAL = 0x1000;
var IMPERIAL = 0x2000;
var REBEL = 0x4000;
var COVERT = 0x8000;

function setStats(name, value) {
 if (value == -1)
   return;

 setCheckBox(name + "_cov", value, COVERT);
 setCheckBox(name + "_imp", value, IMPERIAL);
 setCheckBox(name + "_reb", value, REBEL);
 setCheckBox(name + "_neu", value, NEUTRAL);
 setCheckBox(name + "_hum", value, HUMAN);
 setCheckBox(name + "_tra", value, TRANDOSHAN);
 setCheckBox(name + "_twi", value, TWILEK);
 setCheckBox(name + "_bot", value, BOTHAN);
 setCheckBox(name + "_zab", value, ZABRAK);
 setCheckBox(name + "_rod", value, RODIAN);
 setCheckBox(name + "_mon", value, MONCALAMARI);
 setCheckBox(name + "_woo", value, WOOKIEE);
 setCheckBox(name + "_sul", value, SULLUSTAN);
 setCheckBox(name + "_ith", value, ITHORIAN);
 setCheckBox(name + "_mal", value, MALE);
 setCheckBox(name + "_fem", value, FEMALE);

 setValue(name);
}

function setCheckBox(name, value, mask) {
 if (value & mask)
  document.getElementById(name).checked = true;
 else
  document.getElementById(name).checked = false;
}

function calculateMask(name) {
 var mask = 0;

 mask += (document.getElementById((name + "_cov")).checked) ? COVERT : 0;
 mask += (document.getElementById((name + "_imp")).checked) ? IMPERIAL : 0;
 mask += (document.getElementById((name + "_reb")).checked) ? REBEL : 0;
 mask += (document.getElementById((name + "_neu")).checked) ? NEUTRAL : 0;
 mask += (document.getElementById((name + "_hum")).checked) ? HUMAN : 0;
 mask += (document.getElementById((name + "_twi")).checked) ? TWILEK : 0;
 mask += (document.getElementById((name + "_bot")).checked) ? BOTHAN : 0;
 mask += (document.getElementById((name + "_zab")).checked) ? ZABRAK : 0;
 mask += (document.getElementById((name + "_rod")).checked) ? RODIAN : 0;
 mask += (document.getElementById((name + "_mon")).checked) ? MONCALAMARI : 0;
 mask += (document.getElementById((name + "_woo")).checked) ? WOOKIEE : 0;
 mask += (document.getElementById((name + "_sul")).checked) ? SULLUSTAN : 0;
 mask += (document.getElementById((name + "_ith")).checked) ? ITHORIAN : 0;
 mask += (document.getElementById((name + "_tra")).checked) ? TRANDOSHAN : 0;
 mask += (document.getElementById((name + "_mal")).checked) ? MALE : 0;
 mask += (document.getElementById((name + "_fem")).checked) ? FEMALE : 0;

 return mask;
}

function init() {
 var num = document.getElementById("numItems").value;

 for (var i = 1; i <= num; i++) {
  setStats(("item_" + i), document.getElementById(("item_" + i + "_value")).value);
 }

 document.getElementById("js").value = "enabled";
}

function setValue(name) {
 document.getElementById((name + "_value")).value = calculateMask(name);
}
</script>

<style>
table
{ 
 text-align: center;
 margin:auto;
 border-width: 1;
 font-size: 10px;
 background-color: #999;
 color: #111;
}

input,select {
 font-size: 10px !important;
 text-align: center;
 color: #111;
}



.presets select {
 width: 100%;
}

.ippForm {
 text-align: left;
}

input[type=text] {
 width: 30px;
}

.a0 {
 background-color: #EEE;
}

.a1 {
 background-color: #AAA;
}

body {
 background-color: #CCC;
 text-align:center;
}

</style>
</head>

<body onload="init()">
<h2>SWGemu Loot Table Permission Tool</h2>
<h3>by Bobius</h3>
<form method="post">
<input type="hidden" id="numItems" name="numItems" value="<? echo $numItems; ?>" />
<input type="hidden" id="js" name="js" value="disabled" />
<input type="submit" style="visibility:hidden; width:1px; height:1px" />
<table>
<tr>
 <td class="a1">Name</td>
 <td colspan="4" class="a1">Faction</td>
 <td colspan="10" class="a1">Species</td>
 <td colspan="2" class="a1">Sex</td>
 <td class="pages">
  <input type="submit" name="command" value="<<" />
  <input type="submit" name="command" value="<" />
  <input type="text" name="pageNum" value="<? echo $pageNum; ?>" /> / <? echo $numPages; ?>
  <input type="submit" name="command" value=">" />
  <input type="submit" name="command" value=">>" /> 
 </td>
</tr>
<tr class="a1">
 <td></td>
 <td>Covert</td>
 <td>Imperial</td>
 <td>Rebel</td>
 <td>Neutral</td>
 <td>Human</td>
 <td>Trandoshan</td>
 <td>Twilek</td>
 <td>Bothan</td>
 <td>Zabrak</td>
 <td>Rodian</td>
 <td>Moncalamari</td>
 <td>Wookiee</td>
 <td>Sullustan</td>
 <td>Ithorian</td>
 <td>Male</td>
 <td>Female</td>
 <td></td>
</tr>
<?php
 $i = 0;
 while ($row = mysql_fetch_array($result)) {
 $i++;
?>
<tr class="a<? echo ++$alt % 2;?>">
 <td><? echo $row['name']; ?></td>
 <td><input id="item_<? echo $i; ?>_cov" name="item_<? echo $i; ?>_cov" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_imp" name="item_<? echo $i; ?>_imp" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_reb" name="item_<? echo $i; ?>_reb" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_neu" name="item_<? echo $i; ?>_neu" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_hum" name="item_<? echo $i; ?>_hum" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_tra" name="item_<? echo $i; ?>_tra" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_twi" name="item_<? echo $i; ?>_twi" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_bot" name="item_<? echo $i; ?>_bot" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_zab" name="item_<? echo $i; ?>_zab" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_rod" name="item_<? echo $i; ?>_rod" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_mon" name="item_<? echo $i; ?>_mon" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_woo" name="item_<? echo $i; ?>_woo" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_sul" name="item_<? echo $i; ?>_sul" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_ith" name="item_<? echo $i; ?>_ith" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_mal" name="item_<? echo $i; ?>_mal" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 <td><input id="item_<? echo $i; ?>_fem" name="item_<? echo $i; ?>_fem" type="checkbox" onChange="setValue('item_<? echo $i; ?>')" /></td>
 
 <td class="presets">
  <select onChange="setStats('item_<? echo $i; ?>', this.options[this.selectedIndex].value);" >
   <option value="-1" selected>Preset Templates</option>
   <option value="-1">-------------------------</option>
   <option value="65535">All</option>
   <option value="0">None</option>
   <option value="62975">Humanoids</option>
   <option value="62973">Humanoid Males</option>
   <option value="62974">Humanoid Females</option>
   <option value="62967">Humanoid Footwear</option>
   <option value="17919">Rebel Humanoids</option>
   <option value="9727">Imperial Humanoids</option>
   <option value="61955">Wookies</option>
   <option value="63491">Ithorians</option>
  </select>
 <!-- The below is for adding new presets -->
  <!-- <input type="submit" value="Get Mask" onclick="alert(document.getElementById('item_<? echo $i; ?>_value').value);"/> -->
 <!-- End -->
 </td>
 <input type="hidden" id="item_<? echo $i; ?>_value" name="item_<? echo $i; ?>_value" value="<? echo $row['itemMask']; ?>" />
 <input type="hidden" name="item_<? echo $i; ?>_id" value="<? echo $row['pix']; ?>" />
</tr>
<?
 }
?>
<tr>
 <td colspan="17" class="ippForm">
  <input type="text" name="ipp" value="<? echo $IPP; ?>"/>
  Items / Page
  <input type="submit" name="command" value="Refresh" />
</td>
<td><input type="submit" name="command" value="Commit"/></td>
</tr>
</form>
</table>
</body>
</html>
