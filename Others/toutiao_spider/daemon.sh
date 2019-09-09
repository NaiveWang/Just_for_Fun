#!/bin/bash
while true
do
  python list_chain_amp.py
  python grab_post.py &
  sleep 1800
done
