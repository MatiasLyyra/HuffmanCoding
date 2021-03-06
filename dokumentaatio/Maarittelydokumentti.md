# Määrittelydokumentti

## Aihe ja tavoite

Projektin tavoitteena on luoda komentoriviltä käytettävä ohjelma tiedoston pakkaamista ja purkamista varten. Toteutus tapahtuu C++:lla ja ensisijaisena kohteena on Windows-ympäristö. Riippuen projektin kulusta myös mahdollisesti Linux-ympäristössä toimiva ohjelma. Käytettävä pakkausalgoritmi on Huffmanin koodaus. Valitsin Huffmanin koodauksen, koska se vaikutti mielenkiintoiselta aiheelta ja tiedon pakkaus on aihealue, johon en ole aiemmin perehtynyt. Lisäksi projektin yhteydessä tulee toteuttaa tarvittava toiminnallisuus tiedostojen kirjoittamista ja lukemista esim. otsaketietojen lukeminen yms.

Henkilökohtainen tavoitteeni on oppia lisää ohjelmien toteutuksesta C++ kielellä.

## Tarvittavat tietorakenteet

**Prioriteettijono:** Toteutus minimi/maksimi keolla. Aikavaativuudet lisäämiselle ja poistamiselle O(log n). Tarvitaan mm. Huffman puun tehokkaassa rakentamisessa.

**Dynaaminen taulukko:** Taulukko, joka varaa lisää tilaa tarvittaessa. Yleiskäyttöinen tietorakenne, jota tarvitaan eri puolilla ohjelmaa.

**Vakiokokoinen taulukko(?):** Taulukko, jonka koko määritetään käännösaikana.

**Binääritaulukko:** Dynaaminen taulukko, johon voi tallentaa joukko yksittäisiä bittejä tehokkaasti. Tarvitaan esimerkiksi pakkaamisessa ja purkamisessa.

**Huffman puu:** Pakkauksessa ja purkamisessa käytettävä binääripuu. Lehtisolmut vastaavat syötteessä esiintyviä symboleita (tavuja). Polku puun juuresta lehtisolmuun kertoo kyseisen symbolin koodin. Esimerkiksi kaari vasempaan lapsisolmuun vastaa arvoa 0 ja vastaavasti oikeaan arvoa 1.

## Aikavaativuudet

Ohjelman toiminta voidaan jakaa kolmeen eri vaiheeseen: Huffman puun rakentaminen, pakkaus ja purkaminen. Eri merkkien määrä tulee vaikuttaamaan todennäköisesti huomattavasti vähemmän kokonaisuudessaan algoritmien ajankäyttöön kuin itse merkkien määrä. Tämä johtuu mahdollisten eri merkkien vähäisestä määrästä 256 kpl verrattuna mielivaltaiseen määrään merkkejä. 

### Huffman puun rakentaminen

Ohjelman tulee laskea eri symbolien esiintymismäärät kohteena olevassa tekstissä. Tämä voidaan toteuttaa O(n) ajassa, jossa n vastaa symbolien lukumäärää. Binääripuussa on korkeintaan 2k - 1 solmua yhteensä, jossa k on symbolien lukumäärä. Prioriteettijonolla, joka on toteutettu binäärikeolla, lisäämisen ja poistaminen aikavaativuus pahimmassa tapauksessa on O(log k). Prioriteettijonon täyttämiseen kuluu siis O(k log k) aikaa. Itse rakennusvaiheessa keosta poistetaan kaksi päällimmäistä solmua ja lisätään yksi tilalle. Tätä siis joudutaan tekemään k kertaa, joten rakennusvaiheen aikavaativuus on myös O(k log k).

Yhteensä siis koko rakentamiseen kuluu O(n + k log k) verran aikaa. Tilavaativuus on O(k) johtuen prioriteettijonosta ja taulukosta, joka tallentaa jokaisen symbolin esiintymisen määrän.

### Pakkaus

Pakkausta varten Huffman puu pitää käydä läpi syvyyssuuntaisella haulla. Jokainen solmu käsitellään vain kerran, joten aikavaativuus on O(k), jossa k on erilaisten symbolien määrä. Tämän jälkeen pakkausta varten symbolin koodi löytyy vakioajassa. Itse puu pitää myös muuttaa tallennettavaan muotoon. Tämän aikavaativuus on O(k), jokaisessa puun solmussa tulee käydä yhden kerran. Pakkaus tapahtuu siis ajassa O(k + n), jossa n on käsiteltävien symbolien määrä. Tilavaativuus on O(k + n) pakkaukseen käytettävän taulukon takia ja tuloksena olevan pakatun datan takia.

### Purkaminen

Purkamisessa syötteestä luetaan bittejä yksi kerrallaan ja liikutaan puussa niiden mukaan, kunnes lehtisolmu löytyy. Symbolin löytyminen puusta vois siis vaihdella lähes vakioaikaisesta aina puun korkeuteen saakka. Puu pitää myös muuttaa käytettävään muotoon pakkauksen jäljiltä, jonka aikavaativuus on O(k), jossa k on eri merkkien määrä. Pahimmassa tapauksessa purkamisessa aikavaativuus on O(nh), jossa n syötteessä olevien symbolien määrä ja h Huffman puun korkeus. Yhteensä aikavaativuus on siis O(nh + k). Tilavaativuus on O(n + k) puretun datan tallentamisen ja Huffman puun rakentamisen takia.

## Ohjelman käyttö ja syötteet

### Pakkaaminen

Ohjelma saa syötteenä käyttäjältä pakattavan tiedoston sijainnin ja pakatun tiedoston nimen ja sijainnin. Esimerkiksi: `HuffmanCoding pack -in "dokumentti.txt" -out "pakattu_dokumentti"`. Syötteenä annettu tiedosto ladataan muistiin taulukkona, joka sisältää tiedon yksittäisinä tavuina. 

Lisäksi, jos aikaa on tarpeeksi, ohjelmalle voisi antaa valmiin Huffman puun tiedoston valmiiksi, jolloin sitä ei tarvitsisi sisällyttää itse pakattuun tiedostoon.
Esimerkiksi: `HuffmanCoding pack -in "dokumentti.txt" -out "pakattu_dokumentti" -tree "english_text"`, jossa "english_text" sisältäisi valmiiksi Huffman puun, joka on rakennettu eri kirjainten ja merkkien esiintymistodennäköisyyksien pohjalta esimerkiksi englanninkielisessä tekstissä.

### Purkaminen

Vastaavasti purkaminen tapahtuisi esimerkiksi: `HuffmanCoding unpack -in "pakattu_dokumentti" -out "dokumentti.txt"`. Jos valmiina tallennettu Huffman puu ominaisuus toteutetaan, käyttö voisi olla seuraava `HuffmanCoding unpack -in "pakattu_dokumentti" -out "dokumentti.txt" -tree "english_text"`.
