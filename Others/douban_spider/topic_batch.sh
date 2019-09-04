#!/bin/bash
rm log.txt;
while read ID;
do
  read NAME;
  read NUM;
  echo "id=$ID, name=$NAME, num=$NUM." >> log.txt;
  ./full_topic.sh $ID $NUM $NAME;
done < seed.txt
