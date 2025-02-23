#include <stdio.h>

int main(){
    char str1[100];
    char str2[100];
    int a, b;
    char *formatlf_space_ni = "long double %6g";
    long double with_dot = 12.4567;
    // a = s21_sprintf(str1, formatlf_space_ni, with_dot);
    b = sprintf(str2, formatlf_space_ni, with_dot);
   
    printf("\n%s", str2);

}