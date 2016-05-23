//
//  parse.hpp
//  Linux_project
//
//  Created by vi on 16/3/11.
//  Copyright © 2016年 vi. All rights reserved.
//

#ifndef parse_hpp
#define parse_hpp
#include <string>
#include <vector>

#define MAX_VARIABLE 20
#define MAX_COM_VAR  256
using namespace std;


typedef struct EACH{
    char *command;
    char *variables[MAX_VARIABLE];
    int var_num;
    char *redir[MAX_VARIABLE];
    int redir_num;
    int need_redir;
    
}One_Command_Mult_Variable;

typedef struct ALL{
    One_Command_Mult_Variable data[MAX_COM_VAR];
    int command_num;
    int current_state;
    int pip_num;
    //not need
    int current_using_data;   
}All_token_info;

enum state{
    wait_cmd = 0,
    wait_argpipe = 1,
    finish = 2,
    error = 3
};

All_token_info * __Parse(char* input_data);
vector<string> __GetToken(char* data);
void init_info(All_token_info* info);
int __CHECK_IS_CMD(string command);
int __CHECK_ARGV_is_Pipes(string argv);
int __CHECK_IS_REDIR(string redir);
void free_info(All_token_info* info);

#endif /* parse_hpp */
