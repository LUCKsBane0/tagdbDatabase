#!/bin/bash
cd "$(dirname "$0")"
path=$(/bin/pwd)
temp="export PATH="$"PATH:${path}"
echo "$temp" >> ~/.bashrc
echo "tagdb_fn(){
       if [ "$"# -eq 0 ]; then
           echo "No arguments provided!"
       fi
       (cd $path
       ./tagdb ""$"*")}" >> ~/.bashrc
echo "alias tagdb='tagdb_fn'" >> ~/.bashrc