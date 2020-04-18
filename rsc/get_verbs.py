import sys
print("Am I in a venv: ", hasattr(sys, "real_prefix"))

import requests
from lxml import etree

URL: str = "https://www.allemandfacile.com/exercices/exercice-allemand-2/exercice-allemand-22677.php"
SEPARATOR: str = ","

def get_texts(td) -> str:
    """
    Recursive function: returns the text content,
    or the concatenation of the text content of sub-elements.
    """
    if td.text:
        return td.text.lower()
    else:
        return " ".join(get_texts(c) for c in td)

def write_line(file, a, b, c, d):
    file.write(f'"{a}"{SEPARATOR}"{b}"{SEPARATOR}"{c}"{SEPARATOR}"{d}"\n')

response = requests.get(URL)
if (response.status_code == 200):
    root = etree.HTML(response.content)
    
    with open("verbs.csv", mode="w+", encoding="UTF-8") as f:
        write_line(f, "infinitive", "time 1", "time 2", "translation")
        first = True  # We will skip 1st row

        for table_body in root.xpath("//article//div[@align='center']/table/tbody"):
            for row in table_body:
                if first:
                    first = False
                    continue

                inf = get_texts(row[0]).strip()
                trans = get_texts(row[4]).strip()
                time1 = get_texts(row[2]).strip()
                time2 = get_texts(row[3]).strip()

                write_line(f, inf, time1, time2, trans)
    print("DONE")
else:
    print("ERROR: ", response.status_code)
