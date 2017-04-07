# Toteutusdokumentti

## Ohjelman yleisrakenne

![Luokkakaavio](kuvat/luokkakaavio.png)

### Tärkeimpien luokkien kuvaus

HuffmanTree - Sisältää joukon toisiinsa linkitettyjä puusolmuja. Kyseinen rakenne voidaan muodostaa datasta merkkien esiintymismäärien perusteella tai rakentaa olemassa olevan puun perusteella (katso pakatun tiedoston rakenne).

TreeNode - Yksinkertainen datarakenne, jonka tarkoitus on pitää viitettä mahdollisiin lapsisolmuihin ja dataan.

Encoder - Luokan tehtävänä on pakata sille annettu data käyttäen Huffman puusta muodostettua pakkaustaulukkoa. Luokka on myös vastuussa Huffman puun muuttamisesta sopivaan muotoon tiedostoon pakkaamista varten.

Decoder - Luokan tehtävänä on purkaa sille annettu data, käyttäen Huffman puuta.

### Pakkauksen toiminta

![pakkaus](kuvat/Pakkaus.png)

### Purkamisen toiminta

![pukaminen](kuvat/Purkaminen.png)

### Pakatun tiedoston rakenne

Pakattu tiedosto koostuu kahdesta osasta: Huffman puu binäärimuodossa ja itse pakattu data. Kumpaakin osaa edeltää 64-bittinen etumerkitön kokonaisluku little-endian muodossa, joka kertoo sitä seuraavan osan pituuden biteissä. Puu on tallennttu esijärjestyksessä siten, että 0/False merkitsee jokaista solmua, jolla on lapsisolmuja, ja 1/True jokaista lehtisolmua. Lehtisolmua seuraa 8 bittiä, joka kertoo kyseisen lehtisolmun datan.

## Aika ja tilavaativuudet

### Huffman puun rakentaminen

```
function constructTree(Vector characters)
    priority_queue queue

    frequencies = calculateCharacterFrequencies(characters)
    for each character c in CHARACTERS
        if (frequencies[c] != 0)
            TreeNode leaf
            leaf.data = c
            leaf.frequency = frequencies[c]
            leaf.left = leaf.right = null
            queue.push(leaf)
        endif
    endfor

    while queue.size() > 1
        TreeNode left = queue.pop()
        queue.pop();
        TreeNode right = queue.pop()

        TreeNode parent
        parent.frequency = left.frequency + right.frequency
        parent.left = left
        parent.right = right
        queue.push(parent)
    endwhile

    setRoot(queue.pop())
endfunction


calculateCharacterFrequencies(Vector characters)
    Array frequencies

    for each character c in characters
        ++frequencies[c]
    endfor

    return frequencies
endfunction
```
Aikavaativuus "calculateCharacterFrequencies" funktiolla on O(n), jossa n on characters taulukossa olevien merkkien määrä. Aikavaativuus prioteettijonon täyttämisessa funktiossa "constructTree" on O(k log k) (binäärikekoon lisääminen ja poistaminen O(log k), joka tehdään k kertaa), jossa k on erilaisten merkkien määrä. Prioriteettijonoa purkaessa sieltä poistetaan aina kaksi solmua ja lisätään yksi. While-lauseke suoriteteaan siis k kertaa, joten koko silmukan aikavaativuus on myös O(k log k). Kokonaisuudessaan aikavaativuus on O(n + k log k) ja tilavaativuus O(k).

## Parannusehdotukset

Tiedon purkaminen on huomattavasti hitaampaa verrattuna tiedon pakkaamiseen. Purkamista voisi mahdollisesti nopeuttaa käyttämällä hakutaulukkoa. Toinen parannunusmahdollisuus olisi sisällyttää pakattuun tiedostoon tarkistussumma, jolla tiedoston eheys voitaisiin tarkistaa ennen purkamista.

