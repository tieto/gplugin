# vi:et:ts=4 sw=4 sts=4

from gi.repository import GPlugin

def gplugin_plugin_query():
    return GPlugin.PluginInfo(
        id='gplugin-python/basic-plugin',
        version='1.2.3',
        name='holy shit this is from python!!',
        summary='this first python gplugin plugin',
    )

def gplugin_plugin_load(plugin):
    print('loading')

    return True


def gplugin_plugin_unload(plugin):
    print('unloading')

    return True

