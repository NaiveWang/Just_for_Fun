#!/bin/bash
echo "this script will remove all of the python things, SUPERUSER is needed."
sudo su

rm -rf /usr/bin/python2.x as well as python3.x
rm -rf /usr/lib/python2.x as well as python3.x
rm -rf /usr/local/lib/python2.x as well as python 3.x
apt-get update
