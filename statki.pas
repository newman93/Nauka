{Pierwsza gra. Jakość kodu zerowa...}
PROGRAM statki_v3;

USES
  GRAPH,CRT;

CONST
  ROZMIAR_X = 10;                                       //rozmiar planszy, os OX
  ROZMIAR_Y = 10;                                       //rozmiar planszy, os 0Y
  CZTERO = 4;                                         //wielkosc czteromasztowca
  TRZY = 3;                                             //wielkosc trojmasztowca
  DWU = 2;                                               //wielkosc dwumasztowca
  JEDNO = 1;                                           //wielkosc jednomasztowca

TYPE                                                   //deklaracja typu planszy
  pPlanszy = Byte;
  statki = SET OF Byte;
  plansza = ARRAY[1..ROZMIAR_X,1..ROZMIAR_Y] OF pPlanszy;
  okret = RECORD
        upX : Integer;
        upY : Integer;
        downX : Integer;
        downY : Integer;
  END;

VAR
  pZawodnika1 : plansza;  { Plansza pierwszego zawodnika }
  pZawodnika2 : plansza;  { Plansza drugiego zawodnika }
  pOstrzaluZawodnika1 : plansza; { Plansza, ktora atakuje gracz 1 }
  pOstrzaluZawodnika2 : plansza; { Plansza, ktora atakuje gracz 2 }
  pZestrzelonychZawodnika1 : plansza;  { Statki zestrzelone przez zawodnika 1 }
  pZestrzelonychZawodnika2 : plansza; { Statki zestrzelone przez zawodnika 2 }
  pTestW1 : ARRAY[1..ROZMIAR_X] OF Integer; { Plansza zawierajaca wspolrzedne okretow -- tryb graficzny  - wiersz | Gracz1}
  pTestK1 : ARRAY[1..ROZMIAR_Y] OF Integer; { kolumna }
  pTestW2 : ARRAY[1..ROZMIAR_X] OF Integer; { Plansza zawierajaca wspolrzedne okretow -- tryb graficzny  - wiersz | Gracz2}
  pTestK2 : ARRAY[1..ROZMIAR_Y] OF Integer; { kolumna }
  statek : okret;
  gameEnd : Boolean;
  graczVsGracz : Boolean;
  graczVsKomputer : Boolean;
  gracz : Boolean; { T gracz 1 | F gracz 2 }
  etap : Boolean; { Etap gry -- T ustawianie statkow | F atak }
  ustawianyStatek1 : Byte; { Aktualnie ustawiany statek | gracz1 }
  ustawianyStatek2 : Byte; { Aktualnie ustawiany statek | gracz2 }
  zmiana : Boolean; { Flaga zmiany planszy } { Aktualnie nie uzywam }
  wygrana : Integer; { Licznik sprawdzajacy wygrana }
  ustaw1 : Byte; { licznik ustawianych statkow | gracz 1 }
  ustaw2 : Byte; { licznik ustawianych statkow | gracz 2}

{ DOPISAC ! }
{ Procedura obslugujaca losowanie planszy }  { Dla wersji gry z komputerem }
{ Zmiana zaznaczenia dla zestrzelonych statkow + procedura sprawdzajaca czy caly okret zostal zestrzelony }
{ Pod planszami pole na opis zasasad gry w zaleznosci od gr. vs gr., gr. vs. komp. }
{ Zmiana koloru zestrzelonych statkow. }
{ Wykreslanie obszarow, w kotrych nie moze byc statek podczas ostrzalu }
{ Ostrzal }
{ 5 - tym strzelam }
{ 4 - trafiony czteromasztowiec | 3 - trafiony trzymasztowiec | 2 - trafiony dwumasztowiec | 1 - trafiony jednomasztowiec }
{ 6 - pudlo }

PROCEDURE initialize;
VAR
  ster, tryb : smallint;
  i,j,w,k : Integer;
BEGIN
  ster:=VGA;  tryb:=VGAHi; //inicjalizacja trybu graficznego
  InitGraph(ster, tryb, 'C:\lazarus\fpc\2.6.2\source\packages\graph\src\win32\graph' );
  { Poczatkowe wspolrzedne statku }
  WITH statek DO
  BEGIN
       upX:=40;
       upY:=120;
       downX:=60;
       downY:=140;
  END;
  { Inicjalizacja pustej planszy | planszy ostrzalu dla Gracz1 oraz Gracz2 | plansze zestrzelonych }
  FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
      BEGIN
          pZawodnika1[i][j]:=0;
          pZawodnika2[i][j]:=0;
          pOstrzaluZawodnika1[i][j]:=0;
          pOstrzaluZawodnika2[i][j]:=0;
          pZestrzelonychZawodnika1[i][j]:=0;
          pZestrzelonychZawodnika2[i][j]:=0;
      END;
  { Inicjalizacja tablicy testowej z adresami okretow w trybie graficznym | Gracz1 }
  { Wiersze }
  w:=100;
  FOR i:=1 TO ROZMIAR_X DO
  BEGIN
       w:=w+20;
       pTestW1[i]:=w;
  END;
  { Kolumny }
  k:=20;
  FOR j:=1 TO ROZMIAR_Y DO
  BEGIN
       k:=k+20;
       pTestK1[j]:=k;
  END;
  { Inicjalizacja tablicy testowej z adresami okretow w trybie graficznym | Gracz2 }
  { Wiersze }
  w:=100;
  FOR i:=1 TO ROZMIAR_X DO
  BEGIN
       w:=w+20;
       pTestW2[i]:=w;
  END;
  { Kolumny }
  k:=400;
  FOR j:=1 TO ROZMIAR_Y DO
  BEGIN
       k:=k+20;
       pTestK2[j]:=k;
  END;
  { Tryb gry }
  graczVsGracz:=False;
  graczVsKomputer:=False;
  { Aktualny gracz }
  gracz:=True;
  { Aktualnie ustawiany statek | Gracz1 }
  ustawianyStatek1:=4;
  { Aktualnie ustawiany statek | Gracz2 }
  ustawianyStatek2:=4;
  { Etap gry }
  etap:=True;
  { Flaga zmiany planszy }
  zmiana:=False;
  { Flaga warunku wygrania }
  wygrana:=0;
  { Liczniki ustawianych statkow | gracz1 oraz gracz 2}
  ustaw1:=0;
  ustaw2:=0;
END;

PROCEDURE zmienGracza;
BEGIN
IF NOT(gracz) THEN
BEGIN
   gracz:=True;
   WITH statek DO
   BEGIN
     upX:=40;
     upY:=120;
     downX:=60;
     downY:=140;
   END
END
ELSE
BEGIN
  gracz:=False;
  WITH statek DO
  BEGIN
    upX:=420;
    upY:=120;
    downX:=440;
    downY:=140;
  END
END
END;

{ Obsluga klawiatury - ruch statkiem, - ostrzal  }
PROCEDURE readInput;
VAR
  klawisz : char;
  i,j : Integer;
  test : Byte;
BEGIN
{ TEST }
  REPEAT
  test:=0;
  IF KeyPressed THEN
  BEGIN
       test:=1;
       klawisz:=ReadKey;
       IF ((klawisz=#97) OR (klawisz=#65)) THEN    { Ruch w Lewo}
          IF((statek.upX <> 40) AND (statek.upX <> 420)) THEN
          BEGIN
               statek.upX:=statek.upX-20;
               statek.downX:=statek.downX-20;
          END;

       IF ((klawisz=#68) OR (klawisz=#100)) THEN    { Ruch w Prawo }
          IF((statek.upX <> 220) AND (statek.upX <> 600)) THEN
          BEGIN
               statek.upX:=statek.upX+20;
               statek.downX:=statek.downX+20;
          END;
       IF ((klawisz=#87) OR (klawisz=#119)) THEN    { Ruch w Gore }
          IF(statek.upY <> 120) THEN
          BEGIN
               statek.upY:=statek.upY-20;
               statek.downY:=statek.downY-20;
          END;
       IF ((klawisz=#83) OR (klawisz=#115)) THEN    { Ruch w Dol }
          IF(statek.upY <> 300) THEN
          BEGIN
               statek.upY:=statek.upY+20;
               statek.downY:=statek.downY+20;
          END;
       IF (((klawisz=#70) OR (klawisz=#102)) AND NOT(etap)) THEN     { Ostrzal | Gracz1 }
         IF gracz THEN
          FOR i:=1 TO ROZMIAR_X DO
              IF (pTestW1[i]=statek.upY) THEN
                 FOR j:=1 TO ROZMIAR_Y DO
                     IF (pTestK1[j]=statek.upX) THEN
                        pOstrzaluZawodnika1[i][j]:=5; { Strzelam piatkami }
       IF (((klawisz=#70) OR (klawisz=#102)) AND NOT(etap)) THEN     { Ostrzal | Gracz2 }
         IF NOT(gracz) THEN
          FOR i:=1 TO ROZMIAR_X DO
              IF (pTestW2[i]=statek.upY) THEN
                 FOR j:=1 TO ROZMIAR_Y DO
                     IF (pTestK2[j]=statek.upX) THEN
                        pOstrzaluZawodnika2[i][j]:=5; { Strzelam piatkami }
       IF (((klawisz=#85) OR (klawisz=#117)) AND etap) THEN    { Ustawianie | Gracz1 }
         IF gracz THEN
           FOR i:=1 TO ROZMIAR_X DO
              IF (pTestW1[i]=statek.upY) THEN
                 FOR j:=1 TO ROZMIAR_Y DO
                     IF (pTestK1[j]=statek.upX) THEN
                     BEGIN
                        pZawodnika1[i][j]:=ustawianyStatek1;
                        Inc(ustaw1);
                     END;
        IF (((klawisz=#85) OR (klawisz=#117)) AND etap) THEN    { Ustawianie | Gracz2 }
          IF NOT(gracz) THEN
            FOR i:=1 TO ROZMIAR_X DO
              IF (pTestW2[i]=statek.upY) THEN
                 FOR j:=1 TO ROZMIAR_Y DO
                     IF (pTestK2[j]=statek.upX) THEN
                     BEGIN
                        pZawodnika2[i][j]:=ustawianyStatek2;
                        Inc(ustaw2);
                     END;
        IF (((klawisz=#67) OR (klawisz=#99)) AND NOT(etap)) THEN  { Zmiana gracza }
          zmienGracza;
        IF (klawisz=#27) THEN { Wyjscie z gry }
          gameEnd:=False;
  END;
  UNTIL test=1;
END;

PROCEDURE update;
VAR
  i,j,w,k,l,m : Integer;
  licznik : Integer;
  ostrzal : Integer; { licznik ostrzalu }
  pozycjaJ : Integer; { pierwsza pozycja zestrzelonego | Kolumna }
  pozycjaI : Integer; { pierwsza pozycja zestrzelonego | Wiersz }
  wStatki : statki; { zbior z rodzajami statkow }
  lWykreslen : byte; { licznik wykreslonych pol }
  r,s : byte; { zmienne pomocnicze do wykreslania statkow }   { TEST }
  pozycjaJkolumna : Integer;   { TEST }
  pozycjaJwiersz : Integer; { TEST }
  pozycjaIkolumna : Integer;   { TEST }
  pozycjaIwiersz : Integer; { TEST }
  kolumna : Integer; { TEST }
  wiersz : Integer; { TEST }
  licznikK : Integer; { liczik kolumn : TEST }
BEGIN
  wStatki:=[4,3,2,1];
  kolumna:=0; { TEST }
  wiersz:=0;  { TEST }
  licznikK:=0; { TEST }
  IF gracz AND etap THEN
  BEGIN
  w:=100;
  k:=20;
  licznik:=0;
  FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
          IF (pZawodnika1[i][j]<>0) THEN
          BEGIN
             w:=w+20*i;
             k:=k+20*j;
             l:=w+20;
             m:=k+20;
             SetFillStyle(solidfill,Yellow);
             Bar(k,w,m,l);
             w:=100;
             k:=20;
             continue;
          END;

    IF ((ustawianyStatek1 <> 0) AND (ustawianyStatek1 <> 9)) THEN
    BEGIN
    FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
        IF(pZawodnika1[i][j]=4) THEN
          Inc(licznik);
    IF(licznik = 4) THEN
      ustawianyStatek1:=3;
    licznik:=0;
    FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
        IF(pZawodnika1[i][j]=3) THEN
          Inc(licznik);
    IF(licznik = 6) THEN
      ustawianyStatek1:=2;
    licznik:=0;
    FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
        IF(pZawodnika1[i][j]=2) THEN
          Inc(licznik);
    IF(licznik = 6) THEN
      ustawianyStatek1:=1;
    licznik:=0;
    FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
        IF(pZawodnika1[i][j]=1) THEN
          Inc(licznik);
    IF(licznik = 4) THEN
    BEGIN
      ustawianyStatek1:=0;
    END;
    END
    ELSE
    IF(ustawianyStatek1=0) THEN
    BEGIN
    gracz:=False;
      WITH statek DO
      BEGIN
        upX:=420;
        upY:=120;
        downX:=440;
        downY:=140;
      END;
      ustawianyStatek1:=9; { W celu przejscia na plansze drugiego gracza }
    END;
    END
  ELSE
  IF NOT(gracz) AND etap THEN
  BEGIN
  w:=100;
  k:=400;
  licznik:=0;
  FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
          IF (pZawodnika2[i][j]<>0) THEN
          BEGIN
             w:=w+20*i;
             k:=k+20*j;
             l:=w+20;
             m:=k+20;
             SetFillStyle(solidfill,Yellow);
             Bar(k,w,m,l);
             w:=100;
             k:=400;
             continue;
          END;

    IF ((ustawianyStatek2 <> 0) AND (ustawianyStatek2 <> 9)) THEN
    BEGIN
    FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
        IF(pZawodnika2[i][j]=4) THEN
          Inc(licznik);
    IF(licznik = 4) THEN
      ustawianyStatek2:=3;
    licznik:=0;
    FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
        IF(pZawodnika2[i][j]=3) THEN
          Inc(licznik);
    IF(licznik = 6) THEN
      ustawianyStatek2:=2;
    licznik:=0;
    FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
        IF(pZawodnika2[i][j]=2) THEN
          Inc(licznik);
    IF(licznik = 6) THEN
      ustawianyStatek2:=1;
    licznik:=0;
    FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
        IF(pZawodnika2[i][j]=1) THEN
          Inc(licznik);
    IF(licznik = 4) THEN
    BEGIN
      ustawianyStatek2:=0;
    END;
    END
    ELSE
    IF(ustawianyStatek2=0) THEN
    BEGIN
    gracz:=True;
      WITH statek DO
      BEGIN
        upX:=40;
        upY:=120;
        downX:=60;
        downY:=140;
      END;
      ustawianyStatek2:=9; { W celu przejscia na plansze drugiego gracza }
      etap:=False; { Zmiana etapu gry | Statki ustawione, czas na atak }
    END;
    END;
  IF gracz AND NOT(etap) THEN
  BEGIN
  w:=100;
  k:=20;
  FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
          IF (pOstrzaluZawodnika1[i][j] <> 0) AND (pZawodnika2[i][j] <> 0) THEN
          BEGIN
             pOstrzaluZawodnika1[i][j]:=pZawodnika2[i][j]; { Test | Oznaczam trafiony statek }
             w:=w+20*i;
             k:=k+20*j;
             l:=w+20;
             m:=k+20;
             IF (pOstrzaluZawodnika1[i][j]=1) THEN     { Automatyczne wykreslanie zestrzelonych jednomasztowcow }
               SetFillStyle(solidfill,Red)
             ELSE
               SetFillStyle(solidfill,LightRed);
             Bar(k,w,m,l);
             w:=100;
             k:=20;
             continue;
          END
          ELSE
          IF (pOstrzaluZawodnika1[i][j] <> 0) AND (pZawodnika2[i][j]=0) THEN
          BEGIN
             pOstrzaluZawodnika1[i][j]:=6; { Test | Oznaczam pudlo }
             w:=w+20*i;
             k:=k+20*j;
             l:=w+20;
             m:=k+20;
             SetFillStyle(solidfill,Cyan);
             Bar(k,w,m,l);
             w:=100;
             k:=20;
             continue;
          END;
    { Sprawdzenie wygranej }
   FOR i:=1 TO ROZMIAR_X DO
     FOR j:=1 TO ROZMIAR_Y DO
       IF (pOstrzaluZawodnika1[i][j] IN wStatki) THEN
         wygrana:=wygrana+1;
    IF (wygrana=20) THEN
      gameEnd:=False
    ELSE
      wygrana:=0
  END
  ELSE
  IF NOT(gracz) AND NOT(etap) THEN
  BEGIN
  w:=100;
  k:=400;
  FOR i:=1 TO ROZMIAR_X DO
      FOR j:=1 TO ROZMIAR_Y DO
          IF (pOstrzaluZawodnika2[i][j] <> 0) AND (pZawodnika1[i][j] <> 0) THEN
          BEGIN
             pOstrzaluZawodnika2[i][j]:=pZawodnika1[i][j]; { Test | Oznaczam trafiony statek }
             w:=w+20*i;
             k:=k+20*j;
             l:=w+20;
             m:=k+20;
              IF (pOstrzaluZawodnika2[i][j]=1) THEN     { Automatyczne wykreslanie zestrzelonych jednomasztowcow }
               SetFillStyle(solidfill,Red)
             ELSE
               SetFillStyle(solidfill,LightRed);
             Bar(k,w,m,l);
             w:=100;
             k:=400;
             continue;
          END
          ELSE
          IF (pOstrzaluZawodnika2[i][j] <> 0) AND (pZawodnika1[i][j] = 0) THEN
          BEGIN
             pOstrzaluZawodnika2[i][j]:=6; { Test | Oznaczam pudlo }
             w:=w+20*i;
             k:=k+20*j;
             l:=w+20;
             m:=k+20;
             SetFillStyle(solidfill,Cyan);
             Bar(k,w,m,l);
             w:=100;
             k:=400;
             continue;
          END;
   { Wykreslanie zestrzelonych statkow }
   ostrzal:=0;
   { Zestrzelono 4-masztowiec }
    { Wiersze }
   i:=1;
   WHILE (i<=10) DO
   BEGIN
     ostrzal:=0;
     FOR j:=1 TO ROZMIAR_Y DO
     BEGIN
       IF (pOstrzaluZawodnika2[i][j]=4) THEN
         Inc(ostrzal);
       IF (ostrzal=4) THEN
       BEGIN
         pozycjaJ:=j;
         pozycjaI:=i;
         i:=11;
         break;
       END;
     END;
     Inc(i);
   END;
     { Zestrzelony | Wiersz }
   IF (ostrzal=4) THEN
   BEGIN
   w:=100;
   k:=400;
   w:=w+20*pozycjaI;
   k:=k+20*(pozycjaJ-3);
   l:=w+20;
   m:=k+4*20;
   SetFillStyle(solidfill,Red);
   Bar(k,w,m,l);
   END;

    { Kolumny }
   ostrzal:=0;
   pozycjaI:=11; { Zabezpieczenie }
   i:=1;
   WHILE (i<=10) DO
   BEGIN
     IF (ostrzal=4) THEN
     BEGIN
       pozycjaI:=i-1;
       break;
     END;
     FOR j:=1 TO ROZMIAR_Y DO
     BEGIN
       IF (pOstrzaluZawodnika2[i][j]=4) THEN
       BEGIN
         Inc(ostrzal);
         IF (ostrzal=3) THEN   { Zabezpieczenie gdy w ostatnim wierszu bedzie statek }
           pozycjaJ:=j;
         break;
       END;
     END;
     Inc(i);
   END;
   IF (ostrzal=4) AND (pozycjaI=11) THEN
   BEGIN
     pozycjaI:=i-1;
   END;
    { Zestrzelona | Kolumna }
   IF (ostrzal=4) THEN
   BEGIN
   w:=100;
   k:=400;
   w:=w+20*(pozycjaI-3);
   k:=k+20*pozycjaJ;
   l:=w+4*20;
   m:=k+20;
   SetFillStyle(solidfill,Red);
   Bar(k,w,m,l);
   END;

   { Zestrzelono 3-masztowiec }       { TEST }
    { Wiersze }
   ostrzal:=0;
   i:=1;
   WHILE (i<=10) DO
   BEGIN
     ostrzal:=0;
     FOR j:=1 TO ROZMIAR_Y DO
     BEGIN
       IF (pOstrzaluZawodnika2[i][j]=3) THEN
         Inc(ostrzal);
       IF (ostrzal=3) THEN
       BEGIN
         pozycjaJwiersz:=j;
         pozycjaIwiersz:=i;
         wiersz:=1;
         i:=11;
         break;
       END;
     END;
     Inc(i);
   END;
     { Zestrzelony | Wiersz }
   IF (ostrzal=3) AND (wiersz=1) THEN
   BEGIN
   w:=100;
   k:=400;
   w:=w+20*pozycjaIwiersz;
   k:=k+20*(pozycjaJwiersz-2);
   l:=w+20;
   m:=k+3*20;
   SetFillStyle(solidfill,Red);
   Bar(k,w,m,l);
   END;

    { Kolumny }
   ostrzal:=0;
   pozycjaI:=11; { Zabezpieczenie }
   i:=1;
   WHILE (i<=10) DO
   BEGIN
     IF (ostrzal=3) AND (pozycjaJkolumna=j) THEN
     BEGIN
       pozycjaIkolumna:=i-1;
       kolumna:=1;
       break;
     END;
     FOR j:=1 TO ROZMIAR_Y DO
     BEGIN
       IF (pOstrzaluZawodnika2[i][j]=3) THEN
       BEGIN
         Inc(ostrzal);
         IF (licznikK=0) THEN
         BEGIN
          pozycjaJkolumna:=j;
          Inc(licznikK);
         END;
         {IF (ostrzal=2) THEN   { Zabezpieczenie gdy w ostatnim wierszu bedzie statek }
           pozycjaJ:=j; }
         break;
       END;
     END;
     Inc(i);
   END;
   IF (ostrzal=3) AND (pozycjaIkolumna=11) AND (pozycjaJkolumna=j) THEN
   BEGIN
     pozycjaIkolumna:=i-1;
     kolumna:=1;
   END;
    { Zestrzelona | Kolumna }
   IF (ostrzal=3) AND (kolumna=1) THEN
   BEGIN
   w:=100;
   k:=400;
   w:=w+20*(pozycjaI-2);
   k:=k+20*pozycjaJ;
   l:=w+3*20;
   m:=k+20;
   SetFillStyle(solidfill,Red);
   Bar(k,w,m,l);
   END;

{
   ostrzal:=0;
   { Zestrzelono 2-masztowiec }       { TEST }
    { Wiersze }
   i:=1;
   j:=1;
   WHILE (i<=10) DO
   BEGIN                            0
     ostrzal:=0;
     FOR j:=1 TO ROZMIAR_Y DO
     BEGIN
       IF (pOstrzaluZawodnika2[i][j]=2) THEN
         Inc(ostrzal);
       IF (ostrzal=2) THEN
       BEGIN
         pozycjaJ:=j;
         pozycjaI:=i;
         i:=11;
         break;
       END;
     END;
     Inc(i);
   END;
     { Zestrzelony | Wiersz }
   IF (ostrzal=2) THEN
   BEGIN
   w:=100;
   k:=400;
   w:=w+20*pozycjaI;
   k:=k+20*(pozycjaJ-1);
   l:=w+20;
   m:=k+2*20;
   SetFillStyle(solidfill,Red);
   Bar(k,w,m,l);
   END;

    { Kolumny }
   ostrzal:=0;
   pozycjaI:=11; { Zabezpieczenie }
   FOR i:=1 TO ROZMIAR_X DO
   BEGIN
     IF (ostrzal=2) THEN
     BEGIN
       pozycjaI:=i-1;
     END;
     FOR j:=1 TO ROZMIAR_Y DO
     BEGIN
       IF (pOstrzaluZawodnika2[i][j]=1) THEN
       BEGIN
         Inc(ostrzal);
         IF (ostrzal=1) THEN   { Zabezpieczenie gdy w ostatnim wierszu bedzie statek }
           pozycjaJ:=j;
         break;
       END;
     END;
   END;
   IF (ostrzal=2) AND (pozycjaI=11) THEN
   BEGIN
     pozycjaI:=i;
   END;
    { Zestrzelona | Kolumna }
   IF (ostrzal=2) THEN
   BEGIN
   w:=100;
   k:=400;
   w:=w+20*(pozycjaI-1);
   k:=k+20*pozycjaJ;
   l:=w-2*20;
   m:=k+20;
   SetFillStyle(solidfill,Red);
   Bar(k,w,m,l);
   END;
 }
   FOR i:=1 TO ROZMIAR_X DO
     FOR j:=1 TO ROZMIAR_Y DO
       IF (pOstrzaluZawodnika2[i][j] IN wStatki) THEN
         wygrana:=wygrana+1;
    IF (wygrana=20) THEN
      gameEnd:=False
    ELSE
      wygrana:=0;
END;
END;

PROCEDURE draw;
VAR
  i,j,n : Integer;
  k : String;
BEGIN
  SetTextStyle(SmallFont,0,0);
  SetBkColor(DarkGray);
  ClearDevice;
  SetFillStyle(solidfill,Blue);
  Bar(20,100,240,320);  { Pierwsza Plansza }
  Bar(400,100,620,320); { Druga Plansza }
  { Menu }
  SetFillStyle(solidfill,brown);
  Bar(250,100,390,320);
  OutTextXY(305,120,'MENU');
  OutTextXY(255,140,'OPCJE');
  OutTextXY(255,155,'W - ruch w gore');
  OutTextXY(255,170,'S - ruch w dol');
  OutTextXY(255,185,'A - ruch w lewo');
  OutTextXY(255,200,'D - ruch w prawo');
  IF etap THEN
    OutTextXY(255,215,'U - ustaw statek')
  ELSE
  BEGIN
    OutTextXY(255,215,'F - strzal');
    OutTextXY(255,230,'C - zmiana gracza');
  END;
  OutTextXY(255,280,'ESC - wyjscie');
  OutTextXY(100,80,'Gracz 1');
  OutTextXY(480,80,'Gracz 2');
  OutTextXY(280,30,'Etap gry: ');
  IF etap THEN
    OutTextXY(245,45,'Ustawianie statkow')
  ELSE
    OutTextXY(265,45,'Ostrzal wroga');
  OutTextXY(265,65,'Aktualny ruch:');
  IF gracz THEN
    OutTextXY(290,85,'Gracz 1')
  ELSE
    OutTextXY(290,85,'Gracz 2');
  SetFillStyle(solidfill,LightBlue);
  { Pierwsza Plansza -- label }
  Bar(20,100,240,120);
  Bar(20,100,40,320);
  { Druga Plansza -- label }
  Bar(400,100,620,120);
  Bar(400,100,420,320);
  { Pierwsza Plansza -- linie }
  i:=100;
  SetColor(White);
  REPEAT
  BEGIN
       Line(20,i,240,i);
       i:=i+20;
  END;
  UNTIL (i>320) ;
  j:=20;
  REPEAT
  BEGIN
       Line(j,100,j,320);
       j:=j+20;
  END;
  UNTIL (j>240);
  { Pierwsza Plansza - oznaczenia planszy - Poziome }
  n:=65;
  j:=47;
  FOR i:=1 TO 10 DO
  BEGIN
     k:=chr(n);
     OutTextXY (j,107, k);
     n:=n+1;
     j:=j+20;
  END;
  { Pierwsza Plansza - oznaczenie planszy | Pionowe }
  n:=49;
  j:=127;
  FOR i:=1 TO 9 DO
  BEGIN
       k:=chr(n);
       OutTextXY(27,j,k);
       n:=n+1;
       j:=j+20;
  END;
  OutTextXY(23,j,'10');
  { Druga Plansza -- linie }
  i:=100;
  SetColor(White);
  REPEAT
  BEGIN
       Line(400,i,620,i);
       i:=i+20;
  END;
  UNTIL (i>320) ;
  j:=400;
  REPEAT
  BEGIN
       Line(j,100,j,320);
       j:=j+20;
  END;
  UNTIL (j>620);
  { Druga Plansza -- oznaczenie planszy - Poziome }
  n:=65;
  j:=427;
  FOR i:=1 TO 10 DO
  BEGIN
     k:=chr(n);
     OutTextXY (j,107, k);
     n:=n+1;
     j:=j+20;
  END;
  { Druga Plansza -- oznaczenie planszy | Pionowe }
  n:=49;
  j:=127;
  FOR i:=1 TO 9 DO
  BEGIN
       k:=chr(n);
       OutTextXY(407,j,k);
       n:=n+1;
       j:=j+20;
  END;
  OutTextXY(403,j,'10');
  { Statek -- do ustawienia }
  SetFillStyle(solidfill,LightGreen);
  Bar(statek.upX,statek.upY,statek.downX,statek.downY);
 { Podpowiedzi gracz 1}  { Jezeli tez kochasz PASCALA to przeskocz do wiersza nr 1435 }
  IF (gracz) AND (etap) THEN
  BEGIN
  SetFillStyle(solidfill,Brown);
  Bar(20,340,240,460);
  OutTextXY(25,350,'Statki do ustawienia: ');
  OutTextXY(125,360,'- 4 masztowiec');
  OutTextXY(125,370,'- 3 masztowiec');
  OutTextXY(125,380,'- 3 masztowiec');
  OutTextXY(125,390,'- 2 masztowiec');
  OutTextXY(125,400,'- 2 masztowiec');
  OutTextXY(125,410,'- 2 masztowiec');
  OutTextXY(125,420,'- 1 masztowiec');
  OutTextXY(125,430,'- 1 masztowiec');
  OutTextXY(125,440,'- 1 masztowiec');
  OutTextXY(125,450,'- 1 masztowiec');
  CASE ustaw1 OF
   0 :
  BEGIN
  OutTextXY(25,360,'[][][][]');
  OutTextXY(25,370,'[][][]');
  OutTextXY(25,380,'[][][]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   1 :
  BEGIN
  OutTextXY(25,360,'[O][][][]');
  OutTextXY(25,370,'[][][]');
  OutTextXY(25,380,'[][][]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   2 :
  BEGIN
  OutTextXY(25,360,'[O][O][][]');
  OutTextXY(25,370,'[][][]');
  OutTextXY(25,380,'[][][]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   3 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][]');
  OutTextXY(25,370,'[][][]');
  OutTextXY(25,380,'[][][]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   4 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[][][]');
  OutTextXY(25,380,'[][][]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   5 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][][]');
  OutTextXY(25,380,'[][][]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   6 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][]');
  OutTextXY(25,380,'[][][]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   7 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[][][]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   8 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][][]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   9 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   10 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   11 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[O][]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   12 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[O][O]');
  OutTextXY(25,400,'[][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   13 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[O][O]');
  OutTextXY(25,400,'[O][]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   14 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[O][O]');
  OutTextXY(25,400,'[O][O]');
  OutTextXY(25,410,'[][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   15 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[O][O]');
  OutTextXY(25,400,'[O][O]');
  OutTextXY(25,410,'[O][]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   16 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[O][O]');
  OutTextXY(25,400,'[O][O]');
  OutTextXY(25,410,'[O][O]');
  OutTextXY(25,420,'[]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   17 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[O][O]');
  OutTextXY(25,400,'[O][O]');
  OutTextXY(25,410,'[O][O]');
  OutTextXY(25,420,'[O]');
  OutTextXY(25,430,'[]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   18 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[O][O]');
  OutTextXY(25,400,'[O][O]');
  OutTextXY(25,410,'[O][O]');
  OutTextXY(25,420,'[O]');
  OutTextXY(25,430,'[O]');
  OutTextXY(25,440,'[]');
  OutTextXY(25,450,'[]');
  END;
   19 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[O][O]');
  OutTextXY(25,400,'[O][O]');
  OutTextXY(25,410,'[O][O]');
  OutTextXY(25,420,'[O]');
  OutTextXY(25,430,'[O]');
  OutTextXY(25,440,'[O]');
  OutTextXY(25,450,'[]');
  END;
   20 :
  BEGIN
  OutTextXY(25,360,'[O][O][O][O]');
  OutTextXY(25,370,'[O][O][O]');
  OutTextXY(25,380,'[O][O][O]');
  OutTextXY(25,390,'[O][O]');
  OutTextXY(25,400,'[O][O]');
  OutTextXY(25,410,'[O][O]');
  OutTextXY(25,420,'[O]');
  OutTextXY(25,430,'[O]');
  OutTextXY(25,440,'[O]');
  OutTextXY(25,450,'[O]');
  END;
  END;
  END;
  { Podpowiedzi gracz 2 }
   IF NOT(gracz) AND (etap) THEN
  BEGIN
  SetFillStyle(solidfill,Brown);
  Bar(400,340,620,460);
  OutTextXY(405,350,'Statki do ustawienia: ');
  OutTextXY(505,360,'- 4 masztowiec');
  OutTextXY(505,370,'- 3 masztowiec');
  OutTextXY(505,380,'- 3 masztowiec');
  OutTextXY(505,390,'- 2 masztowiec');
  OutTextXY(505,400,'- 2 masztowiec');
  OutTextXY(505,410,'- 2 masztowiec');
  OutTextXY(505,420,'- 1 masztowiec');
  OutTextXY(505,430,'- 1 masztowiec');
  OutTextXY(505,440,'- 1 masztowiec');
  OutTextXY(505,450,'- 1 masztowiec');
  CASE ustaw2 OF
   0 :
  BEGIN
  OutTextXY(405,360,'[][][][]');
  OutTextXY(405,370,'[][][]');
  OutTextXY(405,380,'[][][]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   1 :
  BEGIN
  OutTextXY(405,360,'[O][][][]');
  OutTextXY(405,370,'[][][]');
  OutTextXY(405,380,'[][][]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   2 :
  BEGIN
  OutTextXY(405,360,'[O][O][][]');
  OutTextXY(405,370,'[][][]');
  OutTextXY(405,380,'[][][]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   3 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][]');
  OutTextXY(405,370,'[][][]');
  OutTextXY(405,380,'[][][]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   4 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[][][]');
  OutTextXY(405,380,'[][][]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   5 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][][]');
  OutTextXY(405,380,'[][][]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   6 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][]');
  OutTextXY(405,380,'[][][]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   7 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[][][]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   8 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][][]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   9 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   10 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   11 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[O][]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   12 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[O][O]');
  OutTextXY(405,400,'[][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   13 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[O][O]');
  OutTextXY(405,400,'[O][]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   14 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[O][O]');
  OutTextXY(405,400,'[O][O]');
  OutTextXY(405,410,'[][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   15 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[O][O]');
  OutTextXY(405,400,'[O][O]');
  OutTextXY(405,410,'[O][]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   16 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[O][O]');
  OutTextXY(405,400,'[O][O]');
  OutTextXY(405,410,'[O][O]');
  OutTextXY(405,420,'[]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   17 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[O][O]');
  OutTextXY(405,400,'[O][O]');
  OutTextXY(405,410,'[O][O]');
  OutTextXY(405,420,'[O]');
  OutTextXY(405,430,'[]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   18 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[O][O]');
  OutTextXY(405,400,'[O][O]');
  OutTextXY(405,410,'[O][O]');
  OutTextXY(405,420,'[O]');
  OutTextXY(405,430,'[O]');
  OutTextXY(405,440,'[]');
  OutTextXY(405,450,'[]');
  END;
   19 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[O][O]');
  OutTextXY(405,400,'[O][O]');
  OutTextXY(405,410,'[O][O]');
  OutTextXY(405,420,'[O]');
  OutTextXY(405,430,'[O]');
  OutTextXY(405,440,'[O]');
  OutTextXY(405,450,'[]');
  END;
   20 :
  BEGIN
  OutTextXY(405,360,'[O][O][O][O]');
  OutTextXY(405,370,'[O][O][O]');
  OutTextXY(405,380,'[O][O][O]');
  OutTextXY(405,390,'[O][O]');
  OutTextXY(405,400,'[O][O]');
  OutTextXY(405,410,'[O][O]');
  OutTextXY(405,420,'[O]');
  OutTextXY(405,430,'[O]');
  OutTextXY(405,440,'[O]');
  OutTextXY(405,450,'[O]');
  END;
  END;
  END;
END;

PROCEDURE menu;
VAR
  klawisz : Char;
BEGIN
    SetBkColor(DarkGray);
    ClearDevice;
    SetFillStyle(solidfill,LightBlue);;
    Bar(20,20,620,460);
    SetTextStyle(BoldFont,0,12);
    OutTextXY(45,45,'STATKI');
    SetTextStyle(SmallFont,0,5);
    OutTextXY(230,180,'MENU');
    SetTextStyle(SmallFont,0,3);
    OutTextXY(100,280,'1 - Gracz vs Gracz');
    SetTextStyle(SmallFont,0,3);
    OutTextXY(70,350,'2 - Gracz vs Komputer');
      klawisz:=ReadKey;
        IF (klawisz=#49) THEN
          graczVsGracz:=True
        ELSE
        IF (klawisz=#50) THEN
          graczVsKomputer:=True;
END;

PROCEDURE exit;
VAR
  klawisz : Char;
BEGIN
    SetBkColor(DarkGray);
    ClearDevice;
    SetFillStyle(solidfill,LightBlue);;
    Bar(20,20,620,460);
    SetTextStyle(BoldFont,0,6);
    IF (wygrana=20) THEN
    BEGIN
      OutTextXY(75,150,'KONIEC GRY');
      OutTextXY(75,200,'WYGRAL: ');
    IF gracz THEN
      OutTextXY(75,250,'Gracz 1')
    ELSE
      OutTextXY(75,250,'Gracz 2')
    END
    ELSE
    OutTextXY(75,200,'KONIEC GRY');
END;


BEGIN
   initialize;
   menu;
   gameEnd:=True;
   REPEAT
          readInput;
          draw;
          update;
          delay(1);
   UNTIL gameEnd <> True;
   exit;
   Readln;
END.
                { SMIECI }
{procedure ustawStatki(var pZawodnika : plansza);     //ustawienie statkow na planszy
var
  x,y,i,j,w,k,l : byte;
begin
  randomize;
  x:=random(10);
  {y:=random(11);
  y:=y-1;}
  x:=x+1;                                //wykluczenie mozliwosci uzyskania zero
  y:=1;
  if (y=1) then
   if ((x+CZTERO)<=11) then
   begin
     j:=x;
     w:=1;                                             //licnzik przebiegu petli
     repeat
      pZawodnika[y][j]:=4;
      wykluczPola(l,k,pZawodnika);
      j:=j+1;
      w:=w+1;
     until (w>4);
   end
   else
   begin
    j:=x;
    w:=1;
   repeat
    pZawodnika[y][j]:=4;
    j:=j-1;
    w:=w+1;
   until (w>4)
   end;
end; }
{procedure wykluczPola(x : byte;y : byte;pZawodnika : plansza);
begin
  pZawodnika[y][x]:=5;
end;}

{
PROCEDURE graczVsGracz;
VAR
  klawisz : Char;
  k : Char;
  i,j,n : Integer;
BEGIN
  SetTextStyle(SmallFont,0,0);
  SetBkColor(DarkGray);
  ClearDevice;
  { Pierwszy gracz }
  SetFillStyle(solidfill,Blue);;
  Bar(20,100,240,320);
  OutTextXY(100,80,'Gracz 1');
  { Pierwsza Plansza -- label }
  Bar(20,100,240,120);
  Bar(20,100,40,320);
  { Pierwsza Plansza -- linie }
  i:=100;
  SetColor(White);
  REPEAT
  BEGIN
       Line(20,i,240,i);
       i:=i+20;
  END;
  UNTIL (i>320) ;
  j:=20;
  REPEAT
  BEGIN
       Line(j,100,j,320);
       j:=j+20;
  END;
  UNTIL (j>240);
  { Pierwsza Plansza - oznaczenia planszy - Poziome }
  n:=65;
  j:=47;
  FOR i:=1 TO 10 DO
  BEGIN
     k:=chr(n);
     OutTextXY(j,107, k);
     n:=n+1;
     j:=j+20;
  END;
  { Pierwsza Plansza - oznaczenie planszy | Pionowe }
  n:=49;
  j:=127;
  FOR i:=1 TO 9 DO
  BEGIN
       k:=chr(n);
       OutTextXY(27,j,k);
       n:=n+1;
       j:=j+20;
  END;
  OutTextXY(23,j,'10');
  klawisz:=ReadKey;
END;

PROCEDURE graczVsKomputer;
BEGIN
END;
}
{
{ Planowane wczytywanie gotowych arkuszu z pliku }
PROCEDURE ustawStatki(VAR pZawodnika : plansza);
BEGIN
   //czteromasztowce
   pZawodnika[1][1]:=4; pZawodnika[1][2]:=4; pZawodnika[1][3]:=4; pZawodnika[1][4]:=4;
   //trzymasztowce
   pZawodnika[3][1]:=3; pZawodnika[3][2]:=3; pZawodnika[3][3]:=3;
   pZawodnika[4][5]:=3; pZawodnika[5][5]:=3; pZawodnika[6][5]:=3;
   //dumasztowce
   pZawodnika[3][7]:=2; pZawodnika[3][8]:=2;
   pZawodnika[6][9]:=2; pZawodnika[7][9]:=2;
   pZawodnika[7][1]:=2; pZawodnika[8][1]:=2;
   //jednomasztowce
   pZawodnika[7][7]:=1; pZawodnika[10][4]:=1; pZawodnika[10][2]:=1; pZawodnika[10][10]:=1;
END;
}

