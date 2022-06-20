# networkDiagnostics

本工具已经在iOS端实现了 Ping、Telnet、Mtr、Dig、Curl 等的终端命令逻辑的工具，并且支持并发操作。
支持的平台：iphone、ipad、mac
本工具的实现都是用socket底层实现的，目前正在开发android和flutter插件工具。
联系方式：qq 450010152

# step 1
add gameNetworkDiagnostics.a 、 libresolv.tbd

# step 2
use pingHost 、curlAddress、 mtrHost、 telnetHost 、 digDomain

this is the result:

2022-06-20 16:45:30.303100+0800 networkDiagnostics[25046:8523480] 网络信息一键诊断
当前本机IP: {
    "awdl0/ipv6" = "fe80::342f:46ff:fe25:9041";
    deviceNetIP = "127.0.0.1";
    "en0/ipv4" = "172.16.1.6";
    "en0/ipv6" = "fe80::815:ab9c:1f84:21d2";
    "en2/ipv4" = "169.254.112.136";
    "en2/ipv6" = "fe80::ca7:f0a8:2fed:b524";
    "ipsec0/ipv6" = "2408:8556:416:7849:145e:808a:ca72:857a";
    "ipsec1/ipv6" = "2408:8556:416:7849:145e:808a:ca72:857a";
    "llw0/ipv6" = "fe80::342f:46ff:fe25:9041";
    "lo0/ipv4" = "127.0.0.1";
    "lo0/ipv6" = "fe80::1";
    netmask = "255.255.252.0";
    "pdp_ip1/ipv6" = "2408:8556:416:7849:f8d1:b531:931a:c72";
    "utun0/ipv6" = "fe80::e756:e417:d0d9:ffd5";
    "utun1/ipv6" = "fe80::7883:7f3:7806:8c60";
    "utun2/ipv6" = "fe80::295:d7af:a1e2:2b49";
    "utun3/ipv6" = "fe80::e37d:caa4:5b29:804e";
}
当前是否联网: 已联网
当前联网类型: wifi网络
本地网关: fe80:3::d9eb:1df9:25a6:1e59
本地DNS: 192.168.1.1, 172.16.0.69

网络分析的远端域名: www.baidu.com
DNS解析结果: 14.215.177.38 (81ms)


开始Telnet
dns time=0ms
connect to host 14.215.177.38 with port 80 ...
#1 channel is open, time=11ms


开始Ping
Ping www.baidu.com (14.215.177.38)
64 bytes from 14.215.177.38: icmp_seq=0 ttl=55 time=27ms
64 bytes from 14.215.177.38: icmp_seq=1 ttl=55 time=7ms
64 bytes from 14.215.177.38: icmp_seq=2 ttl=55 time=6ms
64 bytes from 14.215.177.38: icmp_seq=3 ttl=55 time=7ms
Ping is ending.
--- www.baidu.com Ping statistics ---
4 packets transmitted, 4 packets received, 0% packet loss


开始Mtr
1	**** (100%)loss ****	
2	**** (100%)loss ****	
3	192.168.1.1		3.72ms	6.31ms	3.22ms	 (0%)loss
4	**** (100%)loss ****	
5	**** (100%)loss ****	
6	**** (100%)loss ****	
7	58.63.32.237		60.23ms	16.35ms	8.51ms	 (0%)loss
8	113.96.5.102		11.98ms	8.94ms	17.53ms	 (0%)loss
9	219.135.96.94		36.15ms	10.84ms	 (33%)loss
10	14.29.121.186		32.00ms	12.11ms	11.02ms	 (0%)loss
11	**** (100%)loss ****	
12	**** (100%)loss ****	
13	**** (100%)loss ****	

Mtr: end


开始Dig
QUESTION SECTION:
www.baidu.com.		IN		A

ANSWER SECTION:
www.baidu.com.		49		IN		CNAME		www.a.shifen.com
www.a.shifen.com.		55		IN		A		14.215.177.38

QUERY TIME: 27ms
SERVER: 192.168.1.1, 172.16.0.69

Dig: end


开始Curl
http code=200; time=313ms; http result: <!DOCTYPE html>

<!--STATUS OK--><html> <head><meta http-equiv=content-type content=text/html;charset=utf-8><meta http-equiv=X-UA-Compatible content=IE=Edge><meta content=always name=referrer><link rel=stylesheet type=text/css href=https://ss1.bdstatic.com/5eN1bjq8AAUYm2zgoY3K/r/www/cache/bdorz/baidu.min.css><title>百度一下，你就知道</title></head> <body link=#0000cc> <div id=wrapper> <div id=head> <div class=head_wrapper> <div class=s_form> <div class=s_form_wrapper> <div id=lg> <img hidefocus=true src=//www.baidu.com/img/bd_logo1.png width=270 height=129> </div> <form id=form name=f action=//www.baidu.com/s class=fm> <input type=hidden name=bdorz_come value=1> <input type=hidden name=ie value=utf-8> <input type=hidden name=f value=8> <input type=hidden name=rsv_bp value=1> <input type=hidden name=rsv_idx value=1> <input type=hidden name=tn value=baidu><span class="bg s_ipt_wr"><input id=kw name=wd class=s_ipt value maxlength=255 autocomplete=off autofocus=autofocus></span><span class="bg s_btn_wr"><input type=submit id=su value=百度一下 class="bg s_btn" autofocus></span> </form> </div> </div> <div id=u1> <a href=http://news.baidu.com name=tj_trnews class=mnav>新闻</a> <a href=https://www.hao123.com name=tj_trhao123 class=mnav>hao123</a> <a href=http://map.baidu.com name=tj_trmap class=mnav>地图</a> <a href=http://v.baidu.com name=tj_trvideo class=mnav>视频</a> <a href=http://tieba.baidu.com name=tj_trtieba class=mnav>贴吧</a> <noscript> <a href=http://www.baidu.com/bdorz/login.gif?login&amp;tpl=mn&amp;u=http%3A%2F%2Fwww.baidu.com%2f%3fbdorz_come%3d1 name=tj_login class=lb>登录</a> </noscript> <script>document.write('<a href="http://www.baidu.com/bdorz/login.gif?login&tpl=mn&u='+ encodeURIComponent(window.location.href+ (window.location.search === "" ? "?" : "&")+ "bdorz_come=1")+ '" name="tj_login" class="lb">登录</a>');

                </script> <a href=//www.baidu.com/more/ name=tj_briicon class=bri style="display: block;">更多产品</a> </div> </div> </div> <div id=ftCon> <div id=ftConw> <p id=lh> <a href=http://home.baidu.com>关于百度</a> <a href=http://ir.baidu.com>About Baidu</a> </p> <p id=cp>&copy;2017&nbsp;Baidu&nbsp;<a href=http://www.baidu.com/duty/>使用百度前必读</a>&nbsp; <a href=http://jianyi.baidu.com/ class=cp-feedback>意见反馈</a>&nbsp;京ICP证030173号&nbsp; <img src=//www.baidu.com/img/gs.gif> </p> </div> </div> </div> </body> </html>



dns time=1ms

connect to host www.baidu.com with port 443 ...
#1 channel is open, time=36ms

total time=408ms

Curl: end
