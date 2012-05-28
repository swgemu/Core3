USE swgemu;
DROP TABLE IF EXISTS `characters_dirty`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters_dirty` (
  `character_oid` bigint(20) NOT NULL,
  `account_id` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `galaxy_id` int(5) unsigned NOT NULL DEFAULT '0',
  `firstname` varchar(15) NOT NULL DEFAULT '',
  `surname` varchar(20) DEFAULT NULL,
  `race` tinyint(2) NOT NULL DEFAULT '0',
  `gender` tinyint(1) NOT NULL DEFAULT '0',
  `template` tinytext NOT NULL,
  PRIMARY KEY (`character_oid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;
