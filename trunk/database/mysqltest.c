#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int main()
{
    MYSQL *sql_p;
    MYSQL_RES *result_p;
    MYSQL_ROW row_p;
    int res;

    sql_p = mysql_init(NULL);
    if(sql_p == NULL)
    {
        printf("Init Error!\n");
        exit(1);
    }

    sql_p = mysql_real_connect(sql_p, "localhost", "PIRService", "PIRssap", 
                               "PID", 0, NULL, 0);
    if(!sql_p)
    {
        fprintf(stderr, "%d:%s\n", mysql_errno(sql_p), mysql_error(sql_p));
        exit(1);
    }

    res = mysql_query(sql_p, "INSERT INTO data_org (id, item) VALUES"
                      "(1,'test_string')");
    if(res)
    {
        printf("Insert Error!\n");
        mysql_close(sql_p);
        exit(1);
    }

    res = mysql_query(sql_p, "SELECT * FROM data_org");
    if(res)
    {
        printf("Select Error!\n");
        mysql_close(sql_p);
        exit(1);
    }

    result_p = mysql_use_result(sql_p);
    if(!result_p)
    {
        printf("mysql error!\n");
        mysql_close(sql_p);
        exit(1);
    }

    row_p = mysql_fetch_row(result_p);
    printf("Id=%s, Item=\"%s\"\n", row_p[0], row_p[1]);
    mysql_free_result(result_p);
    mysql_close(sql_p);
    return 0;
}
