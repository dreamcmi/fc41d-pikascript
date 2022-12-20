#ifndef __QL_API_BLE_H__
#define __QL_API_BLE_H__

#include "app_ble.h"
#include "common_bt_defines.h"

#define QL_BT_ADV_INTERVAL_MIN 	32   //UNIT:0.625MS
#define QL_BT_ADV_INTERVAL_MAX 	0X4000  //UNIT:0.625MS

#define QL_BT_SCAN_INTERVAL_MIN 18   //UNIT:0.625MS
#define QL_BT_SCAN_INTERVAL_MAX 4096  //UNIT:0.625MS


#define QL_BT_SCAN_WINDOW_MIN 17   //UNIT:0.625MS
#define QL_BT_SCAN_WINDOW_MAX 4096  //UNIT:0.625MS

#define QL_BT_CONNECT_INTERVAL_MIN 6   //UNIT:1.25MS
#define QL_BT_CONNECT_INTERVAL_MAX 3200  //UNIT:1.25MS
#define QL_BT_CONNECT_LATENCY_MAX 499   
#define QL_BT_CONNECT_TIMEOUT_MIN 10   //UNIT:10MS
#define QL_BT_CONNECT_TIMEOUT_MAX 3200   //UNIT:10MS

typedef enum {
	QL_BT_SUCCESS = 0,
	QL_BT_ERR_PROFILE,
	QL_BT_ERR_CREATE_DB,
	QL_BT_ERR_CMD_NOT_SUPPORT,
	QL_BT_ERR_UNKNOW_IDX,
	QL_BT_ERR_BLE_STATUS,
	QL_BT_ERR_BLE_PARAM,
	QL_BT_ERR_ADV_DATA,
	QL_BT_ERR_CMD_RUN,
	QL_BT_ERR_NO_MEM,
	QL_BT_ERR_INIT_CREATE,
	QL_BT_ERR_INIT_STATE,

	QL_BT_ERR_ATTC_WRITE,
	QL_BT_ERR_ATTC_WRITE_UNREGISTER,
} ql_errcode_bt_e;


typedef struct
{
	/// 16 bits UUID LSB First
	uint8_t uuid[16];
	/// Attribute Permissions (@see enum attm_perm_mask)
	uint16_t perm;
	/// Attribute Extended Permissions (@see enum attm_value_perm_mask)
	uint16_t ext_perm;
	/// Attribute Max Size
	/// note: for characteristic declaration contains handle offset
	/// note: for included service, contains target service handle
	uint16_t max_size;
}ql_attm_desc_t;

struct ql_ble_db_cfg
{
	uint16_t prf_task_id;
	///Service uuid
	uint8_t uuid[16];
	///Number of db
	uint8_t att_db_nb;
	///Start handler, 0 means autoalloc
	uint16_t start_hdl;
	///Attribute database
	ql_attm_desc_t* att_db;
	///Service config
	uint8_t svc_perm;
};


#define QL_PERM_SET(access, right) \
    (((BK_PERM_RIGHT_ ## right) << (access ## _POS)) & (access ## _MASK))

#define QL_PERM_GET(perm, access)\
    (((perm) & (access ## _MASK)) >> (access ## _POS))



ql_errcode_bt_e ql_ble_set_notice_cb(ble_notice_cb_t func);
ql_errcode_bt_e ql_ble_init(void);
ql_errcode_bt_e ql_ble_create_db (struct ql_ble_db_cfg* ble_db_cfg);
uint8_t ql_ble_get_idle_actv_idx_handle(void);
actv_state_t ql_ble_actv_state_get(uint8_t actv_idx);
ql_errcode_bt_e ql_ble_create_advertising(uint8_t actv_idx,unsigned char chnl_map,uint32_t intv_min,uint32_t intv_max,ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_set_adv_data(uint8_t actv_idx, unsigned char* adv_buff, unsigned char adv_len, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_set_scan_rsp_data(uint8_t actv_idx, unsigned char* scan_buff, unsigned char scan_len, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_start_advertising(uint8_t actv_idx, uint16 duration, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_stop_advertising(uint8_t actv_idx, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_adv_start(uint8_t actv_idx, struct adv_param *adv, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_delete_advertising(uint8_t actv_idx, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_create_scaning(uint8_t actv_idx, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_start_scaning(uint8_t actv_idx, uint16_t scan_intv, uint16_t scan_wd, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_scan_start(uint8_t actv_idx, struct scan_param *scan, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_stop_scaning(uint8_t actv_idx, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_delete_scaning(uint8_t actv_idx, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_update_param(uint8_t conn_idx, uint16_t intv_min, uint16_t intv_max,uint16_t latency, uint16_t sup_to, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_gatts_disconnect(uint8_t conn_idx, ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_gatt_mtu_changes(uint8_t conn_idx,uint16_t mtu_size,ble_cmd_cb_t callback);
uint16_t ql_ble_gatt_mtu_get(uint8_t conn_idx);
ql_errcode_bt_e ql_ble_create_conn(uint8_t actv_idx,unsigned short con_interval,unsigned short con_latency,unsigned short sup_to,ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_set_connect_dev_addr(unsigned char actv_idx,struct bd_addr *bdaddr,unsigned char addr_type);
ql_errcode_bt_e ql_ble_gattc_register_discovery_callback(app_sdp_callback cb);
ql_errcode_bt_e ql_ble_gattc_register_event_recv_callback(app_sdp_charac_callback cb);
ql_errcode_bt_e ql_ble_start_conn(uint8_t actv_idx,ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_stop_conn(uint8_t actv_idx,ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_gattc_disconnect(uint8_t conn_idx , uint8_t reason);
#if (BLE_APP_PRESENT && (BLE_CENTRAL) && (BLE_SDP_CLIENT))
ql_errcode_bt_e ql_ble_gattc_read_service_data_by_handle_req(uint8_t conidx,uint16_t handle,ble_cmd_cb_t callback);
ql_errcode_bt_e ql_ble_gattc_write_service_data_req(uint8_t conidx,uint16_t handle,uint16_t data_len,uint8_t *data,ble_cmd_cb_t callback);
#endif
ql_errcode_bt_e ql_ble_gatts_send_ntf_value(uint32_t len, uint8_t *buf, uint16_t att_idx);
ql_errcode_bt_e ql_ble_gatts_send_ind_value(uint32_t len, uint8_t *buf, uint16_t att_idx);


void ql_ble_demo_central_thread_creat(void);
void ql_ble_demo_periphera_thread_creat(void);
#endif
