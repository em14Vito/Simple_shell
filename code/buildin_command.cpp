//
//  buildin_command.cpp
//  shell
//
//  Created by vi on 16/3/13.
//  Copyright © 2016年 vi. All rights reserved.
//

#include "buildin_command.hpp"
#include "history.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
void __Exec(One_Command_Mult_Variable *each,int &state){

    int fd3;

    if(each->redir[0] != NULL){
        //overwrite
        if(strcmp(each->redir[0],">") == 0){
            fd3 = open(each->redir[1],O_RDWR | O_CREAT | O_CREAT,S_IRWXG | S_IRWXU | S_IRWXO);
            dup2(fd3,STDOUT_FILENO);
        }
        //append   
        else if(strcmp(each->redir[0],">>") == 0){
            fd3 = open(each->redir[1],O_RDWR | O_APPEND | O_CREAT | O_CREAT,S_IRWXG | S_IRWXU | S_IRWXO);
            dup2(fd3,STDOUT_FILENO);
        }
        close(fd3);
    }
    
    execvp(each->command,each->variables);
    fprintf(stderr,"%s: command not found\n",each->command);
    exit(-1);
}
void __Cd(One_Command_Mult_Variable *each,int &state){
    //it would appear error if there is no arguments at the back of cd
    if(strcmp(each->command,"cd") == 0){
        if (each->var_num == 1) {
            printf("Error. Without argument after cd\n");
        }
        else{
            chdir(each->variables[1]);
        }
    }
    
}
void __Logout(One_Command_Mult_Variable *each,int &state){
    state = FALSE;

}
void __History(One_Command_Mult_Variable *each,int &state){
    __Printf_History();
    exit(1);
}



void __Exit(One_Command_Mult_Variable *each,int &state){
    state = FALSE;
}


void __Do_redir(One_Command_Mult_Variable *each){
    // // printf("do_red\n");
    // for(int i = 0; i < each->var_num;i++){
    //     //直接覆盖文件写入
    //     if( strcmp(each->redir[0] ,">") == 0){
    //         // 参数
    //         // if( (each->var_num - i) > 1 )
    //         printf("重定向是%s 和 %s\n",each->redir[0],each->redir[1]);


    //             int fd3 = open(each->redir[1],O_RDWR | O_APPEND | O_CREAT | O_CREAT,S_IRWXG | S_IRWXU | S_IRWXO);

    //             dup2(fd3,STDOUT_FILENO);
                

    //     }
         
    //     //往后面添加   
    //     if( strcmp(each->variables[i],">>") == 0){
            
    //     }
    //     if( strcmp(each->variables[i],"<<") == 0){
            
    //     }
    //     if( strcmp(each->variables[i],"<") == 0){
            
    //     }
    // }
    // return;
}
 void __Reset_redir(One_Command_Mult_Variable * each){

 }


