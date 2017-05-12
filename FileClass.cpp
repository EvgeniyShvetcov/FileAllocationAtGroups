//---------------------------------------------------------------------------


#pragma hdrstop
#include "Main.cpp"
#include "FileClass.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
FileClass::FileClass()
{
        _filename = 0;
}

void FileClass::SetFileName(String filename)
{
        _filename = filename;
}

void FileClass::SetWordsArray(vector<String>* words)
{
        for(unsigned int i = 0; i < words->size(); i++)
        {
                _words.push_back(words->operator [](i));
        }
        words->clear();
        words = 0;
}

void FileClass::FillWordsArray(char* filepath)
{
        FILE * file = NULL;
        char str[255] = {0};
        file = fopen(strcat(filepath, _filename.c_str()), "r+");
        if(file == NULL) throw 1;
        while(fgets(str, 255, file) != NULL)
        {
                String infowords;
                unsigned int i = 0;
                do
                {
                        infowords += str[i];
                        if(str[i] == ' ')
                        {
                                _words.push_back(infowords);
                                infowords = "";
                        }
                        if(str[i + 1] == '\0')
                        {
                                _words.push_back(infowords);
                        }
                        i++;
                }
                while(str[i] != '\0');
        }
   fclose(file);
   delete[] str;
}

vector<String> FileClass::GetSimilarWords(FileClass fc)
{
        vector<String> comparedWords;
        for(unsigned int i = 0; i < _words.size(); i++)
        {
                for(unsigned int j = 0; j < fc.GetWordsArray().size(); j++)
                {
                        if(_words[i].AnsiPos(fc.GetWordsArray()[j]) > 0)
                        {
                                comparedWords.push_back(_words[i]);
                        }
                }
        }
        return comparedWords;
}

FileClass::~FileClass()
{
if(!_words.empty())
        _words.clear();
}
