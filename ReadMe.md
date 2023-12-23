# Açık Artırma Program
## Program Hakkında Genel Bilgiler
- Açık Artıma Programım Sizden Bir Ürün İsmi İsteyecektir.
- Ürün İsminin Çok Uzun Olmamasına Dikkat Edin.
- Daha Sonra Girdiğiniz Ürününüzün Bir Başlangıç Fiyatını Alacaktır.
- Daha Sonrasında Gireceğinizi 0’ Dan Büyük Bütün Sayılar Başlangıç Fiyatının Üzerine Eklenecektir.
- Girdiğiniz Her Artımın Kendine Özel Bir ID Si Olacaktır. İşin Aslı Kaç Kişinin Fiyat Artırdığını Kontrol Edebileceksiniz. Çünkü Fiyatı Son Artıran Kişi Otomatik Olarak En Yüksek Teklifi Yapan Kişi Olacaktır.
- Açık Artırmayı Sonlandırmak İçin -1 Değeri Girmeniz Yeterli Olacaktır.
- İşlem Sonunda Program _Price_ Fonksiyonuyla Son Fiyatı Hesaplayacaktır.
- Bu İşlemi Girilen Tüm Fiyat Artımlarını (Başlangıç Fiyatı Dahil) Birbirleriyle Toplayarak Bulacaktır.
- Eğer Herhangi Bir Fiyat Artımı Olmadıysa Yani Son Fiyatla Başlangıç Fiyatı Aynıysa Ürününüz Satılamamış Olacaktır.
---
## Structure Yapısı
- Açık Artırma (Auction) Adında Bir *Structure* Kodumuzda Bulunmakta.
- Bu Structure' ı *typdef* İle Tanımladığımız İçin *main* Bloğumuza Sadece Structure Adı Ve Bir Takma Ad Vererek Bir Değişken Oluşturuyoruz.
- Bu Değişkenin İçeriğinde Yukarıda Da Bahsettiğim Ürün Adı, Teklif Numarası, Artım Miktarı Ve Son Fiyat Adında Özellikler Bulunmakta.
- Yani Oluşturduğumuz Tek Bir Üründe Bu Bilgilerin Hepsini Kolayca Kullanabiliyoruz Ve Fonksiyonları Kullanmak İstediğimizde Tek Bir Değişken Adı Göndererek Tüm Ürün Özelliklerini Gönderebiliyoruz.
---
## Ekran Görüntüleri
![BasariliSatis](https://github.com/TunahanYavuz/AcikArtirmaProgram/assets/143287857/b06e1af1-5fd0-4e27-a996-93225e4e2924)
---

---
![BasarisizSatis](https://github.com/TunahanYavuz/AcikArtirmaProgram/assets/143287857/5d81b180-8ea8-4fc9-830a-ebabde63d56e)

---

## Kod İçeriği
```
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
```