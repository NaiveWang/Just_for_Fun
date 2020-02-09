#!/bin/bash
DATESTAMP=$( date +%Y%m%d%H%M )
echo "creating database $DATESTAMP.db"

sqlite3 $DATESTAMP.db < _douban.db.sql

echo "purging temp log and json files"

rm log.txt &&
rm *.json &&

while read ID
do
  read NAME &&
  read NUM &&
  echo "id=$ID, name=$NAME, num=$NUM." >> log.txt &&
  ./full_topic.sh $ID $NUM $NAME $DATESTAMP.db
done < seed.txt
