#include <stdio.h>
#include <locale.h>
typedef struct {
    char ProductName[40];
    unsigned int BidNumber;
    double LastPrice;
    double PriceIncrease[];
}Auction;


void LastBid(Auction *product);
double Price(Auction *product);

int main() {
    Auction product1;

    setlocale(LC_ALL,"Turkish");

    wprintf(L"Lütfen Ürünün Adını Giriniz\n");
    gets(product1.ProductName);
    wprintf(L"Lütfen Ürünün İlk Fiyatını Giriniz\n");
    scanf("%lf",&product1.PriceIncrease[0]);
    LastBid(&product1);
    wprintf(L"Satın Alınan Ürün : %s\nÖdenecek Fiyat : %lf\nAçık Artırmayı Kazanan Numara : %d",product1.ProductName,Price(&product1),product1.BidNumber-1);
    return 0;
}




void LastBid(Auction *product){
    wprintf(L"Açık Artırma Başladı\nArtık Gireceğiniz 0' dan Büyük Tüm Sayılar Ürünün Fiyatını Artıracaktır\nAçık Artırmayı Sonlandırmak İçin \"-1\" Değerini Giriniz\n");
    double price;
    product->BidNumber=1;
    while(1) {
        wprintf(L"Lütfen Artım Miktarını Giriniz\n");
        if (!scanf("%lf", &price)) {
            wprintf(L"Lütfen Sayı Giriniz\n");
            fflush(stdin);
        }
        if (price == -1) {
            wprintf(L"Açık Artırma Sona Erdi\n");
            break;
        } else if (price <= 0) {
            wprintf(L"Sadece 0' dan Büyük Sayılar Girebilirsiniz\n");
        } else {
            product->PriceIncrease[product->BidNumber] = price;
            ++product->BidNumber;
        }
    }
}

double Price(Auction *product){
    int i=0;
    while(i!=product->BidNumber ) {
    product->LastPrice+=product->PriceIncrease[i];
    i++;
    }

    return product->LastPrice;
}