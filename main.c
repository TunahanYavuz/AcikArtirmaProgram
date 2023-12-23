#include <stdio.h>
#include <locale.h>
#include <wchar.h>

typedef struct {            //structure ı tanımlıyoruz ve özelliklerini giriyoruz.
    wchar_t ProductName[40];
    unsigned int BidNumber;
    double LastPrice;
    double PriceIncrease[];
}Auction;


void Bid(Auction *product);
double Price(Auction *product);

int main() {
    Auction product;
    setlocale(LC_ALL,"Turkish");        //Türkçe mesajları verebilmek için bu kodu ve wprintf fonksiyonunu kullanıyoruz.
    wprintf(L"Lütfen Ürünün Adını Giriniz\n");
    wscanf(L" %ls", product.ProductName);      //Ürün adını alıyoruz.
    wprintf(L"İşlemler Dolar ($) Üzerinden Hesaplanmaktadır\n\tLütfen Ürünün Başlangıç Fiyatını Giriniz\n");
    scanf("%lf",&product.PriceIncrease[0]);            //Ürünün başlangıç fiyatını alıyoruz.
    Bid(&product);                         //Bid fonksiyonuyla açık artırmayı başlatıyoruz.

    if(Price(&product) != product.PriceIncrease[0])   //Ürün fiyatının başlangıç fiyatından farklı olduğunu kontrol ediyoruz.
        wprintf(L"Satın Alınan Ürün : %ls\nÖdenecek Fiyat : %.2lf$\nAçık Artırmayı Kazanan Numara : %d", product.ProductName,
                Price(&product), product.BidNumber - 1);
    else{                                                                                                   //Price fonksiyonuyla ürünün son fiyatını hesaplıyoruz.
        wprintf(L"Herhangi Bir Teklif Yapılmadı %s Adlı Ürün Satılamadı\n", product.ProductName);
    }
    return 0;
}



void Bid(Auction *product){
    wprintf(L"Açık Artırma Başladı\nArtık Gireceğiniz 0' dan Büyük Tüm Sayılar Ürünün Fiyatını Artıracaktır\nAçık Artırmayı Sonlandırmak İçin \"-1\" Değerini Giriniz\n");
    double price;           //Gerekli koşulları sağladığı zaman ürün fiyatını artıracak bir kontrolcü değişkeni atıyoruz.
    product->BidNumber=1;
    while(1) {      //Döngüye sokuyoruz.
        wprintf(L"Ürünün Anlık Fiyatı %.2lf$\n", Price(product));   //Anlık Ücreti Gösteriyoruz.
        wprintf(L"Lütfen Artım Miktarını Giriniz\n");
        if (!scanf("%lf", &price)) {        //Değerin sayı olduğunu kontrol ediyoruz.
            wprintf(L"Lütfen Sayı Giriniz\n");
            fflush(stdin);
        }
        if (price == -1) {      //-1 değeri girilince döngüyü kırıyoruz.
            wprintf(L"Açık Artırma Sona Erdi\n");
            break;
        } else if (price <= 0) {        //0 dan küçük sayı atamalarını kontrol ediyoruz.
            wprintf(L"Sadece 0' dan Büyük Sayılar Girebilirsiniz\n");
        } else {        //Gerekli koşullar sağlandığında girilen değeri ürüne atıyoruz.
            product->PriceIncrease[product->BidNumber] = price;
            ++product->BidNumber;   //Koşul her sağlandığında teklif sayısını 1 artırıyoruz.
        }
    }
}

double Price(Auction *product){     //Ücreti hesapladığımız fonksiyon.
    int i=1;
    product->LastPrice=product->PriceIncrease[0];   //Fonksiyonu birden fazla kez kullandığımız için her kullanışımızda fiyatı düzeltiyoruz.
    while(i!=product->BidNumber ) { //Son artırdığımız teklif sayısıyla BidNumber dizimizin değer girilen kısmından 1 fazla oluyor ve oraya gelene kadar girilen tüm değerleri topluyoruz.
    product->LastPrice+=product->PriceIncrease[i];
    i++;
    }

    return product->LastPrice;      //Ürünün fiyatını döndürüyoruz.
}