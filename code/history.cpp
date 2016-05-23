//
//  history.cpp
//  shell
//
//  Created by vi on 16/3/14.
//  Copyright © 2016年 vi. All rights reserved.
//

#include "history.hpp"
#include <string>
#include <vector>
std::vector<std::string> history_data;

void __Stroe_history(char *h){
    std::string temp = "";
    temp = temp + h;
    history_data.push_back(temp);
}

void __Printf_History(){
    for(int i=0;i<history_data.size();i++){
        printf("%d : %s",i+1,history_data[i].c_str());
    }
}

void __Clear_History(){
    // history_data.clear();
}