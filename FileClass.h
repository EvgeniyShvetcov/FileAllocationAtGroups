//---------------------------------------------------------------------------

#ifndef FileClassH
#define FileClassH
//---------------------------------------------------------------------------
class FileClass
{
private:
        String _filename;
        vector<String> _words;
public:
        FileClass();

        void SetFileName(String filename);
        void SetWordsMassive(vector<String>* words);
        void FillWordsMassive(char* filepath);

        String GetFileName(){return _filename;}
        vector<String> GetWordsMassive(){return _words;}
        vector<String> GetSimilarWords(FileClass fc);

        ~FileClass();
};

#endif
