/*
    Autor: Adrian Kowalski
*/

#include <stdio.h>

typedef enum { dostepna, wypozyczona, zgubiona, w_oprawie, w_trakcie_zakupu } status; 

struct karta{
  char *autor;
  char *tytul;
  int numer;
  int rok; 
  status stat;
};

void sortuj(struct karta _Karta[])
{
  int i,j;
  struct karta tmp;
  
  for (i=0; i<4; i++)
  	for(j=i+1; j<4; j++)
        	if(_Karta[i].numer>_Karta[j].numer)     
                {
                  tmp=_Karta[i];
                  _Karta[i]=_Karta[j];
                  _Karta[j]=tmp;  
                }
}

void wyswietl(struct karta _Karta[])
{
  int i;
  
  for(i=0; i<4; i++)
  {
    printf("Autor: %s Tytul: %s Numer: %d Rok: %d Status: ",_Karta[i].autor,_Karta[i].tytul,_Karta[i].numer,_Karta[i].rok);
    switch (_Karta[i].stat)
    {
      case 0:
      {
              printf("Dostepna\n");
              break;
      }
      case 1:
      {
              printf("Wypozyczona\n");
              break;
      }
      case 2:
      {
              printf("Zgubiona\n");
              break;
      }
      case 3:
      {
              printf("W oprawie\n");
              break;
      }
      case 4:
      {
              printf("W trakcie zakupy\n");
              break;
      }
   }
 }  
};

int main(void)
{
  struct karta _Karta[4] = {
                             {"Mickiewicz","Dziady",12345678,1822, zgubiona},
                             {"Slowacki","Kordian",12345679,1834, w_oprawie}, 
                             {"Sienkiewicz","Potop",12345687,1886, dostepna},
                             {"Reymont","Chlopi",32165487,1904, w_trakcie_zakupu}
                           };
  
  wyswietl(_Karta);
  sortuj(_Karta);
  wyswietl(_Karta);
  
  return 0;
}
