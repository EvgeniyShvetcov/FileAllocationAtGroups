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


//Проверка принадлежности к группе по ключевым словам
bool FileGroup::isOwnGroup(FileClass* fc)
{
        unsigned int comparedwordscount = 0;
        for(unsigned int i = 0; i < fc->GetWordsMassive().size(); i++)
        {
                for(unsigned int j = 0; j < _characteristicWords.size(); j++)
                {
                        if(_characteristicWords[j].AnsiPos(fc->GetWordsMassive()[i]) > 0)
                        {
                                comparedwordscount++;
                        }
                }
        }
        //Если в файле есть ключевые слова группы, то он ей принадлежит
        if(comparedwordscount == _characteristicWords.size())
        {
                return true;
        }
        return false;
}

FileGroup::~FileGroup()
{
        if((!_characteristicWords.empty()) && (!_FilesInGroup.empty()))
        {
                _characteristicWords.clear();
                _FilesInGroup.clear();
        }
}
 