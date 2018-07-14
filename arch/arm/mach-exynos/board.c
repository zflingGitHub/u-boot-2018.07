/*
 * board for power managenment and led test
 *
 * Copyright (C) 2018 zfl
 *             <18609265862@163.com>
 *
 */
#include <common.h>
#include <config.h>
#include <asm/io.h>

//#define USER_LED_TEST
void s_init(void)
{
	writel(readl(0x1002330c) | 0x300, 0x1002330c);
	writel(0, 0x11000c08);
#if 1
	/* led test */
	writel(0x10, 0x11000060);
	writel(0x2, 0x11000064);

	writel(0x1, 0x11000100);
	writel(0x0, 0x11000104);
#endif
}
