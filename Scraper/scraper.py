# https://cenoteka.rs/kategorija/namirnice
# https://cenoteka.rs/kategorija/mlecni-proizvodi
# https://cenoteka.rs/kategorija/voce-i-povrce
# https://cenoteka.rs/kategorija/meso-i-riba

from selenium import webdriver
import sys
import re
from bs4 import BeautifulSoup

# Incijalizacija selenium kontrole pretrazivaca
browser = webdriver.Firefox()

# Kategorije za prikupljanje cena
kategorije = ["https://cenoteka.rs/kategorija/namirnice", "https://cenoteka.rs/kategorija/mlecni-proizvodi", "https://cenoteka.rs/kategorija/voce-i-povrce", "https://cenoteka.rs/kategorija/meso-i-riba"]

# Nalazenje linkova svih namirnica
namirnice = []
for kategorija in kategorije:
	browser.get(kategorija)
	bsObj = BeautifulSoup(browser.page_source, "lxml")
	for namirnica in bsObj.findAll("div",{"class":re.compile("col-6")}):
		namirnica=namirnica.find("a",href = re.compile("proizvodi"))
		if namirnica is not None:
			namirnice.append(namirnica)

prodavnice = ["IDEA", "Gomex", "Maxi", "Univerexport", "Tempo", "DIS", "Roda","LIDL"]

# Izvlacenje informacija za artikle
baza = open("database.txt", "w+")
for namirnica in namirnice:
	stranica = 1
	# Menjanje stranica
	browser.get("https://cenoteka.rs" + namirnica["href"] + "?page=" + str(stranica))
	bsObj = BeautifulSoup(browser.page_source, "lxml")
	while bsObj.find("div", {"class":re.compile("alert-danger")}) is None:
		browser.get("https://cenoteka.rs" + namirnica["href"] + "?page=" + str(stranica))
		bsObj = BeautifulSoup(browser.page_source, "lxml")
		for produkt in bsObj.findAll("div", {"data-product-id":re.compile("\d+")}):
			try:
				ime = produkt.find("a", href = re.compile("artikal"), text=re.compile("\w+")).get_text()
			except AttributeError:
				continue
			mera = produkt.find("div", {"class":re.compile("text-center")}).get_text()
			#mera=format(mera)
			mincena = 10000000
			prodavnica = 0
			minprodavnica = 0
			for cena in produkt.findAll("div", {"class":re.compile("^price")}):
				cena = re.findall("[\d\.,]+", cena.get_text())
				if len(cena) != 0:
					cena=cena[0].replace(".","")
					cena = int(float(cena.replace(",", ".")))
					if cena < mincena:
						minprodavnica = prodavnica
						mincena = cena
				prodavnica+= 1
			baza.write(ime.lower() + "\t" + mera.lower().replace(" ","\t") + "\t" + str(mincena).lower() + "\t" + prodavnice[minprodavnica].lower() + "\r\n")
		stranica+= 1

baza.close()
browser.quit()
sys.exit(0)
