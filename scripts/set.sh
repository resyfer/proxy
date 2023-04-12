#!/bin/bash

# comma separated array as first argument
# extra=(${1//,/ }) # Can't use this as dash in Ubuntu doesn't support it
EXTRA_STR="$1"

HOST=$2
PORT=$3
DE=$4 # Desktop Environment
COLLEGE=$5

PROXY_STR=http://$HOST:$PORT

# Reading Extras
IFS=","
for item in $EXTRA_STR; do

  if [ "$item" = "git" ]; then

    git config --global http.proxy $PROXY_STR
    git config --global https.proxy $PROXY_STR

  elif [ "$item" = "npm" ]; then

    npm config --global set proxy $PROXY_STR
    npm config --global set https-proxy $PROXY_STR

  fi

done
IFS=" "

# Desktop specific commands
if [ "$DE" = "GNOME" ]; then
  gsettings set org.gnome.system.proxy mode 'manual'
  gsettings set org.gnome.system.proxy ignore-hosts "['localhost', '127.0.0.0/8', '::1', '*.local']"
  gsettings set org.gnome.system.proxy.http host "${HOST}"
  gsettings set org.gnome.system.proxy.http port "${PORT}"
  gsettings set org.gnome.system.proxy.https host "${HOST}"
  gsettings set org.gnome.system.proxy.https port "${PORT}"
fi