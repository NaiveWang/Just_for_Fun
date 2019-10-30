#!/bin/bash
DATE=$(date +%Y%m%d-%H%M)
cat _douban.db.sql |sqlite3 $DATE.db
rm log.txt
while read ID
do
  read NAME
  read NUM
  echo "id=$ID, name=$NAME, num=$NUM." >> log.txt
  ./full_topic.sh $ID $NUM $NAME $DATE.db
done < seed.txt
