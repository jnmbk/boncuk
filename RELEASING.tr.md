# Boncuk Sürüm Yayınlama Süreci

Bu belge, Boncuk için yeni bir sürüm yayınlamanın standart prosedürünü özetlemektedir. Çapraz platform kurulum dosyalarının (Windows, macOS, Linux) otomatik olarak oluşturulması için bir GitHub Actions CI/CD iş akışı (pipeline) kullanıyoruz.

## 1. Sürümü Hazırlama
Bir sürüm oluşturmadan önce aşağıdakilerden emin olun:
- İstenen tüm özellikler ve hata düzeltmeleri hedef dala (ör. `qt6` veya `main`) eklendi (merge edildi).
- Yerel testler başarıyla geçiyor.

## 2. Sürüm Numaralarını Güncelleme
Etiket (tag) oluşturmadan önce, kaynak kod yapılandırmasındaki sürüm numaralarını güncelleyin:

1. **`boncuk.pro`** dosyasını açın ve `VERSION` değişkenini güncelleyin:
   ```pro
   VERSION = "2.1.0"
   ```
2. **`windows/boncuk.iss`** dosyasını açın ve `AppVersion` değerini güncelleyin:
   ```ini
   AppVersion=2.1.0
   ```

## 3. Sürüm Güncellemesini Commit Etme
Bu sürüm değişikliklerini deponuza commit edin (işleyin):
```bash
git add boncuk.pro windows/boncuk.iss
git commit -m "Bump version to v2.1.0"
git push origin qt6  # Farklıysa aktif dalınız ile değiştirin
```

## 4. Git Etiketi (Tag) Oluşturma ve Gönderme
GitHub Actions iş akışımız, depoya `v` ile başlayan bir Git etiketi gönderildiğinde uygulamayı otomatik olarak çalıştıracak ve paketleyecek şekilde yapılandırılmıştır.

Yeni sürüm için açıklamalı bir etiket (annotated tag) oluşturun:
```bash
git tag -a v2.1.0 -m "Release version 2.1.0"
```

Etiketi GitHub'a gönderin (push):
```bash
git push origin v2.1.0
```
*(Alternatif olarak, bekleyen tüm etiketleri göndermek için `git push origin --tags` komutunu kullanabilirsiniz).*

## 5. Kurulum Dosyalarını GitHub Actions'tan Alma
Etiket GitHub'a gönderildikten sonra, CI iş akışı kurulum dosyalarını oluşturmaya otomatik olarak başlayacaktır.

1. GitHub depo sayfanızdaki **Actions** sekmesine gidin.
2. En son çalışan iş akışına tıklayın (etiket adınızla eşleşmelidir).
3. Windows, macOS ve Linux için `build-and-test` işlerinin bitmesini bekleyin.
4. İş akışı sayfasının altındaki **Artifacts** bölümüne kaydırın.
5. Oluşturulan yapı (artifact) zip dosyalarını indirin:
   - `Boncuk-Windows-Installer`
   - `Boncuk-macOS-DMG`
   - `Boncuk-Linux-AppImage`

## 6. GitHub Sürümünü Yayınlama
Kurulum dosyalarını kullanıcılarınız için kolayca erişilebilir hale getirmek için:

1. GitHub deponuzun yan menüsündeki **Releases** (Sürümler) bölümüne gidin.
2. **Draft a new release** (Yeni bir sürüm taslağı oluştur) butonuna tıklayın.
3. "Choose a tag" açılır menüsünden, az önce gönderdiğiniz etiketi seçin (ör. `v2.1.0`).
4. Bir başlık yazın ve Sürüm Notları (değişiklik günlüğü, yeni özellikler, hata düzeltmeleri vb.) ekleyin.
5. 5. Adımda indirdiğiniz `.zip` yapı dosyalarını dışa aktarın.
6. Gerçek kurulum dosyalarını (`Boncuk_Setup.exe`, `boncuk.dmg` ve `.AppImage`) sürüm formunun altındaki **Attach binaries** alanına sürükleyip bırakın.
7. **Publish release** (Sürümü yayınla) butonuna tıklayın.

Kullanıcılar artık doğrudan GitHub Releases sayfanızdan işletim sistemlerine uygun (native) kurulum dosyalarını indirebilirler!
