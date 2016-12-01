/*
 * Clock Initialization for board based on EXYNOS4412
 *
 *					2016
 * Modified by AP0904225 <ap0904225@qq.com>
 *
 * Copyright (C) 2013 Samsung Electronics
 * Rajeshwari Shinde <rajeshwari.s@samsung.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <config.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clk.h>
#include <asm/arch/clock.h>
#include "common_setup.h"

#include "exynos4412_setup.h"

/*
 * system_clock_init: Initialize core clock and bus clock.
 * void system_clock_init(void)
 */
void system_clock_init(void)
{
	unsigned int set, clr, clr_src_cpu, clr_pll_con0, clr_src_dmc;
	struct exynos4x12_clock *clk =(struct exynos4x12_clock *)
						samsung_get_base_clock();

	/*
	*	APLL= 1400 MHz
	*	MPLL=800 MHz
	*	EPLL=96 MHz
	*	VPLL=108 MHz
	*	freq (ARMCLK) = 1400 MHz at 1.3 V
	*	freq (ACLK_COREM0) = 350 MHz at 1.3V
	*	freq (ACLK_COREM1) = 188 MHz at 1.3 V
	*	freq (PERIPHCLK) = 1400 MHz at 1.3 V
	*	freq (ATCLK) = 214 MHz at 1.3 V
	*	freq (PCLK_DBG) = 107 MHz at 1.3 V
	*	freq (SCLK_DMC) = 400 MHz at 1.0 V
	*	freq (ACLK_DMCD) = 200 MHz at 1.0 V
	*	freq (ACLK_DMCP) = 100 MHz at 1.0 V
	*	freq (ACLK_ACP) = 200 MHz at 1.0 V
	*	freq (PCLK_ACP) = 100 MHz at 1.0 V
	*	freq (SCLK_C2C) = 400 MHz at 1.0 V
	*	freq (ACLK_C2C) = 200 MHz at 1.0 V
	*	freq (ACLK_GDL) = 200 MHz at 1.0 V
	*	freq (ACLK_GPL) = 100 MHz at 1.0 V
	*	freq (ACLK_GDR) = 200 MHz at 1.0 V
	*	freq (ACLK_GPR) = 100 MHz at 1.0 V
	*	freq (ACLK_400_MCUISP) = 400 MHz at 1.0 V
	*	freq (ACLK_200) = 160 MHz at 1.0 V
	*	freq (ACLK_100) = 100 MHz at 1.0 V
	*	freq (ACLK_160) = 160 MHz at 1.0 V
	*	freq (ACLK_133) = 133 MHz at 1.0 V
	*	freq (SCLK_ONENAND) = 160 MHz at 1.0 V
	*/

	/*
	 *before set system clocks,we switch system clocks src to FINpll
	*/

		/*
		 * Bit values:             0      ;    1
		 * MUX_APLL_SEL:        FIN_PLL   ; FOUT_APLL
		 * MUX_CORE_SEL:        MOUT_APLL ; SCLK_MPLL
		 * MUX_HPM_SEL:         MOUT_APLL ; SCLK_MPLL_USER_C
		 * MUX_MPLL_USER_SEL_C: FIN_PLL   ; SCLK_MPLL
		*/
	clr_src_cpu = MUX_APLL_SEL(1) | MUX_CORE_SEL(1) |
		      MUX_HPM_SEL(1) | MUX_MPLL_USER_SEL_C(1);
	set = MUX_APLL_SEL(0) | MUX_CORE_SEL(0) | MUX_HPM_SEL(0) |
	      MUX_MPLL_USER_SEL_C(0);
	clrsetbits_le32(&clk->src_cpu, clr_src_cpu, set);
	/* Wait for mux change */
	while (readl(&clk->mux_stat_cpu) & MUX_STAT_CPU_CHANGING)
		continue;


	/*
	******************************************************
	* 			Step 1: Set Clock divider
	******************************************************
	*/

	/*=====================set APLL related dividers(CMU_CPU)==============================*/
		/*
		 * Set dividers for MOUTcore
		 * MOUTcore  	=	MOUTapll = 1400 MHz
		 * SCLKapll 	=	MOUTapll / (APLL_RATIO + 1) = 700 MHz (DIVapll:APLL_RATIO=1)
		 * ARMCLK    	=	MOUTcore / (ratio + 1) = 1400 MHz (DIVcore:CORE_RATIO=0;DIVcore2:CORE2_RATIO=0)
		 * ACLK_COREM0 	=   ARMCLK / (COREM0_RATIO + 1) = 355 MHz (DIVcorem0:COREM0_RATIO=3)
		 * ACLK_COREM1 	=   ARMCLK / (COREM1_RATIO + 1) = 188 MHz (DIVcorem1:COREM1_RATIO=7)
		 * PERIPHCLK 	=   ARMCLK / (PERIPH_RATIO + 1) = 1400 MHz (DIVperiph:PERIPH_RATIO=0)
		 * OUTatb		= 	MOUTcore / (ATB_RATIO + 1) = 200 MHz (DIVatb:ATB_RATIO=6)
		 * ATCLK 		=   OUTatb = 200 MHz
		 * PCLK_DBG 	= OUTatb / (PCLK_DBG_RATIO + 1) = 100 MHz (PCLK_DBG_RATIO=1)
		*/
	clr = APLL_RATIO(7) |CORE_RATIO(7)| CORE2_RATIO(7)|
			COREM0_RATIO(7) | COREM1_RATIO(7) |
	      PERIPH_RATIO(7) | ATB_RATIO(7) | PCLK_DBG_RATIO(7) ;
	set = APLL_RATIO(1) |CORE_RATIO(0) | CORE2_RATIO(0) |
			COREM0_RATIO(3) | COREM1_RATIO(7)|
	      PERIPH_RATIO(0) | ATB_RATIO(6) | PCLK_DBG_RATIO(1) ;
	clrsetbits_le32(&clk->div_cpu0, clr, set);

	/* Wait for divider ready status */
	while (readl(&clk->div_stat_cpu0) & DIV_STAT_CPU0_CHANGING)
		continue;

		/* Set dividers for MOUThpm
		 * MOUThpm =	MOUTapll = 1400 MHz
		 * OUTcopy =	MOUThpm / (COPY_RATIO + 1) = 200 (DIVcopy:COPY_RATIO=6)
		 * sclkhpm =	OUTcopy / (HPM_RATIO + 1) = 200 (DIVhpm:HPM_RATIO=0)
		 * ACLK_CORES = ARMCLK / (CORES_RATIO + 1) = 233 (DIVcores:CORES_RATIO=5)
		 */
	clr = COPY_RATIO(7) | HPM_RATIO(7) | CORES_RATIO(7);
	set = COPY_RATIO(6) | HPM_RATIO(0) | CORES_RATIO(5);
	clrsetbits_le32(&clk->div_cpu1, clr, set);

	/* Wait for divider ready status */
	while (readl(&clk->div_stat_cpu1) & DIV_STAT_CPU1_CHANGING)
		continue;


	/*=====================set MPLL related dividers(CMU_DMC)==============================*/

		/*
		 * Set CLK_DIV_DMC0
		 * MOUTmpll = SCLKmpll = 800 MHz
		 * MOUTdmc_bus  = SCLKmpll = 800 MHz
		 * MOUTdphy = SCLKmpll = 800 MHz
		 *
		 * SCLK_DMC = MOUTdmc_bus / (DMC_RATIO + 1) = 400MHz (DIVdmc:DMC_RATIO=1)
		 * ACLK_DMCD = SCLK_DMC / (DMCD_RATIO + 1) = 200MHz  (DIVdmcd:DMCD_RATIO=1)
		 * ACLK_DMCP = ACLK_DMCD / (DMCP_RATIO + 1) = 100MHz (DIVdmcp:DMCP_RATIO=1)
		 * ACLK_ACP = MOUTdmc_bus / (ACP_RATIO + 1) = 200MHz (DIVacp:ACP_RATIO=3)
		 * PCLK_ACP = ACLK_ACP / (ACP_PCLK_RATIO + 1) = 100MHz (DIVacp_pclk:ACP_PCLK_RATIO=1)
		 * SCLK_DPHY = MOUTdphy / (DPHY_RATIO + 1) = 400MHz (DIVdphy:DPHY_RATIO=1)
		 */
	clr = DMC_RATIO(7) | DMCD_RATIO(7) | DMCP_RATIO(7) |
				ACP_RATIO(7) | ACP_PCLK_RATIO(7) | DPHY_RATIO(7);
	set = DMC_RATIO(1) | DMCD_RATIO(1) | DMCP_RATIO(1) |
				ACP_RATIO(3) | ACP_PCLK_RATIO(1) | DPHY_RATIO(1);
	clrsetbits_le32(&clk->div_dmc0, clr, set);

	/* Wait for divider ready status */
	while (readl(&clk->div_stat_dmc0) & DIV_STAT_DMC0_CHANGING)
		continue;

		/*
		 * Set CLK_DIV_DMC1
		 * MOUTmpll = SCLKmpll = 800 MHz
		 * MOUTc2c = SCLKmpll = 800 Mhz
		 * MOUTpwi = SCLKmpll = 800 MHz
		 * MOUTg2d_acp = SCLKmpll = 800 MHz
		 *
		 * SCLK_C2C = MOUTc2c / (C2C_RATIO + 1) = 400MHz (DIVc2c:C2C_RATIO=1)
		 * ACLK_C2C = SCLK_C2C / (C2C_ACLK_RATIO + 1) = 200MHz (DIVc2c_aclk:C2C_ACLK_RATIO=1)
		 * SCLK_PWI = MOUTpwi / (PWI_RATIO + 1) = 100MHz (DIVpwi:PWI_RATIO=7)
		 * SCLK_G2D_ACP = MOUTg2d_acp / (G2D_ACP_RATIO + 1) = 200MHz (G2D_ACP_RATIO=3)
		 * IECDPMCLKEN = ACLK_DMCP/( DPM_RATIO+ 1) = 50MHz(DIVdpm:DPM_RATIO=1)
		 * IECDVSEMCLKEN = ACLK_DMCP/( DVSEM_RATIO+ 1) = 50MHz(DIVdvsem:DVSEM_RATIO=1)
		 */
	clr = C2C_RATIO(7) | C2C_ACLK_RATIO(7) | PWI_RATIO(15) |
				G2D_ACP_RATIO(15) | DVSEM_RATIO(127) | DPM_RATIO(127);
	set = C2C_RATIO(1) | C2C_ACLK_RATIO(1) | PWI_RATIO(7) |
				G2D_ACP_RATIO(3) | DVSEM_RATIO(1) | DPM_RATIO(1);
	clrsetbits_le32(&clk->div_dmc1, clr, set);

	/* Wait for divider ready status */
	while (readl(&clk->div_stat_dmc1) & DIV_STAT_DMC1_CHANGING)
		continue;


	/*=====================set CMU_TOP related dividers==============================*/
		/*
		 * Set CLK_DIV_TOP
		 * SCLKmll_user_t = SCLKmpll = 800 MHz
		 * MOUTACLK_400_MC = SCLKmpll = 800 MHz
		 * MOUTACLK_400_MCUISP = MOUTACLK_400_MC/(ACLK_400_MCUISP_RATIO + 1) = 400MHz (DIVaclk_400_mc:ACLK_400_MCUISP_RATIO=1)
		 * MOUTACLK_200 = SCLKmpll = 800 MHz
		 * ACLK_200 = MOUTACLK_200/(ACLK_200_RATIO + 1) = 160MHz (DIVaclk_200:ACLK_200_RATIO=4)
		 * MOUTACLK_266_gps = SCLKmpll = 800 MHz
		 * ACLK_266_GPS = [MOUTACLK_266_GPS /(ACLK_266_GPS_RATIO + 1)] = 266MHz (DIVaclk_266_gps:ACLK_266_GPS_RATIO=2)
		 * MOUTACLK_100 = SCLKmpll = 800 MHz
		 * ACLK_100 = [MOUTACLK_100/(ACLK_100_RATIO + 1)] = 100MHz (DIVaclk_100:ACLK_100_RATIO=7)
		 * MOUTACLK_160 = SCLKmpll = 800 MHz
		 * ACLK_160 = [MOUTACLK_160 /(ACLK_160_RATIO + 1)] = 160MHz (DIVaclk_160:ACLK_160_RATIO=4)
		 * MOUTACLK_133 = SCLKmpll = 800 MHz
		 * ACLK_133 = [MOUTACLK_133 /(ACLK_133_RATIO + 1)] = 133MHz (DIVaclk_133:ACLK_133_RATIO=5)
		 * MOUTonenand = MOUTonenand_1 = ACLK_133MHz
		 * SCLK_ONENAND = [MOUTONENAND_1 /(ONENAND_RATIO + 1)] = 66MHz (DIVonenand:ONENAND_RATIO=1)
		 */
	clr = ACLK_400_MCUISP_RATIO(7) | ACLK_200_RATIO(7) | ACLK_266_GPS_RATIO(7) |
				ACLK_100_RATIO(15) | ACLK_160_RATIO(7) | ACLK_133_RATIO(7) |ONENAND_RATIO(7);
	set = ACLK_400_MCUISP_RATIO(1) | ACLK_200_RATIO(4) | ACLK_266_GPS_RATIO(2) |
				ACLK_100_RATIO(7) | ACLK_160_RATIO(4) | ACLK_133_RATIO(5) |ONENAND_RATIO(1);
	clrsetbits_le32(&clk->div_top, clr, set);

	/* Wait for divider ready status */
	while (readl(&clk->div_stat_top) & DIV_STAT_TOP_CHANGING)
		continue;

	/*=====================set CMU_LEFTBUS related dividers==============================*/
		/*
		 * Set CLK_DIV_LEFTBUS
		 * MOUTgdl = SCLKmpll = 800 MHz
		 * ACLK_GDL = MOUTgdl/(GDL_RATIO + 1) = 200MHz (DIVgdl:GDL_RATIO=3)
		 * ACLK_GPL = ACLK_GDL/(GPL_RATIO + 1) = 100MHz (DIVgpl:GPL_RATIO=1)
		 */
	clr = GDL_RATIO(7) | GPL_RATIO(7) ;
	set = GDL_RATIO(3) | GPL_RATIO(1) ;
	clrsetbits_le32(&clk->div_leftbus, clr, set);

	/* Wait for divider ready status */
	while (readl(&clk->div_stat_leftbus) & DIV_STAT_LEFTBUS_CHANGING)
		continue;

	/*=====================set CMU_RIGHTBUS related dividers==============================*/
		/*
		 * Set CLK_DIV_RIGHTBUS
		 * MOUTgdr = SCLKmpll = 800 MHz
		 * ACLK_GDR = MOUTgdr/(GDR_RATIO + 1) = 200MHz (DIVgdl:GDR_RATIO=3)
		 * ACLK_GPL = ACLK_GDL/(GPR_RATIO + 1) = 100MHz (DIVgpl:GPR_RATIO=1)
		 */
	clr = GDR_RATIO(7) | GPR_RATIO(7) ;
	set = GDR_RATIO(3) | GPR_RATIO(1) ;
	clrsetbits_le32(&clk->div_rightbus, clr, set);

	/* Wait for divider ready status */
	while (readl(&clk->div_stat_rightbus) & DIV_STAT_LEFTBUS_CHANGING)
		continue;

	/*=====================set other dividers==============================*/

	/* CLK_DIV_PERIL0 (UART0-4 dividers ) */
		/*
		 * MOUTuart0-4 = SCLKMPLL_USER_T =800MHz
		 *
		 * SCLK_UARTx = MOUTuartX / (UARTx_RATIO + 1) = 100MHz (DIVuart0-4:UARTx_RATIO=7)
		*/
	clr = UART0_RATIO(15) | UART1_RATIO(15) | UART2_RATIO(15) |
			  UART3_RATIO(15) | UART4_RATIO(15);
	set = UART0_RATIO(7) | UART1_RATIO(7) | UART2_RATIO(7) |
			  UART3_RATIO(7) | UART4_RATIO(7);
	clrsetbits_le32(&clk->div_peril0, clr, set);

	while (readl(&clk->div_stat_peril0) & DIV_STAT_PERIL0_CHANGING)
		continue;

	/* CLK_DIV_FSYS1 */
	clr = MMC0_RATIO(15) | MMC0_PRE_RATIO(255) | MMC1_RATIO(15) |
			  MMC1_PRE_RATIO(255);
		/*
		 * For MOUTmmc0-3 = 800 MHz (MPLL)
		 *
		 * DOUTmmc1 = MOUTmmc1 / (ratio + 1) = 100 (7)
		 * sclk_mmc1 = DOUTmmc1 / (ratio + 1) = 50 (1)
		 * DOUTmmc0 = MOUTmmc0 / (ratio + 1) = 100 (7)
		 * sclk_mmc0 = DOUTmmc0 / (ratio + 1) = 50 (1)
		*/
	set = MMC0_RATIO(7) | MMC0_PRE_RATIO(1) | MMC1_RATIO(7) |
			  MMC1_PRE_RATIO(1);

	clrsetbits_le32(&clk->div_fsys1, clr, set);

	/* Wait for divider ready status */
	while (readl(&clk->div_stat_fsys1) & DIV_STAT_FSYS1_CHANGING)
		continue;

	/* CLK_DIV_FSYS2 */
	clr = MMC2_RATIO(15) | MMC2_PRE_RATIO(255) | MMC3_RATIO(15) |
			  MMC3_PRE_RATIO(255);
		/*
		 * For MOUTmmc0-3 = 800 MHz (MPLL)
		 *
		 * DOUTmmc3 = MOUTmmc3 / (ratio + 1) = 100 (7)
		 * sclk_mmc3 = DOUTmmc3 / (ratio + 1) = 50 (1)
		 * DOUTmmc2 = MOUTmmc2 / (ratio + 1) = 100 (7)
		 * sclk_mmc2 = DOUTmmc2 / (ratio + 1) = 50 (1)
		*/
	set = MMC2_RATIO(7) | MMC2_PRE_RATIO(1) | MMC3_RATIO(7) |
			  MMC3_PRE_RATIO(1);

	clrsetbits_le32(&clk->div_fsys2, clr, set);

	/* Wait for divider ready status */
	while (readl(&clk->div_stat_fsys2) & DIV_STAT_FSYS2_CHANGING)
		continue;

	/* CLK_DIV_FSYS3 */
	clr = MMC4_RATIO(15) | MMC4_PRE_RATIO(255);
		/*
		 * For MOUTmmc4 = 800 MHz (MPLL)
		 *
		 * DOUTmmc4 = MOUTmmc4 / (ratio + 1) = 100 (7)
		 * sclk_mmc4 = DOUTmmc4 / (ratio + 1) = 100 (0)
		*/
	set = MMC4_RATIO(7) | MMC4_PRE_RATIO(0);

	clrsetbits_le32(&clk->div_fsys3, clr, set);

	/* Wait for divider ready status */
	while (readl(&clk->div_stat_fsys3) & DIV_STAT_FSYS3_CHANGING)
		continue;


	/*
	 * Step 2: Set APLL, MPLL, EPLL, VPLL locktime
	*/
	clr = PLL_LOCKTIME(65535);

	/*====== APLL locktime [APLL = 1400MHz :  SDIV(0) , PDIV(3) , MDIV(175)] =====*/
	set = PLL_LOCKTIME( PDIV(3) * 270 );
	clrsetbits_le32(&clk->apll_lock, clr, set);

	/*====== MPLL locktime [MPLL = 800MHz  :  SDIV(0) , PDIV(3) , MDIV(100)] =====*/
	set = PLL_LOCKTIME( PDIV(3) * 270 );
	clrsetbits_le32(&clk->mpll_lock, clr, set);

	/*====== EPLL locktime [EPLL = 96MHz   :  SDIV(3) , PDIV(2) , MDIV(64)] =====*/
	set = PLL_LOCKTIME( PDIV(2) * 3000 );
	clrsetbits_le32(&clk->epll_lock, clr, set);

	/*====== VPLL locktime [VPLL = 108MHz  :  SDIV(3) , PDIV(2) , MDIV(72)] =====*/
	set = PLL_LOCKTIME( PDIV(2) * 3000 );
	clrsetbits_le32(&clk->vpll_lock, clr, set);


	/*
	 * Step 3: Set PLL PMS values and enable PLL
	 *		1.Set PDIV, MDIV, and SDIV values for APLL, MPLL, EPLL, VPLL
	 *		2.Turn on APLL, MPLL, EPLL, VPLL
	*/

	/**************** Set APLL to 1400MHz ****************/
	/*APLL_CON1*/
	clr = AFC(15) | LOCK_CON_DLY(15) | LOCK_CON_IN(3) |
			LOCK_CON_OUT(3) |FEED_EN(1)| AFC_ENB(1) |
			DCC_ENB(1) | BYPASS(1) |RESV0(1) | RESV1(1);
	set = AFC(0) | LOCK_CON_DLY(8) | LOCK_CON_IN(3) |
			LOCK_CON_OUT(0) |FEED_EN(0)| AFC_ENB(0) |
			DCC_ENB(0) | BYPASS(0) |RESV0(1) | RESV1(0);
	clrsetbits_le32(&clk->apll_con1, clr, set);

	/*APLL_CON0*/
	clr_pll_con0 = SDIV(7) | PDIV(63) | MDIV(1023) | FSEL(1);
	set = SDIV(0) | PDIV(3) | MDIV(175) | FSEL(0) | PLL_ENABLE(1);
	clrsetbits_le32(&clk->apll_con0, clr_pll_con0, set);

	/* Wait for PLL to be locked */
	while (!(readl(&clk->apll_con0) & PLL_LOCKED_BIT))
		continue;


	/**************** Set MPLL to 800MHz ****************/
	/*MPLL_CON1*/
	clr = AFC(15) | LOCK_CON_DLY(15) | LOCK_CON_IN(3) |
			LOCK_CON_OUT(3) |FEED_EN(1)| AFC_ENB(1) |
			DCC_ENB(1) | BYPASS(1) |RESV0(1) | RESV1(1);
	set = AFC(0) | LOCK_CON_DLY(8) | LOCK_CON_IN(3) |
			LOCK_CON_OUT(0) |FEED_EN(0)| AFC_ENB(0) |
			DCC_ENB(0) | BYPASS(0) |RESV0(1) | RESV1(0);
	clrsetbits_le32(&clk->mpll_con1, clr, set);

	/*MPLL_CON0*/
	set = SDIV(0) | PDIV(3) | MDIV(100) | FSEL(0) | PLL_ENABLE(1);
	clrsetbits_le32(&clk->mpll_con0, clr_pll_con0, set);

	/* Wait for PLL to be locked */
	while (!(readl(&clk->mpll_con0) & PLL_LOCKED_BIT))
		continue;


	/**************** Set EPLL to 96MHz ****************/
	/*EPLL_CON2*/
	clr = BYPASS_E_V(1) | SSCG_EN(1) |
			AFC_ENB_E_V(1) |DCC_ENB_E_V(1) ;
	set = BYPASS_E_V(1) | SSCG_EN(1) |
			AFC_ENB_E_V(1) |DCC_ENB_E_V(1) ;
	clrsetbits_le32(&clk->epll_con2, clr, set);

	/*EPLL_CON1*/
	clr = K(65535) | MFR(255) | MRR(31) | SEL_PF(3);
	set = K(0) | MFR(1) | MRR(6) | SEL_PF(3);
	clrsetbits_le32(&clk->epll_con1, clr, set);

	/*EPLL_CON0*/
	set = SDIV(3) | PDIV(2) | MDIV(64) | PLL_ENABLE(1);
	clrsetbits_le32(&clk->epll_con0, clr_pll_con0, set);

	/* Wait for PLL to be locked */
	while (!(readl(&clk->epll_con0) & PLL_LOCKED_BIT))
		continue;


	/**************** Set VPLL to 108MHz ****************/
	/*VPLL_CON2*/
	clr = BYPASS_E_V(1) | SSCG_EN(1) |
			AFC_ENB_E_V(1) |DCC_ENB_E_V(1) ;
	set = BYPASS_E_V(1) | SSCG_EN(1) |
			AFC_ENB_E_V(1) |DCC_ENB_E_V(1) ;
	clrsetbits_le32(&clk->vpll_con2, clr, set);

	/*VPLL_CON1*/
	clr = K(65535) | MFR(255) | MRR(31) | SEL_PF(3);
	set = K(0) | MFR(1) | MRR(6) | SEL_PF(3);
	clrsetbits_le32(&clk->vpll_con1, clr, set);

	/*VPLL_CON0*/
	set = SDIV(3) | PDIV(2) | MDIV(72) | PLL_ENABLE(1);
	clrsetbits_le32(&clk->vpll_con0, clr_pll_con0, set);

	/* Wait for PLL to be locked */
	while (!(readl(&clk->vpll_con0) & PLL_LOCKED_BIT))
		continue;


	/*
	 * Step 4: Select the PLL(APLL, MPLL, EPLL, VPLL ...) output clock
	*/

	/*************** Set CMU_UART0-4 clocks src MUX ***************/

	/* CLK_SRC_PERIL0 */
	clr = UART0_SEL(15) | UART1_SEL(15) | UART2_SEL(15) |
	      UART3_SEL(15) | UART4_SEL(15);
	/*
	 * Set CLK_SRC_PERIL0 clocks src to MPLL
	 * src values: 0(XXTI); 1(XusbXTI); 2(SCLK_HDMI24M); 3(SCLK_USBPHY0);
	 *             5(SCLK_HDMIPHY); 6(SCLK_MPLL_USER_T); 7(SCLK_EPLL);
	 *             8(SCLK_VPLL)
	 *
	 * Set all to SCLK_MPLL_USER_T
	 */
	set = UART0_SEL(6) | UART1_SEL(6) | UART2_SEL(6) | UART3_SEL(6) |
	      UART4_SEL(6);

	clrsetbits_le32(&clk->src_peril0, clr, set);


	/*************** Set CMU_LEFTBUS clocks src MUX ***************/
	/* CLK_SRC_LEFTBUS */
	clr = MUX_GDL_SEL(1) | MUX_MPLL_USER_SEL_L(1);
	set = MUX_GDL_SEL(0) | MUX_MPLL_USER_SEL_L(1);
	clrsetbits_le32(&clk->src_leftbus, clr, set);

	/* Wait for mux change */
	sdelay(0x30000);


	/*************** Set CMU_RIGHTBUS clocks src MUX ***************/
	/* CLK_SRC_RIGHTBUS */
	clr = MUX_MPLL_USER_SEL_R(1) | MUX_GDR_SEL(1);
	set = MUX_MPLL_USER_SEL_R(1) | MUX_GDR_SEL(0);
	clrsetbits_le32(&clk->src_rightbus, clr, set);

	/* Wait for mux change */
	sdelay(0x30000);


	/*************** Set CMU_TOP clocks src MUX ***************/
	/* CLK_SRC_TOP0 */
	clr = MUX_EPLL_SEL(1) | MUX_VPLL_SEL(1) | MUX_ACLK_200_SEL(1) |
			MUX_ACLK_100_SEL(1) | MUX_ACLK_160_SEL(1) |
			MUX_ACLK_133_SEL(1) | MUX_ONENAND_SEL(1) | MUX_ONENAND_1_SEL(1);
	set = MUX_EPLL_SEL(1) | MUX_VPLL_SEL(1) | MUX_ACLK_200_SEL(0) |
			MUX_ACLK_100_SEL(0) | MUX_ACLK_160_SEL(0) |
			MUX_ACLK_133_SEL(0) | MUX_ONENAND_SEL(0) | MUX_ONENAND_1_SEL(0);
	clrsetbits_le32(&clk->src_top0, clr, set);

	/* Wait for mux change */
	sdelay(0x30000);


	/* CLK_SRC_TOP1 */
	clr = MUX_MPLL_USER_SEL_T(1) | MUX_ACLK_400_MCUISP_SEL(1) |
			MUX_ACLK_400_MCUISP_SUB_SEL(1) | MUX_ACLK_200_SUB_SEL(1) |
			MUX_ACLK_266_GPS_SEL(1) | MUX_ACLK_266_GPS_SUB_SEL(1);

	set = MUX_MPLL_USER_SEL_T(1) | MUX_ACLK_400_MCUISP_SEL(0) |
			MUX_ACLK_400_MCUISP_SUB_SEL(1) | MUX_ACLK_200_SUB_SEL(1) |
			MUX_ACLK_266_GPS_SEL(0) | MUX_ACLK_266_GPS_SUB_SEL(1);
	clrsetbits_le32(&clk->src_top1, clr, set);

	/* Wait for mux change */
	sdelay(0x30000);


	/*************** Set CMU_DMC clocks src MUX ***************/
		/*
		 * Set CMU_DMC clocks src to MPLL
		 * Bit values:             0  ; 1
		 * MUX_C2C_SEL:      SCLKMPLL ; SCLKAPLL
		 * MUX_DMC_BUS_SEL:  SCLKMPLL ; SCLKAPLL
		 * MUX_DPHY_SEL:     SCLKMPLL ; SCLKAPLL
		 * MUX_MPLL_SEL:     FINPLL   ; MOUT_MPLL_FOUT
		 * MUX_PWI_SEL:      0110 (MPLL); 0111 (EPLL); 1000 (VPLL); 0(XXTI)
		 * MUX_G2D_ACP0_SEL: SCLKMPLL ; SCLKAPLL
		 * MUX_G2D_ACP1_SEL: SCLKEPLL ; SCLKVPLL
		 * MUX_G2D_ACP_SEL:  OUT_ACP0 ; OUT_ACP1
		*/
	clr_src_dmc = MUX_C2C_SEL(1) | MUX_DMC_BUS_SEL(1) |
		      MUX_DPHY_SEL(1) | MUX_MPLL_SEL(1) |
		      MUX_PWI_SEL(15) | MUX_G2D_ACP0_SEL(1) |
		      MUX_G2D_ACP1_SEL(1) | MUX_G2D_ACP_SEL(1);
	set = MUX_MPLL_SEL(1) | MUX_C2C_SEL(0) | MUX_DMC_BUS_SEL(0) |
			MUX_DPHY_SEL(0) | MUX_PWI_SEL(6) |
			MUX_G2D_ACP0_SEL(0) | MUX_G2D_ACP1_SEL(0) | MUX_G2D_ACP_SEL(0);
	clrsetbits_le32(&clk->src_dmc, clr_src_dmc, set);

	/* Wait for mux change */
	while (readl(&clk->mux_stat_dmc) & MUX_STAT_DMC_CHANGING)
		continue;

	/*************** Set CMU_CPU clocks src MUX ***************/
		/* Set CMU_CPU clocks src to APLL
		 * Bit values:             0      ;    1
		 * MUX_APLL_SEL:        FIN_PLL   ; FOUT_APLL
		 * MUX_CORE_SEL:        MOUT_APLL ; SCLK_MPLL
		 * MUX_HPM_SEL:         MOUT_APLL ; SCLK_MPLL_USER_C
		 * MUX_MPLL_USER_SEL_C: FIN_PLL   ; SCLK_MPLL
		*/
	clr_src_cpu = MUX_APLL_SEL(1) | MUX_CORE_SEL(1) |
					MUX_HPM_SEL(1) | MUX_MPLL_USER_SEL_C(1);
	set = MUX_APLL_SEL(1) | MUX_CORE_SEL(0) | MUX_HPM_SEL(0) |
		  MUX_MPLL_USER_SEL_C(1);
	clrsetbits_le32(&clk->src_cpu, clr_src_cpu, set);

	/* Wait for mux change */
	while (readl(&clk->mux_stat_cpu) & MUX_STAT_CPU_CHANGING)
		continue;
}
