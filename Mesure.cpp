#include "Mesure.h"
#include <iostream>
using namespace std;


int Mesure::valeurToIndiceO3()const{
    int i=0;
    if(O3<=29 && O3>=0){
        i=1;
    }else if(O3<=54 && O3>=30){
        i=2;
    }else if(O3<=79 && O3>=55){
        i= 3;
    }else if(O3<=104 && O3>=80){
        i= 4;
    }else if(O3<=129 && O3>=105){
        i= 5;
    }else if(O3<=149 && O3>=130){
        i= 6;
    }else if(O3<=179 && O3>=150){
        i= 7;
    }else if(O3<=209 && O3>=180){
        i= 8;
    }else if(O3<=239 && O3>=210){
        i= 9;
    }else if(O3>=240){
        i= 10;
    }
    return i;
    
}
int Mesure::valeurToIndiceSO2()const{
    int i=0;
    if(SO2<39 && SO2>0){
        i=1;
    }else if(SO2<=79 && SO2>=40){
        i=2;
    }else if(SO2<=119 && SO2>=80){
        i= 3;
    }else if(SO2<=159 && SO2>=120){
        i= 4;
    }else if(SO2<=199 && SO2>=160){
        i= 5;
    }else if(SO2<=249 && SO2>=200){
        i= 6;
    }else if(SO2<=299 && SO2>=250){
        i= 7;
    }else if(SO2<=399 && SO2>=300){
        i= 8;
    }else if(SO2<=499 && SO2>=400){
        i= 9;
    }else if(SO2>=500){
        i= 10;
    }
    return i;
}
int Mesure::valeurToIndiceNO2()const{
    int i=0;
    if(NO2<29 && NO2>0){
        i=1;
    }else if(NO2<=54 && NO2>=30){
        i=2;
    }else if(NO2<=84 && NO2>=55){
        i= 3;
    }else if(NO2<=109 && NO2>=85){
        i= 4;
    }else if(NO2<=134 && NO2>=110){
        i= 5;
    }else if(NO2<=164 && NO2>=135){
        i= 6;
    }else if(NO2<=199 && NO2>=165){
        i= 7;
    }else if(NO2<=274 && NO2>=200){
        i= 8;
    }else if(NO2<=399 && NO2>=275){
        i= 9;
    }else if(NO2>=400){
        i= 10;
    }
    return i;
}


int Mesure::valeurToIndicePM10()const{
    int i=0;
    if(PM10<6 && PM10>0){
        i=1;
    }else if(PM10<=13 && PM10>=7){
        i=2;
    }else if(PM10<=20 && PM10>=14){
        i= 3;
    }else if(PM10<=27 && PM10>=21){
        i= 4;
    }else if(PM10<=24 && PM10>=28){
        i= 5;
    }else if(PM10<=41 && PM10>=35){
        i= 6;
    }else if(PM10<=49 && PM10>=42){
        i= 7;
    }else if(PM10<=64 && PM10>=50){
        i= 8;
    }else if(PM10<=79 && PM10>=65){
        i= 9;
    }else if(PM10>=80){
        i= 10;
    }
    return i;
}


float Mesure::calculIQAJournee() const{
    int* tab= new int[4];
    tab[0]=valeurToIndiceO3();
    tab[1]=valeurToIndiceSO2();
    tab[2]=valeurToIndiceNO2();
    tab[3]=valeurToIndicePM10();
    float max=tab[0];

    for(int i=1 ; i<4 ; i++){
        if(tab[i]>max){
            max=tab[i];
        }
    }

    delete [] tab;

    return max;
}