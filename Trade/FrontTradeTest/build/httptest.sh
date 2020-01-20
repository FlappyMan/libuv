#! /bin/bash
StartTime=$[$(date +%s%N)/1000000]
ab -c 100 -n 20000 -p ./postUptrade.txt -T application/json -H "token:2131231231" -k http://192.168.1.20:9000/api/private/Uptrade
ab -c 100 -n 20000 -p ./postUptradeBacth.txt -T application/json -H "token:sdasdasdasd" -k http://192.168.1.20:9000/api/private/UptradeBatch
ab -c 100 -n 20000 -p ./postCancelTrade.txt -T application/json -H "token:jktytyter" -k http://192.168.1.20:9000/api/private/CancelTrade
ab -c 100 -n 20000 -p ./postCancelTradeBacth.txt -T application/json -H "token:hfghfghjf" -k http://192.168.1.20:9000/api/private/CancelTradeBatch
EndTime=$[$(date +%s%N)/1000000]
elapsed=$[$EndTime-$StartTime]
echo "scale=3; $elapsed/1000"|bc