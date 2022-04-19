# tagdb database
## Little tag-Database for the terminal
### Usage
Print help message:

    tagdb -h
    
Add tag to database:
 
    tagdb -a <tag> <content>

Search for tags in database:

    tagdb -q <tag> -q <tag>
    
Delete tag with ALL content:
    
    tagdb -dt <tag>
Delete certain content of tag:

    tagdb -dc <tag> <content_line_number>
List all tags without content (WIP!):

    tagdb -l 
#### NOTE

If multiple tags are given to -q and -d(dt & dc)the program will detect tags if ALL or less tags match.

    EXAMPLE:  tagdb -a testtag1,testtag2 testcontent
    MATCH:    tagdb -q testtag1
    MATCH:    tagdb -q testtag1,testtag2
    NO MATCH: tagdb -q testtag1,testtag3
### BUILD
Right now you will have to compile by yourself, but I will add a makefile soon.
* First compile the c++ file with:

        cd tagdbDatabase
        g++ -o tagdb tagdb.cpp
* Then move the binary file to the folder you want to store your database in

        mv tagdb <preferred_folder_path>
* Execute the binary in the preferred folder

        cd <preferred_folder_path>
        ./tagdb
### Add to $PATH
* Execute the provided shellscript (it will edit the .bashrc file in your home directory)
        
        sh inject_path.sh
* Now you can access tagdb in the shell directly
        
        tagdb <args>
