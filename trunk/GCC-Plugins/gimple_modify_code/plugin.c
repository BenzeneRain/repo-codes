#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "config/i386/i386.h"
#include "tree.h"
#include "basic-block.h"
#include "tree-dump.h"
#include "tree-pass.h"
#include "gimple.h"
#include "tree-flow.h"
#include "tree-pass.h"
#include "tree-iterator.h"
#include "langhooks.h"
#include "toplev.h"
#include "intl.h"
#include "gcc-plugin.h"

int plugin_is_GPL_compatible;

static int yes = 0;

static void
my_dump_gimple(gimple gnode, gimple_stmt_iterator *ptrgsi)
{
    int gcode;
    tree tnode;
    tree funcdecl;
    tree desc_node;
    tree ptr_desc_node;
    tree t;
    tree tmp_var;
    tree const_char_restrict_ptr_type_node;
    gimple tmp_gstmt;
    gimple new_gnode;
    const char *hellocstr = "Hello, GCC!\n";
    int i;
    struct c_binding *b;
    expanded_location xloc;

    /*
     * Extract the Gimple Code from a gimple node
     */

    gcode = gimple_code(gnode);

    /*
     * Get the line number of cooresponding 
     * source code from a gimple node
     */
    if(gimple_has_location(gnode))
    {
        xloc = expand_location(gimple_location(gnode));
        printf("line %d:", xloc.line);
    }
    printf("\t\t\t\t%s\n", gimple_code_name[gcode]);
    
    switch(gcode)
    {
        case GIMPLE_ASSIGN:
            /*
             * Add a printf("Hello, GCC!\n"); statement 
             * after the first appearing assignment
             * if yes equals to 1, then we have already
             * added the statement, and no need to add 
             * again
             */
            if(!yes)
            {
                /*
                 * Since printf is a builtin function, we need
                 * to get the function declaration using 
                 * built_in_decls[]. The index number can be
                 * found in gcc source gcc/builtins.def
                 */
                funcdecl = built_in_decls[BUILT_IN_PRINTF];

                if(funcdecl == NULL_TREE)
                {
                    printf("cannot find printf\n");
                }
                else
                {
                    /*
                     * In gimple, every statement is simplified into 
                     * three oprands mode. And our printf() statement 
                     * is change into following two gimple statements:
                     * 
                     * <D.XXX> = (const char * restrict) &"Hello, GCC!\n"[0]
                     * printf(<D.XXX>);
                     *
                     * Note that <D.XXX> is a temporary variable, we can 
                     * actually use any name we like as long as no 
                     * confliction.
                     */

                    /*
                     * Generate a STRING_CST, the value is "Hello, GCC!\n"
                     */
                    desc_node = build_string(strlen(hellocstr), hellocstr);

                    /*
                     * Two points need to notice here:
                     * 1. STRING_CST build by build_string() do
                     *    not have TREE_TYPE set, so we need to 
                     *    set it manually.
                     * 2. build_string() will add a trailing '\0'
                     *    when building the STRING_CST, so we do
                     *    not need to care with it.
                     */
                    TREE_TYPE(desc_node) = build_array_type(
                            char_type_node, 
                            build_index_type(
                                build_int_cst(NULL_TREE, 
                                    strlen(hellocstr))));

                    /*
                     * Define a const char * restrict type node
                     * here for convertion.
                     * I'm not sure why we need to add a restrict
                     * attribute, but GCC really does it when it 
                     * converting a STRING_CST from AST to Gimple.
                     */
                    const_char_restrict_ptr_type_node = 
                        build_qualified_type(
                            build_pointer_type(
                                    build_qualified_type(
                                        char_type_node,
                                        TYPE_QUAL_CONST)),
                            TYPE_QUAL_RESTRICT);

                    /*
                     * When we in AST, if we want to use STRING_CST
                     * the form is like this <ADDR_EXPR<STRING_CST>>,
                     * but when we turn to gimple, it is like this
                     * <ADDR_EXPR<ADDAR_REF<STRING_CST>>>.
                     * So we need to do a convertion there.
                     */

                    /*
                     * First wrap STRING_CST with ARRAY_REF
                     */
                    t = build4(ARRAY_REF, char_type_node, 
                            desc_node, build_int_cst(NULL_TREE, 0), 
                            NULL, NULL);

                    /*
                     * Second wrap ARRAY_REF with ADDR_EXPR
                     */
                    ptr_desc_node = build1(ADDR_EXPR, 
                            const_char_restrict_ptr_type_node,
                            t);

                    /*
                     * I'm not sure why we need to use fold_convert()
                     * here, but if we do not, we cannot make the 
                     * compiling successful.
                     */
                    ptr_desc_node = fold_convert(
                            const_char_restrict_ptr_type_node, 
                            ptr_desc_node);

                    /*
                     * If is_gimple_min_invariant(ptr_desc_node)
                     * is true, we build a corrent argument, otherwise
                     * the argument is not suitable for gimple call
                     */
                    if(!is_gimple_min_invariant(ptr_desc_node))
                    {
                        printf("Something wrong with is_gimple_min_invariant\n");
                        return ;
                    }

                    /*
                     * This applies for a temporary variable
                     */
                    tmp_var = make_rename_temp(
                            const_char_restrict_ptr_type_node,
                            "plugin_var");

                    /*
                     * Build a gimple statement. Still remember that?
                     * <D.XXX> = (const char * restrict) "Hello, GCC!\n"
                     */
                    tmp_gstmt = gimple_build_assign(tmp_var, 
                                                    ptr_desc_node);

                    /*
                     * Check if the gimple statment is corrent
                     */
                    if(!is_gimple_assign(tmp_gstmt))
                    {
                        printf("tmp_gstmt is invalid\n");
                    }

                    printf("Insert gimple statment:");
                    print_gimple_stmt(stdout, tmp_gstmt, 0,
                                TDF_DETAILS | TDF_VERBOSE | TDF_TREE);
                    /*
                     * Insert the gimple statment into the basic block
                     */
                    gsi_insert_after(ptrgsi, tmp_gstmt, 
                            GSI_NEW_STMT);

                    if(is_gimple_operand(tmp_var))
                    {

                        printf("begin to insert printf\n");
                        yes = 1;
                        printf("Insert gimple statment:");
                        /*
                         * Insert the gimple statment printf 
                         * into the basic block
                         */
                        new_gnode = gimple_build_call(
                                funcdecl, 1, tmp_var);
                        print_gimple_stmt(stdout, new_gnode, 0, 0);
                        gsi_insert_after(ptrgsi, new_gnode, 
                                GSI_NEW_STMT); 
                    }
                    else
                    {
                        print_generic_stmt(stdout, ptr_desc_node, 
                                TDF_DETAILS | TDF_VERBOSE | TDF_TREE);
                        printf("Not Gimple Operands\n");
                    }

                    /*
                     * Since we have more than one consecutive statements 
                     * to insert, we can actually use build a gimple 
                     * sequence, insert all statement into the sequence, 
                     * and then insert the sequence into the basic block. 
                     * This seems to be a better method.
                     */
                }
            }
            else
            {
            }
            break;
        default:
            break;
    }
}

static unsigned int
stage1_handler(void)
{
    basic_block bb;
    gimple_stmt_iterator gsi;
    gimple g;
    const char *dname, *aname;
    
    /*
     * Print the filename and function name we are current
     * dealing with.
     */
    if(current_function_decl)
    {
        dname = lang_hooks.decl_printable_name(current_function_decl, 2);
        aname = (IDENTIFIER_POINTER(DECL_ASSEMBLER_NAME(current_function_decl)));
        printf("\n;; Filename %s, Function %s (%s)\n\n", dump_base_name, dname, aname);
    }

    /*
     * Traverse all the basic blocks in this translation unit.
     */
    FOR_EACH_BB(bb)
    {
        /*
         * Print the basic block index
         */
        printf("<Basic Block %d>\n", bb->index);
        /*
         * Traverse the gimple statements in the basic block
         * sequentially.
         */
        for(gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
        {
           g = gsi_stmt(gsi); 
           my_dump_gimple(g, &gsi);
           printf("\n");
        }
    }

    return 0;
}

struct gimple_opt_pass stage1_pass =
{
    {
        GIMPLE_PASS,
        "sem-stage1-mix",
        NULL,
        stage1_handler,
        NULL,
        NULL,
        0,
        0,
        PROP_gimple_any | PROP_cfg,
        0,
        0,
        0,
        TODO_verify_stmts | TODO_dump_func
    }
};


int
plugin_init(struct plugin_name_args *plugin_info,
            struct plugin_gcc_version *version)
{
    const char *plugin_name = plugin_info->full_name;
    struct register_pass_info rp_info;

    rp_info.pass = &stage1_pass.pass;
    rp_info.pos_op = PASS_POS_INSERT_AFTER;
    rp_info.ref_pass_instance_number = 0;
    rp_info.reference_pass_name = "cfg";
   
    register_callback(plugin_name, PLUGIN_PASS_MANAGER_SETUP, 0, &rp_info);
    

    return 0;
}
