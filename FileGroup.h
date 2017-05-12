//---------------------------------------------------------------------------

#ifndef FileGroupH
#define FileGroupH

class FileGroup
{
private:
        String _groupname;
        //Характерные для группы слова
        vector<String> _characteristicWords;
        vector<FileClass> _FilesInGroup;
public:

        FileGroup();

        void SetGroupName(String name);
        void AddCharacteristicWords(String cwords);
        void AddCharacteristicWords(vector<String>* words);
        void AddFileInGroup(FileClass* fc);

        vector<String> GetCharacteristicWords(){return _characteristicWords;}
        vector<FileClass> GetFilesInGroup(){return _FilesInGroup;}
        String GetGroupName(){return _groupname;}
        bool isOwnGroup(FileClass* fc);


        ~FileGroup();

};
//---------------------------------------------------------------------------
#endif
 