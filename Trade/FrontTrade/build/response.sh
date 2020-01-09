#! /bin/bash
StartTime=$[$(date +%s%N)/1000000]
ab -c 100 -n 10000 -p ./response.txt -T application/json -H "token:2131231231" http://192.168.1.20:9000/api/private/Uptrad
EndTime=$[$(date +%s%N)/1000000]
elapsed=$[$EndTime-$StartTime]
echo "scale=3; $elapsed/1000"|bc