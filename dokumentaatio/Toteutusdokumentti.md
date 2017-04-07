# Toteutusdokumentti

## Ohjelman yleisrakenne

### Tärkeimpien luokkien kuvaus

HuffmanTree - Sisältää joukon toisiinsa linkitettyjä puusolmuja. Kyseinen rakenne voidaan muodostaa datasta merkkien esiintymismäärien perusteella tai rakentaa olemassa olevan puun perusteella (katso pakatun tiedoston rakenne).

TreeNode - Yksinkertainen datarakenne, jonka tarkoitus on pitää viitettä mahdollisiin lapsisolmuihin ja dataan.

Encoder - Luokan tehtävänä on pakata sille annettu data käyttäen Huffman puusta muodostettua pakkaustaulukkoa. Luokka on myös vastuussa Huffman puun muuttamisesta sopivaan muotoon tiedostoon pakkaamista varten.

Decoder - Luokan tehtävänä on purkaa sille annettu data, käyttäen Huffman puuta.
