#!/bin/bash
echo export cd "$(dirname "$0")"
/bin/pwd >> ~/.bashrc
echo "alias tagdb= 'tagdb'" >> ~/.bashrc