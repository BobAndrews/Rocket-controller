/*
 * @brief LPC8xx Power ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __PWRD_8XX_H_
#define __PWRD_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup PWRD_8XX CHIP: LPC8xx Power ROM API declarations and functions
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief LPC8XX Power ROM API structure
 */
typedef struct PWRD_API {
	void (*set_pll)(uint32_t cmd[], uint32_t resp[]);	/*!< Set PLL function */
	void (*set_power)(uint32_t cmd[], uint32_t resp[]);	/*!< Set power function */
	void (*set_aclkgate)(uint32_t aclkgate);			/*!< Set ACLKGATE function */
	uint32_t (*get_aclkgate)(void);						/*!< Get ACLKGATE function */
} PWRD_API_T;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __PWRD_8XX_H_ */
