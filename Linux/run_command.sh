#!/bin/bash

command='go run program_demo.go;read -n 1'

setsid gnome-terminal -e "bash -c \"$command\""
