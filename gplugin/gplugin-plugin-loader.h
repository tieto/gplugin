/*
 * Copyright (C) 2011 Gary Kramlich <grim@reaperworld.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#if !defined(GPLUGIN_H_INSIDE) && !defined(GPLUGIN_COMPILATION)
#error "only <gplugin.h> may be included directly"
#endif

#ifndef GPLUGIN_PLUGIN_LOADER_H
#define GPLUGIN_PLUGIN_LOADER_H

#define GPLUGIN_TYPE_PLUGIN_LOADER           (gplugin_plugin_loader_get_type())
#define GPLUGIN_PLUGIN_LOADER(obj)           (G_TYPE_CHECK_INSTANCE_CAST((obj), GPLUGIN_TYPE_PLUGIN_LOADER, GPluginPluginLoader))
#define GPLUGIN_IS_PLUGIN_LOADER(obj)        (G_TYPE_CHECK_INSTANCE_TYPE((obj), GPLUGIN_TYPE_PLUGIN_LOADER))
#define GPLUGIN_PLUGIN_LOADER_GET_IFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE((obj), GPLUGIN_TYPE_PLUGIN_LOADER, GPluginPluginLoaderIface))

typedef struct _GPluginPluginLoader          GPluginPluginLoader;
typedef struct _GPluginPluginLoaderIface     GPluginPluginLoaderIface;

#include <glib.h>
#include <glib-object.h>

#include <gplugin/gplugin-plugin.h>

struct _GPluginPluginLoaderIface {
	GTypeInterface gparent;

	GList *(*supported_extensions)(GPluginPluginLoader *loader);

	GPluginPluginInfo *(*query)(GPluginPluginLoader *loader, const gchar *filename, GError **error);

	GPluginPlugin *(*load)(GPluginPluginLoader *loader, const gchar *filename, GError **error);
	gboolean (*unload)(GPluginPluginLoader *loader, GPluginPlugin *plugin, GError **error);

	void (*_gplugin_reserved_1)(void);
	void (*_gplugin_reserved_2)(void);
	void (*_gplugin_reserved_3)(void);
	void (*_gplugin_reserved_4)(void);
};

G_BEGIN_DECLS

GType gplugin_plugin_loader_get_type(void);

GList *gplugin_plugin_loader_get_supported_extensions(GPluginPluginLoader *loader);

GPluginPluginInfo *gplugin_plugin_loader_query_plugin(GPluginPluginLoader *loader, const gchar *filename, GError **error);

GPluginPlugin *gplugin_plugin_loader_load_plugin(GPluginPluginLoader *loader, const gchar *filename, GError **error);
gboolean gplugin_plugin_loader_unload_plugin(GPluginPluginLoader *loader, GPluginPlugin *plugin, GError **error);

G_END_DECLS

#endif /* GPLUGIN_PLUGIN_LOADER_H */

