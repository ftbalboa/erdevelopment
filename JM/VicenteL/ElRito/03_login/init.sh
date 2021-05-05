#!/bin/sh
sleep 30
export DISPLAY=":0.0"
su chip -c "python /pi/1.py"