#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sys/types.h>
#include <regex.h>


const unsigned char *NODE_NAME[] = {"Max_data_number", "Max_data_length", 
                                    "Max_cache_size", "Max_Buffer_length",
                                    "Max_B_array_size", "Max_L_structure_size",
                                    "Max_W_structure_size", "Max_gamma_tree_size"};
const unsigned char *SUBNODE_NAME[] = {"Description", "Value"};
const unsigned char *ROOTNODE_NAME = "Configuration";
const int NODE_AMT = 8;
const int SUBNODE_AMT = 2;
const char *NUM_PATTERN = "[0-9]\\+";

static int retrieve_cfg_value(xmlNode *node, unsigned long long *value);

static int retrieve_cfg_value(xmlNode *node, unsigned long long *value)
{
    xmlNode *cur_node = NULL;
    char *str, *str1;
    unsigned long long ans;
    regex_t regex;
    regmatch_t pmatch[1];
    int ret;
    int contentlen;
    int numlen;

    ans = 0;
    cur_node = node;
    while(cur_node != NULL && 
          strcmp(cur_node->name, SUBNODE_NAME[1])!= 0)
    {
        cur_node = cur_node->next;
    }

    if(cur_node == NULL || 
       cur_node->children == NULL)
    {
        return 1;
    }

    cur_node = cur_node->children;
    if(cur_node->type != XML_TEXT_NODE)
    {
        return 1;
    }
    
    contentlen = xmlStrlen(cur_node->content); 
    str = (unsigned char *)malloc((contentlen+ 1) * sizeof(unsigned char));
    memset(str, 0, contentlen + 1);
    memcpy(str, cur_node->content, contentlen);

    regcomp(&regex, NUM_PATTERN, 0);
    ret = regexec(&regex, str, 1, pmatch, 0);
    if(ret != 0)
    {
        free(str);
        regfree(&regex);
        return 1;
    }
    
    numlen = pmatch[0].rm_eo - pmatch[0].rm_so + 1;
    str1 = (unsigned char *)malloc((numlen + 1) * sizeof(unsigned char));
    memset(str1, 0, (numlen + 1));
    memcpy(str1, str + pmatch[0].rm_so, numlen);

    ans = (unsigned long long)atoll((char *)str1);
    *value = ans;
   
    free(str);
    free(str1);
    regfree(&regex);
    return 0;
}

static int retrieve_configure(xmlNode *a_node)
{
    xmlNode *cur_node = NULL;
    int i;
    int ret;
    unsigned long long value;

    for(cur_node = a_node; cur_node; cur_node = cur_node->next)
    { 
        switch(cur_node->type)
        {
            case XML_ELEMENT_NODE:
                for(i = 0; i < NODE_AMT; i ++)
                    if(!strcmp(cur_node->name, NODE_NAME[i]))
                        break;
                
                if(i >= NODE_AMT)
                    break;

                ret = retrieve_cfg_value(cur_node->children, &value);
                if(ret != 0)
                {
                    return 1;
                }

                printf("%s: %llu\n", NODE_NAME[i], value);

                break;
            default:
                break;
        }
    }
}

int main(int argc, char **argv)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    int ret;

    if(argc != 2)
    {
        return 1;
    }

    doc = xmlReadFile(argv[1], NULL, 0);
    if(doc == NULL)
    {
        printf("error: Invalid Configuration File %s\n", argv[1]);
        return 1;
    }

    root_element = xmlDocGetRootElement(doc);
    if(strcmp(root_element->name,ROOTNODE_NAME) != 0)
    {
        printf("Invalid Configuration!\n");
        return 1;
    }

    ret = retrieve_configure(root_element->children);
    if(ret != 0)
    {
        printf("Fail to retrieve the configuration!\n");
    }
    xmlFreeDoc(doc);

    return 0;
}
