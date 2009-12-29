#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

static void print_element_names(xmlNode* a_node)
{
    xmlNode *cur_node = NULL;

    for(cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
        switch(cur_node->type)
        {
            case XML_ELEMENT_NODE:
                printf("node type: Element, name:%s\n", cur_node->name);
                break;
            case XML_TEXT_NODE:
                printf("type: %d, content:%s\n", cur_node->type, cur_node->content);
                break;
            default:
                printf("type: %d\n", cur_node->type);
                break;
        }
        if(cur_node->children != NULL)
        {
            printf("Step in\n");
            print_element_names(cur_node->children);
            printf("Step out\n");
        }
    }
}

int main(int argc, char **argv)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    if(argc != 2)
    {
        return 1;
    }

    doc = xmlReadFile(argv[1], NULL, 0);
    if(doc == NULL)
    {
        printf("error: could not parse file %s\n", argv[1]);
        return 1;
    }

    root_element = xmlDocGetRootElement(doc);

    print_element_names(root_element);

    xmlFreeDoc(doc);

    return 0;
}
