# Testausdokumentti

## Yksikkötestaus

Projektissa on käytössä Google Test -ohjelmistokehys, jonka avulla koodin teknistä toimivuutta testataan. Testien kattavuudet ovat nähtävissä [täältä](https://htmlpreview.github.io/?https://github.com/MatiasLyyra/HuffmanCoding/blob/master/dokumentaatio/coverage/index.html).

## Pakkauksen testaus

### Luonnolliset kielet

Testeissä käytetyt tekstit:

[Frankenstein, by Mary Wollstonecraft (Godwin) Shelley](http://www.gutenberg.org/cache/epub/84/pg84.txt)

[The Kalevala, by Elias Lönnrot](http://www.gutenberg.org/cache/epub/7000/pg7000.txt)

Frankenstein-teksti oli kooltaan alun perin 438 KB ja pakkauksen jälkeen 247 KB. HuffmanCoding pienensi siis tiedoston kokoa noin 1.77 kertaisesti. Kalevalan kohdalla puolestaan alkuperäinen koko oli 643 KB ja pakattu koko oli 364 KB. Tiedoston koon vähennys oli siis suunnilleen yhtä suuri kuin Frankensteinin kohdalla.

## Tehokkuuden testaus
