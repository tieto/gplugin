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

#ifndef GPLUGIN_NATIVE_PLUGIN_H
#define GPLUGIN_NATIVE_PLUGIN_H

#define GPLUGIN_TYPE_NATIVE_PLUGIN            (gplugin_plugin_get_type())
#define GPLUGIN_NATIVE_PLUGIN(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), GPLUGIN_TYPE_NATIVE_PLUGIN, GPluginNativePlugin))
#define GPLUGIN_NATIVE_PLUGIN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((obj), GPLUGIN_TYPE_NATIVE_PLUGIN, GPluginNativePluginClass))
#define GPLUGIN_IS_NATIVE_PLUGIN(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), GPLUGIN_TYPE_NATIVE_PLUGIN))
#define GPLUGIN_IS_NATIVE_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((obj), GPLUGIN_TYPE_NATIVE_PLUGIN))
#define GPLUGIN_NATIVE_PLUGIN_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), GPLUGIN_TYPE_NATIVE_PLUGIN, GPluginNativePluginClass))

typedef struct _GPluginNativePlugin           GPluginNativePlugin;
typedef struct _GPluginNativePluginClass      GPluginNativePluginClass;

#include <gplugin/gplugin-plugin.h>

#include <gmodule.h>

#define GPLUGIN_NATIVE_PLUGIN_ABI_VERSION     0x00000001

struct _GPluginNativePlugin {
	GObject parent;
};

struct _GPluginNativePluginClass {
	GObjectClass parent;

	void (*_gplugin_reserved_1)(void);
	void (*_gplugin_reserved_2)(void);
	void (*_gplugin_reserved_3)(void);
	void (*_gplugin_reserved_4)(void);
};

G_BEGIN_DECLS

GType gplugin_native_plugin_get_type(void);

gboolean gplugin_native_plugin_use(GPluginNativePlugin *plugin);
gboolean gplugin_native_plugin_unuse(GPluginNativePlugin *plugin);

GType gplugin_native_plugin_register_type(GPluginNativePlugin *plugin, GType parent, const gchar *name, const GTypeInfo *info, GTypeFlags flags);
void gplugin_native_plugin_add_interface(GPluginNativePlugin *plugin, GType instance_type, GType interface_type, const GInterfaceInfo *interface_info);
GType gplugin_native_plugin_register_enum(GPluginNativePlugin *plugin, const gchar *name, const GEnumValue *values);
GType gplugin_native_plugin_register_flags(GPluginNativePlugin *plugin, const gchar *name, const GFlagsValue *values);

GModule *gplugin_native_plugin_get_module(GPluginNativePlugin *plugin);

G_END_DECLS

#endif /* GPLUGIN_NATIVE_PLUGIN_H */
