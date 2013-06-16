/*
 * Copyright (C) 2011-2013 Gary Kramlich <grim@reaperworld.com>
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

#include "gplugin-python-plugin.h"

/* _POSIX_C_SOURCE get's redefined in Python.h so we undef it to avoid the
 * compiler warning...
 */
#undef _POSIX_C_SOURCE
#include <pygobject.h>
#include <Python.h>

#define GPLUGIN_PYTHON_PLUGIN_GET_PRIVATE(obj) \
	(G_TYPE_INSTANCE_GET_PRIVATE((obj), GPLUGIN_TYPE_PLUGIN, GPluginPythonPluginPrivate))

/******************************************************************************
 * Typedefs
 *****************************************************************************/
typedef struct {
	PyObject *module;
} GPluginPythonPluginPrivate;

/******************************************************************************
 * Enums
 *****************************************************************************/
enum {
	PROP_ZERO,
	PROP_MODULE,
	PROP_LAST,
};

/******************************************************************************
 * Globals
 *****************************************************************************/
static GObjectClass *parent_class = NULL;
static GType type = G_TYPE_INVALID;

/******************************************************************************
 * Private Stuff
 *****************************************************************************/
static PyObject *
gplugin_python_plugin_get_module(const GPluginPythonPlugin *plugin) {
	GPluginPythonPluginPrivate *priv = NULL;

	g_return_val_if_fail(GPLUGIN_IS_PYTHON_PLUGIN(plugin), NULL);

	priv = GPLUGIN_PYTHON_PLUGIN_GET_PRIVATE(plugin);

	return priv->module;
}

static void
gplugin_python_plugin_set_module(GPluginPythonPlugin *plugin,
                                 PyObject *module)
{
	GPluginPythonPluginPrivate *priv = NULL;

	g_return_if_fail(GPLUGIN_IS_PLUGIN(plugin));
	g_return_if_fail(module);

	priv = GPLUGIN_PYTHON_PLUGIN_GET_PRIVATE(plugin);

	if(priv->module)
		Py_DECREF(priv->module);

	priv->module = module;

	if(priv->module)
		Py_INCREF(priv->module);

	g_object_notify(G_OBJECT(plugin), "module");
}

/******************************************************************************
 * Object Stuff
 *****************************************************************************/
static void
gplugin_python_plugin_get_property(GObject *obj, guint param_id, GValue *value,
                                   GParamSpec *pspec)
{
	GPluginPythonPlugin *plugin = GPLUGIN_PYTHON_PLUGIN(obj);

	switch(param_id) {
		case PROP_MODULE:
			g_value_set_pointer(value,
			                    gplugin_python_plugin_get_module(plugin));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, param_id, pspec);
			break;
	}
}

static void
gplugin_python_plugin_set_property(GObject *obj, guint param_id,
                                   const GValue *value, GParamSpec *pspec)
{
	GPluginPythonPlugin *plugin = GPLUGIN_PYTHON_PLUGIN(obj);

	switch(param_id) {
		case PROP_MODULE:
			gplugin_python_plugin_set_module(plugin,
			                                 g_value_get_pointer(value));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, param_id, pspec);
			break;
	}
}

static void
gplugin_python_plugin_finalize(GObject *obj) {
	GPluginPythonPluginPrivate *priv =
		GPLUGIN_PYTHON_PLUGIN_GET_PRIVATE(obj);

	if(priv->module)
		Py_DECREF(priv->module);

	G_OBJECT_CLASS(parent_class)->finalize(obj);
}

static void
gplugin_python_plugin_class_init(GPluginPythonPluginClass *klass) {
	GObjectClass *obj_class = G_OBJECT_CLASS(klass);

	parent_class = g_type_class_peek_parent(klass);

	g_type_class_add_private(klass, sizeof(GPluginPythonPluginPrivate));

	obj_class->get_property = gplugin_python_plugin_get_property;
	obj_class->set_property = gplugin_python_plugin_set_property;
	obj_class->finalize = gplugin_python_plugin_finalize;

	g_object_class_install_property(obj_class, PROP_MODULE,
		g_param_spec_pointer("module", "module",
		                     "The python module object",
		                     G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
}

/******************************************************************************
 * API
 *****************************************************************************/
void
gplugin_python_plugin_register(GPluginNativePlugin *plugin) {
	if(G_UNLIKELY(type == 0)) {
		static const GTypeInfo info = {
			.class_size = sizeof(GPluginPythonPluginClass),
			.class_init = (GClassInitFunc)gplugin_python_plugin_class_init,
			.instance_size = sizeof(GPluginPythonPlugin),
		};

		type = gplugin_native_plugin_register_type(plugin,
		                                           GPLUGIN_TYPE_PLUGIN,
		                                           "GPluginPythonPlugin",
		                                           &info,
		                                           0);
	}
}

GType
gplugin_python_plugin_get_type(void) {
	if(G_UNLIKELY(type == 0)) {
		g_warning("gplugin_python_plugin_get_type was called before "
		          "the type was registered!\n");
	}

	return type;
}
