#include <stdlib.h>
#include <stdio.h>
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

static void
print_tab(int number)
{
    int i;
    for (i = 0; i < number; i ++)
        printf("    ");
}

static void
my_dump_node(tree node, int level)
{
    int code;
    tree_stmt_iterator tsi;
    call_expr_arg_iterator ceai;
    tree tmp_node;
    
    if(node == NULL_TREE)
    {
        return;
    }

    code = (int) TREE_CODE(node);
    switch(code)
    {
        case IDENTIFIER_NODE:
            print_tab(level);
            printf("Identifier node: %s\n", IDENTIFIER_POINTER(node));
            break;
        case FUNCTION_DECL:
            print_tab(level);
            printf("Function declare: %s\n", IDENTIFIER_POINTER(DECL_NAME(node)));
            my_dump_node(DECL_SAVED_TREE(node), level + 1);
            break;
        case BIND_EXPR:
            print_tab(level);
            printf("Inside a block\n");
            my_dump_node(BIND_EXPR_BODY(node), level + 1);
            break;
        case STATEMENT_LIST:
            for(tsi = tsi_start(node); !tsi_end_p(tsi); tsi_next(&tsi))
            {
               my_dump_node(tsi_stmt(tsi), level + 1); 
            }
            break;
        case DECL_EXPR:
            //printf("%s:%d:\n", EXPR_FILENAME(node), EXPR_LINENO(node));
            my_dump_node(DECL_EXPR_DECL(node), level);
            break;
        case RESULT_DECL:
            print_tab(level);
            printf("<retval>\n");
            break;
        case VAR_DECL:
            print_tab(level);
            /*
            printf("Declare variable: %s %s\n",
                    IDENTIFIER_POINTER(DECL_NAME(TYPE_NAME((TREE_TYPE(node))))), 
                    IDENTIFIER_POINTER(DECL_NAME(node)));
            */
            if(DECL_NAME(node))
                printf("variable: %s\n", IDENTIFIER_POINTER(DECL_NAME(node)));
            else if(TREE_CODE(node) == CONST_DECL)
            {
                printf("constant: C.%u\n", DECL_UID(node));
            }
            else
            {
                printf("variable: D.%u\n", DECL_UID(node));
            }
            break;
        case MODIFY_EXPR:
          //  printf("%s:%d:\n", EXPR_FILENAME(node), EXPR_LINENO(node));
            print_tab(level);
            printf("Assignment:\n");
            print_tab(level + 1);
            printf("Left-hand side:\n");
            my_dump_node(TREE_OPERAND(node, 0), level + 2);
            print_tab(level + 1);
            printf("Right-hand side:\n");
            my_dump_node(TREE_OPERAND(node, 1), level + 2);
            break;
        case INTEGER_CST:
            print_tab(level);
            printf("Integer constant "); 
            if(TREE_INT_CST_HIGH(node) == 0)
            {
                printf(HOST_WIDE_INT_PRINT_UNSIGNED, TREE_INT_CST_LOW(node));
            }
            else if(TREE_INT_CST_HIGH(node) == -1 && TREE_INT_CST_LOW(node) != 0)
            {
                printf("-" HOST_WIDE_INT_PRINT_UNSIGNED, TREE_INT_CST_LOW(node));
            }
            else
            {
                printf(HOST_WIDE_INT_PRINT_DOUBLE_HEX, 
                       TREE_INT_CST_HIGH(node), TREE_INT_CST_LOW(node));
            }
            printf("\n");
            break;
        case STRING_CST:
            print_tab(level);
            printf("String constant %s\n", TREE_STRING_POINTER(node));
            break;
        case LABEL_EXPR:
            tmp_node = LABEL_EXPR_LABEL(node);
            printf("%s:%d:\n", EXPR_FILENAME(node), EXPR_LINENO(node));
            print_tab(level);
            if(DECL_NAME(tmp_node) != NULL)
            {
                printf("Label %s", IDENTIFIER_POINTER(DECL_NAME(tmp_node)));
            }
            else if(LABEL_DECL_UID(tmp_node) != -1)
            {
                printf("Label L.%d", LABEL_DECL_UID(tmp_node));
            }
            else if(DECL_UID(tmp_node) != -1)
            {
                printf("Label D.%d", DECL_UID(tmp_node));
            }
            else
            {
                printf("Unknown label");
            }
            printf("\n");
            break;
        case GOTO_EXPR:
            tmp_node = GOTO_DESTINATION(node);
            printf("%s:%d:\n", EXPR_FILENAME(node), EXPR_LINENO(node));
            print_tab(level);
            if(DECL_NAME(tmp_node) != NULL)
            {
                printf("Goto %s", IDENTIFIER_POINTER(DECL_NAME(tmp_node)));
            }
            else if(LABEL_DECL_UID(tmp_node) != -1)
            {
                printf("Goto L.%d", LABEL_DECL_UID(tmp_node));
            }
            else if(DECL_UID(tmp_node) != -1)
            {
                printf("Goto label D.%d", DECL_UID(tmp_node));
            }
            else
            {
                printf("Goto unknown place");
            }
            printf("\n");
            break;
        case LE_EXPR:
        case LT_EXPR:
        case GT_EXPR:
        case GE_EXPR:
        case EQ_EXPR:
        case NE_EXPR:
        case PLUS_EXPR:
        case MINUS_EXPR:
        case MULT_EXPR:
            print_tab(level);
            printf("Binary Expression:\n");
            print_tab(level + 1);
            printf("Operator:\n");
            print_tab(level + 2);
            printf("%s\n", tree_code_name[(int)TREE_CODE(node)]);
            print_tab(level + 1);
            printf("Operand 1:\n");
            my_dump_node(TREE_OPERAND(node, 0), level + 2);
            print_tab(level + 1);
            printf("Operand 2:\n");
            my_dump_node(TREE_OPERAND(node, 1), level + 2);
            break;
        case PREDECREMENT_EXPR:
        case PREINCREMENT_EXPR:
        case POSTDECREMENT_EXPR:
        case POSTINCREMENT_EXPR:
            printf("%s:%d:\n", EXPR_FILENAME(node), EXPR_LINENO(node));
            print_tab(level);
            printf("Unary Expression:\n");
            print_tab(level + 1);
            printf("Operator:\n");
            print_tab(level + 2);
            printf("%s\n", tree_code_name[(int)TREE_CODE(node)]);
            print_tab(level + 1);
            printf("Operand:\n");
            my_dump_node(TREE_OPERAND(node, 0), level + 2);
            break;
        case RETURN_EXPR:
            printf("%s:%d:\n", EXPR_FILENAME(node), EXPR_LINENO(node));
            print_tab(level);
            printf("Return value:\n");
            if(TREE_OPERAND(node, 0) != NULL)
            {
                my_dump_node(TREE_OPERAND(node, 0), level + 1);
            }
            else
            {
                print_tab(level + 1);
                printf("NULL\n");
            }
            break;
        case COND_EXPR:
            printf("%s:%d:\n", EXPR_FILENAME(node), EXPR_LINENO(node));
            print_tab(level);
            printf("Condition Expression:\n");
            print_tab(level + 1);
            printf("Condition:\n");
            my_dump_node(TREE_OPERAND(node, 0), level + 2);
            print_tab(level + 1);
            printf("True:\n");
            my_dump_node(TREE_OPERAND(node, 1), level + 2);
            print_tab(level + 1);
            printf("False:\n");
            my_dump_node(TREE_OPERAND(node, 2), level + 2);
            break;
        case CALL_EXPR:
            printf("%s:%d:\n", EXPR_FILENAME(node), EXPR_LINENO(node));
            print_tab(level);
//            printf("Call %s:\n", tree_code_name[(int)TREE_CODE(CALL_EXPR_FN(node))]);
            printf("Call:\n");
            print_tab(level + 1);
            printf("Destination:\n");
            my_dump_node(CALL_EXPR_FN(node), level + 2);
            print_tab(level + 1);
            printf("Arguments:\n");
            FOR_EACH_CALL_EXPR_ARG(tmp_node, ceai, node)
            {
                my_dump_node(tmp_node, level + 2);
            }
            break;
        case ADDR_EXPR:
        case NOP_EXPR:
            my_dump_node(TREE_OPERAND(node, 0), level);
            break;
        default:
            print_tab(level);
            printf("Unable to solve this node yet, node type is %s\n", tree_code_name[code]);
            break;
    }
}

static void
handle_dump_basic_block(void *gcc_data, void *user_data)
{
    fprintf(stderr, "Enter handle_dump_basic()\n");
    if(gcc_data != NULL)
    //browse_tree((tree)(gcc_data));
    //print_generic_stmt(stderr, (tree)gcc_data, 0);
    //debug_tree((tree)gcc_data);
    //dump_node((tree)gcc_data, TDF_BLOCKS | TDF_VOPS | TDF_LINENO | TDF_VERBOSE, stderr);
    my_dump_node((tree)gcc_data, 0);
    printf("\n\n");
}

static void
my_dump_gimple(gimple gnode)
{
    int gcode;
    tree tnode;
    expanded_location xloc;

    gcode = gimple_code(gnode);
    if(gimple_has_location(gnode))
    {
        xloc = expand_location(gimple_location(gnode));
        printf("line %d:", xloc.line);
    }
    printf("\t\t\t\t%s\n", gimple_code_name[gcode]);
    
    switch(gcode)
    {
        case GIMPLE_ASSIGN:
            tnode = gimple_assign_lhs(gnode);
            my_dump_node(tnode, 0);
            printf(" = ");
            if(gimple_num_ops(gnode) == 3)
            {
                tnode = gimple_assign_rhs1(gnode);
                my_dump_node(tnode, 0);
                printf("%s\n", tree_code_name[gimple_assign_rhs_code(gnode)]);
                tnode = gimple_assign_rhs2(gnode);
                my_dump_node(tnode, 0);
            }
            else if(gimple_num_ops(gnode) == 2)
            {
                tnode = gimple_assign_rhs1(gnode);
                my_dump_node(tnode, 0);
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
    
    if(current_function_decl)
    {
        dname = lang_hooks.decl_printable_name(current_function_decl, 2);
        aname = (IDENTIFIER_POINTER(DECL_ASSEMBLER_NAME(current_function_decl)));
        printf("\n;; Filename %s, Function %s (%s)\n\n", dump_base_name, dname, aname);
    }

    FOR_EACH_BB(bb)
    {
        printf("<Basic Block %d>\n", bb->index);
        for(gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
        {
           g = gsi_stmt(gsi); 
           my_dump_gimple(g);
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
