#!/usr/bin/env python
#!-*-coding:utf-8 -*-
#!@Author:FriendWu
import datetime
import json
import re
import sys
import time
import uuid

import pymysql
from config import Config
import MySQLdb.cursors
from database import Database


class DBOperation(object):
    user_account_list = []
    def __init__(self):
        self.user_list = ['id','user_account','password','source_type','login_attempts','login_time','create_time','update_time']
        self.user_account_list = ['account', 'account_type','source_type', 'user_id','ukex_uid','ukexpay_uid', 'create_time', 'update_time']
        self.user_auth = ['user_id','is_allow_login','paypassword_status','user_status','auth_status','kyc_auth','email_auth','allow_openapi_withdrawal','is_reauth','is_pass_aml',
                          'register_type','verify_type','global_kyc_status','last_operate_time','account_status','os_verify','pin_verify','two_factor','hide_balance','create_time','update_time']
        self.user_facts = ['user_id','first_name','last_name','birthday','country','residence_country','province','city','town','district','street_address','building_number','building_name','sex','zip_code','apartment',
                           'first_residence_certificate','second_residence_certificate','street_code','unit','house_code','passport','passport_ocr','passport_expire','passport_picture','passport_picture_hold','driving_number',
                           'driving_picture','driving_picture_hold','is_europe','nationality','create_time','has_deducted_gbp','has_deducted_eur','has_deducted_usd','update_time']
        self.user_info = ['user_id','mobile','id_type','identity_number','identity_expiry_date','identity_info','paypassword','recommender_level1','recommender_level2','recommender_level3','realname','country',
                          'c2c_info_ext','ext','invit_time','source_of_funds','mobile_binding_time','id_number','ip_address',
                          'address_desc','email','wechat','wechat_img','wechat_openid','alipay','alipay_img','invite_code','custom_cate_id','master_account','source_proj_uid','uuid','uuid_salt','user_image','country_code',
                          'user_type','account_active_time','secret_key','refer_currency',
                          'kyc_refuse_num','lucky_count','c2c_refuse_num','rescue_code','create_time','update_time']
        self.user_assets = ['id','user_id','source_type','usable','freeze','lock_up','status','create_time','update_time']
        self.user_assets_coinID = ['1','72','79','82','83','84','88','89','91','92','93','94','95','96','97','98','99','100','101','102','103','104','105','106','107','108','109','110','111','112','113','114','115','119',
                                   '35','37','38','39']

        # --------------------------------------------------以下是BackTrade数据库表变量部分------------------------------------------
        self.recommended_trade_award = ['id','user_id','recommender_id','market_id','oper_type','coin_id','trading_volume','trading_amount','profit','create_time','update_time']
        self.coin_kline_minimum = ['id','market_id','begin_time','open','high','low','close','trading_volume','create_time','update_time']
        self.kline_record = ['id','market_id','Kline_type','begin_time','open','high','low','close','trading_volume','create_time','update_time']
        self.financial_records = ['id','user_id','coin_id','gross_amount','gross_frozen','gross_sum','fee','fee_frozen','oper_type','oper_id','oper_desc','remaining_amount','remaining_frozen','remaining_sum','record_hash','status','create_time','update_time']
        self.wait_close = ['id', 'user_id', 'market_id', 'price', 'trading_volume', 'traded_volume', 'trading_amount','estimated_fee', 'actual_fee', 'oper_type', 'status', 'endtime','create_time', 'update_time']
    def getColValueType(self,list):
        retStr = ''
        arraySize = len(list)
        for iLoop in range(arraySize):
            retStr += '%s,'
        return retStr[:-1]
    def getColumns(self,list):
        retStr = ''
        for key in list:
            if key == 'condition' or key == 'group' or key == 'change':
                retStr += '`' + key + '`,'
            else:
                retStr += key + ','
        return retStr[:-1]
    def getColValue(self,Obj,list):
        retStr = ''
        for key in list:
            if key in Obj.keys():
                if Obj[key] == None:
                    retStr += 'null,'
                else:
                    retStr += '"' + MySQLdb.escape_string(str(Obj[key])) + '",'
        return retStr[:-1]
    def makeInsertPackage(self,Obj,colList,tableName):
        columns = self.getColumns(colList)  # 获取需要处理的所有字段
        tableValues = self.getColValue(Obj,colList)
        tableColumns = tableName + '(' + columns + ') values(' + tableValues + ');'
        return tableColumns
    def insertToDB(self,tableName,insertObjList,list):
        for Obj in insertObjList:
            tableColumns = self.makeInsertPackage(Obj,list,tableName)
            # 最后添加transfer字段，表示新数据都没有被转换过
            database.inserSQL(database.accountDB_cursor,tableColumns)
    def insertToAssets(self,tableName,insertObjList,list):
        for Obj in insertObjList:
            tableColumns = self.makeInsertPackage(Obj,list,tableName)
            # 最后添加transfer字段，表示新数据都没有被转换过
            database.inserSQL(database.assetsDB_cursor,tableColumns)
    def insertToSA(self,tableName,insertObjList,list):
        for Obj in insertObjList:
            tableColumns = self.makeInsertPackage(Obj,list,tableName)
            # 最后添加transfer字段，表示新数据都没有被转换过
            database.inserSQL(database.SADB_cursor,tableColumns)

    def insertToTrade(self,tableName,insertObjList,list):
        for Obj in insertObjList:
            tableColumns = self.makeInsertPackage(Obj,list,tableName)
            # 最后添加transfer字段，表示新数据都没有被转换过
            database.inserSQL(database.tradeDB_cursor,tableColumns)

    def loadTableUserData(self):
        print ('--------------------导入创建user表---------------------------')
        # ukex - new 用户名登录的用户
        insertList = database.selectSQL(database.ukex_cursor,
                                        'last_insert_id() as id, username as user_account ,password, 1 as source_type, logins as login_attempts, login_time , addtime as create_time , addtime as update_time',
                                        'coin_user where username !="";')
        dbOper.insertToDB('user', insertList, dbOper.user_list)

        # ukex - new 手机号登录的用户
        insertList = database.selectSQL(database.ukex_cursor,
                                        'last_insert_id() as id, moble as user_account ,password, 1 as source_type, logins as login_attempts, login_time , addtime as create_time , addtime as update_time',
                                        'coin_user where moble !="";')
        dbOper.insertToDB('user', insertList, dbOper.user_list)

        # ukex - new 邮箱登录的用户
        insertList = database.selectSQL(database.ukex_cursor,
                                        'last_insert_id() as id, email as user_account ,password, 1 as source_type, logins as login_attempts, login_time , addtime as create_time , addtime as update_time',
                                        'coin_user where email !="";')
        dbOper.insertToDB('user', insertList, dbOper.user_list)

        # ukexpay - new 邮箱登录的用户
        insertList = database.selectSQL(database.ukexpay_cursor,
                                        'last_insert_id() as id, email as user_account ,password, 2 as source_type, 0 as login_attempts, 0 as login_time , create_time as create_time , update_time as update_time',
                                        'cnuk_user_main where email !="";')
        dbOper.insertToDB('user', insertList, dbOper.user_list)
        print ('------------------------------------------------------------')

    def loadTableUserAccountData(self):
        print ('--------------------导入表user_account---------------------------')
        # 将ukexpay的用户账号数据导入到new库中
        insertList = []
        for ukexpay in ukexpayList:
            dic = {}
            searchList = database.selectSQL(database.accountDB_cursor, 'user_id','user_account where account = "' + ukexpay['user_account'] + '";')
            assert (len(searchList) <= 1)
            if len(searchList) == 0:
                dic['account'] = ukexpay['user_account']
                dic['account_type'] = '1'
                dic['source_type'] = '2'
                dic['user_id'] = ukexpay['user_id']
                dic['ukex_uid'] = '0'
                resultList = database.selectSQL(database.ukexpay_cursor, 'uid as user_id',
                                          'cnuk_user_main where email = "' + ukexpay['user_account'] + '";')
                dic['ukexpay_uid'] = resultList[0]['user_id']
                dic['create_time'] = ukexpay['create_time']
                dic['update_time'] = ukexpay['update_time']
                insertList.append(dic)
            else:
                resultList = database.selectSQL(database.ukexpay_cursor, 'uid as user_id','cnuk_user_main where email = "' + ukexpay['user_account'] + '";')
                assert (len(searchList) != 0)
                database.update(database.accountDB_cursor,'user_account set ukexpay_uid = "'+ str(resultList[0]['user_id']) +'" where account = "' + ukexpay['user_account'] + '";')
        dbOper.insertToDB('user_account', insertList, dbOper.user_account_list)
        print ('-----------------------ukexpay导入完成------------------------')

        insertList = []
        for ukex in ukexList:
            dic = {}
            searchList = database.selectSQL(database.accountDB_cursor, 'user_id','user_account where account = "' + ukex['user_account'] + '";')
            assert (len(searchList) <= 1)
            if len(searchList) == 0:
                resultList = database.selectSQL(database.ukex_cursor,"id as user_id",'coin_user where moble = "'+ ukex['user_account'] +'";')
                if len(resultList) == 0:
                    resultList = database.selectSQL(database.ukex_cursor, "id as user_id", 'coin_user where username = "' + ukex['user_account'] + '";')
                    if len(resultList) == 0:
                        resultList = database.selectSQL(database.ukex_cursor, "id as user_id",'coin_user where email = "' + ukex['user_account'] + '";')
                        assert (len(resultList) != 0)
                        dic['account_type'] = 1
                    else:
                        dic['account_type'] = 2
                else:
                    dic['account_type'] = 0

                dic['ukexpay_uid'] = '0'
                dic['source_type'] = '1'
                dic['ukex_uid'] = resultList[0]['user_id']
                dic['user_id'] = ukex['user_id']
                for dicObj in insertList:
                    if str(dicObj['ukex_uid']) == str(dic['ukex_uid']):
                        dic['user_id'] = dicObj['user_id']
                
                dic['account'] = ukex['user_account']
                dic['create_time'] = ukex['create_time']
                dic['update_time'] = ukex['update_time']
                insertList.append(dic)
            else:
                resultList = database.selectSQL(database.ukex_cursor, "id as user_id",'coin_user where email = "' + ukex['user_account'] + '";')
                if len(resultList) == 0:
                    resultList = database.selectSQL(database.ukex_cursor, "id as user_id",'coin_user where username = "' + ukex['user_account'] + '";')
                    if len(resultList) == 0:
                        resultList = database.selectSQL(database.ukex_cursor, "id as user_id",'coin_user where moble = "' + ukex['user_account'] + '";')
                        assert (len(resultList) != 0)
                for dicObj in insertList:
                    if str(dicObj['ukex_uid']) == str(resultList[0]['user_id']):
                        print(dicObj)
                        print(str(resultList[0]['user_id']))
                        comboxList = list(database.selectSQL(database.accountDB_cursor, 'user_id,ukexpay_uid','user_account where account = "' + ukex['user_account'] + '";'))
                        
                        assert(len(comboxList) <= 1)
                        dicObj['user_id'] = comboxList[0]['user_id']
                        dicObj['ukexpay_uid'] = comboxList[0]['ukexpay_uid']
                database.update(database.accountDB_cursor,'user_account set ukex_uid = "' + str(resultList[0]['user_id']) + '" where account = "' + ukex['user_account'] + '";')
        dbOper.insertToDB('user_account', insertList, dbOper.user_account_list)
        print ('-------------------------------------------------------------')

    def loadTableUserAuthData(self):
        print ('--------------------导入表user_auth---------------------------')
        insertList = []
        for object in mappingList:
            insertObj = {}
            insertObj['user_id'] = object['user_id']

            searchUkexList = []
            searchUkexpayList = []
            if object['ukex_uid'] != 0:
                searchUkexList = database.selectSQL(database.ukex_cursor, "is_allow_login as is_allow_login, "
                                                                      "tpwdsetting as paypassword_status, "
                                                                      "status as user_status, "
                                                                      "isauth as auth_status, "
                                                                      "kycauth as kyc_auth, "
                                                                      "is_email as email_auth, "
                                                                      "allow_api_withdrawal as allow_openapi_withdrawal, is_reauth, is_pass_aml, "
                                                                      "register_by as register_type, verify_type, global_kyc_status, last_operate_time, "
                                                                      "addtime as create_time, addtime as update_time",'coin_user where id = "' + str(object['ukex_uid']) + '";')
            if object['ukexpay_uid'] != 0:
                searchUkexpayList = database.selectSQL(database.ukexpay_cursor, "c2c_status as auth_status, "
                                                                      "auth_status as kyc_auth, "
                                                                      "status as account_status, os_verify, pin_verify, two_factor, hide_balance, create_time, update_time"
                                               ,'cnuk_user_main where uid = "' + str(object['ukexpay_uid']) + '";')

            assert (len(searchUkexList) == 1 or len(searchUkexpayList) == 1)
            if len(searchUkexList) != 0 and len(searchUkexpayList) != 0:
                assert (len(searchUkexList) == 1 and len(searchUkexpayList) == 1)
                
                ukexObj = searchUkexList[0]
                ukexpayObj = searchUkexpayList[0]
                if ukexObj['is_allow_login'] == 1:
                    insertObj['is_allow_login'] = 1
                else:
                    insertObj['is_allow_login'] = 0
                insertObj['paypassword_status'] = 1
                if ukexObj['user_status'] == 1:
                    insertObj['user_status'] = 1
                else:
                    insertObj['user_status'] = 0
                insertObj['email_auth'] = ukexObj['email_auth']
                insertObj['allow_openapi_withdrawal'] = ukexObj['allow_openapi_withdrawal']
                insertObj['is_reauth'] = ukexObj['is_reauth']
                insertObj['is_pass_aml'] = ukexObj['is_pass_aml']
                insertObj['register_type'] = ukexObj['register_type']
                insertObj['verify_type'] = ukexObj['verify_type']
                insertObj['global_kyc_status'] = ukexObj['global_kyc_status']
                insertObj['last_operate_time'] = ukexObj['last_operate_time']
                insertObj['account_status'] = ukexpayObj['account_status']
                insertObj['os_verify'] = ukexpayObj['os_verify']
                insertObj['pin_verify'] = ukexpayObj['pin_verify']
                insertObj['two_factor'] = ukexpayObj['two_factor']
                insertObj['hide_balance'] = ukexpayObj['hide_balance']
                insertObj['create_time'] = ukexpayObj['create_time']
                insertObj['update_time'] = ukexpayObj['update_time']
                # ukex - 身份验证(一级)。1.已验证 2.审核中 3.未通过 0.未验证
                # ukexpay - c2c认证状态 -2：冻结KYC提交 -1:未通过 0:未认证 1:认证中 2:已通过
                # 身份验证 1-已验证；2-审核中；3-未通过允许重新验证；4-冻结KYC提交；0-未验证
                if ukexObj['auth_status'] == 1 or ukexpayObj['auth_status'] == 2:
                    insertObj['auth_status'] = 1
                elif ukexObj['auth_status'] == 2 or ukexpayObj['auth_status'] == 1:
                    insertObj['auth_status'] = 2
                elif ukexObj['auth_status'] == 3 or ukexpayObj['auth_status'] == -1:
                    insertObj['auth_status'] = 3
                elif ukexpayObj['auth_status'] == -2:
                    insertObj['auth_status'] = 4
                else:
                    insertObj['auth_status'] = 0
                # ukex - 1.已验证 2.审核中 3.未通过 4.未通过允许重新验证 0.未验证
                # ukexpay -2：冻结KYC提交 -1:未通过 0:未认证 1:认证中 2:已通过
                # 身份验证 1-已验证；2-审核中；3-未通过允许重新验证；4-冻结KYC提交；0-未验证 ；5-未通过不允许重新验证
                if ukexObj['kyc_auth'] == 1 or ukexpayObj['kyc_auth'] == 2:
                    insertObj['kyc_auth'] = 1
                elif ukexObj['kyc_auth'] == 4 or ukexpayObj['kyc_auth'] == -1:
                    insertObj['kyc_auth'] = 3
                elif ukexObj['kyc_auth'] == 2 or ukexpayObj['kyc_auth'] == 1:
                    insertObj['kyc_auth'] = 2
                elif ukexpayObj['kyc_auth'] == -2:
                    insertObj['kyc_auth'] = 4
                elif ukexObj['kyc_auth'] == 3:
                    insertObj['kyc_auth'] = 5
                else:
                    insertObj['kyc_auth'] = 0
            elif len(searchUkexList) != 0:
                assert (len(searchUkexList) == 1)
                ukexObj = searchUkexList[0]
                if ukexObj['is_allow_login'] == 1:
                    insertObj['is_allow_login'] = 1
                else:
                    insertObj['is_allow_login'] = 0
                insertObj['paypassword_status'] = 1
                if ukexObj['user_status'] == 1:
                    insertObj['user_status'] = 1
                else:
                    insertObj['user_status'] = 0
                insertObj['email_auth'] = ukexObj['email_auth']
                insertObj['allow_openapi_withdrawal'] = ukexObj['allow_openapi_withdrawal']
                insertObj['is_reauth'] = ukexObj['is_reauth']
                insertObj['is_pass_aml'] = ukexObj['is_pass_aml']
                insertObj['register_type'] = ukexObj['register_type']
                insertObj['verify_type'] = ukexObj['verify_type']
                insertObj['global_kyc_status'] = ukexObj['global_kyc_status']
                insertObj['last_operate_time'] = ukexObj['last_operate_time']
                insertObj['auth_status'] = ukexObj['auth_status']
                if ukexObj['kyc_auth'] == 1:
                    insertObj['kyc_auth'] = 1
                elif ukexObj['kyc_auth'] == 4:
                    insertObj['kyc_auth'] = 3
                elif ukexObj['kyc_auth'] == 2:
                    insertObj['kyc_auth'] = 2
                elif ukexObj['kyc_auth'] == 3:
                    insertObj['kyc_auth'] = 5
                else:
                    insertObj['kyc_auth'] = 0
                insertObj['create_time'] = ukexObj['create_time']
                insertObj['update_time'] = ukexObj['update_time']
                insertObj['account_status'] = 0
                insertObj['os_verify'] = 0
                insertObj['pin_verify'] = 0
                insertObj['two_factor'] = 0
                insertObj['hide_balance'] = 0
            elif len(searchUkexpayList) != 0:
                assert (len(searchUkexpayList) == 1)
                ukexpayObj = searchUkexpayList[0]
                insertObj['is_allow_login'] = 1
                insertObj['paypassword_status'] = 1
                insertObj['user_status'] = 1
                insertObj['email_auth'] = 0
                insertObj['allow_openapi_withdrawal'] = 1
                insertObj['is_reauth'] = 0
                insertObj['is_pass_aml'] = 0
                insertObj['register_type'] = 0
                insertObj['verify_type'] = 0
                insertObj['global_kyc_status'] = 0
                insertObj['last_operate_time'] = 0
                if ukexpayObj['auth_status'] == 2:
                    insertObj['auth_status'] = 1
                elif ukexpayObj['auth_status'] == -1:
                    insertObj['auth_status'] = 3
                elif ukexpayObj['auth_status'] == 1:
                    insertObj['auth_status'] = 2
                elif ukexpayObj['auth_status'] == -2:
                    insertObj['auth_status'] = 4
                else:
                    insertObj['auth_status'] = 0

                if ukexpayObj['kyc_auth'] == 2:
                    insertObj['kyc_auth'] = 1
                elif ukexpayObj['kyc_auth'] == -1:
                    insertObj['kyc_auth'] = 3
                elif ukexpayObj['kyc_auth'] == 1:
                    insertObj['kyc_auth'] = 2
                elif ukexpayObj['kyc_auth'] == -2:
                    insertObj['kyc_auth'] = 4
                else:
                    insertObj['kyc_auth'] = 0

                insertObj['create_time'] = ukexpayObj['create_time']
                insertObj['update_time'] = ukexpayObj['update_time']
                insertObj['account_status'] = ukexpayObj['account_status']
                insertObj['os_verify'] = ukexpayObj['os_verify']
                insertObj['pin_verify'] = ukexpayObj['pin_verify']
                insertObj['two_factor'] = ukexpayObj['two_factor']
                insertObj['hide_balance'] = ukexpayObj['hide_balance']
            else:
                continue
            insertList.append(insertObj)
        dbOper.insertToDB('user_auth', insertList, dbOper.user_auth)
        print ('-------------------------------------------------------------')

    def loadTableUserFactsData(self):
        print ('--------------------导入表user_facts---------------------------')
        icount = 0
        insertList = []
        for object in mappingList:
            insertObj = {}
            insertObj['user_id'] = object['user_id']
            searchUkexList = []
            searchUkexpayList = []
            if object['ukex_uid'] != 0:
                searchUkexList = database.selectSQL(database.ukex_cursor, "user_id, first_name, last_name, birthday, country , \'\' as residence_country,province ,city,town,district,street_address,building_number,building_name,"
                                                                          "sex,zip_code,\'\' as apartment, living_proof_1 as first_residence_certificate, living_proof_2 as second_residence_certificate,"
                                                                          "street_code, unit, house_code, passport, passport_ocr, passport_expire,passport_1 as passport_picture, passport_2 as passport_picture_hold,"
                                                                          "driving as driving_number, driving_1 as driving_picture, driving_2 as driving_picture_hold, is_eu as is_europe, nationality,has_deducted_gbp,has_deducted_eur,has_deducted_usd, "
                                                                          "0 as create_time, 0 as update_time"
                                                    ,'coin_user_info where user_id = "' + str(object['ukex_uid']) + '";')
            if object['ukexpay_uid'] != 0:
                searchUkexpayList = database.selectSQL(database.ukexpay_cursor, "uid as user_id, first_name, last_name , birth as birthday, residence_country as country, residence_country, state as province,"
                                                                                "city, town, district , street as street_address, building as building_number, building_name, sex, postcode as zip_code,"
                                                                                "apartment, living_proof_1 as first_residence_certificate, living_proof_2 as second_residence_certificate, 0 as has_deducted_gbp, 0 as has_deducted_eur, 0 as has_deducted_usd, 0 as create_time, 0 as update_time "
                                                       , 'cnuk_user_info where uid = "' + str(object['ukexpay_uid']) + '";')
            # assert (len(searchUkexList) == 1 or len(searchUkexpayList) == 1)
            if searchUkexList == None:
                searchUkexList = []
            if searchUkexpayList == None:
                searchUkexpayList = []
            if len(searchUkexList) != 0 and len(searchUkexpayList) != 0:
                assert (len(searchUkexList) == 1 and len(searchUkexpayList) == 1)
                ukexObj = searchUkexList[0]
                ukexpayObj = searchUkexpayList[0]
                insertObj['user_id'] = object['user_id']
                insertObj['first_name'] = ukexObj['first_name']
                insertObj['last_name'] = ukexObj['last_name']
                if ukexObj['birthday'] == '':
                    insertObj['birthday'] = 0
                else:
                    t = datetime.datetime.strptime(ukexObj['birthday'], '%Y-%m-%d')
                    insertObj['birthday'] = str(int(time.mktime(t.timetuple())))
                insertObj['country'] = ukexObj['country']
                insertObj['residence_country'] = ukexpayObj['residence_country']
                insertObj['province'] = ukexObj['province']
                insertObj['city'] = ukexObj['city']
                insertObj['town'] = ukexObj['town']
                insertObj['district'] = ukexObj['district']
                insertObj['has_deducted_gbp'] = ukexObj['has_deducted_gbp']
                insertObj['has_deducted_eur'] = ukexObj['has_deducted_eur']
                insertObj['has_deducted_usd'] = ukexObj['has_deducted_usd']
                insertObj['street_address'] = ukexObj['street_address']
                insertObj['building_number'] = ukexObj['building_number']
                insertObj['building_name'] = ukexObj['building_name']
                if ukexObj['sex'] == '' or ukexObj['sex'] == None:
                    insertObj['sex'] = 0
                else:
                    insertObj['sex'] = ukexObj['sex']
                insertObj['zip_code'] = ukexObj['zip_code']
                insertObj['apartment'] = ukexpayObj['apartment']
                insertObj['first_residence_certificate'] = ukexObj['first_residence_certificate']
                insertObj['second_residence_certificate'] = ukexObj['second_residence_certificate']
                insertObj['street_code'] = ukexObj['street_code']
                insertObj['unit'] = ukexObj['unit']
                insertObj['house_code'] = ukexObj['house_code']
                insertObj['passport'] = ukexObj['passport']
                insertObj['passport_ocr'] = ukexObj['passport_ocr']
                insertObj['passport_expire'] = ukexObj['passport_expire']
                insertObj['passport_picture'] = ukexObj['passport_picture']
                insertObj['passport_picture_hold'] = ukexObj['passport_picture_hold']
                insertObj['driving_number'] = ('' if ukexObj['driving_number'] == None else ukexObj['driving_number'])
                insertObj['driving_picture'] = ukexObj['driving_picture']
                insertObj['driving_picture_hold'] = ukexObj['driving_picture_hold']
                insertObj['is_europe'] = ukexObj['is_europe']
                insertObj['nationality'] = ukexObj['nationality']
                insertObj['create_time'] = ukexObj['create_time']
                insertObj['update_time'] = ukexObj['update_time']
            elif len(searchUkexList) != 0:
                assert (len(searchUkexList) == 1)
                ukexObj = searchUkexList[0]
                insertObj['user_id'] = object['user_id']
                insertObj['first_name'] = ukexObj['first_name']
                insertObj['last_name'] = ukexObj['last_name']
                
                if ukexObj['birthday'] == '':
                    insertObj['birthday'] = 0
                else:
                    t = datetime.datetime.strptime(ukexObj['birthday'], '%Y-%m-%d')
                    insertObj['birthday'] = str(int(time.mktime(t.timetuple())))
                insertObj['country'] = ukexObj['country']
                insertObj['residence_country'] = ukexObj['country']
                insertObj['province'] = ukexObj['province']
                insertObj['city'] = ukexObj['city']
                insertObj['town'] = ukexObj['town']
                insertObj['district'] = ukexObj['district']
                insertObj['street_address'] = ukexObj['street_address']
                insertObj['building_number'] = ukexObj['building_number']
                insertObj['building_name'] = ukexObj['building_name']
                if ukexObj['sex'] == '' or ukexObj['sex'] == None:
                    insertObj['sex'] = 0
                else:
                    insertObj['sex'] = ukexObj['sex']
                insertObj['zip_code'] = ukexObj['zip_code']
                insertObj['apartment'] = ''
                insertObj['first_residence_certificate'] = ukexObj['first_residence_certificate']
                insertObj['second_residence_certificate'] = ukexObj['second_residence_certificate']
                insertObj['street_code'] = ukexObj['street_code']
                insertObj['unit'] = ukexObj['unit']
                insertObj['has_deducted_gbp'] = ukexObj['has_deducted_gbp']
                insertObj['has_deducted_eur'] = ukexObj['has_deducted_eur']
                insertObj['has_deducted_usd'] = ukexObj['has_deducted_usd']
                insertObj['house_code'] = ukexObj['house_code']
                insertObj['passport'] = ukexObj['passport']
                insertObj['passport_ocr'] = ukexObj['passport_ocr']
                insertObj['passport_expire'] = ukexObj['passport_expire']
                insertObj['passport_picture'] = ukexObj['passport_picture']
                insertObj['passport_picture_hold'] = ukexObj['passport_picture_hold']
                insertObj['driving_number'] = ('' if ukexObj['driving_number'] == None else ukexObj['driving_number'])
                insertObj['driving_picture'] = ukexObj['driving_picture']
                insertObj['driving_picture_hold'] = ukexObj['driving_picture_hold']
                insertObj['is_europe'] = ukexObj['is_europe']
                insertObj['nationality'] = ukexObj['nationality']
                insertObj['create_time'] = ukexObj['create_time']
                insertObj['update_time'] = ukexObj['update_time']
            elif len(searchUkexpayList) != 0:
                assert (len(searchUkexpayList) == 1)
                ukexpayObj = searchUkexpayList[0]
                insertObj['user_id'] = object['user_id']
                insertObj['first_name'] = ukexpayObj['first_name']
                insertObj['last_name'] = ukexpayObj['last_name']
                if ukexpayObj['birthday'] == '':
                    insertObj['birthday'] = 0
                else:
                    insertObj['birthday'] = ukexpayObj['birthday']
                insertObj['country'] = ukexpayObj['residence_country']
                insertObj['residence_country'] = ukexpayObj['residence_country']
                insertObj['province'] = ukexpayObj['province']
                insertObj['city'] = ukexpayObj['city']
                insertObj['town'] = ukexpayObj['town']
                insertObj['district'] = ukexpayObj['district']
                insertObj['street_address'] = ukexpayObj['street_address']
                insertObj['building_number'] = ukexpayObj['building_number']
                insertObj['building_name'] = ukexpayObj['building_name']
                if ukexpayObj['sex'] == '' or ukexpayObj['sex'] == None:
                    insertObj['sex'] = 0
                else:
                    if ukexpayObj['sex'] == 'F':
                        insertObj['sex'] = 2
                    else:
                        insertObj['sex'] = 1
                insertObj['zip_code'] = ukexpayObj['zip_code']
                insertObj['apartment'] = ukexpayObj['apartment']
                insertObj['first_residence_certificate'] = ukexpayObj['first_residence_certificate']
                insertObj['second_residence_certificate'] = ukexpayObj['second_residence_certificate']
                insertObj['has_deducted_gbp'] = ukexpayObj['has_deducted_gbp']
                insertObj['has_deducted_eur'] = ukexpayObj['has_deducted_eur']
                insertObj['has_deducted_usd'] = ukexpayObj['has_deducted_usd']
                insertObj['street_code'] = ''
                insertObj['unit'] = ''
                insertObj['house_code'] = ''
                insertObj['passport'] = ''
                insertObj['passport_ocr'] = ''
                insertObj['passport_expire'] = ''
                insertObj['passport_picture'] = ''
                insertObj['passport_picture_hold'] = ''
                insertObj['driving_number'] = ''
                insertObj['driving_picture'] = ''
                insertObj['driving_picture_hold'] = ''
                insertObj['is_europe'] = 0
                insertObj['nationality'] = ''
                insertObj['create_time'] = ukexpayObj['create_time']
                insertObj['update_time'] = ukexpayObj['update_time']
            else:
                icount += 1
                continue
            insertList.append(insertObj)
        dbOper.insertToDB('user_facts', insertList, dbOper.user_facts)
        print ('-------------------------------------------------------------' + str(icount))

    def loadTableUserInfoData(self):
        print ('--------------------导入表user_Info---------------------------')
        insertList = []
        icount = 0
        for object in mappingList:
            insertObj = {}
            insertObj['user_id'] = object['user_id']
            searchUkexList = []
            searchUkexpayMainList = []
            searchUkexpayInfoList = []
            if object['ukex_uid'] != 0:
                searchUkexList = database.selectSQL(database.ukex_cursor, "id as user_id,moble as mobile, id_type , paypassword , invit_1 as recommender_level1,invit_2 as recommender_level2,"
                                                                          "invit_3 as recommender_level3, truename as realname,country,mobletime as mobile_binding_time,idcard as id_number,addip as ip_address ,addr as address_desc,"
                                                                          "email,wechat,wechat_img,openid as wechat_openid ,alipay,alipay_img,invit as invite_code,custom_cate_id,parent_id as master_account,source_proj_uid,"
                                                                          "uuid,uuid_salt,ga as secret_key, 0 as create_time, 0 as update_time"
                                                    ,'coin_user where id = "' + str(object['ukex_uid']) + '";')
            if object['ukexpay_uid'] != 0:
                searchUkexpayMainList = database.selectSQL(database.ukexpay_cursor, "uid as user_id,phone as mobile,pin as paypassword,country,img_url as user_image,country_code,type as user_type,active_time as account_active_time,"
                                                                                    "secret_key,refer_currency, kyc_refuse_num, lucky_count, c2c_refuse_num, rescue_code, 0 as create_time, 0 as update_time"
                                                       , 'cnuk_user_main where uid = "' + str(object['ukexpay_uid']) + '";')
            if object['ukexpay_uid'] != 0:
                searchUkexpayInfoList = database.selectSQL(database.ukexpay_cursor, "uid as user_id,certificate_type as id_type,identity_number, identity_expiry_date, identity_info ,invit_1 as recommender_level1,"
                                                                                    "invit_2 as recommender_level2,invit_3 as recommender_level3 ,cn_name as realname,c2c_info_ext,ext,invit_time,source_of_funds,"
                                                                                    "invit_code as invite_code, 0 as create_time, 0 as update_time"
                                                       , 'cnuk_user_info where uid = "' + str(object['ukexpay_uid']) + '";')
            if searchUkexList == None:
                searchUkexList = []
            if searchUkexpayMainList == None:
                searchUkexpayMainList = []
            if searchUkexpayInfoList == None:
                searchUkexpayInfoList = []
            insertObj['mobile'] = ''
            insertObj['id_type'] = 0
            insertObj['identity_number'] = ''
            insertObj['identity_expiry_date'] = ''
            insertObj['identity_info'] = ''
            insertObj['paypassword'] = ''
            insertObj['recommender_level1'] = ''
            insertObj['recommender_level2'] = ''
            insertObj['recommender_level3'] = ''
            insertObj['realname'] = ''
            insertObj['country'] = ''
            insertObj['c2c_info_ext'] = ''
            insertObj['ext'] = ''
            insertObj['invit_time'] = 0
            insertObj['source_of_funds'] = ''
            insertObj['mobile_binding_time'] = 0
            insertObj['id_number'] = ''
            insertObj['ip_address'] = ''
            insertObj['address_desc'] = ''
            insertObj['email'] = ''
            insertObj['wechat'] = ''
            insertObj['wechat_img'] = ''
            insertObj['wechat_openid'] = ''
            insertObj['alipay'] = ''
            insertObj['alipay_img'] = ''
            insertObj['invite_code'] = ''
            insertObj['custom_cate_id'] = 0
            insertObj['master_account'] = 0
            insertObj['source_proj_uid'] = 0
            insertObj['uuid'] = ''
            insertObj['uuid_salt'] = ''
            insertObj['user_image'] = ''
            insertObj['country_code'] = ''
            insertObj['user_type'] = 0
            insertObj['account_active_time'] = 0
            insertObj['secret_key'] = ''
            insertObj['refer_currency'] = 0
            insertObj['kyc_refuse_num'] = 0
            insertObj['lucky_count'] = 0
            insertObj['c2c_refuse_num'] = 0
            insertObj['rescue_code'] = ''
            insertObj['create_time'] = 0
            insertObj['update_time'] = 0

            if len(searchUkexList) != 0 and len(searchUkexpayMainList) != 0 and len(searchUkexpayInfoList) != 0:
                assert (len(searchUkexList) == 1 and len(searchUkexpayMainList) == 1 and len(searchUkexpayInfoList) == 1)
                ukexObj = searchUkexList[0]
                ukexpayMainObj = searchUkexpayMainList[0]
                ukexpayInfoObj = searchUkexpayInfoList[0]
                insertObj['mobile'] = (ukexObj['mobile'] if ukexObj['mobile'] != '' else ukexpayMainObj['mobile'])
                insertObj['id_type'] = (ukexObj['id_type'] if ukexObj['id_type'] != '' else ukexpayInfoObj['id_type'])
                insertObj['identity_number'] = ukexpayInfoObj['identity_number']
                insertObj['identity_expiry_date'] = ukexpayInfoObj['identity_expiry_date']
                insertObj['identity_info'] = (ukexpayInfoObj['identity_info'] if ukexpayInfoObj['identity_info'] != None else '')
                insertObj['paypassword'] = (ukexObj['paypassword'] if ukexObj['paypassword'] != '' else ukexpayMainObj['paypassword'])
                insertObj['recommender_level1'] = (ukexObj['recommender_level1'] if ukexObj['recommender_level1'] != '' else ukexpayInfoObj['recommender_level1'])
                insertObj['recommender_level2'] = (ukexObj['recommender_level2'] if ukexObj['recommender_level2'] != '' else ukexpayInfoObj['recommender_level2'])
                insertObj['recommender_level3'] = (ukexObj['recommender_level3'] if ukexObj['recommender_level3'] != '' else ukexpayInfoObj['recommender_level3'])
                insertObj['realname'] = (ukexObj['realname'] if ukexObj['realname'] != '' else ukexpayInfoObj['realname'])
                insertObj['country'] = (ukexObj['country'] if ukexObj['country'] != '' else ukexpayMainObj['country'])
                insertObj['c2c_info_ext'] = (ukexpayInfoObj['c2c_info_ext'] if ukexpayInfoObj['c2c_info_ext'] != None else '')
                insertObj['ext'] = (ukexpayInfoObj['ext'] if ukexpayInfoObj['ext'] != None else '')
                insertObj['invit_time'] = (ukexpayInfoObj['invit_time'] if ukexpayInfoObj['invit_time'] != None else 0)
                insertObj['source_of_funds'] = (ukexpayInfoObj['source_of_funds'] if ukexpayInfoObj['source_of_funds'] != None else '')
                insertObj['mobile_binding_time'] = ukexObj['mobile_binding_time']
                insertObj['id_number'] = ukexObj['id_number']
                insertObj['ip_address'] = ukexObj['ip_address']
                insertObj['address_desc'] = ukexObj['address_desc']
                insertObj['email'] = ukexObj['email']
                insertObj['wechat'] = ukexObj['wechat']
                insertObj['wechat_img'] = ukexObj['wechat_img']
                insertObj['wechat_openid'] = ukexObj['wechat_openid']
                insertObj['alipay'] = ukexObj['alipay']
                insertObj['alipay_img'] = ukexObj['alipay_img']
                insertObj['invite_code'] = (ukexObj['invite_code'] if ukexObj['invite_code'] != '' else ukexpayInfoObj['invite_code'])
                insertObj['custom_cate_id'] = (ukexObj['custom_cate_id'] if ukexObj['custom_cate_id'] != None else 0)
                insertObj['master_account'] = ukexObj['master_account']
                insertObj['source_proj_uid'] = ukexObj['source_proj_uid']
                insertObj['uuid'] = ukexObj['uuid']
                insertObj['uuid_salt'] = ukexObj['uuid_salt']
                insertObj['user_image'] = ukexpayMainObj['user_image']
                insertObj['country_code'] = ukexpayMainObj['country_code']
                # 用户类型 user：用户 merchant：做市商
                # 用户类型 0-无；1-user：用户 2-merchant：做市商
                if ukexpayMainObj['user_type'] == 'user':
                    insertObj['user_type'] = 1
                elif ukexpayMainObj['user_type'] == 'merchant':
                    insertObj['user_type'] = 2
                else:
                    insertObj['user_type'] = 0
                insertObj['account_active_time'] = ukexpayMainObj['account_active_time']
                insertObj['secret_key'] = (ukexObj['secret_key'] if ukexObj['secret_key'] != '' else ukexpayMainObj['secret_key'])
                insertObj['refer_currency'] = ukexpayMainObj['refer_currency']
                insertObj['kyc_refuse_num'] = (ukexpayMainObj['kyc_refuse_num'] if ukexpayMainObj['kyc_refuse_num'] != None else 0)
                insertObj['lucky_count'] = ukexpayMainObj['lucky_count']
                insertObj['c2c_refuse_num'] = (ukexpayMainObj['c2c_refuse_num'] if ukexpayMainObj['c2c_refuse_num'] != None else 0)
                insertObj['rescue_code'] = ukexpayMainObj['rescue_code']
                insertObj['create_time'] = ukexpayMainObj['create_time']
                insertObj['update_time'] = ukexpayMainObj['update_time']
            elif len(searchUkexList) != 0 and len(searchUkexpayMainList) != 0:
                assert (len(searchUkexList) == 1 and len(searchUkexpayMainList) == 1)
                ukexObj = searchUkexList[0]
                ukexpayMainObj = searchUkexpayMainList[0]
                insertObj['mobile'] = (ukexObj['mobile'] if ukexObj['mobile'] != '' else ukexpayMainObj['mobile'])
                insertObj['id_type'] = ukexObj['id_type']
                insertObj['paypassword'] = (ukexObj['paypassword'] if ukexObj['paypassword'] != '' else ukexpayMainObj['paypassword'])
                insertObj['recommender_level1'] = ukexObj['recommender_level1']
                insertObj['recommender_level2'] = ukexObj['recommender_level2']
                insertObj['recommender_level3'] = ukexObj['recommender_level3']
                insertObj['realname'] = ukexObj['realname']
                insertObj['country'] = (ukexObj['country'] if ukexObj['country'] != '' else ukexpayMainObj['country'])
                insertObj['mobile_binding_time'] = ukexObj['mobile_binding_time']
                insertObj['id_number'] = ukexObj['id_number']
                insertObj['ip_address'] = ukexObj['ip_address']
                insertObj['address_desc'] = ukexObj['address_desc']
                insertObj['email'] = ukexObj['email']
                insertObj['wechat'] = ukexObj['wechat']
                insertObj['wechat_img'] = ukexObj['wechat_img']
                insertObj['wechat_openid'] = ukexObj['wechat_openid']
                insertObj['alipay'] = ukexObj['alipay']
                insertObj['alipay_img'] = ukexObj['alipay_img']
                insertObj['invite_code'] = ukexObj['invite_code']
                insertObj['custom_cate_id'] = (ukexObj['custom_cate_id'] if ukexObj['custom_cate_id'] != None else 0)
                insertObj['master_account'] = ukexObj['master_account']
                insertObj['source_proj_uid'] = ukexObj['source_proj_uid']
                insertObj['uuid'] = ukexObj['uuid']
                insertObj['uuid_salt'] = ukexObj['uuid_salt']
                insertObj['user_image'] = ukexpayMainObj['user_image']
                insertObj['country_code'] = ukexpayMainObj['country_code']
                # 用户类型 user：用户 merchant：做市商
                # 用户类型 0-无；1-user：用户 2-merchant：做市商
                if ukexpayMainObj['user_type'] == 'user':
                    insertObj['user_type'] = 1
                elif ukexpayMainObj['user_type'] == 'merchant':
                    insertObj['user_type'] = 2
                else:
                    insertObj['user_type'] = 0
                insertObj['account_active_time'] = ukexpayMainObj['account_active_time']
                insertObj['secret_key'] = (ukexObj['secret_key'] if ukexObj['secret_key'] != '' else ukexpayMainObj['secret_key'])
                insertObj['refer_currency'] = ukexpayMainObj['refer_currency']
                insertObj['kyc_refuse_num'] = (ukexpayMainObj['kyc_refuse_num'] if ukexpayMainObj['kyc_refuse_num'] != None else 0)
                insertObj['lucky_count'] = ukexpayMainObj['lucky_count']
                insertObj['c2c_refuse_num'] = (ukexpayMainObj['c2c_refuse_num'] if ukexpayMainObj['c2c_refuse_num'] != None else 0)
                insertObj['rescue_code'] = ukexpayMainObj['rescue_code']
                insertObj['create_time'] = ukexpayMainObj['create_time']
                insertObj['update_time'] = ukexpayMainObj['update_time']
            elif len(searchUkexList) != 0 and len(searchUkexpayInfoList) != 0:
                assert (len(searchUkexList) == 1 and len(searchUkexpayInfoList) == 1)
                ukexObj = searchUkexList[0]
                ukexpayInfoObj = searchUkexpayInfoList[0]
                insertObj['mobile'] = ukexObj['mobile']
                insertObj['id_type'] = (ukexObj['id_type'] if ukexObj['id_type'] != '' else ukexpayInfoObj['id_type'])
                insertObj['identity_number'] = ukexpayInfoObj['identity_number']
                insertObj['identity_expiry_date'] = ukexpayInfoObj['identity_expiry_date']
                insertObj['identity_info'] = (ukexpayInfoObj['identity_info'] if ukexpayInfoObj['identity_info'] != None else '')
                insertObj['paypassword'] = ukexObj['paypassword']
                insertObj['recommender_level1'] = (ukexObj['recommender_level1'] if ukexObj['recommender_level1'] != '' else ukexpayInfoObj['recommender_level1'])
                insertObj['recommender_level2'] = (ukexObj['recommender_level2'] if ukexObj['recommender_level2'] != '' else ukexpayInfoObj['recommender_level2'])
                insertObj['recommender_level3'] = (ukexObj['recommender_level3'] if ukexObj['recommender_level3'] != '' else ukexpayInfoObj['recommender_level3'])
                insertObj['realname'] = (ukexObj['realname'] if ukexObj['realname'] != '' else ukexpayInfoObj['realname'])
                insertObj['country'] = ukexObj['country']
                insertObj['c2c_info_ext'] = (ukexpayInfoObj['c2c_info_ext'] if ukexpayInfoObj['c2c_info_ext'] != None else '')
                insertObj['ext'] = (ukexpayInfoObj['ext'] if ukexpayInfoObj['ext'] != None else '')
                insertObj['invit_time'] = (ukexpayInfoObj['invit_time'] if ukexpayInfoObj['invit_time'] != None else 0)
                insertObj['source_of_funds'] = (ukexpayInfoObj['source_of_funds'] if ukexpayInfoObj['source_of_funds'] != None else '')
                insertObj['mobile_binding_time'] = ukexObj['mobile_binding_time']
                insertObj['id_number'] = ukexObj['id_number']
                insertObj['ip_address'] = ukexObj['ip_address']
                insertObj['address_desc'] = ukexObj['address_desc']
                insertObj['email'] = ukexObj['email']
                insertObj['wechat'] = ukexObj['wechat']
                insertObj['wechat_img'] = ukexObj['wechat_img']
                insertObj['wechat_openid'] = ukexObj['wechat_openid']
                insertObj['alipay'] = ukexObj['alipay']
                insertObj['alipay_img'] = ukexObj['alipay_img']
                insertObj['invite_code'] = (ukexObj['invite_code'] if ukexObj['invite_code'] != '' else ukexpayInfoObj['invite_code'])
                insertObj['custom_cate_id'] = (ukexObj['custom_cate_id'] if ukexObj['custom_cate_id'] != None else 0)
                insertObj['master_account'] = ukexObj['master_account']
                insertObj['source_proj_uid'] = ukexObj['source_proj_uid']
                insertObj['uuid'] = ukexObj['uuid']
                insertObj['uuid_salt'] = ukexObj['uuid_salt']
                insertObj['secret_key'] = ukexObj['secret_key']
            elif len(searchUkexpayMainList) != 0 and len(searchUkexpayInfoList) != 0:
                assert (len(searchUkexpayMainList) == 1 and len(searchUkexpayInfoList) == 1)
                ukexpayMainObj = searchUkexpayMainList[0]
                ukexpayInfoObj = searchUkexpayInfoList[0]
                insertObj['mobile'] = ukexpayMainObj['mobile']
                insertObj['id_type'] = ukexpayInfoObj['id_type']
                insertObj['identity_number'] = ukexpayInfoObj['identity_number']
                insertObj['identity_expiry_date'] = ukexpayInfoObj['identity_expiry_date']
                insertObj['identity_info'] = (ukexpayInfoObj['identity_info'] if ukexpayInfoObj['identity_info'] != None else '')
                insertObj['paypassword'] = ukexpayMainObj['paypassword']
                insertObj['recommender_level1'] = ukexpayInfoObj['recommender_level1']
                insertObj['recommender_level2'] = ukexpayInfoObj['recommender_level2']
                insertObj['recommender_level3'] = ukexpayInfoObj['recommender_level3']
                insertObj['realname'] = ukexpayInfoObj['realname']
                insertObj['country'] = ukexpayMainObj['country']
                insertObj['c2c_info_ext'] = (ukexpayInfoObj['c2c_info_ext'] if ukexpayInfoObj['c2c_info_ext'] != None else '')
                insertObj['ext'] = (ukexpayInfoObj['ext'] if ukexpayInfoObj['ext'] != None else '')
                insertObj['invit_time'] = (ukexpayInfoObj['invit_time'] if ukexpayInfoObj['invit_time'] != None else 0)
                insertObj['source_of_funds'] = (ukexpayInfoObj['source_of_funds'] if ukexpayInfoObj['source_of_funds'] != None else '')
                insertObj['invite_code'] = ukexpayInfoObj['invite_code']
                insertObj['user_image'] = ukexpayMainObj['user_image']
                insertObj['country_code'] = ukexpayMainObj['country_code']
                # 用户类型 user：用户 merchant：做市商
                # 用户类型 0-无；1-user：用户 2-merchant：做市商
                if ukexpayMainObj['user_type'] == 'user':
                    insertObj['user_type'] = 1
                elif ukexpayMainObj['user_type'] == 'merchant':
                    insertObj['user_type'] = 2
                else:
                    insertObj['user_type'] = 0
                insertObj['account_active_time'] = ukexpayMainObj['account_active_time']
                insertObj['secret_key'] = ukexpayMainObj['secret_key']
                insertObj['refer_currency'] = ukexpayMainObj['refer_currency']
                insertObj['kyc_refuse_num'] = (ukexpayMainObj['kyc_refuse_num'] if ukexpayMainObj['kyc_refuse_num'] != None else 0)
                insertObj['lucky_count'] = ukexpayMainObj['lucky_count']
                insertObj['c2c_refuse_num'] = (ukexpayMainObj['c2c_refuse_num'] if ukexpayMainObj['c2c_refuse_num'] != None else 0)
                insertObj['rescue_code'] = ukexpayMainObj['rescue_code']
                insertObj['create_time'] = ukexpayMainObj['create_time']
                insertObj['update_time'] = ukexpayMainObj['update_time']
            elif len(searchUkexList) != 0:
                assert (len(searchUkexList) == 1)
                ukexObj = searchUkexList[0]
                insertObj['mobile'] = ukexObj['mobile']
                insertObj['id_type'] = ukexObj['id_type']
                insertObj['paypassword'] = ukexObj['paypassword']
                insertObj['recommender_level1'] = ukexObj['recommender_level1']
                insertObj['recommender_level2'] = ukexObj['recommender_level2']
                insertObj['recommender_level3'] = ukexObj['recommender_level3']
                insertObj['realname'] = ukexObj['realname']
                insertObj['country'] = ukexObj['country']
                insertObj['mobile_binding_time'] = ukexObj['mobile_binding_time']
                insertObj['id_number'] = ukexObj['id_number']
                insertObj['ip_address'] = ukexObj['ip_address']
                insertObj['address_desc'] = ukexObj['address_desc']
                insertObj['email'] = ukexObj['email']
                insertObj['wechat'] = ukexObj['wechat']
                insertObj['wechat_img'] = ukexObj['wechat_img']
                insertObj['wechat_openid'] = ukexObj['wechat_openid']
                insertObj['alipay'] = ukexObj['alipay']
                insertObj['alipay_img'] = ukexObj['alipay_img']
                insertObj['invite_code'] = ukexObj['invite_code']
                insertObj['custom_cate_id'] = (ukexObj['custom_cate_id'] if ukexObj['custom_cate_id'] != None else 0)
                insertObj['master_account'] = ukexObj['master_account']
                insertObj['source_proj_uid'] = ukexObj['source_proj_uid']
                insertObj['uuid'] = ukexObj['uuid']
                insertObj['uuid_salt'] = ukexObj['uuid_salt']
                insertObj['secret_key'] = ukexObj['secret_key']
            elif len(searchUkexpayMainList) != 0:
                assert (len(searchUkexpayMainList) == 1)
                ukexpayMainObj = searchUkexpayMainList[0]
                insertObj['mobile'] = ukexpayMainObj['mobile']
                insertObj['paypassword'] = ukexpayMainObj['paypassword']
                insertObj['country'] = ukexpayMainObj['country']
                insertObj['user_image'] = ukexpayMainObj['user_image']
                insertObj['country_code'] = ukexpayMainObj['country_code']
                if ukexpayMainObj['user_type'] == 'user':
                    insertObj['user_type'] = 1
                elif ukexpayMainObj['user_type'] == 'merchant':
                    insertObj['user_type'] = 2
                else:
                    insertObj['user_type'] = 0
                insertObj['account_active_time'] = ukexpayMainObj['account_active_time']
                insertObj['secret_key'] = ukexpayMainObj['secret_key']
                insertObj['refer_currency'] = ukexpayMainObj['refer_currency']
                insertObj['kyc_refuse_num'] = (ukexpayMainObj['kyc_refuse_num'] if ukexpayMainObj['kyc_refuse_num'] != None else 0)
                insertObj['lucky_count'] = ukexpayMainObj['lucky_count']
                insertObj['c2c_refuse_num'] = (ukexpayMainObj['c2c_refuse_num'] if ukexpayMainObj['c2c_refuse_num'] != None else 0)
                insertObj['rescue_code'] = ukexpayMainObj['rescue_code']
                insertObj['create_time'] = ukexpayMainObj['create_time']
                insertObj['update_time'] = ukexpayMainObj['update_time']
            elif len(searchUkexpayInfoList) != 0:
                assert (len(searchUkexpayInfoList) == 1)
                ukexpayInfoObj = searchUkexpayInfoList[0]
                insertObj['id_type'] = ukexpayInfoObj['id_type']
                insertObj['identity_number'] = ukexpayInfoObj['identity_number']
                insertObj['identity_expiry_date'] = ukexpayInfoObj['identity_expiry_date']
                insertObj['identity_info'] = (ukexpayInfoObj['identity_info'] if ukexpayInfoObj['identity_info'] != None else '')
                insertObj['recommender_level1'] = ukexpayInfoObj['recommender_level1']
                insertObj['recommender_level2'] = ukexpayInfoObj['recommender_level2']
                insertObj['recommender_level3'] = ukexpayInfoObj['recommender_level3']
                insertObj['realname'] = ukexpayInfoObj['realname']
                insertObj['c2c_info_ext'] = (ukexpayInfoObj['c2c_info_ext'] if ukexpayInfoObj['c2c_info_ext'] != None else '')
                insertObj['ext'] = (ukexpayInfoObj['ext'] if ukexpayInfoObj['ext'] != None else '')
                insertObj['invit_time'] = (ukexpayInfoObj['invit_time'] if ukexpayInfoObj['invit_time'] != None else 0)
                insertObj['source_of_funds'] = (ukexpayInfoObj['source_of_funds'] if ukexpayInfoObj['source_of_funds'] != None else '')
                insertObj['invite_code'] = ukexpayInfoObj['invite_code']
            else:
                icount += 1
                continue
            insertList.append(insertObj)
        dbOper.insertToDB('user_info', insertList, dbOper.user_info)
        print ('-------------------------------------------------------------' + str(icount))

    def createCoinTable(self):
        for coinID in self.user_assets_coinID:
            sqlCreateTable = 'CREATE TABLE user_assets_'+coinID+'(id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'id 无符号64长整型=[时间戳秒+自增int]\' ,\
		                    source_type tinyint(1) NOT NULL COMMENT \'资产状态 0:未知; 1-ukex用户 ;2-ukexpay用户;\' ,\
                            user_id BIGINT NOT NULL COMMENT \'userid\' ,\
                            usable DECIMAL(32,16) unsigned NOT NULL COMMENT \'可用金额\',\
                            freeze DECIMAL(32,16) unsigned NOT NULL  COMMENT \'冻结金额\' ,\
                            lock_up DECIMAL(32,16) unsigned NOT NULL  COMMENT \'锁仓\' ,\
                            status tinyint(1) NOT NULL COMMENT \'资产状态 -3:未激活; -2:隐藏;-1:销户;0-禁用;1-正常;\' ,\
                            create_time int(11) unsigned NOT NULL COMMENT \'创建时间\' ,\
                            update_time int(11) DEFAULT 0  COMMENT \'更新时间\' ,\
                            PRIMARY KEY (id)\
                            ) COMMENT = \'用户资产表\';;'
            database.excuteSQL(database.assetsDB_cursor,sqlCreateTable)

    def loadTableUserAssetsData(self):
        print ('--------------------导入表user_assets---------------------------')

        icount = 0
        for object in mappingList:
            insertObj = {}
            insertObj2 = {}
            searchUkexList = []
            searchUkexpayList = []
            if object['ukex_uid'] != 0:
                searchUkexList = database.selectSQL(database.ukex_cursor,"last_insert_id() as id,coin_id, usable,freeze,lockup as lock_up,  status, add_time as create_time, add_time as update_time",
                                                    'coin_user_coin_balance where user_id = "' + str(object['ukex_uid']) + '";')
            if object['ukexpay_uid'] != 0:
                searchUkexpayList = database.selectSQL(database.ukexpay_cursor,"last_insert_id() as id,coin_id, usable,freeze, status,create_time, update_time"
                                                       , 'cnuk_user_balance where uid = "' + str(object['ukexpay_uid']) + '";')
            # assert (len(searchUkexList) == 1 or len(searchUkexpayList) == 1)
            if searchUkexList == None:
                searchUkexList = []
            if searchUkexpayList == None:
                searchUkexpayList = []
            if len(searchUkexList) != 0 and len(searchUkexpayList) != 0:
                for ukexObj in searchUkexList:
                    insertObj['id'] = ukexObj['id']
                    insertObj['source_type'] = 1
                    insertObj['user_id'] = object['user_id']
                    insertObj['usable'] = ukexObj['usable']
                    insertObj['freeze'] = ukexObj['freeze']
                    insertObj['lock_up'] = ukexObj['lock_up']
                    insertObj['status'] = ukexObj['status']
                    insertObj['create_time'] = ukexObj['create_time']
                    insertObj['update_time'] = ukexObj['update_time']
                    dbOper.insertToAssets('user_assets_' + str(ukexObj['coin_id']), [insertObj], dbOper.user_assets)
                for ukexpayObj in searchUkexpayList:
                    insertObj2['id'] = ukexpayObj['id']
                    insertObj2['source_type'] = 2
                    insertObj2['user_id'] = object['user_id']
                    insertObj2['usable'] = ukexpayObj['usable']
                    insertObj2['freeze'] = ukexpayObj['freeze']
                    insertObj2['lock_up'] = 0
                    insertObj2['status'] = ukexpayObj['status']
                    insertObj2['create_time'] = ukexpayObj['create_time']
                    insertObj2['update_time'] = ukexpayObj['update_time']
                    dbOper.insertToAssets('user_assets_' + str(ukexpayObj['coin_id']), [insertObj2], dbOper.user_assets)
            elif len(searchUkexList) != 0:
                for ukexObj in searchUkexList:
                    insertObj['id'] = ukexObj['id']
                    insertObj['source_type'] = 1
                    insertObj['user_id'] = object['user_id']
                    insertObj['usable'] = ukexObj['usable']
                    insertObj['freeze'] = ukexObj['freeze']
                    insertObj['lock_up'] = ukexObj['lock_up']
                    insertObj['status'] = ukexObj['status']
                    insertObj['create_time'] = ukexObj['create_time']
                    insertObj['update_time'] = ukexObj['update_time']
                    dbOper.insertToAssets('user_assets_' + str(ukexObj['coin_id']), [insertObj], dbOper.user_assets)
            elif len(searchUkexpayList) != 0:
                for ukexpayObj in searchUkexpayList:
                    insertObj2['id'] = ukexpayObj['id']
                    insertObj2['source_type'] = 2
                    insertObj2['user_id'] = object['user_id']
                    insertObj2['usable'] = ukexpayObj['usable']
                    insertObj2['freeze'] = ukexpayObj['freeze']
                    insertObj2['lock_up'] = 0
                    insertObj2['status'] = ukexpayObj['status']
                    insertObj2['create_time'] = ukexpayObj['create_time']
                    insertObj2['update_time'] = ukexpayObj['update_time']
                    dbOper.insertToAssets('user_assets_' + str(ukexpayObj['coin_id']), [insertObj2],dbOper.user_assets)
            else:
                icount += 1
                continue
        print ('-------------------------------------------------------------' + str(icount))

    # --------------------------------------------------以下是BackTrade数据库表导入逻辑部分------------------------------------------
    def loadTableRecommendedTradeAwardData(self):
        icount = 0
        for object in mappingList:
            insertObj = {}
            insertObj['user_id'] = object['user_id']
            searchUkexList = []
            if object['ukex_uid'] != 0:
                searchUkexList = database.selectSQL(database.ukex_cursor,"last_insert_id() as id,invit as recommender_id, name as market_id , type as oper_type , coinname , num as trading_volume , mum as trading_amount,"
                                                                         "fee as profit , addtime as create_time, addtime as update_time",
                                                    'coin_invit where userid = "' + str(object['ukex_uid']) + '";')

            if searchUkexList == None:
                searchUkexList = []

            if len(searchUkexList) != 0:
                for ukexObj in searchUkexList:
                    insertObj['id'] = ukexObj['id']
                    insertObj['recommender_id'] = dbOper.getNewUserId(str(ukexObj['recommender_id']))
                    
                    insertObj['oper_type'] = (1 if '买入' in ukexObj['oper_type'] else 2)
                    
                    key1 = re.sub('[^a-zA-Z_]', '', ukexObj['oper_type'])
                    key2 = re.sub('[^a-zA-Z_]', '', ukexObj['coinname'])
                    if key1 != '' and marketMapping.has_key(key1):
                        insertObj['market_id'] = marketMapping[key1]
                    else:
                        continue
                    if key2 != '' and coinnameMapping.has_key(key2):
                        insertObj['coin_id'] = coinnameMapping[key2]
                    else:
                        continue

                    insertObj['trading_volume'] = ukexObj['trading_volume']
                    insertObj['trading_amount'] = ukexObj['trading_amount']
                    insertObj['profit'] = ukexObj['profit']
                    insertObj['create_time'] = ukexObj['create_time']
                    insertObj['update_time'] = ukexObj['update_time']
                    if str(insertObj['user_id']) == '56':
                        print(insertObj)
                    dbOper.insertToAssets('recommended_trade_award', [insertObj], dbOper.recommended_trade_award)
            else:
                icount += 1
                continue
        
        print ('-------------------------------------------------------------' + str(icount))

    def loadTableKLineMinData(self):
        icount = 0
        insertList = []
        searchUkexList = database.selectSQL(database.ukex_cursor,"id, market as market_id, addtime as begin_time , open ,high , low , close , volume as trading_volume , addtime as create_time, addtime as update_time",
                                                'coin_trade_chart;')
        assert (searchUkexList != None)
        for searchObj in searchUkexList:
            insertObj = {}
            insertObj['id'] = searchObj['id']
            insertObj['market_id'] = marketMapping[searchObj['market_id']]
            insertObj['begin_time'] = searchObj['begin_time']
            insertObj['open'] = searchObj['open']
            insertObj['high'] = searchObj['high']
            insertObj['low'] = searchObj['low']
            insertObj['close'] = searchObj['close']
            insertObj['trading_volume'] = searchObj['trading_volume']
            insertObj['create_time'] = searchObj['create_time']
            insertObj['update_time'] = searchObj['update_time']
            insertList.append(insertObj)
        dbOper.insertToSA('kline_minimum', insertList, dbOper.coin_kline_minimum)
        print ('-------------------------------------------------------------' + str(icount))

    def loadTableKLineRecordData(self):
        icount = 0
        insertList = []
        searchUkexList = database.selectSQL(database.ukex_cursor,"id, market as market_id,type as Kline_type, data , addtime as create_time, addtime as update_time",
                                                'coin_trade_json;')
        assert (searchUkexList != None)
        dicvalue = {}
        for searchObj in searchUkexList:
            insertObj = {}
            insertObj['id'] = searchObj['id']
            if marketMapping.has_key(searchObj['market_id']):
                insertObj['market_id'] = marketMapping[searchObj['market_id']]
                if searchObj['data'] != '':
                    dic = json.loads(searchObj['data'])
                    insertObj['begin_time'] = dic[0]
                    insertObj['trading_volume'] = dic[1]
                    insertObj['open'] = dic[2]
                    insertObj['high'] = dic[3]
                    insertObj['low'] = dic[4]
                    insertObj['close'] = dic[5]
                else:
                    insertObj['begin_time'] = 0
                    insertObj['trading_volume'] = None
                    insertObj['open'] = None
                    insertObj['high'] = None
                    insertObj['low'] = None
                    insertObj['close'] = None

                insertObj['Kline_type'] = searchObj['Kline_type']
                insertObj['create_time'] = searchObj['create_time']
                insertObj['update_time'] = searchObj['update_time']
                insertList.append(insertObj)
            else:
                dicvalue[str(searchObj['market_id'])] = 1
        dbOper.insertToSA('kline_record', insertList, dbOper.kline_record)
        print ('-------------------------------------------------------------' + str(icount))

    def loadTableFinancialRecordsData(self):
        insertList = []
        for object in mappingList:
            searchUkexList = database.selectSQL(database.ukex_cursor,
                                            "id, coinname as coin_id , num_a as gross_amount ,num_b as gross_frozen , num as gross_sum , fee , fee_b as fee_frozen , type as oper_type,"
                                            "nameid as oper_id, remark as oper_desc, mum_a as remaining_amount, mum_b as remaining_frozen, mum as remaining_sum, move as record_hash, status , addtime as create_time, addtime as update_time",
                                            'coin_finance where userid = "' + str(object['ukex_uid']) + '";')
            if searchUkexList == None:
                continue
            for searchObj in searchUkexList:
                insertObj = {}
                insertObj['id'] = searchObj['id']
                insertObj['user_id'] = object['user_id']
                insertObj['coin_id'] = coinnameMapping[searchObj['coin_id']]
                insertObj['gross_amount'] = searchObj['gross_amount']
                insertObj['gross_frozen'] = searchObj['gross_frozen']
                insertObj['gross_sum'] = searchObj['gross_sum']
                insertObj['fee'] = searchObj['fee']
                insertObj['fee_frozen'] = searchObj['fee_frozen']
                insertObj['oper_type'] = searchObj['oper_type']
                insertObj['oper_id'] = searchObj['oper_id']
                insertObj['oper_desc'] = searchObj['oper_desc']
                insertObj['remaining_amount'] = searchObj['remaining_amount']
                insertObj['remaining_frozen'] = searchObj['remaining_frozen']
                insertObj['remaining_sum'] = searchObj['remaining_sum']
                insertObj['record_hash'] = searchObj['record_hash']
                insertObj['status'] = searchObj['status']
                insertObj['create_time'] = searchObj['create_time']
                insertObj['update_time'] = searchObj['update_time']
                insertList.append(insertObj)
        print(len(insertList))
        # dbOper.insertToSA('financial_records', insertList, dbOper.financial_records)
        print ('-------------------------------------------------------------')

    def createWaitCloseTables(self):
        for marketObj in marketMappingList:
            sqlCreateTable = 'CREATE TABLE wait_' + str(marketObj['id']) + '(\
                            id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'id 无符号64长整型=[时间戳秒+自增int]\' ,\
                            user_id BIGINT NOT NULL COMMENT \'userid\' ,\
                            market_id int(11) unsigned NOT NULL COMMENT \'市场id\' ,\
                            price DECIMAL(32,16) unsigned NOT NULL COMMENT \'交易价格\' ,\
                            trading_volume DECIMAL(32,16) NOT NULL COMMENT \'交易量\' ,\
                            traded_volume DECIMAL(32,16) NOT NULL COMMENT \'已成交数量\' ,\
                            trading_amount DECIMAL(32,16) NOT NULL COMMENT \'交易额\' ,\
                            estimated_fee DECIMAL(32,16) NOT NULL COMMENT \'预期手续费\' ,\
                            actual_fee DECIMAL(32,16) NOT NULL COMMENT \'真实手续费\' ,\
                            oper_type tinyint(2) unsigned NOT NULL COMMENT \'操作类型 1-买入；2-卖出\' ,\
                            status tinyint(2) unsigned NOT NULL COMMENT \'交易状态 0-交易未完成；1-交易已完成；2-撤销订单\' ,\
                            endtime int(11) unsigned NOT NULL COMMENT \'完成交易时间\' ,\
                            create_time int(11)  DEFAULT 0  COMMENT \'创建时间\' ,\
                            update_time int(11)  DEFAULT 0  COMMENT \'更新时间\' ,\
                            PRIMARY KEY (id)\
                            ) COMMENT = \'订单下单表\';;'
            database.excuteSQL(database.tradeDB_cursor, sqlCreateTable)

            sqlCreateTable2 = 'CREATE TABLE close_' + str(marketObj['id']) + '(\
                                        id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'id 无符号64长整型=[时间戳秒+自增int]\' ,\
                                        user_id BIGINT NOT NULL COMMENT \'userid\' ,\
                                        market_id int(11) unsigned NOT NULL COMMENT \'市场id\' ,\
                                        price DECIMAL(32,16) unsigned NOT NULL COMMENT \'交易价格\' ,\
                                        trading_volume DECIMAL(32,16) NOT NULL COMMENT \'交易量\' ,\
                                        traded_volume DECIMAL(32,16) NOT NULL COMMENT \'已成交数量\' ,\
                                        trading_amount DECIMAL(32,16) NOT NULL COMMENT \'交易额\' ,\
                                        estimated_fee DECIMAL(32,16) NOT NULL COMMENT \'预期手续费\' ,\
                                        actual_fee DECIMAL(32,16) NOT NULL COMMENT \'真实手续费\' ,\
                                        oper_type tinyint(2) unsigned NOT NULL COMMENT \'操作类型 1-买入；2-卖出\' ,\
                                        status tinyint(2) unsigned NOT NULL COMMENT \'交易状态 0-交易未完成；1-交易已完成；2-撤销订单\' ,\
                                        endtime int(11) unsigned NOT NULL COMMENT \'完成交易时间\' ,\
                                        create_time int(11)  DEFAULT 0  COMMENT \'创建时间\' ,\
                                        update_time int(11)  DEFAULT 0  COMMENT \'更新时间\' ,\
                                        PRIMARY KEY (id)\
                                        ) COMMENT = \'订单下单表\';;'
            database.excuteSQL(database.tradeDB_cursor, sqlCreateTable2)

    def loadTableWaitMarketData(self):
        for object in mappingList:
            searchUkexList = database.selectSQL(database.ukex_cursor,
                                                "id, market as market_id , price ,num as trading_volume , deal as traded_volume , mum as trading_amount , fee as estimated_fee , deal_fee as actual_fee,"
                                                "type as oper_type, status , endtime ,  addtime as create_time, updatetime as update_time",
                                                'coin_trade where userid = "' + str(object['ukex_uid']) + '"and status = 0;')
            if searchUkexList == None:
                continue
            for searchObj in searchUkexList:
                insertObj = {}
                insertObj['id'] = searchObj['id']
                insertObj['user_id'] = object['user_id']
                if searchObj['market_id'] == '':
                    continue
                insertObj['market_id'] = marketMapping[searchObj['market_id']]
                insertObj['price'] = searchObj['price']
                insertObj['trading_volume'] = searchObj['trading_volume']
                insertObj['traded_volume'] = searchObj['traded_volume']
                insertObj['trading_amount'] = searchObj['trading_amount']
                insertObj['estimated_fee'] = searchObj['estimated_fee']
                insertObj['actual_fee'] = searchObj['actual_fee']
                insertObj['oper_type'] = searchObj['oper_type']
                insertObj['status'] = searchObj['status']
                insertObj['endtime'] = searchObj['endtime']
                insertObj['create_time'] = searchObj['create_time']
                insertObj['update_time'] = searchObj['update_time']
                dbOper.insertToTrade('wait_'+str(insertObj['market_id']), [insertObj], dbOper.wait_close)
    def loadTableCloseMarketData(self):
        for object in mappingList:
            searchUkexList = database.selectSQL(database.ukex_cursor,
                                                "id, market as market_id , price ,num as trading_volume , deal as traded_volume , mum as trading_amount , fee as estimated_fee , deal_fee as actual_fee,"
                                                "type as oper_type, status , endtime ,  addtime as create_time, updatetime as update_time",
                                                'coin_trade where userid = "' + str(object['ukex_uid']) + '" and status != 0;')
            if searchUkexList == None:
                continue
            for searchObj in searchUkexList:
                insertObj = {}
                insertObj['id'] = searchObj['id']
                insertObj['user_id'] = object['user_id']
                if searchObj['market_id'] == '':
                    continue
                insertObj['market_id'] = marketMapping[searchObj['market_id']]
                insertObj['price'] = searchObj['price']
                insertObj['trading_volume'] = searchObj['trading_volume']
                insertObj['traded_volume'] = searchObj['traded_volume']
                insertObj['trading_amount'] = searchObj['trading_amount']
                insertObj['estimated_fee'] = searchObj['estimated_fee']
                insertObj['actual_fee'] = searchObj['actual_fee']
                insertObj['oper_type'] = searchObj['oper_type']
                insertObj['status'] = searchObj['status']
                insertObj['endtime'] = searchObj['endtime']
                insertObj['create_time'] = searchObj['create_time']
                insertObj['update_time'] = searchObj['update_time']
                dbOper.insertToTrade('close_' + str(insertObj['market_id']), [insertObj], dbOper.wait_close)

    def createAccountTables(self):
        sqlUser = 'CREATE TABLE `user` (\
                    `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT \'id 自增int\',\
                    `user_account` varchar(256) NOT NULL COMMENT \'用户名\',\
                    `password` varchar(64) NOT NULL COMMENT \'密码\',\
	                `source_type` tinyint(3) unsigned DEFAULT 0 COMMENT \'账号来源 1-ukex；2-ukexpay\' ,\
                    `login_attempts` int(11) unsigned NOT NULL COMMENT \'登录次数\',\
                    `login_time` int(11) unsigned DEFAULT 0 COMMENT \'登录时间\',\
                    `create_time` int(11) NULL DEFAULT 0 COMMENT \'创建时间\',\
                    `update_time` int(11) NULL DEFAULT 0 COMMENT \'更新时间\',\
                    PRIMARY KEY (`id`)\
                    ) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT=\'用户基础信息表\';'
        sqlUserAccount = 'CREATE TABLE `user_account` (\
                            `account` varchar(256) NOT NULL COMMENT \'用户账号\',\
                            `account_type` tinyint(3) unsigned DEFAULT 0 COMMENT \'证件类型 0-手机号码；1-邮箱；2-用户名\' ,\
	                        `source_type` tinyint(3) unsigned DEFAULT 0 COMMENT \'账号来源 1-ukex；2-ukexpay\' ,\
                            `user_id` bigint(20) NOT NULL COMMENT \'userid，用户在系统中唯一标志\',\
	                        `ukex_uid` bigint(20) DEFAULT 0 COMMENT \'ukex_uid，用户在ukex系统中唯一标志\',\
	                        `ukexpay_uid` bigint(20) DEFAULT 0 COMMENT \'ukexpay_uid，用户在ukexpay系统中唯一标志\',\
                            `create_time` int(11) NULL DEFAULT 0 COMMENT \'创建时间\',\
                            `update_time` int(11) NULL DEFAULT 0 COMMENT \'更新时间\',\
                            PRIMARY KEY (`account`)\
                            ) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT=\'用户账号信息表\';'
        sqlUserAuth = 'CREATE TABLE user_auth(\
                        user_id BIGINT NOT NULL COMMENT \'userid 自增int\' ,\
		                is_allow_login tinyint(1) unsigned DEFAULT 1 COMMENT \'是否允许登录 1-允许登录；0-不允许登录\',\
                        paypassword_status  tinyint(1) unsigned NOT NULL  COMMENT \'交易密码输入状态 0-关；1-开\' ,\
                        user_status tinyint(4) unsigned NOT NULL COMMENT \'用户状态 1-正常；0-冻结\' ,\
                        auth_status tinyint(2) DEFAULT 0 COMMENT \'身份验证 1-已验证；2-审核中；3-未通过；4-冻结KYC提交；0-未验证\' ,\
                        kyc_auth tinyint(1) unsigned DEFAULT 0 COMMENT \'kyc验证 1-已验证；2-审核中；3-未通过；4-冻结KYC提交；5-未通过不允许重新验证；0-未验证;\' ,\
                        email_auth tinyint(1) unsigned DEFAULT 0 COMMENT \'邮箱认证 1-已验证；0-未验证\' ,\
                        allow_openapi_withdrawal tinyint(1) unsigned NOT NULL COMMENT \'是否可以通过openid提现 1-允许；0不允许\' ,\
                        is_reauth tinyint(1) unsigned DEFAULT 0 COMMENT \'是否重新认证 1-已重新认证；0-未重新认证\' ,\
                        is_pass_aml tinyint(1) DEFAULT 0 COMMENT \'是否通过 aml 验证 1-通过；0-未通过；-1 认证失败\' ,\
                        register_type tinyint(3) unsigned DEFAULT 0 COMMENT \'注册类型 0-默认；1-邮箱；2-手机\' ,\
                        verify_type tinyint(3) unsigned DEFAULT 0 COMMENT \'验证方式 1-邮箱；2-手机\' ,\
                        global_kyc_status tinyint(3) unsigned DEFAULT 0 COMMENT \'国外 KYC 状态 0-待审核；1-已审核\' ,\
                        last_operate_time  int(11) unsigned DEFAULT 0 COMMENT \'最后一次操作时间 邮箱，手机号，登录密码，交易密码修改\' ,\
		                account_status tinyint(2) unsigned DEFAULT 0 COMMENT \'账户状态 -1:销户 0:未激活 1:正常\',\
		                os_verify tinyint(1) unsigned DEFAULT 0 COMMENT \'APP调用系统验证 0:否 1:是\',\
		                pin_verify tinyint(1) unsigned DEFAULT 0 COMMENT \'APP使用PIN码验证 0:否 1:是\',\
		                two_factor tinyint(1) unsigned DEFAULT 0 COMMENT \'双因子验证 0:否 1:是\',\
		                hide_balance tinyint(1) unsigned DEFAULT 0 COMMENT \'隐藏余额 0:否 1:是\',\
                        create_time int(11)  DEFAULT 0  COMMENT \'创建时间\' ,\
                        update_time int(11)  DEFAULT 0  COMMENT \'更新时间\' ,\
                        PRIMARY KEY (user_id)\
                        ) COMMENT = \'用户权限信息表 \';;'
        sqlUserFacts = 'CREATE TABLE user_facts(\
                            user_id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'用户 id 自增int\' ,\
                            first_name varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'真实姓\' ,\
                            last_name varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'真实名\' ,\
                            birthday int(11) DEFAULT 0 COMMENT \'生日\' ,\
                            country varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'居住地国家\' ,\
                            residence_country varchar(256) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT \'\' COMMENT \'居住地国籍\',\
                            province varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'所属省\' ,\
                            city  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'所属城市\' ,\
                            town  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'镇\' ,\
                            district varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'区\' ,\
                            street_address varchar(128) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'所属街道\' ,\
                            building_number varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT \'\' COMMENT \'建筑号\' ,\
                            building_name varchar(128) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT \'\' COMMENT \'建筑名\' ,\
                            sex tinyint(1) unsigned NOT NULL COMMENT \'性别 0-默认；1-男；2-女；3-未知\' ,\
                            zip_code varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'邮编\' ,\
                            apartment varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT \'\' COMMENT \'apartment\',\
                            first_residence_certificate varchar(256) NOT NULL COMMENT \'居住证明图1\' ,\
                            second_residence_certificate varchar(256) NOT NULL COMMENT \'居住证明图2\' ,\
                            street_code varchar(32) NOT NULL COMMENT \'街道号码\' ,\
                            unit  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'楼栋号(单元号)\' ,\
                            house_code varchar(32) NOT NULL COMMENT \'门牌号\' ,\
                            passport varchar(128) NOT NULL COMMENT \'护照号\' ,\
                            `has_deducted_gbp` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'visa开卡gbp是否已收费 1：已收 0：未收\',\
                            `has_deducted_eur` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'visa开卡eur是否收费 1：已收 0：未收\',\
                            `has_deducted_usd` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'visa开卡usd是否收费 1：已收 0：未收\',\
                            passport_ocr varchar(128) NOT NULL COMMENT \'护照 OCR 码\' ,\
                            passport_expire  varchar(32) NOT NULL COMMENT \'护照过期时间\' ,\
                            passport_picture varchar(256) NOT NULL COMMENT \'护照图 1\' ,\
                            passport_picture_hold varchar(256) NOT NULL COMMENT \'护照图 2(手持)\' ,\
                            driving_number varchar(128) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'驾照号\' ,\
                            driving_picture  varchar(256) NOT NULL COMMENT \'驾照图 1\' ,\
                            driving_picture_hold  varchar(256) NOT NULL COMMENT \'驾照图 2(手持)\' ,\
                            is_europe  tinyint(1) unsigned NOT NULL COMMENT \'是否欧盟成员国用户 0-不是；1-是\' ,\
                            nationality varchar(256) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'用户国籍\' ,\
                            create_time int(11)  DEFAULT 0  COMMENT \'创建时间\' ,\
                            update_time int(11)  DEFAULT 0  COMMENT \'更新时间\' ,\
                            PRIMARY KEY (user_id)\
                        ) COMMENT = \'用户信息扩展表 \';; '
        sqlUserInfo = 'CREATE TABLE user_info(\
                            user_id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'userid 自增int\' ,\
                            mobile varchar(64) NOT NULL COMMENT \'电话号码\' ,\
                            id_type tinyint(3) unsigned DEFAULT 0 COMMENT \'证件类型 0-身份证；1-护照；2-驾照\' ,\
                                identity_number varchar(128) NOT NULL COMMENT \'识别号码 与certificate_type字段对应\',\
                                identity_expiry_date varchar(60) NOT NULL DEFAULT \'\' COMMENT \'证件过期时间\',\
                                identity_info text COMMENT \'识别信息 与certificate_type字段对应 序列化存正、反、手持照的对象地址/id等\',\
                                paypassword varchar(100) NOT NULL COMMENT \'支付密码\' ,\
                            recommender_level1 varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'一级推荐人\' ,\
                            recommender_level2 varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'二级推荐人\' ,\
                            recommender_level3 varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'三级推荐人\' ,\
                                realname varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'真实姓名\' ,\
                                country varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT \'\' COMMENT \'国家\' ,\
                                c2c_info_ext text CHARACTER SET utf8 COLLATE utf8_general_ci COMMENT \'c2c身份认证字段\',\
                                ext text CHARACTER SET utf8 COLLATE utf8_general_ci COMMENT \'拓展字段\',\
                                invit_time int(11) unsigned DEFAULT 0 COMMENT \'推荐时间\',\
                                source_of_funds text  COMMENT \'资金来源\',\
                                mobile_binding_time int(11) unsigned NOT NULL COMMENT \'电话绑定时间\' ,\
                                id_number varchar(32) NOT NULL COMMENT \'身份证号\' ,\
                                ip_address varchar(64) NOT NULL COMMENT \'ip地址\' ,\
                                address_desc varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'地址描述\' ,\
                            email varchar(256) DEFAULT \'\' COMMENT \'邮箱\' ,\
                            wechat varchar(256) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT \'\' COMMENT \'微信名\' ,\
                            wechat_img  varchar(256) DEFAULT \'\' COMMENT \'微信头像\' ,\
                            wechat_openid  varchar(32) DEFAULT \'\' COMMENT \'微信openid\' ,\
                            alipay varchar(256) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT \'\'  COMMENT \'支付宝名\' ,\
                            alipay_img varchar(256) DEFAULT \'\' COMMENT \'支付宝头像\' ,\
                            invite_code varchar(64) NOT NULL COMMENT \'用户推荐码\' ,\
                            custom_cate_id int(11) unsigned DEFAULT 0 COMMENT \'自定义用户分类 id\' ,\
                            master_account  int(11) unsigned DEFAULT 0 COMMENT \'主账户id\' ,\
                            source_proj_uid int(11) unsigned DEFAULT 0 COMMENT \'源项目方uid\' ,\
                            uuid varchar(64) DEFAULT \'\' COMMENT \'api key\' ,\
                            uuid_salt varchar(16) DEFAULT \'\' COMMENT \'key 加密随机数\' ,\
                                user_image varchar(256) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'头像\',\
                                country_code varchar(32) NOT NULL COMMENT \'国别代码(电话前缀)\',\
                                user_type tinyint(2) NOT NULL COMMENT \'用户类型 0-无；1-user：用户 2-merchant：做市商\',\
                                account_active_time int(11) unsigned DEFAULT 0 COMMENT \'邮箱激活时间 未激活为0\',\
                                secret_key varchar(256) DEFAULT \'\' COMMENT \'双因子密钥\',\
                                refer_currency int(11) unsigned  DEFAULT 0 COMMENT \'兑价币id\',\
                                kyc_refuse_num tinyint(2) unsigned  DEFAULT 0 COMMENT \'kyc拒绝次数\',\
                                lucky_count int(11) unsigned NOT NULL DEFAULT 0 COMMENT \'推荐成功次数\',\
                                c2c_refuse_num tinyint(2) unsigned DEFAULT 0 COMMENT \'c2c交易认证拒绝次数\',\
                                rescue_code varchar(32) DEFAULT \'\' COMMENT \'救援码（用户ga解绑）\',\
                            create_time int(11)  DEFAULT 0  COMMENT \'创建时间\' ,\
                            update_time int(11)  DEFAULT 0  COMMENT \'更新时间\' ,\
                            PRIMARY KEY (user_id)\
                        ) COMMENT = \'用户信息表 \';;'
        sqlUserLog = 'CREATE TABLE user_log(\
                        id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'自增int\' ,\
                            user_id BIGINT COMMENT \'userid\' ,\
                            oper_type int(10) unsigned NOT NULL COMMENT \'操作类型\' ,\
                            log text  COMMENT \'操作数据内容\',\
                            create_time int(11)  DEFAULT 0  COMMENT \'创建时间\' ,\
                        PRIMARY KEY (id)\
                    ) COMMENT = \'用户操作日志表\';;'
        database.excuteSQL(database.accountDB_cursor, sqlUser)
        database.excuteSQL(database.accountDB_cursor, sqlUserAccount)
        database.excuteSQL(database.accountDB_cursor, sqlUserAuth)
        database.excuteSQL(database.accountDB_cursor, sqlUserFacts)
        database.excuteSQL(database.accountDB_cursor, sqlUserInfo)
        database.excuteSQL(database.accountDB_cursor, sqlUserLog)

    def createAssetsTables(self):
        sqlRecommand = 'DROP TABLE IF EXISTS `recommended_trade_award`;\
                        CREATE TABLE recommended_trade_award(\
                            id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'id 无符号64长整型=[时间戳秒+自增int]\' ,\
                            user_id BIGINT NOT NULL COMMENT \'userid\' ,\
                            recommender_id int(11) unsigned NOT NULL COMMENT \'推荐用户id 带给userid用户收益的用户\' ,\
                            market_id int(11) unsigned NOT NULL COMMENT \'市场id\' ,\
                            oper_type tinyint(3) unsigned NOT NULL COMMENT \'操作类型 1-买入；2-卖出\' ,\
                            coin_id  int(11) unsigned NOT NULL COMMENT \'奖励币种 id\' ,\
                            trading_volume DECIMAL(32,16) unsigned NOT NULL COMMENT \'交易量\' ,\
                            trading_amount DECIMAL(32,16) unsigned NOT NULL COMMENT \'交易额\' ,\
                            profit DECIMAL(32,16) unsigned NOT NULL COMMENT \'收益\' ,\
                            create_time int(11)  DEFAULT 0  COMMENT \'创建时间\' ,\
                        `update_time` int(11) NULL DEFAULT 0 COMMENT \'更新时间\',\
                            PRIMARY KEY (id)\
                        ) COMMENT = \'推荐奖励表\';;'
        database.excuteSQL(database.assetsDB_cursor, sqlRecommand)

    def createSATables(self):
        sqlFRecord = 'DROP TABLE IF EXISTS `financial_records`;\
                    CREATE TABLE financial_records(\
                        id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'id 无符号64长整型=[时间戳秒+自增int]\' ,\
                        user_id BIGINT NOT NULL COMMENT \'用户id\' ,\
                        coin_id int(11) unsigned NOT NULL COMMENT \'币种 id\' ,\
                        gross_amount DECIMAL(32,16) unsigned NOT NULL COMMENT \'交易前资产总额\' ,\
                        gross_frozen DECIMAL(32,16) unsigned NOT NULL COMMENT \'交易前冻结资产\' ,\
                        gross_sum DECIMAL(32,16) unsigned NOT NULL COMMENT \'交易前资产总计\' ,\
                        fee DECIMAL(32,16) NOT NULL COMMENT \'可用变动\' ,\
                        fee_frozen DECIMAL(32,16) NOT NULL COMMENT \'冻结变动\' ,\
                        oper_type tinyint(4) unsigned NOT NULL COMMENT \'操作类型 1.交易买入 2.交易卖出 3.法币充值 4.法币提现 5.交易奖励 6.交易手续费 7.c2c打款 8.c2c收款 9.交易转出 10.交易转入 11.提现手续费 12.转出手续费 13.系统充值 14.冻结释放 15.挖矿（暂无） 16.服务费 17.项目方归集 18.三方otoc交易\' ,\
                        oper_id int(11) unsigned NOT NULL COMMENT \'操作标识\' ,\
                        oper_desc varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT \'操作备注\' ,\
                        remaining_amount DECIMAL(32,16) unsigned NOT NULL COMMENT \'剩余正常\' ,\
                        remaining_frozen DECIMAL(32,16) unsigned NOT NULL COMMENT \'剩余冻结\' ,\
                        remaining_sum DECIMAL(32,16) unsigned NOT NULL COMMENT \'剩余总计\' ,\
                        record_hash  varchar(64) NOT NULL COMMENT \'防篡改唯一标识\' ,\
                        status  tinyint(4) unsigned NOT NULL COMMENT \'状态 0 未校验 1 正常 2 异常 3 已对账 4：最后一条数据标记(分表)\' ,\
                        create_time int(11) DEFAULT 0 COMMENT \'创建时间\' ,\
                        update_time int(11) DEFAULT 0 COMMENT \'更新时间\' ,\
                        PRIMARY KEY (id)\
                    ) COMMENT = \'财务记录表\';;'

        sqlKlineMin = 'DROP TABLE IF EXISTS `kline_minimum`;\
                        CREATE TABLE kline_minimum(\
                            id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'id 无符号64长整型=[时间戳秒+自增int]\' ,\
                            market_id int(11) unsigned NOT NULL COMMENT \'市场id\' ,\
                            begin_time int(11) unsigned NOT NULL COMMENT \'K线开始时间\' ,\
                            open DECIMAL(32,16)  NULL COMMENT \'开启价\' ,\
                            high DECIMAL(32,16)  NULL COMMENT \'最高价\' ,\
                            low DECIMAL(32,16)  NULL COMMENT \'最低价\' ,\
                            close DECIMAL(32,16)  NULL COMMENT \'收价\' ,\
                            trading_volume DECIMAL(32,16) unsigned COMMENT \'成交量\' ,\
                            create_time int(11) DEFAULT 0 COMMENT \'创建时间\' ,\
                            update_time int(11) DEFAULT 0 COMMENT \'更新时间\' ,\
                            PRIMARY KEY (id)\
                        ) COMMENT = \'最小K线图表 \';;'

        sqlKlineRecord = 'DROP TABLE IF EXISTS `kline_record`;\
                        CREATE TABLE kline_record(\
                            id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'id 无符号64长整型=[时间戳秒+自增int]\' ,\
                            market_id int(11) unsigned NOT NULL COMMENT \'市场id\' ,\
                            Kline_type varchar(128) NOT NULL COMMENT \'K线时间类型 5-5分钟，15-15分钟，30-30分钟，60-60分钟，360-360分钟，1440-1440分钟，10080-10080分钟，43200-43200分钟\' ,\
                            begin_time int(11) unsigned NOT NULL COMMENT \'K线开始时间\' ,\
                            trading_volume DECIMAL(32,16) NULL COMMENT \'K线成交量\' ,\
                            open DECIMAL(32,16)  NULL COMMENT \'开启价\' ,\
                            high DECIMAL(32,16)  NULL COMMENT \'最高价\' ,\
                            low DECIMAL(32,16) NULL COMMENT \'最低价\' ,\
                            close DECIMAL(32,16)  NULL COMMENT \'收价\' ,\
                            create_time int(11) DEFAULT 0 COMMENT \'创建时间\' ,\
                            update_time int(11) DEFAULT 0 COMMENT \'更新时间\' ,\
                            PRIMARY KEY (id)\
                        ) COMMENT = \'K线记录表 记录非最小时间刻度的所有K线信息\';;'
        database.excuteSQL(database.SADB_cursor, sqlFRecord)
        database.excuteSQL(database.SADB_cursor, sqlKlineMin)
        database.excuteSQL(database.SADB_cursor, sqlKlineRecord)

    def createTradeTables(self):
        return
    def createTradeLog(self):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                cur = con.cursor()
                for table in Match_Year.keys():
                    cur.execute("create database Match_" + table + " character set utf8;")
                    for tableName in Match_Year[table]:
                        cur.execute("use Match_" + table + ";")
                        sqlCreateTable = 'CREATE TABLE ' + tableName + ' (\
                                        id BIGINT NOT NULL AUTO_INCREMENT  COMMENT \'id 无符号64长整型=[时间戳秒+自增int]\' ,\
                                        buyer_user_id BIGINT NOT NULL COMMENT \'买方userid\' ,\
                                        seller_user_id BIGINT NOT NULL COMMENT \'卖方userid\' ,\
                                        market_id int(11) unsigned NOT NULL COMMENT \'市场id\' ,\
                                        price DECIMAL(32,16)  NOT NULL COMMENT \'交易价格\' ,\
                                        trading_volume DECIMAL(32,16)  NOT NULL COMMENT \'交易量\' ,\
                                        trading_amount DECIMAL(32,16)  NOT NULL COMMENT \'交易额\' ,\
                                        buyer_fee DECIMAL(32,16)  NOT NULL COMMENT \'买方手续费\' ,\
                                        seller_fee DECIMAL(32,16)  NOT NULL COMMENT \'卖方手续费\' ,\
                                        oper_type tinyint(2) unsigned NOT NULL COMMENT \'操作类型 1-买入；2-卖出\' ,\
                                        buyer_order_id BIGINT NOT NULL COMMENT \'买方挂单id 对应trade交易表中的id\' ,\
                                        seller_order_id BIGINT NOT NULL COMMENT \'卖方挂单id 对应trade交易表中的id\' ,\
                                            create_time int(11)  DEFAULT 0  COMMENT \'创建时间\' ,\
                                        update_time int(11)  DEFAULT 0  COMMENT \'更新时间\' ,\
                                        PRIMARY KEY (id)\
                                    ) COMMENT = \'成交记录表\';;;'
                        cur.execute(sqlCreateTable)
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()

    def loadTableTradeLogData(self):
        dbConfid = Config()
        list = ['id','buyer_user_id','seller_user_id','market_id','price','trading_volume','trading_amount','buyer_fee','seller_fee','oper_type','buyer_order_id','seller_order_id','create_time','update_time']
        for year in Match_Year.keys():
            conn = None
            try:
                if conn is None:
                    conn = MySQLdb.connect(host=dbConfid.accountDB_dbAddress, \
                                                     user=dbConfid.accountDB_userName, \
                                                     passwd=dbConfid.accountDB_password, \
                                                     db=str('Match_'+year), \
                                                     cursorclass=MySQLdb.cursors.DictCursor)
                    cursor = conn.cursor()
                    conn.set_character_set('utf8')
                    cursor.execute('SET NAMES utf8;')
                    cursor.execute('SET CHARACTER SET utf8;')
                    cursor.execute('SET character_set_connection=utf8;')

                    for tradeLogObj in tradeDataList:
                        insertObj = {}
                        timeStamp = tradeLogObj['create_time']
                        timeArray = time.localtime(timeStamp)
                        if year != str(timeArray.tm_year):
                            continue
                        tableName = str(timeArray.tm_mon) + '_' + str(timeArray.tm_mday)
                        insertObj['id'] = tradeLogObj['id']
                        insertObj['buyer_user_id'] = tradeLogObj['buyer_user_id']
                        insertObj['seller_user_id'] = tradeLogObj['seller_user_id']
                        for obj in mappingList:
                            if obj['ukex_uid'] == tradeLogObj['buyer_user_id']:
                                insertObj['buyer_user_id'] = obj['user_id']
                            if obj['ukex_uid'] == tradeLogObj['seller_user_id']:
                                insertObj['seller_user_id'] = obj['user_id']
                        insertObj['market_id'] = marketMapping[tradeLogObj['market_id']]
                        insertObj['price'] = tradeLogObj['price']
                        insertObj['trading_volume'] = tradeLogObj['trading_volume']
                        insertObj['trading_amount'] = tradeLogObj['trading_amount']
                        insertObj['buyer_fee'] = tradeLogObj['buyer_fee']
                        insertObj['seller_fee'] = tradeLogObj['seller_fee']
                        insertObj['oper_type'] = tradeLogObj['oper_type']
                        insertObj['buyer_order_id'] = tradeLogObj['buyer_order_id']
                        insertObj['seller_order_id'] = tradeLogObj['seller_order_id']
                        insertObj['create_time'] = tradeLogObj['create_time']
                        insertObj['update_time'] = tradeLogObj['update_time']
                        tableColumns = self.makeInsertPackage(insertObj, list, tableName)
                        print ('INSERT INTO ' + tableColumns)
                        cursor.execute('INSERT INTO ' + tableColumns)
                        conn.commit()
            except:
                import traceback
                traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
                traceback.print_exc()

    def createBaseTables(self):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                cur = con.cursor()
                cur.execute("create database account character set utf8;")
                cur.execute("create database assets character set utf8;")
                cur.execute("create database sa character set utf8;")
                cur.execute("create database trade character set utf8;")
                cur.execute("create database base character set utf8;")
                cur.execute("create database admin character set utf8;")
                cur.execute("create database kyc character set utf8;")
                cur.execute("create database exassets character set utf8;")
                cur.execute("create database otc character set utf8;")
                cur.execute("create database other character set utf8;")
                cur.execute("use base;")
                # cur.execute("drop table coin_country;")
                cur.execute("CREATE TABLE `coin_country` (\
                                             `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                             `country_en` varchar(200) NOT NULL DEFAULT \'\',\
                                             `country_cn` varchar(200) NOT NULL DEFAULT \'\',\
                                             `code` varchar(20) NOT NULL DEFAULT \'\',\
                                             `mcode` varchar(10) NOT NULL DEFAULT \'\' COMMENT \'手机区号\',\
                                             `number` varchar(10) NOT NULL DEFAULT \'000\' COMMENT \'ISO code\',\
                                             `is_oumeng` tinyint(3) unsigned NOT NULL DEFAULT \'0\' COMMENT \'是否欧盟成员国\',\
                                             `is_eaa` tinyint(3) NOT NULL DEFAULT \'0\' COMMENT \'是否欧盟欧洲经济区国家\',\
                                             `is_forbidden` tinyint(3) NOT NULL DEFAULT \'0\' COMMENT \'是否禁止\',\
                                             `remark_1` varchar(200) NOT NULL DEFAULT \'\',\
                                             `remark_2` varchar(200) NOT NULL DEFAULT \'\',\
                                             `remark_3` varchar(200) NOT NULL DEFAULT \'\',\
                                             PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=245 DEFAULT CHARSET=utf8 COMMENT=\'国家记录表\';")
                # cur.execute("drop table coin_currency_config;")
                cur.execute("CREATE TABLE `coin_currency_config` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT COMMENT \'配置 id\',\
                                            `currency` varchar(30) COLLATE utf8_unicode_ci NOT NULL DEFAULT \'\' COMMENT \'法定货币类型\',\
                                            `name` varchar(60) COLLATE utf8_unicode_ci NOT NULL COMMENT \'名称\',\
                                            `symbol` varchar(10) COLLATE utf8_unicode_ci NOT NULL DEFAULT \'\' COMMENT \'货币符号\',\
                                            `tx_min` decimal(32,16) NOT NULL DEFAULT \'0.00000000\' COMMENT \'最小提现金额\',\
                                            `tx_max` decimal(32,16) NOT NULL DEFAULT \'0.00000000\' COMMENT \'最大提现金额\',\
                                            `tx_multiple` tinyint(3) NOT NULL DEFAULT \'1\' COMMENT \'提现整数倍\',\
                                            `tx_min_fee` decimal(32,16) NOT NULL DEFAULT \'0.00000000\' COMMENT \'最小提现手续费\',\
                                            `tx_fee` decimal(32,16) NOT NULL DEFAULT \'0.00000000\' COMMENT \'提现手续费\',\
                                            `sort` tinyint(3) NOT NULL DEFAULT \'0\' COMMENT \'排序\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'状态 1 可用 0 不可用\',\
                                            `platform_userid` int(11) NOT NULL DEFAULT \'0\' COMMENT \'平台账户 userid\',\
                                            `platform_fee_userid` int(11) NOT NULL DEFAULT \'0\' COMMENT \'平台手续费账户 userid\',\
                                            `day_tx_num` decimal(32,16) DEFAULT \'0.00000000\' COMMENT \'单日提现数量\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;")
                # cur.execute("drop table coin_coin;")
                cur.execute("CREATE TABLE `coin_coin` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `name` varchar(50) NOT NULL,\
                                            `type` varchar(50) NOT NULL COMMENT \'币种类型： rgb (认购币) qbb(钱包币) cxb(创新币) \',\
                                            `title` varchar(50) NOT NULL COMMENT \'中文名称 \',\
                                            `img` varchar(50) NOT NULL,\
                                            `img_ext1` varchar(50) DEFAULT NULL COMMENT \'币种扩展图标 1\',\
                                            `app_img` varchar(50) NOT NULL COMMENT \'app 使用图标\',\
                                            `sort` int(11) unsigned DEFAULT \'0\' COMMENT \'显示顺序 \' ,\
                                            `fee_bili` varchar(50) NOT NULL COMMENT \'挂单比例 \',\
                                            `endtime` int(11) unsigned DEFAULT \'0\',\
                                            `addtime` int(11) unsigned DEFAULT \'0\',\
                                            `status` int(4) unsigned DEFAULT \'0\',\
                                            `fee_meitian` varchar(200) NOT NULL COMMENT \'每天限制\',\
                                            `dj_zj` varchar(200) NOT NULL COMMENT \'钱包服务器ip \',\
                                            `dj_dk` varchar(200) NOT NULL COMMENT \'钱包服务器端口 \',\
                                            `dj_yh` varchar(200) NOT NULL COMMENT \'钱包服务器用户名 \',\
                                            `dj_mm` varchar(200) NOT NULL COMMENT \'钱包服务器密码 \',\
                                            `zr_zs` decimal(32,16) NOT NULL COMMENT \'转入赠送 \',\
                                            `zr_jz` varchar(50) NOT NULL COMMENT \'转入状态 \',\
                                            `zr_dz` varchar(50) NOT NULL COMMENT \'确认次数 \',\
                                            `zr_sm` varchar(50) DEFAULT \'\' COMMENT \'转入说明 \',\
                                            `zc_sm` varchar(50) DEFAULT \'\' COMMENT \'转出说明 \',\
                                            `zc_fee` decimal(32,16) DEFAULT \'0.00000000\' COMMENT \'转出手续费 \',\
                                            `zc_mfee` decimal(32,16) DEFAULT \'0.00000000\' COMMENT \'最低手续费\',\
                                            `zc_user` varchar(200) DEFAULT \'\' COMMENT \'官方手续费地址[重要] \',\
                                            `zc_min` decimal(32,16) NOT NULL COMMENT \'最小转出数量 \',\
                                            `zc_min_zn` decimal(32,16) NOT NULL DEFAULT \'0.00000100\' COMMENT \'站内最小转出数量\',\
                                            `zc_max` decimal(32,16) NOT NULL COMMENT \'最大转出数量 \',\
                                            `zc_jz` varchar(50) NOT NULL COMMENT \'转出状态 \',\
                                            `zc_zd` decimal(32,16) NOT NULL DEFAULT \'0.00000000\' COMMENT \'单笔自动转出限额\',\
                                            `js_yw` varchar(50) NOT NULL COMMENT \'英文名称 \',\
                                            `js_sm` text NOT NULL COMMENT \'币种资料(URL) \',\
                                            `js_qb` varchar(50) NOT NULL COMMENT \'钱包下载 \',\
                                            `js_ym` varchar(50) NOT NULL COMMENT \'源码下载 \',\
                                            `js_gw` varchar(50) NOT NULL COMMENT \'官方链接 \',\
                                            `js_lt` varchar(50) NOT NULL COMMENT \'官方论坛 \',\
                                            `js_wk` varchar(50) NOT NULL COMMENT \'官方挖矿 \',\
                                            `cs_yf` varchar(50) NOT NULL COMMENT \'研发者 \',\
                                            `cs_sf` varchar(50) NOT NULL COMMENT \'核心算法 \',\
                                            `cs_fb` varchar(50) NOT NULL COMMENT \'发布日期 \',\
                                            `cs_qk` varchar(50) NOT NULL COMMENT \'区块速度 \',\
                                            `cs_zl` decimal(32,16) NOT NULL COMMENT \'发行总量 \',\
                                            `cs_cl` decimal(32,16) NOT NULL COMMENT \'存量 \',\
                                            `cs_zm` varchar(50) NOT NULL COMMENT \'证明方式 \',\
                                            `cs_nd` varchar(50) NOT NULL COMMENT \'难度调整 \',\
                                            `cs_jl` decimal(32,16) NOT NULL COMMENT \'区块奖励 \',\
                                            `cs_ts` varchar(50) NOT NULL COMMENT \'主要特色 \',\
                                            `cs_bz` varchar(50) NOT NULL COMMENT \'不足之处 \',\
                                            `zc_wtdays` int(4) DEFAULT NULL COMMENT \'委托转账最大托管天数 \',\
                                            `zr_tips` varchar(1000) DEFAULT NULL COMMENT \'转入提示\',\
                                            `zc_tips` varchar(1000) DEFAULT NULL COMMENT \'转出提示\',\
                                            `auto_zc_day_num` decimal(32,16) DEFAULT \'0.00000000\' COMMENT \'当日自动转出限额\',\
                                            `auto_zc_rate` decimal(32,16) DEFAULT \'100\' COMMENT \'自动转出盈利率限额\',\
                                            `is_split_addr` tinyint(1) DEFAULT \'0\' COMMENT \'是否分离集成地址 0 未分离 1 分离\',\
                                            `is_usable_integra` tinyint(1) DEFAULT \'1\' COMMENT \'集成地址是否可用于转账 1 可用 0 不可用\',\
                                            `main_coin` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT \'主链币种\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `name` (`name`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=120 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT=\'币种配置表\'")
                # cur.execute("drop table coin_coin_ext;")
                cur.execute("CREATE TABLE `coin_coin_ext` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `coin_id` int(11) NOT NULL COMMENT \'币种 id\',\
                                            `name` varchar(30) DEFAULT NULL COMMENT \'币种名称\',\
                                            `main_coin` varchar(200) DEFAULT NULL COMMENT \'主链对应币种，如 usdt 的 eth 主链\',\
                                            `main_coin_name` varchar(30) DEFAULT NULL COMMENT '主链协议名称',\
                                            `zc_fee` decimal(32,16) DEFAULT NULL COMMENT \'转出手续费%\',\
                                            `zc_mfee` decimal(32,16) DEFAULT NULL COMMENT \'转账最小手续费\',\
                                            `zc_min` decimal(32,16) DEFAULT NULL COMMENT \'最小转出量\',\
                                            `zc_max` decimal(32,16) DEFAULT NULL COMMENT \'最大转出量\',\
                                            `is_split_addr` tinyint(1) DEFAULT NULL COMMENT \'是否是分离地址类型 1： 是 0 ：否\',\
                                            `is_usable_integra` tinyint(1) DEFAULT NULL COMMENT \'集成地址是否可用 1：可用 0：不可用\',\
                                            `update_time` int(11) DEFAULT NULL COMMENT \'最后更新时间\',\
                                            `status` tinyint(1) DEFAULT NULL COMMENT \'状态，1：正常 2：禁用\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COMMENT=\'扩展币种配置表，绑定主链币种\'")
                # cur.execute("drop table coin_vip;")
                cur.execute("CREATE TABLE `coin_vip` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `name` varchar(30) COLLATE utf8_unicode_ci NOT NULL COMMENT \'等级名称\',\
                                            `level` tinyint(2) NOT NULL COMMENT \'等级数\',\
                                            `min` int(10) NOT NULL DEFAULT \'0\' COMMENT \'范围最小值\',\
                                            `max` int(10) NOT NULL COMMENT \'范围最大值，如果为 null 这表示无上限\',\
                                            `discount` decimal(3,2) unsigned NOT NULL DEFAULT \'1.00\' COMMENT \'折扣值 eg:0.8（8 折）, 0.95（95 折）\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'可用状态 1 ：可用 0 不可用\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci")
                # cur.execute("drop table coin_vip_user;")
                cur.execute("CREATE TABLE `coin_vip_user` (\
                                            `userid` int(11) NOT NULL COMMENT \'用户 id\',\
                                            `level` tinyint(2) NOT NULL DEFAULT \'0\' COMMENT \'vip 等级\',\
                                            `update_time` int(11) NOT NULL DEFAULT \'0\' COMMENT \'最后更新时间\',\
                                            PRIMARY KEY (`userid`),\
                                            UNIQUE KEY `userid` (`userid`) \
                                            USING BTREE \
                            ) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci")
                # cur.execute("drop table coin_visa_config;")
                cur.execute("CREATE TABLE `coin_visa_config` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT COMMENT \'配置 id\',\
                                            `name` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT \'名称\',\
                                            `currency` varchar(30) COLLATE utf8_unicode_ci NOT NULL DEFAULT \'\' COMMENT \'法定货币类型\',\
                                            `symbol` varchar(10) COLLATE utf8_unicode_ci NOT NULL DEFAULT \'\' COMMENT \'货币符号\',\
                                            `charge` decimal(32,16) NOT NULL DEFAULT \'0.00\' COMMENT \'月服务费\',\
                                            `fee_userid` int(11) NOT NULL DEFAULT '0' COMMENT '平台手续费收款账户',\
                                            `fee` decimal(32,16) NOT NULL DEFAULT \'0.00\' COMMENT \'提现手续费 0.2 代表 0.2%\',\
                                            `open_fee` decimal(32,16) NOT NULL DEFAULT \'0.00\' COMMENT \'开卡手续费\',\
                                            `open_fee_coin_img` varchar(100) COLLATE utf8_unicode_ci NOT NULL DEFAULT \'\' COMMENT \'开卡收费币种图标\',\
                                            `or_open_fee_coin` varchar(30) COLLATE utf8_unicode_ci NOT NULL DEFAULT \'\' COMMENT \'或开卡收费币种\',\
                                            `or_open_fee` decimal(32,16) NOT NULL DEFAULT \'0.00\' COMMENT \'或开卡收费币种费用\',\
                                            `or_open_fee_coin_img` varchar(100) COLLATE utf8_unicode_ci NOT NULL DEFAULT \'\' COMMENT \'或开卡收费币种图标\',\
                                            `status` tinyint(3) NOT NULL DEFAULT \'0\' COMMENT \'状态：1 启用，0 禁用\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci")
                # cur.execute("drop table coin_user_bank_type;")
                cur.execute("CREATE TABLE `coin_user_bank_type` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `name` varchar(200) NOT NULL,\
                                            `title` varchar(200) NOT NULL,\
                                            `url` varchar(200) NOT NULL,\
                                            `img` varchar(200) NOT NULL,\
                                            `mytx` varchar(200) NOT NULL,\
                                            `remark` varchar(50) NOT NULL,\
                                            `sort` int(11) unsigned NOT NULL,\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `endtime` int(11) unsigned NOT NULL,\
                                            `status` int(4) NOT NULL,\
                                            PRIMARY KEY (`id`),\
                                            KEY `status` (`status`), \
                                            KEY `name` (`name`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT=\'常用银行地址\'")
                cur.execute("use admin;")
                # cur.execute("drop table coin_count_fee;")
                cur.execute("CREATE TABLE `coin_count_fee` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `date` int(11) DEFAULT \'0\' COMMENT \'日期\',\
                                            `coinname` varchar(20) DEFAULT \'\' COMMENT \'币\',\
                                            `balance` decimal(32,16) unsigned DEFAULT NULL COMMENT \'当日存量\',\
                                            `coin_zr` decimal(32,16) unsigned DEFAULT NULL COMMENT \'当日充入\',\
                                            `coin_zc` decimal(32,16) unsigned DEFAULT NULL COMMENT \'当日提币\',\
                                            `coin_zc_coin_fee` decimal(32,16) unsigned DEFAULT NULL COMMENT \'当日链上手续费\',\
                                            `coin_zc_coin_fee_total` decimal(32,16) unsigned DEFAULT NULL COMMENT \'链上累计余额\',\
                                            `coin_zc_fee` decimal(32,16) unsigned DEFAULT NULL COMMENT \'当日提币手续费\',\
                                            `coin_zc_fee_total` decimal(32,16) unsigned DEFAULT NULL COMMENT \'提币手续费累计余额\',\
                                            `trade_fee` decimal(32,16) unsigned DEFAULT NULL COMMENT \'交易手续费\',\
                                            `trade_fee_total` decimal(32,16) unsigned DEFAULT NULL COMMENT \'交易手续费 累计余额\',\
                                            `fee_total` decimal(32,16) unsigned DEFAULT NULL COMMENT \'手续费合计\',\
                                            `coin_price` decimal(32,16) unsigned DEFAULT NULL COMMENT \'币价\',\
                                            `coin_price_total` decimal(32,16) unsigned DEFAULT NULL COMMENT \'总收入\',\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=utf8")
                # cur.execute("drop table coin_count_trade;")
                cur.execute("CREATE TABLE `coin_count_trade` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `date` int(11) NOT NULL DEFAULT \'0\' COMMENT \'日期\',\
                                            `coin_a` varchar(20) NOT NULL DEFAULT \'\' COMMENT \'coin_a\',\
                                            `coin_b` varchar(20) NOT NULL DEFAULT \'\' COMMENT \'coin_b\',\
                                            `market` varchar(50) NOT NULL DEFAULT \'\' COMMENT \'市场\',\
                                            `price_cny` decimal(32,16) unsigned NOT NULL COMMENT \'价格\',\
                                            `num` decimal(32,16) unsigned NOT NULL,\
                                            `mum` decimal(32,16) unsigned NOT NULL,\
                                            `fee` decimal(32,16) unsigned NOT NULL,\
                                            `fee_gbp` decimal(32,16) unsigned NOT NULL,\
                                            `amount_cny` decimal(32,16) unsigned NOT NULL,\
                                            `amount_gbp` decimal(32,16) unsigned NOT NULL,\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8")
                # cur.execute("drop table coin_cxb_apply;")
                cur.execute("CREATE TABLE `coin_cxb_apply` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `user_id` int(11) NOT NULL DEFAULT \'0\' COMMENT \'申请发起人 id\',\
                                            `user_name` varchar(100) NOT NULL DEFAULT \'\' COMMENT \'用户名\',\
                                            `email` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'邮箱\',\
                                            `token_name` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'token 名称\',\
                                            `token_symbol` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'token 标志 logo\',\
                                            `official_website` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'官方网站地址\',\
                                            `white_apper_url` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'白皮书链接\',\
                                            `token_standard` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'token 标准\',\
                                            `token_addr` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'token 私有链接地址\',\
                                            `token_decimal` varchar(2) NOT NULL DEFAULT \'\' COMMENT \'token 小数位数\',\
                                            `token_issue_date` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'token 发行日期\',\
                                            `token_max_number` decimal(32,16) NOT NULL DEFAULT \'0.0\' COMMENT \'最大供应数量\',\
                                            `token_circulating_number` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'循环数量 Provide the number of circulating supply\',\
                                            `token_description` text NOT NULL COMMENT \'token 项目描述\',\
                                            `token_audit_report` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'智能合约安全审计报告文件地址\',\
                                            `coinmarketcap_line` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'coinmarketcap_line\',\
                                            `contact_info` text NOT NULL COMMENT \'联系信息\',\
                                            `token_parameters` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'eth token 参数\',\
                                            `mag` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'返回状态信息\',\
                                            `main_line_time` varchar(50) NOT NULL DEFAULT \'\' COMMENT \'主网上线时间\',\
                                            `media_group` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'社交媒体和群组\',\
                                            `exchanges_online` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'已经上线的交易所\',\
                                            `addtime` int(11) NOT NULL DEFAULT \'0\' COMMENT \'申请时间\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'申请状态 0：申请中 1：成功正在处理，2：发行完成，-1 ：拒绝\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 COMMENT=\'创新币申请表\'")
                # cur.execute("drop table coin_finance_tally;")
                cur.execute("CREATE TABLE `coin_finance_tally` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT \'自增 id\',\
                                            `userid` int(11) unsigned NOT NULL COMMENT \'借款用户 id\',\
                                            `adminid` int(11) unsigned NOT NULL COMMENT \'操作管理员 id\',\
                                            `coin_id` int(11) NOT NULL DEFAULT \'0\' COMMENT \'币种 id\',\
                                            `coinname` varchar(50) NOT NULL COMMENT \'币种名称\',\
                                            `amount` decimal(32,16) unsigned NOT NULL COMMENT \'借款金额数量\',\
                                            `remark` varchar(200) NOT NULL DEFAULT \'\' COMMENT \'备注\',\
                                            `ip` varchar(30) NOT NULL DEFAULT \'\',\
                                            `addtime` int(11) unsigned NOT NULL COMMENT \'添加时间\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `userid` (`userid`),\
                                            KEY `coinname` (`coinname`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=426 DEFAULT CHARSET=utf8 COMMENT=\'财务操作记录表\'")
                # cur.execute("drop table coin_admin;")
                cur.execute("CREATE TABLE `coin_admin` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `email` varchar(200) NOT NULL,\
                                            `username` char(16) NOT NULL,\
                                            `nickname` varchar(50) NOT NULL,\
                                            `moble` varchar(50) NOT NULL,\
                                            `password` char(32) NOT NULL,\
                                            `sort` int(11) unsigned NOT NULL,\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `last_login_time` int(11) unsigned NOT NULL,\
                                            `last_login_ip` int(11) unsigned NOT NULL,\
                                            `endtime` int(11) unsigned NOT NULL,\
                                            `status` int(4) NOT NULL,\
                                            `is_notice_tx1` tinyint(3) unsigned NOT NULL DEFAULT \'0\' ,\
                                            `is_notice_tx2` tinyint(3) unsigned NOT NULL DEFAULT \'0\' ,\
                                            `is_notice_sm` tinyint(3) unsigned NOT NULL DEFAULT \'0\',\
                                            `is_notice_bs` tinyint(3) NOT NULL DEFAULT \'0\',\
                                            `is_notice_mycz` tinyint(3) unsigned NOT NULL DEFAULT \'0\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `status` (`status`), \
                                            KEY `username` (`username`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT=\'管理员表\'")
                # cur.execute("drop table coin_admin_log;")
                cur.execute("CREATE TABLE `coin_admin_log` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `adminid` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `rowid` int(11) DEFAULT NULL,\
                                            `type` varchar(200) NOT NULL DEFAULT \'\',\
                                            `remark` varchar(200) NOT NULL DEFAULT \'\',\
                                            `addip` varchar(200) NOT NULL DEFAULT \'\',\
                                            `addr` varchar(200) NOT NULL DEFAULT \'\',\
                                            `addtime` int(10) unsigned NOT NULL DEFAULT \'0\',\
                                            `status` tinyint(4) NOT NULL DEFAULT \'1\',\
                                            `data` text COMMENT \'记录额外数据\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `userid` (`adminid`) USING BTREE \
                            ) ENGINE=InnoDB AUTO_INCREMENT=1822 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC")
                # cur.execute("drop table coin_auth_extend;")
                cur.execute("CREATE TABLE `coin_auth_extend` (\
                                            `group_id` mediumint(10) unsigned NOT NULL COMMENT \'用户 id\',\
                                            `extend_id` mediumint(8) unsigned NOT NULL COMMENT \'扩展表中数据的 id\',\
                                            `type` tinyint(1) unsigned NOT NULL COMMENT \'扩展类型标识 1:栏目分类权限;2:模型权限\',\
                                            UNIQUE KEY `group_extend_type` (`group_id`,`extend_id`,`type`),\
                                            KEY `uid` (`group_id`),\
                                            KEY `group_id` (`extend_id`) \
                                            ) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC")
                # cur.execute("drop table coin_auth_group;")
                cur.execute("CREATE TABLE `coin_auth_group` (\
                                            `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT COMMENT \'用户组 id,\自增主键\',\
                                            `module` varchar(20) NOT NULL COMMENT \'用户组所属模块\',\
                                            `type` tinyint(4) NOT NULL COMMENT \'组类型\',\
                                            `title` char(20) NOT NULL DEFAULT \'\' COMMENT \'用户组中文名称\',\
                                            `description` varchar(80) NOT NULL DEFAULT \'\' COMMENT \'描述信息\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'用户组状态：为 1 正常，为 0 禁用,\-1 为删除\',\
                                            `rules` varchar(1000) NOT NULL DEFAULT \'\' COMMENT \'用户组拥有的规则 id，多个规则 ,\ 隔开\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC")
                # cur.execute("drop table coin_auth_group_access;")
                cur.execute("CREATE TABLE `coin_auth_group_access` (\
                                            `uid` int(10) unsigned NOT NULL COMMENT \'用户 id\',\
                                            `group_id` mediumint(8) unsigned NOT NULL COMMENT \'用户组 id\',\
                                            UNIQUE KEY `uid_group_id` (`uid`,`group_id`),\
                                            KEY `uid` (`uid`),\
                                            KEY `group_id` (`group_id`) \
                                            ) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC")
                # cur.execute("drop table coin_auth_rule;")
                cur.execute("CREATE TABLE `coin_auth_rule` (\
                                            `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT COMMENT \'规则 id,\自增主键\',\
                                            `module` varchar(20) NOT NULL COMMENT \'规则所属 module\',\
                                            `type` tinyint(2) NOT NULL DEFAULT \'1\' COMMENT \'1-url;2-主菜单\',\
                                            `name` char(80) NOT NULL DEFAULT \'\' COMMENT \'规则唯一英文标识\',\
                                            `title` char(20) NOT NULL DEFAULT \'\' COMMENT \'规则中文描述\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'是否有效(0:无效,1:有效)\',\
                                            `condition` varchar(300) NOT NULL DEFAULT \'\' COMMENT \'规则附加条件\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `module` (`module`,`status`,`type`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=3029 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC")
                # cur.execute("drop table coin_menu;")
                cur.execute("CREATE TABLE `coin_menu` (\
                                            `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT \'文档 ID\',\
                                            `title` varchar(50) NOT NULL DEFAULT \'\' COMMENT \'标题\',\
                                            `pid` int(10) unsigned NOT NULL DEFAULT \'0\' COMMENT \'上级分类 ID\',\
                                            `sort` int(10) unsigned NOT NULL DEFAULT \'0\' COMMENT \'排序（同级有效）\',\
                                            `url` char(255) NOT NULL DEFAULT \'\' COMMENT \'链接地址\',\
                                            `hide` tinyint(1) unsigned NOT NULL DEFAULT \'0\' COMMENT \'是否隐藏\',\
                                            `tip` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'提示\',\
                                            `group` varchar(50) DEFAULT \'\' COMMENT \'分组\',\
                                            `is_dev` tinyint(1) unsigned NOT NULL DEFAULT \'0\' COMMENT \'是否仅开发者模式可见\',\
                                            `ico_name` varchar(50) NOT NULL DEFAULT \'0\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `pid` (`pid`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=597 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC")
                cur.execute("use account;")
                # cur.execute("drop table coin_user_bank;")
                cur.execute("CREATE TABLE `coin_user_bank` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(11) unsigned NOT NULL,\
                                            `country` varchar(255) DEFAULT NULL,\
                                            `bankprov` varchar(200) NOT NULL DEFAULT \'\',\
                                            `bankcity` varchar(200) NOT NULL DEFAULT \'\',\
                                            `bank` varchar(200) NOT NULL COMMENT \'银行名称\',\
                                            `bankaddr` varchar(200) NOT NULL,\
                                            `bankcode` varchar(255) DEFAULT NULL,\
                                            `sort_code` varchar(255) DEFAULT \'\' COMMENT \'短码\',\
                                            `iban` varchar(255) DEFAULT \'\' COMMENT \'IBAN（国际银行账号）\',\
                                            `bankcard` varchar(200) NOT NULL DEFAULT \'\',\
                                            `name` varchar(200) NOT NULL DEFAULT \'\',\
                                            `username` varchar(255) DEFAULT NULL COMMENT \'用户名\',\
                                            `sort` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `type` tinyint(3) NOT NULL DEFAULT \'0\' COMMENT \'类型 0 银行卡，1 国际电汇',\
                                            `addtime` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `endtime` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `status` int(4) NOT NULL DEFAULT \'0\',\
                                            `currency` varchar(10) DEFAULT \'cny\' COMMENT \'银行卡货币类型\',\
                                            `swift` varchar(50) NOT NULL DEFAULT \'\' COMMENT \'swift\',\
                                            `account_number` varchar(50) NOT NULL DEFAULT \'\' COMMENT \'account_number\',\
                                            `account_owner` varchar(50) NOT NULL DEFAULT \'\' COMMENT \'account_owner\',\
                                            `ach_number` varchar(50) NOT NULL DEFAULT \'\' COMMENT \'ach_number\',\
                                            `wire_number` varchar(50) NOT NULL DEFAULT \'\' COMMENT \'wire_number\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `status` (`status`), \
                                            KEY `userid` (`userid`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=316 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC")
                # cur.execute("drop table coin_user_auth_fail;")
                cur.execute("CREATE TABLE `coin_user_auth_fail` (\
                                            `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT \'主键\',\
                                            `content` varchar(1024) DEFAULT \'\' COMMENT \'认证失败常见内容\',\
                                            `addtime` int(10) unsigned DEFAULT \'0\' COMMENT \'添加时间\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 COMMENT=\'认证失败表\'")
                # cur.execute("drop table coin_user_extend;")
                cur.execute("CREATE TABLE `coin_user_extend` (\
                                            `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT \'主键\',\
                                            `userid` int(10) unsigned DEFAULT \'0\' COMMENT \'用户 id\',\
                                            `auth_fail_reason` varchar(500) DEFAULT \'\' COMMENT \'认证失败原因\',\
                                            `kyc_fail_reason` varchar(500) DEFAULT \'\' COMMENT \'kyc 认证失败原因（二级）\',\
                                            `addtime` int(10) unsigned DEFAULT \'0\' COMMENT \'添加时间\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8 COMMENT=\'用户扩展表\'")
                # cur.execute("drop table coin_user_global_orc_recode;")
                cur.execute("CREATE TABLE `coin_user_global_orc_recode` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `user_id` int(11) DEFAULT NULL COMMENT \'用户 id\',\
                                            `addtime` int(11) DEFAULT NULL COMMENT \'添加时间\',\
                                            `status` tinyint(2) DEFAULT NULL COMMENT \'状态：0 待处理 1：已处理\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8")
                # cur.execute("drop table coin_user_ocr_recode;")
                cur.execute("CREATE TABLE `coin_user_ocr_recode` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `user_id` int(11) DEFAULT \'0\' COMMENT \'用户 id\',\
                                            `biz_no` varchar(60) DEFAULT \'\' COMMENT \'验证记录唯一编号\',\
                                            `addtime` int(11) DEFAULT \'1\' COMMENT \'添加时间\',\
                                            `endtime` int(11) DEFAULT \'0\' COMMENT \'验证结束时间\',\
                                            `status` varchar(20) DEFAULT NULL COMMENT \'状态 PADDING ：发起验证 NOT_STARTED：get_token 之后，并没有调用过 do 方法，还没有 开始验证 PROCESSING：正在进行 FaceID Lite 验证 OK：完成验证 FAILED：验证流程未完成或出现异常 CANCELLED：用户主动取消了验证 \
                                            流程 TIMEOUT ： 超时\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `biz_no` (`biz_no`) USING BTREE \
                            ) ENGINE=InnoDB AUTO_INCREMENT=236 DEFAULT CHARSET=utf8 COMMENT=\'用户 ocr 记录表\'")
                cur.execute("use kyc;")
                # cur.execute("drop table coin_onfidokyc_application;")
                cur.execute("CREATE TABLE `coin_onfidokyc_application` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `sn` varchar(255) NOT NULL,\
                                            `uid` int(11) NOT NULL COMMENT \'id\',\
                                            `email` varchar(200) NOT NULL COMMENT \'email\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'状态 -2:自动拒绝-1:拒绝 0:申请中 1:OCR 已处理 2:通过 3:自动通过\',\
                                            `create_time` int(11) NOT NULL DEFAULT \'0\' COMMENT \'创建时间\',\
                                            `update_time` int(11) NOT NULL DEFAULT \'0\' COMMENT \'更新时间\',\
                                            `msg` text,\
                                            `ext` text,\
                                            `ocr` text,\
                                            `auto` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'是否交由自动审核程序处理\',\
                                            `edited_ocr` text COMMENT \'ocr 编辑后\',\
                                            `files` text COMMENT \'文件地址\',\
                                            `reports` text COMMENT \'报告\',\
                                            `handle` tinyint(2) DEFAULT \'0\' COMMENT \'是否定时处理下载文件 0：未处理 1：已处理\',\
                                            PRIMARY KEY (`id`,`sn`) USING BTREE ,\
                                            KEY `idx_kyc_application` (`uid`,`email`,`status`) USING BTREE \
                            ) ENGINE=InnoDB AUTO_INCREMENT=227 DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT=\'KYC 申请单\'")
                # cur.execute("drop table coin_user_idcard;")
                cur.execute("CREATE TABLE `coin_user_idcard` (\
                                            `id` int(11) NOT NULL,\
                                            `url1` varchar(255) DEFAULT NULL,\
                                            `url2` varchar(255) DEFAULT NULL,\
                                            `url3` varchar(255) DEFAULT NULL,\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC")
                # cur.execute("drop table coin_user_log;")
                cur.execute("CREATE TABLE `coin_user_log` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(10) unsigned NOT NULL,\
                                            `type` varchar(200) NOT NULL,\
                                            `remark` varchar(200) NOT NULL,\
                                            `addip` varchar(200) NOT NULL,\
                                            `addr` varchar(200) NOT NULL,\
                                            `city` varchar(100) DEFAULT '' COMMENT '城市',\
                                            `addtime` int(10) unsigned NOT NULL,\
                                            `status` tinyint(4) NOT NULL,\
                                            PRIMARY KEY (`id`),\
                                            KEY `userid` (`userid`), \
                                            KEY `status` (`status`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=55980 DEFAULT CHARSET=utf8 COMMENT=\'用户记录表\'")
                # cur.execute("drop table coin_user_notification;")
                cur.execute("CREATE TABLE `coin_user_notification` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT COMMENT \'消息 id\',\
                                            `userid` int(10) NOT NULL DEFAULT \'0\' COMMENT \'用户 id\',\
                                            `currency` varchar(30) NOT NULL DEFAULT \'\' COMMENT \'法币符号 eg eurx gbpx\',\
                                            `sign` varchar(30) NOT NULL DEFAULT \'\' COMMENT \'币种标记名\',\
                                            `content` varchar(300) NOT NULL DEFAULT \'\' COMMENT \'消息内容\',\
                                            `is_read` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'是否 已读 1：已读 0：未读\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `id_sign_read` (`userid`,`sign`,`is_read`) USING BTREE \
                            ) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8")
                # cur.execute("drop table coin_user_operate_log;")
                cur.execute("CREATE TABLE `coin_user_operate_log` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(10) unsigned NOT NULL DEFAULT \'0\' COMMENT \'用户\',\
                                            `type` tinyint(3) NOT NULL DEFAULT \'0\' COMMENT \'类型:1 修改登录密码,2 找回登录密码,3 修改资金密码,4 修改邮箱,5 重新绑定手机号\',\
                                            `remark` varchar(200) NOT NULL DEFAULT \'\' COMMENT \'备注\',\
                                            `addip` varchar(200) NOT NULL DEFAULT \'\' COMMENT \'IP\',\
                                            `addr` varchar(200) NOT NULL DEFAULT \'\' COMMENT \'IP\',\
                                            `status` tinyint(3) NOT NULL DEFAULT \'0\' COMMENT \'状态\',\
                                            `new_data` varchar(1000) NOT NULL DEFAULT \'\' COMMENT \'新数据\',\
                                            `old_data` varchar(1000) NOT NULL DEFAULT \'\' COMMENT \'老数据\',\
                                            `addtime` int(10) unsigned NOT NULL DEFAULT \'0\' COMMENT \'时间\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `userid` (`userid`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=55525 DEFAULT CHARSET=utf8 COMMENT=\'用户操作记录表\'")
                cur.execute("use assets;")
                # cur.execute("drop table coin_balance;")
                cur.execute("CREATE TABLE `coin_balance` (\
                                            `id` int(10) unsigned NOT NULL AUTO_INCREMENT,\
                                            `add_time` int(10) unsigned DEFAULT \'0\' COMMENT \'统计时间\',\
                                            `end_time` int(10) unsigned DEFAULT \'0\' COMMENT \'统计时间\',\
                                            `start_time` int(10) unsigned DEFAULT \'0\' COMMENT \'最后一次正常时间\',\
                                            `coinname` char(32) DEFAULT \'\' COMMENT \'币种名称\',\
                                            `zr_total` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'充值金额\',\
                                            `zr_real` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'实际充值\',\
                                            `zr_fee` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'手续费\',\
                                            `zr_temp` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'中间账户留存\',\
                                            `zc_total` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'提现金额\',\
                                            `zc_fee` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'提现手续费收入\',\
                                            `zc_chain` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'链上手续费\',\
                                            `trade_buy` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'交易佣金-买\',\
                                            `trade_sell` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'交易佣金-卖\',\
                                            `trade_in` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'交易佣金\',\
                                            `trade_mum` decimal(32,16) unsigned DEFAULT NULL COMMENT \'交易额\',\
                                            `invit` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'推广奖励\',\
                                            `income` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'总收入\',\
                                            `money` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'平台余额\',\
                                            `account` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'账户余额\',\
                                            `coin_num` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'链上余额\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=92251 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC")
                # cur.execute("drop table coin_balance_liab;")
                cur.execute("CREATE TABLE `coin_balance_liab` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `coin` varchar(30) DEFAULT NULL,\
                                            `platform_assets` decimal(32,16) unsigned NOT NULL DEFAULT \'0.00000000\' COMMENT \'平台内总资产\',\
                                            `cold_wallet_assets` decimal(32,16) unsigned NOT NULL DEFAULT \'0.00000000\' COMMENT \'冷钱包总资产\',\
                                            `hot_wallet_assets` decimal(32,16) unsigned NOT NULL DEFAULT \'0.00000000\' COMMENT \'热钱包总资产\',\
                                            `borrow_amount` decimal(32,16) unsigned NOT NULL DEFAULT \'0.00000000\' COMMENT \'借款总数\',\
                                            `differ_assets` decimal(32,16) NOT NULL DEFAULT \'0.00000000\' COMMENT \'差额资产\',\
                                            `valuation_coin` varchar(30) DEFAULT NULL COMMENT \'估值币\',\
                                            `valuation` decimal(32,16) unsigned NOT NULL DEFAULT \'0.00000000\' COMMENT \'估值\',\
                                            `addtime` int(11) unsigned NOT NULL DEFAULT \'0\' COMMENT \'新增时间\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=83 DEFAULT CHARSET=utf8 COMMENT=\'平台资产负债记录表\'")
                # cur.execute("drop table coin_mycz;")
                cur.execute("CREATE TABLE `coin_mycz` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(11) unsigned NOT NULL,\
                                            `currency` varchar(30) NOT NULL COMMENT \'币种\',\
                                            `num` decimal(32,16) NOT NULL DEFAULT \'0.00\',\
                                            `mum` decimal(32,16) unsigned NOT NULL DEFAULT \'0.00\',\
                                            `type` varchar(50) NOT NULL COMMENT \'类型:visa 支付卡, bank 银行卡\',\
                                            `tradeno` varchar(50) NOT NULL,\
                                            `remark` varchar(250) NOT NULL DEFAULT \'\',\
                                            `sort` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `addtime` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `endtime` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `status` int(4) NOT NULL DEFAULT \'0\' COMMENT \'状态:0 未付款, 1 充值成功, 2 人工到账, 3 处理中\',\
                                            `truename` varchar(32) DEFAULT \'\',\
                                            `name` varchar(32) DEFAULT \'\',\
                                            `bank` varchar(250) DEFAULT \'\',\
                                            `bankprov` varchar(50) DEFAULT \'\',\
                                            `bankcity` varchar(50) DEFAULT \'\',\
                                            `bankaddr` varchar(50) DEFAULT \'\',\
                                            `bankcard` varchar(200) DEFAULT \'\',\
                                            PRIMARY KEY (`id`), \
                                            KEY `userid` (`userid`), \
                                            KEY `status` (`status`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=174 DEFAULT CHARSET=utf8 COMMENT=\'充值记录表\'")
                # cur.execute("drop table coin_mycz_bank_log;")
                cur.execute("CREATE TABLE `coin_mycz_bank_log` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `mycz_id` int(11) DEFAULT NULL COMMENT \'匹配对应法币充值 id\',\
                                            `currency` varchar(20) DEFAULT NULL COMMENT \'所属币种\',\
                                            `uuid` varchar(100) NOT NULL COMMENT \'通用唯一标识码\',\
                                            `amout` decimal(32,16) unsigned DEFAULT NULL COMMENT \'充值金额\',\
                                            `date` varchar(60) DEFAULT NULL COMMENT \'银行结算时间\',\
                                            `data` text COMMENT \'扩展数据\',\
                                            `create_time` int(11) DEFAULT NULL COMMENT \'添加事件\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `s_uuid` (`currency`,`uuid`) USING BTREE \
                            ) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8mb4")
                # cur.execute("drop table coin_mycz_type;")
                cur.execute("CREATE TABLE `coin_mycz_type` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `max` varchar(200) NOT NULL COMMENT \'名称\',\
                                            `min` varchar(200) NOT NULL COMMENT \'名称\',\
                                            `code` varchar(255) NOT NULL DEFAULT \'\',\
                                            `account_owner` varchar(100) DEFAULT \'\' COMMENT \'account_owner\',\
                                            `account_number` varchar(100) DEFAULT \'\' COMMENT \'account_number\',\
                                            `swift` varchar(100) DEFAULT \'\' COMMENT \'swift\',\
                                            `sort_code` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'短码\',\
                                            `iban` varchar(255) NOT NULL DEFAULT \'\' COMMENT \'IBAN（国际银行账户号码）\',\
                                            `ach_number` varchar(100) NOT NULL DEFAULT \'\' COMMENT \'ach_number\',\
                                            `wire_number` varchar(100) NOT NULL DEFAULT \'\' COMMENT \'wire_number\',\
                                            `address` varchar(100) DEFAULT \'\' COMMENT \'address\',\
                                            `currency` varchar(30) NOT NULL COMMENT \'法币类型 eg CNY USD\',\
                                            `kaihu` varchar(200) NOT NULL COMMENT \'名称\',\
                                            `truename` varchar(200) NOT NULL COMMENT \'名称\',\
                                            `addr` varchar(200) NOT NULL DEFAULT \'\',\
                                            `country` varchar(200) NOT NULL DEFAULT \'\',\
                                            `name` varchar(50) NOT NULL,\
                                            `title` varchar(50) NOT NULL,\
                                            `url` varchar(50) NOT NULL,\
                                            `username` varchar(50) NOT NULL,\
                                            `password` varchar(50) NOT NULL,\
                                            `img` varchar(50) NOT NULL,\
                                            `extra` varchar(50) NOT NULL,\
                                            `remark` varchar(50) NOT NULL,\
                                            `sort` int(11) unsigned NOT NULL,\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `endtime` int(11) unsigned NOT NULL,\
                                            `status` int(4) NOT NULL,\
                                            PRIMARY KEY (`id`),\
                                            KEY `status` (`status`), \
                                            KEY `name` (`name`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT=\'充值类型\'")
                # cur.execute("drop table coin_mytx;")
                cur.execute("CREATE TABLE `coin_mytx` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(11) unsigned NOT NULL,\
                                            `currency` varchar(30) NOT NULL COMMENT \'法币类型\',\
                                            `num` decimal(32,16) unsigned NOT NULL,\
                                            `fee` decimal(32,16) unsigned NOT NULL,\
                                            `mum` decimal(32,16) unsigned NOT NULL,\
                                            `truename` varchar(32) NOT NULL,\
                                            `name` varchar(32) NOT NULL,\
                                            `bank` varchar(250) NOT NULL,\
                                            `bankprov` varchar(50) NOT NULL,\
                                            `bankcity` varchar(50) NOT NULL,\
                                            `bankaddr` varchar(50) NOT NULL,\
                                            `bankcode` varchar(200) NOT NULL DEFAULT \'\',\
                                            `bankcard` varchar(200) NOT NULL,\
                                            `account_number` varchar(50) NOT NULL DEFAULT \'\' COMMENT \'account_number\',\
                                            `sort` int(11) unsigned DEFAULT \'0\',\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `endtime` int(11) unsigned DEFAULT \'0\',\
                                            `status` int(4) NOT NULL,\
                                            `type` tinyint(3) NOT NULL DEFAULT \'1\' COMMENT \'类型:1 银行卡，2 支付卡\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `userid` (`userid`), \
                                            KEY `status` (`status`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=193 DEFAULT CHARSET=utf8 COMMENT=\'提现记录表\'")
                # cur.execute("drop table coin_myzr;")
                cur.execute("CREATE TABLE `coin_myzr` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(11) unsigned NOT NULL,\
                                            `username` varchar(200) NOT NULL,\
                                            `coinname` varchar(200) NOT NULL,\
                                            `main_coin` varchar(30) DEFAULT NULL COMMENT '所属主链',\
                                            `from_user` varchar(30) NOT NULL DEFAULT \'\' COMMENT \'转入从哪个用户来（内部转账，真实姓名）\',\
                                            `txid` varchar(200) NOT NULL,\
                                            `payment_code` varchar(60) NOT NULL DEFAULT \'\' COMMENT \'站内收款码\',\
                                            `num` decimal(32,16) unsigned NOT NULL,\
                                            `mum` decimal(32,16) unsigned NOT NULL,\
                                            `fee` decimal(32,16) NOT NULL,\
                                            `balance` decimal(32,16) NOT NULL DEFAULT \'0.00000000\' COMMENT \'币种余额\',\
                                            `sort` int(11) unsigned DEFAULT \'0\',\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `endtime` int(11) unsigned DEFAULT \'0\',\
                                            `type` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'转入类型 1 内部转入，2 外部转入\',\
                                            `status` int(4) DEFAULT \'0\' COMMENT \'状态:0 处理中，1 完成\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `status` (`status`), \
                                            KEY `userid` (`userid`), \
                                            KEY `coinname` (`coinname`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=67 DEFAULT CHARSET=utf8")
                # cur.execute("drop table coin_myzc;")
                cur.execute("CREATE TABLE `coin_myzc` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(11) unsigned NOT NULL DEFAULT '0',\
                                            `username` varchar(200) NOT NULL DEFAULT '' COMMENT '转出地址',\
                                            `payment_id` varchar(200) DEFAULT '' COMMENT '用户标识付款id（分离地址用）',\
                                            `coinname` varchar(200) NOT NULL DEFAULT '',\
                                            `accept_user` varchar(30) NOT NULL DEFAULT '' COMMENT '接收人姓名（内部转出，真实名称）',\
                                            `txid` varchar(200) NOT NULL DEFAULT '',\
                                            `payment_code` varchar(200) DEFAULT '' COMMENT '站内收款码',\
                                            `num` decimal(32,16) unsigned NOT NULL DEFAULT '0.00000000',\
                                            `fee` decimal(32,16) unsigned NOT NULL DEFAULT '0.00000000',\
                                            `coin_fee` decimal(32,16) DEFAULT '0.00000000',\
                                            `mum` decimal(32,16) unsigned NOT NULL DEFAULT '0.00000000',\
                                            `balance` decimal(32,16) NOT NULL DEFAULT '0.00000000' COMMENT '币种余额',\
                                            `sort` int(11) unsigned NOT NULL DEFAULT '0',\
                                            `addtime` int(11) unsigned NOT NULL DEFAULT '0',\
                                            `endtime` int(11) unsigned NOT NULL DEFAULT '0',\
                                            `status` int(4) NOT NULL DEFAULT '0' COMMENT '状态:0处理中,1转出成功 2失败 3 已汇出',\
                                            `type` tinyint(1) NOT NULL DEFAULT '0' COMMENT '转出类型1内部转出，2外部转出',\
                                            `is_read` tinyint(1) DEFAULT '0' COMMENT '是否读取',\
                                            `is_verify` tinyint(1) DEFAULT '0' COMMENT '是否审核',\
                                            `chain_status` tinyint(1) unsigned DEFAULT '0' COMMENT '链上状态',\
                                            `is_op` tinyint(1) DEFAULT '0' COMMENT '是否已处理（btc清算） 0 未处理  1 已处理',\
                                            PRIMARY KEY (`id`),\
                                            KEY `userid` (`userid`),\
                                            KEY `status` (`status`),\
                                            KEY `coinname` (`coinname`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=38 DEFAULT CHARSET=utf8;")

                # cur.execute("drop table coin_myzc_fee;")
                cur.execute("CREATE TABLE `coin_myzc_fee` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(11) unsigned NOT NULL,\
                                            `username` varchar(200) COLLATE utf8_unicode_ci NOT NULL,\
                                            `coinname` varchar(200) COLLATE utf8_unicode_ci NOT NULL,\
                                            `txid` varchar(200) COLLATE utf8_unicode_ci NOT NULL,\
                                            `type` varchar(200) COLLATE utf8_unicode_ci NOT NULL,\
                                            `fee` decimal(32,16) NOT NULL,\
                                            `num` decimal(32,16) unsigned NOT NULL,\
                                            `mum` decimal(32,16) unsigned NOT NULL,\
                                            `sort` int(11) unsigned NOT NULL,\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `endtime` int(11) unsigned NOT NULL,\
                                            `status` int(4) NOT NULL,\
                                            PRIMARY KEY (`id`),\
                                            KEY `status` (`status`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci")
                # cur.execute("drop table coin_user_coin_addr;")
                cur.execute("CREATE TABLE `coin_user_coin_addr` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `user_id` int(11) NOT NULL COMMENT \'用户 id\',\
                                            `username` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT \'用户名\',\
                                            `coin_name` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT \'\' COMMENT \'钱包名称\',\
                                            `addr` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT \'平台 zcash 钱包地址\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'状态 1:正常 0:停用\',\
                                            `payment_id` varchar(200) COLLATE utf8mb4_unicode_ci DEFAULT \'\' COMMENT \'钱包 payment id\',\
                                            `standard_address` varchar(200) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT \'分离地址\',\
                                            `main_coin` varchar(30) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT '所属主链',\
                                            PRIMARY KEY (`id`),\
                                            KEY `address` (`addr`(191)) USING BTREE COMMENT \'地址索引\' \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT=\'用户钱包地址（增对特殊币 \
                                            种）\'")
                # cur.execute("drop table coin_user_coin_balance_snapshot;")
                cur.execute("CREATE TABLE `coin_user_coin_balance_snapshot` (\
                                            `id` int(30) NOT NULL AUTO_INCREMENT,\
                                            `coin` varchar(30) DEFAULT NULL,\
                                            `user_id` int(11) DEFAULT NULL COMMENT \'用户 id\',\
                                            `usable` decimal(32,16) unsigned DEFAULT NULL COMMENT \'可以资产\',\
                                            `freeze` decimal(32,16) unsigned DEFAULT NULL COMMENT \'冻结资产\',\
                                            `lockup` decimal(32,16) DEFAULT NULL COMMENT \'锁仓资产\',\
                                            `add_time` int(11) DEFAULT NULL COMMENT \'快照时间\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT=\'用户资产快照表\'")
                # cur.execute("drop table coin_user_qianbao;")
                cur.execute("CREATE TABLE `coin_user_qianbao` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(11) unsigned NOT NULL,\
                                            `coinname` varchar(200) NOT NULL,\
                                            `name` varchar(200) NOT NULL,\
                                            `addr` varchar(200) NOT NULL,\
                                            `payment_id` varchar(200) NOT NULL DEFAULT \'\' COMMENT \'分离地址用户付款 id\',\
                                            `sort` int(11) unsigned NOT NULL,\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `endtime` int(11) unsigned NOT NULL,\
                                            `status` int(4) NOT NULL,\
                                            PRIMARY KEY (`id`),\
                                            KEY `status` (`status`), \
                                            KEY `userid` (`userid`), \
                                            KEY `coinname` (`coinname`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT=\'用户钱包表\'")
                # cur.execute("drop table coin_user_transfer_code;")
                cur.execute("CREATE TABLE `coin_user_transfer_code` (\
                                            `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT \'主键\',\
                                            `userid` int(10) unsigned DEFAULT \'0\' COMMENT \'用户 id\',\
                                            `code` char(36) DEFAULT \'\' COMMENT \'付款码\',\
                                            `qrcode` varchar(200) DEFAULT \'\' COMMENT \'二维码\',\
                                            `type` tinyint(3) unsigned DEFAULT \'0\' COMMENT \'0 永久收款码，1 临时收款码\',\
                                            `expire_time` int(10) unsigned DEFAULT \'0\' COMMENT \'失效时间\',\
                                            `coinname` varchar(64) DEFAULT \'\' COMMENT \'币种名称\',\
                                            `num` decimal(32,16) NOT NULL DEFAULT \'0.00000000\' COMMENT \'数量\',\
                                            `money` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'金额\',\
                                            `updatetime` int(10) unsigned DEFAULT \'0\' COMMENT \'更新时间\',\
                                            `addtime` int(10) unsigned DEFAULT \'0\' COMMENT \'添加时间\',\
                                            PRIMARY KEY (`id`),\
                                            UNIQUE KEY `idx_code` (`code`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=utf8 COMMENT=\'用户转帐码\'")
                # cur.execute("drop table coin_user_visa;")
                cur.execute("CREATE TABLE `coin_user_visa` (\
                                            `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT \'主键\',\
                                            `userid` int(10) unsigned DEFAULT \'0\' COMMENT \'用户 id\',\
                                            `account_number` varchar(10) DEFAULT \'\' COMMENT \'account_number\',\
                                            `consumer_id` varchar(30) DEFAULT \'\' COMMENT \'consumer_id\',\
                                            `has_card` tinyint(1) DEFAULT \'1\' COMMENT \'是否有卡 0 无卡 1：有卡\',\
                                            `card_id` varchar(32) DEFAULT \'\' COMMENT \'card_id\',\
                                            `sort_code` varchar(6) DEFAULT \'\' COMMENT \'sort_code\',\
                                            `bic` varchar(11) DEFAULT NULL COMMENT \'bic\',\
                                            `iban` varchar(34) DEFAULT NULL COMMENT \'iban\',\
                                            `coinname` varchar(50) DEFAULT \'\' COMMENT \'币种\',\
                                            `status` tinyint(3) unsigned DEFAULT \'0\' COMMENT \'0申请中，1正常，2未激活\',\
                                            `enabled` tinyint(3) unsigned DEFAULT \'0\' COMMENT \'0 禁用，1 启用\',\
                                            `bank_card` varchar(50) DEFAULT \'\' COMMENT \'银行卡\',\
                                            `last_four` char(4) DEFAULT \'\' COMMENT \'最后四位\',\
                                            `expire_time` char(5) DEFAULT \'\' COMMENT \'有效期(03/19)\',\
                                            `updatetime` int(10) unsigned DEFAULT \'0\' COMMENT \'更新时间\',\
                                            `addtime` int(10) unsigned DEFAULT \'0\' COMMENT \'添加时间\',\
                                            `account_status` varchar(10) DEFAULT \'0\' COMMENT \'消费者账户状态\',\
                                            `card_status` varchar(10) NOT NULL DEFAULT '' COMMENT '卡片状态（同步contis）',\
                                            `card_issue_date` varchar(60) DEFAULT '' COMMENT '卡片发行时间',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=516 DEFAULT CHARSET=utf8 COMMENT=\'用户 VISA 卡\'")
                # cur.execute("drop table coin_user_visa_log;")
                cur.execute("CREATE TABLE `coin_user_visa_log` (\
                                            `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT \'主键\',\
                                            `userid` int(10) unsigned DEFAULT \'0\' COMMENT \'用户 id\',\
                                            `currency` varchar(10) DEFAULT \'\' COMMENT \'币种\',\
                                            `type` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'类型:1 收入,2 支出\',\
                                            `transaction_type` int(10) unsigned DEFAULT \'0\' COMMENT \'类型\',\
                                            `from_account_number` varchar(10) DEFAULT \'\' COMMENT \'from_account_number\',\
                                            `from_sort_code` varchar(6) DEFAULT \'\' COMMENT \'from_sort_code\',\
                                            `to_account_number` varchar(10) DEFAULT \'\' COMMENT \'to_account_number\',\
                                            `to_sort_code` varchar(6) DEFAULT \'\' COMMENT \'to_sort_code\',\
                                            `transaction_id` varchar(32) DEFAULT \'\' COMMENT \'transaction_id\',\
                                            `amount`  decimal(32,16) unsigned NOT NULL DEFAULT \'0.00\' COMMENT \'金额\',\
                                            `from_balance`  decimal(32,16) unsigned NOT NULL DEFAULT \'0.00\' COMMENT \'from 剩余金额\',\
                                            `to_balance`  decimal(32,16) unsigned NOT NULL DEFAULT \'0.00\' COMMENT \'to 剩余金额\',\
                                            `settlement_date` varchar(50) DEFAULT \'\' COMMENT \'时间\',\
                                            `description` varchar(600) NOT NULL DEFAULT \'\',\
                                            `content` text COMMENT \'json 内容\',\
                                            `addtime` int(10) unsigned DEFAULT \'0\' COMMENT \'添加时间\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=48 DEFAULT CHARSET=utf8 COMMENT=\'用户 VISA 卡消费记录\'")
                # cur.execute("drop table coin_znzc;")
                cur.execute("CREATE TABLE `coin_znzc` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(11) unsigned DEFAULT \'0\' COMMENT \'用户 Id\',\
                                            `accept_user` varchar(30) DEFAULT \'\' COMMENT \'接收人姓名\',\
                                            `accept_uid` int(11) DEFAULT \'0\' COMMENT \'接收人 id\',\
                                            `coinname` varchar(200) DEFAULT \'\' COMMENT \'币种\',\
                                            `code` varchar(200) DEFAULT \'\' COMMENT \'转账码\',\
                                            `num` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'数量\',\
                                            `fee` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'手续费\',\
                                            `mum` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'到账\',\
                                            `addtime` int(11) unsigned DEFAULT \'0\' COMMENT \'时间\',\
                                            `endtime` int(11) unsigned DEFAULT \'0\' COMMENT \'时间\',\
                                            `status` int(3) DEFAULT \'0\' COMMENT \'状态\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8")
                # cur.execute("drop table coin_znzr;")
                cur.execute("CREATE TABLE `coin_znzr` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(11) unsigned DEFAULT \'0\' COMMENT \'用户 Id\',\
                                            `from_user` varchar(30) DEFAULT \'\' COMMENT \'转入人姓名\',\
                                            `from_uid` int(11) DEFAULT \'0\' COMMENT \'转入人 id\',\
                                            `coinname` varchar(200) DEFAULT \'\' COMMENT \'币种\',\
                                            `code` varchar(200) DEFAULT \'\' COMMENT \'转账码\',\
                                            `num` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'数量\',\
                                            `fee` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'手续费\',\
                                            `mum` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'到账\',\
                                            `addtime` int(11) unsigned DEFAULT \'0\' COMMENT \'时间\',\
                                            `endtime` int(11) unsigned DEFAULT \'0\' COMMENT \'时间\',\
                                            `status` int(3) DEFAULT \'0\' COMMENT \'状态\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8")
                cur.execute("use trade;")
                # cur.execute("drop table coin_invit_tel;")
                cur.execute("CREATE TABLE `coin_invit_tel` (\
                                            `id` int(10) NOT NULL AUTO_INCREMENT COMMENT \'自增 id\',\
                                            `tel` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT \'手机号码\',\
                                            `invit_id` int(11) NOT NULL COMMENT \'推荐人 id\',\
                                            PRIMARY KEY (`id`),\
                                            UNIQUE KEY `tel` (`tel`) USING BTREE \
                            ) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT=\'推荐绑定手机\'")
                # cur.execute("drop table coin_market;")
                cur.execute("CREATE TABLE `coin_market` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `name` varchar(50) NOT NULL,\
                                            `round` varchar(255) NOT NULL,\
                                            `round_buy_sell_num` int(11) NOT NULL DEFAULT \'8\' COMMENT \'可买(卖)小数位数\',\
                                            `fee_buy` decimal(32,16) NOT NULL,\
                                            `fee_sell` decimal(32,16) NOT NULL,\
                                            `fee_user_id` int(11) DEFAULT \'0\' COMMENT \'手续费保存用户\',\
                                            `buy_min` decimal(32,16) NOT NULL,\
                                            `buy_max` decimal(32,16) NOT NULL,\
                                            `sell_min` decimal(32,16) NOT NULL,\
                                            `sell_max` decimal(32,16) NOT NULL,\
                                            `trade_min` decimal(32,16) NOT NULL,\
                                            `trade_max` decimal(32,16) NOT NULL,\
                                            `invit_buy` varchar(50) NOT NULL,\
                                            `invit_sell` varchar(50) NOT NULL,\
                                            `invit_1` decimal(32,16) NOT NULL,\
                                            `invit_2` decimal(32,16) NOT NULL,\
                                            `invit_3` decimal(32,16) NOT NULL,\
                                            `zhang` decimal(32,16) NOT NULL,\
                                            `die` decimal(32,16) NOT NULL,\
                                            `hou_price` decimal(32,16) NOT NULL,\
                                            `tendency` varchar(1000) NOT NULL,\
                                            `trade` int(11) unsigned NOT NULL,\
                                            `new_price` decimal(32,16) unsigned NOT NULL,\
                                            `buy_price` decimal(32,16) unsigned NOT NULL,\
                                            `sell_price` decimal(32,16) unsigned NOT NULL,\
                                            `min_price` decimal(32,16) unsigned NOT NULL,\
                                            `max_price` decimal(32,16) unsigned NOT NULL,\
                                            `volume` decimal(32,16) unsigned NOT NULL,\
                                            `change` decimal(32,16) NOT NULL,\
                                            `api_min` decimal(32,16) unsigned NOT NULL,\
                                            `api_max` decimal(32,16) unsigned NOT NULL,\
                                            `sort` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `endtime` int(11) unsigned NOT NULL,\
                                            `status` tinyint(4) NOT NULL,\
                                            PRIMARY KEY (`id`),\
                                            KEY `name` (`name`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=130 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT=\'行情配置表\'")
                # cur.execute("drop table coin_market_json;")
                cur.execute("CREATE TABLE `coin_market_json` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `name` varchar(100) COLLATE utf8_unicode_ci NOT NULL,\
                                            `data` varchar(500) COLLATE utf8_unicode_ci NOT NULL,\
                                            `type` varchar(100) COLLATE utf8_unicode_ci NOT NULL,\
                                            `sort` int(11) unsigned NOT NULL,\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `endtime` int(11) unsigned NOT NULL,\
                                            `status` int(4) NOT NULL,\
                                            PRIMARY KEY (`id`),\
                                            KEY `status` (`status`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=78 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci ROW_FORMAT=DYNAMIC")
                cur.execute("use exassets;")
                # cur.execute("drop table coin_addr_pool;")
                cur.execute("CREATE TABLE `coin_addr_pool` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT COMMENT \'ID\',\
                                            `uid` int(11) NOT NULL DEFAULT \'0\' COMMENT \'用户 UID\',\
                                            `coin_id` int(11) NOT NULL DEFAULT \'0\' COMMENT \'币种 id\',\
                                            `coin_name` varchar(200) DEFAULT \'\' COMMENT \'币种名称\',\
                                            `main_coin` varchar(30) DEFAULT NULL COMMENT '所属主链',\
                                            `integration_addr` varchar(255) DEFAULT \'\' COMMENT \'钱包集成地址\',\
                                            `sub_addr` varchar(255) DEFAULT \'\' COMMENT \'钱包标准地址\',\
                                            `payment_id` varchar(200) NOT NULL DEFAULT \'\',\
                                            `ext` text COMMENT \'拓展字段\',\
                                            `create_time` int(11) DEFAULT \'0\' COMMENT \'创建时间\',\
                                            `update_time` int(11) DEFAULT \'0\' COMMENT \'更新时间\',\
                                            PRIMARY KEY (`id`) USING BTREE ,\
                                            KEY `idx_coin_addr_pool` (`coin_id`,`integration_addr`) USING BTREE \
                            ) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT=\'钱包地址池\'")
                cur.execute("use otc;")
                # cur.execute("drop table coin_order;")
                cur.execute("CREATE TABLE `coin_order` (\
                                            `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT \'主键\',\
                                            `orderid` char(15) DEFAULT \'\' COMMENT \'订单号\',\
                                            `pay_type` int(10) DEFAULT \'0\' COMMENT \'支付方式(求和)\',\
                                            `pay_uid` int(10) unsigned DEFAULT \'0\' COMMENT \'用户 id\',\
                                            `pay_user` varchar(64) DEFAULT \'\' COMMENT \'用户名\',\
                                            `pay_status` tinyint(1) unsigned DEFAULT \'0\' COMMENT \'打款状态\',\
                                            `pay_time` int(10) unsigned DEFAULT \'0\' COMMENT \'打款时间\',\
                                            `accept_uid` int(10) unsigned DEFAULT \'0\' COMMENT \'用户 id\',\
                                            `accept_user` varchar(64) DEFAULT \'\' COMMENT \'用户名\',\
                                            `accept_status` tinyint(1) unsigned DEFAULT \'0\' COMMENT \'收款状态\',\
                                            `accept_time` int(10) unsigned DEFAULT \'0\' COMMENT \'收款时间\',\
                                            `market_id` int(10) NOT NULL COMMENT \'所属市场 id\',\
                                            `task_id` int(10) unsigned DEFAULT \'0\' COMMENT \'task id\',\
                                            `coinname` varchar(64) DEFAULT \'\' COMMENT \'币种名称\',\
                                            `currency` varchar(64) DEFAULT \'\' COMMENT \'货币\',\
                                            `price` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'单价\',\
                                            `money` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'金额\',\
                                            `num` decimal(32,16) unsigned NOT NULL DEFAULT \'0.00000000\',\
                                            `addtime` int(10) unsigned DEFAULT \'0\' COMMENT \'添加时间\',\
                                            `is_cancel` tinyint(1) unsigned DEFAULT \'0\',\
                                            `cancel_time` int(10) DEFAULT \'0\' COMMENT \'取消时间\',\
                                            `remark` varchar(255) DEFAULT \'\' COMMENT \'备注\',\
                                            `expire_time` int(10) unsigned DEFAULT \'0\' COMMENT \'到期时间\',\
                                            `is_fed` tinyint(1) unsigned DEFAULT \'0\' COMMENT \'投诉\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8")
                # cur.execute("drop table coin_order_fed;")
                cur.execute("CREATE TABLE `coin_order_fed` (\
                                            `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT \'主键\',\
                                            `userid` int(10) unsigned DEFAULT \'0\' COMMENT \'用户 id\',\
                                            `order_id` int(10) unsigned DEFAULT \'0\' COMMENT \'订单 id\',\
                                            `fed_content` varchar(1024) DEFAULT \'\' COMMENT \'投诉内容\',\
                                            `fed_file` varchar(1000) DEFAULT \'\' COMMENT \'投诉附件\',\
                                            `addtime` int(10) unsigned DEFAULT \'0\' COMMENT \'添加时间\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8")
                # cur.execute("drop table coin_task_config;")
                cur.execute("CREATE TABLE `coin_task_config` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT COMMENT \'c2c 交易市场 id\',\
                                            `coinname` varchar(30) COLLATE utf8_unicode_ci NOT NULL COMMENT \'购买币 eg:buc\',\
                                            `currency` varchar(30) COLLATE utf8_unicode_ci NOT NULL COMMENT \'交易货币 cny\',\
                                            `name` varchar(60) COLLATE utf8_unicode_ci NOT NULL DEFAULT \'\' COMMENT \'显示名称\',\
                                            `task_free_price` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'是否允许用户自定义价格\',\
                                            `task_buy_price` decimal(32,16) NOT NULL DEFAULT \'0.00\' COMMENT \'买价\',\
                                            `task_sell_price` decimal(32,16) NOT NULL DEFAULT \'0.00\' COMMENT \'卖价\',\
                                            `task_pay_time` int(11) NOT NULL DEFAULT \'0\' COMMENT \'默认付款期限\',\
                                            `task_min` decimal(32,16) NOT NULL DEFAULT \'0\' COMMENT \'单笔最小交易额\',\
                                            `task_max` decimal(32,16) NOT NULL DEFAULT \'0\' COMMENT \'单笔最大交易额\',\
                                            `is_default` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'是否为默认\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'是否启用 1 ：启用 0：禁用\',\
                                            `allow_release_uid` text COLLATE utf8_unicode_ci COMMENT \'允许发布挂单人 id（,\号分隔，不填代表不限制）\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci")
                # cur.execute("drop table coin_task;")
                cur.execute("CREATE TABLE `coin_task` (\
                                            `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT \'主键\',\
                                            `user_id` int(10) unsigned DEFAULT NULL COMMENT \'用户 id\',\
                                            `username` varchar(64) DEFAULT \'\' COMMENT \'用户名\',\
                                            `type` tinyint(1) unsigned DEFAULT \'0\' COMMENT \'类型，0 买入，1 卖出\',\
                                            `is_fixed` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'是否是固定价 1:是 0:否（即浮动价）\',\
                                            `float_pct` decimal(32,16) NOT NULL DEFAULT \'0.00000000\' COMMENT \'浮动百分比 eg. 1% 存储为 0.01\',\
                                            `market_id` int(10) NOT NULL,\
                                            `coinname` varchar(64) DEFAULT \'\' COMMENT \'币种名称\',\
                                            `country` varchar(64) DEFAULT \'\' COMMENT \'国家\',\
                                            `currency` varchar(64) DEFAULT \'\' COMMENT \'货币\',\
                                            `price` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'单价\',\
                                            `num` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'交易数量（总共买卖数量）\',\
                                            `num_d` decimal(32,16) unsigned DEFAULT \'0.00000000\' COMMENT \'冻结数量\',\
                                            `pay_type` varchar(64) DEFAULT \'\' COMMENT \'支付方式 alipay :1 wechat:2 bank:4 求和结果\',\
                                            `pay_banks` varchar(64) DEFAULT \'\' COMMENT \'支付银行卡\',\
                                            `pay_time` int(10) unsigned DEFAULT \'0\' COMMENT \'到期时间分钟\',\
                                            `min_limit` decimal(32,16) unsigned DEFAULT \'0.00\' COMMENT \'最小限制\',\
                                            `max_limit` decimal(32,16) DEFAULT \'0.00\' COMMENT \'最大限制\',\
                                            `trade_rule` varchar(512) DEFAULT \'\' COMMENT \'交易规则，备注信息\',\
                                            `addtime` int(10) unsigned DEFAULT \'0\' COMMENT \'添加时间\',\
                                            `status` tinyint(1) unsigned DEFAULT \'0\' COMMENT \'状态 0:关闭 1:开启 2：完成\',\
                                            `is_del` tinyint(1) unsigned DEFAULT \'0\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8")
                # cur.execute("drop table coin_otc_bitmall;")
                cur.execute("CREATE TABLE `coin_otc_bitmall` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` int(11) unsigned NOT NULL DEFAULT \'0\' COMMENT \'用户 Id\',\
                                            `merchant_order_no` varchar(50) DEFAULT \'\' COMMENT \'订单编号\',\
                                            `order_no` varchar(50) DEFAULT \'\' COMMENT \'订单编号(对接方)\',\
                                            `currency` varchar(50) DEFAULT \'\' COMMENT \'币种名称\',\
                                            `num` decimal(32,16) unsigned NOT NULL DEFAULT \'0.00000000\' COMMENT \'数量\',\
                                            `mum` decimal(32,16) unsigned NOT NULL DEFAULT \'0.00000000\' COMMENT \'到账\',\
                                            `type` tinyint(3) NOT NULL DEFAULT \'0\' COMMENT \'类型 1 买,2 卖\',\
                                            `status` tinyint(3) NOT NULL DEFAULT \'0\' COMMENT \'0 交易中,1 交易成功，2 用户主动交易取消，3 支付超时取消，4 仲裁取消\',\
                                            `callback_time` int(11) DEFAULT \'0\' COMMENT \'回调时间\',\
                                            `addtime` int(11) unsigned NOT NULL DEFAULT \'0\' COMMENT \'时间\',\
                                            PRIMARY KEY (`id`),\
                                            UNIQUE KEY `idx_order_id` (`merchant_order_no`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=39 DEFAULT CHARSET=utf8")
                # cur.execute("drop table coin_chat;")
                cur.execute("CREATE TABLE `coin_chat` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `userid` varchar(20) NOT NULL,\
                                            `username` varchar(255) NOT NULL,\
                                            `orderid` char(15) DEFAULT NULL,\
                                            `content` varchar(255) NOT NULL,\
                                            `sort` int(11) unsigned NOT NULL,\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `endtime` int(11) unsigned NOT NULL,\
                                            `status` tinyint(4) NOT NULL COMMENT '标记  1：已读 2：未读',\
                                            PRIMARY KEY (`id`),\
                                            KEY `status` (`status`), \
                                            KEY `userid` (`userid`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT=\'文字聊天表\'")
                cur.execute("use other;")
                cur.execute("CREATE TABLE `coin_config` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `footer_logo` varchar(200) NOT NULL COMMENT \' \',\
                                            `huafei_zidong` varchar(200) NOT NULL COMMENT \'名称\',\
                                            `kefu` varchar(200) NOT NULL,\
                                            `huafei_openid` varchar(200) NOT NULL COMMENT \'名称\',\
                                            `huafei_appkey` varchar(200) NOT NULL COMMENT \'名称\',\
                                            `index_lejimum` varchar(200) NOT NULL COMMENT \'设置\',\
                                            `login_verify` varchar(200) NOT NULL COMMENT \'设置\',\
                                            `fee_meitian` varchar(200) NOT NULL COMMENT \'设置\',\
                                            `top_name` varchar(200) NOT NULL COMMENT \'设置\',\
                                            `web_name` varchar(200) NOT NULL,\
                                            `web_title` varchar(200) NOT NULL,\
                                            `web_logo` varchar(200) NOT NULL,\
                                            `web_llogo_small` varchar(200) NOT NULL,\
                                            `web_keywords` text NOT NULL,\
                                            `web_description` text NOT NULL,\
                                            `web_close` text NOT NULL,\
                                            `web_close_cause` text NOT NULL,\
                                            `web_icp` text NOT NULL,\
                                            `web_cnzz` text NOT NULL,\
                                            `web_ren` text NOT NULL,\
                                            `web_reg` text NOT NULL,\
                                            `market_mr` text NOT NULL,\
                                            `xnb_mr` text NOT NULL,\
                                            `rmb_mr` text NOT NULL,\
                                            `web_waring` text NOT NULL,\
                                            `moble_type` text NOT NULL,\
                                            `moble_url` text NOT NULL,\
                                            `moble_user` text NOT NULL,\
                                            `moble_pwd` text NOT NULL,\
                                            `moble_pwd_int` text NOT NULL,\
                                            `moble_user_int` text NOT NULL,\
                                            `contact_moble` text NOT NULL,\
                                            `contact_weibo` text NOT NULL,\
                                            `contact_tqq` text NOT NULL,\
                                            `contact_qq` text NOT NULL,\
                                            `contact_qqun` text NOT NULL,\
                                            `contact_weixin` text NOT NULL,\
                                            `contact_weixin_img` text NOT NULL,\
                                            `contact_email` text NOT NULL,\
                                            `contact_alipay` text NOT NULL,\
                                            `contact_alipay_img` text NOT NULL,\
                                            `contact_bank` text NOT NULL,\
                                            `user_truename` text NOT NULL,\
                                            `user_moble` text NOT NULL,\
                                            `user_alipay` text NOT NULL,\
                                            `user_bank` text NOT NULL,\
                                            `user_text_truename` text NOT NULL,\
                                            `user_text_moble` text NOT NULL,\
                                            `user_text_alipay` text NOT NULL,\
                                            `user_text_bank` text NOT NULL,\
                                            `user_text_log` text NOT NULL,\
                                            `user_text_password` text NOT NULL,\
                                            `user_text_paypassword` text NOT NULL,\
                                            `mytx_min` decimal(32,16) NOT NULL DEFAULT \'0.00000000\',\
                                            `mytx_max` decimal(32,16) NOT NULL DEFAULT \'0.00000000\',\
                                            `mytx_bei` text NOT NULL,\
                                            `mytx_coin` text NOT NULL,\
                                            `mytx_fee` decimal(32,16) NOT NULL DEFAULT \'0.00000000\',\
                                            `trade_min` decimal(32,16) NOT NULL DEFAULT \'0.00000000\',\
                                            `trade_max` decimal(32,16) NOT NULL DEFAULT \'0.00000000\',\
                                            `trade_limit` decimal(32,16) NOT NULL DEFAULT \'0.00000000\',\
                                            `trade_text_log` text NOT NULL,\
                                            `issue_ci` text NOT NULL,\
                                            `issue_jian` text NOT NULL,\
                                            `issue_min` decimal(32,16) NOT NULL DEFAULT \'0.00000000\',\
                                            `issue_max` decimal(32,16) NOT NULL DEFAULT \'0.00000000\',\
                                            `money_min` decimal(32,16) NOT NULL DEFAULT \'0.00000000\',\
                                            `money_max` decimal(32,16) NOT NULL DEFAULT \'0.00000000\',\
                                            `money_bei` text NOT NULL,\
                                            `money_text_index` text NOT NULL,\
                                            `money_text_log` text NOT NULL,\
                                            `money_text_type` text NOT NULL,\
                                            `invit_type` text NOT NULL,\
                                            `invit_text_txt` text NOT NULL,\
                                            `invit_text_log` text NOT NULL,\
                                            `index_notice_1` text NOT NULL,\
                                            `index_notice_11` text NOT NULL,\
                                            `index_notice_2` text NOT NULL,\
                                            `index_notice_22` text NOT NULL,\
                                            `index_notice_3` text NOT NULL,\
                                            `index_notice_33` text NOT NULL,\
                                            `index_notice_4` text NOT NULL,\
                                            `index_notice_44` text NOT NULL,\
                                            `text_footer` text NOT NULL,\
                                            `shop_text_index` text NOT NULL,\
                                            `shop_text_log` text NOT NULL,\
                                            `shop_text_addr` text NOT NULL,\
                                            `shop_text_view` text NOT NULL,\
                                            `huafei_text_index` text NOT NULL,\
                                            `huafei_text_log` text NOT NULL,\
                                            `addtime` int(11) unsigned NOT NULL,\
                                            `status` int(4) NOT NULL,\
                                            `shop_coin` varchar(200) NOT NULL COMMENT \'计算方式\',\
                                            `shop_logo` varchar(200) NOT NULL COMMENT \'商城 LOGO\',\
                                            `shop_login` varchar(200) NOT NULL COMMENT \'是否要登陆\',\
                                            `index_html` varchar(50) DEFAULT NULL,\
                                            `trade_hangqing` varchar(50) DEFAULT NULL,\
                                            `trade_moshi` varchar(50) DEFAULT NULL,\
                                            `company_name` varchar(200) DEFAULT \'\',\
                                            `company_addr` varchar(200) DEFAULT \'\',\
                                            `app_version` varchar(200) DEFAULT \'\',\
                                            `app_version_code` varchar(30) DEFAULT NULL COMMENT \'app 版本号数（Android 使用）\',\
                                            `login_verify_sms` tinyint(1) DEFAULT \'0\' COMMENT \'是否短信验证登录 1 需要 0 不需要\',\
                                            `login_limit_num` int(10) DEFAULT \'1\' COMMENT \'登录错误限制次数\',\
                                            `login_limit_time` int(10) DEFAULT \'60\' COMMENT \'登录限制，禁止登录时间 单位 秒\',\
                                            `chart_config` text COMMENT \'图表配置\',\
                                            `login_keep_time` int(11) DEFAULT \'1\' COMMENT \'用户保持登录时常（单位小时）\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT=\'系统配置表\'")

                cur.execute("CREATE TABLE `coin_config_other` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `type` varchar(60) DEFAULT \'about_us\' COMMENT \'类型 \'\'about_us\'\' 关于我们\',\
                                            `name` varchar(300) DEFAULT NULL COMMENT \'显示名称\',\
                                            `data_1` varchar(600) DEFAULT NULL COMMENT \'数据 1\',\
                                            `data_2` varchar(600) DEFAULT NULL COMMENT \'数据 2\',\
                                            `data_3` varchar(600) DEFAULT NULL COMMENT \'数据 3\',\
                                            `data_4` varchar(600) DEFAULT NULL COMMENT \'数据 4\',\
                                            `data` text COMMENT \'其他配置数据(序列化)\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'状态 1：正常 0：禁用\',\
                                            `is_edit` tinyint(3) NOT NULL DEFAULT \'0\' COMMENT \'是否后台编辑\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8")
                cur.execute("CREATE TABLE `user_device` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT COMMENT \'id\',\
                                            `device_id` varchar(200) NOT NULL COMMENT \'设备唯一识别码\',\
                                            `uid` bigint(20) NOT NULL DEFAULT \'0\' COMMENT \'用户id\',\
                                            `name` varchar(200) DEFAULT \'\' COMMENT \'设备名称\',\
                                            `token` varchar(200) NOT NULL DEFAULT \'\' COMMENT \'token\',\
                                            `token_time` int(11) NOT NULL DEFAULT \'0\' COMMENT \'token更新时间\',\
                                            `public_key` varchar(200) DEFAULT \'\' COMMENT \'公钥\',\
                                            `equipment` text COMMENT \'设备信息 数组序列化\',\
                                            `comment` varchar(50) DEFAULT \'\' COMMENT \'设备备注\',\
                                            `source_type` tinyint(1) DEFAULT \'0\' COMMENT \'0:未知 1:ukex 2:ukexpay\',\
                                            `status` tinyint(1) DEFAULT \'0\' COMMENT \'-1:禁用 0:正常 1:主要\',\
                                            `create_time` int(11) NOT NULL DEFAULT \'0\' COMMENT \'创建时间\',\
                                            `update_time` int(11) NOT NULL DEFAULT \'0\' COMMENT \'更新时间\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=1646 DEFAULT CHARSET=utf8 COMMENT='用户设备信息';")
                # cur.execute("drop table coin_global_indexs;")
                cur.execute("CREATE TABLE `coin_global_indexs` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `coin_name` varchar(60) NOT NULL,\
                                            `full_name` varchar(90) NOT NULL DEFAULT \'\',\
                                            `img` varchar(300) NOT NULL DEFAULT \'\' COMMENT \'图片地址\',\
                                            `app_img` varchar(300) NOT NULL DEFAULT \'\' COMMENT \'手机图片\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'状态 1 ：正常 0 ：禁用\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 COMMENT=\'全球指数币种配置表\'")
                # cur.execute("drop table coin_shard;")
                cur.execute("CREATE TABLE `coin_shard` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT COMMENT \'碎片 id\',\
                                            `name` varchar(200) DEFAULT NULL COMMENT \'碎片位置名称\',\
                                            `sort` int(11) DEFAULT NULL COMMENT \'排序，越小越靠前\',\
                                            `note` varchar(300) DEFAULT NULL COMMENT \'备注信息\',\
                                            `status` tinyint(1) DEFAULT \'1\' COMMENT \'状态 1 正常 0 禁用\',\
                                            PRIMARY KEY (`id`)\
                                            ) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COMMENT=\'碎片表（特定位置的广告，运营数据）\'")
                # cur.execute("drop table coin_shard_data;")
                cur.execute("CREATE TABLE `coin_shard_data` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `shard_id` int(11) DEFAULT NULL COMMENT \'所属碎片 id\',\
                                            `title` varchar(300) DEFAULT NULL COMMENT \'文字标题\',\
                                            `content` text COMMENT \'内容\',\
                                            `img` varchar(300) DEFAULT NULL COMMENT \'图片地址\',\
                                            `url` varchar(300) DEFAULT NULL COMMENT \'跳转地址\',\
                                            `lang` varchar(30) DEFAULT NULL COMMENT \'所属语言类型 eg zh_cn ,\ en_us\',\
                                            `sort` int(11) DEFAULT NULL COMMENT \'排序，越小越靠前\',\
                                            `data_1` varchar(300) DEFAULT NULL COMMENT \'扩展字段 1\',\
                                            `data_2` varchar(300) DEFAULT NULL COMMENT \'扩展字段 2\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `shard_id_lang` (`shard_id`,`lang`) USING BTREE \
                            ) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COMMENT=\'碎片具体数据\'")
                # cur.execute("drop table coin_text;")
                cur.execute("CREATE TABLE `coin_text` (\
                                            `id` int(11) unsigned NOT NULL AUTO_INCREMENT,\
                                            `name` varchar(255) NOT NULL DEFAULT \'\',\
                                            `title` varchar(255) NOT NULL DEFAULT \'\',\
                                            `content` text NOT NULL,\
                                            `sort` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `addtime` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `endtime` int(11) unsigned NOT NULL DEFAULT \'0\',\
                                            `status` tinyint(4) NOT NULL DEFAULT \'0\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `status` (`status`), \
                                            KEY `name` (`name`) \
                                            ) ENGINE=InnoDB AUTO_INCREMENT=58 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC")
                # cur.execute("drop table coin_ticket_coupon;")
                cur.execute("CREATE TABLE `coin_ticket_coupon` (\
                                            `code` varchar(50) NOT NULL COMMENT \'唯一 SN\',\
                                            `type` varchar(20) NOT NULL DEFAULT \'coin\' COMMENT \'类型 coin:虚拟币 currency:货币\',\
                                            `tmp_id` int(11) NOT NULL DEFAULT \'0\' COMMENT \'对应模板 ID\',\
                                            `coin_id` int(11) NOT NULL DEFAULT \'0\' COMMENT \'币种 ID\',\
                                            `issuer_id` int(11) NOT NULL DEFAULT \'0\' COMMENT \'发行者 ID\',\
                                            `receive_id` int(11) NOT NULL DEFAULT \'0\' COMMENT \'接收者 ID\',\
                                            `amount` decimal(32,16) NOT NULL DEFAULT \'0.00000000\' COMMENT \'金额\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'1\' COMMENT \'状态 2:已使用 1:已发放 0:未发放 -1:已回收 -2:已禁用\',\
                                            `used_time` int(11) NOT NULL DEFAULT \'0\' COMMENT \'使用时间\',\
                                            `recycled_time` int(11) NOT NULL DEFAULT \'0\' COMMENT \'回收时间\',\
                                            `received_time` int(11) NOT NULL DEFAULT \'0\' COMMENT \'接收时间\',\
                                            `created` int(11) NOT NULL DEFAULT \'0\' COMMENT \'创建时间(发行时间)\',\
                                            `updated` int(11) NOT NULL DEFAULT \'0\' COMMENT \'修改时间\',\
                                            `rule_ext` text COMMENT \'独立于模板的限定规则及拓展数据(有效起止时间等相关信息) 序列化数组\',\
                                            PRIMARY KEY (`code`),\
                                            KEY `idx_ticket_coupon` (`tmp_id`,`receive_id`,`issuer_id`,`status`) USING BTREE \
                            ) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT=\'优惠券实体\'")
                # cur.execute("drop table coin_ticket_template;")
                cur.execute("CREATE TABLE `coin_ticket_template` (\
                                            `id` int(11) NOT NULL AUTO_INCREMENT,\
                                            `type` varchar(10) DEFAULT \'ticket\' COMMENT \'类型 coupon:优惠券 ticket:票\',\
                                            `title` varchar(200) DEFAULT NULL COMMENT \'显示名称\',\
                                            `content` varchar(300) DEFAULT NULL COMMENT \'内容描述\',\
                                            `ico` varchar(300) DEFAULT NULL COMMENT \'图标\',\
                                            `url` varchar(600) DEFAULT NULL COMMENT \'跳转地址\',\
                                            `rule_ext` text COMMENT \'限定规则及拓展数据 序列化数组\',\
                                            `status` tinyint(1) NOT NULL DEFAULT \'0\' COMMENT \'状态 0:正常 -1:禁用\',\
                                            `created` int(11) NOT NULL DEFAULT \'0\' COMMENT \'创建时间戳\',\
                                            `updated` int(11) NOT NULL DEFAULT \'0\' COMMENT \'修改时间戳\',\
                                            PRIMARY KEY (`id`),\
                                            KEY `idx_ticket_template` (`type`,`title`,`url`(255),`status`) USING BTREE \
                            ) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT=\'票券模板\'")
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()
    def loadCoinCoin(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                for Obj in selectList:
                    Obj['cs_zl'] = '0.0'
                    Obj['cs_cl'] = '0.0'
                    Obj['cs_jl'] = '0.0'
                    if Obj['zr_zs'] == '':
                        Obj['zr_zs'] = '0.0'
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()
    def loadCxbapply(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                for Obj in selectList:
                    Obj['user_id'] = dbOper.getNewUserId(str(Obj['user_id']))
                    Obj['token_max_number'] = '0.0'
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()

    def loadCoinMarket(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                for Obj in selectList:
                    if Obj['invit_1'] == '':
                        Obj['invit_1'] = '0.0'
                    if Obj['invit_2'] == '':
                        Obj['invit_2'] = '0.0'
                    if Obj['invit_3'] == '':
                        Obj['invit_3'] = '0.0'
                    if Obj['zhang'] == '':
                        Obj['zhang'] = '0.0'
                    if Obj['die'] == '':
                        Obj['die'] = '0.0'
                    if Obj['fee_buy'] == '':
                        Obj['fee_buy'] = '0.0'
                    if Obj['fee_sell'] == '':
                        Obj['fee_sell'] = '0.0'
                    if Obj['buy_min'] == '':
                        Obj['buy_min'] = '0.0'
                    if Obj['buy_max'] == '':
                        Obj['buy_max'] = '0.0'
                    if Obj['sell_min'] == '':
                        Obj['sell_min'] = '0.0'
                    if Obj['sell_max'] == '':
                        Obj['sell_max'] = '0.0'
                    if Obj['trade_min'] == '':
                        Obj['trade_min'] = '0.0'
                    if Obj['trade_max'] == '':
                        Obj['trade_max'] = '0.0'
                    if Obj['hou_price'] == '':
                        Obj['hou_price'] = '0.0'
                        
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()
    def loadStatusData(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                for Obj in selectList:
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()
    def loadCoinOnfidokycApplication(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                for Obj in selectList:
                    Obj['uid'] = dbOper.getNewUserId(str(Obj['uid']))
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()

    def getNewUserId(self,ukexuid):
        if str(ukexuid) == '0':
            return '0'
        for userInfo in mappingList:
            if str(userInfo['ukex_uid']) == str(ukexuid):
                return str(userInfo['user_id'])
        return '777777'
    def getNewUserIdFromPay(self,ukexpayuid):
        if str(ukexpayuid) == '0':
            return '0'
        for userInfo in mappingList:
            if str(userInfo['ukexpay_uid']) == str(ukexpayuid):
                return str(userInfo['user_id'])
        return '777777'
    def synchCoinID(self):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                cur = con.cursor()
                cur.execute('use base;')
                cur.execute('select id as id,name as name from coin_coin;')
                searchUkexList = cur.fetchall()
                searchUkexpayList = list(database.selectSQL(database.ukexpay_cursor,"coin_id as id,coin_name as name",'cnuk_coin;'))
                # 更新ukexpay中的coin_id
                for obj in searchUkexList:
                    for objpay in searchUkexpayList:
                        if obj[1] == objpay['name'].lower():
                            database.update(database.ukexpay_cursor,'cnuk_coin set coin_id = '+ str(obj[0]) + ' where coin_name = "' + str(obj[1]) + '";')
                # ukex中没有的ukexpay的coin_id信息反填
                for obj in searchUkexList:
                    for objpay in searchUkexpayList:
                        if obj[1] == objpay['name'].lower():
                            searchUkexpayList.remove(objpay)
                for insertObj in searchUkexpayList:
                    Obj = {}
                    Obj['id'] = insertObj['id']
                    Obj['name'] = insertObj['name'].lower()
                    Obj['type'] = ''
                    Obj['title'] = ''
                    Obj['img'] = ''
                    Obj['img_ext1'] = ''
                    Obj['app_img'] = ''
                    Obj['sort'] = '0'
                    Obj['fee_bili'] = ''
                    Obj['endtime'] = '0'
                    Obj['addtime'] = '0'
                    Obj['status'] = '0'
                    Obj['fee_meitian'] = ''
                    Obj['dj_zj'] = ''
                    Obj['dj_dk'] = ''
                    Obj['dj_yh'] = ''
                    Obj['dj_mm'] = ''
                    Obj['zr_zs'] = '0.0'
                    Obj['zr_jz'] = '0'
                    Obj['zr_dz'] = ''
                    Obj['zr_sm'] = ''
                    Obj['zc_sm'] = ''
                    Obj['zc_fee'] = '0.0'
                    Obj['zc_mfee'] = '0'
                    Obj['zc_user'] = ''
                    Obj['zc_min'] = '0.0'
                    Obj['zc_min_zn'] = '0.0'
                    Obj['zc_max'] = '0.0'
                    Obj['zc_jz'] = '0'
                    Obj['zc_zd'] = '0.0'
                    Obj['js_yw'] = ''
                    Obj['js_sm'] = ''
                    Obj['js_qb'] = ''
                    Obj['js_ym'] = ''
                    Obj['js_gw'] = ''
                    Obj['js_lt'] = ''
                    Obj['js_wk'] = ''
                    Obj['cs_yf'] = ''
                    Obj['cs_sf'] = ''
                    Obj['cs_fb'] = ''
                    Obj['cs_qk'] = ''
                    Obj['cs_zl'] = '0.0'
                    Obj['cs_cl'] = '0.0'
                    Obj['cs_zm'] = ''
                    Obj['cs_nd'] = ''
                    Obj['cs_jl'] = '0.0'
                    Obj['cs_ts'] = ''
                    Obj['cs_bz'] = ''
                    Obj['zc_wtdays'] = '0'
                    Obj['zr_tips'] = ''
                    Obj['auto_zc_day_num'] = '0'
                    Obj['auto_zc_rate'] = '0'
                    Obj['is_split_addr'] = '0'
                    Obj['is_usable_integra'] = '0'
                    colmun = ['id','name','type','title','img','img_ext1','app_img','sort','fee_bili','endtime','addtime','status','fee_meitian','dj_zj','dj_dk','dj_yh','dj_mm',
                                      'zr_zs','zr_jz','zr_dz','zr_sm','zc_sm','zc_fee','zc_mfee','zc_user','zc_min','zc_min_zn','zc_max','zc_jz','zc_zd','js_yw','js_sm','js_qb','js_ym','js_gw',
                                      'js_lt','js_wk','cs_yf','cs_sf','cs_fb','cs_qk','cs_zl','cs_cl','cs_zm','cs_nd','cs_jl','cs_ts','cs_bz','zc_wtdays',
                                      'zr_tips','auto_zc_day_num','auto_zc_rate','is_split_addr','is_usable_integra']
                    tableColumns = self.makeInsertPackage(Obj, colmun, 'coin_coin')
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()

                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()

    def loadCoinConfig(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                for Obj in selectList:
                    if Obj['mytx_min'] == '':
                        Obj['mytx_min'] = '0.0'
                    if Obj['mytx_max'] == '':
                        Obj['mytx_max'] = '0.0'
                    if Obj['mytx_fee'] == '':
                        Obj['mytx_fee'] = '0.0'
                    if Obj['trade_min'] == '':
                        Obj['trade_min'] = '0.0'
                    if Obj['trade_max'] == '':
                        Obj['trade_max'] = '0.0'
                    if Obj['trade_limit'] == '':
                        Obj['trade_limit'] = '0.0'
                    if Obj['issue_min'] == '':
                        Obj['issue_min'] = '0.0'
                    if Obj['issue_max'] == '':
                        Obj['issue_max'] = '0.0'
                    if Obj['money_min'] == '':
                        Obj['money_min'] = '0.0'
                    if Obj['money_max'] == '':
                        Obj['money_max'] = '0.0'
                        
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()
            
    def loadCoinAddrPool(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                for Obj in selectList:
                    Obj['uid'] = dbOper.getNewUserId(str(Obj['uid']))
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()
    def loadOnlyReplaceUserId(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                for Obj in selectList:
                    if Obj.has_key('user_id'):
                        Obj['user_id'] = dbOper.getNewUserId(str(Obj['user_id']))
                    if Obj.has_key('userid'):
                        Obj['userid'] = dbOper.getNewUserId(str(Obj['userid']))
                    if Obj.has_key('pay_uid'):
                        Obj['pay_uid'] = dbOper.getNewUserId(str(Obj['pay_uid']))
                    if Obj.has_key('accept_uid'):
                        Obj['accept_uid'] = dbOper.getNewUserId(str(Obj['accept_uid']))
                    if Obj.has_key('platform_userid'):
                        Obj['platform_userid'] = dbOper.getNewUserId(str(Obj['platform_userid']))
                    if Obj.has_key('platform_fee_userid'):
                        Obj['platform_fee_userid'] = dbOper.getNewUserId(str(Obj['platform_fee_userid']))
                    if Obj.has_key('fee_userid'):
                        Obj['fee_userid'] = dbOper.getNewUserId(str(Obj['fee_userid']))
                    if Obj.has_key('from_uid'):
                        Obj['from_uid'] = dbOper.getNewUserId(str(Obj['from_uid']))    
                    if Obj.has_key('invit_id'):
                        Obj['invit_id'] = dbOper.getNewUserId(str(Obj['invit_id']))
                        
                        
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()
    def loadCoinTaskConfig(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                
                for Obj in selectList:
                    userids = ''
                    ids = str(Obj['allow_release_uid']).split(',')
                    for id in ids:
                        userids += dbOper.getNewUserId(str(id))
                        userids += ','
                    if userids != '':
                        userids = userids[:-1]
                    Obj['allow_release_uid'] = userids
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()
    def loadCoinTicketCoupon(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                for Obj in selectList:
                    Obj['issuer_id'] = dbOper.getNewUserId(str(Obj['issuer_id']))
                    Obj['receive_id'] = dbOper.getNewUserId(str(Obj['receive_id']))
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()

    def loadUserDeviceData(self,useDBCommand,colmun,tableName,colStr=''):
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.UkexPay_dbAddress, user=dbConfid.UkexPay_userName,
                                      passwd=dbConfid.UkexPay_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukexpay_cursor,colStr,"cnuk_user_device")
                cur = con.cursor()
                cur.execute(useDBCommand)
                colmun.append('source_type')
                for Obj in selectList:
                    Obj['source_type'] = '2'
                    Obj['uid'] = dbOper.getNewUserIdFromPay(str(Obj['uid']))
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()

    def loadCoinUserIdcard(self,useDBCommand,colmun,tableName,colStr=''):
        # 0，12，17
        try:
            con = None
            if con is None:
                dbConfid = Config()
                con = pymysql.connect(host=dbConfid.accountDB_dbAddress, user=dbConfid.accountDB_userName,
                                      passwd=dbConfid.accountDB_password, charset='utf8')
                if colStr == '':
                    colStr = self.getColumns(colmun)
                selectList = database.selectSQL(database.ukex_cursor,colStr,tableName)
                cur = con.cursor()
                cur.execute(useDBCommand)
                for Obj in selectList:
                    Obj['id'] = dbOper.getNewUserId(str(Obj['id']))
                    if Obj['id'] == '0' or Obj['id'] == '777777':
                        continue
                    tableColumns = self.makeInsertPackage(Obj, colmun, tableName)
                    # 最后添加transfer字段，表示新数据都没有被转换过
                    baseSql = 'INSERT INTO '+tableColumns
                    cur.execute(baseSql)
                    con.commit()
                cur.close()
                con.close()
        except:
            import traceback
            traceback.print_exc(file=open('traceback_INFO.txt', 'a+'))
            traceback.print_exc()
    
if __name__ == '__main__':
    reload(sys)
    sys.setdefaultencoding('utf-8')

    dbOper = DBOperation()
    dbOper.createBaseTables()

    database = Database()
    # 创建数据库account中的表
    dbOper.createAccountTables()

    # 加载 user 表的数据A
    dbOper.loadTableUserData()

    # 获取user表中的ukex用户信息和ukexpay的用户信息用于做后续处理
    ukexList = database.selectSQL(database.accountDB_cursor, 'id as user_id, user_account,create_time,update_time',
                                  'user where user_account !="" and source_type = 1')
    ukexpayList = database.selectSQL(database.accountDB_cursor, 'id as user_id, user_account,create_time,update_time',
                                     'user where user_account !="" and source_type = 2')
    # 加载 user_account 表的数据
    dbOper.loadTableUserAccountData()

    mappingList = database.selectSQL(database.accountDB_cursor, 'user_id, ukex_uid,ukexpay_uid,account',
                                     'user_account where account !=""')
    mappingList = list(mappingList)
    tempArray = []
    temp = {}
    for obj in mappingList:
        if temp.has_key(str(obj['ukex_uid'])) and str(obj['ukex_uid']) != '0':
            continue
        else:
            temp[str(obj['ukex_uid'])] = 1
            tempArray.append(obj)
    mappingList = tempArray

    dbOper.loadStatusData('use account',['id','content','addtime'],'coin_user_auth_fail')
    dbOper.loadOnlyReplaceUserId('use account', ['id', 'userid', 'country','bankprov','bankcity','bank','bankaddr','bankcode','sort_code','iban','bankcard','name','username','sort','type','addtime','endtime','status','currency',
                                          'swift','account_number','account_owner','ach_number','wire_number'], 'coin_user_bank')
    dbOper.loadOnlyReplaceUserId('use account', ['id', 'userid', 'auth_fail_reason', 'kyc_fail_reason', 'addtime'], 'coin_user_extend')
    dbOper.loadOnlyReplaceUserId('use account', ['id', 'user_id', 'addtime','status'], 'coin_user_global_orc_recode')
    dbOper.loadOnlyReplaceUserId('use account', ['id', 'user_id', 'biz_no','addtime','endtime','status'], 'coin_user_ocr_recode')

    dbOper.loadStatusData('use admin', ['id', 'email', 'username', 'nickname', 'moble', 'password', 'sort', 'addtime', 'last_login_time', 'last_login_ip', 'endtime', 'status', 'is_notice_tx1', 'is_notice_tx2',
                                        'is_notice_sm', 'is_notice_bs', 'is_notice_mycz'], 'coin_admin')
    dbOper.loadStatusData('use admin', ['id', 'adminid', 'rowid', 'type', 'remark', 'addip', 'addr', 'addtime', 'status', 'data'], 'coin_admin_log')
    dbOper.loadStatusData('use admin', ['group_id', 'extend_id', 'type'], 'coin_auth_extend')
    dbOper.loadStatusData('use admin', ['id', 'module', 'type', 'title', 'description', 'status', 'rules'], 'coin_auth_group')
    dbOper.loadStatusData('use admin', ['uid', 'group_id'], 'coin_auth_group_access')
    dbOper.loadStatusData('use admin', ['id', 'module', 'type', 'name', 'title', 'status', 'condition'], 'coin_auth_rule','id,module,type,name,title,status,`condition`')
    dbOper.loadStatusData('use admin', ['id', 'date', 'coinname', 'balance', 'coin_zr', 'coin_zc', 'coin_zc_coin_fee', 'coin_zc_coin_fee_total', 'coin_zc_fee', 'coin_zc_fee_total', 'trade_fee', 'trade_fee_total',
                                        'fee_total', 'coin_price', 'coin_price_total', 'addtime'], 'coin_count_fee')
    dbOper.loadStatusData('use admin', ['id', 'date', 'coin_a', 'coin_b', 'market', 'price_cny', 'num', 'mum', 'fee', 'fee_gbp', 'amount_cny', 'amount_gbp', 'addtime'], 'coin_count_trade')
    dbOper.loadCxbapply('use admin', ['id', 'user_id', 'user_name', 'email', 'token_name', 'token_symbol', 'official_website', 'white_apper_url', 'token_standard', 'token_addr', 'token_decimal', 'token_issue_date',
                                        'token_max_number', 'token_circulating_number', 'token_description', 'token_audit_report', 'coinmarketcap_line', 'contact_info', 'token_parameters', 'mag', 'main_line_time',
                                        'media_group', 'exchanges_online','addtime','status'], 'coin_cxb_apply')
    dbOper.loadOnlyReplaceUserId('use admin', ['id', 'userid', 'adminid', 'coin_id', 'coinname', 'amount', 'remark', 'ip', 'addtime'], 'coin_finance_tally')
    dbOper.loadStatusData('use admin', ['id', 'title', 'pid', 'sort', 'url', 'hide', 'tip', 'group', 'is_dev', 'ico_name'], 'coin_menu','id,title,pid,sort,url,hide,tip,`group`,is_dev,ico_name')
    
    dbOper.loadStatusData('use assets', ['id','add_time','end_time','start_time','coinname','zr_total','zr_real','zr_fee','zr_temp','zc_total','zc_fee','zc_chain','trade_buy','trade_sell','trade_in',
                                         'trade_mum','invit','income','money','account','coin_num'], 'coin_balance')
    dbOper.loadStatusData('use assets', ['id','coin','platform_assets','cold_wallet_assets','hot_wallet_assets','borrow_amount','differ_assets','valuation_coin','valuation','addtime'], 'coin_balance_liab')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','currency','num','mum','type','tradeno','remark','sort','addtime','endtime','status','truename','name','bank','bankprov','bankcity','bankaddr','bankcard'], 'coin_mycz')
    dbOper.loadStatusData('use assets', ['id','mycz_id','currency','uuid','amout','date','data','create_time'], 'coin_mycz_bank_log')
    dbOper.loadStatusData('use assets', ['id','max','min','code','account_owner','account_number','swift','sort_code','iban','ach_number','wire_number','address','currency','kaihu','truename','addr','country','name',
                                         'title','url','username','password','img','extra','remark','sort','addtime','endtime','status'], 'coin_mycz_type')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','currency','num','fee','mum','truename','name','bank','bankprov','bankcity','bankaddr','bankcode','bankcard','account_number','sort','addtime','endtime',
                                         'status','type'], 'coin_mytx')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','username','payment_id','coinname','accept_user','txid','payment_code','num','fee','coin_fee','mum','balance','sort','addtime','endtime','status','type','is_read','is_verify','chain_status','is_op'], 'coin_myzc')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','username','coinname','txid','type','fee','num','mum','sort','addtime','endtime','status'], 'coin_myzc_fee')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','username','coinname','from_user','txid','payment_code','num','mum','fee','balance','sort','addtime','endtime','type','status','main_coin'], 'coin_myzr')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','user_id','username','coin_name','addr','status','payment_id','standard_address','main_coin'], 'coin_user_coin_addr')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','coin','user_id','usable','freeze','lockup','add_time'], 'coin_user_coin_balance_snapshot')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','coinname','name','addr','payment_id','sort','addtime','endtime','status'], 'coin_user_qianbao')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','code','qrcode','type','expire_time','coinname','num','money','updatetime','addtime'], 'coin_user_transfer_code')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','account_number','consumer_id','has_card','card_id','sort_code','bic','iban','coinname','status','enabled','bank_card','last_four','expire_time','updatetime','addtime',
                                         'account_status','card_status','card_issue_date'], 'coin_user_visa')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','currency','type','transaction_type','from_account_number','from_sort_code','to_account_number','to_sort_code','transaction_id','amount','from_balance','to_balance',
                                         'settlement_date','description','content','addtime'], 'coin_user_visa_log')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','accept_user','accept_uid','coinname','code','num','fee','mum','addtime','endtime','status'], 'coin_znzc')
    dbOper.loadOnlyReplaceUserId('use assets', ['id','userid','from_user','from_uid','coinname','code','num','fee','mum','addtime','endtime','status'], 'coin_znzr')
    
    dbOper.loadCoinCoin('use base',['id','name','type','title','img','img_ext1','app_img','sort','fee_bili','endtime','addtime','status','fee_meitian','dj_zj','dj_dk','dj_yh','dj_mm',
                                      'zr_zs','zr_jz','zr_dz','zr_sm','zc_sm','zc_fee','zc_mfee','zc_user','zc_min','zc_min_zn','zc_max','zc_jz','zc_zd','js_yw','js_sm','js_qb','js_ym','js_gw',
                                      'js_lt','js_wk','cs_yf','cs_sf','cs_fb','cs_qk','cs_zl','cs_cl','cs_zm','cs_nd','cs_jl','cs_ts','cs_bz','zc_wtdays',
                                      'zr_tips','auto_zc_day_num','auto_zc_rate','is_split_addr','is_usable_integra'],'coin_coin')
    dbOper.synchCoinID()
    dbOper.loadStatusData('use base',['id','coin_id','name','main_coin','main_coin_name','zc_fee','zc_mfee','zc_min','zc_max','is_split_addr','is_usable_integra','update_time','status'],'coin_coin_ext')
    dbOper.loadStatusData('use base',['id','country_en','country_cn','code','mcode','number','is_oumeng','is_eaa','is_forbidden','remark_1','remark_2','remark_3'],'coin_country')
    dbOper.loadOnlyReplaceUserId('use base',['id','currency','name','symbol','tx_min','tx_max','tx_multiple','tx_min_fee','tx_fee','sort','status','platform_userid','platform_fee_userid','day_tx_num'],'coin_currency_config')
    dbOper.loadStatusData('use base',['id','name','title','url','img','mytx','remark','sort','addtime','endtime','status'],'coin_user_bank_type')
    dbOper.loadStatusData('use base',['id','name','level','min','max','discount','status'],'coin_vip')
    dbOper.loadOnlyReplaceUserId('use base',['userid','level','update_time'],'coin_vip_user')
    
    dbOper.loadOnlyReplaceUserId('use base',['id','name','currency','symbol','charge','fee','open_fee','open_fee_coin_img','or_open_fee_coin','or_open_fee','or_open_fee_coin_img','status'],'coin_visa_config')
    
    dbOper.loadCoinAddrPool('use exassets', ['id','uid','coin_id','coin_name','main_coin','integration_addr','sub_addr','payment_id','ext','create_time','update_time'], 'coin_addr_pool')
    
    dbOper.loadCoinOnfidokycApplication('use kyc',['id','sn','uid','email','status','create_time','update_time','msg','ext','ocr','auto','edited_ocr','files','reports','handle'],'coin_onfidokyc_application')
    dbOper.loadCoinUserIdcard('use kyc',['id','url1','url2','url3'],'coin_user_idcard')
    dbOper.loadOnlyReplaceUserId('use kyc',['id','userid','type','remark','addip','addr','addtime','status'],'coin_user_log')
    dbOper.loadOnlyReplaceUserId('use kyc',['id','userid','currency','sign','content','is_read'],'coin_user_notification')
    dbOper.loadOnlyReplaceUserId('use kyc',['id','userid','type','remark','addip','addr','status','new_data','old_data','addtime'],'coin_user_operate_log')
    
    dbOper.loadOnlyReplaceUserId('use otc', ['id', 'userid', 'username', 'orderid', 'content', 'sort', 'addtime', 'endtime', 'status'], 'coin_chat')
    dbOper.loadOnlyReplaceUserId('use otc',['id', 'orderid', 'pay_type', 'pay_uid', 'pay_user', 'pay_status', 'pay_time', 'accept_uid', 'accept_user', 'accept_status', 'accept_time', 'market_id', 'task_id', 'coinname', 'currency',
                           'price', 'money', 'num', 'addtime', 'is_cancel', 'cancel_time', 'remark', 'expire_time', 'is_fed'], 'coin_order')
    dbOper.loadOnlyReplaceUserId('use otc',['id', 'userid', 'order_id', 'fed_content', 'fed_file', 'addtime'], 'coin_order_fed')
    dbOper.loadOnlyReplaceUserId('use otc',['id', 'userid', 'merchant_order_no', 'order_no', 'currency', 'num', 'mum', 'type', 'status', 'callback_time', 'addtime'], 'coin_otc_bitmall')
    dbOper.loadOnlyReplaceUserId('use otc',
                          ['id', 'user_id', 'username', 'type', 'is_fixed', 'float_pct', 'market_id', 'coinname', 'country', 'currency', 'price', 'num', 'num_d', 'pay_type', 'pay_banks',
                           'pay_time', 'min_limit', 'max_limit', 'trade_rule','addtime','status','is_del'], 'coin_task')
    dbOper.loadCoinTaskConfig('use otc',
                          ['id', 'coinname', 'currency', 'name', 'task_free_price', 'task_buy_price', 'task_sell_price', 'task_pay_time', 'task_min', 'task_max', 'is_default', 'status', 'allow_release_uid'], 'coin_task_config')
    
    dbOper.loadCoinConfig('use other',['id','footer_logo','huafei_zidong','kefu','huafei_openid','huafei_appkey','index_lejimum','login_verify','fee_meitian','top_name','web_name','web_title','web_logo','web_llogo_small',
                                       'web_keywords','web_description','web_close','web_close_cause','web_icp','web_cnzz','web_ren','web_reg', 'market_mr', 'xnb_mr', 'rmb_mr', 'web_waring', 'moble_type', 'moble_url', 'moble_user',
                                       'moble_pwd', 'moble_pwd_int', 'moble_user_int', 'contact_moble', 'contact_weibo', 'contact_tqq', 'contact_qq','contact_qqun', 'contact_weixin', 'contact_weixin_img', 'contact_email',
                                       'contact_alipay', 'contact_alipay_img', 'contact_bank', 'user_truename', 'user_moble', 'user_alipay', 'user_bank', 'user_text_truename', 'user_text_moble', 'user_text_alipay', 'user_text_bank',
                                       'user_text_log', 'user_text_password', 'user_text_paypassword', 'mytx_min', 'mytx_max', 'mytx_bei', 'mytx_coin', 'mytx_fee', 'trade_min', 'trade_max', 'trade_limit', 'trade_text_log', 'issue_ci',
                                       'issue_jian', 'issue_min', 'issue_max', 'money_min', 'money_max', 'money_bei', 'money_text_index', 'money_text_log', 'money_text_type', 'invit_type',
                                       'invit_text_txt','invit_text_log', 'index_notice_1', 'index_notice_11', 'index_notice_2', 'index_notice_22', 'index_notice_3', 'index_notice_33','index_notice_4','index_notice_44',
                                       'text_footer', 'shop_text_index', 'shop_text_log', 'shop_text_addr', 'shop_text_view', 'huafei_text_index', 'huafei_text_log', 'addtime', 'status', 'shop_coin', 'shop_logo', 'shop_login',
                                       'index_html', 'trade_hangqing','trade_moshi', 'company_name', 'company_addr', 'app_version', 'app_version_code', 'login_verify_sms', 'login_limit_num',
                                       'login_limit_time', 'chart_config', 'login_keep_time'], 'coin_config')
    dbOper.loadStatusData('use other',['id', 'type', 'name', 'data_1', 'data_2', 'data_3', 'data', 'status', 'is_edit'], 'coin_config_other')

    dbOper.loadUserDeviceData('use other',['id', 'device_id', 'uid', 'name', 'token', 'token_time', 'public_key', 'equipment', 'comment','status','create_time','update_time'], 'user_device')
    dbOper.loadStatusData('use other',['id', 'coin_name', 'full_name', 'img', 'app_img', 'status'], 'coin_global_indexs')
    dbOper.loadStatusData('use other',['id', 'name', 'sort', 'note', 'status'], 'coin_shard')
    dbOper.loadStatusData('use other',['id', 'shard_id', 'title', 'content', 'img', 'url', 'lang', 'sort', 'data_1', 'data_2'], 'coin_shard_data')
    dbOper.loadStatusData('use other',['id', 'name', 'title', 'content', 'sort', 'addtime', 'endtime', 'status'], 'coin_text')
    dbOper.loadCoinTicketCoupon('use other',['code', 'type', 'tmp_id', 'coin_id', 'issuer_id', 'receive_id', 'amount', 'status', 'used_time', 'recycled_time', 'received_time', 'created', 'updated', 'rule_ext'], 'coin_ticket_coupon')
    dbOper.loadStatusData('use other',['id', 'type', 'title', 'content', 'ico', 'url', 'rule_ext', 'status', 'created', 'updated'], 'coin_ticket_template')
    
    dbOper.loadOnlyReplaceUserId('use trade', ['id', 'tel', 'invit_id'],'coin_invit_tel')

    dbOper.loadCoinMarket('use trade', ['id', 'name', 'round', 'round_buy_sell_num', 'fee_buy', 'fee_sell', 'fee_user_id', 'buy_min', 'buy_max', 'sell_min', 'sell_max', 'trade_min', 'trade_max', 'invit_buy', 'invit_sell',
                                        'invit_1', 'invit_2', 'invit_3', 'zhang', 'die', 'hou_price', 'tendency', 'trade','new_price', 'buy_price', 'sell_price', 'min_price', 'max_price', 'volume', 'change', 'api_min',
                                        'api_max','sort','addtime','endtime','status'],'coin_market','id,name,round,round_buy_sell_num,fee_buy,fee_sell,fee_user_id,buy_min,buy_max,sell_min,sell_max,trade_min,trade_max,invit_buy,invit_sell,invit_1,invit_2,invit_3,zhang,die,hou_price,tendency,trade,new_price,buy_price,sell_price,min_price,max_price,volume,`change`,api_min,api_max,sort,addtime,endtime,status')
    dbOper.loadStatusData('use trade', ['id', 'name', 'data', 'type', 'sort', 'addtime', 'endtime', 'status'],'coin_market_json')

    # 创建数据库assets中的表
    dbOper.createAssetsTables()

    # 创建数据库 sa 中的表
    dbOper.createSATables()

    # 创建数据库 trade 中的表
    dbOper.createTradeTables()

    # 加载 user_auth 表的数据
    dbOper.loadTableUserAuthData()

    # 加载 user_facts 表的数据
    dbOper.loadTableUserFactsData()

    # 加载 user_info 表的数据
    dbOper.loadTableUserInfoData()

    # 创建所有币种的资产表
    dbOper.createCoinTable()
    # 加载各资产表中的用户信息
    dbOper.loadTableUserAssetsData()

    # # print('-------------------------分割线以下是BackTrade部分------------------------------')
    coinMappingList = database.selectSQL(database.ukex_cursor, 'name, id','coin_coin')
    marketMappingList = database.selectSQL(database.ukex_cursor, 'name, id','coin_market')
    coinnameMapping = {}
    for coinObj in coinMappingList:
        coinnameMapping[coinObj['name']] = coinObj['id']

    marketMapping = {}
    for marketObj in marketMappingList:
        marketMapping[marketObj['name']] = marketObj['id']

    # 加载 recommended_trade_award 表的数据
    dbOper.loadTableRecommendedTradeAwardData()

    # 加载 kline_minimum 表的数据
    dbOper.loadTableKLineMinData()

    # 加载 kline_record 表的数据
    dbOper.loadTableKLineRecordData()

    # 加载 financial_records 表的数据R
    dbOper.loadTableFinancialRecordsData()

    # 加载 wait_[market_id] & close_[market_id] 表的数据
    dbOper.createWaitCloseTables()
    dbOper.loadTableWaitMarketData()
    dbOper.loadTableCloseMarketData()

    # 加载 coin_trade_log 表中的数据
    tradeDataList = database.selectSQL(database.ukex_cursor, 'id, userid as buyer_user_id, peerid as seller_user_id, market as market_id , price, num as trading_volume, mum as trading_amount, fee_buy as buyer_fee,'
                                                             'fee_sell as seller_fee,  type as oper_type, buy_id as buyer_order_id, sell_id as seller_order_id,addtime as create_time, addtime as update_time','coin_trade_log')
    Match_Year = {}
    for obj in tradeDataList:
        timeStamp = obj['create_time']
        timeArray = time.localtime(timeStamp)
        if Match_Year.has_key(str(timeArray.tm_year)):
            setArray = Match_Year[str(timeArray.tm_year)]
            tableName = str(timeArray.tm_mon) + '_' + str(timeArray.tm_mday)
            setArray.add(tableName)
        else:
            tableName = str(timeArray.tm_mon) + '_' +str(timeArray.tm_mday)
            setArray = {tableName}
            Match_Year[str(timeArray.tm_year)] = setArray

    # 创建数据库和表
    dbOper.createTradeLog()
    dbOper.loadTableTradeLogData()

