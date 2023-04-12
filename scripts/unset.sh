#!/bin/bash

# comma separated array as first argument
# extra=(${1//,/ }) # Can't use this as dash in Ubuntu doesn't support it
EXTRA_STR="$1"

DE=$2

# Reading Extras
IFS=","
for item in $EXTRA_STR; do

  if [ "$item" = "git" ]; then

    git config --global --unset http.proxy
    git config --global --unset https.proxy

  elif [ "$item" = "npm" ]; then

    npm config --global set proxy $PROXY_STR
    npm config --global set https-proxy $PROXY_STR

  fi

done
IFS=" "

if [ "$DE" = "GNOME" ]; then
  gsettings set org.gnome.system.proxy mode 'none'
fi