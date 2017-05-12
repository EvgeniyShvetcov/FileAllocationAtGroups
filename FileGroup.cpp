//---------------------------------------------------------------------------


#pragma hdrstop

#include "Main.cpp"
#include "FileGroup.h"
#include "FileClass.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
FileGroup::FileGroup()
{
}

void FileGroup::SetGroupName(String name)
{
        _groupname = name;
}

void FileGroup::AddCharacteristicWords(String word)
{
        _characteristicWords.push_back(word);
}

void FileGroup::AddCharacteristicWords(vector<String>* word)
{
        if(!word->empty())
        {
                for(unsigned int i = 0; i < word->size(); i++)
                {
                        _characteristicWords.push_back(word->operator[](i));
                }
        }
}

void FileGroup::AddFileInGroup(FileClass* fc)
{
        _FilesInGroup.push_back(*fc);
}


bool FileGroup::IsOwnGroup(FileClass* fc)
{
        unsigned int comparedwordscount = 0;
        for(unsigned int i = 0; i < fc->GetWordsArray().size(); i++)
        {
                for(unsigned int j = 0; j < _characteristicWords.size(); j++)
                {
                        if(_characteristicWords[j].AnsiPos(fc->GetWordsArray()[i]) > 0)
                        {
                                comparedwordscount++;
                        }
                }
        }
        if(comparedwordscount == _characteristicWords.size())
        {
                return true;
        }
        return false;
}

String FileGroup::GetCharacteristicWordsInOneRow()
{
        String allwords;
        for(unsigned int i = 0; i < _characteristicWords.size(); i++)
        {
                if(i != _characteristicWords.size() - 1)
                {
                        allwords = allwords + _characteristicWords[i] + ",";
                }
                else
                {
                        allwords = allwords + _characteristicWords[i];
                }
        }
        return Utf8ToAnsi(allwords);
}

FileGroup::~FileGroup()
{
        if((!_characteristicWords.empty()) && (!_FilesInGroup.empty()))
        {
                _characteristicWords.clear();
                _FilesInGroup.clear();
        }
}
 