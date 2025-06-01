# Kullanıcı Seçenekleri (Müşteri)

Müşteri giriş işlemleri şu şekilde yapılabilir:

- Ürün listesi (ID, isim, fiyat, stok bilgisi)
- Sepete ürün ekleme (ID ve adet girerek)
- Aynı ürün tekrar eklendiğinde miktar artırılır
- Stok kontrolü yapılır ve stoktan otomatik düşülür
- Sepetteki ürünleri ve toplam bölmeyi görüntüleme
- Sipariş oluşturma
- Siparişler `siparisler.txt` dosyasına otomatik olarak depolanır
- Sipariş ID'si otomatik olarak artar ve `siparis_id.txt` dosyasında tutulur

---

# Yönetici İşlevleri

Yönetici girişi sırasında şu işlemler yapılabilir:

1. **Stok Miktarı Artırma**  
   - Var olan bir ürünün stok miktarı artırılabilir.  
   - Ürün ID'si ve eklenecek miktar girilir.

2. **Yeni Ürün Ekle**  
   - Yeni bir ürün adı, fiyat ve stok bilgisi sisteme girilerek eklenebilir.  
   - Ürün ID'si sistem tarafından otomatik olarak verilmektedir.

3. **Sertifikaları Görüntüle**  
   - `siparisler.txt` dosyada tüm siparişler terminalde listelenir.

4. **Çıkış Yap**  
   - Yönetici panelinden çıkılır.

---

# Dosyalar

- `siparisler.txt`: Sipariş kayıtlarını tutar.  
- `siparis_id.txt`: Her siparişe özel benzersiz bir ID'yi tutar.  
- `eticaret.c`: Projenin kaynak kodu.
