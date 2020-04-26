## explorer

###### yet another php based web file explorer

git history for explorer was completely lost at some point of time as well as proper version of dependencies 

#### TECHNOLOGIES

explorer were built with:

-   php5.6
-   flight

#### OPERATION LIST

-   void set : string path - set given path, should be existed directory
-   void step : string name - step into given directory name, name should be scalar and should be existed directory
-   void forward : void - forward to previous path, should have previous path
-   void back : void - back to previous path, should have previous path
-   void father : void - step into parent directory, should be not root directory
-   void root : void - set current path to root directory
-   void open : string name, string id - open file with given name and set connection given id, name should be scalar file should exists and id should be unique
-   void save : string name, string data - save file with given name and given data, name should be scalar file should exists
-   void create_file : string name - create new file or overrite old with given name, name should be scalar
-   void create_directory : string name - create new directory or overrite old with given name, name should be scalar
-   void rename : string from, string to - rename file or directory from given name to new given name, from should be scalar and to should be scalar
-   void delete : string[] names - delete files or directories with given names, names should be
-   void move : string[] names - move files or directories with given names, names should be
-   void copy : string[] names - copy files or directories with given names, names should be
-   void paste : void - paste copied or moved files or directories into current directory
-   void find : string pattern - find all files and directories that match pattern, pattern should be valid regular expression
-   void sort : string field - sort all files and directories by given field, field should be either name or mimetype or timestamp or size
-   void show : void - show all files and directories in current directory call natively

##### UNMAINTAINED

#### LICENSE

explorer is [MIT licensed](LICENSE)
