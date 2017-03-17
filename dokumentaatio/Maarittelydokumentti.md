# Määrittelydokumentti

## Aihe ja tavoite

Projektin tavoitteena on luoda koemntoriviltä käytettävä ohjelma tiedoston pakkaamista ja purkamista varten. Totetus tapahtuu C++:lla ja ensisijaisena kohteena on Windows-ympäristö. Riippuen projektin kulusta myös mahdollisesti Linux-ympäristössä toimiva ohjelma. Käytettävä pakkausalgortimi on Huffmanin koodaus. Valitsin Huffmanin koodauksen, koska se vaikutti mielenkiintoiselta aiheelta ja tiedon pakkaus on aihealue, johon en ole aiemmin perehtynyt. Lisäksi projektin yhteydessä tulee toteuttaa tarvittava toiminnallisuus tiedostojen kirjoittamista ja lukemista esim. otsaketietojen lukeminen yms.

Henkilökohtainen tavoitteeni on oppia lisää ohjelmien toteutuksesta C++ kielellä.

## Tarvittavat tietorakenteet

Prioriteettijono: Totetus minimi/maksimi keolla. Aikavaativudet lisäämiselle ja poistamiselle O(log n). Tarvitaan mm. Huffmanin puun tehokkaassa rakentamisessa.

Dynaaminen taulukko: Taulukko, joka varaa lisää tilaa tarvittaessa. Yleiskäyttöinen tietorakenne, jota tarvitaan eri puolilla ohjelmaa.

Vakiokokoinen taulukko(?): Taulukko, jonka koko määritetään käännösaikana.

Binääritaulukko: Dynaaminen taulukko, johon voi tallentaa joukko yksittäsiä bittejä tehokkaasti. Tarvitaan esimerkiksi pakkaamisessa ja purkamisessa.

Huffman puu: Pakkauksessa ja purkamisessa käytettävä binääripuu. Lehtisolmut vastaavat syötteessä esiintyviä symboleita (tavuja). Polku puun juuresta lehtisolmuun kertoo kyseisen symbolin koodin. Esimerkiksi kaari vasempaan lapsisolmuun vastaa arvoa 0 ja vastaavasti oikeaan arvoa 1.

## Ohjelman käyttö ja syötteet

### Pakkaaminen

Ohjelma saa syötteenä käyttäjältä pakattavan tiedoston sijainnin ja pakatun tiedoston nimen ja sijainnin. Esimerkiksi: `HuffmanCoding pack -in "dokumentti.txt" -out "pakattu_dokumentti".

Lisäksi, jos aikaa on tarpeeksi, ohjelmalle voisi antaa valmiin Huffmanin puun tiedoston valmiiksi, jolloin sitä ei tarvitsisi sisällyttää itse pakattuun tiedostoon.
Esimerkiksi: `HuffmanCoding pack -in "dokumentti.txt" -out "pakattu_dokumentti" -tree "english_text"`, jossa "english_text" sisältäisi valmiiksi Huffmanin puun, joka on rakennettu eri kirjainten ja merkkien esiintymistodennäköisyyksien pohjalta englanninkielisessä tekstissä.

### Purkaminen

Vastaavasti purkaminen tapahtuisi esimerkiksi: `HuffmanCoding unpack -in "pakattu_dokumentti" -out "dokumentti.txt"`. Jos valmiina tallenttu Huffmanin puu ominaisuus toteuteaan, käyttö voisi olla seuraava `HuffmanCoding unpack -in "pakattu_dokumentti" -out "dokumentti.txt" -tree "english_text".
