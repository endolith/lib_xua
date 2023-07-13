// Copyright 2011-2023 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#ifndef _CLOCKING_H_
#define _CLOCKING_H_

#include <xs1.h>
#include "xua.h"

interface pll_ref_if
{
    void toggle();
    void init();
    void toggle_timed(int relative);
};

[[distributable]]
void PllRefPinTask(server interface pll_ref_if i_pll_ref, out port p_sync);

/** Clock generation and digital audio I/O handling.
 *
 *  \param c_spdif_rx channel connected to S/PDIF receive thread
 *  \param c_adat_rx channel connect to ADAT receive thread
 *  \param i_pll_ref interface to taslk that outputs clock signal to drive external frequency synthesizer
 *  \param c_audio channel connected to the audio() thread
 *  \param c_clk_ctl channel connected to Endpoint0() for configuration of the
 *                   clock
 *  \param c_clk_int channel connected to the decouple() thread for clock
                     interrupts
 */
void clockGen(streaming chanend ?c_spdif_rx, chanend ?c_adat_rx, client interface pll_ref_if i_pll_ref, chanend c_audio, chanend c_clk_ctl, chanend c_clk_int);

#if (XUA_USE_APP_PLL)
struct PllSettings
{
    // Count we expect on MCLK port timer at SW PLL check point.
    // Note, we expect wrapping so this is essentiually a modulus
    unsigned adder;
    unsigned fracIdx;
    int firstUpdate;
};

void AppPllEnable(tileref tile, int mclkFreq_hz);
void AppPllGetSettings(int clkFreq_hz, struct PllSettings &pllSettings);
void AppPllUpdate(tileref tile, unsigned short mclk_pt, struct PllSettings &pllSettings);
#endif
#endif

