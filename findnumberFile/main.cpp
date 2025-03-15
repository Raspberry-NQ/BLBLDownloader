#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <filesystem>
#include <algorithm>
#include "windows.h"

/*
 *搜索机部分
 * 1.创建标记文件;再读取视频号文件,把文件里的aid读出来
 * 2.寻找是否有匹配的文件,写入标记文件的对应行
 * 3.换到下一行.直到遍历完成后,启动批量下载部分
 *批量下载部分
 * 1.先逐行读取标记文件,直到读到0,然后找到视频号文件对应行
 * 2.启动下载
 *
 */



namespace fs = std::filesystem;
using namespace std;
// 专用函数：检查当前可执行文件所在目录
bool check_mp4_by_number(const std::string& number_str) {
    try {
        // 获取当前可执行文件路径（Windows专用方法）
        wchar_t exe_path[MAX_PATH];
        GetModuleFileNameW(nullptr, exe_path, MAX_PATH);
        fs::path work_dir = fs::path(exe_path).parent_path();

        // 匿名函数：检测文件名是否符合要求
        auto check_filename = [&](const fs::path& file_path) {
            // 必须满足以下所有条件
            return fs::is_regular_file(file_path) &&
                   (file_path.extension() == ".mp4" ||
                    file_path.extension() == ".MP4") &&
                   (file_path.stem().string().find(number_str) != std::string::npos);
        };

        // 使用目录迭代器进行搜索
        for (const auto& entry : fs::directory_iterator(work_dir)) {
            if (check_filename(entry.path())) {
                return true;
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "文件系统异常: " << e.what() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "运行时异常: " << e.what() << '\n';
    }
    return false;
}



int generateSearchResultFile(string filename){

    string resultFileName="searchResult.txt";

    cout<<" ksks ->"<<filename<<endl;
    ifstream fin;
    ofstream fout;

    fout.open(resultFileName);
    fin.open(filename,ios::in);
    if(fin.is_open()==false){
        cout<<"****************************************************"<<endl;
        cout<<"*                   open failed                    *"<<endl;
        cout<<"****************************************************"<<endl;
        system("pause");
        return -1;
    }
    char stsign[]="st";
    char startsign[]="start";
    char stopsign[]="stop";
    char line[200]={0};
    char commend[300]={0};
    //char link[]="https://www.bilibili.com/video/BV1De411B7un";//31->B
    char oflink[50];

    char bb[]="BBDown";
    char outCommend[]=" -F<aid><videoTitle>";
    long int count=0;
    int BVlength=0;
    int videocount=-1;
    //----------------------------------------------------------------
    while(fin.getline(line,sizeof(line))){
        int t;
        if(line[0]=='s'&&line[1]=='t'){
            cout<<"st@HERE"<<endl;
            if(line[2]=='\000'){
                cout<<"-1 for quit"<<endl;
                cout<<" 0 for start"<<endl;
                cout<<">0 for count"<<endl;
                cin>>t;
                if(t==-1){
                    cout<<"-1 -> STOP @ HERE";
                    return 0;
                }
                else if(t==0){
                    cout<<"START @ HERE";
                    break;
                }
                else if(t>0){
                    videocount=t;
                    break;
                }
                else{
                    return 0;
                }
            }
            else if(line[2]==' '){
                if(line[3]=='-'){
                    cout<<"STOP @ HERE";
                    return 0;
                }
                else if(line[3]=='+'){
                    cout<<"START @ HERE";
                    break;
                }
            }
        }
        else{
            continue;
        }
    }

    //----------------------------------------------------------------
    while (fin.getline(line,sizeof(line)) && videocount!=0){
        videocount-=1;
        char *BV;
        for(int i=0;i<30;i++){
            oflink[i]=line[31+i];//
            if(line[31+i]=='\000'){
                BVlength=i;
                BV=new char[BVlength-2];
                for(;i!=1;i--){
                    BV[i-2]=oflink[i];
                }
                break;
            }
        }//oflink has get the BV num

        if(check_mp4_by_number(BV)==true){
            cout<<"视频文件： "<<oflink<<" 存在"<<endl;
            fout<<1<<" "<<oflink<<endl;
        }
        else{
            cout<<"不存在视频文件： "<<oflink<<endl;
            fout<<0<<" "<<oflink<<endl;
        }


    }

}

int fileDownload(){
    ifstream fin;
    fin.open("searchResult.txt");

    if(fin.is_open()==false){
        throw "open failed";
    }

    const string commandfront="BBDown ";
    const string commandlast=" -aria2 -F^<aid^>^<videoTitle^>";

    char BV[100];

    while(fin.getline(BV,sizeof(BV))){
        if(BV[0]=='0'){
            string command;
            command +=commandfront;
            int p=1;
            while(BV[p]!='\000'){
                command+=BV[p];
                p++;
            }
            command+=commandlast;
            cout<<command<<endl;
            char commandChar[command.length()];
            for(int i=0;i<command.length();i++){
                commandChar[i]=command[i];
            }
            system(commandChar);
        }
        else{
            continue;
        }
    }

}


int main() {
    while(1){
        int mode=-1;
        cout<<"1 检查文件"<<endl;
        cout<<"2 批量下载"<<endl;
        cin>>mode;
        if(mode==1){
            string filename;
            cout<<"输入BBDown生成的内容文件";
            cin>>filename;
            generateSearchResultFile(filename);
            cout<<"已经生成searchResult.txt"<<endl;
        }
        else if(mode ==2 ){
            fileDownload();
        }
        else{
            return 1;
        }
    }


    system("pause");
    return 0;
}

