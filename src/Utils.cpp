#include <Utils.h>

byte charToDgital(char charDig)
{
    switch (charDig)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    }

    return 0;
}


byte stringToByte(String str){
    byte ch=0;

    char charStr[str.length()];
    Serial.print("\nstr.lenght():");
    Serial.println(str.length());
    strcpy(charStr, str.c_str());

    
    for(int i=str.length()-1;i>=0;i--){
        Serial.print("i:");
        Serial.println(i);
        Serial.print("charStr[i]:");
        Serial.println(charStr[i]);

        ch=ch+charToDgital(charStr[i])*pow(10,(str.length()-i-1));
        Serial.print("ch:");
        Serial.println(ch);
    }

    return ch;


}