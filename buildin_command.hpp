	//
//  buildin_command.hpp
//  shell
//
//  Created by vi on 16/3/13.
//  Copyright © 2016年 vi. All rights reserved.
//

#ifndef buildin_command_hpp
#define buildin_command_hpp

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parse.hpp"

//mode_t fd_mode =S_IRWXG | S_IRWXU | S_IRWXO;
//int append = O_RDWR | O_APPEND | O_CREAT ;   //读写方式打开，内容往尾部添加 >>
//int over_write =  O_RDWR | O_TRUNC | O_CREAT ;//读写方式打开，内容往尾部添加 >


enum TRUE_OR_FALUSE{
    TRUE = 1,
    FALSE = 0
};

void __Exit(One_Command_Mult_Variable *each,int &state);
void __Cd(One_Command_Mult_Variable *each,int &state);
void __Logout(One_Command_Mult_Variable *each,int &state);
void __History(One_Command_Mult_Variable *each,int &state);
void __Exec(One_Command_Mult_Variable *each,int &state);
void __Do_redir(One_Command_Mult_Variable *each);
void __Reset_redir(One_Command_Mult_Variable * each);


#endif /* buildin_command_hpp */
