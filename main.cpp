/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>

// -----------------------------------------------------------------
// 2) SINIF (Class)
// Bir "Arac" için bir plan (blueprint) tanımlıyoruz.
// Bu sınıf aynı zamanda "Soyut" bir sınıftır.
// -----------------------------------------------------------------
class Arac {

// 4) KAPSÜLLEME (Encapsulation)
// 'protected', bu değişkenlere sadece bu sınıfın ve ondan MİRAS alan
// alt sınıfların (Otomobil, Motosiklet) erişebileceği anlamına gelir.
// 'main' gibi dış fonksiyonlar doğrudan erişemez.
protected:
    std::string marka;
    int hiz;

public:
    // Yapıcı metod (Constructor)
    Arac(std::string m) : marka(m), hiz(0) {
        // 'marka' ve 'hiz' değişkenleri burada başlatıldı.
    }

    // 3) SOYUTLAMA (Abstraction)
    // Dış dünya, bir aracın nasıl hızlandığının detaylarını (motorun nasıl
    // çalıştığı, yakıtın nasıl püskürtüldüğü vb.) bilmek zorunda değil.
    // Sadece "hizlan" komutunu bilmesi yeterlidir. Bu metod, karmaşıklığı gizler.
    void hizlan(int artis) {
        hiz += artis;
        std::cout << marka << " hızlanıyor. Yeni hız: " << hiz << " km/s" << std::endl;
    }

    void yavasla(int azalis) {
        hiz -= azalis;
        if (hiz < 0) hiz = 0;
        std::cout << marka << " yavaşlıyor. Yeni hız: " << hiz << " km/s" << std::endl;
    }

    // 3) SOYUTLAMA (Daha ileri bir örnek: Pure Virtual Function)
    // Bu fonksiyon, "Her araç bir şekilde çalışmalıdır" der,
    // ama NASIL çalıştığını söylemez. Bu detayı alt sınıflara bırakır.
    // Bu satır, 'Arac' sınıfını SOYUT (Abstract) bir sınıf yapar.
    // Yani, doğrudan bir 'Arac' nesnesi oluşturulamaz.
    virtual void calistir() = 0; 

    // 6) POLİMORFİZM (Polymorphism)
    // 'virtual' anahtar kelimesi, bu fonksiyonun alt sınıflar tarafından
    // "ezilebileceğini" (override) belirtir.
    virtual void kornaCal() {
        std::cout << "Genel araç kornası!" << std::endl;
    }

    // Sanal yıkıcı metod (Best practice)
    virtual ~Arac() {} 
};

// -----------------------------------------------------------------
// 5) MİRAS (Inheritance)
// 'Otomobil' sınıfı, 'public Arac' ifadesiyle 'Arac' sınıfından miras alıyor.
// 'Otomobil' artık bir 'Arac'tır ve onun tüm 'protected'/'public' özelliklerine sahiptir.
// -----------------------------------------------------------------
class Otomobil : public Arac {
private:
    int kapiSayisi; // Otomobil'e özel bir özellik

public:
    // Otomobil'in yapıcı metodu, önce base sınıf (Arac) yapıcı metodunu çağırır.
    Otomobil(std::string m, int kapi) : Arac(m), kapiSayisi(kapi) {}

    // Soyut (pure virtual) olan 'calistir' fonksiyonunu burada tanımlamak ZORUNDAYIZ.
    void calistir() override {
        std::cout << marka << " (Otomobil) kontağı çevrilerek çalıştı." << std::endl;
    }

    // 6) POLİMORFİZM (Polymorphism)
    // 'Arac' sınıfındaki 'kornaCal' fonksiyonunu yeniden tanımlıyoruz (override).
    void kornaCal() override {
        std::cout << marka << " (Otomobil) diyor ki: DÜT DÜT!" << std::endl;
    }
};

// -----------------------------------------------------------------
// 5) MİRAS (Inheritance)
// 'Motosiklet' sınıfı da 'Arac' sınıfından miras alıyor.
// -----------------------------------------------------------------
class Motosiklet : public Arac {
public:
    Motosiklet(std::string m) : Arac(m) {}

    // 'calistir' fonksiyonunu Motosiklet'e özel tanımlıyoruz.
    void calistir() override {
        std::cout << marka << " (Motosiklet) marşa basılarak çalıştı." << std::endl;
    }

    // 6) POLİMORFİZM (Polymorphism)
    // 'kornaCal' fonksiyonunu Motosiklet'e özel yeniden tanımlıyoruz.
    void kornaCal() override {
        std::cout << marka << " (Motosiklet) diyor ki: BİP BİP!" << std::endl;
    }
};

// --- Polimorfizmi Göstermek İçin Yardımcı Bir Fonksiyon ---
// Bu fonksiyon, bir 'Arac' pointer'ı alır.
// Gelen nesnenin 'Otomobil' mi 'Motosiklet' mi olduğunu BİLMEZ.
// Sadece onun bir 'Arac' olduğunu bilir.
void araciSur(Arac* aracPtr) {
    std::cout << "--- Araç Sürüş Testi ---" << std::endl;
    aracPtr->calistir(); // Hangi nesne geldiyse (Oto/Moto) ONUN 'calistir' metodu çalışır.
    aracPtr->kornaCal(); // Hangi nesne geldiyse ONUN 'kornaCal' metodu çalışır.
    aracPtr->hizlan(30);
    std::cout << "-------------------------" << std::endl;
}


int main() {
    // 1) NESNE (Object)
    // 'Otomobil' ve 'Motosiklet' SINIFLARINDAN 'nesneler' (örnekler) oluşturuyoruz.
    Otomobil myCar("Ford", 4);
    Motosiklet myBike("Yamaha");

    // 'Arac' soyut bir sınıf olduğu için bunu yapamayız:
    // Arac genelArac("Genel"); // HATA! 'calistir' pure virtual olduğu için.

    std::cout << "\n*** Doğrudan Nesne Çağrıları ***" << std::endl;
    myCar.calistir();
    myCar.kornaCal();
    
    myBike.calistir();
    myBike.kornaCal();

    // 4) KAPSÜLLEME (Encapsulation) Kanıtı
    // 'hiz' değişkeni 'protected' olduğu için ona dışarıdan doğrudan erişemeyiz.
    // myCar.hiz = 100; // HATA!
    // Hızı değiştirmek için public metodu (Soyutlama arayüzünü) kullanmalıyız:
    myCar.hizlan(50); // Bu çalışır.

    // 6) POLİMORFİZM (Polymorphism) Kanıtı
    std::cout << "\n*** Polimorfizm Testi (araciSur fonksiyonu) ***" << std::endl;
    
    // 'araciSur' fonksiyonuna 'Otomobil' nesnesinin adresini veriyoruz.
    // 'Otomobil', 'Arac' sınıfından türediği için bu geçerlidir.
    araciSur(&myCar);

    // Aynı 'araciSur' fonksiyonuna şimdi de 'Motosiklet' nesnesinin adresini veriyoruz.
    // Fonksiyon, nesnenin türüne göre (Otomobil veya Motosiklet)
    // FARKLI 'kornaCal' ve 'calistir' metotlarını (formlarını) çağırdı.
    // "Polimorfizm" (Çok Biçimlilik) budur.
    araciSur(&myBike);

    return 0;
}
