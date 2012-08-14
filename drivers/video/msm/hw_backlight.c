/* drivers\video\msm\hw_backlight.c
 * backlight driver for 7x30 platform
 *
 * Copyright (C) 2010 HUAWEI Technology Co., ltd.
 * 
 * Date: 2010/12/07
 * 
 */

#include "msm_fb.h"
#include <linux/mfd/pmic8058.h>
#include <mach/gpio.h>
#include <mach/vreg.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/pwm.h>
#include <mach/pmic.h>
#include <linux/earlysuspend.h>
#include <linux/spinlock.h>
#include <linux/semaphore.h>
#include <linux/hardware_self_adapt.h>
#include "hw_lcd_common.h"
#include <mach/rpc_pmapp.h>

/*CABC CTL MACRO , RANGE 0 to 255*/
#define PWM_PERIOD ( NSEC_PER_SEC / ( 22 * 1000 ) )	/* ns, period of 22Khz */
#define PWM_LEVEL 255
#define PWM_DUTY_LEVEL (PWM_PERIOD / PWM_LEVEL)
#define PM_GPIO25_PWM_ID  1
#define PM_GPIO26_PWM_ID  2
#define ADD_VALUE			4
#define PWM_LEVEL_ADJUST	226
#define BL_MIN_LEVEL 	    30

/*LPG CTL MACRO  range 0 to 100*/
#define PWM_LEVEL_ADJUST_LPG	90
#define BL_MIN_LEVEL_LPG 	    10
static struct pwm_device *bl_pwm;
/* move semaphore to msm_fb.c */
static struct msm_fb_data_type *mfd_local;
static boolean backlight_set = FALSE;
static atomic_t suspend_flag = ATOMIC_INIT(0);

int backlight_pwm_gpio_config(void)
{
    int rc;
	struct pm_gpio backlight_drv = 
	{
		.direction      = PM_GPIO_DIR_OUT,
		.output_buffer  = PM_GPIO_OUT_BUF_CMOS,
		.output_value   = 0,
		.pull           = PM_GPIO_PULL_NO,
		.vin_sel        = 0,
		.out_strength   = PM_GPIO_STRENGTH_HIGH,
		.function       = PM_GPIO_FUNC_2,
		.inv_int_pol 	= 1,
	};
	/* U8800 use PM_GPIO25 as backlight's PWM,but U8820 use PM_GPIO26 */
    if(machine_is_msm7x30_u8800() 
		|| machine_is_msm7x30_u8800_51() 
		|| machine_is_msm8255_u8800_pro() 
		|| machine_is_msm8255_u8860() 
		|| machine_is_msm8255_c8860() 
		|| machine_is_msm8255_u8860lp()
        || machine_is_msm8255_u8860_r()
		|| machine_is_msm8255_u8860_92()
		|| machine_is_msm8255_u8680()
		|| machine_is_msm8255_u8667()
		|| machine_is_msm8255_u8860_51()
		|| machine_is_msm8255_u8730())
	{
        rc = pm8xxx_gpio_config( 24, &backlight_drv);
    }
    else if(machine_is_msm7x30_u8820()) 
    {
    	rc = pm8xxx_gpio_config( 25, &backlight_drv);
    }
	else
	{
    	rc = -1;
	}
	
    if (rc) 
	{
		pr_err("%s LCD backlight GPIO config failed\n", __func__);
		return rc;
	}
    return 0;
}
/* use the mmp pin like three-leds */
void msm_backlight_set(int level)
{
    static uint8 last_level = 0;
	static boolean first_set_bl = TRUE;
	/* keep duty 10% < level < 90% */
#ifdef CONFIG_ARCH_MSM7X27A
	if(level)
	{
		level = ((level * PWM_LEVEL_ADJUST_LPG) / PWM_LEVEL ); 
		if (level < BL_MIN_LEVEL_LPG)        
		{    
			level = BL_MIN_LEVEL_LPG;      
		}
	}
    if (last_level == level)
    {
        return ;
    }
    last_level = level;
	pmapp_disp_backlight_set_brightness(last_level);
#endif

#ifdef CONFIG_ARCH_MSM7X30
	if(TRUE == first_set_bl)
	{
		backlight_pwm_gpio_config();
		/* U8800 use PM_GPIO25 as backlight's PWM,but U8820 use PM_GPIO26 */
		if(machine_is_msm7x30_u8800() 
			|| machine_is_msm7x30_u8800_51() 
			|| machine_is_msm8255_u8800_pro()
			|| machine_is_msm8255_u8860() 
			|| machine_is_msm8255_c8860()
			|| machine_is_msm8255_u8860lp()
            || machine_is_msm8255_u8860_r()
			|| machine_is_msm8255_u8860_92()
			|| machine_is_msm8255_u8680()
			|| machine_is_msm8255_u8667()
			|| machine_is_msm8255_u8860_51()
			|| machine_is_msm8255_u8730())

		{
			bl_pwm = pwm_request(PM_GPIO25_PWM_ID, "backlight");
		}
		else if(machine_is_msm7x30_u8820())
		{
			bl_pwm = pwm_request(PM_GPIO26_PWM_ID, "backlight");
		}
		else
		{
			bl_pwm = NULL;
		}

		if (NULL == bl_pwm || IS_ERR(bl_pwm)) 
		{
			pr_err("%s: pwm_request() failed\n", __func__);
			bl_pwm = NULL;
		}
		first_set_bl = FALSE;
	}
	if (bl_pwm)
	{
		if(level)
		{
			level = ((level * PWM_LEVEL_ADJUST) / PWM_LEVEL + ADD_VALUE); 
			if (level < BL_MIN_LEVEL)
			{
				level = BL_MIN_LEVEL;
			}
		}	
	    if (last_level == level)
	    {
	        return ;
	    }
	    last_level = level;
		pwm_config(bl_pwm, PWM_DUTY_LEVEL*level/NSEC_PER_USEC, PWM_PERIOD/NSEC_PER_USEC);
		pwm_enable(bl_pwm);
	}
#endif
}

void cabc_backlight_set(struct msm_fb_data_type * mfd)
{	     
	struct msm_fb_panel_data *pdata = NULL;   
	uint32 bl_level = mfd->bl_level;
	/* keep duty 10% < level < 90% */
	if (bl_level)    
   	{   
		bl_level = ((bl_level * PWM_LEVEL_ADJUST) / PWM_LEVEL + ADD_VALUE); 
		if (bl_level < BL_MIN_LEVEL)        
		{    
			bl_level = BL_MIN_LEVEL;      
		}  
	}
	/* backlight ctrl by LCD-self, like as CABC */  
	pdata = (struct msm_fb_panel_data *)mfd->pdev->dev.platform_data;  
	if ((pdata) && (pdata->set_cabc_brightness))   
   	{       
		pdata->set_cabc_brightness(mfd,bl_level);
	}

}

void pwm_set_backlight(struct msm_fb_data_type *mfd)
{
	lcd_panel_type lcd_panel_wvga = LCD_NONE;
	/*When all the device are resume that can turn the light*/
	if(atomic_read(&suspend_flag)) 
	{
		mfd_local = mfd;
		backlight_set = TRUE;
		return;
	}
#ifdef CONFIG_ARCH_MSM7X27A
	
	
	lcd_panel_wvga = get_lcd_panel_type();
	if ((MIPI_RSP61408_CHIMEI_WVGA == lcd_panel_wvga ) 
		|| (MIPI_RSP61408_BYD_WVGA == lcd_panel_wvga )
		|| (MIPI_RSP61408_TRULY_WVGA == lcd_panel_wvga )
		|| (MIPI_HX8369A_TIANMA_WVGA == lcd_panel_wvga ))
	{
		/* keep duty is 75% of the quondam duty */
		mfd->bl_level = mfd->bl_level * 75 / 100;
	}
#endif
	if (get_hw_lcd_ctrl_bl_type() == CTRL_BL_BY_MSM)
	{
		msm_backlight_set(mfd->bl_level);
 	}   
	else    
 	{
		cabc_backlight_set(mfd);  
 	}
	return;
}
#ifdef CONFIG_HAS_EARLYSUSPEND
static void pwm_backlight_suspend( struct early_suspend *h)
{
	atomic_set(&suspend_flag,1);
}

static void pwm_backlight_resume( struct early_suspend *h)
{
	atomic_set(&suspend_flag,0);
	
	if (backlight_set == TRUE)
	{
		if (get_hw_lcd_ctrl_bl_type() == CTRL_BL_BY_LCD)
		{
			/* MIPI use two semaphores */
			if(get_hw_lcd_interface_type() == LCD_IS_MIPI_CMD)
			{
				down(&mfd_local->dma->mutex);
				down(&mfd_local->sem);
				pwm_set_backlight(mfd_local);
				up(&mfd_local->sem);
				up(&mfd_local->dma->mutex);
			}
			/* MDDI don't use semaphore */
			else if((get_hw_lcd_interface_type() == LCD_IS_MDDI_TYPE1)
				||(get_hw_lcd_interface_type() == LCD_IS_MDDI_TYPE2))
			{
				pwm_set_backlight(mfd_local);
			}
			else
			{
				down(&mfd_local->sem);
				pwm_set_backlight(mfd_local);
				up(&mfd_local->sem);
			}
		}
		else
		{
			down(&mfd_local->sem);
			pwm_set_backlight(mfd_local);
			up(&mfd_local->sem);
		}
	}
}
/*add early suspend*/
static struct early_suspend pwm_backlight_early_suspend = {
	.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN - 1,
	.suspend = pwm_backlight_suspend,
	.resume = pwm_backlight_resume,
};
#endif


static int __init pwm_backlight_init(void)
{
	
#ifdef CONFIG_HAS_EARLYSUSPEND
	register_early_suspend(&pwm_backlight_early_suspend);
#endif

	return 0;
}
module_init(pwm_backlight_init);
