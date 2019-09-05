#!/bin/bash
python img_grabber.py & P1=$!
echo $P1
python img_grabber.py & P2=$!
echo $P2
python img_grabber.py
#wait
kill -9 $P1 $P2
