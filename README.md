<h1 align="center">IdCenterSender-so ---分布式64位ID发号器,PHP扩展版本</h1>

### PHP语言实现版本

- [IdCenterSender - PHP原生版本](https://github.com/whiteCcinn/IdCenterSender-so)

分布式64位ID发号器,PHP扩展版本

## 原理

参考Snowflake算法,根据自身设计情况扩展了其中的细节。具体组成如下图：
	
![bits_struct.jpg](https://raw.githubusercontent.com/whiteCcinn/IdCenterSender/master/pic/bits_struct.png)

> 如图所示，64bits 分成了4个部分。

> 0. 最高位舍弃
> 1. 毫秒级的时间戳,有41个bit.能够使用139年，当然这些是可以扩展的,可以通知指定起始时间来延长这个日期长度。也就是说服务启动开始之后就可以持续使用139年
> 2. 自定义分布式机器节点id,占位12个bit,能够支持8191个节点。部署的时候可以配置好服务器id,也就是代码里面的node_id变量，每一台机器都需要用不同的node_id来标志，就像mysql的server_id一样
> 3. 进程（毫秒）自增序号。占位10bit,一毫秒能产生2047个id。

## 总结特点：
- 类snowflake算法
- ID发号器有效期可以延续从发布开始的139年
- 分布式支持8191台机器
- 单进程调用的情况下，并发每秒支持200万个ID生成

## 扩展的形式特点-唯一性保证：
- 结合自旋锁+共享内存实现的高并发ID发号
- 安装扩展之后，无需额外的类库，直接调用PHP的接口 `ck_get_id()` 即可。


## 安装步骤

```
phpize
./configure
make && make install
```

把扩展添加到 `php.ini` 中。默认情况如下操作
```
vim /etc/php.ini

extension=cckeyid.so
```

并且添加分布式节点和服务起始时间戳
```
vim /etc/php.ini

// 添加如下sections
[Cckeyid]
;0-8191
cckeyid.node_id=0
;< (int)current-time
cckeyid.epoch=0
```

重启服务器

## 使用

```
var_dump(ck_get_id());

//output:string(19) "3146501943896047616"
```
