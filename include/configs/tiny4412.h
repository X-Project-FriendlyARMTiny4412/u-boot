/*
 *			2016
 * 	Author AP0904225 <ap0904225@qq.com>
 *
 * Configuration settings for the FriendlyARM TINY4412 (EXYNOS4412) board.
 *     FriendlyARM Tiny4412 SDK board hardware version:
 *           core board   :  Tiny4412-1412
 *           bottom board :  Tiny4412/Super4412SDK 1506
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_TINY4412_H
#define __CONFIG_TINY4412_H

#include <configs/exynos4-common.h>

/* TIZEN THOR downloader support */
#undef CONFIG_CMD_THOR_DOWNLOAD
#undef CONFIG_USB_FUNCTION_THOR

/* High Level Configuration Options */
#define TINY4412			1	/* working with TINY4412*/

#define CONFIG_SYS_DCACHE_OFF		1

/* TINY4412-1412 core board has 8 bank of DRAM */
#define CONFIG_NR_DRAM_BANKS		8
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define PHYS_SDRAM_1			CONFIG_SYS_SDRAM_BASE
#define SDRAM_BANK_SIZE			(128 << 20)	/* 128 MB */

/* memtest works on */
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + 0x6000000)
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x3E00000)

#define CONFIG_SYS_TEXT_BASE		0x43E00000

#define CONFIG_MACH_TYPE		MACH_TYPE_TINY4412

/* select serial console configuration */
#define CONFIG_SERIAL2
#define CONFIG_BAUDRATE			115200

/* Console configuration */
#define CONFIG_DEFAULT_CONSOLE		"console=ttySAC1,115200n8\0"

#define CONFIG_SYS_MEM_TOP_HIDE	(1 << 20)	/* ram console */

#define CONFIG_SYS_MONITOR_BASE	0x00000000

/* Power Down Modes */
#define S5P_CHECK_SLEEP			0x00000BAD
#define S5P_CHECK_DIDLE			0xBAD00000
#define S5P_CHECK_LPA			0xABAD0000

#define CONFIG_SUPPORT_RAW_INITRD

/* MMC SPL */
#define COPY_BL2_FNPTR_ADDR	0x02020030
#define CONFIG_SPL_TEXT_BASE	0x02023400
#define CONFIG_SPL_STACK	0x02060000

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x40007000\0" \
	"rdaddr=0x48000000\0" \
	"kerneladdr=0x40007000\0" \
	"ramdiskaddr=0x48000000\0" \
	"console=ttySAC2,115200n8\0" \
	"mmcdev=0\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=load mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc ...; " \
		"env import -t $loadaddr $filesize\0" \
        "loadbootscript=load mmc ${mmcdev} ${loadaddr} boot.scr\0" \
        "bootscript=echo Running bootscript from mmc${mmcdev} ...; " \
                "source ${loadaddr}\0"
#define CONFIG_BOOTCOMMAND \
	"if mmc rescan; then " \
		"echo SD/MMC found on device ${mmcdev};" \
		"if run loadbootenv; then " \
			"echo Loaded environment from ${bootenv};" \
			"run importbootenv;" \
		"fi;" \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...;" \
			"run uenvcmd;" \
		"fi;" \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"fi; " \
	"fi;" \
	"load mmc ${mmcdev} ${loadaddr} uImage; bootm ${loadaddr} "

#define CONFIG_CLK_1000_400_200

/* MIU (Memory Interleaving Unit) */
#define CONFIG_MIU_2BIT_21_7_INTERLEAVED

#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_ENV_SIZE			(16 << 10)	/* 16 KB */
#define RESERVE_BLOCK_SIZE		(512)
#define BL1_SIZE			(8 << 10) /* 8K reserved for BL1*/
#define BL2_SIZE			(16 << 10) /*16 K reserved for BL2/SPL*/
#define CONFIG_ENV_OFFSET		(RESERVE_BLOCK_SIZE + BL1_SIZE + BL2_SIZE)

#define CONFIG_SPL_LDSCRIPT	"board/samsung/common/exynos-uboot-spl.lds"
#define CONFIG_SPL_MAX_FOOTPRINT	(14 * 1024)

#define CONFIG_SYS_INIT_SP_ADDR		0x02040000

/* U-Boot copy size from SD/MMC to DRAM.*/
#define COPY_BL2_SIZE		0x80000
#define BL2_START_OFFSET	((CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)/512)
#define BL2_SIZE_BLOC_COUNT	(COPY_BL2_SIZE/512)  /* u-boot size is 512K */

/*
 *    SD/MMC(1 Block = 512B) layout:
 *    +------------+-------------------------------------------------------------------------------------------------+
 *    |                                                                             |
 *    |            |                    |                     |                     |                      |
 *    |   512B     |   8K(bl1)          |   16k(bl2/spl)      |   16k(ENV)          |  512k(u-boot)        |
 *    |            |                    |                     |                     |                      |
 *    |                                                                             |
 *    <- Block0  ->-<- Block1~Block16 ->-<- Block17~Block48 ->-<- Block49~Block80 ->-<- Block81~Block1073 ->----------+
 *
 *
 */



#endif	/* __CONFIG_H */
