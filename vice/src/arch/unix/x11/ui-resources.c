/*
 * ui-resources.c
 *
 * Written by
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  Andr� Fachat <fachat@physik.tu-chemnitz.de>
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
 *
 */

#include "vice.h"

#include <stdio.h>

#include "lib.h"
#include "resources.h"
#include "utils.h"


struct ui_resources_s {
    char *html_browser_command;
    int use_private_colormap;
    int save_resources_on_exit;
    int depth;
};
typedef struct ui_resources_s ui_resources_t;

static ui_resources_t ui_resources;

static unsigned int ui_resources_initialized = 0;


/* Warning: This cannot actually be changed at runtime.  */
static int set_depth(resource_value_t v, void *param)
{
    int d = (int)v;

    /* Minimal sanity check.  */
    if (d < 0 || d > 32)
        return -1;

    ui_resources.depth = d;
    return 0;
}

static int set_html_browser_command(resource_value_t v, void *param)
{
    util_string_set(&ui_resources.html_browser_command, (char *)v);
    return 0;
}

static int set_use_private_colormap(resource_value_t v, void *param)
{
    ui_resources.use_private_colormap = (int)v;
    return 0;
}

static int set_save_resources_on_exit(resource_value_t v, void *param)
{
    ui_resources.save_resources_on_exit = (int)v;
    return 0;
}

static const resource_t resources[] = {
    { "HTMLBrowserCommand", RES_STRING, (resource_value_t)"netscape %s",
      (void *)&ui_resources.html_browser_command,
      set_html_browser_command, NULL },
    { "PrivateColormap", RES_INTEGER, (resource_value_t)0,
      (void *)&ui_resources.use_private_colormap,
      set_use_private_colormap, NULL },
    { "SaveResourcesOnExit", RES_INTEGER, (resource_value_t)0,
      (void *)&ui_resources.save_resources_on_exit,
      set_save_resources_on_exit, NULL },
    { "DisplayDepth", RES_INTEGER, (resource_value_t)0,
      (void *)&ui_resources.depth,
      set_depth, NULL },
    { NULL }
};

int ui_resources_init(void)
{
    ui_resources_initialized = 1;
    return resources_register(resources);
}

void ui_resources_shutdown(void)
{
    if (ui_resources_initialized)
        lib_free(ui_resources.html_browser_command);
}

