DROP TABLE `bazaar_items`

CREATE TABLE `bazaar_items` (
  `objectid` bigint(20) unsigned NOT NULL,
  `description` varchar(45) NOT NULL,
  `item_type` int(10) unsigned NOT NULL,
  `ownerid` bigint(20) unsigned NOT NULL,
  `ownername` varchar(45) NOT NULL,
  `price` int(10) unsigned NOT NULL,
  `auction` tinyint(1) NOT NULL,
  `sold` tinyint(1) NOT NULL default '0',
  `expire` bigint(20) unsigned NOT NULL,
  `terminalid` bigint(20) unsigned NOT NULL,
  `planet` smallint(5) unsigned NOT NULL,
  `buyerid` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`objectid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
