/*
 * Copyright (C) 2014 Samsung Electronics
 * Przemyslaw Marczak <p.marczak@samsung.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __EXYNOS4412_SETUP__
#define __EXYNOS4412_SETUP__

/* A/M/E/V PLL_CON0 */
#define SDIV(x)                 ((x) & 0x7)
#define PDIV(x)                 (((x) & 0x3f) << 8)
#define MDIV(x)                 (((x) & 0x3ff) << 16)
#define FSEL(x)                 (((x) & 0x1) << 27)
#define PLL_LOCKED_BIT          (0x1 << 29)
#define PLL_ENABLE(x)           (((x) & 0x1) << 31)

/* A/M PLL_CON1 */
#define AFC(x)                 ((x) & 0xf)
#define LOCK_CON_DLY(x)        (((x) & 0xf) << 8)
#define LOCK_CON_IN(x)        (((x) & 0x3) << 12)
#define LOCK_CON_OUT(x)        (((x) & 0x3) << 14)
#define FEED_EN(x)        (((x) & 0x1) << 16)
#define AFC_ENB(x)        (((x) & 0x1) << 20)
#define DCC_ENB(x)        (((x) & 0x1) << 21)
#define BYPASS(x)        (((x) & 0x1) << 22)
#define RESV0(x)        (((x) & 0x1) << 23)
#define RESV1(x)        (((x) & 0x1) << 24)

/* E/V PLL_CON1 */
#define K(x)                 ((x) & 0xffff)
#define MFR(x)        (((x) & 0xff) << 16)
#define MRR(x)        (((x) & 0x1f) << 24)
#define SEL_PF(x)        (((x) & 0x3) << 9)

/* E/V PLL_CON2 */
#define ICP_BOOST(x)    ((x) & 0x3)
#define FSEL_E_V(x)        (((x) & 0x1) << 2)
#define FVCO_EN(x)        (((x) & 0x1) << 3)
#define BYPASS_E_V(x)        (((x) & 0x1) << 4)
#define SSCG_EN(x)        (((x) & 0x1) << 5)
#define AFC_ENB_E_V(x)        (((x) & 0x1) << 6)
#define DCC_ENB_E_V(x)        (((x) & 0x1) << 7)
#define EXTAFC(x)        (((x) & 0x1f) << 8)

#define PLL_LOCKTIME(x)	((x) & 0xffff)


/* CLK_SRC_CPU */
#define MUX_APLL_SEL(x)         ((x) & 0x1)
#define MUX_CORE_SEL(x)         (((x) & 0x1) << 16)
#define MUX_HPM_SEL(x)          (((x) & 0x1) << 20)
#define MUX_MPLL_USER_SEL_C(x)  (((x) & 0x1) << 24)

#define MUX_STAT_CHANGING       0x100

/* CLK_MUX_STAT_CPU */
#define APLL_SEL(x)             ((x) & 0x7)
#define CORE_SEL(x)             (((x) & 0x7) << 16)
#define HPM_SEL(x)              (((x) & 0x7) << 20)
#define MPLL_USER_SEL_C(x)      (((x) & 0x7) << 24)
#define MUX_STAT_CPU_CHANGING   (APLL_SEL(MUX_STAT_CHANGING) | \
				CORE_SEL(MUX_STAT_CHANGING) | \
				HPM_SEL(MUX_STAT_CHANGING) | \
				MPLL_USER_SEL_C(MUX_STAT_CHANGING))

/* CLK_DIV_CPU0 */
#define CORE_RATIO(x)           ((x) & 0x7)
#define COREM0_RATIO(x)         (((x) & 0x7) << 4)
#define COREM1_RATIO(x)         (((x) & 0x7) << 8)
#define PERIPH_RATIO(x)         (((x) & 0x7) << 12)
#define ATB_RATIO(x)            (((x) & 0x7) << 16)
#define PCLK_DBG_RATIO(x)       (((x) & 0x7) << 20)
#define APLL_RATIO(x)           (((x) & 0x7) << 24)
#define CORE2_RATIO(x)          (((x) & 0x7) << 28)

/* CLK_DIV_STAT_CPU0 */
#define DIV_CORE(x)             ((x) & 0x1)
#define DIV_COREM0(x)           (((x) & 0x1) << 4)
#define DIV_COREM1(x)           (((x) & 0x1) << 8)
#define DIV_PERIPH(x)           (((x) & 0x1) << 12)
#define DIV_ATB(x)              (((x) & 0x1) << 16)
#define DIV_PCLK_DBG(x)         (((x) & 0x1) << 20)
#define DIV_APLL(x)             (((x) & 0x1) << 24)
#define DIV_CORE2(x)            (((x) & 0x1) << 28)

#define DIV_STAT_CHANGING       0x1
#define DIV_STAT_CPU0_CHANGING  (DIV_CORE(DIV_STAT_CHANGING) | \
				DIV_COREM0(DIV_STAT_CHANGING) | \
				DIV_COREM1(DIV_STAT_CHANGING) | \
				DIV_PERIPH(DIV_STAT_CHANGING) | \
				DIV_ATB(DIV_STAT_CHANGING) | \
				DIV_PCLK_DBG(DIV_STAT_CHANGING) | \
				DIV_APLL(DIV_STAT_CHANGING) | \
				DIV_CORE2(DIV_STAT_CHANGING))

/* CLK_DIV_CPU1 */
#define COPY_RATIO(x)           ((x) & 0x7)
#define HPM_RATIO(x)            (((x) & 0x7) << 4)
#define CORES_RATIO(x)          (((x) & 0x7) << 8)

/* CLK_DIV_STAT_CPU1 */
#define DIV_COPY(x)             ((x) & 0x7)
#define DIV_HPM(x)              (((x) & 0x1) << 4)
#define DIV_CORES(x)            (((x) & 0x1) << 8)

#define DIV_STAT_CPU1_CHANGING	(DIV_COPY(DIV_STAT_CHANGING) | \
				DIV_HPM(DIV_STAT_CHANGING) | \
				DIV_CORES(DIV_STAT_CHANGING))

/* CLK_SRC_DMC */
#define MUX_C2C_SEL(x)		((x) & 0x1)
#define MUX_DMC_BUS_SEL(x)	(((x) & 0x1) << 4)
#define MUX_DPHY_SEL(x)		(((x) & 0x1) << 8)
#define MUX_MPLL_SEL(x)		(((x) & 0x1) << 12)
#define MUX_PWI_SEL(x)		(((x) & 0xf) << 16)
#define MUX_G2D_ACP0_SEL(x)	(((x) & 0x1) << 20)
#define MUX_G2D_ACP1_SEL(x)	(((x) & 0x1) << 24)
#define MUX_G2D_ACP_SEL(x)	(((x) & 0x1) << 28)

/* CLK_MUX_STAT_DMC */
#define C2C_SEL(x)		(((x)) & 0x7)
#define DMC_BUS_SEL(x)		(((x) & 0x7) << 4)
#define DPHY_SEL(x)		(((x) & 0x7) << 8)
#define MPLL_SEL(x)		(((x) & 0x7) << 12)
/* #define PWI_SEL(x)		(((x) & 0xf) << 16)  - Reserved */
#define G2D_ACP0_SEL(x)		(((x) & 0x7) << 20)
#define G2D_ACP1_SEL(x)		(((x) & 0x7) << 24)
#define G2D_ACP_SEL(x)		(((x) & 0x7) << 28)

#define MUX_STAT_DMC_CHANGING	(C2C_SEL(MUX_STAT_CHANGING) | \
				DMC_BUS_SEL(MUX_STAT_CHANGING) | \
				DPHY_SEL(MUX_STAT_CHANGING) | \
				MPLL_SEL(MUX_STAT_CHANGING) |\
				G2D_ACP0_SEL(MUX_STAT_CHANGING) | \
				G2D_ACP1_SEL(MUX_STAT_CHANGING) | \
				G2D_ACP_SEL(MUX_STAT_CHANGING))

/* CLK_DIV_DMC0 */
#define ACP_RATIO(x)		((x) & 0x7)
#define ACP_PCLK_RATIO(x)	(((x) & 0x7) << 4)
#define DPHY_RATIO(x)		(((x) & 0x7) << 8)
#define DMC_RATIO(x)		(((x) & 0x7) << 12)
#define DMCD_RATIO(x)		(((x) & 0x7) << 16)
#define DMCP_RATIO(x)		(((x) & 0x7) << 20)

/* CLK_DIV_STAT_DMC0 */
#define DIV_ACP(x)		((x) & 0x1)
#define DIV_ACP_PCLK(x)		(((x) & 0x1) << 4)
#define DIV_DPHY(x)		(((x) & 0x1) << 8)
#define DIV_DMC(x)		(((x) & 0x1) << 12)
#define DIV_DMCD(x)		(((x) & 0x1) << 16)
#define DIV_DMCP(x)		(((x) & 0x1) << 20)

#define DIV_STAT_DMC0_CHANGING	(DIV_ACP(DIV_STAT_CHANGING) | \
				DIV_ACP_PCLK(DIV_STAT_CHANGING) | \
				DIV_DPHY(DIV_STAT_CHANGING) | \
				DIV_DMC(DIV_STAT_CHANGING) | \
				DIV_DMCD(DIV_STAT_CHANGING) | \
				DIV_DMCP(DIV_STAT_CHANGING))

/* CLK_DIV_DMC1 */
#define G2D_ACP_RATIO(x)	((x) & 0xf)
#define C2C_RATIO(x)		(((x) & 0x7) << 4)
#define PWI_RATIO(x)		(((x) & 0xf) << 8)
#define C2C_ACLK_RATIO(x)	(((x) & 0x7) << 12)
#define DVSEM_RATIO(x)		(((x) & 0x7f) << 16)
#define DPM_RATIO(x)		(((x) & 0x7f) << 24)

/* CLK_DIV_STAT_DMC1 */
#define DIV_G2D_ACP(x)		((x) & 0x1)
#define DIV_C2C(x)		(((x) & 0x1) << 4)
#define DIV_PWI(x)		(((x) & 0x1) << 8)
#define DIV_C2C_ACLK(x)		(((x) & 0x1) << 12)
#define DIV_DVSEM(x)		(((x) & 0x1) << 16)
#define DIV_DPM(x)		(((x) & 0x1) << 24)

#define DIV_STAT_DMC1_CHANGING	(DIV_G2D_ACP(DIV_STAT_CHANGING) | \
				DIV_C2C(DIV_STAT_CHANGING) | \
				DIV_PWI(DIV_STAT_CHANGING) | \
				DIV_C2C_ACLK(DIV_STAT_CHANGING) | \
				DIV_DVSEM(DIV_STAT_CHANGING) | \
				DIV_DPM(DIV_STAT_CHANGING))

/* CLK_DIV_TOP */
#define	ACLK_400_MCUISP_RATIO(x)	(((x) & 0x7) << 24)
#define	ACLK_266_GPS_RATIO(x)	(((x) & 0x7) << 20)
#define	ONENAND_RATIO(x)	(((x) & 0x7) << 16)
#define	ACLK_133_RATIO(x)	(((x) & 0x7) << 12)
#define ACLK_160_RATIO(x)	(((x) & 0x7) << 8)
#define ACLK_100_RATIO(x)	(((x) & 0xf) << 4)
#define ACLK_200_RATIO(x)	((x) & 0x7)

#define DIV_STAT_TOP_CHANGING	(ACLK_400_MCUISP_RATIO(DIV_STAT_CHANGING) | \
				ACLK_266_GPS_RATIO(DIV_STAT_CHANGING) | \
				ONENAND_RATIO(DIV_STAT_CHANGING) | \
				ACLK_133_RATIO(DIV_STAT_CHANGING) | \
				ACLK_160_RATIO(DIV_STAT_CHANGING) | \
				ACLK_100_RATIO(DIV_STAT_CHANGING) | \
				ACLK_200_RATIO(DIV_STAT_CHANGING))

/* CLK_SRC_TOP0 */
#define MUX_ONENAND_SEL(x)		(((x) & 0x1) << 28)
#define MUX_ACLK_133_SEL(x)		(((x) & 0x1) << 24)
#define MUX_ACLK_160_SEL(x)		(((x) & 0x1) << 20)
#define MUX_ACLK_100_SEL(x)		(((x) & 0x1) << 16)
#define MUX_ACLK_200_SEL(x)		(((x) & 0x1) << 12)
#define MUX_VPLL_SEL(x)		(((x) & 0x1) << 8)
#define MUX_EPLL_SEL(x)		(((x) & 0x1) << 4)
#define MUX_ONENAND_1_SEL(x)	((x) & 0x1)

/* CLK_MUX_STAT_TOP */
#define ONENAND_SEL(x)		(((x) & 0x3) << 28)
#define ACLK_133_SEL(x)		(((x) & 0x3) << 24)
#define ACLK_160_SEL(x)		(((x) & 0x3) << 20)
#define ACLK_100_SEL(x)		(((x) & 0x3) << 16)
#define ACLK_200_SEL(x)		(((x) & 0x3) << 12)
#define VPLL_SEL(x)		(((x) & 0x3) << 8)
#define EPLL_SEL(x)		(((x) & 0x3) << 4)
#define ONENAND_1_SEL(x)	((x) & 0x3)

/* CLK_SRC_TOP1 */
#define MUX_ACLK_400_MCUISP_SUB_SEL(x)		(((x) & 0x1) << 24)
#define MUX_ACLK_200_SUB_SEL(x)		(((x) & 0x1) << 20)
#define MUX_ACLK_266_GPS_SUB_SEL(x)		(((x) & 0x1) << 16)
#define MUX_MPLL_USER_SEL_T(x)		(((x) & 0x1) << 12)
#define MUX_ACLK_400_MCUISP_SEL(x)		(((x) & 0x1) << 8)
#define MUX_ACLK_266_GPS_SEL(x)		(((x) & 0x1) << 4)

/* CLK_MUX_STAT_TOP1 */
#define ACLK_400_MCUISP_SUB_SEL(x)		(((x) & 0x3) << 24)
#define ACLK_200_SUB_SEL(x)		(((x) & 0x3) << 20)
#define ACLK_266_GPS_SUB_SEL(x)		(((x) & 0x3) << 16)
#define MPLL_USER_SEL_T(x)		(((x) & 0x3) << 12)
#define ACLK_400_MCUISP_SEL(x)		(((x) & 0x3) << 8)
#define ACLK_266_GPS_SEL(x)		(((x) & 0x3) << 4)






/*CLK_DIV_LEFTBUS*/
#define GDL_RATIO(x)	((x) & 0x7)
#define GPL_RATIO(x)	(((x) & 0x7) << 4)

#define DIV_STAT_LEFTBUS_CHANGING	(GDL_RATIO(DIV_STAT_CHANGING) | \
										GPL_RATIO(DIV_STAT_CHANGING) )
/* CLK_SRC_LEFTBUS */
#define MUX_MPLL_USER_SEL_L(x)		(((x) & 0x1) << 4)
#define MUX_GDL_SEL(x)		((x) & 0x1)

/* CLK_MUX_STAT_LEFTBUS */
#define MPLL_USER_SEL_L(x)		(((x) & 0x3) << 4)
#define GDL_SEL(x)		((x) & 0x3)


/*CLK_DIV_RIGHTBUS*/
#define GDR_RATIO(x)	((x) & 0x7)
#define GPR_RATIO(x)	(((x) & 0x7) << 4)

#define DIV_STAT_RIGHTBUS_CHANGING	(GDR_RATIO(DIV_STAT_CHANGING) | \
								GPR_RATIO(DIV_STAT_CHANGING) )

/* CLK_SRC_RIGHTBUS */
#define MUX_MPLL_USER_SEL_R(x)		(((x) & 0x1) << 4)
#define MUX_GDR_SEL(x)		((x) & 0x1)

/* CLK_MUX_STAT_RIGHTBUS */
#define MPLL_USER_SEL_R(x)		(((x) & 0x3) << 4)
#define GDR_SEL(x)		((x) & 0x3)




/* Set CLK_SRC_PERIL0 */
#define UART4_SEL(x)		(((x) & 0xf) << 16)
#define UART3_SEL(x)		(((x) & 0xf) << 12)
#define UART2_SEL(x)		(((x) & 0xf) << 8)
#define UART1_SEL(x)		(((x) & 0xf) << 4)
#define UART0_SEL(x)		((x) & 0xf)

/* Set CLK_DIV_PERIL0 */
#define UART4_RATIO(x)		(((x) & 0xf) << 16)
#define UART3_RATIO(x)		(((x) & 0xf) << 12)
#define UART2_RATIO(x)		(((x) & 0xf) << 8)
#define UART1_RATIO(x)		(((x) & 0xf) << 4)
#define UART0_RATIO(x)		((x) & 0xf)

/* Set CLK_DIV_STAT_PERIL0 */
#define DIV_UART4(x)		(((x) & 0x1) << 16)
#define DIV_UART3(x)		(((x) & 0x1) << 12)
#define DIV_UART2(x)		(((x) & 0x1) << 8)
#define DIV_UART1(x)		(((x) & 0x1) << 4)
#define DIV_UART0(x)		((x) & 0x1)

#define DIV_STAT_PERIL0_CHANGING	(DIV_UART4(DIV_STAT_CHANGING) | \
					DIV_UART3(DIV_STAT_CHANGING) | \
					DIV_UART2(DIV_STAT_CHANGING) | \
					DIV_UART1(DIV_STAT_CHANGING) | \
					DIV_UART0(DIV_STAT_CHANGING))

/* CLK_DIV_FSYS1 */
#define MMC0_RATIO(x)		((x) & 0xf)
#define MMC0_PRE_RATIO(x)	(((x) & 0xff) << 8)
#define MMC1_RATIO(x)		(((x) & 0xf) << 16)
#define MMC1_PRE_RATIO(x)	(((x) & 0xff) << 24)

/* CLK_DIV_STAT_FSYS1 */
#define DIV_MMC0(x)		((x) & 1)
#define DIV_MMC0_PRE(x)		(((x) & 1) << 8)
#define DIV_MMC1(x)		(((x) & 1) << 16)
#define DIV_MMC1_PRE(x)		(((x) & 1) << 24)

#define DIV_STAT_FSYS1_CHANGING		(DIV_MMC0(DIV_STAT_CHANGING) | \
					DIV_MMC0_PRE(DIV_STAT_CHANGING) | \
					DIV_MMC1(DIV_STAT_CHANGING) | \
					DIV_MMC1_PRE(DIV_STAT_CHANGING))

/* CLK_DIV_FSYS2 */
#define MMC2_RATIO(x)		((x) & 0xf)
#define MMC2_PRE_RATIO(x)	(((x) & 0xff) << 8)
#define MMC3_RATIO(x)		(((x) & 0xf) << 16)
#define MMC3_PRE_RATIO(x)	(((x) & 0xff) << 24)

/* CLK_DIV_STAT_FSYS2 */
#define DIV_MMC2(x)		((x) & 0x1)
#define DIV_MMC2_PRE(x)		(((x) & 0x1) << 8)
#define DIV_MMC3(x)		(((x) & 0x1) << 16)
#define DIV_MMC3_PRE(x)		(((x) & 0x1) << 24)

#define DIV_STAT_FSYS2_CHANGING		(DIV_MMC2(DIV_STAT_CHANGING) | \
					DIV_MMC2_PRE(DIV_STAT_CHANGING) | \
					DIV_MMC3(DIV_STAT_CHANGING) | \
					DIV_MMC3_PRE(DIV_STAT_CHANGING))

/* CLK_DIV_FSYS3 */
#define MMC4_RATIO(x)		((x) & 0x7)
#define MMC4_PRE_RATIO(x)	(((x) & 0xff) << 8)

/* CLK_DIV_STAT_FSYS3 */
#define DIV_MMC4(x)		((x) & 0x1)
#define DIV_MMC4_PRE(x)		(((x) & 0x1) << 8)

#define DIV_STAT_FSYS3_CHANGING		(DIV_MMC4(DIV_STAT_CHANGING) | \
					DIV_MMC4_PRE(DIV_STAT_CHANGING))


#endif /*__EXYNOS4412_SETUP__ */
