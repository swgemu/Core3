DROP TABLE IF EXISTS `swgemu`.`consentlist`;
CREATE TABLE  `swgemu`.`consentlist` (
  `character_id` mediumint(8) unsigned NOT NULL default '0',
  `targets` text,
  PRIMARY KEY  USING BTREE (`character_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;