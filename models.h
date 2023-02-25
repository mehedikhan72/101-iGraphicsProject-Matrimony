#ifndef MODELS_H
#define MODELS_H

struct PersonalData
{
    int pk; // unique field to retrieve data.
    char username[64]; // this field will be used to distinguish every user.
    char name[128];
    int age;
    char gender[6];
    char religion[24];
    char location[128];
    char education[256];
    char occupation[128];
    int net_worth; // in bdt.
    char about[1000];
};

struct FamilyData
{
    char fathers_name[128];
    char mothers_name[128];
    char fathers_occupation[128];
    char mothers_occupation[128];
};

#endif 
