#!/bin/bash
python avatar_grabber.py & P1=$!
echo $P1
python avatar_grabber.py & P2=$!
echo $P2
python avatar_grabber.py & P3=$!
echo $P3
python avatar_grabber.py
#wait
kill -9 $P1 $P2 $P3
