//
//  FSM.cpp
//  shell
//
//  Created by vi on 16/3/13.
//  Copyright © 2016年 vi. All rights reserved.
//

#include "FSM.hpp"
#include "buildin_command.hpp"

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
// int child,parent;
void exit_child(int a){
// printf("child is %d and it is %d\n",child,getpid());
    if(a != 0)  kill(a,SIGABRT);
}


//only two pipe
int __Start_Process(All_token_info *info){
    
    if(info == NULL){
        return 1;
    }
    int com_num = info->command_num;
    int pip = info->pip_num;
    int type,state =TRUE;
    signal(SIGINT,exit_child);
    
        if(pip == 0){
            int child = fork();
            One_Command_Mult_Variable *each = &info->data[com_num-1];
            
            if(child == 0){
                type = __Check_command_type(info->data[com_num-1].command);
                state = TRUE;
                __Execute_Command(type,each,state);
            }
                
            waitpid(child,NULL,0);
            if(strcmp(each->command,"cd") == 0 )__Cd(each,state);

            if(state == FALSE){
                info->current_state = FALSE;
            }
            
        }
        else if(pip == 1){
            //if there are two command:
            if(info->data[1].var_num == 0) {
                printf("Wrong, you need two commands\n");
                return 1;
            }
            int pid[2];
            int pipe_fd[2];
            /* Create the pipe */
            if (pipe(pipe_fd) < 0)
            {   
                perror ("pipe failed");
                exit (errno);
            }

            /* Create a process space for the ls */
            if ((pid[0]=fork()) < 0)
            {
                perror ("Fork failed");
                exit(errno);
            }  
            //child process
            if (pid[0] == 0)
            {
                /*
                * Set stdout to pipe
                */
                close (pipe_fd[0]);
                dup2 (pipe_fd[1], 1);
                close (pipe_fd[1]);
                
                /* Execute the command */
                One_Command_Mult_Variable *each = &info->data[com_num-2];
                type = __Check_command_type(info->data[com_num-2].command);
                __Execute_Command(type,each,info->current_state);
                
                printf("Wrong\n");
                
            }
            wait(NULL);
            //parents，
            if (pid[0])
            {
                /* We're in the parent */
                /* Create a process space for the more */

                if ((pid[1]=fork()) < 0)
                {
                    perror ("Fork failed");
                    exit(errno);
                }

                if (!pid[1])
                {
                    
                    
                    /* We're in the child */
                    /* Set stdin to pipe */
                    close (pipe_fd[1]);
                    dup2 (pipe_fd[0], 0);
                    close (pipe_fd[0]);

                    /* Execute the command parents */
                    One_Command_Mult_Variable *each = &info->data[com_num-1];
                    //check command type;
                    type = __Check_command_type(info->data[com_num-1].command);
                    __Execute_Command(type,each,info->current_state);
                    printf("Wrong\n");
                    
                    
                }
                if(pid[1]){
                /* This is the parent */
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);
                    waitpid (pid[1], NULL, 0);
                    kill(pid[0],SIGKILL);
                }

            }
        }
    
    return 1;
}
//int __Start_Process(All_token_info *info){
//
//    if(info == NULL){
//        info->current_state = finish;
//        return TRUE;
//    }
//
//    int com_num = info->command_num;
//    int type,state =TRUE;
//    signal(SIGINT,exit_child);
//    for(int i = 0; i< com_num; i++){
//
//        child = fork();
//        if(child == 0){
//            One_Command_Mult_Variable *each = &info->data[i];
//            //check command type;
////                    cout <<"start" <<each->command<< each->var_num << endl;
//            type = __Check_command_type(info->data[i].command);
//            state = TRUE;
//            __Execute_Command(type,each,state);
//            
//            if(state == FALSE){
//                info->current_state = FALSE;
////
//            }
//        }
//        wait(NULL);
//        if(state == FALSE){
//            break;
//        }
//    }
//    return 1;
//}
int __Check_command_type(char *type){


    if(strcmp(type, "cd") == 0){
        return CD;
    }
    else if(strcmp(type, "history") ==0){
        return HISTORY;
    }
    else if (strcmp(type,"exit") ==0){
        return EXIT;
    }
    else if (strcmp(type, "logout") ==0){
        return LOGOUT;
    }
    return EXEC;
    
}

//state is use to check whether it is somethings wrong in execute. 
void __Execute_Command(int type,One_Command_Mult_Variable *com_and_args,int &state){
    // __Do_redir(info->data[com_num-1]);
    // __Do_redir(com_and_args);
    if(type == EXIT){
        __Exit(com_and_args,state);
    }
    else if(type == HISTORY){
        __History(com_and_args,state);
    }
    else if(type == LOGOUT){
        __Logout(com_and_args,state);
    }
    else if (type == CD){
        // __Cd(com_and_args,state);
        exit(1);
    }
    else if(type == EXEC){
        __Exec(com_and_args,state);
    }


}
