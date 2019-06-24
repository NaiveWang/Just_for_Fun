#!/bin/bash
sqlite3 base <<EOF
delete from content;
update post set is_split=0;
vacuum
EOF
S=$(date +%s%N)
./text_cmp
E=$(date +%s%N)
echo "block gen c language : took $[($E - $S)/1000000]ms."
sqlite3 base <<EOF
delete from content;
update post set is_split=0;
vacuum
EOF
S=$(date +%s%N)
java -jar text_cmp.jar 0
E=$(date +%s%N)
echo "block gen java : took $[($E - $S)/1000000]ms."
echo "conclusion : java is bullshit."
