#include "ql_include.h"



#define WLAN_DEFAULT_IP         "192.168.19.1"
#define WLAN_DEFAULT_GW         "192.168.19.1"
#define WLAN_DEFAULT_MASK       "255.255.255.0"

/*回调函数，用于scan结束后解析scan结果*/
static void scan_cb(void *ctxt, uint8_t param)
{
	
/* CFG_WPA_CTRL_IFACE */
	static const char *crypto_str[] = {
		"None",
		"WEP",
		"WPA_TKIP",
		"WPA_AES",
		"WPA2_TKIP",
		"WPA2_AES",
		"WPA2_MIXED",		////QL_SECURITY_TYPE_WPA3_SAE
		"WPA3_SAE",	  		/**< WPA3 SAE */
		"WPA3_WPA2_MIXED",	/** WPA3 SAE or WPA2 AES */
		"AUTO",
	};

	ScanResult_adv apList;
	if (wlan_sta_scan_result(&apList) == 0) {
		int ap_num = apList.ApNum;
		int i;

		ql_wlan_log("Got ap count: %d\r\n", apList.ApNum);
		for (i = 0; i < ap_num; i++)
			ql_wlan_log("    \"%s\", " MACSTR "\b, %d, %s, %d\n",
					apList.ApList[i].ssid, MAC2STR(apList.ApList[i].bssid),
					apList.ApList[i].ApPower, crypto_str[apList.ApList[i].security],
					apList.ApList[i].channel);
		os_free(apList.ApList);
	}

}


void ql_demo_scan_app_init(void)
{
	/*注册scan回调函数*/
	mhdr_scanu_reg_cb(scan_cb, 0);
	/*开始scan*/
	ql_wlan_start_scan();
}

void ql_demo_scan_adv_app_init(uint8_t *oob_ssid)
{
    uint8_t **ssid_array;

    ssid_array = &oob_ssid;
	/*注册扫描应答函数*/
	mhdr_scanu_reg_cb(scan_cb, 0);

	ql_wlan_log("scan for ssid:%s\r\n", oob_ssid);
	ql_wlan_start_assign_scan(ssid_array, 1);
}

void ql_demo_softap_app_init(char *ap_ssid, char *ap_key)
{
	/*定义一个结构体，用于传入参数*/
    ql_network_InitTypeDef_s wNetConfig;
    int len;

	/*置空结构体*/
    os_memset(&wNetConfig, 0x0, sizeof(ql_network_InitTypeDef_s));

    len = os_strlen(ap_ssid);
    if(SSID_MAX_LEN < len)
    {
        ql_wlan_log("ssid name more than 32 Bytes\r\n");
        return;
    }

    len = os_strlen(ap_key);
    if(63 < len)
    {
        bk_printf("key  more than 63 Bytes\r\n");
        return;
    }

	/*传入要连接的ap ssid 和 ap key*/
    os_strcpy((char *)wNetConfig.wifi_ssid, ap_ssid);
    os_strcpy((char *)wNetConfig.wifi_key, ap_key);

	/*当前为ap模式*/
    wNetConfig.wifi_mode = QL_SOFT_AP;
	/*采用DHCP SERVER模式，需要将静态地址分配为本地地址*/
    wNetConfig.dhcp_mode = DHCP_SERVER;
    wNetConfig.wifi_retry_interval = 100;
    os_strcpy((char *)wNetConfig.local_ip_addr, WLAN_DEFAULT_IP);
    os_strcpy((char *)wNetConfig.net_mask, WLAN_DEFAULT_MASK);
    os_strcpy((char *)wNetConfig.gateway_ip_addr, WLAN_DEFAULT_GW);
    os_strcpy((char *)wNetConfig.dns_server_ip_addr, WLAN_DEFAULT_GW);

    ql_wlan_log("ssid:%s  key:%s\r\n", wNetConfig.wifi_ssid, wNetConfig.wifi_key);
	/*启动ap*/
	ql_wlan_start(&wNetConfig);
}

void ql_demo_sta_app_init(char *oob_ssid,char *connect_key)
{
	/*定义一个结构体，用于传入参数*/
	ql_network_InitTypeDef_s wNetConfig;
    int len;

	/*置空结构体*/
	os_memset(&wNetConfig, 0x0, sizeof(network_InitTypeDef_st));

	/*检查SSID的长度，不能超过32字节*/
    len = os_strlen(oob_ssid);
    if(SSID_MAX_LEN < len)
    {
        ql_wlan_log("ssid name more than 32 Bytes\r\n");
        return;
    }

	/*将SSID跟密码传入结构体*/
	os_strcpy((char *)wNetConfig.wifi_ssid, oob_ssid);
	os_strcpy((char *)wNetConfig.wifi_key, connect_key);

	/*当前为客户端模式*/
	wNetConfig.wifi_mode = QL_STATION;
	/*采用DHCP CLIENT的方式获得，从路由器动态获取IP地址*/
	wNetConfig.dhcp_mode = DHCP_CLIENT;
	wNetConfig.wifi_retry_interval = 100;

	ql_wlan_log("ssid:%s key:%s\r\n", wNetConfig.wifi_ssid, wNetConfig.wifi_key);
	/*启动WiFi连接*/
	ql_wlan_start(&wNetConfig);
}

void ql_demo_sta_adv_app_init(char *oob_ssid,char *connect_key)
{
	/*定义一个结构体，用于传入参数*/
	ql_network_InitTypeDef_adv_s	wNetConfigAdv;

	/*置空结构体*/
	os_memset( &wNetConfigAdv, 0x0, sizeof(network_InitTypeDef_adv_st) );

	/*传入要连接的SSID*/
	os_strcpy((char*)wNetConfigAdv.ap_info.ssid, oob_ssid);
	/*传入要连接的网络的bssid，下面这个bssid仅供参考*/
	hwaddr_aton("48:ee:0c:48:93:12", (u8 *)(wNetConfigAdv.ap_info.bssid));
	/*要连接网络的加密方式。具体参数参考该结构体说明。*/
	wNetConfigAdv.ap_info.security = QL_SECURITY_TYPE_WPA2_MIXED;
	/*要连接的网络的信道*/
	wNetConfigAdv.ap_info.channel = 11;

	/*要连接的网络密码以及密码长度*/
	os_strcpy((char*)wNetConfigAdv.key, connect_key);
	wNetConfigAdv.key_len = os_strlen(connect_key);
	/*通过DHCP的方式获取IP地址等网络信息*/
	wNetConfigAdv.dhcp_mode = DHCP_CLIENT;
	wNetConfigAdv.wifi_retry_interval = 100;

	 /*启动快速连接*/
	ql_wlan_start_sta_adv(&wNetConfigAdv);
}

void ql_demo_wlan_app_init(VIF_ADDCFG_PTR cfg)
{
    ql_network_InitTypeDef_s network_cfg;
	ql_network_InitTypeDef_adv_s	networkadv_cfg;

    if(cfg->wlan_role == QL_STATION) {
        if(cfg->adv == 1) {
        	os_memset( &networkadv_cfg, 0x0, sizeof(network_InitTypeDef_adv_st) );

        	os_strcpy((char*)networkadv_cfg.ap_info.ssid, cfg->ssid);
        	hwaddr_aton("48:ee:0c:48:93:12", (u8 *)(networkadv_cfg.ap_info.bssid));
        	networkadv_cfg.ap_info.security = QL_SECURITY_TYPE_WPA2_MIXED;
        	networkadv_cfg.ap_info.channel = 11;

        	os_strcpy((char*)networkadv_cfg.key, cfg->key);
        	networkadv_cfg.key_len = os_strlen(cfg->key);
        	networkadv_cfg.dhcp_mode = DHCP_CLIENT;
        	networkadv_cfg.wifi_retry_interval = 100;

        	ql_wlan_start_sta_adv(&networkadv_cfg);
            return;
        } else {
        	os_memset(&network_cfg, 0x0, sizeof(network_InitTypeDef_st));

        	os_strcpy((char *)network_cfg.wifi_ssid, cfg->ssid);
        	os_strcpy((char *)network_cfg.wifi_key, cfg->key);

        	network_cfg.wifi_mode = QL_STATION;
        	network_cfg.dhcp_mode = DHCP_CLIENT;
        	network_cfg.wifi_retry_interval = 100;

        	ql_wlan_log("ssid:%s key:%s\r\n", network_cfg.wifi_ssid, network_cfg.wifi_key);
        }
    } else if(cfg->wlan_role == QL_SOFT_AP) {
        os_memset(&network_cfg, 0x0, sizeof(network_InitTypeDef_st));
        os_strcpy((char *)network_cfg.wifi_ssid, cfg->ssid);
        os_strcpy((char *)network_cfg.wifi_key, cfg->key);

        network_cfg.wifi_mode = QL_SOFT_AP;
        network_cfg.dhcp_mode = DHCP_SERVER;
        network_cfg.wifi_retry_interval = 100;
        os_strcpy((char *)network_cfg.local_ip_addr, WLAN_DEFAULT_IP);
        os_strcpy((char *)network_cfg.net_mask, WLAN_DEFAULT_MASK);
        os_strcpy((char *)network_cfg.gateway_ip_addr, WLAN_DEFAULT_GW);
        os_strcpy((char *)network_cfg.dns_server_ip_addr, WLAN_DEFAULT_GW);

        ql_wlan_log("ssid:%s  key:%s\r\n", network_cfg.wifi_ssid, network_cfg.wifi_key);
    }

    ql_wlan_start(&network_cfg);

}

void ql_demo_state_app_init(void)
{
	/*定义结构体用于保存连接状态*/
	ql_LinkStatusTypeDef_s linkStatus;
	ql_network_InitTypeDef_ap_s ap_info;
	char ssid[33] = {0};

	ql_wlan_log("sta: %d, softap: %d, b/g/n\r\n", sta_ip_is_start(), uap_ip_is_start());

	/*STATION模式下的连接状态*/
	if (sta_ip_is_start()) {
		/*将用于保存状态的结构体置空*/
		os_memset(&linkStatus, 0x0, sizeof(LinkStatusTypeDef));
		/*获取连接状态*/
		ql_wlan_get_link_status(&linkStatus);
		os_memcpy(ssid, linkStatus.ssid, 32);
		/*打印连接状态*/
		ql_wlan_log("sta:rssi=%d,ssid=%s,bssid=" MACSTR ",channel=%d,cipher_type:",
				  linkStatus.wifi_strength, ssid, MAC2STR(linkStatus.bssid), linkStatus.channel);
		switch (ql_sta_chiper_type()) {
		case QL_SECURITY_TYPE_NONE:
			ql_wlan_log("OPEN\r\n");
			break;
		case QL_SECURITY_TYPE_WEP :
			ql_wlan_log("WEP\r\n");
			break;
		case QL_SECURITY_TYPE_WPA_TKIP:
			ql_wlan_log("TKIP\r\n");
			break;
		case QL_SECURITY_TYPE_WPA_AES:
			ql_wlan_log("WPA_AES\r\n");
			break;
		case QL_SECURITY_TYPE_WPA2_AES:
			ql_wlan_log("CCMP\r\n");
			break;
		case QL_SECURITY_TYPE_WPA2_TKIP:
			ql_wlan_log("WPA2_TKIP\r\n");
			break;
		case QL_SECURITY_TYPE_WPA2_MIXED:
			ql_wlan_log("WPA/WPA2 MIXED\r\n");
			break;
		case QL_SECURITY_TYPE_AUTO:
			ql_wlan_log("AUTO\r\n");
			break;
		case QL_SECURITY_TYPE_WPA3_SAE:
			ql_wlan_log("WPA3\n");
			break;
		case QL_SECURITY_TYPE_WPA3_WPA2_MIXED:
			ql_wlan_log("WPA2/WPA3 MIXED\n");
			break;
		default:
			ql_wlan_log("Error\r\n");
			break;
		}
	}

	/*AP模式下的连接状态*/
	if (uap_ip_is_start()) {
		/*将用于保存连接状态的结构体置空*/
		os_memset(&ap_info, 0x0, sizeof(network_InitTypeDef_ap_st));
		/*获取连接状态*/
		ql_wlan_ap_para_info_get(&ap_info);
		os_memcpy(ssid, ap_info.wifi_ssid, 32);
		/*打印出获取的连接状态值*/
		ql_wlan_log("softap:ssid=%s,channel=%d,dhcp=%d,cipher_type:\r\n",
				  ssid, ap_info.channel, ap_info.dhcp_mode);
		
		switch (ap_info.security) {
		case QL_SECURITY_TYPE_NONE:
			ql_wlan_log("OPEN\r\n");
			break;
		case QL_SECURITY_TYPE_WEP :
			ql_wlan_log("WEP\r\n");
			break;
		case QL_SECURITY_TYPE_WPA_TKIP:
			ql_wlan_log("TKIP\r\n");
			break;
		case QL_SECURITY_TYPE_WPA2_AES:
			ql_wlan_log("CCMP\r\n");
			break;
		case QL_SECURITY_TYPE_WPA2_MIXED:
			ql_wlan_log("WPA/WPA2 MIXED\r\n");
			break;
		case QL_SECURITY_TYPE_AUTO:
			ql_wlan_log("AUTO\r\n");
			break;
		case QL_SECURITY_TYPE_WPA3_SAE:
			ql_wlan_log("WPA3\n");
			break;
		case QL_SECURITY_TYPE_WPA3_WPA2_MIXED:
			ql_wlan_log("WPA2/WPA3 MIXED\n");
			break;
		default:
			ql_wlan_log("Error\r\n");
			break;
		}
		ql_wlan_log("ip=%s,gate=%s,mask=%s,dns=%s\r\n",
				  ap_info.local_ip_addr, ap_info.gateway_ip_addr, ap_info.net_mask, ap_info.dns_server_ip_addr);
	}
}

void ql_demo_ip_app_init(void)
{
	/*定义一个用于保存网络状态的结构体*/
    ql_IPStatusTypedef_s ipStatus;

	/*将该结构体置空*/
	os_memset(&ipStatus, 0x0, sizeof(IPStatusTypedef));
	/*获取网络状态，并保存在该结构体中*/
	ql_wlan_get_ip_status(&ipStatus, QL_STATION);

	/*打印获取的网络状态*/
	ql_wlan_log("dhcp=%d ip=%s gate=%s mask=%s mac=" MACSTR "\r\n",
				ipStatus.dhcp, ipStatus.ip, ipStatus.gate,
				ipStatus.mask, MAC2STR((unsigned char*)ipStatus.mac));
}

/* monitor 回调函数*/
void ql_demo_monitor_cb(uint8_t *data, int len, wifi_link_info_t *info)
{
	ql_wlan_log("len:%d\r\n", len);
		
	//Only for reference
	/*
	User can get ssid and key by prase monitor data,
	refer to the following code, which is the way airkiss
	use monitor get wifi info from data
	*/

}

