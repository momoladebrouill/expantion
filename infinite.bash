#!/usr/bin/env sh


gcc main.c -o animation.out
./animation.out
while true
do
    read -p "Continue ?" choix
    case "$choix" in
        n|N) break;;
        y|Y|"") ./animation.out;;
        *) echo "Invalid response: $choix";;
    esac
done
rm animation.out
