#!/bin/bash

nohup ./test.sh float O3 1 >> "gdb.log_OfRun_${i}" 2>&1 &
