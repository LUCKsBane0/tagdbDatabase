#!/bin/bash
cd "$$(dirname "$0")"
path=$(/bin/pwd)
temp="export PATH=${path}"
echo "$temp">>~/.bashrc
echo "alias tagdb= 'tagdb'" >> ~/.bashrc