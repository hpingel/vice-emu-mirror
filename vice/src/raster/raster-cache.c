/*
 * raster-cache.c - Simple cache for the raster-based video chip emulation
 * helper.
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

#include <string.h>

#include "lib.h"
#include "raster-cache.h"


void raster_cache_init(raster_cache_t *cache, unsigned int num_sprites)
{
    unsigned int i;

    if (num_sprites > 0) {
        for (i = 0; i < RASTER_CACHE_MAX_SPRITES; i++)
            raster_sprite_cache_init(&(cache->sprites[i]));

        cache->gfx_msk = lib_calloc(1, RASTER_CACHE_GFX_MSK_SIZE);
    }

    memset(cache->background_data, 0, RASTER_CACHE_MAX_TEXTCOLS);
    memset(cache->foreground_data, 0, RASTER_CACHE_MAX_TEXTCOLS);
    memset(cache->color_data_1, 0, RASTER_CACHE_MAX_TEXTCOLS);
    memset(cache->color_data_2, 0, RASTER_CACHE_MAX_TEXTCOLS);
    memset(cache->color_data_3, 0, RASTER_CACHE_MAX_TEXTCOLS);

    cache->is_dirty = 1;
}

