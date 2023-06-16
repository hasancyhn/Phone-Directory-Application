// HASAN CEYHAN 20010011091 - Veri Yapýlarý Dersi Telefon Rehber Uygulamasý

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

// Kütüphanelerimi ekledim, kayýt tutacak olan struct yapýmý oluþturdum. 				Telefon numarasý neden int deðil çünkü C'de int üzerinde gezmek zor.
// Bir tane main() fonksiyonum var içinde menü yapýsý var. Menü yapýsýyla kullanýcdan talepler alýnarak program iþleniyor.
// Ýlk olarak main()'de boþ bir kayýt oluþturuyorum içini NULL olarak tanýmlýyorum bundan sonraki iþlemlerde içi doldurularak devam edecek program.

// "->" structer elemanýna, structer'ý gösteren bir pointer ile ulaþýr.

struct kaydol{
    char isim[50];
    char soyisim[50];
    char telefonNumarasi[20];
    struct kaydol * birSonraki;
};

// Fonksiyonun çaðrýldýðý yerden "ilkKayit" deðiþken bilgisini alarak, kullanýcýnýn eklediðini yeni kaydý "ilkKayit"'a ekler. Yeni kayýdýn "birSonraki" bilgisine önceki "ilkKayit"'ý tanýmlanýr. Sonuçta yeni "ilkKayit" bilgisini döndürür.
// MAÝN'DEN ilkKayit BURAYA GÖNDERÝLDÝ.
struct kaydol* ilkSirayaKisiEkle(struct kaydol *ilkKayit){
    // DAHA ÖNCE HÝÇ KÝMSE REHBERE EKLENMEMÝÞSE ÝF BLOÐUNA GÝRER.
    if (ilkKayit == NULL){
    	// HAFIZADA YER AÇILDI VE KULLANICIDAN BÝLGÝLER ALINDI.
        ilkKayit = (struct kaydol*) malloc(sizeof(struct kaydol));
        printf("\nÝsim yazýnýz (Ali-Kadir-Mustafa): ");					scanf("%s",ilkKayit->isim);
        printf("Soyisim yazýnýz (Ateþ-Duvar-Kitap): ");					scanf("%s",ilkKayit->soyisim);
        printf("Telefon numarasý: ");									scanf("%s",ilkKayit->telefonNumarasi);
        // STRUCT'TA YER ALAN birSonraki KISMINA ilkKayit'ý EÞÝTLEDÝK.
		// BÖYLELÝKLE TEK BÝR KÝÞÝ DAHÝ OLSA DÖNGÜ KENDÝSÝNÝ GÖSTERECEK YANÝ ÝLK EKLENEN KÝÞÝYÝ GÖSTERÝYOR. SONUÇ OLARAK DAÝRESEL YAPIYI KURDUK.
        ilkKayit->birSonraki = ilkKayit;	// TEK ELEMANLI OLDUÐU ÝÇÝN KENDÝ ADRESÝNÝ GÖSTERDÝ.
        return ilkKayit;
        // ilkKayit main'de fonksiyonu çagýrdýgýmýz ilk kayda eþitleniyor.
        // daireselde basa ekledýgým ýcýn her yený eklenen kayýt ilkkayit oluyor.
    }
    else{
    	// HAFIZADA YER AÇTIK.
        struct kaydol *newKayit = (struct kaydol*) malloc(sizeof(struct kaydol));
        // TELEFON NUMARALARININ ÇAKIÞMA ÝHTÝMALÝNE ÝSTÝNADEN ayniTelefonNumarasi ÝSMÝNDE DEÐÝÞKEN OLUÞTURULDU. 1 OLDUÐU SÜRECE KAYIT EKLENECEK.
        int ayniTelefonNumarasi =1;
        while(ayniTelefonNumarasi == 1){
            printf("\nÝsim yazýnýz (Ali-Kadir-Mustafa): ");				scanf("%s",newKayit->isim);
            printf("Soyisim yazýnýz (Ateþ-Duvar-Kitap): ");				scanf("%s",newKayit->soyisim);
            printf("Telefon numarasý: ");								scanf("%s",newKayit->telefonNumarasi);
            // birSonraki (SONRAKÝ DEÐÝÞKENÝN ADRESÝNÝ TUTUYOR) ÝSÝMLÝ POÝNTER'A ilkKayit'ýn ADRESÝ ATANDI.
            newKayit->birSonraki = ilkKayit;
            
            // telefonNumarasiSorgula FONKSÝYONU SAYESÝNDE AYNI NUMARANIN OLUP OLMADIÐI KONTROL EDÝLÝYOR.
			ayniTelefonNumarasi = telefonNumarasiSorgula(ilkKayit, newKayit->telefonNumarasi);
			// telefonNumarasiSorgula isimli FONKSÝYONUN DEÐERÝ 1 OLDUÐU SÜRECE DÖNGÜ DEVAM EDER VE KÝÞÝ EKLENÝR.
        }
        // araBul DEÐÝÞKENÝYLE EKLENEN 2. , 3. ... KAYIT EÞÝTLENÝYOR.
        struct kaydol * araBul = ilkKayit;
        while (araBul->birSonraki!=ilkKayit)
            araBul = araBul->birSonraki;
        // ÝLK EKLENEN KÝÞÝNÝN ADRESÝNÝ BAÐLIYORUZ KAYBOLMAMASI ÝÇÝN. (ADRESÝNÝ ATIYORUZ)
        araBul->birSonraki = newKayit;
        // BUNLAR BÝRBÝRÝNE BAÐLI OLDUÐU ÝÇÝN ilkKayit  ARTIK newKayit OLMUÞ OLUYOR.
        ilkKayit= newKayit;
        return ilkKayit;
        // BUNDAN SONRA SÜREKLÝ AYNI ÝÞLEM YAPILIYOR. birSonraki KISMINA ÖNCEKÝ KÝÞÝNÝN ADRESÝ EKLENÝYOR SONRADA ilkKayit OLARAK TANIMLANIYOR.
        // eklenen kayýtlarýn adresi sürekli ilkKayit'ýn adresine eþit oluyor.
        // son ekelnen kayýt adresi ilkKayit oluyor.
    }
}

// Rehberde yer alan her þey gösterilir.
void rehberEkrandaGoster(struct kaydol *ilkKayit){
	// ADRESÝNÝ TUTUYORUZ.
    struct kaydol * araBul = ilkKayit;
    // ilkKayit DEÐÝÞKENÝ BOÞSA YANÝ KÝÞÝ EKLENMEMÝÞSE KULLANICIYA BÝLGÝLENDÝRME MESAJI VERÝLÝYOR.
    if(ilkKayit == NULL){
        printf("\nTelefon rehberinde herhangi bir veriye ulaþýlamadý!\n\n");
        return;
    }
    // EÐER ilkKayit NULL DEÐÝLSE DOLUYSA ÝLK KÝÞÝNÝN BÝLGÝLERÝNÝ BURADA YAZDIRIYORUZ.
    printf("\nÝsim Soyisim: %s %s \nTelefon Numarasý: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
    // araBul DEÐÝÞKENÝ, sonraki ADRES (SONRAKÝ KÝÞÝ) VARSA ONU BULUYOR.
	araBul = araBul->birSonraki;
	// BÝRDEN FAZLA KÝÞÝ VARSA AÞAÐIDAKÝ DÖNGÜ ÇALIÞIR.
    while(araBul != ilkKayit){
    	// BÝRDEN FAZLA KÝÞÝ VARSA ONLARIDA BURADA YAZDIRIYORUZ
        printf("\nÝsim Soyisim: %s %s \nTelefon Numarasý: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
        // araBul DEÐÝÞKENÝ SONRAKÝ ADRES (SONRAKÝ KÝÞÝ) VARSA ONU BULUYOR. BULAMAYANA KADAR DÖNGÜ DEVAM EDER.
		araBul = araBul->birSonraki;
    }
}

// Rehber ayný telefon numarasýnýn olup olmadýðýnýn kontrolu yapýlýr.
int telefonNumarasiSorgula(struct kaydol *ilkKayit, char telefonNumarasi[]){
    char telefonRehberindekiNumara[20];
    // ADRESÝNÝ TUTUYORUZ.
    struct kaydol * araBul = ilkKayit;
    
    // strcpy() fonksiyonu --> Ýkinci parametre, birinci parametreye kopyalanýr.
    // kontrolEtChar FONKSÝYONUNDA KULLANMAK ÝÇÝN KOPYALAMA ÝÞLEMÝ GERÇEKLEÞTÝRÝLDÝ.
    strcpy(telefonRehberindekiNumara, araBul->telefonNumarasi);
    
    // "kontrolEtChar" FONKSÝYONU 0 DEÐERÝNÝ DÖNDÜRÜRSE TELEFON REHBERÝNDE O NUMARA BULUNMUÞ DEMEKTÝR.
    int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, telefonNumarasi);
    if(telefonNumarasiKarsilastirma == 0 ){
        printf("\nTelefon numarasý daha önce kaydedilmiþ. Tekrar deneyiniz.\n");
        return 1;
    }
    // araBul DEÐÝÞKENÝ, SONRAKÝ ADRES (SONRAKÝ KÝÞÝ) VARSA ONU BULUYOR.
    araBul = araBul->birSonraki;
    // BÝRDEN FAZLA KÝÞÝ VARSA AÞAÐIDAKÝ DÖNGÜYE GÝRERÝZ. SONRAKÝ KÝÞÝYÝ BULANA KADAR DÖNGÜ DÖNER.
    while(araBul != ilkKayit){
        char telefonRehberindekiNumara[20];

        // strcpy() fonksiyonu --> Ýkinci parametre, birinci parametreye kopyalanýr.
		// kontrolEtChar FONKSÝYONUNDA KULLANMAK ÝÇÝN KOPYALAMA ÝÞLEMÝ GERÇEKLEÞTÝRÝLDÝ.
        strcpy(telefonRehberindekiNumara, araBul->telefonNumarasi);

        // "kontrolEtChar" FONKSÝYONU 0 DEÐERÝNÝ DÖNDÜRÜRSE TELEFON REHBERÝNDE O NUMARA BULUNMUÞ DEMEKTÝR.
        int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, telefonNumarasi);
        if(telefonNumarasiKarsilastirma == 0 ){
        	// printf fonksiyonu ile ekranda bilgilendirme mesajý verilir.
            printf("\nTelefon numarasý daha önce kaydedilmiþ. Tekrar deneyiniz.\n");
            return 1;
        }
        // araBul DEÐÝÞKENÝ SONRAKÝ ADRES (SONRAKÝ KÝÞÝ) VARSA ONU BULUYOR. BULAMAYANA KADAR DÖNGÜ DEVAM EDER.
        araBul = araBul->birSonraki;
    }
   return 0;
}

// Telefon rehberinden telefon numarasý girilerek aramanýn gerçekleþtirilmesi.
void telefonNumarasiylaAramaYap(struct kaydol *ilkKayit, char aranacakTelNo[]){
    char telefonRehberindekiNumara[20];
    // araBul DEÐÝÞKENÝ OLUÞTURULUP ilkKayit BUNA EÞÝTLENDÝ.
    struct kaydol * araBul = ilkKayit;
    // kontrolEtChar FONKSÝYONUNDA KULLANMAK ÝÇÝN KOPYALAMA ÝÞLEMÝ GERÇEKLEÞTÝRÝLDÝ.
    strcpy(telefonRehberindekiNumara, araBul->telefonNumarasi);

	// "kontrolEtChar" FONKSÝYONU 0 DEÐERÝNÝ DÖNDÜRÜRSE TELEFON REHBERÝNDE O NUMARA BULUNMUÞ DEMEKTÝR.
    int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, aranacakTelNo);
    if(telefonNumarasiKarsilastirma == 0 ){
    	// BULUNAN ÝLK KÝÞÝ YAZDIRILIR.
        printf("\nÝsim Soyisim: %s %s \nTelefon Numarasý: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
        return;
    }
    
    // araBul DEÐÝÞKENÝ SONRAKÝ ADRES (SONRAKÝ KÝÞÝ) VARSA ONU BULUYOR.
    araBul = araBul->birSonraki;
    
	// ARANAN NUMARA ÝLK KÝÞÝYE AÝT DEÐÝLSE AÞAÐIDAKÝ DÖNGÜYE GÝRERÝZ.
    while(araBul != ilkKayit){
        char telefonRehberindekiNumara[20];
    	// kontrolEtChar FONKSÝYONUNDA KULLANMAK ÝÇÝN KOPYALAMA ÝÞLEMÝ GERÇEKLEÞTÝRÝLDÝ.
        strcpy(telefonRehberindekiNumara, araBul->telefonNumarasi);
        
		// "kontrolEtChar" FONKSÝYONU 0 DEÐERÝNÝ DÖNDÜRÜRSE TELEFON REHBERÝNDE O NUMARA BULUNMUÞ DEMEKTÝR.
        int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, aranacakTelNo);
        if(telefonNumarasiKarsilastirma == 0 ){
        	// BULUNAN 2. , 3. , 4. ... KÝÞÝ EKRANA YAZDIRILIR.
            printf("\n\nÝsim Soyisim: %s %s \nTelefon Numarasý: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
            return;
        }
        // araBul DEÐÝÞKENÝ SONRAKÝ ADRES (SONRAKÝ KÝÞÝ) VARSA ONU BULUYOR. BULAMAYANA KADAR DÖNGÜ DEVAM EDER.
        araBul = araBul->birSonraki;
    }
    printf("\n\nEþleþmiþ herhangi bir kiþiye rastlanmadý.\n\n");
}

// Telefon rehberinden telefon numarasý girilerek kiþinin silinmesi.
// Neden 2 ayrý silme iþlemi var birisinde dairesel baðý koparmamak için böyle yapýlýyor.
struct kaydol* kayitSil(struct kaydol *ilkKayit, char silmekIstenilenTelefonNumarasi[]){
    char telefonRehberindekiNumara[20];
    // araBul DEÐÝÞKENÝ OLUÞTURULUP ilkKayit BUNA EÞÝTLENDÝ.
    struct kaydol * araBul = ilkKayit;

    // kontrolEtChar FONKSÝYONUNDA KULLANMAK ÝÇÝN KOPYALAMA ÝÞLEMÝ GERÇEKLEÞTÝRÝLDÝ.
    strcpy(telefonRehberindekiNumara, araBul->telefonNumarasi);
    
	// ÝLK KÝÞÝYÝ SÝLECEKSEK BU BLOK ÇALIÞIR ************************************************************
	// "kontrolEtChar" FONKSÝYONU 0 DEÐER DÖNDÜRÜRSE GÝRÝLEN TELEFON NUMARASIYLA KARÞILAÞILMIÞ DEMEKTÝR.
    int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, silmekIstenilenTelefonNumarasi);
    if(telefonNumarasiKarsilastirma == 0 ){
    	// BURDAKÝ DÖNGÜYLE SON ELEMAN (KÝÞÝ) ARANIYOR. NEDEN SON KÝÞÝ BULUNUYOR? ÝLK KÝÞÝYÝ SÝLECEÐÝMÝZ ÝÇÝN SON KÝÞÝYLE ARASINDAKÝ DAÝRESEL BAÐI KOPARMAMALIYIZ.
        while (araBul->birSonraki !=ilkKayit){	
            araBul = araBul->birSonraki;		// SON ELEMAN BULUNUYOR.
        }
        // DAÝRESEL BAÐI KOPARMAMAK ÝÇÝN ÝLK KÝÞÝNÝN ADRESÝ SON KÝÞÝNÝN ADRESÝNE ATANIYOR.
        araBul->birSonraki =ilkKayit->birSonraki;
        
        // free() fonksiyonunun kullanýmý hakkýnda bilgi. malloc() fonksiyonu ile tahsis edilen belleði boþaltýr.
        free(ilkKayit);						// TUTULAN ÝLK KÝÞÝNÝN ADRESÝ BOÞALTILIR.
        
        ilkKayit = araBul->birSonraki;		// ilkKayit'ýn ADRESÝ NORMALDE BOÞ ÇÜNKÜ SÝLDÝK. BURADA araBul'un BULDUÐU SON KÝÞÝNÝN ADRESÝNÝ ATIYORUZ.
        printf("\n%s numaralý telefon numarasý silindi.\n\n", silmekIstenilenTelefonNumarasi);
        return ilkKayit;
    }
	// ARADAN VEYAHUT SONDAN SÝLME ÝÞLEMÝ ************************************************************
    while(araBul->birSonraki != ilkKayit){
        char telefonRehberindekiNumara[20];
        
        // kontrolEtChar FONKSÝYONUNDA KULLANMAK ÝÇÝN KOPYALAMA ÝÞLEMÝ GERÇEKLEÞTÝRÝLDÝ.
        strcpy(telefonRehberindekiNumara, araBul->birSonraki->telefonNumarasi);
        
		// "kontrolEtChar" FONKSÝYONU 0 DEÐER DÖNDÜRÜRSE GÝRÝLEN TELEFON NUMARASIYLA KARÞILAÞILMIÞ DEMEKTÝR.
        int telefonNumarasiKarsilastirma = kontrolEtChar(telefonRehberindekiNumara, silmekIstenilenTelefonNumarasi);
    	if(telefonNumarasiKarsilastirma == 0 ){
			struct kaydol * temp;			// SÝLÝNECEK KÝÞÝ ÝÇÝN GEÇÝCÝ BÝR DEÐÝÞKEN OLUÞTURULDU.
            temp=araBul->birSonraki;		// SÝLÝNECEK ÖÐE GEÇÝCÝ BÝR DEÐÝÞKENE ATANDI.
            araBul->birSonraki = araBul->birSonraki->birSonraki;	// SÝLÝNECEK ÖÐENÝN ÖNCESÝYLE SONRASININ ADRESLERÝ BAÐLANIYOR.
            free(temp);						// SÝLÝNECEK ÖÐE SÝLÝNDÝ.
            printf("\n%s numaralý telefon numarasý silindi.\n\n", silmekIstenilenTelefonNumarasi);
            return ilkKayit;
        }
        araBul = araBul->birSonraki;		// DÖNGÜNÜN ÝÇÝNDE BULAMAZSA araBul BÝRSONRAKÝ KAYDI HAREKET ETTÝRÝYOR.
	}
    printf("\n\nHerhangi bir veriye ulaþýlamadý!\n\n");
    return ilkKayit;
}

// Rehberde arama yapmamýza (isim-soyisme göre) yarayan fonksiyon.
void isimSoyisimRehberdeBul(struct kaydol *ilkKayit, char isim[], char soyisim[]){
    char rehberdekiIsim[50],rehberdekiSoyisim[50];
    struct kaydol * araBul = ilkKayit;
    
    // kontrolEtChar FONKSÝYONUNDA KULLANMAK ÝÇÝN KOPYALAMA ÝÞLEMÝ GERÇEKLEÞTÝRÝLDÝ.
    strcpy(rehberdekiIsim, araBul->isim);
    strcpy(rehberdekiSoyisim, araBul->soyisim);

	// "kontrolEtChar" FONKSÝYONU 0 DEÐER DÖNDÜRÜRSE GÝRÝLEN ÝSÝM-SOYÝSÝMLE KARÞILAÞILMIÞ DEMEKTÝR.
    int isimleriKarsilastir = kontrolEtChar(rehberdekiIsim, isim);
    int soyisimleriKarsilastir = kontrolEtChar(rehberdekiSoyisim, soyisim);
    if(isimleriKarsilastir == 0 && soyisimleriKarsilastir == 0){
    	// Bulunan isim ve soyisim ekrana yazdýlýr.
        printf("\nÝsim Soyisim: %s %s \nTelefon Numarasý: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
        printf("****************************************************************************************************\n\n");
        return;
    }

    araBul = araBul->birSonraki;		// DÖNGÜNÜN ÝÇÝNDE BULAMAZSA araBul BÝRSONRAKÝ KAYDI HAREKET ETTÝRÝYOR.

    while(araBul != ilkKayit){
    	// kontrolEtChar FONKSÝYONUNDA KULLANMAK ÝÇÝN KOPYALAMA ÝÞLEMÝ GERÇEKLEÞTÝRÝLDÝ.
        strcpy(rehberdekiIsim, araBul->isim);
        strcpy(rehberdekiSoyisim, araBul->soyisim);
        
	// "kontrolEtChar" FONKSÝYONU 0 DEÐER DÖNDÜRÜRSE GÝRÝLEN ÝSÝM-SOYÝSÝMLE KARÞILAÞILMIÞ DEMEKTÝR.
        int isimleriKarsilastir = kontrolEtChar(rehberdekiIsim, isim);
        int soyisimleriKarsilastir = kontrolEtChar(rehberdekiSoyisim, soyisim);
        if(isimleriKarsilastir == 0 && soyisimleriKarsilastir == 0){
        	// Bulunan isim ve soyisim ekrana yazdýlýr.
            printf("\n\nÝsim Soyisim: %s %s \nTelefon Numarasý: %s\n\n",araBul->isim,araBul->soyisim,araBul->telefonNumarasi);
            return;
        }
        araBul = araBul->birSonraki;	// DÖNGÜNÜN ÝÇÝNDE BULAMAZSA araBul BÝRSONRAKÝ KAYDI HAREKET ETTÝRÝYOR.
    }
    printf("\n\nEþleþmiþ herhangi bir kiþiye rastlanmadý.\n\n");
}

// Char (isim-soyisim) verilerinin ayný olup olmadýðýný karþýlaþtýran fonksiyon.
int kontrolEtChar(char a[], char b[]){
    int tempNumber=1;
    // ÖZETLE "tempNumber" DEÐERÝ 0 ÝSE AYNI, DEÐÝLSE FARKLIDIR.
    int i=0; char g[50];
	int q = 0;
    while (a[i] == b[i])	// ÝSÝMLER KARÞILAÞTIRILIYOR.
        if (a[i++] == '\0') // HAFIZADAN AYRILAN DÝZÝNÝN SONUNA YANÝ HASAN YAZDIK DÝYELÝM N HARFÝNDEN SONRA \0 YAZILIYOR BU DA BÝTTÝÐÝNÝ GÖSTERÝYOR.
            return(0);		// DÖNGÜDEN ÇIKAR VE 0 DÖNER.
    return tempNumber;
}

// Telefon rehberi soyisimlere göre sýralanýr.
void soyismeGoreSirala(struct kaydol *ilkKayit){
	int yerDegistirildi, i;
	struct kaydol *ilkPointer;
	struct kaydol *ikinciPointer = NULL;
	if (ilkKayit == NULL){
        return;
    }
	do{
		// ilk önce ilkKayit yapýlýr BÜTÜN FONKSÝYONLARDA YAPILDI
		// dairesel olduðu için ilk önce ilkKayit'ý dýþarda döngünün dýþýnda iþliyoruz. Dairesel olmasaydý döngü NULL'u görünce duracaðý için doðrusalda direk döngüye girilebilirdi.
		yerDegistirildi = 0;
		ilkPointer = ilkKayit;
		// strcmp() FONKSÝYONUNUN KULLANIMI HAKKINDA BÝLGÝ
		// int strcmp(const char *str1, const char *str2);
		// Str1 parametresi ile gösterilen karakter dizisini str2 parametresi ile gösterilen karakter dizisi ile karþýlaþtýrýr.
		// Eðer her iki karakter dizisindeki tüm karakterler ayný ise sýfýr deðeri, aksi takdirde sýfýrdan farklý bir deðer geri döndürür.
		if (strcmp(ilkPointer->soyisim,ilkPointer->birSonraki->soyisim)>0){ // ayný isim çýkarsa 0 dönüyor ama ýsým soyýsým farklýysa ýslem gerceklestýrýlýyor
					yerDegistir(ilkPointer, ilkPointer->birSonraki);		// - çýkarsa sýralama zaten dogurudur
					yerDegistirildi = 1;
				}

			ilkPointer = ilkPointer->birSonraki;
		// ilkKayit döngü görürse durur o yüzden döngu yapýalcak her fonksyýonda dýsarda ilkKayit a iþlem yapýp ilkPointer/araBul birSonraki kayda eþleyip dönguye gýrýyoruz
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
    printf("\nSoyisimlerine göre sýralama gerçekleþtirildi.\n");
}

// Rehberdeki kayýtlarýn yerlerini deðiþtirmek için yazýlmýþ fonksiyon.
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
	// ilkKayit'ý DÖNGÜYE SOKARSAK DÖNGÜ ÇALIÞMAZ O YÜZDEN ilkKayit'ý DIÞARDA YAPIYORUZ.
    struct kaydol * ilkKayit = NULL;	// "ilkKayit" deðerine NULL deðer atandý.
    int yapilacakIslemSecimi;
    char isim[50];
    char soyisim[50];
    do{
        printf("1 - Telefon rehberine veri giriþi yapmak için 1'e basýnýz. \n");
        printf("2 - Telefon rehberinde isme göre arama yapmak için 2'ye basýnýz. \n");
        printf("3 - Telefon numarasiyla arama yapmak için 3'e basýnýz. \n");
        printf("4 - Telefon rehberini görmek için 4'e basýnýz.' \n");
        printf("5 - Telefon rehberini soyisimlerine göre görmek için 5'e basýnýz. \n");
        printf("6 - Telefon rehberiniden telefon numarasý girerek kayýt silmek için 6'ya basýnýz. \n");
        printf("7 - Çýkýþ! \n");
        printf("\nLütfen gerçekleþtirmek istediðiniz iþlemin numarasýný tuþlayýnýz: ");			scanf("%d", &yapilacakIslemSecimi);

        // 1
        if (yapilacakIslemSecimi == 1){
        	// Yeni eklenen veri ("ilkKayit") ilkSirayaKisiEkle fonksiyonuna aktarýlarak ilk deðer yerine geçer.
            ilkKayit = ilkSirayaKisiEkle(ilkKayit);
            //system("CLS");
            printf("\nTelefon rehberine bir kiþi baþarýyla eklendi.\n\n");
        }
        // 2
        if (yapilacakIslemSecimi == 2){
            if(ilkKayit == NULL){
                printf("\nHerhangi bir veriye ulaþýlamadý!\n\n");
            }
            else{
                printf("\nAramak istediðiniz kiþinin ismini yazýnýz: ");			scanf("%s", isim);
                printf("Aramak istediðiniz kiþinin soyisminini yazýnýz: ");			scanf("%s", soyisim);
                isimSoyisimRehberdeBul(ilkKayit,isim,soyisim);
            }
        }
        // 3
        if (yapilacakIslemSecimi == 3){
            if(ilkKayit == NULL){
                printf("\nHerhangi bir veriye ulaþýlamadý!\n\n");
            }
            else{
                char aranacakTelNo[15];
                printf("\nAramak istediðiniz kiþinin telefon numarasýný tuþlayýnýz: ");			scanf("%s",aranacakTelNo);
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
                printf("\nHerhangi bir veriye ulaþýlamadý!\n\n");
            }
            else{
                char silmekIstenilenTelefonNumarasi[15];
                printf("\nSilmek istediðiniz telefon numarasýný tuþlayýnýz: ");					scanf("%s",silmekIstenilenTelefonNumarasi);
                ilkKayit = kayitSil(ilkKayit,silmekIstenilenTelefonNumarasi);
            }
        }
    }
    while(yapilacakIslemSecimi !=7);
    return 0;
}
