#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
using namespace std;
bool compare_list(list<string>a,list<string>b){
    int temp = 0;
    list<string>::iterator it_a;
    list<string>::iterator it_b;
    //Iterate through both lists and return true if all tags have a match
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
//this find tags at the "," positions
list<string> gettags(string tags){
    list<string> taglist;
    int pos = tags.find(",");
    int oldpos = 0;
    do{
        //special case for the first iteration
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
//print help message
    if(option == "-h"){
        cout << "Usage:\n"
                "-h: print help message\n"
                "-q <tag>,<tag>,... : search for tags\n"
                "-q <tag,<tag>,... -q <tag>,<tag>: search for multiple tag groups\n"
                "-a <tag>,<tag>,... <content>: add content to database\n"
                "-dt <tag>,<tag>: delete tags with ALL content \n"
                "-dc <tag> <line_number>: delete specific content of tag \n"
                "-l : list all tags\n"
                "NOTE: if multiple tags are given -q and -d(dt & dc)the program will detect tags if ALL or less tags match\n"
                "e.g.      tagdb -a testtag1,testtag2 testcontent\n"
                "MATCH:    tagdb -q testtag1\n"
                "MATCH:    tagdb -q testtag1,testtag2\n"
                "NO MATCH: tagdb -q testtag1,testtag3\n";
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
        int linecount = 0;
        string pre_stags = argv[2];
        list<string> stags = gettags(pre_stags);
        list<string> ftags;
        ifstream in("database");
        string lines;

        while (getline(in, lines)){
            ftags = gettags(lines.substr(0,lines.find(" ")));
            if (compare_list(stags,ftags) ){
                cout << linecount++ << " " << lines.substr(lines.find(" ")+1,string::npos)<<"\n";
            }
        }
        in.close();
    }
    //search for multiple tagstrings
    if (option == "-q" && argc > 3){
        int linecount = 0;
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
        //here another loop is added so all the taglists are included (maybe dont try to understand, might cause headaches)
        list<list<string>>::iterator elem;
        for(elem = taglist.begin();elem != taglist.end(); ++elem){
            ifstream in("database");
            string lines;
            linecount = 0;

            while (getline(in, lines)){
                ftags = gettags(lines.substr(0,lines.find(" ")));
                if (compare_list(*elem,ftags) ){
                        cout << linecount++ << " " << lines.substr(lines.find(" ") + 1, string::npos) << "\n";
                }
            }
            cout << "___________________________\n";
        }
    }
    //delete tags
    if(option == "-dt"){
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
    //delete certain content of tags
    if(option == "-dc"){
    string p_deltags = argv[2];
    string temp = argv[3];
    int contentnb = stoi(temp);
    int counter = 0;
    list<string> ftags;
    list<string> deltags = gettags(p_deltags);
    ifstream in;
    in.open("database");
    ofstream of;
    of.open("database_temp");
    string lines;
        while (getline(in, lines)){
            ftags = gettags(lines.substr(0,lines.find(" ")));
            if (compare_list(deltags,ftags)){
                if(contentnb == counter){
                    counter ++;
                }
                else{
                counter++;
                of << lines << endl;
                }
            }
            else{
                of << lines << endl;}
        }
        of.close();
        in.close();
        remove("database");
        rename("database_temp","database");
    }
    if(option == "-l"){
    ifstream in("database");
    string lines;
    int counter = 0;
    list<string> ftags;
    list<string> finaltags;
        while (getline(in, lines)){
             finaltags.merge(gettags(lines.substr(0,lines.find(" "))));
         }
        finaltags.sort();
        finaltags.unique();
        list<string>::iterator it_a;
        for(it_a = finaltags.begin();it_a != finaltags.end(); ++it_a){
            cout << ++counter << " " << *it_a << "\n";
        }
    }
    return 0;
}