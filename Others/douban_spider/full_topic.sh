#!/bin/bash
echo "grabbing topic $3 with id $1, which assumed to have $2 topics";
echo "purging environment";
PY=python;
DB=$4;
SQLITE=sqlite3;


rm $1.json
rm -rf raw
mkdir raw
echo "grabbing raw json slice data";
$PY bloody_hack.py $1 $2;
echo "merging and extracting posts into one json file";
$PY extractor.py $1;
echo "add this topic to local db"
echo "insert into topic(id, title)values('$1', '$3');"|$SQLITE $DB
echo "importing location and user data into local database"
$PY import_user.py $1 $DB 2>>log.txt
echo "importing posts, image links and comments into local database"
$PY import_post.py $1 $DB 2>>log.txt
