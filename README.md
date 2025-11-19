| Supported Targets |  ESP32-S2 |
| ----------------- |  -------- |

# project description (CZ)

Vytvořte task (xTaskCreate()), který s vámi zvolenou periodou blikne LED-kou. Na
přípravcích Kaluga použijte adresovatelnou LED připojenou na pin IO45.
2) Připojte se k Wi-Fi (example wifi/getting_started/station). Vypište IP adresu, kterou ESP
dostalo přiřazenou. Doporučuji použít vlastní Wi-Fi hotspot ke kterému se ESP připojí.
3) Připojte se k NTP serveru, nakonfigurujte systémový čas v ESP a nastavte časové pásmo
ČR. Čas ve formátu yyyy-mm-dd hh:mm:ss se periodicky bude vypisovat do terminálu.
4) Umožněte změnu periody blikání LED-ky z úlohy 1) pomocí zapsání příkazu z PC terminálu
(example peripherals/uart/echo). Formát příkazu bude “PER:xxx“ kde xxx je perioda
v stovkách ms 123 je tedy 12,3 sekundy. Nastavenou délku periody v ms pošlete do PC.
5) Přidejte příkaz “UNIXTIME?“ na něj ESP odpoví posláním aktuálního UNIX-ového času.
6) Generujte opravdu náhodná čísla a zajistěte, že bude možné je generovat i pokud by došlo
k vypnutí Wi-Fi. Umožněte generování a vypsání náhodného čísla pomocí příkazu
“RANDOM?“. Výsledné číslo bude v hexadecimálním formátu a vždy bude mít šířku 64 bitů.
7) Zjistěte, zda ESP32-S2 (popřípadě jiné ESP32) obsahuje unikátní sériové číslo, které
jedinečně identifikuje každý čip. Popřípadě nějakou jinou hodnotu, kterou je možné použít
jako unikátní sériové číslo. Toto číslo v hexadecimálním formátu vypište do terminálu při
inicializaci.
8) Upravte projekt tak, aby nedocházelo k vypisování žádných logů, které jste sami
nevytvořili. ESP tedy na sériovou linku bude posílat jen a pouze váš vlastní text. Jedinou
přijatelnou výjimkou jsou logy, které ESP posílá před načtením aplikačního firmwaru
(vašeho kódu) během chodu bootloaderu.
9) Přidejte snímání teploty ESP pomocí interního teplotního čidla. Výpis teploty bude v °C a °F
na sériovou linku pomocí příkazu “TEMPERATURE?“. Teploty vypište s přesností na
desetinu stupně.
10) Generujte sinusový signál na pinu IO17. Zobrazte jej na osciloskopu. Amplituda sinusového
signálu bude co největší. Frekvenci zvolte libovolně. Generovaný signál zobrazte na
osciloskopu.

# additional info

In code there are some more function other than whats specified there however theyre not really important
For the project to work on other machines path needs to be set correctly in settings.json and in c_cpp_properties.json
Also correct COM needs to be specified

