#include <iostream>
//#include<windows.h>
const int BUF_SIZE = 128 * 1024;
char buf[BUF_SIZE];
int main(void)
{
    setvbuf(stdout, buf, _IOFBF, BUF_SIZE);
    for (int i = 0; i < 256; i++)
    {
        // std::cout << "i:\t" << i << "\t";
        std::cout << std::flush << "\033[48;5;" << i << "m" << std::flush;
        std::cout <<i<< "\t\033[0m" << std::flush;
        if (i && !((i + 3) % 6))
        {
            std::cout << "\n";
        }
        else
        {
            std::cout<<std::flush//<<"\t"<<std::flush;
            ;
        }
        
    }
    //while(1);
    return 0;
}