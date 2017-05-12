//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <fstream.h>
#include <iostream.h>
#include <windows.h>
#include <string.h>
#include <vector>
#include <conio.h>
#include "FileClass.h"
#include "FileGroup.h"

using namespace std;
unsigned int groupnumber = 0;
void ShowFilesInGroup(FileGroup fg);
void FileAllocationAtGroups(vector<FileClass>* files, vector<FileGroup>* FileGroups);
void FindOtherFilesInGroup(vector<FileClass>* files, vector<FileGroup>* groups);
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    WIN32_FIND_DATA FindFileName;
    HANDLE hf;

    vector<String>* FileNames = new vector<String>();
    vector<FileClass>* FilesArray = new vector<FileClass>();
    vector<FileGroup>* FileGroups = new vector<FileGroup>();

    char directory_path[40] = { 0 }, files_path[40] = { 0 };
    unsigned int filecounter = 0;

    printf("Введите путь до директории: ");
    fgets(directory_path, 40, stdin);

    printf("Введите количество групп похожих файлов: ");
    scanf("%d", &groupnumber);
    
    directory_path[strlen(directory_path) - 1] = '\0';
    strcpy(files_path, directory_path);
    strcat(files_path, "\\");
    strcat(directory_path, "\\*.txt");

    hf = FindFirstFile(directory_path, &FindFileName);
    do
    {
        FileNames->push_back(FindFileName.cFileName);
        FileClass fc;
        fc.SetFileName(FileNames->operator [](filecounter));
        fc.FillWordsMassive(files_path);
        FilesArray->push_back(fc);
        fill(files_path + (strlen(files_path) - fc.GetFileName().Length()), files_path + 40, 0);
        filecounter++;
    }
    while(FindNextFile(hf, &FindFileName) != 0);
    for(unsigned int i = 0; i < FilesArray->size(); i++)
    {
        printf("%s\n", FilesArray->operator[](i).GetFileName());
        for(unsigned int j = 0; j < FilesArray->operator[](i).GetWordsMassive().size(); j++)
        {
                printf("%s", "-");
                printf("%s\n", FilesArray->operator [](i).GetWordsMassive()[j]);
        }
    }
    FileAllocationAtGroups(FilesArray, FileGroups);
    for(unsigned int k = 0; k < FileGroups->size(); k++)
    {
        ShowFilesInGroup(FileGroups->operator[](k));
    }
    printf("%s", "Нажмите любую клавишу, чтобы закрыть программу...");
    getch();
}
//---------------------------------------------------------------------------
void FileAllocationAtGroups(vector<FileClass>* files, vector<FileGroup>* groups)
{
        //Вспомогательная переменная для избегания повторов при сравнении файлов
        unsigned int shift = 0;
        for(unsigned int i = 0; i < files->size(); i++)
        {
                for(unsigned int j = 0 + shift; j < files->size(); j++)
                {
                        if(i != j)
                        {
                                FileGroup fg;
                                if(groups->size() == groupnumber)
                                {
                                        i = files->size();
                                        break;
                                }
                                fg.AddCharacteristicWords(&(files->operator[](i).GetSimilarWords(files->operator[](j))));
                                if(!fg.GetCharacteristicWords().empty())
                                {
                                        fg.SetGroupName("Группа" + IntToStr(groups->size() + 1));
                                        groups->push_back(fg);
                                }
                        }
                }
                shift++;
        }
        FindOtherFilesInGroup(files, groups);
}

void FindOtherFilesInGroup(vector<FileClass>* files, vector<FileGroup>* groups)
{
        for(unsigned int i = 0; i < groups->size(); i++)
        {
                for(unsigned int j = 0; j < files->size(); j++)
                {
                        if(groups->operator[](i).isOwnGroup(&(files->operator[](j))))
                        {
                                groups->operator[](i).AddFileInGroup(&files->operator[](j));
                        }
                }
        }
}

void ShowFilesInGroup(FileGroup fg)
{
        printf("%s\n", fg.GetGroupName() + " похожие слова: " + fg.GetCharacteristicWords()[0] + "," + fg.GetCharacteristicWords()[1] + "," + fg.GetCharacteristicWords()[2]);
        for(unsigned int i = 0; i < fg.GetFilesInGroup().size(); i++)
        {
                printf("%s", "-");
                printf("%s\n", fg.GetFilesInGroup()[i]);
        }
}
