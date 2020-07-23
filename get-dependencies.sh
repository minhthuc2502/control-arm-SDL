#!/bin/bash -eu
# sudo 
if [ $(id -u) != "0" ]; then
echo "You must be the superuser to run this script" >&2
exit 1
fi
# Install dependencies
echo "Verifing library installed..."
listDependencies=(cmake libevdev-dev libsdl2-dev libboost-dev libboost-test-dev libmicrohttpd-dev)
for dependencie in "${listDependencies[@]}"
do
    echo "Ugrade ..."
    apt upgrade
    if [[ $(dpkg ${dependencie} &> /dev/null) -ne 0 ]]; then
        echo "Downloading ${dependencie}..."
        apt-get -y install ${dependencie}
    else
        echo "${dependencie} is installed!"
    fi
done
echo "Verifing library installed done"