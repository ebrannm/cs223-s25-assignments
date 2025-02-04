#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Enter digits: ");
    char* c_arr = malloc(sizeof(char) * 32);
    scanf("%s", c_arr);
    int* i_arr = malloc(sizeof(int) *96);
    int idx = 0; 
    for (int i = 0; i < strlen(c_arr); i++){
        if (c_arr[i] < 58 && c_arr[i] > 47) {
           i_arr[idx] = c_arr[i] - 48;   
           idx += 1;
        } else {
           if (c_arr[i] > 100) {
              i_arr[idx] = 1;
              idx +=1;
              c_arr[i] -= 100;
        }            
        i_arr[idx] = c_arr[i] / 10;
        idx += 1;
        i_arr[idx] = c_arr[i] % 10;
        idx += 1;
        }
    }
    
    free(c_arr);
    int temp, swapped;
    for (int i = 0; i < idx; i++) {
       swapped = 0;
       for (int j = 0; j  < idx - i - 1; j++) {
           if (i_arr[j] > i_arr[j + 1]) {
               temp = i_arr[j];
               i_arr[j] = i_arr[j + 1]; 
               i_arr[j + 1] = temp;
               swapped = 1;
           }    
       }
       if (swapped == 0){
           break;
       }
    }
    for (int i = 0; i < idx; i++) {
        printf("%d ", i_arr[i]);
    } 
    printf("\n");
    free(i_arr);
    return 0;
}    
       
    
