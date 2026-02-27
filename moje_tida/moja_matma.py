
from modulo import modulo



def dodaj_modulo(a, b, mod):

    liczba_a = modulo(a, mod)
    liczba_b = modulo(b, mod)
    wynik = liczba_a + liczba_b

    return int(wynik)

def pomnoz_modulo(a, b, mod):

    liczba_a = modulo(a, mod)
    liczba_b = modulo(b, mod)
    wynik = liczba_a * liczba_b
    return int(wynik)

def czy_rowne_w_modulo(a, b, mod):

    liczba_a = modulo(a, mod)
    liczba_b = modulo(b, mod)
    return liczba_a == liczba_b

