// SPDX-License-Identifier: GPL-2.0+
/*
 * DRM driver for Sitronix ST7796S panels
 *
 * Orange Pi Zero 3W (Allwinner A733) — LCDWiki 4.0" SPI Module
 * (MSP4020/MSP4021), 480x320, 4-wire SPI + DC, XPT2046 touch,
 * PWM backlight. Direct 8-bit SPI (SPI MODE0, MSBFIRST) — this is
 * NOT a 16-bit waveshare-bridge panel, so the standard mipi_dbi
 * Type-C3 command path is used (do NOT install a 16-bit command hook).
 *
 * Init sequence and MADCTL rotation values taken verbatim from the
 * vendor demo library (LCDWiki 4.0inch_SPI_Module_ST7796S demo,
 * LCDWIKI_SPI.cpp ST7796S_regValues[] + Set_Rotation() generic branch,
 * which is what ST7796S resolves to):
 *   rotation 0: 0x28 = MV|BGR        (landscape 480x320, normal)
 *   rotation 1: 0x48 = MX|BGR        (portrait 320x480)
 *   rotation 2: 0xF8 = MX|MY|ML|MV|BGR
 *   rotation 3: 0x98 = MY|ML|BGR
 * DRM rotation property 0 (default) => landscape 480x320 = MV|BGR.
 *
 * Panel: QD-40037C1-00 3.95" TFT (sold as 4.0"), 320(RGB)x480 portrait
 * glass mounted landscape on the module PCB.
 */

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/property.h>
#include <linux/spi/spi.h>

#include <video/mipi_display.h>

#include <drm/clients/drm_client_setup.h>
#include <drm/drm_atomic_helper.h>
#include <drm/drm_drv.h>
#include <drm/drm_fbdev_dma.h>
#include <drm/drm_gem_atomic_helper.h>
#include <drm/drm_gem_dma_helper.h>
#include <drm/drm_managed.h>
#include <drm/drm_mipi_dbi.h>
#include <drm/drm_modeset_helper.h>

#define ST7796S_MADCTL_MY	BIT(7)
#define ST7796S_MADCTL_MX	BIT(6)
#define ST7796S_MADCTL_MV	BIT(5)
#define ST7796S_MADCTL_ML	BIT(4)
#define ST7796S_MADCTL_BGR	BIT(3)

static void st7796s_enable(struct drm_simple_display_pipe *pipe,
			   struct drm_crtc_state *crtc_state,
			   struct drm_plane_state *plane_state)
{
	struct mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	struct mipi_dbi *dbi = &dbidev->dbi;
	u8 addr_mode;
	int ret, idx;

	if (!drm_dev_enter(pipe->crtc.dev, &idx))
		return;

	DRM_DEBUG_KMS("\n");

	ret = mipi_dbi_poweron_conditional_reset(dbidev);
	if (ret < 0)
		goto out_exit;
	if (ret == 1)
		goto out_enable;

	/* Unlock manufacturer command access */
	mipi_dbi_command(dbi, 0xF0, 0xC3);
	mipi_dbi_command(dbi, 0xF0, 0x96);

	/* Interface pixel format: 16bpp RGB565 */
	mipi_dbi_command(dbi, 0x3A, 0x05);

	/* Display function control / porch etc from vendor demo */
	mipi_dbi_command(dbi, 0xB0, 0x80);
	mipi_dbi_command(dbi, 0xB6, 0x00, 0x02);
	mipi_dbi_command(dbi, 0xB5, 0x02, 0x03, 0x00, 0x04);
	mipi_dbi_command(dbi, 0xB1, 0x80, 0x10);
	mipi_dbi_command(dbi, 0xB4, 0x00);
	mipi_dbi_command(dbi, 0xB7, 0xC6);
	mipi_dbi_command(dbi, 0xC5, 0x24);
	mipi_dbi_command(dbi, 0xE4, 0x31);
	mipi_dbi_command(dbi, 0xE8, 0x40, 0x8A, 0x00, 0x00,
			 0x29, 0x19, 0xA5, 0x33);
	mipi_dbi_command(dbi, 0xC2);
	mipi_dbi_command(dbi, 0xA7);

	/* Gamma */
	mipi_dbi_command(dbi, 0xE0,
			 0xF0, 0x09, 0x13, 0x12, 0x12, 0x2B, 0x3C, 0x44,
			 0x4B, 0x1B, 0x18, 0x17, 0x1D, 0x21);
	mipi_dbi_command(dbi, 0xE1,
			 0xF0, 0x09, 0x13, 0x0C, 0x0D, 0x27, 0x3B, 0x44,
			 0x4D, 0x0B, 0x17, 0x17, 0x1D, 0x21);

	/* Lock manufacturer access */
	mipi_dbi_command(dbi, 0xF0, 0xC3);
	mipi_dbi_command(dbi, 0xF0, 0x69);

	/* Normal display mode on, then exit sleep (vendor order) */
	mipi_dbi_command(dbi, 0x13);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(120);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_ON);
	msleep(50);

out_enable:
	/*
	 * Vendor Set_Rotation() mapping for ST7796S (LCDWiki generic
	 * branch). DRM rotation 0 = landscape 480x320 = MV|BGR.
	 */
	switch (dbidev->rotation) {
	case 90:
		addr_mode = ST7796S_MADCTL_MX | ST7796S_MADCTL_BGR;
		break;
	case 180:
		addr_mode = ST7796S_MADCTL_MX | ST7796S_MADCTL_MY |
			    ST7796S_MADCTL_ML | ST7796S_MADCTL_MV |
			    ST7796S_MADCTL_BGR;
		break;
	case 270:
		addr_mode = ST7796S_MADCTL_MY | ST7796S_MADCTL_ML |
			    ST7796S_MADCTL_BGR;
		break;
	default:
		addr_mode = ST7796S_MADCTL_MV | ST7796S_MADCTL_BGR;
		break;
	}
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);
	mipi_dbi_enable_flush(dbidev, crtc_state, plane_state);
out_exit:
	drm_dev_exit(idx);
}

static const struct drm_simple_display_pipe_funcs st7796s_pipe_funcs = {
	DRM_MIPI_DBI_SIMPLE_DISPLAY_PIPE_FUNCS(st7796s_enable),
};

/* 4.0" 480x320 (3:2), physical ~85 x 56 mm */
static const struct drm_display_mode st7796s_mode = {
	DRM_SIMPLE_MODE(480, 320, 85, 56),
};

DEFINE_DRM_GEM_DMA_FOPS(st7796s_fops);

static const struct drm_driver st7796s_driver = {
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &st7796s_fops,
	DRM_GEM_DMA_DRIVER_OPS_VMAP,
	DRM_FBDEV_DMA_DRIVER_OPS,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "st7796s",
	.desc			= "Sitronix ST7796S",
	.major			= 1,
	.minor			= 0,
};

static const struct of_device_id st7796s_of_match[] = {
	{ .compatible = "sitronix,st7796s" },
	{ .compatible = "lcdwiki,4inch-st7796s" },
	{},
};
MODULE_DEVICE_TABLE(of, st7796s_of_match);

static const struct spi_device_id st7796s_id[] = {
	{ "st7796s", 0 },
	{ "4inch-st7796s", 0 },
	{ }
};
MODULE_DEVICE_TABLE(spi, st7796s_id);

static int st7796s_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct mipi_dbi_dev *dbidev;
	struct drm_device *drm;
	struct mipi_dbi *dbi;
	struct gpio_desc *dc;
	u32 rotation = 0;
	int ret;

	dbidev = devm_drm_dev_alloc(dev, &st7796s_driver,
				    struct mipi_dbi_dev, drm);
	if (IS_ERR(dbidev))
		return PTR_ERR(dbidev);

	dbi = &dbidev->dbi;
	drm = &dbidev->drm;

	dbi->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(dbi->reset))
		return dev_err_probe(dev, PTR_ERR(dbi->reset),
				     "Failed to get GPIO 'reset'\n");

	dc = devm_gpiod_get(dev, "dc", GPIOD_OUT_LOW);
	if (IS_ERR(dc))
		return dev_err_probe(dev, PTR_ERR(dc),
				     "Failed to get GPIO 'dc'\n");

	dbidev->backlight = devm_of_find_backlight(dev);
	if (IS_ERR(dbidev->backlight))
		return PTR_ERR(dbidev->backlight);

	device_property_read_u32(dev, "rotation", &rotation);

	ret = mipi_dbi_spi_init(spi, dbi, dc);
	if (ret)
		return ret;

	/*
	 * Direct 8-bit SPI panel: keep the standard Type-C3 command path
	 * installed by mipi_dbi_spi_init(). Do NOT override dbi->command
	 * with a 16-bit bridge handler (that is only for waveshare-style
	 * SPI-to-parallel converter HATs).
	 *
	 * MISO/SDO is OPTIONAL on this module (wiring skips pin 9), so
	 * panel-ID reads would float. Disable read commands like ili9486
	 * does — unconditional init on every enable.
	 */
	dbi->read_commands = NULL;

	ret = mipi_dbi_dev_init(dbidev, &st7796s_pipe_funcs,
				&st7796s_mode, rotation);
	if (ret)
		return ret;

	drm_mode_config_reset(drm);

	ret = drm_dev_register(drm, 0);
	if (ret)
		return ret;

	spi_set_drvdata(spi, drm);

	drm_client_setup(drm, NULL);

	return 0;
}

static void st7796s_remove(struct spi_device *spi)
{
	struct drm_device *drm = spi_get_drvdata(spi);

	drm_dev_unplug(drm);
	drm_atomic_helper_shutdown(drm);
}

static void st7796s_shutdown(struct spi_device *spi)
{
	drm_atomic_helper_shutdown(spi_get_drvdata(spi));
}

static struct spi_driver st7796s_spi_driver = {
	.driver = {
		.name = "st7796s",
		.of_match_table = st7796s_of_match,
	},
	.id_table = st7796s_id,
	.probe = st7796s_probe,
	.remove = st7796s_remove,
	.shutdown = st7796s_shutdown,
};
module_spi_driver(st7796s_spi_driver);

MODULE_DESCRIPTION("Sitronix ST7796S DRM driver");
MODULE_AUTHOR("opikernel");
MODULE_LICENSE("GPL");
