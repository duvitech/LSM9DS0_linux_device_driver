

/*
 *
 *
 *
 *
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */



#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>

#include "lsm9ds0.h


struct LSM9DS0_device {
        struct i2c_client *client;
        
        struct mutex lock;
        /* TODO */
};


static int __devinit LSM9DS0_i2c_probe(struct i2c_client *client,
                const struct i2c_device_id *id)
{
        struct LSM9DS0_device *lsm9dso_dev;
        struct device *dev = &client->dev;   // to use for device reports
        int ret;

#if defined SMBUS_COMPATIBLE
        if (!i2c_check_functionality(client->adapter,
                I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
                I2C_FUNC_SMBUS_I2C_BLOCK)) {
                //printk(KERN_ERR "%s: CLIENT NOT SMB-I2C CAPABLE\n", __func__);
                dev_err(dev, "CLIENT NOT SMB-I2C CAPABLE\n");
                return -ENODEV;
        }
#endif

#if defined I2C_COMPATIBLE

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(dev, "client not i2c capable\n");
		return -ENODEV;
	}
	
#endif
        
        
        
        lsm9dso_devlsm9dso_dev = kzalloc(sizeof(struct LSM9DS0_device), GFP_KERNEL);
        if (lsm9dso_dev == NULL) {
                //printk(KERN_ERR "%s: no memory\n", __func__);
                dev_err(dev, "Failed to create, no memory\n");
                return -ENOMEM;
        }


	mutex_init(&lsm9dso_dev->lock);
	mutex_lock(&lsm9dso_dev->lock);
	
	

        lsm9dso_dev->client = client;
        i2c_set_clientdata(client, lsm9dso_dev);
        
        // use defaults to initialize the sensor, not using platform data */
        
        // enable all axes //
        // do initial state, further can be set up by the user depending upon his requirement//
        
        
        
        /* TODO: do something */



	mutex_unlock(&lsm9dso_dev->lock);
	dev_info(dev, "LSM9DS0 client probing completed\n");
	
	
        return 0;
}

static int __devexit LSM9DS0_i2c_remove(struct i2c_client *client)
{
        struct LSM9DS0_device *lsm9ds0_dev = i2c_get_clientdata(client);

        /* TODO: do something */

        kfree(lsm9ds0_dev);
        return 0;
}

static int LSM9DS0_i2c_suspend(struct i2c_client *client, pm_messaget_t msg)
{
        struct LSM9DS0_device *lsm9ds0_dev = i2c_get_clientdata(client);
        
        /* TO DO */
        return 0;
}

static int LSM9DS0_i2c_resume(struct i2c_client *client)
{
        struct LSM9DS0_device *lsm9sd0_dev = i2c_get_clientdata(client);

	/* TO DO */
        return 0;
}



static const struct i2c_device_id LSM9DS0_i2c_id_table[] = {
        { "LSM9DS0_i2c_client", 0 },
        { },
};

MODULE_DEVICE_TABLE(i2c, LSM9DS0_i2c_id_table);

static struct i2c_driver LSM9DS0_i2c_driver = {
        .probe    = LSM9DS0_i2c_probe,
        .remove   = __devexit_p(LSM9DS0_i2c_remove),
        .id_table = LSM9DS0_i2c_id_table,
        .suspend  = LSM9DS0_i2c_suspend,
        .resume   = LSM9DS0_i2c_resume,
        .driver   = {
        	.owner = THIS_MODULE,
                .name = "LSM9DS0_i2c_client",
        },
};

static int __init LSM9DS0_init(void)
{
        return i2c_add_driver(&LSM9DS0_i2c_driver);
}

static void __exit LSM9DS0_exit(void)
{
        i2c_del_driver(&LSM9DS0_i2c_driver);
}


module_init(LSM9DS0_init);
module_exit(LSM9DS0_exit);

MODULE_DESCRIPTION("LSM9DS0 I2C client driver");
MODULE_LICENSE("GPL");
