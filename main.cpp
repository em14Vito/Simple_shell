//
//  main.cpp
//  shell
//
//  Created by vi on 16/3/11.
//  Copyright © 2016年 vi. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

//#include "parse.hpp"
#include "FSM.hpp"
#include "history.hpp"
#include "buildin_command.hpp"
int  main(){
    char a[256];
    char buf[256];
    getcwd(buf,sizeof(buf));
    printf("Start\n%s@vito>>>",buf);
    int p = getpid();
    while(1){
        fgets(a, 256, stdin);
        __Stroe_history(a);
        All_token_info* all=(All_token_info*)malloc(sizeof(All_token_info));
        all =  __Parse(a);
        __Start_Process(all);
        if(all == NULL){
            getcwd(buf,sizeof(buf));
            printf("%s@vito>>>",buf);
            continue;           
        }
        if(all->current_state == TRUE){
            getcwd(buf,sizeof(buf));
            printf("%s@vito>>>",buf);
        }
        else if(all->current_state == FALSE){
            free_info(all);
            __Clear_History();
            break;
        }
    }
    printf("Bye Bye\n");
    wait(NULL);
    kill(p,SIGKILL);
    return 0;
}

