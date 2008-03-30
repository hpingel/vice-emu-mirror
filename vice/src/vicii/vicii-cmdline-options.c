/*
 * vicii-cmdline-options.c - Command-line options for the MOS 6569 (VIC-II)
 * emulation.
 *
 * Written by
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  Andreas Boose <viceteam@t-online.de>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 * */

#include "vice.h"

#include <stdio.h>

#include "cmdline.h"
#include "raster-cmdline-options.h"
#ifdef HAS_TRANSLATION
#include "translate.h"
#endif
#include "vicii-cmdline-options.h"
#include "viciitypes.h"


/* VIC-II command-line options.  */
#ifdef HAS_TRANSLATION
static const cmdline_option_trans_t cmdline_options[] =
{
    { "-VICIIchecksb", SET_RESOURCE, 0, NULL, NULL, "VICIICheckSbColl",
      (void *)1, 0, IDCLS_ENABLE_SPRITE_BACKGROUND },
    { "+VICIIchecksb", SET_RESOURCE, 0, NULL, NULL, "VICIICheckSbColl",
      (void *)0, 0, IDCLS_DISABLE_SPRITE_BACKGROUND },
    { "-VICIIcheckss", SET_RESOURCE, 0, NULL, NULL, "VICIICheckSsColl",
      (void *)1, 0, IDCLS_ENABLE_SPRITE_SPRITE },
    { "+VICIIcheckss", SET_RESOURCE, 0, NULL, NULL, "VICIICheckSsColl",
      (void *)0, 0, IDCLS_DISABLE_SPRITE_SPRITE },
    { "-newluminance", SET_RESOURCE, 0, NULL, NULL, "VICIINewLuminances",
      (void *)1, 0, IDCLS_USE_NEW_LUMINANCES },
    { "+newluminance", SET_RESOURCE, 0, NULL, NULL, "VICIINewLuminances",
      (void *)0, 0, IDCLS_USE_OLD_LUMINANCES },
    { "-saturation", SET_RESOURCE, 1, NULL, NULL, "ColorSaturation", NULL,
      IDCLS_P_0_2000, IDCLS_SET_SATURATION },
    { "-contrast", SET_RESOURCE, 1, NULL, NULL, "ColorContrast", NULL,
      IDCLS_P_0_2000, IDCLS_SET_CONTRAST },
    { "-brightness", SET_RESOURCE, 1, NULL, NULL, "ColorBrightness", NULL,
      IDCLS_P_0_2000, IDCLS_SET_BRIGHTNESS },
    { "-gamma", SET_RESOURCE, 1, NULL, NULL, "ColorGamma", NULL,
      IDCLS_P_0_2000, IDCLS_SET_GAMMA },
    { NULL }
};
#else
static const cmdline_option_t cmdline_options[] =
{
    { "-VICIIchecksb", SET_RESOURCE, 0, NULL, NULL, "VICIICheckSbColl",
      (void *)1, NULL, "Enable sprite-background collision registers" },
    { "+VICIIchecksb", SET_RESOURCE, 0, NULL, NULL, "VICIICheckSbColl",
      (void *)0, NULL, "Disable sprite-background collision registers" },
    { "-VICIIcheckss", SET_RESOURCE, 0, NULL, NULL, "VICIICheckSsColl",
      (void *)1, NULL, "Enable sprite-sprite collision registers" },
    { "+VICIIcheckss", SET_RESOURCE, 0, NULL, NULL, "VICIICheckSsColl",
      (void *)0, NULL, "Disable sprite-sprite collision registers" },
    { "-newluminance", SET_RESOURCE, 0, NULL, NULL, "VICIINewLuminances",
      (void *)1, NULL, "Use new luminances" },
    { "+newluminance", SET_RESOURCE, 0, NULL, NULL, "VICIINewLuminances",
      (void *)0, NULL, "Use old luminances" },
    { "-saturation", SET_RESOURCE, 1, NULL, NULL, "ColorSaturation", NULL,
      "<0-2000>", "Set saturation of internal calculated palette [1000]" },
    { "-contrast", SET_RESOURCE, 1, NULL, NULL, "ColorContrast", NULL,
      "<0-2000>", "Set contrast of internal calculated palette [1100]" },
    { "-brightness", SET_RESOURCE, 1, NULL, NULL, "ColorBrightness", NULL,
      "<0-2000>", "Set brightness of internal calculated palette [1100]" },
    { "-gamma", SET_RESOURCE, 1, NULL, NULL, "ColorGamma", NULL,
      "<0-2000>", "Set gamma of internal calculated palette [900]" },
    { NULL }
};
#endif

int vicii_cmdline_options_init(void)
{
    if (raster_cmdline_options_chip_init("VICII", vicii.video_chip_cap) < 0)
        return -1;

#ifdef HAS_TRANSLATION
    return cmdline_register_options_trans(cmdline_options);
#else
    return cmdline_register_options(cmdline_options);
#endif
}

