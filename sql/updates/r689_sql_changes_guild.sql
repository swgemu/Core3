ALTER TABLE `characters` ADD `guildpermission` TINYINT(3) UNSIGNED DEFAULT '0' NOT NULL AFTER `adminLevel`;

CREATE TABLE `guilds_sponsoring` (
  `guild_id` int(11) unsigned NOT NULL,
  `guild_name` varchar(255) NOT NULL default 'Default Guild',
  `sponsored_time` varchar(10) default NULL,
  `sponsored_by` bigint(11) unsigned default NULL,
  `sponsored` bigint(11) unsigned default NULL,
  `pix` bigint(11) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`pix`),
  KEY `sponsored_ix` (`sponsored`),
  KEY `sponsor_ix` (`sponsored_by`),
  KEY `guild_ix` (`guild_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `guilds`;

CREATE TABLE `guilds` (
  `guild_id` int(11) unsigned NOT NULL auto_increment,
  `guild_tag` varchar(255) NOT NULL default 'DEFAULT',
  `guild_name` varchar(255) NOT NULL default 'Default Guild',
  `members` int(4) unsigned zerofill NOT NULL default '0000',
  `created` varchar(10) default NULL,
  `leader` bigint(11) default NULL,
  `last_name_change` varchar(10) default NULL,
  PRIMARY KEY  (`guild_id`),
  KEY `guildID_ix` (`guild_id`),
  KEY `guidleader_ix` (`leader`),
  KEY `guildTag_ix` (`guild_tag`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;


INSERT INTO `guilds` VALUES ('0', 'DEFAULT', 'Default Guild', '0000', null, '0', null);
INSERT INTO `guilds` VALUES ('1', 'SWGEMU', 'SWGEmu Test Guild', '0000', null, '0', null);
INSERT INTO `guilds` VALUES ('2', 'DEV', 'Developers', '0000', null, '0', null);
