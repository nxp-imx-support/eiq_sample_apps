#!/bin/sh
# Copyright (c) 2019 NXP Semiconductors
# Author: Vanessa Maegima
# SPDX-License-Identifier:	MIT
LOG=log.txt

for i in 0 1 2
do
    if [ -z "$(cat $LOG | grep -w "Prediction for test case ${i}")" ]
    then
        continue
    else
        echo $(cat $LOG | grep -w "Prediction for test case ${i}" | awk -F"[()]" '{print $2}')
        break
    fi
done
