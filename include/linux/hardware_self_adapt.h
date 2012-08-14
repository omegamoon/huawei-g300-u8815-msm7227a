#ifndef HARDWARE_SELF_ADAPT_H
#define HARDWARE_SELF_ADAPT_H

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                    GPIO/BIO   S E R V I C E S

GENERAL DESCRIPTION

REFERENCES

EXTERNALIZED FUNCTIONS
  None.

INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright (c) 2009 by HUAWEI, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

 This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


when       who      what, where, why
-------------------------------------------------------------------------------
20091123    hqt      creat
=========================================================================== */
#define IC_PM_ON   1
#define IC_PM_OFF  0
/* updated for regulator interface */
#define IC_PM_VDD 2700000   /*set gp4 voltage as 2700mV for all*/

#define MMI_KEY_UP   	false
#define MMI_KEY_DOWN 	true
/*  for the 7x27a and  8x55  use the same code*/
#ifdef CONFIG_ARCH_MSM7X27A
#define BATTERY_GET_CHARGE_STAET_PROC       121
#define BATTERY_SET_BATT_DELTA_PROC 	    120 
#define BATTERY_LEVEL_PROC                  119
/* for 7x27a  current_consuem rpc  id  */
#define PM_CURRENT_CONSUME_NOTIFY_PROC      100
#else
#define BATTERY_GET_CHARGE_STAET_PROC       121
#define BATTERY_SET_BATT_DELTA_PROC 	    17  
#define BATTERY_LEVEL_PROC                  19   
/* for 8x55  current_consuem rpc  id  */
#define PM_CURRENT_CONSUME_NOTIFY_PROC      200
#endif
typedef enum
{
   LCD_IS_MIPI_CMD = 0, 
   LCD_IS_MIPI_VIDEO,
   LCD_IS_MDDI_TYPE1,
   LCD_IS_MDDI_TYPE2,
   LCD_IS_RGB, 
   LCD_IS_UNKNOW = 0xF,
}hw_lcd_interface_type;

typedef enum
{
	LCD_HW_ID0 = 0,    
	LCD_HW_ID1,
	LCD_HW_ID2,
	LCD_HW_ID3, 
	LCD_HW_ID_MAX = 0xFF,
} hw_lcd_id_index;
typedef enum
{
   LCD_PANEL_ALIGN_LSB,
   LCD_PANEL_ALIGN_MSB,
   LCD_PANEL_ALIGN_INVALID = 0xFF
}lcd_align_type;

typedef enum
{
	LCD_S6D74A0_SAMSUNG_HVGA,
	LCD_ILI9325_INNOLUX_QVGA,
	LCD_ILI9325_BYD_QVGA,
	LCD_ILI9325_WINTEK_QVGA,
	LCD_SPFD5408B_KGM_QVGA,
	LCD_HX8357A_BYD_QVGA,
	LCD_HX8368A_SEIKO_QVGA,
	LCD_ILI9325C_WINTEK_QVGA,
	LCD_HX8368A_TRULY_QVGA,
	LCD_NT35582_TRULY_WVGA,
	LCD_NT35582_BYD_WVGA,
	LCD_NT35510_ALPHA_SI_WVGA,
	LCD_NT35560_TOSHIBA_FWVGA,
	LCD_NT35510_ALPHA_SI_WVGA_TYPE2,
	MDDI_RSP61408_CHIMEI_WVGA,
	MDDI_RSP61408_BYD_WVGA,
	MDDI_HX8369A_TIANMA_WVGA,
	LCD_HX8357B_TIANMA_HVGA,
	LCD_ILI9481D_INNOLUX_HVGA,
	LCD_ILI9481DS_TIANMA_HVGA,
	LCD_R61529_TRULY_HVGA,
	LCD_NT35410_CHIMEI_HVGA,
	LCD_HX8347D_TRULY_QVGA,
	LCD_HX8347D_CHIMEI_QVGA,
	LCD_HX8347G_TIANMA_QVGA,
	LCD_HX8357C_TIANMA_HVGA,
	MIPI_NT35560_TOSHIBA_FWVGA,
	MIPI_RSP61408_CHIMEI_WVGA,
	MIPI_RSP61408_BYD_WVGA,
	MIPI_HX8357C_CHIMEI_HVGA,
	MIPI_HX8357C_TIANMA_HVGA,
	MIPI_HX8369A_TIANMA_WVGA,
	MIPI_HX8357C_CHIMEI_IPS_HVGA,
	MDDI_HX8357C_TIANMA_HVGA,
	MDDI_HX8357C_CHIMEI_HVGA,
	MDDI_HX8357C_CHIMEI_IPS_HVGA,
	MIPI_HX8357C_TIANMA_IPS_HVGA,
	MIPI_RSP61408_TRULY_WVGA, 

	LCD_MAX_NUM,
	LCD_NONE =0xFF
}lcd_panel_type;

/********************************************
 *CTRL_BL_BY_LCD : control LCD backlight by lcd
 *CTRL_BL_BY_MSM : control LCD backlight by msm
 ********************************************/
typedef enum
{
	CTRL_BL_BY_LCD = 0,
	CTRL_BL_BY_MSM ,
	CTRL_BL_BY_UNKNOW = 0xF,
}hw_lcd_ctrl_bl_type;

typedef enum
{
	LCD_IS_QVGA     = 320,
	LCD_IS_HVGA     = 480,
	LCD_IS_WVGA     = 800,
	LCD_IS_FWVGA     = 854,
	LCD_IS_DEFAULT     = LCD_IS_HVGA,
}lcd_type;

typedef enum
{
    HW_VER_SUB_VA            = 0x0,
    HW_VER_SUB_VB            = 0x1,
    HW_VER_SUB_VC            = 0x2,
    HW_VER_SUB_VD            = 0x3,
    HW_VER_SUB_VE            = 0x4,
    HW_VER_SUB_VF            = 0x5,
    HW_VER_SUB_VG            = 0x6,
    HW_VER_SUB_SURF          = 0xF,
    HW_VER_SUB_MAX           = 0xF
}hw_ver_sub_type;

/*add new g-sensor*/
typedef enum
{
	GS_ADIX345 	= 0x01,
	GS_ST35DE	= 0x02,
	GS_ST303DLH = 0X03,
	GS_MMA8452  = 0x04,
	GS_BMA250   = 0x05,
	GS_STLIS3XH	= 0x06,
	GS_ADI346   = 0x07,
	GS_KXTIK1004= 0x08,
}hw_gs_type;
typedef enum
{
	COMPASS_TOP_GS_TOP 			=0,
	COMPASS_TOP_GS_BOTTOM 		=1,
	COMPASS_BOTTOM_GS_TOP 		=2,
	COMPASS_BOTTOM_GS_BOTTOM	=3,
	COMPASS_NONE_GS_BOTTOM		=4,
	COMPASS_NONE_GS_TOP			=5,
}compass_gs_position_type;
typedef enum
{
	NONE_SENSOR	= 0,
	G_SENSOR 	= 0x01,
	L_SENSOR	= 0x02,
	P_SENSOR 	= 0X04,
	M_SENSOR	= 0x08,
	GY_SENSOR   = 0x10,
}sensors_list_type;

typedef enum
{
   WIFI_BROADCOM = 0,
   WIFI_QUALCOMM,
   WIFI_NONE = 0xF,	
}hw_wifi_device_type;
hw_wifi_device_type get_hw_wifi_device_type(void);
typedef enum
{
   WIFI_BROADCOM_4329,
   WIFI_BROADCOM_4330,
   WIFI_QUALCOMM_6005,
   WIFI_UNKNOW = 0xFF,	
}hw_wifi_device_model;
hw_wifi_device_model get_hw_wifi_device_model(void);
typedef enum
{
   HW_NODS = 0,    /* single sim card type */
   HW_DS,          /* double sim card type */
   HW_NONES = 0xF,	
}hw_ds_type;
hw_ds_type get_hw_ds_type(void);

typedef enum
{
   RAISE_TRIGGER = 0, 
   FALL_TRIGGER,
   DOUBLE_EDGE_TRIGGER = 0xF,	
}hw_sd_trigger_type;
hw_sd_trigger_type get_hw_sd_trigger_type(void);

typedef enum
{
    HW_BT_WAKEUP_GPIO_IS_27 = 27,
    HW_BT_WAKEUP_GPIO_IS_83 = 83,
    HW_BT_WAKEUP_GPIO_IS_NONES = 0xFF,
}hw_bt_wakeup_gpio_type;
hw_bt_wakeup_gpio_type get_hw_bt_wakeup_gpio_type(void);

#ifdef CONFIG_ARCH_MSM7X27A
#define GPIO_COMPASS_INT  18
#else
#define GPIO_COMPASS_INT  132
#endif

typedef enum
{
    AUDIO_PROPERTY_INVALID = 0x0,
    SINGLE_MIC = 0x1,
    DUAL_MIC = 0x2,
    MIC_NONE = 0xf,
    FIR_ENABLE = 0x10,
    FIR_DISABLE = 0xf0,
    FM_BROADCOM = 0x100,
    FM_QUALCOMM = 0x200,

    AUDIO_TYPE_MAX = 0xffff
}audio_property_type;

audio_property_type get_audio_fm_type(void);
audio_property_type get_audio_fir_enabled(void);
audio_property_type get_audio_mic_type(void);
void get_audio_property(char *audio_property);


/*add compass platform data and the func of power_switch*/
struct gs_platform_data {
	int (*adapt_fn)(void);	/* fucntion is suported in some product */
	int slave_addr;     /*I2C slave address*/
	int dev_id;         /*who am I*/
	int *init_flag;     /*Init*/
	compass_gs_position_type (*get_compass_gs_position)(void);
	int (*gs_power)(int on);
};

struct compass_platform_data {
	int (*compass_power)(int on);
};

struct gyro_platform_data {
	u8 fs_range;
	u8 axis_map_x;     /*x map read data[axis_map_x] from i2c*/
	u8 axis_map_y;
	u8 axis_map_z;
	
	u8 negate_x;       /*negative x,y or z*/
	u8 negate_y;
	u8 negate_z;
	int dev_id;        /*who am I*/
	int slave_addr;
	int (*gyro_power)(int on);
};
compass_gs_position_type  get_compass_gs_position(void);

#define HW_VER_MAIN_MASK (0xFFF0)
#define HW_VER_SUB_MASK  (0x000F)

bool st303_gs_is_supported(void);
void set_st303_gs_support(bool status);

/*
 *  return: 0 ----not support RGB LED driver
 *          1 ----support RGB LED driver
 */
bool rgb_led_is_supported(void);
bool camera_is_supported(void);
void set_camera_support(bool status);
bool board_support_flash(void);

/*
 *  return: 0 ----not support bcm wifi
 *          1 ----support bcm wifi
 *          *p_gpio  return MSM WAKEUP WIFI gpio value
 */
unsigned int board_support_bcm_wifi(unsigned *p_gpio);

lcd_panel_type get_lcd_panel_type(void);
int board_use_tssc_touch(bool * use_touch_key);
int board_support_ofn(bool * ofn_support);

char *get_compass_gs_position_name(void);
char *get_sensors_list_name(void);
char *get_wifi_device_name(void);
lcd_panel_type get_lcd_panel_type(void);
hw_lcd_ctrl_bl_type get_hw_lcd_ctrl_bl_type(void);
lcd_type get_hw_lcd_resolution_type(void);
lcd_align_type get_lcd_align_type(void);
char *get_lcd_panel_name(void);
int board_surport_fingers(bool * is_surport_fingers);

hw_lcd_interface_type get_hw_lcd_interface_type(void); 
hw_ver_sub_type get_hw_sub_board_id(void);
#ifdef CONFIG_HUAWEI_POWER_DOWN_CHARGE
unsigned int get_charge_flag(void);
#endif
lcd_type atag_get_lcd_y_res(void);

#ifdef CONFIG_FRAMEBUF_SELF_ADAPT
void get_frame_buffer_mem_region(__u32 *start_addr, __u32 *size);
#endif

void get_cust_buffer_mem_region(__u32 * start_addr, __u32 * size);

bool qwerty_is_supported(void);

#ifdef CONFIG_HUAWEI_FEATURE_PROXIMITY_EVERLIGHT_APS_9900
#define MSM_7X27A_APS9900_INT 17
#define MSM_7X30_APS9900_INT 89
struct aps9900_hw_platform_data {
    int (*aps9900_power)(int on);
    int (*aps9900_gpio_config_interrupt)(void);
};
#endif
typedef enum
{
   HW_MIRROR_AND_FLIP = 0,    /* mirror and flip */
   HW_NOT_MIRROR_OR_FLIP,          /* not mirror or fliP */
   HW_CAMERA_NONES = 0xF,	
}hw_camera_type;
hw_camera_type get_hw_camera_mirror_type(void);
#endif

