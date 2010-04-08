#include <stdlib.h>
#include <config.h>
#include <system.h>
#include <coretypes.h>
#include <tree.h>
#include <tree-pass.h>
#include <intl.h>
#include <gcc-plugin.h>

int plugin_is_GPL_compatible;

void handle_end_of_compilation_unit(void *event_data, void *data)
{
    warning(0, G_("my gcc plugin: End of compilation unit"));
}

static bool gate_my_gcc_plugin_example(void)
{
    warning(0, G_("my gcc plugin: trigger gate_my_gcc_plugin_example"));
    return true;
}

static struct gimple_opt_pass pass_my_gcc_plugin_example=
{
    {
        GIMPLE_PASS,
        "plugin",
        gate_my_gcc_plugin_example,
        NULL,
        NULL,
        NULL,
        0,
        0,
        PROP_cfg,
        0,
        0,
        0,
        TODO_dump_func
    }
};

int plugin_init(struct plugin_name_args *pg_info, struct plugin_gcc_version *version)
{
    struct register_pass_info pass_info;
    char               *ref_pass_name = NULL;
    int                ref_instance_number = 0;
    int                i;
    int                argc = pg_info->argc;
    const char *plugin_name = pg_info->full_name;
    struct             plugin_argument *argv = pg_info->argv;
    struct plugin_info info = {"0.01", "my_gcc_plugin help should go here"};

    printf("my gcc plugin argc: %d\n", argc);

    for(i = 0; i < argc; i ++)
        printf("my gcc plugin argv %s: %s\n", argv[i].key, argv[i].value);
    
    for(i = 0; i < argc; ++ i)
        if(strcmp(argv[i].key, "ref-pass-name") == 0)
            if(argv[i].value != NULL)
            {
                ref_pass_name = argv[i].value;
            }
            else
            {
                warning(0, G_("option '-fplugin-arg-%s-ref-pass-name' requires a pass name"), plugin_name);
            }
        else if(strcmp(argv[i].key, "ref-pass-instance-num") == 0)
        {
            if(argv[i].value)
            {
                ref_instance_number = strtol(argv[i].value, NULL, 0);
            }
            else
            {
                warning(0, G_("option 'fplugin-arg-%s-ref_instance_num requires an integer value'"), plugin_name);
            }
        }
        else
        {
            warning(0, G_("plugin %qs: unrecognized argument %qs ignored"), plugin_name, argv[i].key);
        }

    if(!ref_pass_name)
    {
        error (G_("plugin %qs requires a reference pass name"), plugin_name);
    }

    pass_info.pass = &pass_my_gcc_plugin_example.pass;
    pass_info.reference_pass_name = ref_pass_name;
    pass_info.ref_pass_instance_number = ref_instance_number;
    pass_info.pos_op = PASS_POS_INSERT_AFTER;

    
//    register_callback(plugin_name, PLUGIN_INFO, NULL, (void *)&info);
    register_callback(plugin_name, PLUGIN_PASS_MANAGER_SETUP, NULL, &pass_info);
    register_callback(plugin_name, PLUGIN_FINISH_UNIT, handle_end_of_compilation_unit, NULL);
    
    return 0;
}
