# ESP32_skolni_projekt

Školní projekt pro ESP32S2

## Použité zařízení
ESP32S2

## Požadavky
- ESP-IDF framework (v4.4 nebo novější)
- ESP32S2 vývojová deska

## Instalace ESP-IDF
Pokud ještě nemáte nainstalovaný ESP-IDF, postupujte podle oficiálního průvodce:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/get-started/

## Struktura projektu
```
ESP32_skolni_projekt/
├── main/
│   ├── CMakeLists.txt
│   └── main.c
├── CMakeLists.txt
├── sdkconfig.defaults
└── README.md
```

## Jak sestavit a nahrát projekt

1. Nastavte ESP-IDF prostředí:
```bash
. $HOME/esp/esp-idf/export.sh
```

2. Nastavte target na ESP32S2:
```bash
idf.py set-target esp32s2
```

3. Sestavte projekt:
```bash
idf.py build
```

4. Nahrajte do ESP32S2 (nahraďte PORT vaším portem, např. /dev/ttyUSB0 nebo COM3):
```bash
idf.py -p PORT flash
```

5. Zobrazte výstup ze sériové konzole:
```bash
idf.py -p PORT monitor
```

Nebo vše najednou:
```bash
idf.py -p PORT flash monitor
```

## Konfigurace
Projekt je předkonfigurovaný pro ESP32S2 v souboru `sdkconfig.defaults`. Pro další nastavení použijte:
```bash
idf.py menuconfig
```

## Přidání vlastního kódu
- Hlavní kód aplikace je v `main/main.c`
- Pro přidání dalších souborů je upravte `main/CMakeLists.txt`
- Pro přidání externích komponent vytvořte adresář `components/`
