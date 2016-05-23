//
//  parse.cpp
//  Linux_project
//
//  Created by vi on 16/3/11.
//  Copyright © 2016年 vi. All rights reserved.
//

#include "parse.hpp"
//#include "buildin_command.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <iostream>
using namespace std;




//when symbol '|' appear,info->command would add 1,if command which is corresponding is null, error
//eg: [ cat | cat ] √; [ cat | ] x,
All_token_info * __Parse(char* input_data){
    //whether there are some data in here
    if (input_data[0] == '\n' || input_data[0] == '\0')
        return NULL;
    //get all token and removal redundant space
    vector<string> ALL = __GetToken(input_data);
    All_token_info* info=(All_token_info*)malloc(sizeof(All_token_info));;

    init_info(info);
    int index;
    int arg_num=0;
    //check all token and save them in info
    for(index=0; index<ALL.size(); index++){
        //check command
        if( __CHECK_IS_CMD(ALL[index]) ){
            //first one is command
            info->command_num = info->command_num + 1;
            //put command into info. need to malloc info's char* first
            info->data[info->command_num-1].command =
            (char*)malloc( ALL[index].size() *sizeof(char*) );
            strcpy(info->data[info->command_num-1].command, ALL[index].c_str());
            info->data[info->command_num-1].variables[arg_num] =
            (char*)malloc( ALL[index].size() *sizeof(char*) );
            strcpy(info->data[info->command_num-1].variables[arg_num], ALL[index].c_str());
            arg_num++;
            info->data[info->command_num-1].var_num = arg_num;
            //check arguments
            for(index++;index<ALL.size(); index++){
                //if it is redirect
                if( __CHECK_IS_REDIR(ALL[index])){
                  //no redirect symbol
                    if(index+1 < ALL.size()){
                        //put redirect argument into info. need to malloc info's char* first
                        info->data[info->command_num-1].redir[0] =
                        (char*)malloc( ALL[index].size() *sizeof(char*) );
                        strcpy(info->data[info->command_num-1].redir[0],ALL[index].c_str() );
                        info->data[info->command_num-1].redir[1] =
                        (char*)malloc( ALL[index+1].size() *sizeof(char*) );
                        strcpy(info->data[info->command_num-1].redir[1],ALL[index+1].c_str() );
                        info->data[info->command_num-1].redir_num+= 2;
                        index++;
                        continue;
                    }
                    //no argument in the end, report error and exit
                    else{
                        info->data[info->command_num-1].redir_num+= 1;
                        index = (int)ALL.size();    //use exit loop
                        printf("Wrong. No argument after redir.\n");
                        free_info(info);
                        break;
                        
                    }   
                }
                //if it is arguemnts
                else if( !__CHECK_ARGV_is_Pipes(ALL[index]) ){
                    //put arguments into info. need to malloc info's char* first
                    info->data[info->command_num-1].variables[arg_num] = (char*)malloc( ALL[index].size() *sizeof(char*) );
                    strcpy(info->data[info->command_num-1].variables[arg_num], ALL[index].c_str());
                    arg_num++;
                }
                //no argument or redirect, it is pipes '|'
                else{

                    //jump this symbol '|'。
                    info->data[info->command_num-1].var_num = arg_num;
                    arg_num = 0;
                    info->pip_num++;
                    break;
                }
                info->data[info->command_num-1].var_num = arg_num;
            }
        }

    else{
            //error,no command;
        }
    }
    return info;
}


vector<string> __GetToken(char* input_data){
    int begin,end;
    string token;
    string data = "";
    data = data + input_data;
    vector<string> ALL_CMD_ARG;
    
    //get first command
    while(1){
        //removal '\0'
        if(data.rfind("\n") != string::npos){
            data.erase( data.rfind("\n",data.size()-1) );
        }
        //begin 代表token的头，end代表截取到哪个位
        begin =(int) data.find_first_not_of(' ');
        //solve string end with space
        if(begin == string::npos)
            break;
        
        data.erase(0,begin);
        end =(int) data.find(' ');
        
        if (end != string::npos){
            token = data.substr(0,end);
            ALL_CMD_ARG.push_back(token);
            data.erase(0,end);
        }
        else{
            ALL_CMD_ARG.push_back(data);
            break;
        }
    }
    return ALL_CMD_ARG;
    

}

void init_info(All_token_info* info){
    info->current_using_data = 0;
    info->command_num = 0;
    info->current_state = 1;
    info->pip_num = 0;
    for(int i =0; i< MAX_COM_VAR; i++){
        info->data[i].need_redir = 0;
        info->data[i].var_num = 0;
        info->data[i].redir_num = 0;
        info->data[i].command=NULL;
        info->data[i].variables[0] = NULL;
        info->data[i].redir[0] = NULL;
    }
}

int __CHECK_IS_CMD(string command){
    int correct = 1;        //0  false;  1  true;
    if( !isalpha(command[0]) ){
        //first string is not command
        if((command[0] == '.' && command[1] == '/') | command.find('/')){
            correct = 1;
        }
        else{
            correct = 0;
        }
    }
    return correct;
}


int __CHECK_ARGV_is_Pipes(string argv){
    int correct = 0;        //0 is not "|";1 is "|"
    if(argv == "|"){
        correct = 1;
    }
    return correct;
}

void free_info(All_token_info* info){
    if(info == NULL)    return;
    for(int i= 0;i< info->command_num;i++){
        free(info->data[i].command);
        for(int j = 0; j < info->data[i].var_num;j++){
            free(info->data[i].variables[j]);
            free(info->data[i].redir[j]);
        }
        for(int j = 0; j < info->data[i].redir_num;j++){
            free(info->data[i].redir[j]);
        }
    }
    free(info);
    return;
}

int __CHECK_IS_REDIR(string redir){
    int correct = 0;
    if(redir == ">" || redir == ">>"){
        correct = 1;
    }
    return correct;
}
