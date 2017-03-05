# RSRPCalclulator
Programista płakał jak komitował xD

Wyznaczenie rozkładu mocy sygnału referencyjnego RSRP dla stacji bazowych eNodeB w sieci LTE.

FICZERY (Jak coś nie działa lub się wywali to znaczy, że coś źle zrobiłeś :D)

1. Możliwość dodania stacji bazowej.
Celem jest umożliwienie określenia położenia stacji bazowej, wysokości umieszczenia anteny nad terenem oraz nadania nazwy, po której będzie identyfikowana.

2. Zaznaczenie położenia stacji bazowej na mapie.
Po dodaniu stacji bazowej, na mapie zostanie zaznaczone jej położenie w postaci czerwonego kółka z krzyżykiem.

3. Możliwość wpisania wszystkich potrzebnych parametrów sektora.
Celem jest umożliwienie, dodania sektora do danej stacji bazowej. Użytkownik ma możliwość wypełnienia formularza, zawierającego wszystkie parametry istotne dla planowania zasięgu sektora, oraz wczytania pliku z charakterystyką anteny. 
Plik musi być w formacie „csv”, gdzie kąt oraz odpowiadające mu tłumienie musi być oddzielone średnikiem. 
Przykładowe pliki z charakterystykami zostały dołączone do folderu z aplikacją.

4. Widok mapy
Po uruchomieniu aplikacji zostaje załadowana mapa wysokościowa, oraz wyświetlona w centralnej części okna aplikacji.

5. Parametry toru odbiorczego.
Użytkownik ma możliwość określenia parametrów toru odbiorczego takich jak zysk anteny, wysokość terminala oraz wartość tłumienia toru odbiorczego.

6. Zmiana minimalnej wartości sygnały RSRP.
Użytkownik ma możliwość określenia minimalnej granicznej wartości RSRP, dla której będą wykonywane obliczenia. Poniżej tej wartości wyniki nie zostaną zapisane i zobrazowane.

7. Domyślna minimalna wartość sygnału RSRP.
Domyślna minimalna wartość sygnału RSRP jest określona jako -120 [dBm]. 3GPP definiuje najmniejszą wartość RSRP jako -140 [dBm], jednak w rzeczywistości wymaga się zapewnienia SNIR większego jak 20 [dB]. Dlatego przy planowaniu sieci przyjmuje się
minimalną wartość RSRP na poziomie -120 [dBm]. Taka wartość będzie wyświetlona w okienku „Minimum value of RSRP”, dopóki nie zostanie zmieniona przez użytkownika.

8. Zaznaczenie obszaru obliczeń.
Użytkownik ma możliwość zaznaczenia obszaru obliczeń, po przez zaznaczenie na mapie kwadratu.

9. Zapamiętanie obszaru obliczeń.
Obszar obliczeń jest zapamiętany do czasu jego ponownego zaznaczenia. Jeżeli użytkownik zaznaczy obszar to wszystkie kolejne obliczenia będą wyznaczane dla nowego obszaru.

10. Powiększanie oraz zmniejszanie mapy.
Użytkownik ma możliwość zmniejszenia oraz powiększenia obrazu mapy, poprzez kliknięcie przycisku „Zoom in” lub „Zoom out”.

11. Uruchomienie kalkulacji.
Po wciśnięciu przycisku „Run” użytkownik spowoduje rozpoczęcie obliczania rozkładu sygnału referencyjnego dla zadanych parametrów oraz obszaru.

12. Reprezentacja wyników.
Gdy program zakończy wszystkie obliczenia, automatycznie zostanie wyrysowana kolorowa mapa określająca wartość rozkładu sygnały RSRP.

13. Kolorowa skala.
Po pojawieniu się rozkładu poziomu sygnału RSRP na mapie, w lewej części okna aplikacji, pojawi się kolorowa skala, określająca przypisanie kolorów dla określonych poziomów RSRP. Na końcu i początku skali pojawią się wartości, odpowiednio, największa oraz najmniejsza obliczona wartość sygnału RSRP.

14. Analiza wartości w danym punkcie.
Użytkownik ma możliwość sprawdzenia wartości wyznaczonego RSRP w danym punkcie, po zaznaczeniu opcji „Value from point”. Gdy użytkownik kliknie myszką w wybrany punkt na kolorowej mapie rozkładu, obok opcji „Value from point”, pojawi się obliczona wartość sygnału referencyjnego w tym punkcie, wyrażona w [dBm].

15. Suwak minimum RSRP.
Użytkownik ma do dyspozycji suwak, określający minimalną, wyświetlaną wartość sygnału RSRP. Po zmianie pozycji suwaka, na mapie pojawią się wartości sygnału większe od wartości ustalonej poprzez suwak. Szybkie przesuwanie suwakiem dynamicznie zmienia wyświetlane wartości. Po prawej stronie suwaka wyświetla się aktualna wartość progu RSRP. Po lewej stronie wyświetla się wartość progu RSRP dla, którego zostały wykonane obliczenia (czyli najmniejsza wartość do jakiej można przesunąć suwak).

16. Zbadanie odległości na mapie.
Po zaznaczeniu opcji profil terenu jest możliwość sprawdzenia odległości na mapie. W tym celu należy kliknąć w punkt początkowy, a następnie przesunąć myszką do punktu końcowego i puścić przycisk. Na mapie pojawi się linia łącząca dwa punkty. Obok opcji „Terrain profile” pojawi się odległość między zaznaczonymi dwoma punktami wyrażona w metrach.

17. Wyznaczenia profilu terenu. //TODO
Po zaznaczeniu dwóch punktów w taki sposób ja w wymaganiu nr 16, oraz kliknięciu przycisku „show terrain profile” wyświetli się okno pokazujące profil terenu oraz wartość sygnału w funkcji odległości po miedzy zaznaczonymi punktami.

18. Zapisanie konfiguracji sieci. //TODO
Użytkownik ma możliwość zapisania konfiguracji sieci, po kliknięciu przycisku „Save configuration”, znajdującego się w Menu na pasku zadań.

19. Wgranie konfiguracji sieci z pliku. //TODO
Jeżeli użytkownik posiada zapisaną konfiguracje sieci, ma możliwość wgrania jej poprzez wybranie pliku z zapisem. W tym celu z opcji „Menu” na pasku zadań należy wybrać opcję „Import configuration”.

20. Możliwość zapisu obliczonych danych. //TODO
Użytkownik ma możliwość zapisania powstałych obliczeń, w celu późniejszego ich wczytania oraz ponownej reprezentacji w postaci kolorowej mapy.

21. Wyświetlenie drzewa obiektów. //TODO
Po dodaniu stacji bazowych oraz sektorów, zostaną wyświetlone wszystkie powstałe obiekty w postaci drzewa – stacje bazowe oraz przynależne do nich sektory wraz z wartościami parametrów.

22. Edycja wprowadzonych danych. //TODO
Użytkownik ma możliwość edytowania wprowadzonych obiektów sieci.

23. Usuwanie danych. //TODO
Użytkownik ma możliwość usunięcia jednego (wybranego) lub wszystkich obiektów sieci.
