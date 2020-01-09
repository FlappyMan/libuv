#! /bin/bash
StartTime=$[$(date +%s%N)/1000000]
ab -c 10 -n 100000 -p ./postUptrade.txt -T application/json -H "token:2131231231" http://192.168.1.20:9000/api/private/Uptrad
ab -c 10 -n 100000 -p ./postUptradeBacth.txt -H "token:sdasdasdasd" http://192.168.1.20:9000/api/private/UptradeBatc
ab -c 10 -n 100000 -p ./postCancelTrade.txt -H "token:jktytyter" http://192.168.1.20:9000/api/private/CancelTrad
ab -c 10 -n 100000 -p ./postCancelTradeBacth.txt -H "token:hfghfghjf" http://192.168.1.20:9000/api/private/CancelTradeBatc
EndTime=$[$(date +%s%N)/1000000]
elapsed=$[$EndTime-$StartTime]
echo "scale=3; $elapsed/1000"|bc