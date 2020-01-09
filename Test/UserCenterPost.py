import requests,json
 
if __name__ == '__main__':
    url_json = 'http://192.168.1.20:9999'
    data_json = json.dumps({'wuyoupeng':'test data'})
    r_json = requests.post(url_json,data_json)
    print(r_json)
