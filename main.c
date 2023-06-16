// HASAN CEYHAN 20010011091 - Veri Yap�lar� Dersi Telefon Rehber Uygulamas�

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

// K�t�phanelerimi ekledim, kay�t tutacak olan struct yap�m� olu�turdum. 				Telefon numaras� neden int de�il ��nk� C'de int �zerinde gezmek zor.
// Bir tane main() fonksiyonum var i�inde men� yap�s� var. Men� yap�s�yla kullan�cdan talepler al�narak program i�leniyor.
// �lk olarak main()'de bo� bir kay�t olu�turuyorum i�ini NULL olarak tan�ml�yorum bundan sonraki i�lemlerde i�i doldurularak devam edecek program.

// "->" structer eleman�na, structer'� g�steren bir pointer ile ula��r.

struct kaydol{
    char isim[50];
    char soyisim[50];
    char telefonNumarasi[20];
    struct kaydol * birSonraki;
};

// Fonksiyonun �a�r�ld��� yerden "ilkKayit" de�i�ken bilgisini alarak, kullan�c�n�n ekledi�ini yeni kayd� "ilkKayit"'a ekler. Yeni kay�d�n "birSonraki" bilgisine �nceki "ilkKayit"'� tan�mlan�r. Sonu�ta yeni "ilkKayit" bilgisini d�nd�r�r.
// MA�N'DEN ilkKayit BURAYA G�NDER�LD�.
struct kaydol* ilkSirayaKisiEkle(struct kaydol *ilkKayit){
    // DAHA �NCE H�� K�MSE REHBERE EKLENMEM��SE �F BLO�UNA G�RER.
    if (ilkKayit == NULL){
    	// HAFIZADA YER A�ILDI VE KULLANICIDAN B�LG�LER ALINDI.
        ilkKayit = (struct kaydol*) malloc(sizeof(struct kaydol));
        printf("\n�sim yaz�n�z (Ali-Kadir-Mustafa): ");					scanf("%s",ilkKayit->isim);
        printf("Soyisim yaz�n�z (Ate�-Duvar-Kitap): ");					scanf("%s",ilkKayit->soyisim);
        printf("Telefon numaras�: ");									scanf("%s",ilkKayit->telefonNumarasi);
        // STRUCT'TA YER ALAN birSonraki KISMINA ilkKayit'� E��TLED�K.
		// B�YLEL�KLE TEK B�R K��� DAH� OLSA D�NG� KEND�S�N� G�STERECEK YAN� �LK EKLENEN K���Y� G�STER�YOR. SONU� OLARAK DA�RESEL YAPIYI KURDUK.
        ilkKayit->birSonraki = ilkKayit;	// TEK ELEMANLI OLDU�U ���N KEND� ADRES�N� G�STERD�.
        return ilkKayit;
        // ilkKayit main'de fonksiyonu �ag�rd�g�m�z ilk kayda e�itleniyor.
        // daireselde basa ekled�g�m �c�n her yen� eklenen kay�t ilkkayit oluyor.
    }
    else{
    	// HAFIZADA YER A�TIK.
        struct kaydol *newKayit = (struct kaydol*) malloc(sizeof(struct kaydol));
        // TELEFON NUMARALARININ �AKI�MA �HT�MAL�NE �ST�NADEN ayniTelefonNumarasi �SM�NDE DE���KEN OLU�TURULDU. 1 OLDU�U S�RECE KAYIT EKLENECEK.
        int ayniTelefonNumarasi =1;
        while(ayniTelefonNumarasi == 1){
            printf("\n�sim yaz�n�z (Ali-Kadir-Mustafa): ");				scanf("%s",newKayit->isim);
            printf("Soyisim yaz�n�z (Ate�-Duvar-Kitap): ");				scanf("%s",newKayit->soyisim);
            printf("Telefon numaras�: ");								scanf("%s",newKayit->telefonNumarasi);
            // birSonraki (SONRAK� DE���KEN�N ADRES�N� TUTUYOR) �S�ML� PO�NTER'A ilkKayit'�n ADRES� ATANDI.
            newKayit->birSonraki = ilkKayit;
            
            // telefonNumarasiSorgula FONKS�YONU SAYES�NDE AYNI NUMARANIN OLUP OLMADI�I KONTROL ED�L�YOR.
			ayniTelefonNumarasi = telefonNumarasiSorgula(ilkKayit, newKayit->telefonNumarasi);
			// telefonNumarasiSorgula isimli FONKS�YONUN DE�ER� 1 OLDU�U S�RECE D�NG� DEVAM EDER VE K��� EKLEN�R.
        }
        // araBul DE���KEN�YLE EKLENEN 2. , 3. ... KAYIT E��TLEN�YOR.
        struct kaydol * araBul = ilkKayit;
        while (araBul->birSonraki!=ilkKayit)
            araBul = araBul->birSonraki;
        // �LK EKLENEN K���N�N ADRES�N� BA�LIYORUZ KAYBOLMAMASI ���N. (ADRES�N� ATIYORUZ)
        araBul->birSonraki = newKayit;
        // BUNLAR B�RB�R�NE BA�LI OLDU�U ���N ilkKayit  ARTIK newKayit OLMU� OLUYOR.
        ilkKayit= newKayit;
        return ilkKayit;
        // BUNDAN SONRA S�REKL� AYNI ��LEM YAPILIYOR. birSonraki KISMINA �NCEK� K���N�N ADRES� EKLEN�YOR SONRADA ilkKayit OLARAK TANIMLANIYOR.
        // eklenen kay�tlar�n adresi s�rekli ilkKayit'�n adresine e�it oluyor.
        // son ekelnen kay�t adresi ilkKayit oluyor.
    }
}

// Rehberde yer alan her �ey g�sterilir.
void rehberEkrandaGoster(struct kaydol *ilkKayit){
	// ADRES�N� TUTUYORUZ.
    struct kaydol * araBul = ilkKayit;
    // ilkKayit DE���KEN� BO�SA YAN� K��� EKLENMEM��SE KULLANICIYA B�LG�LEND�RME MESAJI VER�L�YOR.
    if(ilkKayit == NULL){
        printf("\nTelefon rehberinde herhangi bir veriye ula��lamad�!\n\n");
        return;
    }
    // E�ER ilkKayit NULL DE��LSE DOLUYSA �LK K���N�N B�LG�LER�N� BURADA YAZDIRIYORUZ.
    printf("\n�sim Soyisim: %s %s \nTelefon Numaras�: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
    // araBul DE���KEN�, sonraki ADRES (SONRAK� K���) VARSA ONU BULUYOR.
	araBul = araBul->birSonraki;
	// B�RDEN FAZLA K��� VARSA A�A�IDAK� D�NG� �ALI�IR.
    while(araBul != ilkKayit){
    	// B�RDEN FAZLA K��� VARSA ONLARIDA BURADA YAZDIRIYORUZ
        printf("\n�sim Soyisim: %s %s \nTelefon Numaras�: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
        // araBul DE���KEN� SONRAK� ADRES (SONRAK� K���) VARSA ONU BULUYOR. BULAMAYANA KADAR D�NG� DEVAM EDER.
		araBul = araBul->birSonraki;
    }
}

// Rehber ayn� telefon numaras�n�n olup olmad���n�n kontrolu yap�l�r.
int telefonNumarasiSorgula(struct kaydol *ilkKayit, char telefonNumarasi[]){
    char telefonRehberindekiNumara[20];
    // ADRES�N� TUTUYORUZ.
    struct kaydol * araBul = ilkKayit;
    
    // strcpy() fonksiyonu --> �kinci parametre, birinci parametreye kopyalan�r.
    // kontrolEtChar FONKS�YONUNDA KULLANMAK ���N KOPYALAMA ��LEM� GER�EKLE�T�R�LD�.
    strcpy(telefonRehberindekiNumara, araBul->telefonNumarasi);
    
    // "kontrolEtChar" FONKS�YONU 0 DE�ER�N� D�ND�R�RSE TELEFON REHBER�NDE O NUMARA BULUNMU� DEMEKT�R.
    int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, telefonNumarasi);
    if(telefonNumarasiKarsilastirma == 0 ){
        printf("\nTelefon numaras� daha �nce kaydedilmi�. Tekrar deneyiniz.\n");
        return 1;
    }
    // araBul DE���KEN�, SONRAK� ADRES (SONRAK� K���) VARSA ONU BULUYOR.
    araBul = araBul->birSonraki;
    // B�RDEN FAZLA K��� VARSA A�A�IDAK� D�NG�YE G�RER�Z. SONRAK� K���Y� BULANA KADAR D�NG� D�NER.
    while(araBul != ilkKayit){
        char telefonRehberindekiNumara[20];

        // strcpy() fonksiyonu --> �kinci parametre, birinci parametreye kopyalan�r.
		// kontrolEtChar FONKS�YONUNDA KULLANMAK ���N KOPYALAMA ��LEM� GER�EKLE�T�R�LD�.
        strcpy(telefonRehberindekiNumara, araBul->telefonNumarasi);

        // "kontrolEtChar" FONKS�YONU 0 DE�ER�N� D�ND�R�RSE TELEFON REHBER�NDE O NUMARA BULUNMU� DEMEKT�R.
        int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, telefonNumarasi);
        if(telefonNumarasiKarsilastirma == 0 ){
        	// printf fonksiyonu ile ekranda bilgilendirme mesaj� verilir.
            printf("\nTelefon numaras� daha �nce kaydedilmi�. Tekrar deneyiniz.\n");
            return 1;
        }
        // araBul DE���KEN� SONRAK� ADRES (SONRAK� K���) VARSA ONU BULUYOR. BULAMAYANA KADAR D�NG� DEVAM EDER.
        araBul = araBul->birSonraki;
    }
   return 0;
}

// Telefon rehberinden telefon numaras� girilerek araman�n ger�ekle�tirilmesi.
void telefonNumarasiylaAramaYap(struct kaydol *ilkKayit, char aranacakTelNo[]){
    char telefonRehberindekiNumara[20];
    // araBul DE���KEN� OLU�TURULUP ilkKayit BUNA E��TLEND�.
    struct kaydol * araBul = ilkKayit;
    // kontrolEtChar FONKS�YONUNDA KULLANMAK ���N KOPYALAMA ��LEM� GER�EKLE�T�R�LD�.
    strcpy(telefonRehberindekiNumara, araBul->telefonNumarasi);

	// "kontrolEtChar" FONKS�YONU 0 DE�ER�N� D�ND�R�RSE TELEFON REHBER�NDE O NUMARA BULUNMU� DEMEKT�R.
    int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, aranacakTelNo);
    if(telefonNumarasiKarsilastirma == 0 ){
    	// BULUNAN �LK K��� YAZDIRILIR.
        printf("\n�sim Soyisim: %s %s \nTelefon Numaras�: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
        return;
    }
    
    // araBul DE���KEN� SONRAK� ADRES (SONRAK� K���) VARSA ONU BULUYOR.
    araBul = araBul->birSonraki;
    
	// ARANAN NUMARA �LK K���YE A�T DE��LSE A�A�IDAK� D�NG�YE G�RER�Z.
    while(araBul != ilkKayit){
        char telefonRehberindekiNumara[20];
    	// kontrolEtChar FONKS�YONUNDA KULLANMAK ���N KOPYALAMA ��LEM� GER�EKLE�T�R�LD�.
        strcpy(telefonRehberindekiNumara, araBul->telefonNumarasi);
        
		// "kontrolEtChar" FONKS�YONU 0 DE�ER�N� D�ND�R�RSE TELEFON REHBER�NDE O NUMARA BULUNMU� DEMEKT�R.
        int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, aranacakTelNo);
        if(telefonNumarasiKarsilastirma == 0 ){
        	// BULUNAN 2. , 3. , 4. ... K��� EKRANA YAZDIRILIR.
            printf("\n\n�sim Soyisim: %s %s \nTelefon Numaras�: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
            return;
        }
        // araBul DE���KEN� SONRAK� ADRES (SONRAK� K���) VARSA ONU BULUYOR. BULAMAYANA KADAR D�NG� DEVAM EDER.
        araBul = araBul->birSonraki;
    }
    printf("\n\nE�le�mi� herhangi bir ki�iye rastlanmad�.\n\n");
}

// Telefon rehberinden telefon numaras� girilerek ki�inin silinmesi.
// Neden 2 ayr� silme i�lemi var birisinde dairesel ba�� koparmamak i�in b�yle yap�l�yor.
struct kaydol* kayitSil(struct kaydol *ilkKayit, char silmekIstenilenTelefonNumarasi[]){
    char telefonRehberindekiNumara[20];
    // araBul DE���KEN� OLU�TURULUP ilkKayit BUNA E��TLEND�.
    struct kaydol * araBul = ilkKayit;

    // kontrolEtChar FONKS�YONUNDA KULLANMAK ���N KOPYALAMA ��LEM� GER�EKLE�T�R�LD�.
    strcpy(telefonRehberindekiNumara, araBul->telefonNumarasi);
    
	// �LK K���Y� S�LECEKSEK BU BLOK �ALI�IR ************************************************************
	// "kontrolEtChar" FONKS�YONU 0 DE�ER D�ND�R�RSE G�R�LEN TELEFON NUMARASIYLA KAR�ILA�ILMI� DEMEKT�R.
    int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, silmekIstenilenTelefonNumarasi);
    if(telefonNumarasiKarsilastirma == 0 ){
    	// BURDAK� D�NG�YLE SON ELEMAN (K���) ARANIYOR. NEDEN SON K��� BULUNUYOR? �LK K���Y� S�LECE��M�Z ���N SON K���YLE ARASINDAK� DA�RESEL BA�I KOPARMAMALIYIZ.
        while (araBul->birSonraki !=ilkKayit){	
            araBul = araBul->birSonraki;		// SON ELEMAN BULUNUYOR.
        }
        // DA�RESEL BA�I KOPARMAMAK ���N �LK K���N�N ADRES� SON K���N�N ADRES�NE ATANIYOR.
        araBul->birSonraki =ilkKayit->birSonraki;
        
        // free() fonksiyonunun kullan�m� hakk�nda bilgi. malloc() fonksiyonu ile tahsis edilen belle�i bo�alt�r.
        free(ilkKayit);						// TUTULAN �LK K���N�N ADRES� BO�ALTILIR.
        
        ilkKayit = araBul->birSonraki;		// ilkKayit'�n ADRES� NORMALDE BO� ��NK� S�LD�K. BURADA araBul'un BULDU�U SON K���N�N ADRES�N� ATIYORUZ.
        printf("\n%s numaral� telefon numaras� silindi.\n\n", silmekIstenilenTelefonNumarasi);
        return ilkKayit;
    }
	// ARADAN VEYAHUT SONDAN S�LME ��LEM� ************************************************************
    while(araBul->birSonraki != ilkKayit){
        char telefonRehberindekiNumara[20];
        
        // kontrolEtChar FONKS�YONUNDA KULLANMAK ���N KOPYALAMA ��LEM� GER�EKLE�T�R�LD�.
        strcpy(telefonRehberindekiNumara, araBul->birSonraki->telefonNumarasi);
        
		// "kontrolEtChar" FONKS�YONU 0 DE�ER D�ND�R�RSE G�R�LEN TELEFON NUMARASIYLA KAR�ILA�ILMI� DEMEKT�R.
        int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, silmekIstenilenTelefonNumarasi);
    	if(telefonNumarasiKarsilastirma == 0 ){
			struct kaydol * temp;			// S�L�NECEK K��� ���N GE��C� B�R DE���KEN OLU�TURULDU.
            temp=araBul->birSonraki;		// S�L�NECEK ��E GE��C� B�R DE���KENE ATANDI.
            araBul->birSonraki = araBul->birSonraki->birSonraki;	// S�L�NECEK ��EN�N �NCES�YLE SONRASININ ADRESLER� BA�LANIYOR.
            free(temp);						// S�L�NECEK ��E S�L�ND�.
            printf("\n%s numaral� telefon numaras� silindi.\n\n", silmekIstenilenTelefonNumarasi);
            return ilkKayit;
        }
        araBul = araBul->birSonraki;		// D�NG�N�N ���NDE BULAMAZSA araBul B�RSONRAK� KAYDI HAREKET ETT�R�YOR.
	}
    printf("\n\nHerhangi bir veriye ula��lamad�!\n\n");
    return ilkKayit;
}

// Rehberde arama yapmam�za (isim-soyisme g�re) yarayan fonksiyon.
void isimSoyisimRehberdeBul(struct kaydol *ilkKayit, char isim[], char soyisim[]){
    char rehberdekiIsim[50],rehberdekiSoyisim[50];
    struct kaydol * araBul = ilkKayit;
    
    // kontrolEtChar FONKS�YONUNDA KULLANMAK ���N KOPYALAMA ��LEM� GER�EKLE�T�R�LD�.
    strcpy(rehberdekiIsim, araBul->isim);
    strcpy(rehberdekiSoyisim, araBul->soyisim);

	// "kontrolEtChar" FONKS�YONU 0 DE�ER D�ND�R�RSE G�R�LEN �S�M-SOY�S�MLE KAR�ILA�ILMI� DEMEKT�R.
    int isimleriKarsilastir = kontrolEtChar(rehberdekiIsim, isim);
    int soyisimleriKarsilastir = kontrolEtChar(rehberdekiSoyisim, soyisim);
    if(isimleriKarsilastir == 0 && soyisimleriKarsilastir == 0){
    	// Bulunan isim ve soyisim ekrana yazd�l�r.
        printf("\n�sim Soyisim: %s %s \nTelefon Numaras�: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
        printf("****************************************************************************************************\n\n");
        return;
    }

    araBul = araBul->birSonraki;		// D�NG�N�N ���NDE BULAMAZSA araBul B�RSONRAK� KAYDI HAREKET ETT�R�YOR.

    while(araBul != ilkKayit){
    	// kontrolEtChar FONKS�YONUNDA KULLANMAK ���N KOPYALAMA ��LEM� GER�EKLE�T�R�LD�.
        strcpy(rehberdekiIsim, araBul->isim);
        strcpy(rehberdekiSoyisim, araBul->soyisim);
        
	// "kontrolEtChar" FONKS�YONU 0 DE�ER D�ND�R�RSE G�R�LEN �S�M-SOY�S�MLE KAR�ILA�ILMI� DEMEKT�R.
        int isimleriKarsilastir = kontrolEtChar(rehberdekiIsim, isim);
        int soyisimleriKarsilastir = kontrolEtChar(rehberdekiSoyisim, soyisim);
        if(isimleriKarsilastir == 0 && soyisimleriKarsilastir == 0){
        	// Bulunan isim ve soyisim ekrana yazd�l�r.
            printf("\n\n�sim Soyisim: %s %s \nTelefon Numaras�: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
            return;
        }
        araBul = araBul->birSonraki;	// D�NG�N�N ���NDE BULAMAZSA araBul B�RSONRAK� KAYDI HAREKET ETT�R�YOR.
    }
    printf("\n\nE�le�mi� herhangi bir ki�iye rastlanmad�.\n\n");
}

// Char (isim-soyisim) verilerinin ayn� olup olmad���n� kar��la�t�ran fonksiyon.
int kontrolEtChar(char a[], char b[]){
    int tempNumber=1;
    // �ZETLE "tempNumber" DE�ER� 0 �SE AYNI, DE��LSE FARKLIDIR.
    int i=0; char g[50];
	int q = 0;
    while (a[i] == b[i])	// �S�MLER KAR�ILA�TIRILIYOR.
        if (a[i++] == '\0') // HAFIZADAN AYRILAN D�Z�N�N SONUNA YAN� HASAN YAZDIK D�YEL�M N HARF�NDEN SONRA \0 YAZILIYOR BU DA B�TT���N� G�STER�YOR.
            return(0);		// D�NG�DEN �IKAR VE 0 D�NER.
    return tempNumber;
}

// Telefon rehberi soyisimlere g�re s�ralan�r.
void soyismeGoreSirala(struct kaydol *ilkKayit){
	int yerDegistirildi, i;
	struct kaydol *ilkPointer;
	struct kaydol *ikinciPointer = NULL;
	if (ilkKayit == NULL){
        return;
    }
	do{
		// ilk �nce ilkKayit yap�l�r B�T�N FONKS�YONLARDA YAPILDI
		// dairesel oldu�u i�in ilk �nce ilkKayit'� d��arda d�ng�n�n d���nda i�liyoruz. Dairesel olmasayd� d�ng� NULL'u g�r�nce duraca�� i�in do�rusalda direk d�ng�ye girilebilirdi.
		yerDegistirildi = 0;
		ilkPointer = ilkKayit;
		// strcmp() FONKS�YONUNUN KULLANIMI HAKKINDA B�LG�
		// int strcmp(const char *str1, const char *str2);
		// Str1 parametresi ile g�sterilen karakter dizisini str2 parametresi ile g�sterilen karakter dizisi ile kar��la�t�r�r.
		// E�er her iki karakter dizisindeki t�m karakterler ayn� ise s�f�r de�eri, aksi takdirde s�f�rdan farkl� bir de�er geri d�nd�r�r.
		if (strcmp(ilkPointer->soyisim,ilkPointer->birSonraki->soyisim)>0){ // ayn� isim ��karsa 0 d�n�yor ama �s�m soy�s�m farkl�ysa �slem gerceklest�r�l�yor
					yerDegistir(ilkPointer, ilkPointer->birSonraki);		// - ��karsa s�ralama zaten dogurudur
					yerDegistirildi = 1;
				}

			ilkPointer = ilkPointer->birSonraki;
		// ilkKayit d�ng� g�r�rse durur o y�zden d�ngu yap�alcak her fonksy�onda d�sarda ilkKayit a i�lem yap�p ilkPointer/araBul birSonraki kayda e�leyip d�nguye g�r�yoruz
		while (ilkPointer->birSonraki != ilkKayit){
				if (strcmp(ilkPointer->soyisim,ilkPointer->birSonraki->soyisim)>0){
					yerDegistir(ilkPointer, ilkPointer->birSonraki);
					yerDegistirildi = 1;
				}
			ilkPointer = ilkPointer->birSonraki;
		}
		ikinciPointer = ilkPointer;
	}
	while (yerDegistirildi);
    printf("\nSoyisimlerine g�re s�ralama ger�ekle�tirildi.\n");
}

// Rehberdeki kay�tlar�n yerlerini de�i�tirmek i�in yaz�lm�� fonksiyon.
void yerDegistir(struct kaydol *degistir1, struct kaydol *degistir2){
    char geciciIsim[50],geciciSoyisim[50];
    char geciciTelefonNumarasi[15];
    strcpy(geciciIsim,degistir1->isim);
	strcpy(degistir1->isim,degistir2->isim);
	strcpy(degistir2->isim,geciciIsim);
	strcpy(geciciSoyisim,degistir1->soyisim);
	strcpy(degistir1->soyisim,degistir2->soyisim);
	strcpy(degistir2->soyisim,geciciSoyisim);
	strcpy(geciciTelefonNumarasi,degistir1->telefonNumarasi);
	strcpy(degistir1->telefonNumarasi,degistir2->telefonNumarasi);
	strcpy(degistir2->telefonNumarasi,geciciTelefonNumarasi);
}

int main (){
	setlocale(LC_ALL, "Turkish");
	// ilkKayit'� D�NG�YE SOKARSAK D�NG� �ALI�MAZ O Y�ZDEN ilkKayit'� DI�ARDA YAPIYORUZ.
    struct kaydol * ilkKayit = NULL;	// "ilkKayit" de�erine NULL de�er atand�.
    int yapilacakIslemSecimi;
    char isim[50];
    char soyisim[50];
    do{
        printf("1 - Telefon rehberine veri giri�i yapmak i�in 1'e bas�n�z. \n");
        printf("2 - Telefon rehberinde isme g�re arama yapmak i�in 2'ye bas�n�z. \n");
        printf("3 - Telefon numarasiyla arama yapmak i�in 3'e bas�n�z. \n");
        printf("4 - Telefon rehberini g�rmek i�in 4'e bas�n�z.' \n");
        printf("5 - Telefon rehberini soyisimlerine g�re g�rmek i�in 5'e bas�n�z. \n");
        printf("6 - Telefon rehberiniden telefon numaras� girerek kay�t silmek i�in 6'ya bas�n�z. \n");
        printf("7 - ��k��! \n");
        printf("\nL�tfen ger�ekle�tirmek istedi�iniz i�lemin numaras�n� tu�lay�n�z: ");			scanf("%d", &yapilacakIslemSecimi);

        // 1
        if (yapilacakIslemSecimi == 1){
        	// Yeni eklenen veri ("ilkKayit") ilkSirayaKisiEkle fonksiyonuna aktar�larak ilk de�er yerine ge�er.
            ilkKayit = ilkSirayaKisiEkle(ilkKayit);
            //system("CLS");
            printf("\nTelefon rehberine bir ki�i ba�ar�yla eklendi.\n\n");
        }
        // 2
        if (yapilacakIslemSecimi == 2){
            if(ilkKayit == NULL){
                printf("\nHerhangi bir veriye ula��lamad�!\n\n");
            }
            else{
                printf("\nAramak istedi�iniz ki�inin ismini yaz�n�z: ");			scanf("%s", isim);
                printf("Aramak istedi�iniz ki�inin soyisminini yaz�n�z: ");			scanf("%s", soyisim);
                isimSoyisimRehberdeBul(ilkKayit,isim,soyisim);
            }
        }
        // 3
        if (yapilacakIslemSecimi == 3){
            if(ilkKayit == NULL){
                printf("\nHerhangi bir veriye ula��lamad�!\n\n");
            }
            else{
                char aranacakTelNo[15];
                printf("\nAramak istedi�iniz ki�inin telefon numaras�n� tu�lay�n�z: ");			scanf("%s",aranacakTelNo);
                telefonNumarasiylaAramaYap(ilkKayit,aranacakTelNo);
            }
        }
        // 4
        if (yapilacakIslemSecimi == 4){
            rehberEkrandaGoster(ilkKayit);
        }
        // 5
        if (yapilacakIslemSecimi == 5){
            soyismeGoreSirala(ilkKayit);
            rehberEkrandaGoster(ilkKayit);
        }
        // 6
        if (yapilacakIslemSecimi == 6){
            if(ilkKayit == NULL){
                printf("\nHerhangi bir veriye ula��lamad�!\n\n");
            }
            else{
                char silmekIstenilenTelefonNumarasi[15];
                printf("\nSilmek istedi�iniz telefon numaras�n� tu�lay�n�z: ");					scanf("%s",silmekIstenilenTelefonNumarasi);
                ilkKayit = kayitSil(ilkKayit,silmekIstenilenTelefonNumarasi);
            }
        }
    }
    while(yapilacakIslemSecimi !=7);
    return 0;
}
