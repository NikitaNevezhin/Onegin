import re

roman_numbers = [
    'I', 'II', 'III', 'IV', 'V', 'VI', 'VII', 'VIII', 'IX', 'X',
    'XI', 'XII', 'XIII', 'XIV', 'XV', 'XVI', 'XVII', 'XVIII', 'XIX', 'XX',
    'XXI', 'XXII', 'XXIII', 'XXIV', 'XXV', 'XXVI', 'XXVII', 'XXVIII', 'XXIX', 'XXX',
    'XXXI', 'XXXII', 'XXXIII', 'XXXIV', 'XXXV', 'XXXVI', 'XXXVII', 'XXXVIII', 'XXXIX', 'XL',
    'XLI', 'XLII', 'XLIII', 'XLIV', 'XLV', 'XLVI', 'XLVII', 'XLVIII', 'XLIX', 'L',
    'LI', 'LII', 'LIII', 'LIV', 'LV', 'LVI', 'LVII', 'LVIII', 'LIX', 'LX',
    'LXI', 'LXII', 'LXIII', 'LXIV', 'LXV', 'LXVI', 'LXVII', 'LXVIII', 'LXIX', 'LXX'
]

note_pattern = r'\([0-9]+\)'

in_note = False

with open("OneginText.txt", "r", encoding="utf8") as read_file, \
     open("RawOneginText.txt", "w", encoding="utf8") as write_file:

    for line in read_file.readlines():
        if '[' in line:
            if ']' not in line:
                in_note = True
            continue

        if "]" in line:
            in_note = False
            continue

        if in_note:
            continue

        if line == "\n" or any(num in line for num in roman_numbers):
            continue
        else:
            line = line.replace("’", "'")
            line = line.replace("“", '"')
            line = line.replace("”", '"')
            line = line.replace("—", "-")
            write_file.write(re.sub(note_pattern, "", line))


