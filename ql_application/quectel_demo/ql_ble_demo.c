#include "ql_include.h"


/***************ble test******************/
#if CFG_ENABLE_QUECTEL_BLE_PERIPHERA

static ql_task_t ble_periphera_hdl = NULL;
int ble_periphera_state = 0;
uint8_t adv_actv_idx = -1;
char ble_name[32] = {0};
struct adv_param g_adv_info = {0};


#define QL_DEMO_ATT_DECL_PRIMARY_SERVICE_128     {0x00,0x28,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define QL_DEMO_ATT_DECL_CHARACTERISTIC_128      {0x03,0x28,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define QL_DEMO_ATT_DESC_CLIENT_CHAR_CFG_128     {0x02,0x29,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define NOTIFY_CHARACTERISTIC_128           {0x15,0xFF,0,0,0x34,0x56,0,0,0,0,0x28,0x37,0,0,0,0}
static const uint8_t ql_demo_svc_uuid[16] = {0x36,0xF5,0,0,0x34,0x56,0,0,0,0,0x28,0x37,0,0,0,0};
enum
{
	QL_DEMO_IDX_SVC,
	QL_DEMO_IDX_FF03_VAL_CHAR,
	QL_DEMO_IDX_FF03_VAL_VALUE,
	QL_DEMO_IDX_FF03_VAL_NTF_CFG,
	QL_DEMO_IDX_NB,
};
ql_attm_desc_t ql_demo_att_db[QL_DEMO_IDX_NB] =
{
	//  Service Declaration
	[QL_DEMO_IDX_SVC]              = {QL_DEMO_ATT_DECL_PRIMARY_SERVICE_128, QL_PERM_SET(RD, ENABLE), 0, 0},

    [QL_DEMO_IDX_FF03_VAL_CHAR]    = {QL_DEMO_ATT_DECL_CHARACTERISTIC_128,  QL_PERM_SET(RD, ENABLE), 0, 0},
	//  Level Characteristic Value
	[QL_DEMO_IDX_FF03_VAL_VALUE]   = {NOTIFY_CHARACTERISTIC_128,   QL_PERM_SET(WRITE_REQ, ENABLE) |    QL_PERM_SET(NTF, ENABLE), QL_PERM_SET(RI, ENABLE)|QL_PERM_SET(UUID_LEN, UUID_16), 512},

	//  Level Characteristic - Client Characteristic Configuration Descriptor

	 [QL_DEMO_IDX_FF03_VAL_NTF_CFG] = {QL_DEMO_ATT_DESC_CLIENT_CHAR_CFG_128, QL_PERM_SET(RD, ENABLE)|QL_PERM_SET(WRITE_REQ, ENABLE), 0, 0},
};


static void ql_demo_periphera_notice_cb(ble_notice_t notice, void *param)
{
    switch (notice)
    {
    case BLE_5_STACK_OK:
        os_printf("ble stack ok");
        break;
    case BLE_5_WRITE_EVENT:
    {
        write_req_t *w_req = (write_req_t *)param;
        os_printf("write_cb:conn_idx:%d, prf_id:%d, add_id:%d, len:%d, data[0]:%02x\r\n",
                  w_req->conn_idx, w_req->prf_id, w_req->att_idx, w_req->len, w_req->value[0]);
#if 1
        // 回传测试
        ql_ble_gatts_send_ntf_value(w_req->len , w_req->value , QL_DEMO_IDX_FF03_VAL_VALUE);
#endif

        break;
    }
    case BLE_5_READ_EVENT:
    {
        read_req_t *r_req = (read_req_t *)param;
        os_printf("read_cb:conn_idx:%d, prf_id:%d, add_id:%d\r\n",
                  r_req->conn_idx, r_req->prf_id, r_req->att_idx);
        r_req->value[0] = 0x12;
        r_req->value[1] = 0x34;
        r_req->length = 2;
        break;
    }
    case BLE_5_REPORT_ADV:
    {
        recv_adv_t *r_ind = (recv_adv_t *)param;
        os_printf("r_ind:actv_idx:%d, adv_addr:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                  r_ind->actv_idx, r_ind->adv_addr[0], r_ind->adv_addr[1], r_ind->adv_addr[2],
                  r_ind->adv_addr[3], r_ind->adv_addr[4], r_ind->adv_addr[5]);
        break;
    }
    case BLE_5_MTU_CHANGE:
    {

        mtu_change_t *m_ind = (mtu_change_t *)param;
        os_printf("m_ind:conn_idx:%d, mtu_size:%d\r\n", m_ind->conn_idx, m_ind->mtu_size);
        break;
    }
    case BLE_5_CONNECT_EVENT:
    {
        conn_ind_t *c_ind = (conn_ind_t *)param;
        os_printf("c_ind:conn_idx:%d, addr_type:%d, peer_addr:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                  c_ind->conn_idx, c_ind->peer_addr_type, c_ind->peer_addr[0], c_ind->peer_addr[1],
                  c_ind->peer_addr[2], c_ind->peer_addr[3], c_ind->peer_addr[4], c_ind->peer_addr[5]);

        break;
    }
    case BLE_5_DISCONNECT_EVENT:
    {
        discon_ind_t *d_ind = (discon_ind_t *)param;
        os_printf("d_ind:conn_idx:%d,reason:%d\r\n", d_ind->conn_idx,d_ind->reason);
        break;
    }
    case BLE_5_ATT_INFO_REQ:
    {
        att_info_req_t *a_ind = (att_info_req_t *)param;
        os_printf("a_ind:conn_idx:%d\r\n", a_ind->conn_idx);
        a_ind->length = 128;
        a_ind->status = ERR_SUCCESS;
        break;
    }
    case BLE_5_CREATE_DB:
    {
        create_db_t *cd_ind = (create_db_t *)param;
        os_printf("cd_ind:prf_id:%d, status:%d\r\n", cd_ind->prf_id, cd_ind->status);
        break;
    }
    case BLE_5_INIT_CONNECT_EVENT:
    {
        conn_ind_t *c_ind = (conn_ind_t *)param;
        os_printf("BLE_5_INIT_CONNECT_EVENT:conn_idx:%d, addr_type:%d, peer_addr:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                  c_ind->conn_idx, c_ind->peer_addr_type, c_ind->peer_addr[0], c_ind->peer_addr[1],
                  c_ind->peer_addr[2], c_ind->peer_addr[3], c_ind->peer_addr[4], c_ind->peer_addr[5]);
        break;
    }
    case BLE_5_INIT_DISCONNECT_EVENT:
    {
        discon_ind_t *d_ind = (discon_ind_t *)param;
        os_printf("BLE_5_INIT_DISCONNECT_EVENT:conn_idx:%d,reason:%d\r\n", d_ind->conn_idx,d_ind->reason);
        break;
    }
    case BLE_5_SDP_REGISTER_FAILED:
        os_printf("BLE_5_SDP_REGISTER_FAILED\r\n");
        break;
    default:
        break;
    }
}

static void ble_periphera_cmd_cb(ble_cmd_t cmd, ble_cmd_param_t *param)
{
    os_printf("cmd:%d idx:%d status:%d\r\n", cmd, param->cmd_idx, param->status);
}

static void ql_ble_demo_get_mac_address(char *ble_mac)
{
    char tmp_mac[6] = {0};
    if(ble_mac == NULL)
    {
        return;
    }
    wifi_get_mac_address((char *)&tmp_mac[0], 2);
    tmp_mac[0] += 1; // add 1, diff from wifi's mac
    memcpy(ble_mac, tmp_mac, 6);
}


static void ql_ble_periphera_demo_entry(void *arg)
{
    unsigned char ble_mac[6] = {0};
    struct adv_param *adv_info = &g_adv_info;
    int ret = 0;
    
    while (1)
    {
        /* 等待协议栈初始化完成 */
        while (kernel_state_get(TASK_BLE_APP) != APPM_READY)
        {
            ql_rtos_task_sleep_ms(200);
        }

        if(ble_periphera_state == 0)
        {
            /* 设置ble事件callback */
            ql_ble_set_notice_cb(ql_demo_periphera_notice_cb);

            /* 添加蓝牙服务 */
            struct ql_ble_db_cfg ble_db_cfg;
            ble_db_cfg.att_db = ql_demo_att_db;
            ble_db_cfg.att_db_nb = QL_DEMO_IDX_NB;
            ble_db_cfg.prf_task_id = 0;
            ble_db_cfg.start_hdl = 0;
            ble_db_cfg.svc_perm = QL_PERM_SET(SVC_UUID_LEN, UUID_16);
            memcpy(&(ble_db_cfg.uuid[0]), &ql_demo_svc_uuid[0], 16);
            ql_ble_create_db(&ble_db_cfg);

            /* 设置广播参数 */
            adv_info->interval_min = 160;
            adv_info->interval_max = 160;
            adv_info->channel_map = 7;
            adv_info->duration = 0;

            /* 设置蓝牙广播数据  */
            ql_ble_demo_get_mac_address((char *)ble_mac);
            memset(ble_name, 0, sizeof(ble_name));
            ret = snprintf(ble_name, sizeof(ble_name) - 1,
                        "FC41D_%02x:%02x:%02x:%02x:%02x:%02x",
                        ble_mac[0], ble_mac[1], ble_mac[2], ble_mac[3], ble_mac[4], ble_mac[5]);
            adv_info->advData[0] = 0x02;
            adv_info->advData[1] = 0x01;
            adv_info->advData[2] = 0x06;
            adv_info->advData[3] = ret + 1;
            adv_info->advData[4] = 0x09;
            memcpy(&adv_info->advData[5], ble_name, ret);
            adv_info->advDataLen = 5 + ret;

            /* 获取空闲的actv_idx */
            adv_actv_idx = ql_ble_get_idle_actv_idx_handle();
            if (adv_actv_idx >= BLE_ACTIVITY_MAX)
            {
                return ;
            }
            /* 该actv_idx空闲时 */
            if (app_ble_actv_state_get(adv_actv_idx) == ACTV_IDLE)
            {
                ql_ble_adv_start(adv_actv_idx, adv_info, ble_periphera_cmd_cb);
            }
            else /*如果该actv_idx已经被创建，则直接开始广播*/
            {
                ql_ble_start_advertising(adv_actv_idx, 0, ble_periphera_cmd_cb);
            }

            ble_periphera_state = 1;
        }
        ql_rtos_task_sleep_ms(20);
    }

    ql_rtos_task_delete(NULL);
}

void ql_ble_demo_periphera_thread_creat(void)
{
    OSStatus err = kNoErr;
    // todo  create new thread;
    err = ql_rtos_task_create(&ble_periphera_hdl,
                                8*1024,
                                THD_EXTENDED_APP_PRIORITY,
                                "ble_demo",
                                ql_ble_periphera_demo_entry,
                                0);

    if (err != kNoErr)
    {
        return ;
    }

    return;
}

#endif

#if CFG_ENABLE_QUECTEL_BLE_CENTRAL
int ble_central_state = 0;
static ql_task_t ble_central_hdl = NULL;
uint8_t scan_actv_idx = -1;
uint8_t conn_actv_idx = -1;

struct scan_param g_scan_info = {0};

uint8_t conn_addr[6] = {0};
uint8_t adv_addr_type = 0; //0:public ,1:random
uint8_t scan_success_flag = 0;
uint8_t data_handle = 0;


static void ble_central_cmd_cb(ble_cmd_t cmd, ble_cmd_param_t *param);

/*! Definition of an AD Structure as contained in Advertising and Scan Response packets. An Advertising or Scan Response packet contains several AD Structures. */
typedef struct gapAdStructure_tag
{
    uint8_t         length;     /*!< Total length of the [adType + aData] fields. Equal to 1 + lengthOf(aData). */
    uint8_t      adType;     /*!< AD Type of this AD Structure. */
    uint8_t*        aData;      /*!< Data contained in this AD Structure; length of this array is equal to (gapAdStructure_t.length - 1). */
} gapAdStructure_t;


void app_demo_ble_adv_report_deal(const recv_adv_t * p_adv_report)
{
    uint8_t index = 0;
    uint8_t loop_cnt = 0;
  
    while(index < p_adv_report->data_len)
    {
        gapAdStructure_t adElement;
       
        adElement.length = p_adv_report->data[index];
        adElement.adType = p_adv_report->data[index + 1];
        adElement.aData = (uint8_t *)&p_adv_report->data[index + 2];
    
        if(!memcmp(adElement.aData , "phone_server" , strlen("phone_server")))  //check adv name
        {
            int8_t adv_rssi = p_adv_report->rssi;
            os_printf("Found Device NAME:\"%s\", RSSI:%ddBm, mac:", "test"  , adv_rssi);
            for(uint8_t i = 0; i < 6; i++)
            {
                os_printf("%02X ", p_adv_report->adv_addr[i]);
            }
            os_printf("\r\n");

            memcpy(conn_addr , p_adv_report->adv_addr , 6);
            adv_addr_type = p_adv_report->adv_addr_type;
            scan_success_flag = 1;
            //停止扫描
            ql_ble_stop_scaning(scan_actv_idx , ble_central_cmd_cb);

            return;
        }
        
        /* Move on to the next AD elemnt type */
        index += adElement.length + sizeof(uint8_t);
  
        loop_cnt++;
        if(loop_cnt >= 250)
        break;
    }  
}


static void ql_demo_central_notice_cb(ble_notice_t notice, void *param)
{
    switch (notice)
    {
    case BLE_5_STACK_OK:
        os_printf("ble stack ok");
        break;
    case BLE_5_WRITE_EVENT:
    {
        write_req_t *w_req = (write_req_t *)param;
        os_printf("write_cb:conn_idx:%d, prf_id:%d, add_id:%d, len:%d, data[0]:%02x\r\n",
                  w_req->conn_idx, w_req->prf_id, w_req->att_idx, w_req->len, w_req->value[0]);

        break;
    }
    case BLE_5_READ_EVENT:
    {
        read_req_t *r_req = (read_req_t *)param;
        os_printf("read_cb:conn_idx:%d, prf_id:%d, add_id:%d\r\n",
                  r_req->conn_idx, r_req->prf_id, r_req->att_idx);
        r_req->value[0] = 0x12;
        r_req->value[1] = 0x34;
        r_req->length = 2;
        break;
    }
    case BLE_5_REPORT_ADV:
    {
        recv_adv_t *r_ind = (recv_adv_t *)param;
        os_printf("r_ind:actv_idx:%d, adv_addr:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                  r_ind->actv_idx, r_ind->adv_addr[0], r_ind->adv_addr[1], r_ind->adv_addr[2],
                  r_ind->adv_addr[3], r_ind->adv_addr[4], r_ind->adv_addr[5]);

        app_demo_ble_adv_report_deal(r_ind);
                  
        break;
    }
    case BLE_5_MTU_CHANGE:
    {
        mtu_change_t *m_ind = (mtu_change_t *)param;
        os_printf("m_ind:conn_idx:%d, mtu_size:%d\r\n", m_ind->conn_idx, m_ind->mtu_size);
        break;
    }
    case BLE_5_CONNECT_EVENT:
    {
        conn_ind_t *c_ind = (conn_ind_t *)param;
        os_printf("c_ind:conn_idx:%d, addr_type:%d, peer_addr:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                  c_ind->conn_idx, c_ind->peer_addr_type, c_ind->peer_addr[0], c_ind->peer_addr[1],
                  c_ind->peer_addr[2], c_ind->peer_addr[3], c_ind->peer_addr[4], c_ind->peer_addr[5]);

        break;
    }
    case BLE_5_DISCONNECT_EVENT:
    {
        discon_ind_t *d_ind = (discon_ind_t *)param;
        os_printf("d_ind:conn_idx:%d,reason:%d\r\n", d_ind->conn_idx,d_ind->reason);
        break;
    }
    case BLE_5_ATT_INFO_REQ:
    {
        att_info_req_t *a_ind = (att_info_req_t *)param;
        os_printf("a_ind:conn_idx:%d\r\n", a_ind->conn_idx);
        a_ind->length = 128;
        a_ind->status = ERR_SUCCESS;
        break;
    }
    case BLE_5_CREATE_DB:
    {
        create_db_t *cd_ind = (create_db_t *)param;
        os_printf("cd_ind:prf_id:%d, status:%d\r\n", cd_ind->prf_id, cd_ind->status);
        break;
    }
    case BLE_5_INIT_CONNECT_EVENT:
    {
        conn_ind_t *c_ind = (conn_ind_t *)param;
        os_printf("BLE_5_INIT_CONNECT_EVENT:conn_idx:%d, addr_type:%d, peer_addr:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                  c_ind->conn_idx, c_ind->peer_addr_type, c_ind->peer_addr[0], c_ind->peer_addr[1],
                  c_ind->peer_addr[2], c_ind->peer_addr[3], c_ind->peer_addr[4], c_ind->peer_addr[5]);
        break;
    }
    case BLE_5_INIT_DISCONNECT_EVENT:
    {
        discon_ind_t *d_ind = (discon_ind_t *)param;
        os_printf("BLE_5_INIT_DISCONNECT_EVENT:conn_idx:%d,reason:%d\r\n", d_ind->conn_idx,d_ind->reason);
        break;
    }
    case BLE_5_SDP_REGISTER_FAILED:
        os_printf("BLE_5_SDP_REGISTER_FAILED\r\n");
        break;
    default:
        break;
    }
}

static void ble_central_cmd_cb(ble_cmd_t cmd, ble_cmd_param_t *param)
{
    os_printf("cmd:%d idx:%d status:%d\r\n", cmd, param->cmd_idx, param->status);
}


static void quec_ble_app_sdp_characteristic_cb(unsigned char conidx,uint16_t chars_val_hdl,unsigned char uuid_len,unsigned char *uuid)
{
    os_printf("[APP]characteristic conidx:%d,handle:0x%02x(%d),UUID:0x",conidx,chars_val_hdl,chars_val_hdl);
    for(int i = 0; i< uuid_len; i++)
    {
        os_printf("%02x ",uuid[i]);
    }
    os_printf("\r\n");

    data_handle = chars_val_hdl;
}

//receive slave data
void quec_app_sdp_charac_cb(CHAR_TYPE type,uint8 conidx,uint16_t hdl,uint16_t len,uint8 *data)
{
    os_printf("[APP]type:%x conidx:%d,handle:0x%02x(%d),len:%d,0x",type,conidx,hdl,hdl,len);
    for(int i = 0; i< len; i++)
    {
        os_printf("%02x ",data[i]);
    }
   
    os_printf("\r\n");

#if 1
        //数据回传测试
        ql_ble_gattc_write_service_data_req(conidx , hdl , len , data , ble_central_cmd_cb);
#endif
}


#include "app_sdp.h"
static const app_sdp_service_uuid service_tab[] ={
	{
		.uuid_len = 0x02,
		.uuid[0] = 0x00,
		.uuid[1] = 0x18,
	},
	{
		.uuid_len = 0x02,
		.uuid[0] = 0x01,
		.uuid[1] = 0x18,
	},
};
   


static void ql_ble_central_demo_entry(void *arg)
{
    struct scan_param *scan_info = &g_scan_info;
    
    while (1)
    {
        /* 等待协议栈初始化完成 */
        while (kernel_state_get(TASK_BLE_APP) != APPM_READY)
        {
            ql_rtos_task_sleep_ms(200);
        }

        if(ble_central_state == 0)
        {
            /* 设置ble事件callback */
            ql_ble_set_notice_cb(ql_demo_central_notice_cb);

            /* ble初始化 */
            ql_ble_init();

            /* 设置扫描参数 */
            scan_info->channel_map = 0x07;
            scan_info->interval = 0x50;
            scan_info->window = 0x20;

            /* 获取空闲的actv_idx */
            scan_actv_idx = ql_ble_get_idle_actv_idx_handle();
            if (scan_actv_idx >= BLE_ACTIVITY_MAX)
            {
                return ;
            }
            /* 该actv_idx空闲时 */
            if (app_ble_actv_state_get(scan_actv_idx) == ACTV_IDLE)
            {
                ql_ble_scan_start(scan_actv_idx , scan_info , ble_central_cmd_cb);
            }
            else /*如果该actv_idx已经被创建，则直接开始广播*/
            {
                ql_ble_start_scaning(scan_actv_idx , scan_info->interval , scan_info->window , ble_central_cmd_cb);
            }

            ble_central_state = 1;
        }


        if(1 == ble_central_state)
        {
            if(1 == scan_success_flag)
            {
                /*等待扫描停止*/
                ql_rtos_task_sleep_ms(2000);

                /*获取当前空闲的actv_idx*/
                conn_actv_idx = ql_ble_get_idle_actv_idx_handle();
                os_printf("conn_actv_idx = %d\r\n" , conn_actv_idx);
                if (conn_actv_idx >= BLE_ACTIVITY_MAX)
                {
                    return ;
                }
           
                /*设置discovery回调函数*/
                // register_app_sdp_service_tab(sizeof(service_tab)/sizeof(app_sdp_service_uuid),service_tab);
                // app_sdp_service_filtration(1);

                ql_ble_gattc_register_discovery_callback(quec_ble_app_sdp_characteristic_cb);
                ql_ble_gattc_register_event_recv_callback(quec_app_sdp_charac_cb);

                /*创建连接actv*/
                ql_ble_create_conn(conn_actv_idx, 0X30, 0,500,ble_central_cmd_cb);
                os_printf("set connect address\r\n");
                ql_rtos_task_sleep_ms(1000);
                ql_ble_set_connect_dev_addr(conn_actv_idx,(struct bd_addr *)conn_addr,adv_addr_type);
                os_printf("start connect ....\r\n");
                ql_ble_start_conn(conn_actv_idx , ble_central_cmd_cb);

                scan_success_flag = 0;
            }
        }
        ql_rtos_task_sleep_ms(20);
    }

    ql_rtos_task_delete(NULL);
}

void ql_ble_demo_central_thread_creat(void)
{
    OSStatus err = kNoErr;
    // todo  create new thread;
    err = ql_rtos_task_create(&ble_central_hdl,
                                8*1024,
                                THD_EXTENDED_APP_PRIORITY,
                                "ble_central_demo",
                                ql_ble_central_demo_entry,
                                0);

    if (err != kNoErr)
    {
        return ;
    }

    return;
}

#endif
