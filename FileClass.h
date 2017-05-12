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
        void SetWordsArray(vector<String>* words);
        void FillWordsArray(char* filepath);

        String GetFileName(){return _filename;}
        vector<String> GetWordsArray(){return _words;}
        vector<String> GetSimilarWords(FileClass fc);

        ~FileClass();
};

#endif
