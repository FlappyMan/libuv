#! /bin/bash
StartTime=$[$(date +%s%N)/1000000]
ab -c 1000 -n 10000 -p ./postUptrade.txt -T application/json -H "token:2131231231" http://192.168.1.20:9000/api/private/Uptrade
ab -c 1000 -n 10000 -p ./postUptradeBacth.txt -T application/json -H "token:sdasdasdasd" http://192.168.1.20:9000/api/private/UptradeBatch
ab -c 1000 -n 10000 -p ./postCancelTrade.txt -T application/json -H "token:jktytyter" http://192.168.1.20:9000/api/private/CancelTrade
ab -c 1000 -n 10000 -p ./postCancelTradeBacth.txt -T application/json -H "token:hfghfghjf" http://192.168.1.20:9000/api/private/CancelTradeBatch
EndTime=$[$(date +%s%N)/1000000]
elapsed=$[$EndTime-$StartTime]
echo "scale=3; $elapsed/1000"|bc