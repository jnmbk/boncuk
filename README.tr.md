# Boncuk

**Boncuk**, hızlı, basit ve kullanışlı bir Türkçe-İngilizce-Almanca sözlüktür. Başlangıçta `pysozluk-qt` projesinin C++ ile yazılmış hali olarak ortaya çıkan Boncuk, çevirileri hem çevrimiçi (online) hem de çevrimdışı (offline) yapabilmeniz için hafif bir masaüstü arayüzü ve konsol aracı sunar.

## Özellikler

- **Çoklu Dil Desteği:** Türkçe, İngilizce ve Almanca dilleri arasında kelime çevirisi.
- **Çevrimiçi & Çevrimdışı Modlar:**
  - Hızlı çevrimdışı aramalar için gömülü SQLite veritabanı içerir.
  - Sesli Sözlük üzerinden çevrimiçi sonuçları getirmeyi destekler.
- **Komut Satırı Arayüzü (CLI):** Terminal üzerinden hızlı aramalar yapmak için gömülü konsol modu.
- **Arama Geçmişi:** Önceki aramalarınızın yapılandırılabilir bir geçmişini tutar.
- **Hafif ve Hızlı:** Maksimum performans ve minimum kaynak tüketimi için C++ ve Qt kullanılarak geliştirilmiştir.

## Gereksinimler

Boncuk'u derlemek ve çalıştırmak için şunlara ihtiyacınız vardır:
- Qt 4.3 veya daha yenisi (Qt 6'ya kadar yeni Qt sürümleriyle uyumludur)
- Qt için SQLite eklentisi (Qt sürümünüze bağlı olarak `libqt4-sql-sqlite` veya eşdeğeri)
- Make, GCC/Clang veya standart C++ derleme araçları

## Kurulum

### Kaynak Koddan Derleme

1. **Depoyu klonlayın:**
   ```bash
   git clone https://github.com/yourusername/boncuk.git
   cd boncuk
   ```

2. **Çeviri dosyalarını oluşturun:**
   ```bash
   lrelease boncuk.pro
   ```

3. **Projeyi derleyin:**
   ```bash
   qmake
   make
   ```

4. **Boncuk'u çalıştırın:**
   Derlenen çalıştırılabilir dosya `bin/` dizini içine yerleştirilecektir.
   ```bash
   ./bin/boncuk
   ```

## Kullanım

### Grafiksel Arayüz (GUI)
Grafiksel arayüzü başlatmak için `boncuk` uygulamasını çalıştırmanız yeterlidir. Bir kelime yazıp Enter tuşuna basarak çevirileri görebilirsiniz. Arama butonuna basılı tutarak (veya menüyü kullanarak) aramanızı yalnızca o kelime için çevrimiçi veya çevrimdışı olacak şekilde değiştirebilirsiniz.

### Konsol Arayüzü (CLI)
Aranacak kelimeyi argüman olarak vererek Boncuk'u doğrudan terminalinizden de kullanabilirsiniz:
```bash
boncuk "aranacak kelime"
```

## Katkıda Bulunma

Projeye yapacağınız katkılardan mutluluk duyarız! Lütfen GitHub üzerinden bir Pull Request (Çekme İsteği) göndermekten veya bir sorun (issue) açmaktan çekinmeyin.
- Planlanan özellikler ve bilinen hatalar için `TODO` dosyasına bakabilirsiniz.
- Katkıda bulunanların listesi için `AUTHORS` dosyasına bakabilirsiniz.

## Lisans

Boncuk açık kaynaklı bir yazılımdır. Daha fazla detay için `COPYING` dosyasına bakabilirsiniz.
