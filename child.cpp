#include <iostream>
#include <conio.h>
#include <cstdlib>

void vibor(int* mas, const int prob );

int main(int argc, char* argv[])
{
    _cputs("I am created.\n");
  std::cout << " Argc --:" << argc << std::endl;
    int* forSorting = new int[argc];
    for (int i = 1; i <argc; i++) {
        std::cout << " argv[" << i  << "]" << " = " << argv[i] << std::endl;
    }

    for (int i = 0; i < argc-1; i++) {
       
        forSorting[i] = atoi((const char*)argv[i + 1]);
    }

   
    std::cout << " Argc :" << argc << std::endl;
 
    vibor(forSorting, argc -1 );

    printf("%s", "Sorting string : ");
    for (int i = 0; i < argc ; i++)
        printf("%d%s", forSorting[i], " ");

    delete[] forSorting;
    _cputs("\nPress any key to finish.\n");
    _getch();

    return 0;
}
void vibor(int* mas, const int prob )
{
    
    int j = 0;
    int tmp = 0;
    for (int i = 0; i < prob - 1; i++) {
        j = i;
        for (int k = i; k < prob - 1; k++) {
            if (mas[j] > mas[k]) {
                j = k;
            }
        }
        tmp = mas[i];
        mas[i] = mas[j];
        mas[j] = tmp;
    }
}
