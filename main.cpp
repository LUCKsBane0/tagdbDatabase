#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
using namespace std;
bool compare_list(list<string>a,list<string>b){
    int temp = 0;
    list<string>::iterator it_a;
    list<string>::iterator it_b;
for(it_a = a.begin();it_a != a.end(); ++it_a){
    for(it_b = b.begin();it_b != b.end(); ++it_b){
    if(*it_a == *it_b){
    temp ++;
        }
    }
}
if(a.size() == temp ){
    return true;
}
else {
    return false;}
}
list<string> gettags(string tags){
    list<string> taglist;
    int pos = tags.find(",");
    int oldpos = 0;
    do{
        string temp;
        if(oldpos == 0){
            temp = tags.substr(oldpos,pos-oldpos);
            oldpos = pos;
            taglist.push_back(temp);
        }
        else{
            pos = tags.find(",",pos+1);
            temp = tags.substr(oldpos+1, pos-oldpos-1);
            oldpos = pos;
            taglist.push_back(temp);
       }
    }
    while(pos!= string::npos);
    return taglist ;
}
int main(int argc,char**argv) {
    if(argc == 1){
        cout << "Please use -h to print help message\n";
        return 0;

    }
    string option = argv[1];

    if(option == "-h"){
        cout << "Usage:\n"
                "-h: print help message\n"
                "-q <tag>,<tag>,... : search for tags\n"
                "-q <tag,<tag>,... -q <tag>,<tag>: search for multiple tag groups\n"
                "-a <tag>,<tag>,... <content>: add content to database\n"
                "-d <tag>,<tag>,... :delete tags with content from database \n";
    }
    //add content to database
    if (option == "-a"){
        string tags = argv[2];
        ofstream file;
        file.open("database",ios_base::app);
        file << tags<< " ";
        for (int i = 3; i < argc; ++i) {
            file << argv[i]<<" ";
        }
        file << "\n";
        file.close();
    }
    //search for content in database
    if (option == "-q" && argc ==3){
        string pre_stags = argv[2];
        list<string> stags = gettags(pre_stags);
        list<string> ftags;
        ifstream in("database");
        string lines;

        while (getline(in, lines)){
            ftags = gettags(lines.substr(0,lines.find(" ")));
            if (compare_list(stags,ftags) ){
                cout << lines.substr(lines.find(" ")+1,string::npos)<<"\n";
            }
        }
        in.close();
    }
    if (option == "-q" && argc > 3){
        ostringstream ostrstr;
        string tagstring;
        string qs;
        string tags;
        list<list<string>> taglist;
        list<string> ftags;

        for (int i = 1; i <= argc; ++i) {
            ostrstr << argv[i]<< " ";

        }
        tagstring = ostrstr.str();
        istringstream istrstr (tagstring);
        string tags_old;
        while (istrstr){
            istrstr >> qs >> tags;
            if (tags_old == tags){
                continue;
            }
            taglist.push_back(gettags(tags));
            tags_old = tags;
        }
        list<list<string>>::iterator elem;
        for(elem = taglist.begin();elem != taglist.end(); ++elem){
            ifstream in("database");
            string lines;

            while (getline(in, lines)){
                ftags = gettags(lines.substr(0,lines.find(" ")));
                if (compare_list(*elem,ftags) ){
                        cout << lines.substr(lines.find(" ") + 1, string::npos) << "\n";
                }
            }
        }
    }
    if(option == "-d"){
    string p_deltags = argv[2];
    list<string> deltags = gettags(p_deltags);
    list<string> ftags;
    ifstream in;
    in.open("database");
    ofstream of;
    of.open("database_temp");
    string lines;
        while (getline(in, lines)){
            ftags = gettags(lines.substr(0,lines.find(" ")));
            if (compare_list(deltags,ftags) ){
            }
            else{
            of << lines << endl;}
        }
        of.close();
        in.close();
        remove("database");
        rename("database_temp","database");
    }

    return 0;
}