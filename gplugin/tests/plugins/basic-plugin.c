/*
 * Copyright (C) 2011-2014 Gary Kramlich <grim@reaperworld.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include <gplugin.h>
#include <gplugin-native.h>

G_MODULE_EXPORT GPluginPluginInfo *
gplugin_query(GPLUGIN_UNUSED GError **error) {
	const gchar * const authors[] = {
		"author1",
		NULL
	};

	return gplugin_plugin_info_new(
		"gplugin/native-basic-plugin",
		0x01020304,
		"name", "basic plugin",
		"category", "test",
		"version", "version",
		"summary", "summary",
		"license-id", "license",
		"description", "description",
		"authors", authors,
		"website", "website",
		NULL
	);
}

G_MODULE_EXPORT gboolean
gplugin_load(GPLUGIN_UNUSED GPluginNativePlugin *plugin,
             GPLUGIN_UNUSED GError **error)
{
	return TRUE;
}

G_MODULE_EXPORT gboolean
gplugin_unload(GPLUGIN_UNUSED GPluginNativePlugin *plugin,
               GPLUGIN_UNUSED GError **error)
{
	return TRUE;
}

