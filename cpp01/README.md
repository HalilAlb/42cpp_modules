# CPP01 Modülü - Detaylı Açıklama ve Debug Rehberi

Bu döküman CPP01 modülündeki her bir egzersiz için detaylı açıklama ve debug adımlarını içerir.

---

## ex00: BraiiiiiiinnnzzzZ (Zombie)

### 📋 Proje Amacı
Stack ve Heap bellek yönetimi arasındaki farkları anlamak, `new` ve `delete` operatörlerini öğrenmek.

### 🔧 Dosya Yapısı
- **Zombie.hpp/cpp**: Zombie sınıfı tanımı ve implementasyonu
- **newZombie.cpp**: Heap'te zombie oluşturur
- **randomChump.cpp**: Stack'te zombie oluşturur
- **main.cpp**: Test programı

### 💡 Nasıl Çalışır?

#### Zombie Sınıfı (Zombie.hpp ve Zombie.cpp)

**Header Dosyası (Zombie.hpp):**
```cpp
#ifndef _ZOMBIE_
#define _ZOMBIE_

#include <string>
#include <iostream>

class Zombie {
private:
    std::string _name;  // Zombie'nin ismi (private - dışarıdan erişilemez)

public:
    Zombie();                      // Default constructor (parametre almaz)
    Zombie(std::string name);      // Parametreli constructor (isim alır)
    ~Zombie();                     // Destructor (nesne yok edilirken çağrılır)
    void announce(void);           // "BraiiiiiiinnnzzzZ..." mesajını yazdırır
};

// Global fonksiyonlar (sınıf dışında)
Zombie* newZombie(std::string name);  // Heap'te zombie oluşturur
void randomChump(std::string name);    // Stack'te zombie oluşturur

#endif
```

**Açıklama:**
- `#ifndef _ZOMBIE_` → Header guard (dosyanın birden fazla include edilmesini önler)
- `private:` → Bu değişkenlere sadece sınıf içinden erişilebilir
- `public:` → Bu fonksiyonlara dışarıdan erişilebilir
- Constructor'lar → Nesne oluşturulurken otomatik çağrılır
- Destructor `~Zombie()` → Nesne yok edilirken otomatik çağrılır (bellek temizliği için)

**Implementation Dosyası (Zombie.cpp):**
```cpp
#include "Zombie.hpp"

// Default constructor - parametre almadan zombie oluşturur
Zombie::Zombie(void) : _name("foo") {
    // _name değişkenini "foo" olarak başlatır (initialization list kullanımı)
}

// Parametreli constructor - isimle zombie oluşturur
Zombie::Zombie(std::string name) : _name(name) {
    // _name değişkenini verilen name ile başlatır
}

// announce fonksiyonu - zombie'nin konuşması
void Zombie::announce(void) {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

// Destructor - nesne yok edilirken çağrılır
Zombie::~Zombie(void) {
    std::cout << _name << " has been destroyed." << std::endl;
    // Bu sayede hangi zombie'nin ne zaman yok edildiğini görebiliriz
}
```

**Initialization List Nedir?**
```cpp
Zombie::Zombie(std::string name) : _name(name) { }
//                                  ^^^^^^^^^^^^
//                                  Bu initialization list
```
- Constructor body'den ÖNCE çalışır
- Daha verimlidir (direkt initialize eder, assignment yapmaz)
- Const ve referans member'lar için zorunludur

#### 1. Stack'te Nesne Oluşturma (randomChump.cpp)
```cpp
#include "Zombie.hpp"

void randomChump(std::string name) {
    Zombie zombie(name);  // Stack'te oluşturulur (otomatik bellek)
    zombie.announce();     // "name: BraiiiiiiinnnzzzZ..." yazdırır
    return;
    // Fonksiyon bitince 'zombie' otomatik olarak yok edilir
    // Destructor çağrılır: "name has been destroyed." yazdırılır
}
```

**Ne Olur?**
1. `Zombie zombie(name)` → Stack'te zombie nesnesi oluşturulur
2. Constructor çağrılır → `_name` set edilir
3. `announce()` çağrılır → Mesaj yazdırılır
4. Fonksiyon biter → **Otomatik olarak** destructor çağrılır
5. Bellek otomatik temizlenir → Manuel `delete` gerektirmez!

**Stack'in Özellikleri:**
- ✅ Hızlı (direkt CPU register'ları kullanır)
- ✅ Otomatik temizlik (scope bitince silinir)
- ❌ Sınırlı boyut (~8MB tipik)
- ❌ Scope dışına çıkamaz

#### 2. Heap'te Nesne Oluşturma (newZombie.cpp)
```cpp
#include "Zombie.hpp"

Zombie* newZombie(std::string name) {
    Zombie* zombie = new Zombie(name);  // Heap'te oluşturulur (dinamik bellek)
    zombie->announce();                  // "name: BraiiiiiiinnnzzzZ..." yazdırır
    return zombie;  // Pointer döndürülür - nesne hala bellekte yaşıyor!
}
```

**Ne Olur?**
1. `new Zombie(name)` → Heap'te bellek ayrılır ve zombie oluşturulur
2. Constructor çağrılır → `_name` set edilir
3. Heap'teki nesnenin adresi `zombie` pointer'ına atanır
4. `announce()` çağrılır (pointer ile: `->` operatörü)
5. Pointer döndürülür → **Nesne hala bellekte yaşıyor!**
6. Çağıran fonksiyon `delete` ile silmek ZORUNDA

**Heap'in Özellikleri:**
- ✅ Büyük boyut (RAM'in çoğu kullanılabilir)
- ✅ Scope'tan bağımsız (fonksiyon bitince de yaşar)
- ❌ Yavaş (sistem çağrısı gerektirir)
- ❌ Manuel yönetim (`delete` gerekir, yoksa memory leak!)

**main.cpp'de Kullanım:**
```cpp
#include "Zombie.hpp"

int main(void) {
    std::string name;

    // STACK KULLANIMI
    std::cout << "Creating zombie on the stack." << std::endl;
    std::cout << "Zombie name:" << std::flush;
    std::cin >> name;
    randomChump(name);  // Fonksiyon bitince otomatik silinir
    // Bu noktada stack zombie'si artık yok!

    // HEAP KULLANIMI
    std::cout << "\nCreating zombie on the heap." << std::endl;
    std::cout << "Zombie name: " << std::flush;
    std::cin >> name;
    
    Zombie *zombie2 = newZombie(name);  // Heap'te oluşturuldu
    // zombie2 hala yaşıyor, istediğimiz kadar kullanabiliriz
    
    delete zombie2;  // MANUEL SİLMEK ZORUNLU!
    // "name has been destroyed." yazdırılır
    
    return 0;
}
```

#### Stack vs Heap Görsel Analoji

```
STACK (Tabak Yığını):
┌─────────┐
│ Zombie3 │ ← Son giren
├─────────┤
│ Zombie2 │
├─────────┤
│ Zombie1 │ ← İlk giren
└─────────┘
Fonksiyon bitince en üstteki tabak otomatik kaldırılır (LIFO)

HEAP (Depo):
┌─────────────────────────┐
│  ┌───┐      ┌───┐       │
│  │ Z1│      │ Z3│       │
│  └───┘  ┌───┐───┘       │
│         │ Z2│            │
│         └───┘            │
└─────────────────────────┘
İstediğiniz yere koyabilirsiniz, ama kendiniz kaldırmalısınız!

### 🐛 Debug Adımları

#### Adım 1: Derleme
```bash
cd ex00
make
```

**Olası Hatalar:**
- `undefined reference to Zombie::announce()` → Zombie.cpp'yi Makefile'a eklemeyi unutmuşsunuz
- `error: 'string' is not a member of 'std'` → `#include <string>` eksik

#### Adım 2: Çalıştırma
```bash
./zombie
```

**Test Senaryosu:**
```
# Stack zombie için:
Stack Zombie
# Çıktı: "Stack Zombie: BraiiiiiiinnnzzzZ..."
# Ardından: "Stack Zombie has been destroyed."

# Heap zombie için:
Heap Zombie
# Çıktı: "Heap Zombie: BraiiiiiiinnnzzzZ..."
# Delete edildiğinde: "Heap Zombie has been destroyed."
```

#### Adım 3: Bellek Sızıntısı Kontrolü
```bash
# macOS için:
leaks -atExit -- ./zombie

# Linux için:
valgrind --leak-check=full ./zombie
```

**Beklenen Sonuç:** `0 leaks` veya `All heap blocks were freed`

**Sık Karşılaşılan Hatalar:**
- ❌ `delete zombie2;` satırını unutmak → **Bellek sızıntısı!**
- ❌ Stack zombie'yi delete etmeye çalışmak → **Segmentation fault!**

### ✅ Doğru Kullanım Örnekleri

**Ne zaman Stack:**
- Kısa ömürlü nesneler
- Fonksiyon içinde kullanılıp unutulacak nesneler
- Otomatik temizlik istediğinizde

**Ne zaman Heap:**
- Uzun ömürlü nesneler
- Fonksiyon dışında kullanılacak nesneler
- Büyük nesneler (stack overflow'dan kaçınmak için)

---

## ex01: Moar brainz! (Zombie Horde)

### 📋 Proje Amacı
Dinamik dizi tahsisi (`new[]` ve `delete[]`) öğrenmek.

### 🔧 Dosya Yapısı
- **zombieHorde.cpp**: N adet zombie içeren dizi oluşturur
- **setName()**: Zombie'lere isim atamak için setter fonksiyonu

### 💡 Nasıl Çalışır?

#### Zombie Sınıfı Güncellemeleri

**Zombie.hpp'ye Eklenen:**
```cpp
class Zombie {
private:
    std::string _name;

public:
    Zombie();                    // Default constructor (ÖNEMLİ!)
    Zombie(std::string name);    // Parametreli constructor
    ~Zombie();
    void announce(void);
    void setName(std::string name);  // YENİ! İsim değiştirme fonksiyonu
};

Zombie* zombieHorde(int j, std::string name);  // YENİ! Horde oluşturan fonksiyon
```

**Neden Default Constructor Gerekli?**
```cpp
Zombie* zombies = new Zombie[5];  // 5 elemanlı dizi
```
Bu satır çalıştığında:
1. Bellekte 5 zombie için yer ayrılır
2. Her zombie için **default constructor** çağrılır
3. Eğer default constructor yoksa → DERLEME HATASI!

**Zombie.cpp'ye Eklenen:**
```cpp
void Zombie::setName(std::string name) {
    this->_name = name;  // 'this' pointer'ı nesnenin kendisini gösterir
    return;
}
```
- `this` → Üzerinde çalışılan nesnenin pointer'ı
- `this->_name` → Bu nesnenin _name değişkeni
- Parametre ile member variable aynı isimde olduğunda `this->` kullanılır

#### zombieHorde Fonksiyonu (zombieHorde.cpp)

```cpp
#include "Zombie.hpp"

Zombie* zombieHorde(int j, std::string name) {
    // 1. ADIM: Dinamik dizi tahsisi
    Zombie* zombies = new Zombie[j];
    // Bu satır j tane Zombie oluşturur
    // Her biri için default constructor çağrılır
    // Hepsi "foo" ismiyle başlar
    
    // 2. ADIM: Her zombie'ye aynı ismi ata
    for (int i = 0; i < j; i++)
        zombies[i].setName(name);
        // zombies[i] → i. zombie'ye erişim (array notation)
        // setName() → İsmini değiştir
    
    // 3. ADIM: Dizinin ilk elemanının pointer'ını döndür
    return (zombies);
    // zombies değişkeni aslında dizinin ilk elemanının adresi
}
```

**Detaylı Açıklama:**

**1. `new Zombie[j]` ne yapar?**
```cpp
// j = 3 için:
new Zombie[3]
    ↓
Bellekte:
[Zombie("foo")] [Zombie("foo")] [Zombie("foo")]
     ↑
zombies pointer'ı buraya işaret eder
```

**2. Array indexing nasıl çalışır?**
```cpp
zombies[0]  →  *(zombies + 0)  →  İlk zombie
zombies[1]  →  *(zombies + 1)  →  İkinci zombie
zombies[2]  →  *(zombies + 2)  →  Üçüncü zombie
```

**3. Neden setName() gerekli?**
```cpp
// YANLIŞ: Constructor'ı tekrar çağıramazsınız
zombies[i] = Zombie(name);  // ❌ Assignment yapar, yeniden construct etmez

// DOĞRU: Setter fonksiyonu kullanın
zombies[i].setName(name);   // ✅ Var olan nesnenin ismini değiştirir
```

#### main.cpp Kullanımı

```cpp
#include "Zombie.hpp"

int main(void) {
    int numzombie;
    std::string name;
    Zombie* zombies;  // Pointer tanımla (henüz bellek ayrılmadı)
    
    // Kullanıcıdan input al
    std::cout << "Creating horde of zombie" << std::endl;
    std::cout << "Number of Zombie: " << std::flush;
    std::cin >> numzombie;  // Kaç zombie?
    
    std::cout << "Name of each Zombie: " << std::flush;
    std::cin >> name;  // Hepsinin ismi ne olsun?

    // Horde'u oluştur
    zombies = zombieHorde(numzombie, name);
    // zombies artık numzombie tane zombie içeren bir diziye işaret ediyor

    // Her birini konuştur
    for (int i = 0; i < numzombie; i++)
        zombies[i].announce();
        // "name: BraiiiiiiinnnzzzZ..." x numzombie

    // DİZİYİ SİL - ÇOK ÖNEMLİ!
    delete [] zombies;
    // [] kullanılması ZORUNLU (dizi siliyoruz)
    // Her zombie için destructor çağrılır
    
    return 0;
}
```

#### new[] ve delete[] Kuralları

```cpp
// TEK NESNE
Zombie* z = new Zombie("Foo");
delete z;  // Tek nesne silme

// DİZİ
Zombie* arr = new Zombie[5];
delete[] arr;  // Dizi silme ([] ÖNEMLİ!)
```

**Yanlış Kullanım Sonuçları:**
```cpp
Zombie* arr = new Zombie[5];

// ❌ YANLIŞ - Sadece ilk elemanı siler!
delete arr;
// Sonuç: 4 zombie bellekte kalır → MEMORY LEAK!
// Sadece arr[0] için destructor çağrılır

// ✅ DOĞRU - Tüm diziyi siler
delete[] arr;
// Sonuç: 5 zombie'nin hepsi silinir
// Her biri için destructor çağrılır
```

#### Bellek Düzeni

```
new Zombie[3] çağrıldığında:

HEAP:
┌─────────────────────────────────────────────┐
│ [Meta Data] │ Zombie1 │ Zombie2 │ Zombie3 │ │
└─────────────────────────────────────────────┘
       ↑            ↑
       │            └── zombies pointer'ı buraya işaret eder
       │
       └── Sistem kaç eleman olduğunu buraya yazar
           (delete[] bunu kullanır)

delete[] zombies çağrıldığında:
1. Meta data'dan eleman sayısını okur (3)
2. Her biri için destructor çağırır (3 kez)
3. Tüm belleği serbest bırakır
```

### 🐛 Debug Adımları

#### Adım 1: Derleme
```bash
cd ex01
make
```

#### Adım 2: Test
```bash
./zombieHorde
# Input: 5
# Input: Foo
```

**Beklenen Çıktı:**
```
Foo: BraiiiiiiinnnzzzZ...
Foo: BraiiiiiiinnnzzzZ...
Foo: BraiiiiiiinnnzzzZ...
Foo: BraiiiiiiinnnzzzZ...
Foo: BraiiiiiiinnnzzzZ...
Foo has been destroyed.
Foo has been destroyed.
...
```

#### Adım 3: Bellek Kontrolü
```bash
leaks -atExit -- ./zombieHorde
```

**Kritik Noktalar:**
- ✅ `delete[] zombies;` kullanılmalı (sadece `delete` değil!)
- ✅ Default constructor gerekli (çünkü `new Zombie[N]` önce tüm nesneleri default constructor ile oluşturur)
- ❌ `delete zombies;` → Sadece ilk eleman silinir, bellek sızıntısı!

### 🎯 Önemli Notlar
- `new` → `delete`
- `new[]` → `delete[]`
- Asla karıştırmayın!

---

## ex02: HI THIS IS BRAIN

### 📋 Proje Amacı
Pointer ve referans arasındaki farkları anlamak.

### 💡 Nasıl Çalışır?

#### Temel Kavramlar

**1. String Değişkeni Tanımlama**
```cpp
std::string a = "HI THIS IS BRAIN";
```
- `a` isminde bir string oluşturulur
- Stack'te saklanır
- Değeri: "HI THIS IS BRAIN"
- Bellekte bir adresi var (örn: `0x7ffeea2b9a80`)

**2. Pointer (İşaretçi) Oluşturma**
```cpp
std::string* stringPTR = &a;
```
- `stringPTR` → bir pointer (işaretçi)
- Tip: `std::string*` (string pointer'ı)
- `&a` → `a`'nın bellek adresini al
- `stringPTR` artık `a`'nın adresini tutuyor

**Pointer Nedir?**
```
Pointer = Bellek adresini tutan değişken

┌─────────────┐      ┌──────────────────────┐
│  stringPTR  │      │         a            │
│             │      │                      │
│ 0x7ffe...80 │ ───→ │ "HI THIS IS BRAIN"  │
└─────────────┘      └──────────────────────┘
   (adres tutar)         (asıl veri)
```

**3. Referans Oluşturma**
```cpp
std::string& stringREF = a;
```
- `stringREF` → bir referans (takma ad)
- Tip: `std::string&` (string referansı)
- `= a` → `a`'ya referans ver
- `stringREF` artık `a`'nın başka bir ismi

**Referans Nedir?**
```
Referans = Var olan değişkenin başka bir ismi

┌──────────────────────┐
│         a            │  ← Asıl isim
│  (stringREF)         │  ← Takma ad (alias)
│ "HI THIS IS BRAIN"   │
└──────────────────────┘
  İkisi de aynı yeri gösterir!
```

#### main.cpp Tam Açıklaması

```cpp
#include <iostream>

int main(void)
{
    // 1. String oluştur
    std::string a = "HI THIS IS BRAIN";
    
    // 2. Pointer oluştur (adres tutar)
    std::string* stringPTR = &a;
    //           ^           ^
    //           |           └── a'nın adresini al
    //           └── pointer tipi
    
    // 3. Referans oluştur (takma ad)
    std::string& stringREF = a;
    //           ^           ^
    //           |           └── a'ya referans
    //           └── referans tipi
    
    // ADRES YAZDIRMA
    std::cout << "Adresse of a (value): " << &a << std::endl;
    // &a → a'nın adresi (örn: 0x7ffeea2b9a80)
    
    std::cout << "Adresse of a (pointer): " << stringPTR << std::endl;
    // stringPTR zaten adres tutuyor, direkt yazdır
    // Aynı çıktı: 0x7ffeea2b9a80
    
    std::cout << "Adresse of a (REF): " << &stringREF << std::endl;
    // &stringREF → aslında &a demek (çünkü stringREF = a)
    // Aynı çıktı: 0x7ffeea2b9a80
    
    std::cout << std::endl;  // Boş satır
    
    // DEĞER YAZDIRMA
    std::cout << "Value of a (pointer): " << *stringPTR << std::endl;
    // *stringPTR → pointer'ın gösterdiği değer (dereferencing)
    // Çıktı: HI THIS IS BRAIN
    
    std::cout << "Value of a (ref): " << stringREF << std::endl;
    // stringREF → a ile aynı, direkt kullan
    // Çıktı: HI THIS IS BRAIN
    
    return (0);
}
```

#### Detaylı Operatörler

**& Operatörü (İki Farklı Kullanım)**
```cpp
// 1. ADRES ALMA (address-of)
int x = 42;
int* ptr = &x;  // x'in adresini al
std::cout << &x;  // x'in adresini yazdır

// 2. REFERANS TİPİ TANIMLAMA
int& ref = x;  // x'e referans
void func(int& param);  // Referans parametresi
```

** * Operatörü (İki Farklı Kullanım)**
```cpp
// 1. POINTER TİPİ TANIMLAMA
int* ptr;  // Pointer tanımlama
std::string* strPtr;

// 2. DEREFERENCING (pointer'ın gösterdiği değere erişim)
int value = *ptr;  // ptr'nin gösterdiği değeri al
*ptr = 10;  // ptr'nin gösterdiği yere 10 yaz
```

#### Karşılaştırma Tablosu

| İşlem | Değişken | Pointer | Referans |
|-------|----------|---------|----------|
| **Tanımlama** | `string a` | `string* ptr` | `string& ref` |
| **Başlatma** | `= "text"` | `= &a` | `= a` |
| **Adres alma** | `&a` | `ptr` | `&ref` |
| **Değere erişim** | `a` | `*ptr` | `ref` |
| **Üye erişimi** | `a.length()` | `ptr->length()` | `ref.length()` |
| **NULL olabilir mi?** | - | ✅ Evet | ❌ Hayır |
| **Yeniden atanamaz** | Değer değişir | Başka yeri gösterebilir | ❌ Değiştirilemez |

#### Bellek Görünümü

```
Stack Memory:
┌────────────────────────────────┐
│  a:                            │
│  ┌──────────────────────────┐  │
│  │ "HI THIS IS BRAIN"       │  │ ← 0x7ffeea2b9a80
│  └──────────────────────────┘  │
│                                │
│  stringPTR:                    │
│  ┌──────────────────────────┐  │
│  │ 0x7ffeea2b9a80           │  │ ← a'nın adresi
│  └──────────────────────────┘  │
│                                │
│  stringREF:                    │
│  (Aslında a'nın başka ismi)    │
│  a ile aynı bellek kullanır    │
└────────────────────────────────┘
```

#### Pointer vs Referans: Pratik Örnekler

**Değer Değiştirme:**
```cpp
std::string a = "HELLO";
std::string* ptr = &a;
std::string& ref = a;

// Pointer ile
*ptr = "WORLD";
std::cout << a;  // WORLD

// Referans ile
ref = "BRAIN";
std::cout << a;  // BRAIN

// Hepsi aynı değişkeni değiştiriyor!
```

**NULL Kontrolü:**
```cpp
// Pointer NULL olabilir
std::string* ptr = NULL;
if (ptr != NULL)
    std::cout << *ptr;  // Güvenli

// Referans NULL olamaz (derleme hatası)
std::string& ref;  // ❌ HATA: Başlatılmak zorunda
std::string& ref = NULL;  // ❌ HATA: NULL olamaz
```

**Yeniden Atama:**
```cpp
std::string a = "A";
std::string b = "B";

std::string* ptr = &a;
ptr = &b;  // ✅ OK: Artık b'yi gösteriyor

std::string& ref = a;
ref = b;  // ❌ Dikkat! Bu b'yi göstermez, a'nın değerini b yapar!
std::cout << a;  // B (a'nın değeri değişti!)
```

### 🔍 Farklar

| Özellik | Pointer | Referans |
|---------|---------|----------|
| Syntax | `*stringPTR` | `stringREF` |
| Adres alma | `stringPTR` | `&stringREF` |
| NULL olabilir mi? | ✅ Evet | ❌ Hayır |
| Yeniden atanabilir mi? | ✅ Evet | ❌ Hayır |
| Dereferans | `*ptr` gerekli | Otomatik |

### 🐛 Debug Adımları

```bash
cd ex02
make
./Brain
```

**Beklenen Çıktı:**
```
Adresse of a (value): 0x7ff...
Adresse of a (pointer): 0x7ff...  (aynı adres)
Adresse of a (REF): 0x7ff...      (aynı adres)

Value of a (pointer): HI THIS IS BRAIN
Value of a (ref): HI THIS IS BRAIN
```

### ✅ Öğrenilmesi Gerekenler
- Her üç yöntem de **aynı bellek adresini** gösterir
- Referanslar başlatıldıktan sonra değiştirilemez
- Referanslar NULL olamaz (güvenli!)

---

## ex03: Unnecessary violence (Weapon)

### 📋 Proje Amacı
Referans ve pointer kullanım durumlarını öğrenmek.

### 💡 Tasarım Kararları

#### Weapon Sınıfı (Weapon.hpp ve Weapon.cpp)

**Header Dosyası:**
```cpp
#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
public:
    Weapon(const std::string &type);  // Constructor (silah tipi alır)
    const std::string &getType() const;  // Getter (tip döndürür)
    void setType(const std::string &newType);  // Setter (tip değiştirir)

private:
    std::string _type;  // Silahın tipi (örn: "crude spiked club")
};

#endif
```

**Önemli Noktalar:**

**1. const std::string& Neden Kullanılır?**
```cpp
// ❌ KÖTÜ: Değer kopyalar (yavaş, bellekte yer kaplar)
Weapon(std::string type);
std::string getType();

// ✅ İYİ: Referans kullanır (hızlı, kopyalama yok)
Weapon(const std::string& type);
const std::string& getType() const;
```

**const Referans Avantajları:**
```
Normal Parametre:          const Referans:
┌──────────┐              ┌──────────┐
│ Original │              │ Original │
└──────────┘              └────┬─────┘
     │ COPY                    │ Sadece bak
     ↓                         ↓
┌──────────┐              (Referans)
│  Copy    │              Kopyalama YOK!
└──────────┘
Bellek: 2x                Bellek: 1x
```

**2. getType() Fonksiyonu:**
```cpp
const std::string& getType() const;
//^^^^^              ^^^^^    ^^^^^
//  1                  2        3

// 1. Dönüş tipi const referans → Değiştirilemez, kopyalanmaz
// 2. Referans döndür → Hızlı
// 3. Fonksiyon const → Nesneyi değiştirmez
```

**Implementation (Weapon.cpp):**
```cpp
#include "Weapon.hpp"

// Constructor: Silah tipini başlat
Weapon::Weapon(const std::string &type) : _type(type) {
    // Initialization list kullanarak _type'ı başlat
}

// Getter: Silah tipini döndür
const std::string &Weapon::getType() const {
    return (_type);  // _type'ın referansını döndür (kopyalama yok!)
}

// Setter: Silah tipini değiştir
void Weapon::setType(const std::string &newType) {
    _type = newType;  // _type'ı güncelle
}
```

#### HumanA - Referans Kullanır

**Header Dosyası (HumanA.hpp):**
```cpp
#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"
#include <string>

class HumanA {
public:
    HumanA(const std::string &name, Weapon &weapon);
    //                               ^^^^^^^^
    //                               Referans! (& var)
    void attack() const;

private:
    std::string _name;
    Weapon &_weapon;  // REFERANS! Her zaman geçerli bir silaha işaret eder
    //      ^
    //      Referans tipi
};

#endif
```

**Neden Referans?**
- ✅ HumanA **her zaman** bir silaha sahiptir
- ✅ Silah constructor'da verilir
- ✅ Silah değiştirilemez (başka silaha geçemez)
- ✅ NULL olamaz (güvenli)

**Implementation (HumanA.cpp):**
```cpp
#include "HumanA.hpp"
#include <iostream>

// Constructor: İsim ve silahı başlat
HumanA::HumanA(const std::string &name, Weapon &weapon) 
    : _name(name), _weapon(weapon) {
    // Initialization list ZORUNLU!
    // Çünkü referanslar başlatıldıktan sonra değiştirilemez
}
//  ^^^^^^^^^^^^^^^^^^^^^^^^
//  İkisi de initialization list ile başlatılıyor

// Attack fonksiyonu
void HumanA::attack() const {
    std::cout << _name << " attacks with their " 
              << _weapon.getType() << std::endl;
    //         ^^^^^^^^^
    //         Referans olduğu için . operatörü kullanılır
}
```

**Neden Initialization List Zorunlu?**
```cpp
// ❌ YANLIŞ: Referans constructor body'de atanamaz
HumanA::HumanA(const std::string &name, Weapon &weapon) {
    _name = name;     // OK (string assignment)
    _weapon = weapon;  // HATA! Referans yeniden atanamaz!
}

// ✅ DOĞRU: Initialization list kullan
HumanA::HumanA(const std::string &name, Weapon &weapon) 
    : _name(name), _weapon(weapon) {
    // Referans doğrudan başlatılır
}
```

#### HumanB - Pointer Kullanır

**Header Dosyası (HumanB.hpp):**
```cpp
#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>

class HumanB {
public:
    HumanB(const std::string &name);  // Silah YOK!
    void setWeapon(Weapon &weapon);   // Silahı sonradan ver
    void attack() const;

private:
    std::string _name;
    Weapon *_weapon;  // POINTER! NULL olabilir
    //      ^
    //      Pointer tipi
};

#endif
```

**Neden Pointer?**
- ✅ HumanB başlangıçta silahsız olabilir
- ✅ Silah daha sonra verilebilir (`setWeapon`)
- ✅ NULL olabilir (silahsız durum)
- ✅ Silah değiştirilebilir

**Implementation (HumanB.cpp):**
```cpp
#include "HumanB.hpp"
#include <iostream>

// Constructor: Sadece isim alır, silah yok!
HumanB::HumanB(const std::string &name) 
    : _name(name), _weapon(NULL) {
    // _weapon'ı NULL olarak başlat
    // Silah daha sonra setWeapon ile verilecek
}

// Silah ver fonksiyonu
void HumanB::setWeapon(Weapon &weapon) {
    _weapon = &weapon;  // Weapon'ın adresini al ve pointer'a ata
    //        ^
    //        Referansın adresini al
}

// Attack fonksiyonu
void HumanB::attack() const {
    if (_weapon)  // NULL kontrolü ZORUNLU!
        std::cout << _name << " attacks with their " 
                  << _weapon->getType() << std::endl;
        //         ^^^^^^^^^^
        //         Pointer olduğu için -> operatörü kullanılır
    else
        std::cout << _name << " attacks with their bare hands!" 
                  << std::endl;
        // Silah yoksa çıplak elle saldır
}
```

**Pointer İşlemleri:**
```cpp
// Adres alma
Weapon club("sword");
Weapon *ptr = &club;  // club'ın adresini al

// Dereferencing (değere erişim)
*ptr = club;  // Değer ataması

// Üye erişimi
ptr->getType();  // Pointer ile üye erişimi (-> operatörü)
(*ptr).getType();  // Aynı şey, ama daha karmaşık
```

#### main.cpp Kullanımı

```cpp
#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

int main() {
    // TEST 1: HumanA (Referans kullanır)
    {
        Weapon club = Weapon("crude spiked club");
        HumanA bob("Bob", club);  // Bob'a hemen silah ver
        //                 ^^^^
        //                 club'ı referans olarak ver
        
        bob.attack();  // "Bob attacks with their crude spiked club"
        
        club.setType("some other type of club");  // Silahı değiştir
        bob.attack();  // "Bob attacks with their some other type of club"
        // Bob'un silahı da değişti! (aynı nesneye referans)
    }
    
    // TEST 2: HumanB (Pointer kullanır)
    {
        Weapon club = Weapon("crude spiked club");
        HumanB jim("Jim");  // Jim silahsız başlıyor!
        
        jim.setWeapon(club);  // Şimdi silah ver
        //            ^^^^
        //            club'ın referansını ver (setWeapon içinde adres alınacak)
        
        jim.attack();  // "Jim attacks with their crude spiked club"
        
        club.setType("some other type of club");  // Silahı değiştir
        jim.attack();  // "Jim attacks with their some other type of club"
        // Jim'in silahı da değişti! (aynı nesneye pointer)
    }
    
    return 0;
}
```

#### Bellek Düzeni Karşılaştırması

**HumanA (Referans):**
```
Stack:
┌────────────────┐
│  Weapon club   │ ← "crude spiked club"
└────────┬───────┘
         │
         │ Referans (doğrudan bağlantı)
         ↓
┌────────────────┐
│  HumanA bob    │
│  _name: "Bob"  │
│  _weapon: &    │ ← club'a referans (her zaman geçerli)
└────────────────┘
```

**HumanB (Pointer):**
```
Stack:
┌────────────────┐
│  Weapon club   │ ← "crude spiked club" @ 0x7fff...
└────────────────┘
         ↑
         │ Pointer (adres tutar)
         │
┌────────────────┐
│  HumanB jim    │
│  _name: "Jim"  │
│  _weapon: 0x7..│ ← club'ın adresi (NULL olabilir)
└────────────────┘
```

#### Karar Ağacı: Referans mı Pointer mı?

```
Silah her zaman gerekli mi?
├─ EVET
│  └─ Referans kullan (HumanA)
│      ✅ Her zaman geçerli
│      ✅ NULL kontrolü gereksiz
│      ✅ Başlatıldıktan sonra değişmez
│
└─ HAYIR (opsiyonel)
   └─ Pointer kullan (HumanB)
       ✅ NULL olabilir
       ✅ Sonradan verilebilir
       ✅ Değiştirilebilir
       ⚠️  NULL kontrolü gerekli
```

### 🐛 Debug Adımları

#### Adım 1: Derleme
```bash
cd ex03
make
```

#### Adım 2: Test
```bash
./ex03
```

**Beklenen Çıktı:**
```
Bob attacks with their crude spiked club
Bob attacks with their some other type of club
Jim attacks with their crude spiked club
Jim attacks with their some other type of club
```

#### Adım 3: NULL Kontrolü Testi
HumanB.cpp'de `attack()` fonksiyonunu kontrol edin:
```cpp
void HumanB::attack() const {
    if (_weapon)  // NULL kontrolü gerekli!
        std::cout << _name << " attacks with their " 
                  << _weapon->getType() << std::endl;
    else
        std::cout << _name << " has no weapon!" << std::endl;
}
```

### ⚠️ Sık Yapılan Hatalar

1. **HumanA'da pointer kullanmak**
   ```cpp
   // ❌ Yanlış
   HumanA(std::string name, Weapon* weapon)
   ```

2. **HumanB'de referans kullanmak**
   ```cpp
   // ❌ Yanlış - başlangıçta silah olmayabilir!
   Weapon& _weapon;
   ```

3. **Getter'da değer döndürmek**
   ```cpp
   // ❌ Yavaş - kopyalama maliyeti
   std::string getType() const { return _type; }
   
   // ✅ Hızlı - referans döndürme
   const std::string& getType() const { return _type; }
   ```

---

## ex04: Sed is for losers

### 📋 Proje Amacı
Dosya işlemleri ve string manipülasyonu.

### 💡 Nasıl Çalışır?

#### Program Akışı

**1. Komut Satırı Argümanları**
```cpp
int main(int argc, char **argv)
```
- `argc` → Argüman sayısı
- `argv` → Argüman dizisi
- `argv[0]` → Program adı
- `argv[1]` → Dosya adı
- `argv[2]` → Aranacak string (s1)
- `argv[3]` → Yerine konacak string (s2)

**Kullanım:**
```bash
./replace dosya.txt "eski" "yeni"
           ^         ^      ^
        argv[1]   argv[2] argv[3]
```

**2. Argüman Kontrolü**
```cpp
if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
    return (1);
}
```
- `argc != 4` → Tam olarak 4 argüman olmalı (program adı + 3 parametre)
- `std::cerr` → Hata çıktısı (std::cout'tan farklı stream)
- `return (1)` → Hata kodu döndür

**3. Parametreleri Kaydet**
```cpp
std::string filename = argv[1];  // "dosya.txt"
std::string s1 = argv[2];         // "eski"
std::string s2 = argv[3];         // "yeni"
```
- `argv` char* dizisi → `std::string`'e dönüştür
- C++98'de otomatik dönüşüm var

**4. Dosyayı Aç (Input)**
```cpp
std::ifstream infile(filename.c_str());
//^^^^^^^^^         ^^^^^^^^^^^^^^^^
//  Tip              C string'e çevir (C++98 gereksinimi)

if (!infile.is_open()) {
    std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
    return (1);
}
```
- `std::ifstream` → Input File Stream (okuma için)
- `.c_str()` → C++98'de string'i const char*'a çevirir
- `is_open()` → Dosya başarıyla açıldı mı kontrol et
- Hata durumunda programı sonlandır

**5. Dosya İçeriğini Oku**
```cpp
std::string content;   // Tüm içerik buraya gelecek
std::string line;       // Her satır geçici olarak buraya
bool first = true;      // İlk satır mı kontrolü

while (std::getline(infile, line)) {
    if (!first)
        content += "\n";  // İlk satırdan sonra newline ekle
    content += line;       // Satırı ekle
    first = false;         // Artık ilk satır değil
}
infile.close();  // Dosyayı kapat
```

**Neden first değişkeni?**
```
Dosya içeriği:
Line1
Line2
Line3

Yanlış okuma:      Doğru okuma (first ile):
\nLine1            Line1
\nLine2            \nLine2
\nLine3            \nLine3
```

**getline() Nasıl Çalışır?**
```cpp
std::getline(infile, line)
//           ^       ^
//           |       └── Okunan satır buraya
//           └── Hangi dosyadan?

// Newline karakterini OKUR ama line'a EKLEMEZ!
// Her çağrıda bir sonraki satırı döndürür
// Dosya bitince false döner (while döngüsü biter)
```

#### replaceAll() Fonksiyonu - Detaylı Açıklama

```cpp
std::string replaceAll(const std::string &content, 
                       const std::string &s1,
                       const std::string &s2)
{
    size_t pos;    // Arama pozisyonu
    size_t found;  // Bulunan pozisyon
    
    // 1. BOŞ STRING KONTROLÜ
    if (s1.empty())
        return (content);
    // s1 boşsa değiştirme yapma (sonsuz döngü önleme)
    
    // 2. SONUÇ STRING'İ OLUŞTUR
    std::string result;  // Sonuç buraya birikecek
    pos = 0;  // Başlangıç pozisyonu
    
    // 3. TÜM EŞLEŞMELERİ BUL VE DEĞİŞTİR
    while ((found = content.find(s1, pos)) != std::string::npos) {
        //     ^^^^^^^^^^^^^^^^^^^^^         ^^^^^^^^^^^^^^^^^^^^
        //     s1'i pos'tan itibaren bul      npos = bulunamadı
        
        // a) Önceki kısmı ekle
        result.append(content, pos, found - pos);
        //            ^^^^^^^  ^^^  ^^^^^^^^^^^^
        //            Kaynak   Başlangıç  Uzunluk
        
        // b) Yeni string'i ekle
        result.append(s2);
        
        // c) Arama pozisyonunu güncelle
        pos = found + s1.length();
        //    ^^^^^   ^^^^^^^^^^^^
        //    Bulunan  s1'in uzunluğu kadar ilerle
    }
    
    // 4. KALAN KISMI EKLE
    result.append(content, pos, content.length() - pos);
    //            ^^^^^^^  ^^^  ^^^^^^^^^^^^^^^^^^^^^
    //            Kaynak   Başlangıç  Sonuna kadar
    
    return (result);
}
```

**Görsel Örnek:**
```
content = "Hello World Hello"
s1 = "Hello"
s2 = "Hi"

Adım 1: found = 0
  pos=0           found=0
  v               v
  Hello World Hello
  └─┬─┘
    s1 bulundu!

result.append(content, 0, 0);  // "" (boş)
result.append("Hi");            // "Hi"
pos = 0 + 5 = 5

Adım 2: found = 12
  pos=5                 found=12
      v                 v
  Hello World Hello
              └─┬─┘
                s1 bulundu!

result.append(content, 5, 7);  // " World "
result.append("Hi");            // "Hi"
pos = 12 + 5 = 17

Adım 3: found = npos (bulunamadı)
  pos=17
                      v
  Hello World Hello
                   └─┘
                   kalan

result.append(content, 17, 0);  // "" (kalan yok)

Sonuç: "Hi World Hi"
```

**std::string::find() Açıklaması:**
```cpp
size_t pos = str.find(search, start);
//             ^^^^   ^^^^^^  ^^^^^
//             String Aranan  Nereden başla

// Dönüş değerleri:
// - Bulunursa: İlk eşleşmenin index'i
// - Bulunamazsa: std::string::npos (genelde -1 veya en büyük sayı)
```

**std::string::append() Açıklaması:**
```cpp
// Versiyon 1: String ekle
result.append("text");

// Versiyon 2: Substring ekle
result.append(source, start, length);
//            ^^^^^^  ^^^^^  ^^^^^^
//            Kaynak  Başlangıç  Kaç karakter
```

**6. Çıktı Dosyası Oluştur**
```cpp
std::string outfilename = filename + ".replace";
// "dosya.txt" → "dosya.txt.replace"

std::ofstream outfile(outfilename.c_str());
//^^^^^^^^^         ^^^^^^^^^^^^^^^^^^^^
//Output file       C string'e çevir

if (!outfile.is_open()) {
    std::cerr << "Error: Could not create file '" << outfilename << "'" << std::endl;
    return (1);
}
```
- `std::ofstream` → Output File Stream (yazma için)
- Dosya yoksa oluşturur
- Varsa üzerine yazar (dikkat!)

**7. Sonucu Yaz**
```cpp
outfile << result;  // Tüm sonucu dosyaya yaz
outfile.close();    // Dosyayı kapat (önemli!)
```

**8. Başarı Mesajı**
```cpp
std::cout << "File processed successfully. Output: " << outfilename << std::endl;
return (0);  // Başarılı sonlanma
```

#### Tam Çalışma Örneği

**Input (test.txt):**
```
Hello World
Hello C++
Hello 42
```

**Komut:**
```bash
./replace test.txt "Hello" "Hi"
```

**Adım Adım:**
1. Dosyayı oku → `content = "Hello World\nHello C++\nHello 42"`
2. replaceAll çağır:
   - 1. Hello → Hi: `"Hi World\nHello C++\nHello 42"`
   - 2. Hello → Hi: `"Hi World\nHi C++\nHello 42"`
   - 3. Hello → Hi: `"Hi World\nHi C++\nHi 42"`
3. Sonucu yaz → `test.txt.replace`

**Output (test.txt.replace):**
```
Hi World
Hi C++
Hi 42
```

#### C++98 Özellikleri

**1. .c_str() Kullanımı**
```cpp
// C++98:
std::ifstream file(filename.c_str());  // const char* gerekli

// C++11+:
std::ifstream file(filename);  // std::string direkt alır
```

**2. size_t Tipi**
```cpp
size_t pos;  // İşaretsiz tam sayı (unsigned)
// String index'leri ve uzunlukları için kullanılır
// Negatif olamaz!
```

**3. std::string::npos**
```cpp
if (found == std::string::npos)
//           ^^^^^^^^^^^^^^^^^^^
//           "Not Position" - bulunamadı demek
//           Genelde en büyük size_t değeri (18446744073709551615)
```

### 🐛 Debug Adımları

#### Adım 1: Test Dosyası Oluştur
```bash
cd ex04
echo "Hello World Hello" > test.txt
```

#### Adım 2: Derleme ve Test
```bash
make
./replace test.txt Hello Hi
cat test.txt.replace
```

**Beklenen Çıktı:**
```
Hi World Hi
```

#### Adım 3: Edge Case'leri Test Et

**Test 1: Boş String**
```bash
./replace test.txt "" replacement
# Boş string kontrolü yapılmalı!
```

**Test 2: Bulunamayan String**
```bash
./replace test.txt "NotFound" "Something"
# Orijinal içerik korunmalı
```

**Test 3: Örtüşen Değiştirmeler**
```bash
echo "aaa" > test2.txt
./replace test2.txt "aa" "b"
# Beklenen: "ba" (ilk "aa" değişir, kalan "a")
```

**Test 4: Özel Karakterler**
```bash
echo "a\nb\nc" > test3.txt
./replace test3.txt "\n" " "
# Newline karakterleri literal olarak işlenmeli
```

### ⚠️ Sık Yapılan Hatalar

1. **C++98'de .c_str() unutmak**
   ```cpp
   // ❌ C++98'de hata verir
   std::ifstream infile(filename);
   
   // ✅ Doğru
   std::ifstream infile(filename.c_str());
   ```

2. **Dosya açma kontrolü yapmamak**
   ```cpp
   // ✅ Her zaman kontrol et
   if (!infile.is_open()) {
       std::cerr << "Error opening file" << std::endl;
       return 1;
   }
   ```

3. **Newline karakterlerini kaybetmek**
   ```cpp
   // ❌ Son satırda newline yok
   while (std::getline(infile, line))
       content += line;
   
   // ✅ Newline'ları koru
   bool first = true;
   while (std::getline(infile, line)) {
       if (!first) content += "\n";
       content += line;
       first = false;
   }
   ```

---

## ex05: Harl 2.0

### 📋 Proje Amacı
Member function pointer'ları öğrenmek.

### 💡 Nasıl Çalışır?

#### Harl Sınıfı (Harl.hpp)

```cpp
#ifndef _Harl_
#define _Harl_

#include <iostream>

class Harl {
public:
    Harl();   // Constructor
    ~Harl();  // Destructor
    void complain(std::string level);  // Şikayet fonksiyonu

private:
    void debug(void);    // DEBUG seviyesi
    void info(void);     // INFO seviyesi
    void warning(void);  // WARNING seviyesi
    void error(void);    // ERROR seviyesi
};

#endif
```

**Tasarım:**
- 4 private fonksiyon → Sadece `complain()` üzerinden erişilebilir
- `complain()` public → Dışarıdan çağrılabilir
- String parametresi → "DEBUG", "INFO", "WARNING", "ERROR"

#### Harl Implementation (Harl.cpp)

**1. Constructor ve Destructor**
```cpp
Harl::Harl() {
    // Boş - özel initialization gerekmiyor
}

Harl::~Harl() {
    // Boş - özel cleanup gerekmiyor
}
```

**2. Şikayet Fonksiyonları**
```cpp
void Harl::debug(void) {
    std::cout << "[ DEBUG ]\n"
              << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!\n";
}

void Harl::info(void) {
    std::cout << "[ INFO ]\n"
              << "I cannot believe adding extra bacon costs more money. "
              << "You didn't put enough bacon in my burger! "
              << "If you did, I wouldn't be asking for more!\n";
}

void Harl::warning(void) {
    std::cout << "[ WARNING ]\n"
              << "I think I deserve to have some extra bacon for free. "
              << "I've been coming for years, whereas you started working here just last month.\n";
}

void Harl::error(void) {
    std::cout << "[ ERROR ]\n"
              << "This is unacceptable! I want to speak to the manager now.\n";
}
```

**3. complain() Fonksiyonu - Ana Mantık**

```cpp
void Harl::complain(std::string level) {
    // ADIM 1: Member Function Pointer Tipi Tanımla
    typedef void (Harl::*HarlMemFn)(void);
    //      ^^^^  ^^^^^^^           ^^^^^^
    //      Dönüş Sınıf::*          Parametreler
    //      tipi   (member ptr)
    
    // HarlMemFn artık bir tip ismi
    // "Harl sınıfının void döndüren, parametre almayan member fonksiyonu"
    
    // ADIM 2: Seviye İsimleri Dizisi
    const char *levell[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    //          ^^^^^^^^
    //          C-style string dizisi
    
    // ADIM 3: Fonksiyon Pointer Dizisi
    HarlMemFn funcs[] = {&Harl::debug, &Harl::info, 
                         &Harl::warning, &Harl::error};
    //                   ^^^^^^^^^^^^
    //                   Member fonksiyonun adresi
    
    // ADIM 4: Eşleşeni Bul ve Çağır
    for (int i = 0; i < 4; ++i) {
        if (level == levell[i]) {
            // Eşleşme bulundu!
            (this->*funcs[i])();
            //^^^^   ^^^^^^^^
            //this   fonksiyon pointer'ı
            //       Member function call syntax
            return;  // İşimiz bitti, çık
        }
    }
    
    // ADIM 5: Hiç eşleşme yoksa
    std::cout << "[ Probably complaining about insignificant problems ]\n";
}
```

#### Member Function Pointer Detayları

**Syntax Açıklaması:**
```cpp
// Normal fonksiyon pointer:
void (*funcPtr)(void);  // Global/static fonksiyon

// Member function pointer:
void (ClassName::*memFuncPtr)(void);  // Sınıf üye fonksiyonu
//    ^^^^^^^^^
//    Sınıf adı ve ::* gerekli!
```

**Adres Alma:**
```cpp
// Normal fonksiyon:
funcPtr = &functionName;

// Member fonksiyon:
memFuncPtr = &ClassName::functionName;
//           ^^^^^^^^^^^
//           Sınıf adı zorunlu!
```

**Çağırma:**
```cpp
// Normal pointer:
(*funcPtr)();
funcPtr();  // Kısayol

// Member pointer (nesne ile):
(object.*memFuncPtr)();
//      ^^
//      .* operatörü (dot-star)

// Member pointer (pointer ile):
(objectPtr->*memFuncPtr)();
//         ^^^
//         ->* operatörü (arrow-star)
```

#### complain() Çalışma Örneği

**Senaryo: level = "WARNING"**

```
1. Diziler oluşturulur:
levell[]:  ["DEBUG", "INFO", "WARNING", "ERROR"]
funcs[]:   [&debug,  &info,  &warning,  &error ]

2. For döngüsü:
i=0: "WARNING" == "DEBUG"?   → Hayır, devam
i=1: "WARNING" == "INFO"?    → Hayır, devam
i=2: "WARNING" == "WARNING"? → EVET!
     (this->*funcs[2])();
     (this->*&Harl::warning)();
     warning() çağrıldı!
     return;

3. Çıktı:
[ WARNING ]
I think I deserve to have some extra bacon for free...
```

**Senaryo: level = "INVALID"**

```
1. For döngüsü:
i=0: "INVALID" == "DEBUG"?   → Hayır
i=1: "INVALID" == "INFO"?    → Hayır
i=2: "INVALID" == "WARNING"? → Hayır
i=3: "INVALID" == "ERROR"?   → Hayır

2. Döngü biter, hiç eşleşme yok

3. Default mesaj:
[ Probably complaining about insignificant problems ]
```

#### Bellek Düzeni

```cpp
HarlMemFn funcs[4];
```

**Bellekte:**
```
funcs dizisi:
┌──────────────────┐
│ &Harl::debug     │ ← funcs[0]
├──────────────────┤
│ &Harl::info      │ ← funcs[1]
├──────────────────┤
│ &Harl::warning   │ ← funcs[2]
├──────────────────┤
│ &Harl::error     │ ← funcs[3]
└──────────────────┘

levell dizisi:
┌──────────────────┐
│ "DEBUG"          │ ← levell[0]
├──────────────────┤
│ "INFO"           │ ← levell[1]
├──────────────────┤
│ "WARNING"        │ ← levell[2]
├──────────────────┤
│ "ERROR"          │ ← levell[3]
└──────────────────┘

İndeksler paralel!
```

#### main.cpp Kullanımı

```cpp
#include "Harl.hpp"

int main() {
    Harl software;  // Harl nesnesi oluştur
    
    // Seviye dizisi
    std::string level[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    
    // Her seviyeyi test et
    for(int i = 0; i < 4; i++) {
        std::cout << level[i] << std::endl;
        //          ^^^^^^^^
        //          Hangi seviye çağrılacak yazdır
        
        software.complain(level[i]);
        //       ^^^^^^^^ ^^^^^^^^
        //       Fonksiyon Parametre
        
        std::cout << std::endl;  // Boş satır
    }
    
    return 0;
}
```

**Çıktı:**
```
DEBUG
[ DEBUG ]
I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger...

INFO
[ INFO ]
I cannot believe adding extra bacon costs more money...

WARNING
[ WARNING ]
I think I deserve to have some extra bacon for free...

ERROR
[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

#### Neden Function Pointer?

**Alternatif 1: If-Else Zinciri (Kötü)**
```cpp
void complain(std::string level) {
    if (level == "DEBUG")
        debug();
    else if (level == "INFO")
        info();
    else if (level == "WARNING")
        warning();
    else if (level == "ERROR")
        error();
    else
        std::cout << "Invalid\n";
}
```
❌ Uzun ve tekrarlı
❌ Yeni seviye eklemek zor
❌ Okunması zor

**Alternatif 2: Function Pointer Array (İyi)**
```cpp
void complain(std::string level) {
    typedef void (Harl::*HarlMemFn)(void);
    const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    HarlMemFn funcs[] = {&Harl::debug, &Harl::info, 
                         &Harl::warning, &Harl::error};
    for (int i = 0; i < 4; ++i) {
        if (level == levels[i]) {
            (this->*funcs[i])();
            return;
        }
    }
}
```
✅ Temiz ve düzenli
✅ Yeni seviye eklemek kolay (sadece diziye ekle)
✅ Veri odaklı tasarım

#### typedef Kullanımı

**typedef Nedir?**
```cpp
// Uzun tip isimlerini kısaltır
typedef void (Harl::*HarlMemFn)(void);
//      ^^^^^^^^^^^^^^^^^^^^^^^  ^^^^^^^^^^
//      Asıl tip                 Yeni isim

// Kullanım:
HarlMemFn ptr;  // void (Harl::*ptr)(void); ile aynı
```

**Neden Kullanılır?**
```cpp
// typedef OLMADAN:
void (Harl::*funcs[])(void) = {...};  // Okuması zor!

// typedef İLE:
typedef void (Harl::*HarlMemFn)(void);
HarlMemFn funcs[] = {...};  // Çok daha okunaklı!
```

#### this Pointer'ı

**this Nedir?**
```cpp
class Harl {
    void complain(std::string level) {
        (this->*funcs[i])();
        //^^^^
        //this = Bu nesnenin pointer'ı
    }
};

Harl h1;
h1.complain("DEBUG");  // this = &h1

Harl h2;
h2.complain("INFO");   // this = &h2
```

**this Kullanım Şekilleri:**
```cpp
this->member;    // Member variable/function erişimi
(*this).member;  // Aynı şey (daha az kullanılır)
this->*ptr;      // Member function pointer çağrısı
```

### 🔍 Member Function Pointer Syntax

```cpp
// Tip tanımı
typedef void (ClassName::*FuncPtr)(void);

// Adres alma
FuncPtr ptr = &ClassName::functionName;

// Çağırma
(object.*ptr)();      // Object ile
(objectPtr->*ptr)();  // Pointer ile
```

### 🐛 Debug Adımları

#### Adım 1: Derleme ve Test
```bash
cd ex05
make
./Harl
```

**Beklenen Çıktı:**
```
DEBUG
[ DEBUG ]
I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger...

INFO
[ INFO ]
I cannot believe adding extra bacon costs more money...

WARNING
[ WARNING ]
I think I deserve to have some extra bacon for free...

ERROR
[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

#### Adım 2: Geçersiz Level Testi
main.cpp'yi düzenleyin:
```cpp
harl.complain("INVALID");
```
**Beklenen:** "Probably complaining about insignificant problems"

### 🎯 Alternatif Yaklaşımlar (Eğitim Amaçlı)

**Yaklaşım 1: If-else zinciri (❌ Kötü)**
```cpp
if (level == "DEBUG") debug();
else if (level == "INFO") info();
else if (level == "WARNING") warning();
else if (level == "ERROR") error();
```

**Yaklaşım 2: Map kullanımı (❌ C++98'de karmaşık)**
```cpp
std::map<std::string, HarlMemFn> funcMap;
funcMap["DEBUG"] = &Harl::debug;
// ...
```

**Yaklaşım 3: Function pointer array (✅ Temiz ve verimli)**
```cpp
// Kullandığımız yöntem - O(n) ama temiz
```

---

## ex06: Harl filter

### 📋 Proje Amacı
Switch-case ve fall-through mekanizmasını öğrenmek.

### 💡 Nasıl Çalışır?

#### Yardımcı Fonksiyon: getLevelIndex()

```cpp
int getLevelIndex(std::string level) {
    const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    //          ^^^^^^^^
    //          Seviye isimleri dizisi
    
    for (int i = 0; i < 4; ++i) {
        if (level == levels[i])
            return (i);  // Eşleşen seviyenin index'ini döndür
    }
    
    return (-1);  // Bulunamadı
}
```

**Dönüş Değerleri:**
```
"DEBUG"   → 0
"INFO"    → 1
"WARNING" → 2
"ERROR"   → 3
"INVALID" → -1
```

#### main() Fonksiyonu - Detaylı

```cpp
int main(int argc, char **argv) {
    // ADIM 1: Argüman Kontrolü
    if (argc != 2) {
        std::cerr << "Usage: ./harlFilter <level>" << std::endl;
        return (1);
    }
    // argc = 1 → Sadece program adı (hata!)
    // argc = 2 → Program adı + seviye (doğru!)
    // argc > 2 → Fazla argüman (hata!)
    
    // ADIM 2: Harl Nesnesi Oluştur
    Harl harl;
    
    // ADIM 3: Seviye Index'ini Al
    int levelIndex = getLevelIndex(argv[1]);
    //               ^^^^^^^^^^^^^^^^^^^^^^^^
    //               argv[1] = kullanıcının girdiği seviye
    
    // ADIM 4: Switch-Case ile Filtreleme
    switch (levelIndex) {
        case 0:  // DEBUG seviyesi
            harl.complain("DEBUG");
            std::cout << std::endl;
            // ⚠️ break YOK! Devam eder (fall-through)
            
        case 1:  // INFO seviyesi
            harl.complain("INFO");
            std::cout << std::endl;
            // ⚠️ break YOK! Devam eder
            
        case 2:  // WARNING seviyesi
            harl.complain("WARNING");
            std::cout << std::endl;
            // ⚠️ break YOK! Devam eder
            
        case 3:  // ERROR seviyesi
            harl.complain("ERROR");
            std::cout << std::endl;
            break;  // ✅ Burada dur!
            
        default:  // Geçersiz seviye
            std::cout << "[ Probably complaining about insignificant problems ]" 
                      << std::endl;
    }
    
    return (0);
}
```

#### Switch-Case Fall-Through Mekanizması

**Fall-Through Nedir?**
```cpp
switch (x) {
    case 1:
        statement1;
        // break yok!
    case 2:
        statement2;
        break;
}

// x = 1 ise:
// statement1 çalışır
// break olmadığı için case 2'ye de girer
// statement2 de çalışır
// break görülünce durur
```

**Normal Kullanım (break ile):**
```cpp
switch (x) {
    case 1:
        statement1;
        break;  // Durur, case 2'ye girmez
    case 2:
        statement2;
        break;
}
```

#### ex06'daki Fall-Through Kullanımı

**Amaç:** Belirtilen seviyeden itibaren TÜM seviyeleri göster

**Örnek 1: levelIndex = 0 (DEBUG)**
```
switch (0) {
    case 0:  ← BURADAN BAŞLA
        DEBUG mesajı yazdır
        (break yok, devam)
    case 1:  ← BURAYA DA GİR
        INFO mesajı yazdır
        (break yok, devam)
    case 2:  ← BURAYA DA GİR
        WARNING mesajı yazdır
        (break yok, devam)
    case 3:  ← BURAYA DA GİR
        ERROR mesajı yazdır
        break;  ← BURADA DUR
}

Çıktı: DEBUG, INFO, WARNING, ERROR (hepsi!)
```

**Örnek 2: levelIndex = 2 (WARNING)**
```
switch (2) {
    case 0:  ← ATLA
        (çalışmaz)
    case 1:  ← ATLA
        (çalışmaz)
    case 2:  ← BURADAN BAŞLA
        WARNING mesajı yazdır
        (break yok, devam)
    case 3:  ← BURAYA DA GİR
        ERROR mesajı yazdır
        break;  ← BURADA DUR
}

Çıktı: WARNING, ERROR
```

**Örnek 3: levelIndex = -1 (INVALID)**
```
switch (-1) {
    case 0:  ← UYUŞMUYOR
    case 1:  ← UYUŞMUYOR
    case 2:  ← UYUŞMUYOR
    case 3:  ← UYUŞMUYOR
    default: ← BURAYA GİR
        Invalid mesajı yazdır
}

Çıktı: [ Probably complaining about insignificant problems ]
```

#### Detaylı Akış Diyagramı

```
Kullanıcı: ./harlFilter WARNING

1. argc kontrolü:
   argc = 2 ✅ OK

2. getLevelIndex("WARNING"):
   i=0: "WARNING" == "DEBUG"?   → Hayır
   i=1: "WARNING" == "INFO"?    → Hayır
   i=2: "WARNING" == "WARNING"? → Evet! return 2

3. levelIndex = 2

4. switch (2):
   ┌────────────┐
   │ case 0?    │ → Hayır, atla
   ├────────────┤
   │ case 1?    │ → Hayır, atla
   ├────────────┤
   │ case 2? ✅ │ → Evet! Buradan başla
   │            │
   │ WARNING    │ → Yazdır
   │ endl       │ → Yeni satır
   │ (no break) │ → Devam et ↓
   ├────────────┤
   │ case 3?    │ → Zaten içerdeyiz, çalıştır
   │            │
   │ ERROR      │ → Yazdır
   │ endl       │ → Yeni satır
   │ break;     │ → DUR! ■
   └────────────┘

Çıktı:
[ WARNING ]
I think I deserve to have some extra bacon for free...

[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

#### Kullanım Örnekleri

**Test 1: DEBUG**
```bash
$ ./harlFilter DEBUG
[ DEBUG ]
I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!

[ INFO ]
I cannot believe adding extra bacon costs more money...

[ WARNING ]
I think I deserve to have some extra bacon for free...

[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

**Test 2: INFO**
```bash
$ ./harlFilter INFO
[ INFO ]
I cannot believe adding extra bacon costs more money...

[ WARNING ]
I think I deserve to have some extra bacon for free...

[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

**Test 3: WARNING**
```bash
$ ./harlFilter WARNING
[ WARNING ]
I think I deserve to have some extra bacon for free...

[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

**Test 4: ERROR**
```bash
$ ./harlFilter ERROR
[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

**Test 5: Geçersiz**
```bash
$ ./harlFilter RANDOM
[ Probably complaining about insignificant problems ]
```

**Test 6: Parametre Yok**
```bash
$ ./harlFilter
Usage: ./harlFilter <level>
```

#### Switch-Case Detayları

**1. case Değerleri**
```cpp
switch (expression) {
    case constant_value:  // Sabit değer olmalı!
        statements;
        break;
}

// ✅ Geçerli:
case 0:
case 'A':
case MY_CONSTANT:

// ❌ Geçersiz:
case x:         // Değişken kullanılamaz
case 1 + y:     // Expression olamaz
```

**2. default Case**
```cpp
switch (x) {
    case 1:
        // ...
        break;
    default:  // Hiçbir case uymazsa
        // ...
        break;  // default'ta break opsiyonel (zaten sonda)
}
```

**3. break'in Önemi**
```cpp
// ⚠️ Unutulan break:
switch (x) {
    case 1:
        std::cout << "One";
        // break unutuldu!
    case 2:
        std::cout << "Two";
        break;
}

// x = 1 için çıktı: "OneTwo" (her ikisi de çalışır!)
```

**4. Birden Fazla Case, Aynı Kod**
```cpp
switch (x) {
    case 1:
    case 2:
    case 3:
        std::cout << "1, 2 veya 3";
        break;
    case 4:
    case 5:
        std::cout << "4 veya 5";
        break;
}
```

#### ex05 vs ex06 Farkları

**ex05: Tüm Seviyeleri Göster**
```cpp
for (int i = 0; i < 4; i++) {
    harl.complain(level[i]);
}
// Çıktı: DEBUG, INFO, WARNING, ERROR (sırayla)
```

**ex06: Filtreli Gösterim**
```cpp
switch (levelIndex) {
    case 0:  // DEBUG'tan başla
        // DEBUG, INFO, WARNING, ERROR göster
    case 2:  // WARNING'den başla
        // WARNING, ERROR göster
}
```

**Karşılaştırma Tablosu:**

| Özellik | ex05 | ex06 |
|---------|------|------|
| **Amaç** | Hepsini göster | Filtreleyerek göster |
| **Girdi** | Yok (sabit) | Komut satırı argümanı |
| **Mekanizma** | For döngüsü | Switch-case fall-through |
| **Çıktı** | Hep 4 mesaj | Seçilen seviyeden itibaren |

#### Gerçek Hayat Analojisi

**Alarm Seviyeleri:**
```
Level 4 (ERROR):   🚨 Kritik - Tüm alarmlar çalsın!
                   ├─ Level 4 alarm ✓
                   ├─ Level 3 alarm ✓
                   ├─ Level 2 alarm ✓
                   └─ Level 1 alarm ✓

Level 2 (WARNING): ⚠️  Uyarı - Orta seviyeden başla
                   ├─ Level 2 alarm ✓
                   ├─ Level 1 alarm ✓
                   └─ (Level 3-4 çalmasın)
```

Switch-case fall-through bu mantığı uygular:
- ERROR → Her şey çalışır
- WARNING → WARNING ve ERROR
- INFO → INFO, WARNING, ERROR
- DEBUG → Hepsi

#### Kod Optimizasyonu

**Verimsiz Yaklaşım:**
```cpp
if (levelIndex == 0) {
    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
}
else if (levelIndex == 1) {
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
}
// ... çok tekrar var!
```

**Verimli Yaklaşım (ex06):**
```cpp
switch (levelIndex) {
    case 0: harl.complain("DEBUG");
    case 1: harl.complain("INFO");
    case 2: harl.complain("WARNING");
    case 3: harl.complain("ERROR");
            break;
}
// Fall-through ile tekrar yok!
```

### 🐛 Debug Adımları

#### Test 1: DEBUG seviyesi
```bash
./Harlfilter DEBUG
```
**Beklenen:** Tüm mesajlar (DEBUG, INFO, WARNING, ERROR)

#### Test 2: INFO seviyesi
```bash
./Harlfilter INFO
```
**Beklenen:** INFO, WARNING, ERROR (DEBUG yok)

#### Test 3: WARNING seviyesi
```bash
./Harlfilter WARNING
```
**Beklenen:** WARNING, ERROR (DEBUG ve INFO yok)

#### Test 4: ERROR seviyesi
```bash
./Harlfilter ERROR
```
**Beklenen:** Sadece ERROR

#### Test 5: Geçersiz seviye
```bash
./Harlfilter INVALID
```
**Beklenen:** "Probably complaining about insignificant problems"

#### Test 6: Parametre kontrolü
```bash
./Harlfilter
```
**Beklenen:** "Usage: ./harlFilter <level>"

### 🎯 Fall-through Mekanizması

```
WARNING verilirse:
├─ case 0 (DEBUG): atla
├─ case 1 (INFO): atla
├─ case 2 (WARNING): ✓ buradan başla
│   ├─ WARNING yazdır
│   └─ break yok, devam et ↓
├─ case 3 (ERROR): ✓ buraya da gir
│   ├─ ERROR yazdır
│   └─ break var, dur!
```

### ⚠️ Dikkat Edilmesi Gerekenler

1. **Fall-through kasıtlıdır!** Normal kodda genelde hata olarak kabul edilir
2. **Default case önemli** - geçersiz girişleri yakalar
3. **Break yerleştirme** - sadece ERROR'dan sonra break

---

## 🛠️ Genel Debug Teknikleri

### 1. Compilation Flags
```bash
# Daha fazla uyarı için
c++ -Wall -Wextra -Werror -Wpedantic -std=c++98

# Debug bilgisi ekle
c++ -g -Wall -Wextra -Werror -std=c++98
```

### 2. GDB Kullanımı
```bash
# Derleme
make

# GDB ile çalıştır
gdb ./program

# GDB komutları
(gdb) break main        # main'de breakpoint
(gdb) run              # Başlat
(gdb) step             # Adım adım ilerle
(gdb) print variable   # Değişken değerini göster
(gdb) backtrace        # Call stack'i göster
(gdb) quit             # Çık
```

### 3. Bellek Kontrolü
```bash
# macOS
leaks -atExit -- ./program

# Linux
valgrind --leak-check=full --show-leak-kinds=all ./program
```

### 4. Print Debug
```cpp
// Geçici debug için
#include <iostream>
std::cout << "DEBUG: variable = " << variable << std::endl;

// Fonksiyon çağrı takibi
std::cout << __FUNCTION__ << " called" << std::endl;
std::cout << __FILE__ << ":" << __LINE__ << std::endl;
```

---

## 📚 Önemli Kavramlar Özeti

### Stack vs Heap
- **Stack:** Otomatik, hızlı, sınırlı boyut
- **Heap:** Manuel, yavaş, büyük boyut

### Pointer vs Referans
- **Pointer:** NULL olabilir, yeniden atanabilir, `->` kullanır
- **Referans:** NULL olamaz, sabit, `.` kullanır

### Memory Management
- `new` ↔ `delete`
- `new[]` ↔ `delete[]`
- Her `new` için mutlaka `delete`

### File Operations
- Her zaman açılma kontrolü yapın
- C++98'de `.c_str()` kullanın
- Dosyayı kapamayı unutmayın

### Function Pointers
- Normal: `void (*ptr)(void)`
- Member: `void (Class::*ptr)(void)`
- Çağırma: `(object.*ptr)()` veya `(ptr->*ptr)()`

---

## 🎓 İleri Seviye Notlar

### C++98 vs Modern C++ Farkları

```cpp
// C++98
std::ifstream file(filename.c_str());
for (int i = 0; i < n; i++) { }

// C++11+
std::ifstream file(filename);
for (auto i = 0; i < n; i++) { }
```

### Orthodox Canonical Form
Her sınıf için düşünülmesi gerekenler:
1. Default Constructor
2. Copy Constructor
3. Copy Assignment Operator
4. Destructor

Örnek:
```cpp
class MyClass {
public:
    MyClass();                              // Default
    MyClass(const MyClass& other);          // Copy
    MyClass& operator=(const MyClass& rhs); // Assignment
    ~MyClass();                             // Destructor
};
```

---

## 📖 Kaynaklar ve Referanslar

- **C++ Reference:** https://cppreference.com
- **C++98 Standard**
- **Effective C++** by Scott Meyers
- **42 Subject PDF'leri**

---

**Son Güncelleme:** 7 Aralık 2025
**Hazırlayan:** GitHub Copilot
**Modül:** CPP01 - Memory allocation, pointers to members, references, switch statement
