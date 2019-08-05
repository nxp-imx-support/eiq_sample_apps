#!/bin/sh
# Copyright (c) 2019 NXP Semiconductors
# Author: Vanessa Maegima
# SPDX-License-Identifier:	MIT
LOG=/home/root/ArmnnTests/log.txt

ID=$(cat $LOG | grep "prediction" | sed 's/[)(]//g')
ID=$(echo $ID | awk '{print $4}')
[ -z $ID ] && echo error || echo $ID
