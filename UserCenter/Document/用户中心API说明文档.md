[TOC]

# 历史记录
日期		 | 作者		| 内容
-------------|----------|------------------------------
2019-12-30   | WYP     | 文档创建


日期		 | 作者		| API名称                            |描述
-------------|---------|------------------------------------|---------------------------------|---------------------------------------------------------------
2019-12-30   | WYP     | [api/UserCenter/Login](#Login)      | 创建


# API说明
- 用户中心server与ukex和ukexpay服务端之间采用Http通信
- 接口相对路径：/api/{0}/{1}，其中0和1为不同接口动态变化的值
- 带删除线的接口为废弃接口，但仍在使用。不再使用的接口会直接从文档删除

## header说明
- 必填项为token

### User-Agent
- 无


## json格式说明
服务端返回的json将包含固定的status和数据字段data。

## 状态码Code
状态码将分不同的号段供不同的接口使用，以达到根据编号即可查出是哪个接口的哪个错误。


## 返回值格式
格式一：返回单个值

    {"status": 1, "data":31276}

格式二：返回对象

    {"status": 1,"data":{"Name":"兑换商品1", "Desc":"兑换商品描述"}}

格式三：返回列表

    {"status": 1,"data":[
        {"Name":"兑换商品1", "Desc":"兑换商品描述"},
        {"Name":"兑换商品1", "Desc":"兑换商品描述"}
    ]}

# 接口及数据报文
## http 客户端API请求

### 新增用户账号
> <a id="Login">Api/UserCenter/Login</a>
> 作者 ：吴友鹏

是否携带token：否

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
usercount              | string            |  是  | 用户账号
password               | string            |  是  | 用户密码
source_type            | int               |  是  | 来源类型 1-ukex；2-ukexpay；

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "添加成功"/"添加失败"

### 登录
> <a id="Login">Api/UserCenter/Login</a>
> 作者 ：吴友鹏

是否携带token：否

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
usercount              | string            |  是  | 用户账号
password               | string            |  是  | 用户密码

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data

字段                   | 数据类型           | 必填 | 备注
-----------------------|-------------------|------|--------------------------
token                  | string            |  是  | server生成的token
deadLine               | int               |  是  | token截至日期
uid                    | string            |  是  | userid

### 更新登录密码
> <a id="passwordLogin">Api/Password/Login</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
usercount              | string            |  是  | 用户账号
password               | string            |  是  | 用户密码

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "密码修改成功"/"密码修改失败"


### 交易密码
> <a id="passwordPay">Api/Password/Pay</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
uid                    | string            |  是  | 用户id
paypassword            | string            |  是  | 支付密码
oper_type              | int               |  是  | 操作类型：1-验证交易密码；2-修改交易密码

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "验证成功"/"验证失败" or "修改成功"/"修改失败"


### 设备绑定
> <a id="AddBindDevice">Api/Device/AddBindDevice</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
uid                    | string            |  是  | 用户id
device_id              | string            |  是  | 设备唯一码
device_name            | string            |  是  | 设备名称
device_os              | string            |  是  | 设备系统

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "绑定成功"/"绑定失败"

### 删除设备绑定
> <a id="RemoveBindDevice">Api/Device/RemoveBindDevice</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
uid                    | string            |  是  | 用户id
device_id              | string            |  是  | 设备唯一码

响应status:
{"0":154221241,"1":"142       ","2":"           8400.23              ","3":"           8400.23              ","4":"           8400.23              ","5":"           8400.23              "}

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "移除成功"/"移除失败"

### 检测设备绑定
> <a id="CheckBindDevice">Api/Device/CheckBindDevice</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
uid                    | string            |  是  | 用户id
device_id              | string            |  是  | 设备唯一码

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data 
字段                   | 数据类型           | 必填 | 备注
-----------------------|-------------------|------|--------------------------
groupid                | string            |  是  | 用户组id，1：超级管理员；2：普通用户

### 用户权限信息
> <a id="UserAuth">Api/User/Auth</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
column                 | List<T>            |  是  | 新增字段名
value                  | List<T>            |  是  | 对应字段的值
oper_type              | int                |  是  | 1-新增权限数据；2-修改权限数据；3-查找验证权限数据

T -> column:
字段                   | 数据类型           | 必填 | 描述
-----------------------|-------------------|------|--------------------------
"is_allow_login"       | string            |  是  | 对应权限字段名

T -> value:
值                     | 数据类型           | 必填 | 描述
-----------------------|-------------------|------|--------------------------
1                      | int               |  是  | column对应字段值

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "操作成功"/"操作失败"

### 用户信息
> <a id="UserInfo">Api/User/Info</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
column                 | List<T>            |  是  | 新增字段名
value                  | List<T>            |  是  | 对应字段的值
oper_type              | int                |  是  | 1-修改数据；2-查找数据

T -> column:
字段                   | 数据类型           | 必填 | 描述
-----------------------|-------------------|------|--------------------------
"mobile"               | string            |  是  | 对应权限字段名

T -> value:
值                     | 数据类型           | 必填 | 描述
-----------------------|-------------------|------|--------------------------
"13628379881"          | string            |  是  | column对应字段值

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "操作成功"/"操作失败"


### 用户真实信息
> <a id="UserRealInfo">Api/User/RealInfo</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
column                 | List<T>            |  是  | 新增字段名
value                  | List<T>            |  是  | 对应字段的值
oper_type              | int                |  是  | 1-修改数据；2-查找数据

T -> column:
字段                   | 数据类型           | 必填 | 描述
-----------------------|-------------------|------|--------------------------
"first_name"           | string            |  是  | 对应权限字段名

T -> value:
值                     | 数据类型           | 必填 | 描述
-----------------------|-------------------|------|--------------------------
"wu"                   | string            |  是  | column对应字段值

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "操作成功"/"操作失败"

### 资产新增
> <a id="BalanceAdd">Api/Balance/AddBalance</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
coinId                 | string            |  是  | 充值货币id
quantityNum            | string            |  是  | 充值到账数量


响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "充值成功"/"充值失败"


### 资产减少
> <a id="BalanceReduce">Api/Balance/ReduceBalance</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
coinId                 | string            |  是  | 充值货币id
quantityNum            | string            |  是  | 充值减少数量


响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "操作成功"/"操作失败"

### 资产转移
> <a id="BalanceReduce">Api/Balance/ReduceBalance</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
buyerUserId            | string            |  是  | 购买者userid
sellerUserId           | string            |  是  | 出售者userid
coinId                 | string            |  是  | 货币id
transNum               | string            |  是  | 交易数量

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "操作成功"/"操作失败"

### 资产配置
> <a id="BalanceAllocation">Api/Balance/AllocationBalance</a>
> 作者 ：吴友鹏

是否携带token：是

请求方式：POST

请求数据：

字段                    | 数据类型          | 必填 | 备注
-----------------------|-------------------|------|--------------------------
UserId                 | string            |  是  | 用户id
coinId                 | string            |  是  | 被配置的货币id
AssetsNum              | string            |  是  | 被配置资产数量 
oper_type              | int               |  是  | 1-冻结资产；2-解冻资产

响应status:

- 0 ：status 失败
- 1 ：status 成功

响应数据：data = "操作成功"/"操作失败"