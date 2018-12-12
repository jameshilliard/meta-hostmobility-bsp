/*
 * Copyright (c) 2017 Host Mobiltiy AB
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/arch/gp_padctrl.h>
#include <asm/arch/pinmux.h>
#include <asm/arch-tegra/ap.h>
#include <asm/arch-tegra/tegra.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <i2c.h>
#include "pinmux-config-mx4_t30.h"
#include "../common/tdx-common.h"

#ifndef CONFIG_SPL_BUILD
#include "../mx4_common/mx4_common.h"
#endif

int arch_misc_init(void)
{
	if (readl(NV_PA_BASE_SRAM + NVBOOTINFOTABLE_BOOTTYPE) ==
	    NVBOOTTYPE_RECOVERY) {
		printf("USB recovery mode, disabled autoboot\n");
		setenv("bootdelay", "-1");
		setenv("bootretry", "-1");
	}

#ifndef CONFIG_SPL_BUILD
	if (ping_mx4_pic())
		printf("Failed to ping mx4 pic\n");
#endif

	return 0;
}

int checkboard(void)
{
	puts("Model: Toradex Colibri T30 1GB\n");

	return 0;
}

#if defined(CONFIG_OF_LIBFDT) && defined(CONFIG_OF_BOARD_SETUP)
int ft_board_setup(void *blob, bd_t *bd)
{
	return ft_common_board_setup(blob, bd);
}
#endif

/*
 * Routine: pinmux_init
 * Description: Do individual peripheral pinmux configs
 */
void pinmux_init(void)
{
	pinmux_config_pingrp_table(tegra3_pinmux_common,
				   ARRAY_SIZE(tegra3_pinmux_common));

	pinmux_config_pingrp_table(unused_pins_lowpower,
				   ARRAY_SIZE(unused_pins_lowpower));

	/* Initialize any non-default pad configs (APB_MISC_GP regs) */
	pinmux_config_drvgrp_table(colibri_t30_padctrl,
				   ARRAY_SIZE(colibri_t30_padctrl));
}

/*
 * Enable AX88772B USB to LAN controller
 */
void pin_mux_usb(void)
{
	/* Reset ASIX using LAN_RESET */
	gpio_request(TEGRA_GPIO(DD, 0), "LAN_RESET");
	gpio_direction_output(TEGRA_GPIO(DD, 0), 0);
	udelay(5);
	gpio_set_value(TEGRA_GPIO(DD, 0), 1);
}
