/*
 * dwt_lib.h
 *
 *  Created on: 2017/10/07
 *      Author: takeshi
 */
#include "stm32f7xx_hal.h"

#ifndef DWT_LIB_H_
#define DWT_LIB_H_

#define DWT_LSR_SLK_Pos                1
#define DWT_LSR_SLK_Msk                (1UL << DWT_LSR_SLK_Pos)
// CoreSight Lock Status Register lock availability bit
#define DWT_LSR_SLI_Pos                0
#define DWT_LSR_SLI_Msk                (1UL << DWT_LSR_SLI_Pos)
// CoreSight Lock Access key, common for all
#define DWT_LAR_KEY                    0xC5ACCE55

volatile uint32_t start_time;
volatile uint32_t stop_time;
volatile float process_time_us;
volatile float cpuload;

uint32_t get_cpu_cycle();
void init_cpu_cycle();
float get_process_time(uint32_t start,uint32_t stop);
float get_cpu_load(uint32_t start,uint32_t stop);

static inline void dwt_access_enable(int ena)
{
    uint32_t lsr = DWT->LSR;//ロックステータスのチェック

    if ((lsr & DWT_LSR_SLI_Msk) != 0)
    {
        if (ena)
        {
            if ((lsr & DWT_LSR_SLK_Msk) != 0)    //locked: access need unlock
                DWT->LAR = DWT_LAR_KEY;//ロック解除キーの入力
        }
        else
        {
            if ((lsr & DWT_LSR_SLK_Msk) == 0)    //unlocked
                DWT->LAR = 0;
        }
    }
}
#endif /* DWT_LIB_H_ */
