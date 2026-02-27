
import unittest
import moja_matma


class TestModuloFunctions(unittest.TestCase):

    def test_dodawanie_proste(self):
        wynik = moja_matma.dodaj_modulo(3, 5, 7)
        self.assertEqual(wynik, 1)

    def test_dodawanie_z_zerem(self):
        wynik = moja_matma.dodaj_modulo(0, 5, 5)
        self.assertEqual(wynik, 0)  

    def test_mnozenie_proste(self):
        wynik = moja_matma.pomnoz_modulo(4, 3, 10)
        self.assertEqual(wynik, 2)

    def test_mnozenie_przez_zero(self):
        wynik = moja_matma.pomnoz_modulo(99, 0, 7)
        self.assertEqual(wynik, 0)

    def test_liczby_rowne(self):
        wynik = moja_matma.czy_rowne_w_modulo(7, 14, 7)
        self.assertTrue(wynik)

    def test_liczby_rozne(self):
        wynik = moja_matma.czy_rowne_w_modulo(7, 8, 7)
        self.assertFalse(wynik)

if __name__ == '__main__':
    unittest.main()