#include <linux/kernel.h>
#include <linux/i2c.h>

#define I2C_BUS_NUM    //TO BE DECIDED LATER


static struct i2c_board_info LSM9DS0_i2c_board_info[] __initdata = {
        { 
			I2C_BOARD_INFO("LSM9DS0_i2c_client", 0x0X3C),
			//.irq = IRQ_GPIO(),   // TO DO LATER
		},

};

static void __init LSM9DS0_board_init(void)  // citation needed
{
        i2c_register_board_info(I2C_BUS_NUM, LSM9DS0_i2c_board_info, 
                        ARRAY_SIZE(LSM9DS0_i2c_board_info));

}