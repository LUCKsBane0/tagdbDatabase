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
    
    tagdb -d <tag>
    
### BUILD
Right now you will have to compile by yourself, but I will add a makefile soon.
* First compile the c++ file with:

        g++ -o tagdb tagdb.cpp
* Then move the binary file to the folder you want to store your database in

        cd tagdbDatabase
        mv tagdb <preferred_folder_path>
* Execute the binary in the preferred folder

        cd <preferred_folder_path>
        ./tagdb
### Add to $PATH
* Execute the provided shellscript (it will edit the .bashrc file in your home directory)
        
        sh inject_path.sh
* Now you can access tagdb in the shell directly
        
        tagdb <args>
