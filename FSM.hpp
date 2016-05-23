//
//  FSM.hpp
//  shell
//
//  Created by vi on 16/3/13.
//  Copyright © 2016年 vi. All rights reserved.
//

#ifndef FSM_hpp
#define FSM_hpp

#include <stdio.h>
#include "parse.hpp"
int __WAIT_CMD(All_token_info *info);
void __WAIT_ARGPIPE(All_token_info *info);
int __Check_command_type(char *type);
void __Execute_Command(int type,One_Command_Mult_Variable *com_and_args,int &state);
int __Start_Process(All_token_info *info);

enum command_type {
    CD = 0,
    HISTORY =1,
    EXIT = 2,
    LOGOUT = 3,
    EXEC = 4,
    //可能不需要
    ERROR =5
};

#endif 
/* FSM_hpp */
