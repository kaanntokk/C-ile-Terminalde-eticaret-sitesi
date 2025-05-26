#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ürün yapısı
struct Urun {
    int id;
    char isim[50];
    float fiyat;
    int stok;
};

// Sepet yapısı
struct Sepet {
    struct Urun urun;
    int adet;
};

// Sipariş ID'sini dosyadan okuma
int siparisIDOku() {
    FILE *idDosya = fopen("siparis_id.txt", "r");
    int id = 0;
    if (idDosya != NULL) {
        fscanf(idDosya, "%d", &id);
        fclose(idDosya);
    }
    return id;
}

// Sipariş ID'sini güncelleme
void siparisIDGuncelle(int yeniID) {
    FILE *idDosya = fopen("siparis_id.txt", "w");
    if (idDosya != NULL) {
        fprintf(idDosya, "%d", yeniID);
        fclose(idDosya);
    }
}

int main() {
    struct Urun urunler[100];
    int urun_sayisi = 3;

    urunler[0] = (struct Urun){1, "Telefon", 5000.0, 10};
    urunler[1] = (struct Urun){2, "Bilgisayar", 10000.0, 5};
    urunler[2] = (struct Urun){3, "Klavye", 300.0, 20};

    int secim;

    printf("=== HOSGELDINIZ ===\n");
    printf("1 - Musteri Girisi\n");
    printf("2 - Yonetici Girisi\n");
    printf("Seciminiz: ");
    scanf("%d", &secim);

    if (secim == 1) {
        printf("\n[Musteri girisi baslatiliyor...]\n");

        struct Sepet sepet[10];
        int sepet_sayisi = 0;
        int secim, adet;
        char devam;

        printf("\n=== URUN LISTESI ===\n");
        for (int i = 0; i < urun_sayisi; i++) {
            printf("%d - %s | %.0f TL | Stok: %d\n",
                urunler[i].id, urunler[i].isim, urunler[i].fiyat, urunler[i].stok);
        }

        do {
            printf("\nSepete eklemek istediginiz urunun ID'sini girin: ");
            scanf("%d", &secim);

            if (secim < 1 || secim > urun_sayisi) {
                printf("Gecersiz urun ID'si!\n");
                continue;
            }

            if (urunler[secim-1].stok == 0) {
                printf("Bu urun stokta yok! Baska bir urun secin.\n");
                continue;
            }

            printf("Kac adet eklemek istiyorsunuz? ");
            scanf("%d", &adet);

            if (adet <= 0 || adet > urunler[secim-1].stok) {
                printf("Gecersiz adet! (Stokta yeterli urun yok)\n");
                continue;
            }

            int bulundu = 0;
            for (int i = 0; i < sepet_sayisi; i++) {
                if (sepet[i].urun.id == urunler[secim-1].id) {
                    sepet[i].adet += adet;
                    bulundu = 1;
                    break;
                }
            }
            if (!bulundu) {
                sepet[sepet_sayisi].urun = urunler[secim-1];
                sepet[sepet_sayisi].adet = adet;
                sepet_sayisi++;
            }

            urunler[secim-1].stok -= adet;

            printf("\n--- Sepetiniz ---\n");
            for (int i = 0; i < sepet_sayisi; i++) {
                printf("%s x%d = %.0f TL\n",
                    sepet[i].urun.isim,
                    sepet[i].adet,
                    sepet[i].urun.fiyat * sepet[i].adet);
            }

            printf("Baska urun eklemek istiyor musunuz? (E/e: Evet, H/h: Hayir): ");
            scanf(" %c", &devam);

        } while (devam == 'E' || devam == 'e');

        printf("\n=== SEPETINIZ ===\n");
        float toplam = 0.0;
        for (int i = 0; i < sepet_sayisi; i++) {
            printf("%s x%d = %.0f TL\n",
                sepet[i].urun.isim, sepet[i].adet, sepet[i].urun.fiyat * sepet[i].adet);
            toplam += sepet[i].urun.fiyat * sepet[i].adet;
        }
        printf("\nToplam Tutar: %.0f TL\n", toplam);

        int siparisID = siparisIDOku();
        siparisID++;
        siparisIDGuncelle(siparisID);

        FILE *dosya = fopen("siparisler.txt", "a");
        if (dosya == NULL) {
            printf("Siparis dosyasi acilamadi!\n");
            return 1;
        }

        fprintf(dosya, "=== Yeni Siparis ===\n");
        fprintf(dosya, "Siparis ID: %d\n", siparisID);
        for (int i = 0; i < sepet_sayisi; i++) {
            fprintf(dosya, "%s x%d = %.0f TL\n",
                sepet[i].urun.isim, sepet[i].adet, sepet[i].urun.fiyat * sepet[i].adet);
        }
        fprintf(dosya, "Toplam Tutar: %.0f TL\n", toplam);
        fprintf(dosya, "Siparis Durumu: Hazirlaniyor\n\n");

        fclose(dosya);

        printf("\nSiparisiniz 'siparisler.txt' dosyasina kaydedildi.\n");

    } else if (secim == 2) {
        printf("\n[Yonetici girisi baslatiliyor...]\n");
        int admin_secim;
        do {
            printf("\n=== YONETICI PANELI ===\n");
            printf("1 - Stok Miktari Artir\n");
            printf("2 - Yeni Urun Ekle\n");
            printf("3 - Siparisleri Goruntule\n");
            printf("4 - Cikis Yap\n");
            printf("Seciminiz: ");
            scanf("%d", &admin_secim);

            if (admin_secim == 1) {
                printf("\n=== STOK ARTIRMA ===\n");
                for (int i = 0; i < urun_sayisi; i++) {
                    printf("%d - %s | Mevcut Stok: %d\n", urunler[i].id, urunler[i].isim, urunler[i].stok);
                }
                int urunID, eklenenAdet;
                printf("Stok artirmak istediginiz urunun ID'sini girin: ");
                scanf("%d", &urunID);

                if (urunID < 1 || urunID > urun_sayisi) {
                    printf("Gecersiz urun ID'si!\n");
                    continue;
                }

                printf("Kac adet eklemek istiyorsunuz? ");
                scanf("%d", &eklenenAdet);

                if (eklenenAdet <= 0) {
                    printf("Gecersiz adet!\n");
                    continue;
                }

                urunler[urunID-1].stok += eklenenAdet;
                printf("Stok guncellendi! Yeni stok: %d\n", urunler[urunID-1].stok);
            } else if (admin_secim == 2) {
                printf("\n=== YENI URUN EKLEME ===\n");
                char yeniIsim[50];
                float yeniFiyat;
                int yeniStok;

                printf("Yeni urunun adini girin: ");
                scanf(" %[^\n]", yeniIsim);  // ✅ Doğru şekilde boşluklu metin okur

                printf("Yeni urunun fiyatini girin: ");
                scanf("%f", &yeniFiyat);
                printf("Yeni urunun stok miktarini girin: ");
                scanf("%d", &yeniStok);

                urun_sayisi++;
                urunler[urun_sayisi-1].id = urun_sayisi;
                strcpy(urunler[urun_sayisi-1].isim, yeniIsim);
                urunler[urun_sayisi-1].fiyat = yeniFiyat;
                urunler[urun_sayisi-1].stok = yeniStok;

                printf("Yeni urun basariyla eklendi!\n");
            } else if (admin_secim == 3) {
                printf("\n=== SIPARISLER ===\n");
                FILE *dosyaOku = fopen("siparisler.txt", "r");
                if (dosyaOku == NULL) {
                    printf("Siparis dosyasi bulunamadi!\n");
                } else {
                    char satir[200];
                    while (fgets(satir, sizeof(satir), dosyaOku)) {
                        printf("%s", satir);
                    }
                    fclose(dosyaOku);
                }
            } else if (admin_secim == 4) {
                printf("\n[Cikis yapiliyor...]\n");
            } else {
                printf("Gecersiz secim yaptiniz!\n");
            }

        } while (admin_secim != 4);

    } else {
        printf("Gecersiz secim yaptiniz!\n");
    }

    return 0;
}



